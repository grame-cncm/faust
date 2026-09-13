/************************************************************************
 ************************************************************************
    FAUST signal library
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

#include <cfloat>
#include "sigs-state.hh"

namespace sigs {

State g;

}  // namespace sigs

// The float ranges per precision (index gFloatSize : 1 float, 2 double, 3 quad, 4 fixed-point).
// (the same tables floats.cpp sets for every backend ; index gFloatSize :
// 1 float, 2 double, 3 quad, 4 fixed-point). floatmax holds the IEEE-754
// exponent masks, despite its name.
static const double  kFloatMin[] = {0, FLT_MIN, DBL_MIN, LDBL_MIN, FLT_MIN};
static const int64_t kFloatMax[] = {0, 0x7F800000, 0x7FF0000000000000, 0x7FF0000000000000, 0x7F800000};

double sigs::inummin()
{
    return kFloatMin[g.gFloatSize];
}

int64_t sigs::inummax()
{
    return kFloatMax[g.gFloatSize];
}
