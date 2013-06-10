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
 
#include "prim2.hh"
#include "global.hh"

#include <stdlib.h>

Tree ffunction (Tree signature, Tree incfile, Tree libfile)
{
	return tree(gGlobal->FFUN, signature, incfile, libfile);
}

bool isffunction(Tree t)
{
	return t->node() == Node(gGlobal->FFUN); 
}

Tree ffsignature(Tree ff) 
{ 
	return ff->branch(0); 
}

const char* ffincfile(Tree ff)
{
	return tree2str(ff->branch(1));
}

const char* fflibfile(Tree ff)
{
	return tree2str(ff->branch(2));
}

int ffrestype(Tree t)
{
	return tree2int(hd(ffsignature(t)));
}

const char* ffname(Tree t)
{
    Tree namelist = nth(ffsignature(t),1);
    //cerr << "ffname " << tree2str(nth(namelist,gFloatSize-1)) << endl;
    return tree2str(nth(namelist, gGlobal->gFloatSize - 1));
}

int ffarity(Tree t)
{
	return len(ffsignature(t))-2;
}

int ffargtype(Tree t, int i)
{
	return tree2int(nth(ffsignature(t), i+2));
}
