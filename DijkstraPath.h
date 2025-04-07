#ifndef DIJKSTRA_PATH_H_
#define DIJKSTRA_PATH_H_

#include <algorithm>
#include <limits>

#include "BaseWeightAlgorithm.h"


class DijkstraPath : public WeightAlgorithm {
	public:
		DijkstraPath() {}
		DijkstraPath(WeightGraph weightGraph): WeightAlgorithm(weightGraph) {
			_minDist.resize(_weightGraph.getWeightMatrixAdjacency().size(), std::numeric_limits<int>::max());
			_minDist[0] = 0;
		}
		void search();
    private:
		void _searchMinDist(int currentVertex);
		void _searchPath(int finalVertex);
		void _output();
        std::vector<int> _visitVertex;
        std::vector<int> _minDist;
        std::vector<int> _path;
};

#endif