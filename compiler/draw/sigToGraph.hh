#ifndef SIGTOGRAPH_HH
#define SIGTOGRAPH_HH

#include "signals.hh"
#include <string>
#include <iostream>
#include <fstream>
#include "sigraterules.hh"

using namespace std;

/**
 * Draw a list of signals L as a directed graph using
 * graphviz's dot language
 */
void sigToGraph (Tree sig, ofstream& fout, RateInferrer* R);

#endif // SIGTOGRAPH_HH
