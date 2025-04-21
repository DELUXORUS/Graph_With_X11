#ifndef BASE_WEIGHT_ALGHORITMS_H
#define BASE_WEIGHT_ALGHORITMS_H

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include "Vertex.h"

using std::cin;
using std::cout;
using std::endl;


class WeightAlgorithm {
    public:
        // WeightAlgorithm(WeightGraph weightGraph): _weightGraph(weightGraph) {};
        WeightAlgorithm() {};
        // static void initialize(std::map<int, std::vector<Vertex>> listAdjacency,
        //                         std::vector<std::vector<int>> matrixAdjacency,
        //                         std::vector<Vertex> numberVertex);
        virtual void initialize(std::map<int, std::vector<Vertex>> listAdjacency,
                        std::vector<std::vector<int>> matrixAdjacency,
                        std::vector<Vertex> numberVertex) = 0;
        virtual void search() = 0;
    protected:
        virtual void _output() = 0;
        std::map<int, std::vector<Vertex>> _listAdjacencyForCurrentGraph;
        std::vector<std::vector<int>> _matrixAdjacencyForCurrentGraph;
        std::vector<Vertex> _numberVertexForCurrentGraph;
         
        // WeightGraph _weightGraph;
};

#endif
