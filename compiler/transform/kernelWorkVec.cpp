/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "kernelWorkVec.hh"

#include "signals.hh"

// source of a kernel read : unwrap ONE literal delay. x@d -> (x, d) ;
// anything else -> (t, 0).
static Tree kernelSrc(Tree t, int& sh)
{
    Tree a, b;
    int  d;
    if (isSigDelay(t, a, b) && isSigInt(b, &d)) {
        sh = d;
        return a;
    }
    sh = 0;
    return t;
}

bool kernelWorkVec(Tree t, tvec& V)
{
    tvec W;
    if (!isSigFIR(t, W)) {
        return false;
    }
    int  sh;
    Tree src = kernelSrc(W[0], sh);
    if (sh == 0) {
        V = W;
        return true;
    }
    V.clear();
    V.push_back(src);
    for (int k = 0; k < sh; k++) {
        V.push_back(sigInt(0));
    }
    for (size_t i = 1; i < W.size(); i++) {
        V.push_back(W[i]);
    }
    return true;
}
