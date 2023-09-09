// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-
//-----------------------------------------------------------------------------
// eoPMXover.h
//-----------------------------------------------------------------------------

#ifndef eoPMXover_h
#define eoPMXover_h

#include <algorithm>
#include <utils/eoRNG.h>
#include <eoInit.h>
#include <unordered_map>

/*
 * Partially Mapped Crossover
 *   P1 = [4, 2, 0, 1, 3]
 *   P2 = [1, 0, 3, 4, 2]
 * Selecionar dois pontos de corte. Os valores de dentro
 * serão trocados nos filhos.
 *   C1 = [4, 2, 3, 4, 3]
 * Faz-se o mapeamento dos valores dentro do intervalo
 *   3 <-> 0, 4<->1
 * Preservar aqueles que não fazem conflito fora do intervalo
 *   C1 = [*, 2, 3, 4, *]
 * Mapear o restante
 *   C1 = [1, 2, 3, 4, 0]
 */

template <class Chrom>
class eoPMXover : public eoQuadOp<Chrom>
{
public:
    virtual std::string className() const { return "eoPMXover"; }

    /**
     * @return true if the chromosome has changed
     * @param _chrom1 The first chromosome which will be crossed with chrom2.
     * @param _chrom2 The second chromosome which will be crossed with chrom1.
     */
    bool operator()(Chrom &_chrom1, Chrom &_chrom2)
    {
        unsigned cut1, cut2;

        cut1 = eo::rng.random(_chrom1.size());
        cut2 = eo::rng.random(_chrom1.size());


        // Cria copias dos pais. Assim os originais viram filhos
        Chrom tmp1 = _chrom1;
        Chrom tmp2 = _chrom2;

        // char direction = eo::rng.flip() ? 1 : -1;
        // unsigned cut2 = 1 + eo::rng.random(_chrom1.size());
        // unsigned cut1 = eo::rng.random(cut2);

        cross(tmp1, tmp2, _chrom1, cut1, cut2);
        cross(tmp2, tmp1, _chrom2, cut1, cut2);

        _chrom1.invalidate();
        _chrom2.invalidate();

        return true;
    }

private:
    /**
     * @param _chrom1 The first parent chromosome.
     * @param _chrom2 The second parent chromosome.
     * @param _child The result chromosome.
     * @param _cut1 index of the first cut
     * @param _cut2 index of the second cut
     */
    void cross(Chrom &_chrom1, Chrom &_chrom2, Chrom &_child, unsigned _cut1, unsigned _cut2)
    {

        unsigned size;
        size = _chrom1.size();

        // * Sem ordenação torna o acesso mais rápido
        std::unordered_map<int, int> mapping; // mapeia valor do pai1 ao pai2
        for (unsigned i = std::min(_cut1, _cut2); i <= std::max(_cut1, _cut2); ++i)
        {
            _child[i] = _chrom2[i];
            mapping[_chrom1[i]] = _chrom2[i];
            mapping[_chrom2[i]] = _chrom1[i];
        }

        std::vector<bool> repeated(size, true);

        for (auto gene : _child)
        {
            repeated[gene] = !repeated[gene];
        }

        for (unsigned i = 0; i < size; i++)
        {
            if (i < std::min(_cut1, _cut2) && i > std::max(_cut1, _cut2) && repeated[_child[i]])
            {
                repeated[_child[i]] = false;
                _child[i] = mapping[_child[i]];
            }
        }
    }
};

#endif
