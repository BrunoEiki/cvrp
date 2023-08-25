#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdexcept>
#include <iostream>

#include <nlohmann/json.hpp>
#include <fstream>

#include <eo>
#include <ga.h>
#include <eoReal.h>

// Vetor solucao de valores com a ordem de entrega
typedef eoReal<int> Solucao;

// Vetor rota de entregas a serem feitas. Cada entrega é identificada
// por um id inteiro. Deve respeitar a capacidade maximo do veiculo.
typedef eoReal<int> Rotas;

// Parser do JSON para coletar a quantidade de entregas

// OSRM

// FUNCAO OBJETIVO (FITNESS)
// Soma as distâncias percorridas por cada rota. Vence a que
// tiver menor distância
int fitness_evaluation(const Individuo &_individuo)
{
	int soma = 0;
	for (unsigned int i : _individuo)
	{
		soma += i;
	}
	return soma;
}

void main_function(int /*argc*/, char ** /*argv*/)
{
	const unsigned int SEED = 42;
	//	const unsigned int INDIVIDUAL_SIZE = 100;
	const unsigned int POPULATION_SIZE = 100;
	const unsigned int MAX_GENERATION = 1000;
	const float CROSS_RATE = 0.8;
	//	const double BIT_MUTATION_PROB = 0.02;
	const float MUTATION_RATE = 1.0;
	const unsigned int TOURNAMENT_SIZE = 100;

	std::ifstream file("./example.json");
	nlohmann::json j;
	file >> j;
	std::string jstr = j["details"]["tutorial"];
	std::cout << jstr << '\n';
}
