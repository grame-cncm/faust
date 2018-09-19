#ifndef __NORMALIZE__
#define __NORMALIZE__
#include "tree.hh"

Tree normalizeAddTerm(Tree t);

Tree normalizeDelay1Term(Tree s);
Tree normalizeFixedDelayTerm(Tree s, Tree d);

#endif
