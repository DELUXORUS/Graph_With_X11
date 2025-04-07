#include "SimpleChain.h"


void SimpleChain::search() {
    int initVertex, finalVertex;
    cout << endl << "Simple Chains" << endl;
    cout << "Enter initial and final vertex:" << endl;
    cin >> initVertex >> finalVertex;


    simpleChain.push_back(initVertex);

    for(int j = 0; j < _graph.getListAdjacency()[initVertex].size(); j++)
        _search(_graph.getListAdjacency()[initVertex][j], finalVertex);
}

void SimpleChain::_search(int currentVertex, int finalVertex) {    
    if(_check(currentVertex) == 1)
        return;
    
    else if(currentVertex == finalVertex) {
        simpleChain.push_back(currentVertex);
        _output();
        simpleChain.pop_back();
        return;
    }
    
    simpleChain.push_back(currentVertex);

    for(int j = 0; j < _graph.getListAdjacency()[currentVertex].size(); j++)
        _search(_graph.getListAdjacency()[currentVertex][j], finalVertex);
    
    simpleChain.pop_back();
    return;
}

int SimpleChain::_check(int currentVertex) {
    for(auto it = simpleChain.begin(); it != simpleChain.end(); it++)
        if(*it == currentVertex)
            return 1;

    return 0;
}

void SimpleChain::_output() {
    for(auto it = simpleChain.begin(); it != simpleChain.end();) {
        cout << *it;
        
        if(++it != simpleChain.end())
        cout << " => ";
    }
    
    cout << endl;
}