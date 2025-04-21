#ifndef ALGORITHM_PRIMA_H_
#define ALGORITHM_PRIMA_H_

#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include <set>

#include "BaseWeightAlgorithm.h"
#include "Vertex.h"


class AlgorithmPrima : public WeightAlgorithm {
    public:
        void initialize(std::map<int, std::vector<Vertex>> listAdjacency,
                        std::vector<std::vector<int>> matrixAdjacency,
                        std::vector<Vertex> numberVertex);
        // AlgorithmPrima(WeightGraph weightGraph): WeightAlgorithm(weightGraph) {}

        std::map<int, std::vector<Vertex>>& getTreeListAdjacency() { return _treeListAdjacency; }
        // WeightGraph getWeightGraph() { return _weightGraph; }
        void search();
    private:
        void _output();
        void _createTree();
        
        std::map<int, std::vector<Vertex>> _treeListAdjacency;
        std::set<int> _visitVertex;

};

#endif