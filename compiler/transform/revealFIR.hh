#pragma once

#include "signals.hh"

Tree revealFIR(Tree L);

// sig is a recursive projection and
// can represented by an IIR, return that IIR
Tree revealIIR(Tree sig);