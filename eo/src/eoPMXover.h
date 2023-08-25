// #ifndef eoOrderXover_h
// #define eoOrderXover_h

#ifndef eoPMXover_h
#define eoPMXover_h

#include <algorithm>
#include <utils/eoRNG.h>
#include <eoInit.h>
#include <unordered_map>

template <class Chrom>
class eoPMXover : public eoQuadOp<Chrom>
{
public:
    virtual std::string className() const { return "eoPMXover"; }

    bool operator()(Chrom &_chrom1, Chrom &_chrom2)
    {
        unsigned cut1, cut2;
        // generate two different indices
        cut1 = eo::rng.random(_chrom1.size());
        do
        {
            cut2 = eo::rng.random(_chrom1.size());
        } while (cut1 == cut2);

        // Cria copias dos pais. Assim os originais viram filhos
        Chrom tmp1 = _chrom1;
        Chrom tmp2 = _chrom2;

        // for (int i = std::min(cut1, cut2); i <= std::max(cut1, cut2); ++i)
        // {
        //     child1[i] = parent2[i];
        //     child2[i] = parent1[i];
        // }

        std::unordered_map<int, int> mapping;
        for (int i = cut1; i <= cut2; ++i)
        {
            mapping[parent1[i]] = parent2[i];
            mapping[parent2[i]] = parent1[i];
        }

        // char direction = eo::rng.flip() ? 1 : -1;
        // unsigned cut2 = 1 + eo::rng.random(_chrom1.size());
        // unsigned cut1 = eo::rng.random(cut2);

        cross(tmp1, tmp2, _chrom1, direction, cut1, cut2);
        cross(tmp2, tmp1, _chrom2, direction, cut1, cut2);

        // _chrom1.invalidate();
        // _chrom2.invalidate();

        return true;
    }

private:
    void cross(Chrom &_chrom1, Chrom &_chrom2, Chrom &_child, char _direction, unsigned _cut1, unsigned _cut2)
    {
        
        // unsigned size, id = 0, from = 0;
        // size = _chrom1.size();

        // std::vector<bool> verif(size, false);

        // for (unsigned i = _cut1; i < _cut2; i++)
        // {
        //     _child[id++] = _chrom1[i];
        //     verif[_chrom1[i] % size] = true;
        // }

        // while (_chrom2[from] != _child[_cut2 - 1])
        //     from++;

        // for (unsigned i = 0; i < size; i++)
        // {
        //     unsigned j = (_direction * i + from + size) % size;
        //     if (!verif[_chrom2[j] % size])
        //     {
        //         _child[id++] = _chrom2[j];
        //         verif[_chrom2[j] % size] = true;
        //     }
        // }
    }
};

#endif
