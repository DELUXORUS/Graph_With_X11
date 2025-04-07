#ifndef SIMPLE_CHAIN_H
#define SIMPLE_CHAIN_H

#include "BaseAlgorithm.h"


class SimpleChain : public Algorithm {
    public:
        SimpleChain() {};
        SimpleChain(Graph graph): Algorithm(graph) {}
        void search();
    private:
        void _search(int currentVertex, int finalVertex);
        int _check(int currentVertex);
        void _output();
        std::vector<int> simpleChain;
};

#endif