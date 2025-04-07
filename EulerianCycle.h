#ifndef EULERIAN_CYCLE_H_
#define EULERIAN_CYCLE_H_

#include "BaseAlgorithm.h"


class EulerianCycle : public Algorithm {
    public:
        EulerianCycle() {}
        EulerianCycle(Graph graph): Algorithm(graph) {}
        void search();
    private:
        void _search(int currentVertex);
        int _check();
        void _output();
        std::vector<int> _eulerianCycleOrPath;
};

#endif