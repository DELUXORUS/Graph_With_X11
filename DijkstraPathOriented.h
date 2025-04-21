#ifndef DIJKSTRA_PATH_ORIENTED_H_
#define DIJKSTRA_PATH_ORIENTED_H_

#include <limits>
#include <algorithm>

#include "BaseWeightAlgorithm.h"


class DijkstraPathOriented : public WeightAlgorithm {
    public:
        void initialize(std::map<int, std::vector<Vertex>> listAdjacency,
                        std::vector<std::vector<int>> matrixAdjacency,
                        std::vector<Vertex> numberVertex);
        DijkstraPathOriented() {}
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



