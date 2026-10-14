#pragma once
#include "signals.hh"

Tree revealIIR(Tree lsig);

// the single-definition recursions y = mix(c, x, y@1), mix(c, y@1, x) become IRM nodes
Tree revealIRM(Tree lsig);

