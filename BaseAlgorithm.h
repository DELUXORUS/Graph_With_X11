#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <iostream>

#include "Graph.h"


class Algorithm {
    public:
        // Algorithm(Graph graph): _graph(graph) {};
        virtual void initialize(std::map<int, std::vector<int>> listAdjacency,
                                std::vector<std::vector<int>> matrixAdjacency,
                                std::vector<Vertex> numberVertex) = 0;
        Algorithm() {};
        virtual void search() = 0;
    protected:
        virtual void _output() = 0;
        std::map<int, std::vector<int>> _listAdjacencyForCurrentGraph;
        std::vector<std::vector<int>> _matrixAdjacencyForCurrentGraph;
        std::vector<Vertex> _numberVertexForCurrentGraph;
        // Graph _graph;
};
#endif
