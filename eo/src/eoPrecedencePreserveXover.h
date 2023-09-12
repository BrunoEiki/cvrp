// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-
//-----------------------------------------------------------------------------
// eoPrecedencePreserveXover.h
//-----------------------------------------------------------------------------

#ifndef eoPrecedencePreserveXover_h
#define eoPrecedencePreserveXover_h

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
class eoPrecedencePreserveXover : public eoQuadOp<Chrom>
{
public:
    virtual std::string className() const { return "eoPrecedencePreserveXover"; }

    /**
     * @return true if the chromosome has changed
     * @param _chrom1 The first chromosome which will be crossed with chrom2.
     * @param _chrom2 The second chromosome which will be crossed with chrom1.
     */
    bool operator()(Chrom &_chrom1, Chrom &_chrom2)
    {
        unsigned size = _chrom1.size();
        std::vector<bool> mask(size);
        for (unsigned i = 0; i <= size; ++i)
        {
            mask[i] = rand() % 2;
        }

        Chrom tmp1 = _chrom1;
        Chrom tmp2 = _chrom2;

        cross(tmp1, tmp2, _chrom1, mask);
        mask.flip();
        cross(tmp2, tmp1, _chrom2, mask);

        _chrom1.invalidate();
        _chrom2.invalidate();

        return true;
    }

private:
    /**
     * @param _parent1 The first parent chromosome.
     * @param _parent2 The second parent chromosome.
     * @param _child The result chromosome.
     * @param _mask The mask to define which parent will contribute in each iteration.
     */
    void cross(Chrom &_parent1, Chrom &_parent2, Chrom &_child, std::vector<bool> &_mask)
    {

        unsigned size = _parent1.size();
        std::vector<bool> check(size, false);

        _child.resize(size, -1);

        unsigned current1 = 0;
        unsigned current2 = 0;

        unsigned index = 0;

        while (index < size)
        {
            if (_mask[index])
            {
                while (current2 < size && check[_parent2[current2]])
                {
                    current2++;
                }

                if (current2 == size)
                {
                    _mask[index] = false;

                } else {
                    _child[index] = _parent2[current2];
                    check[_parent2[current2]] = true;
                }
            }
            else
            {
                while (current1 < size && check[_parent1[current1]])
                {
                    current1++;
                }

                if (current1 == size)
                {
                    _mask[index] = true;

                } else {
                    _child[index] = _parent1[current1];
                    check[_parent1[current1]] = true;
                }
            }
            index++;
        }
    }
};

#endif