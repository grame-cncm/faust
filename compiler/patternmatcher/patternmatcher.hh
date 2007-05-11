
#ifndef __PATTERNMATCHER__
#define __PATTERNMATCHER__

using namespace std;
#include <vector>
#include "tlib.hh"

struct Automaton;

/* Create a pattern matching automaton from the given list of rules. */

Automaton *make_pattern_matcher(Tree R);

/* Apply the pattern matcher to a single argument, starting from a given state
   s. Returns the resulting state, modifies the variable bindings E
   accordingly, and sets C to the resulting closure if a final state is
   reached. Result will be -1 to indicate a matching failure, and C will be
   set to nil if no final state has been reached yet. */

int apply_pattern_matcher(Automaton *A,		// automaton
                          int s,		// start state
	                  Tree X,		// arg to be matched
			  Tree& C,		// output closure (if any)
			  vector<Tree>& E);	// modified output environments

#endif
