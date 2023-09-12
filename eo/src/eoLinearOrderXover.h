// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-
//-----------------------------------------------------------------------------
// eoLinearOrderXover.h
//-----------------------------------------------------------------------------

#ifndef eoLinearOrderXover_h
#define eoLinearOrderXover_h

#include <algorithm>
#include <utils/eoRNG.h>
#include <eoInit.h>
#include <unordered_map>

/*
In the basis of
Falkenauer e Bouffouix (Croce, Tadei e Volta, 1995)
algorithm
*/

template <class Chrom>
class eoLinearOrderXover : public eoQuadOp<Chrom>
{
public:
    virtual std::string className() const { return "eoLinearOrderXover"; }

    /**
     * @return true if the chromosome has changed
     * @param _chrom1 The first chromosome which will be crossed with chrom2.
     * @param _chrom2 The second chromosome which will be crossed with chrom1.
     */
    bool operator()(Chrom &_chrom1, Chrom &_chrom2)
    {
        unsigned _cut1, _cut2;

        _cut1 = eo::rng.random(_chrom1.size());
        _cut2 = eo::rng.random(_chrom1.size());

        do
            _cut2 = rng.random(_chrom1.size());
        while (_cut1 == _cut2);

        if (_cut1 > _cut2)
        {
            size_t tmp = _cut1;
            _cut1 = _cut2;
            _cut2 = tmp;
        }

        Chrom tmp1 = _chrom1;
        Chrom tmp2 = _chrom2;

        cross(tmp1, tmp2, _chrom1, _chrom2, _cut1, _cut2);

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
    void cross(Chrom &_parent1, Chrom &_parent2, Chrom &_child1, Chrom &_child2, unsigned _cut1, unsigned _cut2)
    {

        unsigned size = _parent1.size();

        _child1.resize(size, -1);
        _child2.resize(size, -1);

        for (unsigned i = _cut1; i <= _cut2; ++i)
        {
            _child1[i] = _parent2[i];
            _child2[i] = _parent1[i];
        }

        for (unsigned i = 0; i < size; ++i)
        {
            if (i < _cut1 || i > _cut2)
            {
                unsigned val1 = _parent1[i];
                unsigned val2 = _parent2[i];

                unsigned count1 = 0;
                unsigned count2 = 0;

                while (std::find(_child1.begin(), _child1.end(), val1) != _child1.end())
                {
                    val1 = _parent1[count1++];
                }

                while (std::find(_child2.begin(), _child2.end(), val2) != _child2.end())
                {
                    val2 = _parent2[count2++];
                }

                _child1[i] = val1;
                _child2[i] = val2;
            }
        }
    }
};

#endif
