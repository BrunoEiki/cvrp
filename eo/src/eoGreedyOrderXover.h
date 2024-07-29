// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-
//-----------------------------------------------------------------------------
// eoGreedyXover.h
//-----------------------------------------------------------------------------

#ifndef eoGreedyOrderXover_h
#define eoGreedyOrderXover_h

//-----------------------------------------------------------------------------

#include <algorithm>
#include <set>
#include "utils/eoRNG.h"
#include "eoInit.h"
#include <random>

/**
 * apply greedyOrderXover on two chromosomes.
 * Example:
 *
 * @ingroup Variators
 */
template <class Chrom>
class eoGreedyXover : public eoQuadOp<Chrom>
{
public:
	/// The class name.
	virtual std::string className() const { return "eoGreedyXover"; }

	GreedyOrderXover(const std::vector<std::vector<double>> &matrix, const std::vector<int> &deliveryWeights,
										uint64_t sortingBufferSize)
    : matrix(matrix), deliveryWeights(deliveryWeights), sortingBufferSize(sortingBufferSize) {
	engine = std::mt19937(rd());
}


	/**
	 * @return true if the chromosome has changed
	 * @param _chrom1 The first chromosome which will be crossed with chrom2.
	 * @param _chrom2 The second chromosome which will be crossed with chrom1.
	 */
	bool operator()(Chrom &_parent1, Chrom &_parent2)
	{
		size_t chromosomeLength = parent1.size();
		int point2 = generatePoint(1, chromosomeLength);
		int point1 = generatePoint(0, point2);

		Chrom child1 = generateChild(_parent1, _parent2);
		Chrom child2 = generateChild(_parent1, _parent2);

		_parent1.swap(child1);
		_parent2.swap(child2);

		return true;
	}

private:
	const std::vector<std::vector<double>> &matrix;

	int generatePoint(int low, int high) {
		std::uniform_int_distribution<int> dist(low, high - 1);
		return dist(engine);
	}


	Chrom generateChild(Chrom &_parent1, Chrom &_parent2)
	{
		const size_t chromosomeLength = parent1.size();
		Encoding child(chromosomeLength, -1);
		vector<bool> inChild(chromosomeLength, false);
		vector<int> notInChild;

		for (int i = point1; i < point2; i++) {
			child[i] = parent1[i];
			inChild[parent1[i]] = true;
		}

		for (size_t i = 0; i < parent2.size(); i++) {
			if (!inChild[parent2[i]]) {
				notInChild.push_back(parent2[i]);
			}
		}

		// const size_t N = (size_t)notInChild.size() * this->sortRate;  // Sorting rate (%). Default is 10%
		int currentGeneInChild = child.at(point2 - 1);

		for (size_t i = 0; i < notInChild.size(); i++) {
			size_t k = i + this->sortingBufferSize < notInChild.size() ? i + this->sortingBufferSize : notInChild.size() - 1;

			std::sort(notInChild.begin() + i, notInChild.begin() + k, [&](int a, int b) {
				double distance_a = matrix->get(currentGeneInChild, a);
				double distance_b = matrix->get(currentGeneInChild, b);
				return distance_a < distance_b;
			});

			currentGeneInChild = notInChild[i];
		}

		size_t index = point2;
		for (int gene : notInChild) {
			child.at(index++) = gene;
			if (index == child.size()) {
				index = 0;
			}
		}

		return child;

	}
};

/** @example t-eoGreedyXover.cpp
 */

#endif