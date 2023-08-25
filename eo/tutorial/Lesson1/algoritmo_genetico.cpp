#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdexcept>
#include <iostream>

#include <eo>
#include <ga.h>

// using namespace std;
typedef eoBit<int> Individuo;

// FUNCAO OBJETIVO (FITNESS)
// Quanto mais 1's, melhor. Portanto basta contar quantos 1 existem
int fitness_evaluation(const Individuo & _individuo) {
    int soma = 0;
    for (unsigned int i : _individuo) {
        soma += i;
    }
    return soma;
}

void main_function(int /*argc*/, char **/*argv*/) {

    // ====== ATRIBUTOS ======

    const unsigned int SEED = 42;
    const unsigned int INDIVIDUAL_SIZE = 50;
    const unsigned int POPULATION_SIZE = 80;
    const unsigned int MAX_GENERATION = 20;
    const float CROSS_RATE = 0.8;
    const double BIT_MUTATION_PROB = 0.02;
    const float MUTATION_RATE = 1.0;
    const unsigned int TOURNAMENT_SIZE = 10;

    eo::rng.reseed(SEED);

    eoEvalFuncPtr<Individuo> eval(fitness_evaluation);

    // ====== INICIALIZAR A POPULACAO ======
    eoPop<Individuo> pop;
    for (unsigned int i = 0; i < POPULATION_SIZE; i++) {
        Individuo individuo;
        
        for  (unsigned int j = 0; j < INDIVIDUAL_SIZE; j++) {
            bool bit = rng.flip();  // aleatorio {0 ou 1}
            individuo.push_back(bit);
        }
        eval(individuo);
        pop.push_back(individuo);
    }    

    
    // ====== PRINTAR A POPULACAO ======
    std::cout << "=========== POPULACAO INICIAL ===========\n";
    std::cout << "Tamanho: " << pop << "\n";

    
    // ====== SELECAO ======
    //eoDetTournamentSelect<Individuo> selecao(TOURNAMENT_SIZE);
    eoRandomSelect<Individuo> selecao;
    //eoProportionalSelect<Individuo> selecao;

    // ====== CROSSOVER ======
    eo1PtBitXover<Individuo> crossover;
    // eoUBitXover<Individuo> crossover;

    // ====== MUTACAO ======
    eoBitMutation<Individuo> mutacao(BIT_MUTATION_PROB);

    // ====== CONDICAO DE PARADA ======
    eoGenContinue<Individuo> continua(MAX_GENERATION);


    // ====== ALGORITMO GENETICO PADRAO ======
    // - [ ] Selecao
    // - [ ] Crossover
    // - [ ] Taxa de Crossover, Mutacao e Taxa de Mutacao
    // - [ ] Funcao Objetivo
    // - [ ] Criterio de Parada 
    eoSGA<Individuo> algoritmo_genetico(selecao, crossover, CROSS_RATE, 
                                        mutacao, MUTATION_RATE, eval, continua);
    algoritmo_genetico(pop);


    pop.sort();
    std::cout << pop;

    
}

int main(int argc, char **argv) {
    try {
        main_function(argc, argv);

    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
}