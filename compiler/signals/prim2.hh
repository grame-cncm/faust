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
 
#ifndef _Prim2_
#define _Prim2_

#include "tlib.hh"
#include "sigtype.hh"

// fonction de gestion des foreign functions (ffun) dans FAUST (fonctions C externes)

Tree ffunction (Tree signature, Tree incfile, Tree libfile);

bool 		isffunction(Tree t);

Tree 		ffsignature(Tree t);
const char* ffname(Tree t);
int 		ffarity(Tree t);
int 		ffrestype(Tree t);
int 		ffargtype(Tree t, int i);
const char* ffincfile(Tree t);
const char* fflibfile(Tree t);

#endif
