#include "PaintAlgorithm.h"


void PaintAlgorithm::search() {
    _sortVertex();
    _colorDistribution();
    _output();
}

void PaintAlgorithm::_sortVertex() {
    int maxSize = 0;

    for(auto rowList : _graph.getListAdjacency()) {
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
                auto it = std::find(_graph.getListAdjacency()[vertexForCheck].begin(),
                                     _graph.getListAdjacency()[vertexForCheck].end(),
                                     currentVertex);

                if (it != _graph.getListAdjacency()[vertexForCheck].end()) {
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
    std::cout << std::endl << "Many Colors" << std::endl;

    for (const auto& row : _manyColors) {
        std::cout << "Color " << row.first << ":";

        for (int vertex : row.second) {
            std::cout << "   " << vertex;
        }

        std::cout << std::endl;
    }
}