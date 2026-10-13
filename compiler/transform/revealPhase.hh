/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#pragma once
#include "signals.hh"

/// W / P written phase(x, P) when W is the remainder x % P of the same P (see revealPhase.cpp)
Tree revealPhase(Tree lsig);
