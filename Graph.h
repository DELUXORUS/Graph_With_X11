#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <stack>

#include "Vertex.h"

using std::cout;
using std::cin;
using std::endl;


class Graph {
    public:
        Graph() {};
        void fillListAdjacency();
        void fillMatrixAdjacency(int vertex1, int vertex2);
        std::map<int, std::vector<int>>& getListAdjacency() { return _listAdjacency; }
        std::vector<std::vector<int>>& getMatrixAdjacency() { return _matrixAdjacency; }
        std::vector<Vertex>& getVectorVertex() { return _numberVertex; }
        int getNumberVertex() { return _numberVertex.size(); }
        void outputMatrixAdjacency();
        void outputListAdjacency();
        bool checkEdge(int numberVertex1, int numberVertex2);
        void reset();
    protected:
        std::vector<Vertex> _numberVertex;
        std::vector<std::vector <int>> _matrixAdjacency;
        std::map<int, std::vector<int>> _listAdjacency;
};

#endif