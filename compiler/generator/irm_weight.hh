/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#ifndef _IRM_WEIGHT_
#define _IRM_WEIGHT_

#include "signals.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"

/**
 * IRM(x; p), the smoother y = mix(p, x, y'), p its pole : the weight of x, 1 - p, when the
 * normal form wrote the pole as the complement Sum(1, neg(w)) (the state of a TPT filter,
 * p = 1 - 2g) : w, read as it is, exact ; nullptr otherwise.
 */
inline Tree irmInputWeight(Tree p)
{
    Tree w;
    tvec ws;
    if (isSigSum(p, ws) && ws.size() == 2 && isOne(ws[0]) && isSigNeg(ws[1], w)) {
        return w;
    }
    return nullptr;
}

#endif
