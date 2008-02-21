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
#include "delayline.hh"


void VectorCompiler::compileMultiSignal (Tree L)
{
    //contextor recursivness(0);
    L = prepare(L);     // optimize, share and annotate expression
    for (int i = 0; i < fClass->inputs(); i++) {
        fClass->addSlowCode(subst("float* input$0 = &input[$0][index];", T(i)));
    }
    for (int i = 0; i < fClass->outputs(); i++) {
        fClass->addSlowCode(subst("float* output$0 = &output[$0][index];", T(i)));
    }
    for (int i = 0; isList(L); L = tl(L), i++) {
        Tree sig = hd(L);
        fClass->addExecCode(subst("output$0[i] = $1;", T(i), CS(sig)));
    }
    generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot));
    if (fDescription) {
        fDescription->ui(prepareUserInterfaceTree(fUIRoot));
    }
}


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
            // projection of a recursive group x
            if (l->findRecDefinition(x)) {
                // x is already in the loop stack
                l->addRecDependency(x);
                return ScalarCompiler::generateCode(sig);
            } else {
                // x must be defined
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




void VectorCompiler::generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp)
{
    if (mxd == 0) {
        vectorLoop(fClass, ctype, vname, exp);
    } else {
        dlineLoop(fClass, ctype, vname, mxd, exp);
    }
}


string VectorCompiler::generateVariableStore(Tree sig, const string& exp)
{
    Type        t = getSigType(sig);

    if (getSigType(sig)->variability() == kSamp) {
        string      vname, ctype;
        getTypedNames(t, "Vector", ctype, vname);
        vectorLoop(fClass, ctype, vname, exp);
        return subst("$0[i]", vname);
    } else {
        return ScalarCompiler::generateVariableStore(sig, exp);
    }
}


/**
 * Generate code for accessing a delayed signal. The generated code depend of 
 * the maximum delay attached to exp and the gLessTempSwitch. 
 */

string VectorCompiler::generateFixDelay (Tree sig, Tree exp, Tree delay)
{
    int     mxd, d; 
    string  vecname;
 
    CS(exp); // ensure exp is compiled to have a vector name

    mxd = fOccMarkup.retrieve(exp)->getMaxDelay();

    assert(getVectorNameProperty(exp, vecname));

    if (mxd == 0) {
        // not a real vector name but a scalar name
        return vecname;

    } else if (mxd < gMaxCopyDelay) {
        if (isSigInt(delay, &d)) {
            if (d == 0) {
                return subst("$0[i]", vecname);
            } else {
                return subst("$0[i-$1]", vecname, T(d));
            }
        } else {
            return subst("$0[i-$1]", vecname, CS(delay));
        }

    } else {

        // long delay : we use a ring buffer of size 2^x
        int     N   = pow2limit( mxd+1 );
        return generateCacheCode(sig, subst("$0[(IOTA-$1)&$2]", vecname, CS(delay), T(N-1))); 
    }
}


