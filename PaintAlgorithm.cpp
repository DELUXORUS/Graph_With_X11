#include "PaintAlgorithm.h"


void PaintAlgorithm::initialize(std::map<int, std::vector<int>> listAdjacency,
                                std::vector<std::vector<int>> matrixAdjacency,
                                std::vector<Vertex> numberVertex)
{
copy(listAdjacency.begin(), listAdjacency.end(), 
inserter(_listAdjacencyForCurrentGraph, _listAdjacencyForCurrentGraph.end()));
_matrixAdjacencyForCurrentGraph = matrixAdjacency;
_numberVertexForCurrentGraph = numberVertex;
}

void PaintAlgorithm::search() {
    _sortVertex();
    _colorDistribution();
    _output();
}

void PaintAlgorithm::_sortVertex() {
    int maxSize = 0;

    for(auto rowList : _listAdjacencyForCurrentGraph) {
        if(rowList.second.size() >= maxSize) {
            _vertexSortedDegree.insert(_vertexSortedDegree.begin(), rowList.first);
            maxSize = rowList.second.size();
        }
        else
            _vertexSortedDegree.push_back(rowList.first);
    }
}

void PaintAlgorithm::_colorDistribution() {
    int countSet = 1;

    _manyColors[countSet].push_back(_vertexSortedDegree[0]);
    ++countSet;

    for (size_t i = 1; i < _vertexSortedDegree.size(); ++i) {
        int currentVertex = _vertexSortedDegree[i];
        bool foundColor = false;

        for (int j = 1; j < countSet; ++j) {
            bool canAdd = true;

            for (int vertexForCheck : _manyColors[j]) {
                auto it = std::find(_listAdjacencyForCurrentGraph[vertexForCheck].begin(),
                                    _listAdjacencyForCurrentGraph[vertexForCheck].end(),
                                     currentVertex);

                if (it != _listAdjacencyForCurrentGraph[vertexForCheck].end()) {
                    canAdd = false;
                    break;
                }
            }

            if (canAdd == true) {
                _manyColors[j].push_back(currentVertex);
                foundColor = true;
                break;
            }
        }

        if (foundColor == false) {
            _manyColors[countSet].push_back(currentVertex);
            ++countSet;
        }
    }
}

void PaintAlgorithm::_output() {
    cout << endl << "Many Colors" << endl;

    for (const auto& row : _manyColors) {
        cout << "Color " << row.first << ":";

        for (int vertex : row.second) {
            cout << "   " << vertex;
        }

        cout << endl;
    }
}