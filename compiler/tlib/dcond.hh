#ifndef DCOND_HH
#define DCOND_HH

#include "list.hh"

/*
 * Dcond are conditions in disjunctive normal form implemented
 * as set of set of Tree
 */

// WARNING : Memoization probably needed here !!!!

Tree dnfCond (Tree c);                  // create a dcond from a simple expression

Tree dnfAnd (Tree c1, Tree c2);         // And operation between two conditions in DNF

Tree dnfOr (Tree c1, Tree c2);          // Or operation between two conditions in DNF

bool dnfLess (Tree c1, Tree c2);        // True if (c1 v c2) == c2 i.e. c1 ==> c2


Tree cnfCond (Tree c);
Tree cnfAnd (Tree c1, Tree c2);
Tree cnfOr (Tree c1, Tree c2);
bool cnfLess (Tree c1, Tree c2);

#endif // DCOND_HH
