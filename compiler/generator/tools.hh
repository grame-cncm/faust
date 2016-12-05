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

#ifndef GET_CACHE_LINE_SIZE_H_INCLUDED
#define GET_CACHE_LINE_SIZE_H_INCLUDED

#include <iostream>
#include <stddef.h>

using namespace std;

template <typename T>
void print_type(char const* name)
{
    cout << name
    << " sizeof = " << sizeof (T)
    << " alignof = " << __alignof__ (T)
    << endl;
}

// Author: Nick Strupat
// Date: October 29, 2010
// Returns the cache line size (in bytes) of the processor, or 0 on failure

size_t cache_line_size();

#endif

