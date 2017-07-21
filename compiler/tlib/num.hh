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
 
/*****************************************************************************
******************************************************************************
								NUM 
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Nums are tagged unions of ints and floats. Nums are completly described by 
this header file.

 API:
 ----
	num(10);				: num with int content
	num(3.14159);			: num with double content
	
	num op num				: op is any C binary operator
	
	type(num)				: 0 = int, 1 = double
	int(num);				: int content of num or conversion
	double(num);				: double content of num or conversion
	
 History :
 ---------
 	2002-02-08 : First version
	
******************************************************************************
*****************************************************************************/

#ifndef __NUM__
#define __NUM__

#include <math.h>

#include "garbageable.hh"

//-------------------------------------------------------------------------
// Class num = (type x (int + double))
//		type 0 -> int
//		type 1 -> double
//-------------------------------------------------------------------------

class num : public virtual Garbageable
{
    
private:
    
	int	fType;
	union { 
		int 	i; 
		double 	f;
	} fData;

 public:
    
	// constructors
	num (int x=0) 		: fType(0) 			{ fData.i = x; }
	num (double x) 		: fType(1)  		{ fData.f = x; }
	num (const num& n) 	: fType(n.fType) 	{ fData.i = n.fData.i; }

	num& operator = (int n) 	{ fType = 0; fData.i = n; return *this; }
	num& operator = (double n) 	{ fType = 1; fData.f = n; return *this; }
 	
	// accessors
	int			type() 		const 	{ return fType; }
	operator 	int() 		const 	{ return (fType) ? int(fData.f) : fData.i; }
	operator 	double() 	const 	{ return (fType) ? fData.f : double(fData.i); }
	
	// predicats
	bool operator == (const num& n) const { return fType == n.fType && fData.i == n.fData.i; }
	bool operator != (const num& n) const { return fType != n.fType || fData.i != n.fData.i; }
	
};

inline int isfloat (const num& n) { return n.type(); }

inline const num operator+ (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)+double(y)) : num(int(x)+int(y)); }

inline const num operator- (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)-double(y)) : num(int(x)-int(y)); }

inline const num operator* (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)*double(y)) : num(int(x)*int(y)); }

inline const num operator/ (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)/double(y)) : num(int(x)/int(y)); }

inline const num operator% (const num& x, const num& y)	
	{ return num(int(x)%int(y)); }

// Bit shifting operations
inline const num operator<< (const num& x, const num& y)
	{ return num(int(x)<<int(y)); }

inline const num operator>> (const num& x, const num& y)	
	{ return num(int(x)>>int(y)); }

// Bitwise operations
inline const num operator& (const num& x, const num& y)
	{ return num(int(x)&int(y)); }

inline const num operator| (const num& x, const num& y)	
	{ return num(int(x)|int(y)); }

inline const num operator^ (const num& x, const num& y)	
	{ return num(int(x)^int(y)); }

// Comparaison operations
inline const num operator> (const num& x, const num& y)
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)>double(y)) : num(int(x)>int(y)); }

inline const num operator< (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)<double(y)) : num(int(x)<int(y)); }

inline const num operator>= (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)>=double(y)) : num(int(x)>=int(y)); }

inline const num operator<= (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)<=double(y)) : num(int(x)<=int(y)); }

inline const num operator== (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)==double(y)) : num(int(x)==int(y)); }

inline const num operator!= (const num& x, const num& y)	
	{ return (isfloat(x)|isfloat(y)) ? num(double(x)!=double(y)) : num(int(x)!=int(y)); }

#endif    
