#include "HamiltonianCycle.h"


void HamiltonianCycle::search() { 
    _hamiltonianCycle[0] = 1; 
    cout << endl << "Hamiltonian Cycle" << endl; 
    
    if(_search(1) == false )
        cout << "\nSolution does not exist"; 
    
    else
        _output(); 
}

bool HamiltonianCycle::_search(int pos) { 
    if(pos == _graph.getNumberVertex()) { 
        if(_graph.getMatrixAdjacency()[_hamiltonianCycle[pos - 1] - 1][_hamiltonianCycle[0] - 1] == 1) {
            _hamiltonianCycle[pos] = _hamiltonianCycle[0];
            return true; 
        }

        else
            return false; 
    } 

    for(int currentVertex = 1; currentVertex <= _graph.getNumberVertex(); currentVertex++) { 
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
    if (_graph.getMatrixAdjacency()[_hamiltonianCycle[pos - 1] - 1][currentVertex - 1] == 0) 
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