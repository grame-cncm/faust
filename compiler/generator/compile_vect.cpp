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
#include "ppsig.hh"


/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string VectorCompiler::generateCode (Tree sig)
{
    if (fClass->topLoop()->isEmpty() == false && needSeparateLoop(sig)) {
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




/**
 * Test if a signal need to be compiled in a separate loop.
 * @param sig the signal expression to test.
 * @return true if a separate loop is needed
 */
bool VectorCompiler::needSeparateLoop(Tree sig)
{
    Occurences* o = fOccMarkup.retrieve(sig);
    Type        t = getSigType(sig);
    int         c = getSharingCount(sig);
    bool        b;

    int         i;
    Tree        x;

    if (verySimple(sig) || t->variability()<kSamp) {
        // non sample computation never require a loop
        b = false;
    } else if (isProj(sig, &i ,x)) {
        // recursive expressions require a separate loop
        cerr << "REC ";
        b = true;
    } else if (o->getMaxDelay()>0) {
        // delayed expressions require a separate loop
        cerr << "DLY ";
        b = true;
    } else if (c > 1) {
        // expressions used several times required a separate loop
        cerr << "SHA(" << c << ") ";
        b = true;
    } else {
        // sample expressions that are not recursive, not delayed
        // and not shared, doesn't require a separate loop.
        b = false;
    }

    if (b) { 
        cerr << "separate loop for " << ppsig(sig) << endl;
    }
    return b;
}
