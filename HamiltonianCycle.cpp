#include "HamiltonianCycle.h"


void HamiltonianCycle::initialize(std::map<int, std::vector<int>> listAdjacency,
                                    std::vector<std::vector<int>> matrixAdjacency,
                                    std::vector<Vertex> numberVertex)
{
    copy(listAdjacency.begin(), listAdjacency.end(), 
        inserter(_listAdjacencyForCurrentGraph, _listAdjacencyForCurrentGraph.end()));
    _matrixAdjacencyForCurrentGraph = matrixAdjacency;
    _numberVertexForCurrentGraph = numberVertex;
    // std::vector<int> hamiltonianCycle(_graph.getNumberVertex() + 1, -1);
    _hamiltonianCycle.resize(_numberVertexForCurrentGraph.size() + 1, -1);
}

void HamiltonianCycle::search() { 
    _hamiltonianCycle[0] = 1; 
    cout << endl << "Hamiltonian Cycle" << endl; 
    
    if(_search(1) == false )
        cout << "\nSolution does not exist"; 
    
    else
        _output(); 
}

bool HamiltonianCycle::_search(int pos) { 
    if(pos == _numberVertexForCurrentGraph.size()) { 
        if(_matrixAdjacencyForCurrentGraph[_hamiltonianCycle[pos - 1] - 1][_hamiltonianCycle[0] - 1] == 1) {
            _hamiltonianCycle[pos] = _hamiltonianCycle[0];
            return true; 
        }

        else
            return false; 
    } 

    for(int currentVertex = 1; currentVertex <= _numberVertexForCurrentGraph.size(); currentVertex++) { 
        if(_check(currentVertex, pos)) { 
            _hamiltonianCycle[pos] = currentVertex; 

            if(_search(pos + 1) == true) 
                return true; 

                _hamiltonianCycle[pos] = -1; 
        } 
    } 

    return false; 
} 

int HamiltonianCycle::_check(int currentVertex, int pos) {
    if (_matrixAdjacencyForCurrentGraph[_hamiltonianCycle[pos - 1] - 1][currentVertex - 1] == 0) 
    return false; 

    for (int i = 0; i < pos; i++) 
        if (_hamiltonianCycle[i] == currentVertex) 
            return false; 

    return true;
}

void HamiltonianCycle::_output() {
    for(auto it = _hamiltonianCycle.begin(); it != _hamiltonianCycle.end();) {
        cout << *it;; 
        
        if(++it != _hamiltonianCycle.end())
            cout << " => ";
    }

    cout << endl;
}