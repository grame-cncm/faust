#ifndef __GRAPHSORTING__
#define __GRAPHSORTING__

#include <set>
#include "loop.hh"

class CodeLoop;

typedef set<Loop*>      lset;
typedef set<CodeLoop*>  lclset;

typedef vector<Loop*>   lvec;

typedef vector<lset>    lgraph;  
typedef vector<lclset>  lclgraph;  

/**
 * Topological sort of an acyclic graph of loops starting 
 * from its root. The loops are collect in an lgraph : a 
 * vector of sets of loops
 */
void sortGraph(Loop* root, lgraph& V);

/**
 * Compute how many time each loop is used in a DAG
 */
void computeUseCount(Loop* l);

/**
 * Group together sequences of loops
 */
void groupSeqLoops(Loop* l);
 
#endif
