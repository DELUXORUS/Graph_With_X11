#ifndef PRUEFER_DECODE_H
#define PRUEFER_DECODE_H

#include <vector>
#include <map>
#include <algorithm>

#include "BaseAlgorithm.h"
#include "PrueferEncode.h"


class PrueferDecode {
    public:
        PrueferDecode(std::vector<int> prueferCode): _prueferCode(prueferCode) {}
        void search();
    private:
        void _output();
        void _prueferDecoding(int vertex1, int vertex2);
        void _outputPrueferCode();
        void _outputAdditionCode();
        std::map<int, std::vector<int>> _listAdjacencyTree;
        std::vector<int> _prueferCode;
        std::vector<int> _additionPrueferCode;
};

#endif