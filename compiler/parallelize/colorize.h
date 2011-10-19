#ifndef __COLORIZE__
#define __COLORIZE__

#include <set>
#include <algorithm>
#include <iterator>

#include "tlib.hh"

void splitDependance(const set<Tree>& exps, set<Tree>& post, set<Tree>& pre);

#endif
