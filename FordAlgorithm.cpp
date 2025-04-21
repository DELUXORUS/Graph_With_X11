#include "FordAlgorithm.h"


void FordAlgorithm::initialize(std::map<int, std::vector<Vertex>> listAdjacency,
                               std::vector<std::vector<int>> matrixAdjacency,
                               std::vector<Vertex> numberVertex) 
{
    copy(listAdjacency.begin(), listAdjacency.end(), 
         inserter(_listAdjacencyForCurrentGraph, _listAdjacencyForCurrentGraph.end()));
    _matrixAdjacencyForCurrentGraph = matrixAdjacency;
    _numberVertexForCurrentGraph = numberVertex;

    _minDist.resize(_matrixAdjacencyForCurrentGraph.size(), std::numeric_limits<int>::max());
}

void FordAlgorithm::search() {
	cout << endl << "Search for the minimum path to each vertex from a given vertex";
    cout << endl << "Enter initial vertex: " << endl;
    cin >> _initVertex;
    _minDist[_initVertex - 1] = 0;
	_searchMinDist(_initVertex);
	_output();
}

void FordAlgorithm::_searchMinDist(int currentVertex) {
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

void FordAlgorithm::_output() {
    cout << endl << "Minimal distance from vertex " << _initVertex << " to each vertex:" << endl;

    for (size_t i = 0; i < _minDist.size(); ++i) {
        cout << std::setw(5);
        cout << "Vertex " << i + 1 << ": ";

        if (_minDist[i] == std::numeric_limits<int>::max()) {
            cout << "inf";
        }
        else {
            cout << _minDist[i];
        }

        cout << endl;
    }

    cout << endl;
}