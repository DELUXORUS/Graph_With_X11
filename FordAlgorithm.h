#ifndef FORD_ALGORITHM_H_
#define FORD_ALGORITHM_H_

#include <limits>
#include <iomanip>

#include "BaseWeightAlgorithm.h"


class FordAlgorithm : public WeightAlgorithm {
    public:
        void initialize(std::map<int, std::vector<Vertex>> listAdjacency,
                        std::vector<std::vector<int>> matrixAdjacency,
                        std::vector<Vertex> numberVertex);
        FordAlgorithm() {}
        void search();
        private:
        void _searchMinDist(int currentVertex);
        void _output();
        int _initVertex;
        std::vector<int> _visitVertex;
        std::vector<int> _minDist;
};

#endif



