// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-
//-----------------------------------------------------------------------------
// eoCycleXover.h
//-----------------------------------------------------------------------------

#ifndef eoCycleXover_h
#define eoCycleXover_h

//-----------------------------------------------------------------------------

#include <algorithm>
#include <set>
#include "utils/eoRNG.h"
#include "eoInit.h"

/**
 * apply cycleXover on two chromosomes.
 * Example:
 *
 * @ingroup Variators
 */
template <class Chrom>
class eoCycleXover : public eoQuadOp<Chrom>
{
public:
        /// The class name.
        virtual std::string className() const { return "eoCycleXover"; }

        /**
         * @return true if the chromosome has changed
         * @param _chrom1 The first chromosome which will be crossed with chrom2.
         * @param _chrom2 The second chromosome which will be crossed with chrom1.
         */
        bool operator()(Chrom &_chrom1, Chrom &_chrom2)
        {

                Chrom tmp1 = _chrom1;
                Chrom tmp2 = _chrom2;

                cross(tmp1, tmp2, _chrom2);
                cross(tmp2, tmp1, _chrom1);

                _chrom1.invalidate();
                _chrom2.invalidate();

                return true;
        }

private:
        /**
         * @param _chrom1 The first parent chromosome.
         * @param _chrom2 The second parent chromosome.
         * @param _child The result chromosome.
         * @param _direction The direction of the OrderXover (left: -1 or right: 1)
         * @param _cut1 index of the first cut
         * @param _cut2 index of the second cut
         */
        void cross(Chrom &_chrom1, Chrom &_chrom2, Chrom &_child)
        {
                unsigned size;
                size = _chrom1.size();

                bool direction = true;
                int curr = _chrom1[0];
                std::set<int> seen;

                while (seen.count(curr) == 0)
                {
                        _child[curr] = curr;
                        seen.insert(curr);
                        direction = !direction;

                        if (direction)
                                curr = _chrom1[curr];
                        else
                                curr = _chrom2[curr];
                }

                for (unsigned i = 0; i < size; i++)
                {
                        if (seen.count(_chrom2[i]) == 0)
                        {
                                _child[i] = _chrom2[i];
                        }
                }
                seen.clear();
        }
};
/** @example t-eoCycleXover.cpp
 */

#endif
