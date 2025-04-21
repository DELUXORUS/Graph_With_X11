#ifndef FLOYD_ALGORITHM_H_
#define FLOYD_ALGORITHM_H_

#include <algorithm>
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <iomanip>

#include "BaseWeightAlgorithm.h"


class FloydAlgorithm : public WeightAlgorithm {
    public:
        void initialize(std::map<int, std::vector<Vertex>> listAdjacency,
                        std::vector<std::vector<int>> matrixAdjacency,
                        std::vector<Vertex> numberVertex);
        FloydAlgorithm() {}
        void search();
    private:
        void _search(int currentVertex, int finalVertex, 
                     std::vector<std::pair<int,int>> _simpleChain, 
                     std::set<int>& visitedVertex);
        bool _checkSourceDrain(int source, int drain);
        int _removeMinWeightInChain(std::vector<std::pair<int,int>>& _simpleChain);
        void _output();
        void _outputSet(std::set<int>& set);
        std::map<int, std::vector<Vertex>> _listAdjacency;
        // std::vector<std::pair<int,int>> _simpleChain;
        int _bandwidth;
};

#endif



