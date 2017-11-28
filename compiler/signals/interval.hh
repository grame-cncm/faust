/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/
 
#ifndef __signals_intervals__
#define __signals_intervals__

#include <math.h>
#include <iostream>

#ifdef _WIN32
inline double log2(double e) { return log(e)/log(double(2)); }
#endif

using namespace std;

inline double min(double x, double y) { return (x<y) ? x:y; }
inline double max(double x, double y) { return (x>y) ? x:y; }
inline double min4(double a, double b, double c, double d)	{ return min(min(a, b), min(c, d)); }
inline double max4(double a, double b, double c, double d)	{ return max(max(a, b), max(c, d)); }

struct interval : public virtual Garbageable
{
	bool	valid;			///< true if it is a valid interval
	double	lo;				///< minimal value
	double	hi;				///< maximal value
	
    interval ()						: valid(false), lo(-HUGE_VAL), hi(HUGE_VAL) {}
    interval (double n) 			: valid(true), lo(n), hi(n) {}
	interval (double n, double m) 	: valid(true), lo(min(n,m)), hi(max(n,m)) {}
    interval (const interval& r)	: valid(r.valid), lo(r.lo), hi(r.hi) {}
	
    bool isvalid()  { return valid; }
    bool isconst()  { return valid && (lo == hi); }
    bool haszero()  { return (lo <= 0) && (0 <= hi); }
};

inline ostream& operator<<(ostream& dst, const interval& i) 	
{ 
	if (i.valid) {
		return dst << "interval(" << i.lo << ", " << i.hi << ")";
	} else {
		return dst << "interval()";
	}
}

inline interval reunion(const interval& x, const interval& y)
{
	if (x.valid & y.valid) {
		return interval(min(x.lo,y.lo), max(x.hi,y.hi));
	} else {
		return interval();
	}
}

inline interval operator+(const interval& x, const interval& y) 	
{ 
	return (x.valid&y.valid) ? interval(x.lo+y.lo, x.hi+y.hi) : interval(); 
}

inline interval operator-(const interval& x, const interval& y) 	
{ 
	return (x.valid & y.valid) ? interval(x.lo-y.hi, x.hi-y.lo) : interval();; 
}

inline interval operator*(const interval& x, const interval& y) 	
{ 
	if (x.valid&y.valid) {
		double a = x.lo*y.lo;
		double b = x.lo*y.hi;
		double c = x.hi*y.lo;
		double d = x.hi*y.hi;
		return interval(min4(a,b,c,d), max4(a,b,c,d));
	} else {
		return interval();
	}
}

inline interval operator/(const interval& x, const interval& y)
{
	return (x.valid && y.valid && ((y.lo > 0) || (y.hi < 0))) 
			? x * interval(1/y.hi,1/y.lo)
			: interval();
}

inline interval operator%(const interval& x, const interval& y)
{
	return (x.valid && y.valid && x.lo >= 0 && y.lo > 0) 
			? interval(0,y.hi)
			: interval();
}

/**
 * Convert a number 1bbb..b into a bit mask 1111..1 of same width
 */
inline int bitmask (double x)	{
    int v = int(x);
    for (int i=1; i<32; i*=2)   { v |= v>>i; }
    return v;
}

//----------------------booleans&bits--------------------------------------

inline interval operator&(const interval& x, const interval& y)
{
	if (x.valid && y.valid) {
		if (x.lo >= 0 && y.lo >= 0) {
			return interval(0, bitmask(x.hi) & bitmask(y.hi));
		} else if (y.lo >= 0) {
			return interval(0, bitmask(y.hi));
		} else if (x.lo >= 0) {
			return interval(0, bitmask(y.hi));
		} else {
			return interval();
		}
	} else if (x.valid && x.lo >= 0) {
		return interval(0, bitmask(x.hi));
	} else if (y.valid && y.lo >= 0) {
		return interval(0, bitmask(y.hi));
	} else {
		return interval();
	}
}

inline interval operator|(const interval& x, const interval& y)
{
	if (x.valid && y.valid && x.lo >= 0 && y.lo >= 0) {
		return interval(0, bitmask(x.hi) | bitmask(y.hi));
	} else {
		return interval();
	}
}

inline interval operator^(const interval&, const interval&)
{
	return interval();
}

inline interval operator<<(const interval&, const interval&)
{
	return interval();
}

inline interval operator>>(const interval&, const interval&)
{
	return interval();
}

// ---------------------comparaisons------------------------------
// note : les comparaisons ne portent pas sur les intervals 
// mais l'interval des comparaisons de signaux

inline interval operator<(const interval&, const interval&)
{
	return interval(0,1);
}

inline interval operator<=(const interval&, const interval&)
{
	return interval(0,1);
}

inline interval operator>(const interval&, const interval&)
{
	return interval(0,1);
}

inline interval operator>=(const interval&, const interval&)
{
	return interval(0,1);
}

inline interval operator==(const interval&, const interval&)
{
	return interval(0,1);
}

inline interval operator!=(const interval&, const interval&)
{
	return interval(0,1);
}

//-----------------------------------------------------------------------

inline interval min(const interval& x, const interval& y)
{
	return interval(min(x.lo,y.lo), min(x.hi,y.hi));
}

inline interval max(const interval& x, const interval& y)
{
	return interval(max(x.lo,y.lo), max(x.hi,y.hi));
}

inline interval pow(const interval& x, const interval& y)
{
    if (x.lo > 0.0) {
        double a = pow(x.lo,y.lo);
        double b = pow(x.lo,y.hi);
        double c = pow(x.hi,y.lo);
        double d = pow(x.hi,y.hi);
        return interval(min4(a,b,c,d), max4(a,b,c,d));
    } else {
        //std::cerr << "interval not computed for : pow(" << x <<"," << y << ")" << std::endl;
        return interval();
    }
}

inline interval iint(const interval& x)
{
    return interval(double(int(x.lo)), double(int(x.hi)));
}

inline interval fmod(const interval& x, const interval& y)
{
    interval n = iint(x/y);
    return x - n*y;
}

inline interval abs(const interval& x)
{
	if (x.valid) {
		if (x.lo >= 0) {
			return x;
		} else if (x.hi < 0) {
			return interval(fabs(x.hi), fabs(x.lo));
		} else {
			return interval(0, max(fabs(x.lo), x.hi));
		}
	} else {
		return x;
	}
}		

#endif
