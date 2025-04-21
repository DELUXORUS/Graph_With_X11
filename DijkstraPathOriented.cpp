#include "DijkstraPathOriented.h"


void DijkstraPathOriented::initialize(std::map<int, std::vector<Vertex>> listAdjacency,
                                      std::vector<std::vector<int>> matrixAdjacency,
                                      std::vector<Vertex> numberVertex) 
{
    copy(listAdjacency.begin(), listAdjacency.end(), 
         inserter(_listAdjacencyForCurrentGraph, _listAdjacencyForCurrentGraph.end()));
    _matrixAdjacencyForCurrentGraph = matrixAdjacency;
    _numberVertexForCurrentGraph = numberVertex;

    _minDist.resize(_matrixAdjacencyForCurrentGraph.size(), std::numeric_limits<int>::max());
	// _minDist[0] = 0;
}
// Как и обычный алгоритм

void DijkstraPathOriented::search() {
	int initVertex, finalVertex;
	cout << endl << "Dijkstra Path" << endl;
    cout << "Enter initial and final vertex:" << endl;
    cin >> initVertex >> finalVertex;
    _minDist[initVertex - 1] = 0;
	_searchMinDist(initVertex);
	_path.push_back(finalVertex);
	_searchPath(finalVertex);
	_output();
}

void DijkstraPathOriented::_searchMinDist(int currentVertex) {
	_visitVertex.push_back(currentVertex - 1);

	for(auto& adjacencyVertex : _listAdjacencyForCurrentGraph[currentVertex]) {
		int numberAdjacencyVertex = adjacencyVertex.getNumber();
		int weightAdjacencyVertex = adjacencyVertex.getWeight();
		int point = weightAdjacencyVertex + _minDist[currentVertex - 1];

		if(find(_visitVertex.begin(), _visitVertex.end(), numberAdjacencyVertex - 1) == _visitVertex.end())
			if(point < _minDist[numberAdjacencyVertex - 1]) 
				_minDist[numberAdjacencyVertex - 1] = point;
	}

	int nextVertex = -1;
    int minDistance = std::numeric_limits<int>::max();

    for (int i = 0; i < _minDist.size(); ++i) {
        if (find(_visitVertex.begin(), _visitVertex.end(), i) == _visitVertex.end() && _minDist[i] < minDistance) {
            minDistance = _minDist[i];
            nextVertex = i + 1;
        }
    }

    if (nextVertex != -1)
        _searchMinDist(nextVertex);
}

void DijkstraPathOriented::_searchPath(int finalVertex) {
	int weightAdjacency, weightCurrentVertex;
	int numberAdjacency;

    for (size_t i = 0; i < _matrixAdjacencyForCurrentGraph.size(); ++i) {
        std::vector<int> currentRow = _matrixAdjacencyForCurrentGraph[i];
        numberAdjacency = i + 1;
        weightCurrentVertex = currentRow[finalVertex - 1];

        if (weightCurrentVertex != std::numeric_limits<int>::max()) {
            weightAdjacency = _minDist[finalVertex - 1] - weightCurrentVertex;

            if(_minDist[numberAdjacency - 1] == weightAdjacency) {
                _path.insert(_path.begin(), numberAdjacency);
                _searchPath(numberAdjacency);
                break;
            }
        }
	}
}

void DijkstraPathOriented::_output() {
	cout << "Minimal Path" << endl;

    for(auto it = _path.begin(); it != _path.end();) {
        cout << *it;
        
        if(++it != _path.end())
        cout << " => ";
    }
    
    cout << endl;
}