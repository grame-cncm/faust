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

#include <iostream>
#include <fstream>
#include <sstream>

#include "compile_vect.hh"
#include "floats.hh"
#include "ppsig.hh"

void VectorCompiler::compileMultiSignal(Tree L)
{
    //contextor recursivness(0);
    L = prepare(L);     // optimize, share and annotate expression

    for (int i = 0; i < fClass->inputs(); i++) {
        fClass->addZone3(subst("$1* input$0 = &input[$0][index];", T(i), xfloat()));
    }
    for (int i = 0; i < fClass->outputs(); i++) {
        fClass->addZone3(subst("$1* output$0 = &output[$0][index];", T(i), xfloat()));
    }

    fClass->addSharedDecl("fullcount");
    fClass->addSharedDecl("input");
    fClass->addSharedDecl("output");

    for (int i = 0; isList(L); L = tl(L), i++) {
        Tree sig = hd(L);
        fClass->openLoop("count");
        fClass->addExecCode(Statement("", subst("output$0[i] = $2$1;", T(i), CS(sig), xcast())));
        fClass->closeLoop(sig);
    }

    generateMetaData();
    generateUserInterfaceTree(prepareUserInterfaceTree(fUIRoot), true);
 	generateMacroInterfaceTree("", prepareUserInterfaceTree(fUIRoot));
    if (fDescription) {
        fDescription->ui(prepareUserInterfaceTree(fUIRoot));
    }
    
    if (gGlobal->gPrintJSONSwitch) {
        ofstream xout(subst("$0.json", gGlobal->makeDrawPath()).c_str());
        xout << fJSON.JSON();
    }
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string VectorCompiler::CS(Tree sig)
{
    string code;
    //cerr << "ENTER VectorCompiler::CS : "<< ppsig(sig) << endl;
    if (!getCompiledExpression(sig, code)) {
        code = generateCode(sig);
		//cerr << "CS : " << code << " for " << ppsig(sig) << endl;
        setCompiledExpression(sig, code);
    } else {
        // we require an already compiled expression
        // therefore we must update the dependencies of
        // the current loop
        int     i;
        Tree	x, d, r;
        Loop*   ls;
        Loop*   tl = fClass->topLoop();

        if (fClass->getLoopProperty(sig,ls)) {
            // sig has a loop property
            //cerr << "CASE SH : fBackwardLoopDependencies.insert : " << tl << " --depend(A)son--> " << ls << endl;
			tl->fBackwardLoopDependencies.insert(ls);

        } else if (isSigFixDelay(sig, x, d) && fClass->getLoopProperty(x,ls)) {
            //cerr << "CASE DL : fBackwardLoopDependencies.insert : " << tl << " --depend(B)son--> " << ls << endl;
            tl->fBackwardLoopDependencies.insert(ls);

        } else if (isSigFixDelay(sig, x, d) && isProj(x, &i, r) && fClass->getLoopProperty(r,ls)) {
            //cerr << "CASE DR : fBackwardLoopDependencies.insert : " << tl << " --depend(B)son--> " << ls << endl;
            tl->fBackwardLoopDependencies.insert(ls);

        } else if (isProj(sig, &i, r) && fClass->getLoopProperty(r,ls)) {
            //cerr << "CASE R* : fBackwardLoopDependencies.insert : " << tl << " --depend(B)son--> " << ls << endl;
            tl->fBackwardLoopDependencies.insert(ls);

        } else {
            if (isProj(sig, &i, r)) {
                //cerr << "SYMBOL RECURSIF EN COURS ??? " << *r << endl;
            } else if (getCertifiedSigType(sig)->variability()<kSamp) {
                //cerr << "SLOW EXPRESSION " << endl;
            } else {
                //cerr << "Expression absorbée" << *sig << endl;
            }

        }
    }
    //cerr << "EXIT VectorCompiler::CS : "<< ppsig(sig) << "---code---> " << code << endl;
	return code;
}

string VectorCompiler::generateCode(Tree sig)
{
    generateCodeRecursions(sig);
    return generateCodeNonRec(sig);
}

void VectorCompiler::generateCodeRecursions(Tree sig)
{
    Tree    id, body;
    string  code;
    //cerr << "VectorCompiler::generateCodeRecursions( " << ppsig(sig) << " )" << endl;
    if (getCompiledExpression(sig, code)) {
        //cerr << "** ALREADY VISITED : " << code << " ===> " << ppsig(sig) << endl;
        return;
    } else if( isRec(sig, id, body) ) {
        //cerr << "we have a recursive expression non compiled yet : " << ppsig(sig) << endl;
        setCompiledExpression(sig, "[RecursionVisited]");
        fClass->openLoop(sig, "count");
        generateRec(sig, id, body);
        fClass->closeLoop(sig);
    } else {
        // we go down the expression
        vector<Tree>  subsigs;
        int n = getSubSignals(sig, subsigs, false);
        for (int i=0; i<n; i++) { generateCodeRecursions(subsigs[i]); }
    }
}

string VectorCompiler::generateCodeNonRec(Tree sig)
{
    string  code;
    if (getCompiledExpression(sig, code)) {
        // already visited
        return code;
    } else {
        //cerr << "VectorCompiler::generateCodeNonRec( " << ppsig(sig) << " )" << endl;
        code = generateLoopCode(sig);
        setCompiledExpression(sig, code);
        return code;
    }
}

/**
 * Compile a signal
 * @param sig the signal expression to compile.
 * @return the C code translation of sig as a string
 */
string VectorCompiler::generateLoopCode(Tree sig)
{
    int     i;
    Tree    x;
    Loop*   l;

    l = fClass->topLoop();
    faustassert(l);
    //cerr << "VectorCompiler::OLDgenerateCode " << ppsig(sig) << endl;
    if (needSeparateLoop(sig)) {
        // we need a separate loop unless it's an old recursion
        if (isProj(sig, &i, x)) {
            // projection of a recursive group x
            if (l->hasRecDependencyIn(singleton(x))) {
                // x is already in the loop stack
                return ScalarCompiler::generateCode(sig);
            } else {
                // x must be defined
                fClass->openLoop(x, "count");
                string c = ScalarCompiler::generateCode(sig);
                fClass->closeLoop(sig);
                return c;
            }
        } else {
            fClass->openLoop("count");
            string c = ScalarCompiler::generateCode(sig);
            fClass->closeLoop(sig);
            return c;
        }
    } else {
        return ScalarCompiler::generateCode(sig);
    }
}

/**
 * Generate cache code for a signal if needed
 * @param sig the signal expression.
 * @param exp the corresponding C code.
 * @return the cached C code
 */
string VectorCompiler::generateCacheCode(Tree sig, const string& exp)
{
    string      vname, ctype;
    int         sharing = getSharingCount(sig);
    Type        t = getCertifiedSigType(sig);
    old_Occurences* o = fOccMarkup->retrieve(sig);
    int         d = o->getMaxDelay();

    if (t->variability() < kSamp) {
        if (d == 0) {
            // non-sample, not delayed : same as scalar cache
            return ScalarCompiler::generateCacheCode(sig,exp);

        } else {
            // it is a non-sample expressions but used delayed
            // we need a delay line
			getTypedNames(getCertifiedSigType(sig), "Vec", ctype, vname);
            if ((sharing > 1) && !verySimple(sig)) {
                // first cache this expression because it
                // it is shared and complex
                string cachedexp =  generateVariableStore(sig, exp);
                generateDelayLine(ctype, vname, d, cachedexp, getConditionCode(sig));
                setVectorNameProperty(sig, vname);
                return cachedexp;
            } else {
                // no need to cache this expression because
                // it is either not shared or very simple
                generateDelayLine(ctype, vname, d, exp, getConditionCode(sig));
                setVectorNameProperty(sig, vname);
                return exp;
            }
        }
    } else {
        // sample-rate signal
        if (d > 0) {
            // used delayed : we need a delay line
            getTypedNames(getCertifiedSigType(sig), "Yec", ctype, vname);
            generateDelayLine(ctype, vname, d, exp, getConditionCode(sig));
            setVectorNameProperty(sig, vname);

            if (verySimple(sig)) {
                return exp;
            } else {
                if (d < gGlobal->gMaxCopyDelay) {
                    return subst("$0[i]", vname);
                } else {
                    // we use a ring buffer
                    string mask = T(pow2limit(d + gGlobal->gVecSize)-1);
                    return subst("$0[($0_idx+i) & $1]", vname, mask);
                }
            }
        } else {
            // not delayed
            if (sharing > 1 && !verySimple(sig)) {
                // shared and not simple : we need a vector
                // cerr << "ZEC : " << ppsig(sig) << endl;
                getTypedNames(getCertifiedSigType(sig), "Zec", ctype, vname);
                generateDelayLine(ctype, vname, d, exp, getConditionCode(sig));
                setVectorNameProperty(sig, vname);
                return subst("$0[i]", vname);
           } else {
                // not shared or simple : no cache needed
                return exp;
            }
        }
    }
}

/**
 * Test if a signal need to be compiled in a separate loop.
 * @param sig the signal expression to test.
 * @return true if a separate loop is needed
 */
bool VectorCompiler::needSeparateLoop(Tree sig)
{
    old_Occurences* o = fOccMarkup->retrieve(sig);
    Type        t = getCertifiedSigType(sig);
    int         c = getSharingCount(sig);
    bool        b;

    int         i;
    Tree        x,y;

    if (o->getMaxDelay() > 0) {
        //cerr << "DLY "; // delayed expressions require a separate loop
        b = true;
    } else if (verySimple(sig) || t->variability()<kSamp) {
        b = false;      // non sample computation never require a loop
    } else if (isSigFixDelay(sig, x, y)) {
        b = false;      //
    } else if (isProj(sig, &i, x)) {
        //cerr << "REC "; // recursive expressions require a separate loop
        b = true;
    } else if (c > 1) {
        //cerr << "SHA(" << c << ") "; // expressions used several times required a separate loop
        b = true;
    } else {
        // sample expressions that are not recursive, not delayed
        // and not shared, doesn't require a separate loop.
        b = false;
    }
/*    if (b) {
        cerr << "Separate Loop for " << ppsig(sig) << endl;
    } else {
        cerr << "Same Loop for " << ppsig(sig) << endl;
    }*/
    return b;
}

void VectorCompiler::generateDelayLine(const string& ctype, const string& vname, int mxd, const string& exp, const string& ccs)
{
    if (mxd == 0) {
        vectorLoop(ctype, vname, exp, ccs);
    } else {
        dlineLoop(ctype, vname, mxd, exp, ccs);
    }
}

string VectorCompiler::generateVariableStore(Tree sig, const string& exp)
{
    Type t = getCertifiedSigType(sig);

    if (getCertifiedSigType(sig)->variability() == kSamp) {
        string      vname, ctype;
        getTypedNames(t, "Vector", ctype, vname);
        vectorLoop(ctype, vname, exp, getConditionCode(sig));
        return subst("$0[i]", vname);
    } else {
        return ScalarCompiler::generateVariableStore(sig, exp);
    }
}

/**
 * Generate code for accessing a delayed signal. The generated code depend of
 * the maximum delay attached to exp and the gLessTempSwitch.
 */

string VectorCompiler::generateFixDelay(Tree sig, Tree exp, Tree delay)
{
    int mxd, d;
    string vecname;

    //cerr << "VectorCompiler::generateFixDelay " << ppsig(sig) << endl;

    string code = CS(exp); // ensure exp is compiled to have a vector name

    mxd = fOccMarkup->retrieve(exp)->getMaxDelay();

    if (! getVectorNameProperty(exp, vecname)) {
        if (mxd == 0) {
            //cerr << "it is a pure zero delay : " << code << endl;
            return code;
        } else {
            cerr << "No vector name for : " << ppsig(exp) << endl;
            faustassert(0);
        }
    }

    if (mxd == 0) {
        // not a real vector name but a scalar name
        return subst("$0[i]", vecname);

    } else if (mxd < gGlobal->gMaxCopyDelay){
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
        int N = pow2limit(mxd + gGlobal->gVecSize);

        if (isSigInt(delay, &d)) {
            if (d == 0) {
                return subst("$0[($0_idx+i)&$1]", vecname, T(N-1));
            } else {
                return subst("$0[($0_idx+i-$2)&$1]", vecname, T(N-1), T(d));
            }
        } else {
            return subst("$0[($0_idx+i-$2)&$1]", vecname, T(N-1), CS(delay));
        }
    }
}

/**
 * Generate code for the delay mecchanism. The generated code depend of the
 * maximum delay attached to exp and the "less temporaries" switch
 */

string VectorCompiler::generateDelayVec(Tree sig, const string& exp, const string& ctype, const string& vname, int mxd)
{
    // it is a non-sample but used delayed
    // we need a delay line
    generateDelayLine(ctype, vname, mxd, exp, getConditionCode(sig));
    setVectorNameProperty(sig, vname);
    if (verySimple(sig)) {
        return exp;
    } else {
        return subst("$0[i]", vname);
    }
}

#if 0
static int pow2limit(int x)
{
    int n = 2;
    while (n < x) { n = 2*n; }
    return n;
}
#endif

/**
 * Generate the code for a (short) delay line
 * @param k the c++ class where the delay line will be placed.
 * @param l the loop where the code will be placed.
 * @param tname the name of the C++ type (float or int)
 * @param dlname the name of the delay line (vector) to be used.
 * @param delay the maximum delay
 * @param cexp the content of the signal as a C++ expression
 */
void  VectorCompiler::vectorLoop(const string& tname, const string& vecname, const string& cexp, const string& ccs)
{
    // -- declare the vector
    fClass->addSharedDecl(vecname);

    // -- variables moved as class fields...
    fClass->addZone1(subst("$0 \t$1[$2];", tname, vecname, T(gGlobal->gVecSize)));

    // -- compute the new samples
    fClass->addExecCode(Statement(ccs, subst("$0[i] = $1;", vecname, cexp)));
}

/**
 * Generate the code for a (short) delay line
 * @param k the c++ class where the delay line will be placed.
 * @param l the loop where the code will be placed.
 * @param tname the name of the C++ type (float or int)
 * @param dlname the name of the delay line (vector) to be used.
 * @param delay the maximum delay
 * @param cexp the content of the signal as a C++ expression
 */
void  VectorCompiler::dlineLoop(const string& tname, const string& dlname, int delay, const string& cexp, const string& ccs)
{
    if (delay < gGlobal->gMaxCopyDelay) {

        // Implementation of a copy based delayline

	    // create names for temporary and permanent storage
	    string  buf = subst("$0_tmp", dlname);
        string  pmem= subst("$0_perm", dlname);

        // constraints delay size to be multiple of 4
        delay = (delay+3)&-4;

        // allocate permanent storage for delayed samples
        string  dsize   = T(delay);
        fClass->addDeclCode(subst("$0 \t$1[$2];", tname, pmem, dsize));

        // init permanent memory
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i]=0;", pmem, dsize));

        // compute method

        // -- declare a buffer and a "shifted" vector
        fClass->addSharedDecl(buf);

        // -- variables moved as class fields...
        fClass->addZone1(subst("$0 \t$1[$2+$3];", tname, buf, T(gGlobal->gVecSize), dsize));

        fClass->addFirstPrivateDecl(dlname);
        fClass->addZone2(subst("$0* \t$1 = &$2[$3];", tname, dlname, buf, dsize));

        // -- copy the stored samples to the delay line
        fClass->addPreCode(Statement(ccs, subst("for (int i=0; i<$2; i++) $0[i]=$1[i];", buf, pmem, dsize)));

        // -- compute the new samples
        fClass->addExecCode(Statement(ccs, subst("$0[i] = $1;", dlname, cexp)));

        // -- copy back to stored samples
        fClass->addPostCode(Statement(ccs, subst("for (int i=0; i<$2; i++) $0[i]=$1[count+i];", pmem, buf, dsize)));

    } else {

        // Implementation of a ring-buffer delayline

        // the size should be large enough and aligned on a power of two
        delay   = pow2limit(delay + gGlobal->gVecSize);
        string  dsize   = T(delay);
        string  mask    = T(delay-1);

        // create names for temporary and permanent storage
        string  idx = subst("$0_idx", dlname);
        string  idx_save = subst("$0_idx_save", dlname);

        // allocate permanent storage for delayed samples
        fClass->addDeclCode(subst("$0 \t$1[$2];", tname, dlname, dsize));
        fClass->addDeclCode(subst("int \t$0;", idx));
        fClass->addDeclCode(subst("int \t$0;", idx_save));

        // init permanent memory
        fClass->addClearCode(subst("for (int i=0; i<$1; i++) $0[i]=0;", dlname, dsize));
        fClass->addClearCode(subst("$0 = 0;", idx));
        fClass->addClearCode(subst("$0 = 0;", idx_save));

        // -- update index
        fClass->addPreCode(Statement(ccs, subst("$0 = ($0+$1)&$2;", idx, idx_save, mask)));

        // -- compute the new samples
        fClass->addExecCode(Statement(ccs, subst("$0[($2+i)&$3] = $1;", dlname, cexp, idx, mask)));

        // -- save index
        fClass->addPostCode(Statement(ccs, subst("$0 = count;", idx_save)));
    }
}

string VectorCompiler::generateWaveform(Tree sig)
{
    string  vname;
    int     size;

    declareWaveform(sig, vname, size);
    fClass->addPostCode(Statement(getConditionCode(sig), subst("idx$0 = (idx$0 + count) % $1;", vname, T(size))));
    return generateCacheCode(sig, subst("$0[(idx$0+i)%$1]", vname, T(size)));
}
