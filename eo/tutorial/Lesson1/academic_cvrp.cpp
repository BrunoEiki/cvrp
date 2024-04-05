#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <algorithm>

#include <nlohmann/json.hpp>

#include <eo>
#include <es.h>
#include <eoInt.h>
#include <eoSurviveAndDie.h>
#include <eoOrderXover.h>
#include <eoOrderXover2.h>
#include <eoPMXover.h>
#include <eoLinearOrderXover.h>
#include <eoPMXover.h>
#include <eoCycleXover.h>
#include <eoPrecedencePreserveXover.h>
#include <eoPartiallyMappedXover.h>
#include <eoGreedyXover.h>
#include <eoTwoOptMutation.h>

using namespace std;

// VARIAVEIS GLOBAIS
std::pair<double, double> origin;                   // ponto de partida
std::vector<std::pair<double, double>> coordenadas; // pontos de entregas
std::vector<int> pesos;                             // peso de cada entrega
int capacity;

std::vector<std::vector<double>> *matrix; // matriz com distâncias euclidianas

std::string readBuffer;

double lng, lat;

// REPRESENTATION
//-----------------------------------------------------------------------------
// define your individuals
// typedef eoReal<double> Indi;

typedef eoVector<double, int32_t> Chrom;

double euclidian_distance(double x1_point, double y1_point, double x2_point, double y2_point)
{
    return sqrt(pow(x2_point - x1_point, 2) + pow(y2_point - y1_point, 2));
}

void create_distance_matrix(std::vector<std::vector<double>> &matrix, int individual_size)
{
    const size_t numDeliveries = individual_size;
    // std::vector<std::vector<double>> *matrix = new std::vector<std::vector<double>>(numDeliveries + 1.0, std::vector<double>(numDeliveries + 1.0, 0.0));

    for (size_t i = 0; i < numDeliveries; i++)
    {
        // 1. Não existe distância entre entrega de índice igual
        // 2. A origem não está entre os pontos de entrega
        // 3. Convencionou-se que a distância da origem até a primeira
        // entrega (ou entrega 0) está na extremidade da matriz. Se
        // existem 5 entregas, a matriz terá tamanho 6 e tal distância
        // vai estar em [i][5]

        double originDist = euclidian_distance(origin.first, origin.second,
                                               coordenadas[i].first, coordenadas[i].second);
        matrix[numDeliveries][i] = originDist;
        matrix[i][numDeliveries] = originDist;

        for (size_t j = 0; j < numDeliveries; j++)
        {
            if (i != j)
            {
                // double dist = routingService->distanceBetween(currentDelivery.point, instance.deliveries.at(j).point);
                double dist = euclidian_distance(coordenadas[i].first, coordenadas[i].second,
                                                 coordenadas[j].first, coordenadas[j].second);
                matrix[i][j] = dist;
                matrix[j][i] = dist;
            }
        }
    }
};

