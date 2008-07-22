#ifndef __GRAPHSORTING__
#define __GRAPHSORTING__


#include <set>
#include "loop.hh"

 

typedef set<Loop*>      lset;
typedef vector<Loop*>   lvec;
typedef vector<lset>    lgraph;    

/**
 * Topological sort of an acyclic graph of loops starting 
 * from its root. The loops are collect in an lgraph : a 
 * vector of sets of loops
 */
void sortGraph(Loop* root,lgraph& V);

#endif
