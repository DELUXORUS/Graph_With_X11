#include "AlgorithmPrima.h"


void AlgorithmPrima::search() {
    int firstVertex = 1;
    cout << endl << "Algorithm Prima" << endl;

    _visitVertex.insert(firstVertex);
    _createTree();
    _output();
} 

void AlgorithmPrima::_createTree() {
    while (_visitVertex.size() < _weightGraph.getWeightListAdjacency().size()) {
        Vertex minEdge = {0, std::numeric_limits<int>::max(), 0, 0};
        int selectVisitVertex = -1;
        
        for (int vertex : _visitVertex) {
            for (auto& adjacencyVertex : _weightGraph.getWeightListAdjacency()[vertex]) {
                if (_visitVertex.find(adjacencyVertex.getNumber()) == _visitVertex.end() && adjacencyVertex.getWeight() < minEdge.getWeight()) {
                    minEdge = adjacencyVertex;
                    selectVisitVertex = vertex;
                }
            }
        }

        if (selectVisitVertex != -1) {
            _treeListAdjacency[selectVisitVertex].push_back(minEdge);

            for(auto& vertex : _weightGraph.getWeightListAdjacency()[minEdge.getNumber()])
                if(vertex.getNumber() == selectVisitVertex)
                    _treeListAdjacency[minEdge.getNumber()].push_back(vertex);

            _visitVertex.insert(minEdge.getNumber());
        }
    }
}

void AlgorithmPrima::_output() {
    cout << "List Adjacency Weight Hull" << endl;

    for(int i = 1; i <= _treeListAdjacency.size(); i++) {
        printf("Vertex %d:\n", i);
        for(int j = 0; j < _treeListAdjacency[i].size(); j++) {
            cout << "   vertex: " 
            << _treeListAdjacency[i][j].getNumber()
            << ", size: " << _treeListAdjacency[i][j].getWeight()
            << ", coord: " << _treeListAdjacency[i][j].getX() << ";" << _treeListAdjacency[i][j].getY() << endl;
        }

        cout << endl;
    }
}