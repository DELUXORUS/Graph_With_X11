#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <iostream>

#include "Graph.h"


class Algorithm {
    public:
        Algorithm(Graph graph): _graph(graph) {};
        Algorithm() {};
        virtual void search() = 0;
    protected:
        virtual void _output() = 0;
        Graph _graph;
};
#endif
