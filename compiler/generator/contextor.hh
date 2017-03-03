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
	HISTORY
	22/01/05 : corrected bug on bool signals cached in float variables
*****************************************************************************/

#ifndef __CONTEXTOR__
#define __CONTEXTOR__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "exception.hh"

/**
 *	An automatic stack of contexts
 *
 */
class contextor
{
	static int 	top;
	static int	pile[1024];

 public:
	contextor(int n)	{ top = 0; pile[top] = n; }	// contructor to be called only once at the
                                                    // top level to initialize the stack

	contextor() 		{ faustassert(top >= 0 && top < 1023); int n = pile[top++]; pile[top] = n; }
	~contextor() 		{ top--; }

	void set(int n)	{ pile[top] = n; }
	int get()	{ return pile[top]; }
};

#endif
