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
#include <bits/stdc++.h>

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
        unsigned _cut1;
        unsigned _cut2;

        _cut1 = eo::rng.random(_chrom1.size());
        _cut2 = eo::rng.random(_chrom1.size());

        do
            _cut2 = rng.random(_chrom1.size());
        while (_cut1 == _cut2);

        if (_cut1 > _cut2)
        {
            unsigned tmp = _cut1;
            _cut1 = _cut2;
            _cut2 = tmp;
        }

        Chrom tmp1 = _chrom1;
        Chrom tmp2 = _chrom2;

        cross(tmp1, tmp2, _chrom1, _cut1, _cut2);
        cross(tmp2, tmp1, _chrom2, _cut1, _cut2);

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
        std::set<int> setSegment; // set of elements in the crossover segment
        unsigned size = _chrom1.size();
        unsigned j = 0;

        for (unsigned i = _cut1; i <= _cut2; ++i)
        {
            _child[i] = _chrom2[i];
            setSegment.insert(_child[i]);
        }

        for (unsigned i = 0; i < size; ++i)
        {
            if (setSegment.find(_chrom1[i]) == setSegment.end()) // if not in the set
            {
                _child[j] = _chrom1[i];
                j += 1;
            }
            if (j == _cut1)
            {
                if (j < size - 1)
                {
                    j = _cut2 + 1;
                }
                else
                {
                    break;
                }
            }
        }
        setSegment.clear();
    }
};

#endif
