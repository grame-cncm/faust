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
string  VectorCompiler::CS (Tree sig)
{
    int         i;
    Tree        x;
    string      code;

    if (!getCompiledExpression(sig, code)) {
        code = generateCode(sig);
        setCompiledExpression(sig, code);
    } else {
        // check for recursive dependencies
        Loop*   l = fClass->topLoop();
        if (isProj(sig, &i, x) && l->findRecDefinition(x)) {
            l->addRecDependency(x);
        }
    }
    return code;
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string VectorCompiler::generateCode (Tree sig)
{
    int     i;
    Tree    x;
    Loop*   l;

    l = fClass->topLoop();
    assert(l);

    if (needSeparateLoop(sig)) {
        // we need a separate loop unless it's an old recursion
        if (isProj(sig, &i, x)) {
            if (l->findRecDefinition(x)) {
                l->addRecDependency(x);
                return ScalarCompiler::generateCode(sig);
            } else {
                fClass->openLoop(x, "count");
                string c = ScalarCompiler::generateCode(sig);
                fClass->closeLoop();
                return c;
            }
        } else {
            fClass->openLoop("count");
            string c = ScalarCompiler::generateCode(sig);
            fClass->closeLoop();
            return c;
        }
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
    Tree        x,y;

    if (verySimple(sig) || t->variability()<kSamp) {
        b = false;      // non sample computation never require a loop
    } else if (isSigFixDelay(sig, x, y)) {
        b = false;      // 
    } else if (isProj(sig, &i ,x)) {
        //cerr << "REC "; // recursive expressions require a separate loop
        b = true;
    } else if (o->getMaxDelay()>0) {
        //cerr << "DLY "; // delayed expressions require a separate loop
        b = true;
    } else if (c > 1) {
        //cerr << "SHA(" << c << ") "; // expressions used several times required a separate loop
        b = true;
    } else {
        // sample expressions that are not recursive, not delayed
        // and not shared, doesn't require a separate loop.
        b = false;
    }
    return b;
}
