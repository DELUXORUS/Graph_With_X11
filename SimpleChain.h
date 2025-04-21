#ifndef SIMPLE_CHAIN_H
#define SIMPLE_CHAIN_H

#include "BaseAlgorithm.h"


class SimpleChain : public Algorithm {
    public:
        SimpleChain() {};
        // SimpleChain(Graph graph): Algorithm(graph) {}
        void initialize(std::map<int, std::vector<int>> listAdjacency,
                        std::vector<std::vector<int>> matrixAdjacency,
                        std::vector<Vertex> numberVertex);
        void search();
    private:
        void _search(int currentVertex, int finalVertex);
        int _check(int currentVertex);
        void _output();
        std::vector<int> simpleChain;
};

#endif