void gerarVetorAleatorio(Chrom &_chrom, int n)
{
    for (int i = 0; i < n; ++i)
    {
        _chrom.push_back(i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(_chrom.begin(), _chrom.end(), gen);
}

// EVAL
//-----------------------------------------------------------------------------
// uma função fitness que calcula a distância total percorrida mantendo a restrição
// de capacidade.
//    @param _indi Um indivíduo de valores reais
double real_value(const Chrom &_chrom)
{
    std::string entregas;
    int carga_max = capacity; // Carga Maxima padrao = 180
    int num_deliveries = pesos.size();
    int peso_atual = pesos[_chrom[0]];
    int peso_total = 0;
    double distancia_veiculo = 0.0;
    double total_distancia_veiculos = 0.0;

    int i = 0;
    int j = 1;
    int veiculo = 0;
    distancia_veiculo = (*matrix)[num_deliveries][_chrom[i]];

    while (j < num_deliveries)
    {
        if (peso_atual + pesos[_chrom[j]] > carga_max)
        {
            peso_total += peso_atual;
            total_distancia_veiculos += distancia_veiculo;

            // reset variables
            peso_atual = pesos[_chrom[j]];
            distancia_veiculo = (*matrix)[num_deliveries][_chrom[j]];
            veiculo++;
            std::ofstream out("/home/eiki/cvrp/eo/tutorial/Lesson1/nome.txt", std::ios::out | std::ios::app);
            out << "Veiculo " << veiculo << "\n";
        }
        else
        {
            peso_atual += pesos[_chrom[j]];
            distancia_veiculo += (*matrix)[_chrom[i]][_chrom[j]];
        }
        i++;
        j++;
    }

    return total_distancia_veiculos;
}

void main_function(int argc, char *argv[])
{
    /*
     * argv[1]: json file name
     */
    std::cout << fixed;

    std::cout << argv[1];

    std::ifstream f("/home/eiki/cvrp/eo/tutorial/Lesson1/dataset/Vrp-Set-A/A/A-n32-k5.vrp.json");
    auto jsonDados = nlohmann::json::parse(f);

    capacity = jsonDados["capacity"];
    int dimension = jsonDados["dimension"];
    origin = {jsonDados["origin"]["x"], jsonDados["origin"]["y"]};

    if (jsonDados["deliveries"].is_array())
    {
        for (const auto &entrega : jsonDados["deliveries"])
        {
            lng = entrega["point"]["x"].get<double>();
            lat = entrega["point"]["y"].get<double>();
            coordenadas.emplace_back(lng, lat);

            pesos.emplace_back(entrega["size"]);
        }
    }

    // =======================
    //       PARAMETROS
    // ========================
    const unsigned int SEED = 42;
    const unsigned int IND_SIZE = dimension; // Tamanho do indivíduo (solução).
    const unsigned int POP_SIZE = 80;        // Tamanho da população. Padrão = 80.
    const unsigned int MAX_GEN = 100;        // Número de gerações. Padrão 100.
    const unsigned int TOURNAMENT_SIZE = 2;
    const float CROSS_RATE = 0.8;
    const float MUTATION_RATE = 0.01;

    rng.reseed(SEED);
    matrix = new std::vector<std::vector<double>>(IND_SIZE + 1, std::vector<double>(IND_SIZE + 1, 0.0));
    create_distance_matrix(*matrix, IND_SIZE);

    // EVAL
    /////////////////////////////
    // Fitness function
    ////////////////////////////
    // Evaluation: from a plain C++ fn to an EvalFunc Object
    eoEvalFuncPtr<Chrom> eval(real_value);

    // ======================
    // GERAÇÃO DA POPULAÇÃO
    // ======================
    // Individuo: vetor solução com a ordem das entregas

    eoPop<Chrom> pop;
    // std::cout << "\nTamanho do Individuo: " << IND_SIZE;
    // fill it!
    for (unsigned int igeno = 0; igeno < POP_SIZE; igeno++)
    {
        Chrom v; // void individual, to be filled
        gerarVetorAleatorio(v, IND_SIZE);
        // cout << "\n\nindividuo " << igeno << ": ";
        eval(v);          // evaluate it
        pop.push_back(v); // and put it in the population
    }

    // SELECTION
    eoDetTournamentSelect<Chrom> select(TOURNAMENT_SIZE);
    // eoDeterministicSaDReplacement<Chrom> select(10, 10);

    // CROSSOVER
    eoCycleXover<Chrom> xover; // converge mto rapido
    // eoPartiallyMappedXover<Chrom> xover;   //converge mt rapido
    // eoPrecedencePreserveXover<Chrom> xover;  //converge mto rapido
    // eoLinearOrderXover<Chrom> xover; // errado
    // eoOrderXover2<Chrom> xover; //converge mto rapido
    // eoOrderXover<Chrom> xover;
    // eoGreedyXover<Chrom> xover(*matrix);

    // MUTATION
    // eoUniformMutation<Chrom> mutation(EPSILON);
    eoTwoOptMutation<Chrom> mutation;

    // termination condition
    // stop after MAX_GEN generations
    eoGenContinue<Chrom> continuator(MAX_GEN);

    // TERMINATION CONDITION
    eoSGA<Chrom> gga(select, xover, CROSS_RATE,
                     mutation, MUTATION_RATE, eval, continuator);

    gga(pop);

    // pop.sort();
    // cout << "\n\nCONFIGURAÇAO FINAL";
    // cout << "\n===========================";
    // cout << "\nDistTot  Tam   Indices";
    // cout << "\n=========================== pop: " << pop;
}

int main(int argc, char **argv)
{
    try
    {
        main_function(argc, argv);
    }
    catch (exception &e)
    {
        cout << "Exceção: " << e.what() << "\n";
    }
    return 1;
}
