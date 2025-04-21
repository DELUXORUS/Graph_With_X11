#include "EulerianCycle.h"


void EulerianCycle::initialize(std::map<int, std::vector<int>> listAdjacency,
                                std::vector<std::vector<int>> matrixAdjacency,
                                std::vector<Vertex> numberVertex)
{
    copy(listAdjacency.begin(), listAdjacency.end(), 
        inserter(_listAdjacencyForCurrentGraph, _listAdjacencyForCurrentGraph.end()));
    _matrixAdjacencyForCurrentGraph = matrixAdjacency;
    _numberVertexForCurrentGraph = numberVertex;
}

void EulerianCycle::search() {
    int firstVertexPathEulerian = _check();

    switch(firstVertexPathEulerian) {
        case -1: {
            cout << endl << "This graph is not an Eulerian graph!" << endl; 
            break; 
        }
        
        case 0: {
            cout << endl << "Eulerian cycle" << endl;
            int firstVertex = 1;
            _search(firstVertex);
            _output();
            cout << endl;
            break;
        }
        
        default: {
            cout << endl << "Eulerian path" << endl;
            std::vector<std::vector<int>> copyMatrixAdjacency = _matrixAdjacencyForCurrentGraph;
            _search(firstVertexPathEulerian);
            _output();
            break;
        }
    }
}

void EulerianCycle::_search(int currentVertex) {
    std::vector<std::vector <int>> copyMatrixAdjacency = _matrixAdjacencyForCurrentGraph;
    std::stack<int> vertexPath;

vertexPath.push(currentVertex);

while(vertexPath.empty() != 1) {
    int currentVertex = vertexPath.top() - 1;
    int i;

    for (i = 0; i < _numberVertexForCurrentGraph.size(); ++i)
        if(copyMatrixAdjacency[currentVertex][i] != 0)
            break;
    
    if(i == _numberVertexForCurrentGraph.size()) {
        _eulerianCycleOrPath.push_back(currentVertex + 1);
        vertexPath.pop();
    }

    else {
        --copyMatrixAdjacency[currentVertex][i];
        --copyMatrixAdjacency[i][currentVertex];
        vertexPath.push(i + 1);
    }
}
}

void EulerianCycle::_output() {
    for(auto it = _eulerianCycleOrPath.begin(); it < _eulerianCycleOrPath.end();) {
        cout << *it;
        
        if(++it != _eulerianCycleOrPath.end())
            cout << " => ";
    }

    cout << endl;
}

int EulerianCycle::_check() {
    std::vector<int> oddVertex;

    for(int i = 1; i <= _listAdjacencyForCurrentGraph.size(); i++) {
        if((_listAdjacencyForCurrentGraph[i].size() % 2) != 0) {
            oddVertex.push_back(i);
        }
    }

    if(oddVertex.size() == 2)
        return oddVertex[0];
    
    else if(oddVertex.size() == 0)
        return 0;

    return -1;
}