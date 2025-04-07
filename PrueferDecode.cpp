#include "PrueferDecode.h"


void PrueferDecode::search() {
    cout << endl << "Pruefer Decoding" << endl;
    int sizeTree = _prueferCode.size() + 2;
    
    for(int i = 1; i <= sizeTree; i++)
        if(find(_prueferCode.begin(), _prueferCode.end(), i) == _prueferCode.end())
            _additionPrueferCode.push_back(i);
    
    _prueferDecoding(_additionPrueferCode[0], _prueferCode[0]);
    _output();
}

void PrueferDecode::_prueferDecoding(int vertexAddition, int vertexCodePruefer) {
    _listAdjacencyTree[vertexCodePruefer].push_back(vertexAddition);
    _listAdjacencyTree[vertexAddition].push_back(vertexCodePruefer);
    
    _additionPrueferCode.erase(remove(_additionPrueferCode.begin(), _additionPrueferCode.end(), vertexAddition), _additionPrueferCode.end());
    
    if(count(_prueferCode.begin(), _prueferCode.end(), vertexCodePruefer) == 1) {
        auto pos = lower_bound(_additionPrueferCode.begin(), _additionPrueferCode.end(), vertexCodePruefer);
        _additionPrueferCode.insert(pos, vertexCodePruefer);
    }
    
    _prueferCode.erase(find(_prueferCode.begin(), _prueferCode.end(), vertexCodePruefer));

    if(_prueferCode.size() != 0)
        _prueferDecoding(_additionPrueferCode[0], _prueferCode[0]);

    else {
        int firstVertex = _additionPrueferCode[0];
        int secontVertex = _additionPrueferCode[1];
        _listAdjacencyTree[firstVertex].push_back(secontVertex);
        _listAdjacencyTree[secontVertex].push_back(firstVertex);
        return;
    }
}   

void PrueferDecode::_output() {
    cout << "List Adjacency Tree" << endl;
    
    for(int i = 1; i <= _listAdjacencyTree.size(); i++) {
        cout << "Vertex " << i << ":"; 
        
        for(int j = 0; j < _listAdjacencyTree[i].size(); j++)
            cout << "   " << _listAdjacencyTree[i][j];
        
        cout << endl;
    }
}