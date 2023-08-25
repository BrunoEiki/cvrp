#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <eo>
#include <es.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;

static size_t WriteCallback(char *contents, size_t size, size_t nmemb, char *buffer_in)
{
    ((std::string *)buffer_in)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

// REPRESENTATION
//-----------------------------------------------------------------------------
// define your individuals
typedef eoReal<double> Indi;

// EVAL
//-----------------------------------------------------------------------------
// a simple fitness function that computes the euclidian norm of a real vector
//    @param _indi A real-valued individual

double real_value(const Indi &_indi)
{
    double sum = 0;
    for (unsigned i = 0; i < _indi.size(); i++)
        sum += _indi[i] * _indi[i];
    return (-sum); // maximizing only
}

int main()
{

    std::ifstream file("./cvrp-0-ba-41.json");
    nlohmann::json jsonDados;
    file >> jsonDados;

    // Vetor para armazenar os pontos
    std::vector<std::pair<double, double>> pontos;
    std::vector<int> capacidades;

    if (jsonDados["deliveries"].is_array())
    {
        for (const auto &entrega : jsonDados["deliveries"])
        {
            double lng = entrega["point"]["lng"];
            double lat = entrega["point"]["lat"];
            pontos.emplace_back(lng, lat);

            capacidades.emplace_back(entrega["size"]);
        }
    }

    std::stringstream s;
    std::string grande;

    s << pontos[0].first << "," << pontos[0].second;
    s << pontos[1].first << "," << pontos[1].second << ";";

    grande = s.str();

    std::cout << grande;
    CURL *curl;

    CURLcode res;
    std::string readBuffer;
    std::stringstream ss;
    std::string url;

    ss << "http://localhost:5000/route/v1/driving/" + grande + "?annotations=distance&continue_straight=false";
    url = ss.str();
    std::cout << url;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            // Processar a resposta aqui
            std::cout << "Distancia calculada!";
        }
        else
        {
            std::cerr << "Erroo ao realizar a solicitação HTTP: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}