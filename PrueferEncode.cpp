#include "PrueferEncode.h"


void PrueferEncode::search() {
    if(_encode() == true) {
        cout << endl << "Code Pruefer: ";
        _output();
    }
    
    else 
        cout << endl << "The represented graph is not a tree!" << endl;
}

bool PrueferEncode::_encode() {
    while(_codePruefer.size() != (_graph.getNumberVertex() - 2)) {
        int minNumberVertex = std::numeric_limits<int>::max() ;
        int countDegreeVertex = 0;

        for(int j = 1; j < _graph.getListAdjacency().size(); j++) {
            if(_deformableListAdjacency[j].size() == 1) {
                if(j < minNumberVertex) {
                    minNumberVertex = j;
                    countDegreeVertex++;
                }
            }
        }

        if(countDegreeVertex == 0)
            return false;
        
        int parentVertex = _deformableListAdjacency[minNumberVertex][0];
        _codePruefer.push_back(parentVertex);
        
        _deformableListAdjacency[parentVertex].erase(
            remove(_deformableListAdjacency[parentVertex].begin(), 
                    _deformableListAdjacency[parentVertex].end(), 
                    minNumberVertex), 
            _deformableListAdjacency[parentVertex].end());

        _deformableListAdjacency.erase(minNumberVertex);
    }
    
    return true;
}

void PrueferEncode::_output() {
    for(auto it : _codePruefer)
        cout << it << "   ";

    cout << endl;
}