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
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string VectorCompiler::generateCode (Tree sig)
{
    if (needSeparateLoop(sig)) {
        fClass->openLoop("count");
        string c = ScalarCompiler::generateCode(sig);
        fClass->closeLoop();
        return c;
    } else {
        return ScalarCompiler::generateCode(sig);
    }
}


/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string VectorCompiler::generateCacheCode(Tree sig, const string& exp)
{
    return ScalarCompiler::generateCacheCode(sig, exp);
}


bool VectorCompiler::needSeparateLoop(Tree sig)
{
    return false;
}
