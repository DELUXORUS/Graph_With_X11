#include "FloydAlgorithm.h"


void FloydAlgorithm::initialize(std::map<int, std::vector<Vertex>> listAdjacency,
                                std::vector<std::vector<int>> matrixAdjacency,
                                std::vector<Vertex> numberVertex) 
{
    copy(listAdjacency.begin(), listAdjacency.end(), 
         inserter(_listAdjacencyForCurrentGraph, _listAdjacencyForCurrentGraph.end()));
    _matrixAdjacencyForCurrentGraph = matrixAdjacency;
    _numberVertexForCurrentGraph = numberVertex;

    copy(_listAdjacencyForCurrentGraph.begin(), _listAdjacencyForCurrentGraph.end(), 
         inserter(_listAdjacency, _listAdjacency.end()));
}

void FloydAlgorithm::search() {
    int source, drain;
    cout << endl << "Enter the source vertex and the drain vertex: "  << endl;
    cin >> source >> drain;
    std::vector<std::pair<int,int>> simpleChain;
    std::set<int> visitedVertex;

    if (_checkSourceDrain(source, drain) == true) {
        _search(source, drain, simpleChain, visitedVertex);
        _output();
    }
    else {
        cout << endl << "Introduced vertices are not source and drain" << endl;
    }
}

bool FloydAlgorithm::_checkSourceDrain(int source, int drain) {
    if (_listAdjacency[drain].size() == 0 &&
        _listAdjacency[source].size() != 0) 
    {
        for (size_t i = 0; i < _matrixAdjacencyForCurrentGraph.size(); ++i) {
            if (_matrixAdjacencyForCurrentGraph[i][source - 1] != std::numeric_limits<int>::max())
                return false;
        }
    }
    else {
        return false;
    }

    return true;
}

void FloydAlgorithm::_search(int currentVertex, int finalVertex, 
                             std::vector<std::pair<int,int>> simpleChain, 
                             std::set<int>& visitedVertex) 
{
    cout << endl << "CurrentVertex: " << currentVertex << ", FinalVertex: " << finalVertex << endl;
    static bool flagExit = 0;
    static int backVertex = -1;

    visitedVertex.insert(currentVertex);
    
    if (currentVertex == finalVertex) {
        backVertex = _removeMinWeightInChain(simpleChain);
        visitedVertex.erase(currentVertex);
        flagExit = 1;
        return;
    }
    

    int currentSizeVectorAdjacency = _listAdjacency[currentVertex].size();
    
    while (_listAdjacency[currentVertex].size() > 0) {
        Vertex maxWeightVertex = {-1, 0, -1, -1}; 

        for (auto& vertexAdjacency : _listAdjacency[currentVertex]) {
            if (visitedVertex.find(vertexAdjacency.getNumber()) == visitedVertex.end()) 
            {
                if (vertexAdjacency.getWeight() > maxWeightVertex.getWeight()) {
                    maxWeightVertex = vertexAdjacency;
                }
            }
        }

        _outputSet(visitedVertex);
        cout << "Vertex with max weight: " << maxWeightVertex.getNumber() << endl;

        if (maxWeightVertex.getNumber() == -1) {
            return;
        }
        
        simpleChain.push_back({currentVertex, maxWeightVertex.getNumber()});
        _search(maxWeightVertex.getNumber(), finalVertex, simpleChain, visitedVertex);      
        maxWeightVertex.setWeight(0);

        cout << endl << "current vertex: " << currentVertex << endl; 
        cout << "back vertex: " << backVertex << endl;
        cout << "after delete size vector adjacency: " << _listAdjacency[currentVertex].size() << endl;
        cout << "current size vector adjacency: " << currentSizeVectorAdjacency << endl << endl;

        if (backVertex != -1 ) {
            if (backVertex != currentVertex) {
                visitedVertex.erase(currentVertex);
                return;
            } 
            else {
                backVertex = -1;
            }
        }
    }

    visitedVertex.erase(currentVertex);
}

int FloydAlgorithm::_removeMinWeightInChain(std::vector<std::pair<int,int>>& simpleChain) {
    int minWeight = std::numeric_limits<int>::max();
    struct MinEdge {
        int firstVertex;
        int secondVertex;
        int idSecondVertexInList;
    };

    std::vector<MinEdge> minEdges;

    for (int i = 0; i < simpleChain.size(); ++i) {
        int firstVertex = simpleChain[i].first;
        int secondVertex = simpleChain[i].second;

        for (int j = 0; j < _listAdjacency[firstVertex].size(); ++j) {
            Vertex currentVertex = _listAdjacency[firstVertex][j];

            if (currentVertex.getNumber() == secondVertex) {
                MinEdge minEdge = {firstVertex, currentVertex.getNumber(), j};

                if (currentVertex.getWeight() != 0) {
                    if (currentVertex.getWeight() < minWeight) {
                        minEdges.clear();
                        minWeight = currentVertex.getWeight();
                        minEdges.push_back(minEdge);
                    }
                    else if (currentVertex.getWeight() == minWeight) {
                        minEdges.push_back(minEdge);
                    }
                }
            }
        }
    }

    for (auto& edge : simpleChain) {
        int currentVertex = edge.first;

        for (size_t i = 0; i < _listAdjacency[currentVertex].size(); ++i) {
            if (_listAdjacency[currentVertex][i].getNumber() == edge.second) {
                _listAdjacency[currentVertex][i].setWeight(_listAdjacency[currentVertex][i].getWeight() - minWeight);
            }
        }
    }

    for (auto& minEdge : minEdges) {
        _listAdjacency[minEdge.firstVertex].erase(_listAdjacency[minEdge.firstVertex].begin() + minEdge.idSecondVertexInList);
    

        if (_listAdjacency[minEdge.firstVertex].size() == 0) {
            for (auto& row : _listAdjacency) {
                for (size_t i = 0; i < _listAdjacency[row.first].size(); ++i) {
                    if (_listAdjacency[row.first][i].getNumber() == minEdge.firstVertex) {
                        _listAdjacency[row.first][i].setWeight(0);
                    }
                }
            }
        }
    }

    cout << endl << "Minimal weight in chain: " << minWeight << endl;
    cout << "This edge: " << minEdges[0].firstVertex << "-" << minEdges[0].secondVertex << endl;
    _bandwidth += minWeight;

    return minEdges.front().firstVertex;
}

void FloydAlgorithm::_output() {
    cout << endl << "Bandwidth for this graph: " << _bandwidth << endl;
}

void FloydAlgorithm::_outputSet(std::set<int>& set) {
    for (auto& i : set) {
        cout << std::setw(5);
        cout << i ;
        // cout << "   ";
    }

    cout << endl;
}