#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

#include <eo>
#include <es.h>
#include <eoInt.h>
#include <eoOrderXover.h>
#include <eoPMXover.h>
#include <eoTwoOptMutation.h>

using namespace std;
typedef eoInt<double> Chrom;

double real_value(const Chrom &_chrom)
{
    double sum = 0;
    for (auto gene : _chrom)
    {
        sum += gene;
    }
    return sum;
}

int main(int argc, char **argv)
{
    const unsigned int SEED = 42;
    const unsigned int IND_SIZE = 5;  // Tamanho do indivíduo (solução)
    const unsigned int POP_SIZE = 10; // Tamanho da população
    const unsigned int MAX_GEN = 50;
    const unsigned int TOURNAMENT_SIZE = 2;
    const float CROSS_RATE = 0.8;
    const float MUTATION_RATE = 0.01;

    rng.reseed(SEED);

    eoEvalFuncPtr<Chrom> eval(real_value);

    Chrom v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(2);
    v1.push_back(0);

    Chrom v2;
    v2.push_back(0);
    v2.push_back(2);
    v2.push_back(3);
    v2.push_back(1);
    v2.push_back(4);

    eoPop<Chrom> pop;
    pop.push_back(v1);
    pop.push_back(v2);

    // SELECTION
    eoDetTournamentSelect<Chrom> select(TOURNAMENT_SIZE);

    // CROSSOVER
    eoPMXover<Chrom> xover;
    // eoSegmentCrossover<Chrom> xover;

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

    return 0;
}