#ifndef __COLORIZE__
#define __COLORIZE__

#include <algorithm>
#include <iterator>
#include <set>

#include "tlib.hh"

void splitDependance(const set<Tree>& exps, set<Tree>& post, set<Tree>& pre);

#endif
