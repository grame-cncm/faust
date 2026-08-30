#pragma once
#include "signals.hh"

Tree revealIIR(Tree lsig);

/// instruction probe (FAUST_SS_SPLIT) : letrec-splitting potential, see revealIIR.cpp
void projSCCReport(Tree lsig);
