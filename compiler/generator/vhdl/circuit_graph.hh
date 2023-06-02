#pragma once

//-------------------------CircuitGraph-----------------------------------
// Weighted graph representing the final VHDL circuit, including registers
//------------------------------------------------------------------------

#include "global.hh"
#include <vector>

struct CircuitEdge {
    int target;
    int weight;
};

struct CircuitVertex {
    int propagation_delay;
};

class CircuitGraph {
   private:
    std::vector<CircuitVertex> _vertices;
    std::vector<std::vector<CircuitEdge>> _edges;

   public:
    /** Initializes a CircuitGraph from a signal */
    CircuitGraph(Tree signal) {

    }

    /** Optimizes the CircuitGraph using implemented methods
     * Optimization passes:
     * - retiming
     * */
    void optimize();
};
