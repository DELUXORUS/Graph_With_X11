#include "WeightGraph.h"


void WeightGraph::reset() {
    _numberVertex.clear();
    _weightMatrixAdjacency.clear();
    _weightListAdjacency.clear();
}

bool WeightGraph::checkEdge(int numberVertex1, int numberVertex2) {
    
    numberVertex1--;
    numberVertex2--;

    if(numberVertex1 == numberVertex2)
        return true;
    
    if(numberVertex1 >= _weightMatrixAdjacency.size() || numberVertex2 >= _weightMatrixAdjacency.size())
    return false;
    
    if(_weightMatrixAdjacency[numberVertex1][numberVertex2] != std::numeric_limits<int>::max())
        return true;

    return false;
}

// void WeightGraph::initializeWeightGraph(std::vector<Vertex> numberVertex) {
//     _numberVertex = numberVertex;
//     _weightMatrixAdjacency.resize(_numberVertex.size(), std::vector<int>(_numberVertex.size(), 0));
// }

void WeightGraph::fillMatrixWeight(int vertex1, int vertex2, int weight) {
    _weightMatrixAdjacency.resize(_numberVertex.size());

    for (size_t i = 0; i < _weightMatrixAdjacency.size(); ++i) {
        _weightMatrixAdjacency[i].resize(_numberVertex.size(), std::numeric_limits<int>::max());
    }

    _weightMatrixAdjacency[vertex1 - 1][vertex2 - 1] = weight;
    _weightMatrixAdjacency[vertex2 - 1][vertex1 - 1] = weight;
}

void WeightGraph::outputMatrixWeightGraph() {
    cout << endl << "Matrix Adjacency Weight Graph" << endl;

    for (size_t i = 0; i < _weightMatrixAdjacency.size(); i++) {
        for (size_t j = 0; j < _weightMatrixAdjacency.size(); j++) {
                cout << std::setw(5);

                if (_weightMatrixAdjacency[i][j] == std::numeric_limits<int>::max()) {
                    cout << "inf";
                }
                else {
                    cout << _weightMatrixAdjacency[i][j]; 
                }

                cout << "   ";
        }
        
        cout << endl;
    }
}

void WeightGraph::fillListWeight() {
    for(int i = 0; i < _weightMatrixAdjacency.size(); i++)
        _weightListAdjacency[i + 1].clear();

    for(int i = 0; i < _weightMatrixAdjacency.size() - 1; i++) {
        for(int j = i + 1; j < _weightMatrixAdjacency.size(); j++) {
            if(_weightMatrixAdjacency[i][j] != std::numeric_limits<int>::max()) {
                // if (_weightListAdjacency.size() != 0) {
                    // _addInOrderInList(i + 1, j + 1);
                // }
                // else {
                    _weightListAdjacency[i + 1].push_back({j + 1, _weightMatrixAdjacency[i][j], _numberVertex[j].getX(), _numberVertex[j].getY()});
                    _weightListAdjacency[j + 1].push_back({i + 1, _weightMatrixAdjacency[i][j], _numberVertex[i].getX(), _numberVertex[i].getY()});
                // }
            }
        }
    }
}

// void WeightGraph::_addInOrderInList(int firstVertex, int secondVertex) {
//     Vertex vertex = {secondVertex, 
//         _weightMatrixAdjacency[firstVertex - 1][secondVertex - 1], 
//         _numberVertex[secondVertex - 1].getX(), 
//         _numberVertex[secondVertex - 1].getY()};

//     if (_weightListAdjacency[firstVertex].size() == 0) {
//         _weightListAdjacency[firstVertex].push_back(vertex);
//     } 
//     else {
//         for (auto vertexAdjacency : _weightListAdjacency[firstVertex]) {
//             if (vertexAdjacency.getNumber() < secondVertex) {
//                 _weightListAdjacency[firstVertex].push_back(vertex);
//             }
//         }
//     }

//     vertex = {firstVertex, 
//         _weightMatrixAdjacency[firstVertex - 1][secondVertex - 1], 
//         _numberVertex[firstVertex - 1].getX(), 
//         _numberVertex[firstVertex - 1].getY()};

//     if (_weightListAdjacency[secondVertex].size() == 0) {
//         _weightListAdjacency[secondVertex].push_back(vertex);
//     }
//     else {
//         for (auto vertexAdjacency : _weightListAdjacency[secondVertex]) {
//             if (vertexAdjacency.getNumber() < firstVertex) {
//                 _weightListAdjacency[secondVertex].push_back(vertex);
//             }
//         }
//     }
// }

void WeightGraph::outputListWeightGraph() {
    cout << endl << "List Adjacency Weight Graph" << endl;

    for(int i = 1; i <= _weightListAdjacency.size(); i++) {
        printf("Vertex %d:\n", i);
        for(int j = 0; j < _weightListAdjacency[i].size(); j++) {
            cout << "   vertex: " 
            << _weightListAdjacency[i][j].getNumber()
            << ", size: " << _weightListAdjacency[i][j].getWeight()
            << ", coord: " << _weightListAdjacency[i][j].getX() << ";" << _weightListAdjacency[i][j].getY() << endl;      
        }

        cout << endl;
    }
}