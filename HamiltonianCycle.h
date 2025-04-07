#ifndef HAMILTONIAN_CYCLE_H
#define HAMILTONIAN_CYCLE_H

#include "BaseAlgorithm.h"


class HamiltonianCycle : public Algorithm {
    public:
        HamiltonianCycle() {};
        HamiltonianCycle(Graph graph): Algorithm(graph) {
            std::vector<int> hamiltonianCycle(_graph.getNumberVertex() + 1, -1);
            _hamiltonianCycle = hamiltonianCycle;
        }
        void search();
    private:
        bool _search(int pos);
        int _check(int currentVertex, int pos);
        void _output();
        std::vector<int> _hamiltonianCycle;
};

#endif