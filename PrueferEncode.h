#ifndef PRUEFER_ENCODE_H
#define PRUEFER_ENCODE_H

#include <vector>
#include <set>
#include <limits>
#include <algorithm>

#include "BaseAlgorithm.h"


class PrueferEncode : public Algorithm {
    public:
        PrueferEncode() {}
        PrueferEncode(Graph graph): Algorithm(graph) {
            _deformableListAdjacency = _graph.getListAdjacency(); 
        }
        void search();
        std::vector<int>& getCodePruefer() { return _codePruefer; }
    private:
        void _output();
        bool _encode();
        std::map<int, std::vector<int>> _deformableListAdjacency;
        std::vector<int> _codePruefer;
};

#endif