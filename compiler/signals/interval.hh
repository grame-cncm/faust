/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef __signals_intervals__
#define __signals_intervals__

#include <cmath>
#include <iostream>

#include "exception.hh"
#include "garbageable.hh"

//#include "global.hh"

#include "interval/interval_def.hh"

#include "interval/interval_algebra.hh"

extern itv::interval_algebra gAlgebra;

//#include "global.hh"

#ifdef _WIN32
inline double log2(double e)
{
    return log(e) / log(double(2));
}
#endif

using namespace std;

inline double min(double x, double y)
{
    return (x < y) ? x : y;
}
inline double max(double x, double y)
{
    return (x > y) ? x : y;
}
inline double min4(double a, double b, double c, double d)
{
    return min(min(a, b), min(c, d));
}
inline double max4(double a, double b, double c, double d)
{
    return max(max(a, b), max(c, d));
}

// itv::interval_algebra gAlgebra;

// extern global* gGlobal;

using interval = itv::interval;

inline interval operator+(const interval& x, const interval& y)
{
    return gAlgebra.Add(x, y);
}

inline interval operator-(const interval& x, const interval& y)
{
    return gAlgebra.Sub(x, y);
}

inline interval operator*(const interval& x, const interval& y)
{
    return gAlgebra.Mul(x, y);
}

inline interval operator/(const interval& x, const interval& y)
{
    return gAlgebra.Div(x, y);
}

// The result should be [0..y.hi[, approximated with 0, nexttoward(y.hi, -INFINITY)
inline interval operator%(const interval& x, const interval& y)
{
    return gAlgebra.Mod(x, y);
}

//----------------------booleans&bits--------------------------------------

inline interval operator&(const interval& x, const interval& y)
{
    return gAlgebra.And(x, y);
}

inline interval operator|(const interval& x, const interval& y)
{
    return gAlgebra.Or(x, y);
}

inline interval operator^(const interval& x, const interval& y)
{
    return gAlgebra.Xor(x, y);
}

inline interval operator<<(const interval& x, const interval& y)
{
    return gAlgebra.Lsh(x, y);
}

inline interval operator>>(const interval& x, const interval& y)
{
    return gAlgebra.Rsh(x, y);
}

// ---------------------comparaisons------------------------------
// Note : the comparisons are not about the intervals
// but the interval of the signal comparisons

inline interval operator<(const interval& x, const interval& y)
{
    return gAlgebra.Lt(x, y);
}

inline interval operator<=(const interval& x, const interval& y)
{
    return gAlgebra.Le(x, y);
}

inline interval operator>(const interval& x, const interval& y)
{
    return gAlgebra.Gt(x, y);
}

inline interval operator>=(const interval& x, const interval& y)
{
    return interval(0, 1);
}

inline interval operator==(const interval& x, const interval& y)
{
    return gAlgebra.Eq(x, y);
}

inline interval operator!=(const interval& x, const interval& y)
{
    return gAlgebra.Ne(x, y);
}

//-----------------------------------------------------------------------

inline interval min(const interval& x, const interval& y)
{
    return gAlgebra.Min(x, y);
}

inline interval max(const interval& x, const interval& y)
{
    return gAlgebra.Max(x, y);
}

inline interval pow(const interval& x, const interval& y)
{
    return gAlgebra.Pow(x, y);
}

inline interval iint(const interval& x)
{
    return gAlgebra.Int(x);
}

inline interval fmod(const interval& x, const interval& y)
{
    return gAlgebra.Mod(x, y);
}

inline interval abs(const interval& x)
{
    return gAlgebra.Abs(x);
}

/**
 * @struct res
 * the fixed-point resolution of the signal
 * i.e. the index of the least significant bit of the fixed-point representation of the signal.
 * which is a _relative_ number.
 */

struct res : public virtual Garbageable {
    bool valid;  ///< true if a resolution has indeed been compiled
    int  index;  ///< the index of the lsb, if any

    res() : valid(false), index(0) {}
    res(int i) : valid(true), index(i) {}

    string toString() const
    {
        string sout;
        sout += "r(";
        sout += valid ? to_string(index) : "???";
        sout += ")";
        return sout;
    }
};

inline ostream& operator<<(ostream& dst, const res& r)
{
    return dst << r.toString();
}

#endif
