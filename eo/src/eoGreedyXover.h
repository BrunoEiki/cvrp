// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-
//-----------------------------------------------------------------------------
// eoGreedyXover.h
//-----------------------------------------------------------------------------

#ifndef eoGreedyXover_h
#define eoGreedyXover_h

//-----------------------------------------------------------------------------

#include <algorithm>
#include <set>
#include "utils/eoRNG.h"
#include "eoInit.h"
#include <random>

// #include <paradiseo/eo/eoOp.h>

// #include <cvrp/adjacency_matrix.hpp>
// #include <metaheuristics/encoding.hpp>
// #include <random>

/**
 * apply greedyXover on two chromosomes.
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

	eoGreedyXover(const std::vector<std::vector<double>> &matrix) : matrix(matrix){};

	/**
	 * @return true if the chromosome has changed
	 * @param _chrom1 The first chromosome which will be crossed with chrom2.
	 * @param _chrom2 The second chromosome which will be crossed with chrom1.
	 */
	bool operator()(Chrom &_parent1, Chrom &_parent2)
	{
		Chrom child1 = generateChild(_parent1, _parent2);
		Chrom child2 = generateChild(_parent1, _parent2);

		_parent1.swap(child1);
		_parent2.swap(child2);

		return true;
	}

private:
	const std::vector<std::vector<double>> &matrix;

	inline size_t get_index_of(std::vector<int> &vec, int value)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (static_cast<int>(vec[i]) == value)
			{
				return i;
			}
		}
		return vec.size();
	}

	Chrom generateChild(Chrom &_parent1, Chrom &_parent2)
	{
		Chrom _child;
		const size_t chromosomeLength = _parent1.size(); // ! espero que Chrom tenha método size()
		std::vector<bool> inChild(chromosomeLength, false);

		std::mt19937 engine;
		std::random_device rd;
		engine = std::mt19937(rd());

		std::uniform_int_distribution<int> uniform(0, chromosomeLength - 1);
		int firstGene = uniform(engine);
		_child.push_back(firstGene);
		inChild[firstGene] = true;

		while (_child.size() < chromosomeLength)
		{
			int currentGene = *(_child.end() - 1);
			int index1 = get_index_of(_parent1, currentGene);
			int index2 = get_index_of(_parent2, currentGene);

			std::vector<int> neighbors = {
				_parent1[(index1 - 1) % chromosomeLength],
				_parent1[(index1 + 1) % chromosomeLength],
				_parent2[(index2 - 1) % chromosomeLength],
				_parent2[(index2 + 1) % chromosomeLength]};

			std::sort(neighbors.begin(), neighbors.end(), [&](int a, int b)
					  {
				double distance_a = this->matrix[currentGene][a];
				double distance_b = this->matrix[currentGene][b];
				return distance_a < distance_b; });

			size_t prevSize = _child.size();
			for (size_t i = 0; i < neighbors.size(); i++)
			{
				if (!inChild[neighbors[i]])
				{
					_child.push_back(neighbors[i]);
					inChild[neighbors[i]] = true;
					currentGene = neighbors[i];
					break;
				}
			}
			if (_child.size() == prevSize)
			{
				int randGene = uniform(engine);
				while (inChild[randGene])
				{
					randGene = uniform(engine);
				}
				_child.push_back(randGene);
				inChild[randGene] = true;
				currentGene = randGene;
			}
		}

		return _child;
	}
};

/** @example t-eoGreedyXover.cpp
 */

#endif