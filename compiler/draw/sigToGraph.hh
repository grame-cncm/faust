#ifndef SIGTOGRAPH_HH
#define SIGTOGRAPH_HH

#include <fstream>
#include <iostream>
#include <string>
#include "signals.hh"
#include "sigraterules.hh"

using namespace std;

/**
 * Draw a list of signals L as a directed graph using
 * graphviz's dot language
 */
void sigToGraph(Tree sig, ofstream& fout, RateInferrer* R);

#endif  // SIGTOGRAPH_HH
