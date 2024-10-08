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
#include <numeric>
#include <limits.h>

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
#include <eoGreedyOrderXover.h>
#include <eoTwoOptMutation.h>

using namespace std;

// VARIAVEIS GLOBAIS
std::pair<double, double> origin;                   // ponto de partida
std::vector<std::pair<double, double>> coordenadas; // pontos de entregas
std::vector<int> pesos;                             // peso de cada entrega
int capacity;
// int minimum_vehicles;
int infinity = std::numeric_limits<int>::max();

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
    int veiculo = 1;
    distancia_veiculo = (*matrix)[num_deliveries][_chrom[i]];
    int sum_of_elems = std::accumulate(pesos.begin(), pesos.end(), 0);
    
    // std::ofstream out("/home/eiki/cvrp/eo/tutorial/Lesson1/customers.txt", std::ios::out | std::ios::app);


    while (j < num_deliveries) //&& veiculo <= minimum_vehicles
    {
        if ((peso_atual + pesos[_chrom[j]] > carga_max))
        {
            peso_total += peso_atual;
            total_distancia_veiculos += distancia_veiculo + (*matrix)[num_deliveries][_chrom[i]]; // last customer to origin point

            // reset variables
            peso_atual = pesos[_chrom[j]];
            distancia_veiculo = (*matrix)[num_deliveries][_chrom[j]];
            veiculo++;
        }
        else
        {   
            // if (veiculo > minimum_vehicles){
            //     throw std::runtime_error("Número de Veículos ultrapassou o valor ótimo!");
            // }
            peso_atual += pesos[_chrom[j]];
            distancia_veiculo += (*matrix)[_chrom[i]][_chrom[j]];
        }
        i++;
        j++;
    }
    
    if (peso_total != sum_of_elems)
    {
        peso_total += peso_atual;
        total_distancia_veiculos += distancia_veiculo +  (*matrix)[num_deliveries][_chrom[i]];
    }

    // if (veiculo < minimum_vehicles){
    //     throw std::runtime_error("Menos Veiculos que o valor ótimo!");
    // }

    return total_distancia_veiculos;
}

void main_function(int argc, std::string instance_name)
{
    /*
     * argv[1]: json file name
     */
    std::cout << fixed;

    // std::string instance_name = argv[1];

    // std::string fullPath = "/home/eiki/cvrp/eo/tutorial/Lesson1/dataset/Vrp-Set-A/A/" + instance_name;
    // std::string fullPath = "/home/eiki/cvrp/eo/tutorial/Lesson1/dataset/Uchoa/" + instance_name;
    std::string fullPath = "/home/eiki/cvrp/eo/tutorial/Lesson1/dataset/" + instance_name;

    std::ifstream f(fullPath);
    auto jsonDados = nlohmann::json::parse(f);

    capacity = jsonDados["capacity"];
    int dimension = jsonDados["dimension"];
    // minimum_vehicles = jsonDados["minimum_vehicles"];
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
    const unsigned int POP_SIZE = 200;        // Tamanho da população. Padrão = 80.
    const unsigned int MAX_GEN = 1000;        // Número de gerações. Padrão 100.
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

    // o ver será substituido aqui pelo bash.
    // CROSSOVER
    
    // eoGreedyXover<Chrom> xover(*matrix);
	// eoPartiallyMappedXover<Chrom> xover;   //converge mt rapido
    // eoCycleXover<Chrom> xover; // converge mto rapido
    // eoOrderXover<Chrom> xover;
    eoPrecedencePreserveXover<Chrom> xover;  //converge mto rapido
    // eoGreedyOrderXover<Chrom> xover(*matrix, pesos, 10);
    
    // eoLinearOrderXover<Chrom> xover; // errado
    // eoOrderXover2<Chrom> xover; //converge mto rapido

    // MUTATION
    // eoUniformMutation<Chrom> mutation(EPSILON);
    eoTwoOptMutation<Chrom> mutation;

    // termination condition
    // stop after MAX_GEN generations
    eoGenContinue<Chrom> continuator(MAX_GEN);

    std::stringstream instance_path;

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
        if (argc >= 2){
            std::string instance_name = argv[1];
            main_function(argc, instance_name);
        }

    }
    catch (exception &e)
    {
        cout << "Exceção: " << e.what() << "\n";
    }
    return 1;
}
