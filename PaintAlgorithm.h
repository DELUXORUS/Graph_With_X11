#ifndef PAINT_ALGORITHM_H_
#define PAINT_ALGORITHM_H_

#include <vector>
#include <algorithm>

#include "BaseAlgorithm.h"


class PaintAlgorithm : public Algorithm {
    public:
        PaintAlgorithm() {}
        PaintAlgorithm(Graph graph) : Algorithm(graph) {}
        void search();
    private:
        void _sortVertex();
        void _colorDistribution();
        void _output();
        std::vector<int> _vertexSortedDegree;
        std::map<int, std::vector<int>> _manyColors;
};

#endif