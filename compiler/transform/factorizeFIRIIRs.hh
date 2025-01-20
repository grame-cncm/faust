#pragma once

#include "signals.hh"

// Transform FIRs and IIRs by factorizing common coefficients when possible
Tree factorizeFIRIIRs(Tree L);
