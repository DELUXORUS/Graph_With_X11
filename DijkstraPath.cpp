#include "DijkstraPath.h"


void DijkstraPath::search() {
	int initVertex, finalVertex;
	cout << endl << "Dijkstra Path" << endl;
 	cout << "Enter initial and final vertex:" << endl;
  	cin >> initVertex >> finalVertex;
	_searchMinDist(initVertex);
	_path.push_back(finalVertex);
	_searchPath(finalVertex);
	_output();
}

void DijkstraPath::_searchMinDist(int currentVertex) {
	_visitVertex.push_back(currentVertex - 1);

	for(auto& adjacencyVertex : _weightGraph.getWeightListAdjacency()[currentVertex]) {
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
        if (std::find(_visitVertex.begin(), _visitVertex.end(), i) == _visitVertex.end() && _minDist[i] < minDistance) {
            minDistance = _minDist[i];
            nextVertex = i + 1;
        }
    }

    if (nextVertex != -1)
        _searchMinDist(nextVertex);
}

void DijkstraPath::_searchPath(int finalVertex) {
	int weightAdjacency, weightCurrentVertex;
	int numberAdjacency;

	for(auto& adjacencyVertex : _weightGraph.getWeightListAdjacency()[finalVertex]) {
		weightCurrentVertex = adjacencyVertex.getWeight();
		numberAdjacency = adjacencyVertex.getNumber();
		weightAdjacency = _minDist[finalVertex - 1] - weightCurrentVertex;
		
		if(_minDist[numberAdjacency - 1] == weightAdjacency) {
			_path.insert(_path.begin(), numberAdjacency);
			_searchPath(numberAdjacency);
			break;
		}
	}
}

void DijkstraPath::_output() {
	cout << "Minimal Path" << endl;

    for(auto it = _path.begin(); it != _path.end();) {
        cout << *it;
        
        if(++it != _path.end())
        cout << " => ";
    }
    
    cout << endl;
}