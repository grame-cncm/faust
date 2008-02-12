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



#include "compile_vect.hh"


/**
 * Open a non-recursive loop on top of the loop stack
 */
void    VectorCompiler::openLoop(const string& size)
{
    fTopLoopStack = new Loop(fTopLoopStack, size);
}


/**
 * Open a recursive loop on top of the loop stack
 */
void    VectorCompiler::openLoop(Tree recsymbol, const string& size)
{
    fTopLoopStack = new Loop(recsymbol, fTopLoopStack, size);    
}


/**
 * Close the top loop and either store it in the loop set
 * or merge it within the enclosing one
 */
void    VectorCompiler::closeLoop()
{
    assert(fTopLoopStack);
    Loop* l = fTopLoopStack;
    fTopLoopStack = l->fEnclosingLoop;

    if (l->hasRecDependencies()) {
        assert(fTopLoopStack);
        fTopLoopStack->absorb(l);
        delete l;
    } else {
        fLoopSet.insert(l);
    }
}


