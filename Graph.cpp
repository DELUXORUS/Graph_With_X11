#include "Graph.h"


void Graph::reset() {
    _numberVertex.clear();
    _matrixAdjacency.clear();
    _listAdjacency.clear();
}

bool Graph::checkEdge(int numberVertex1, int numberVertex2) {
    numberVertex1--;
    numberVertex2--;

    if(numberVertex1 >= _matrixAdjacency.size() || numberVertex2 >= _matrixAdjacency.size())
        return false;

    
    if(_matrixAdjacency[numberVertex1][numberVertex2] == 1)
        return true;

    return false;
}

void Graph::fillMatrixAdjacency(int vertex1, int vertex2) {
    // _matrixAdjacency.resize(_numberVertex.size(), std::vector<int>(_numberVertex.size()));
    _matrixAdjacency.resize(_numberVertex.size());

    for (size_t i = 0; i < _matrixAdjacency.size(); ++i) {
        _matrixAdjacency[i].resize(_numberVertex.size(), 0);
    }


    _matrixAdjacency[vertex1 - 1][vertex2 - 1] = 1;
    _matrixAdjacency[vertex2 - 1][vertex1 - 1] = 1;
}

void Graph::fillListAdjacency() {
    for(int i = 0; i < _numberVertex.size(); i++)
            _listAdjacency[i + 1].clear();

    for(int i = 0; i < _numberVertex.size() - 1; i++) {
        for(int j = i + 1; j < _numberVertex.size(); j++) {
            if(_matrixAdjacency[i][j] == 1) {
                _listAdjacency[i + 1].push_back(j + 1);
                _listAdjacency[j + 1].push_back(i + 1);
            }
        }
    }
}

void Graph::outputMatrixAdjacency() {
    cout << endl << "Matrix Adjacency" << endl;
    
    for(int i = 0; i < _numberVertex.size(); i++) {
        for(int j = 0; j < _numberVertex.size(); j++)
            cout << _matrixAdjacency[i][j] << "   ";
        
        cout << endl;
    }
}

void Graph::outputListAdjacency() {
    cout << endl << "List Adjacency" << endl;
    
    for(int i = 1; i <= _numberVertex.size(); i++) {
        cout << "Vertex " << i << ":"; 
        
        for(int j = 0; j < _listAdjacency[i].size(); j++)
            cout << "   " << _listAdjacency[i][j];
        
        cout << endl;
    }
}