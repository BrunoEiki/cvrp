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

#include <curl/curl.h>
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
#include <eoTwoOptMutation.h>

using namespace std;

static size_t WriteCallback(char *contents, size_t size, size_t nmemb, char *buffer_in)
{
    ((std::string *)buffer_in)->append(contents, size * nmemb);
    return size * nmemb;
}

// VARIAVEIS GLOBAIS
std::ifstream file("./cvrp-0-to-99.json");
nlohmann::json jsonDados;

std::pair<double, double> origem;                   // ponto de partida
std::vector<std::pair<double, double>> coordenadas; // pontos de entregas
std::vector<int> pesos;                             // peso de cada entrega

double lng, lat;

// REPRESENTATION
//-----------------------------------------------------------------------------
// define your individuals
// typedef eoReal<double> Indi;

typedef eoInt<double> Chrom;

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
    int carga_max = 180;

    int i = 0;
    int peso_atual;
    int pop_size = pesos.size();
    double soma_distancia = 0.0;

    while (i < pop_size)
    {
        // VARIAVEIS PARA REQUISIÇÃO
        CURL *curl;
        CURLcode res;
        std::string readBuffer;
        std::string url;

        std::stringstream coordinate;
        std::stringstream requisicao;

        peso_atual = 0;

        // * Hub coordinate
        coordinate << origem.first << "," << origem.second << ";";
        while (true)
        {
            if ((i == pop_size) || (peso_atual + pesos[_chrom[i]] > carga_max))
                break;

            peso_atual += pesos[_chrom[i]];
            coordinate << coordenadas[_chrom[i]].first << "," << coordenadas[_chrom[i]].second << ";";
            i++;
        }
        // Return back to hub
        coordinate << origem.first << "," << origem.second;

        // ==========================================================
        // REQUISITAR CALCULO DE DISTANCIA NO SERVIDOR LOCAL DO OSRM
        // ==========================================================
        curl = curl_easy_init();
        entregas = coordinate.str();
        requisicao << "http://localhost:5000/route/v1/driving/" + entregas + "?annotations=distance&continue_straight=false";
        url = requisicao.str();

        if (curl)
        {

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);

            if (res == CURLE_OK)
            {
                // SOMAR AS DISTANCIAS DE CADA VEICULO
                nlohmann::json jsonObject = nlohmann::json::parse(readBuffer);
                // ! DOUBLE CHECK
                soma_distancia += jsonObject["routes"][0]["distance"].get<double>();
            }
            else
            {
                std::cerr << "Erro ao realizar a solicitação HTTP: " << curl_easy_strerror(res) << std::endl;
            }
            curl_easy_cleanup(curl);
        }
    }
    return soma_distancia;
}

void main_function(int /*argc*/, char ** /*argv*/)
{
    std::cout << fixed;

    // =======================================
    // IMPORTAR AS COORDENADAS DAS ENTREGAS
    // =======================================
    try
    {
        file >> jsonDados;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro durante a leitura do arquivo JSON: " << e.what() << std::endl;
    }

    // ! osrm requer primeiro "lng" depois "lat".
    lng = jsonDados["origin"]["lng"].get<double>();
    lat = jsonDados["origin"]["lat"].get<double>();
    origem = {lng, lat};

    if (jsonDados["deliveries"].is_array())
    {
        for (const auto &entrega : jsonDados["deliveries"])
        {
            lng = entrega["point"]["lng"].get<double>();
            lat = entrega["point"]["lat"].get<double>();
            coordenadas.emplace_back(lng, lat);

            pesos.emplace_back(entrega["size"]);
        }
    }

    // =======================
    //       PARAMETROS
    // ========================
    const unsigned int SEED = 42;
    const unsigned int IND_SIZE = pesos.size(); // Tamanho do indivíduo (solução).
    const unsigned int POP_SIZE = 80;           // Tamanho da população. Padrão = 80.
    const unsigned int MAX_GEN = 100;           // Número de gerações. Padrão 100.
    const unsigned int TOURNAMENT_SIZE = 2;
    // const double EPSILON = 0.01; // range for real uniform mutation
    const float CROSS_RATE = 0.8;
    // const double BIT_MUTATION_PROB = 0.02;
    const float MUTATION_RATE = 0.01;

    rng.reseed(SEED);

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

    // pop.sort();
    // cout << "\n\nCONFIGURAÇAO INICIAL";
    // cout << "\n===========================";
    // cout << "\nDistTot  Tam   Indices";
    // cout << "\n=========================== pop: " << pop;

    // SELECTION
    eoDetTournamentSelect<Chrom> select(TOURNAMENT_SIZE);
    // eoDeterministicSaDReplacement<Chrom> select(10, 10);

    // CROSSOVER
    // eoCycleXover<Chrom> xover; // converge mto rapido
    // eoPartiallyMappedXover<Chrom> xover;   //converge mt rapido
    // eoPrecedencePreserveXover<Chrom> xover;  //converge mto rapido
    eoLinearOrderXover<Chrom> xover; // errado
    // eoOrderXover2<Chrom> xover; //converge mto rapido
    // eoOrderXover<Chrom> xover;

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

// (25773, 200000 + 33986, 800000 + 31799, 400000 + 31799, 400000 + 28334, 400000) / 5
