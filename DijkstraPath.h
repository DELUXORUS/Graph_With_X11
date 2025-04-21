#ifndef DIJKSTRA_PATH_H_
#define DIJKSTRA_PATH_H_

#include <algorithm>
#include <limits>

#include "BaseWeightAlgorithm.h"


class DijkstraPath : public WeightAlgorithm {
	public:
		DijkstraPath() {}
		void initialize(std::map<int, std::vector<Vertex>> listAdjacency,
						std::vector<std::vector<int>> matrixAdjacency,
						std::vector<Vertex> numberVertex);
		// DijkstraPath(WeightGraph weightGraph): WeightAlgorithm(weightGraph) {
			// _minDist.resize(_matrixAdjacencyForCurrentGraph.size(), std::numeric_limits<int>::max());
			// _minDist[0] = 0;
		// }
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