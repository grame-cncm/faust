/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "exception.hh"
#include "global.hh"
#include "interval_def.hh"
#include "ppsig.hh"
#include "prim2.hh"
#include "recursiveness.hh"
#include "sigFIR.hh"
#include "sigIIR.hh"
#include "signals.hh"
#include "sigprint.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "xtended.hh"

using namespace std;

/*
 Signal typing system is built not doing any assumption about the signal tree,
 like being already 'typed' using kInt/kReal types and with sigInt/sigFloat
 operations at the right places.
 The typeAnnotation/inferSigType functions thus analyze each node and possibly
 use floatCast, intCast, boolCast when appropriate.
 */

//--------------------------------------------------------------------------
// prototypes
//--------------------------------------------------------------------------

static TupletType* initialRecType(Tree t);
static TupletType* maximalRecType(Tree t);

static Type T(Tree term, Tree env);

static Type inferSigType(Tree sig, Tree env);
static Type inferFFType(Tree ff, Tree ls, Tree env);
static Type inferFConstType(Tree type);
static Type inferFVarType(Tree type);
static Type inferRecType(Tree var, Tree body, Tree env);
static Type inferTableType(Tree size, Tree gen, Tree env);
static Type inferReadTableType(Type tbl, Type ri);
static Type inferWriteTableType(Type tbl, Type wi, Type ws);
static Type inferProjType(Type t, int i, int vec);
static Type inferXType(Tree sig, Tree env);
static Type inferDocConstantTblType(Type size, Type init);
static Type inferDocWriteTblType(Type size, Type init, Type widx, Type wsig);
static Type inferDocAccessTblType(Type tbl, Type ridx);
static Type inferWaveformType(Tree lv, Tree env);
static Type inferFIRType(Tree sig, Tree env);
static Type inferIIRType(Tree sig, Tree env);

/**
 * Convert a constant signal into a double using its bounds (not very safe).
 *
 * @param sig the signal to be converted
 * @return the mean of its biggest and smallest value
 */
static double constSig2double(Tree sig)
{
    Type ty = getSigType(sig);
    if (ty->variability() != kKonst) {
        throw faustexception("ERROR : constSig2double, must a constant numerical expression\n");
    }
    interval bds = ty->getInterval();
    if (bds.lo() != bds.hi()) {
        throw faustexception(
            "ERROR : constSig2double, constant value with non-singleton interval, don't know what"
            " to do, please report");
    }
    return bds.lo();
}

/**
 * Dereference a Type to AudioType and promote its type to TupletType.
 * if the AudioType is not a TupletType, then fails.
 *
 * @param t the type to promote
 * @return the *t as a TupletType
 */
static ::TupletType derefRecCert(Type t)
{
    TupletType* p = isTupletType(t);
    faustassert(p);
    return *p;
}

/**
 * Compute the resulting interval of an arithmetic operation.
 *
 * @param op code of the operation
 * @param s1 interval of the left operand
 * @param s2 interval of the right operand
 * @return the resulting interval
 */
static interval arithmetic(int opcode, const interval& x, const interval& y)
{
    switch (opcode) {
        case kAdd:
            return x + y;
        case kSub:
            return x - y;
        case kMul:
            return x * y;
        case kDiv:
            return x / y;
        case kRem:
            return x % y;
        case kLsh:
            return x << y;
        case kARsh:
            return x >> y;
        case kGT:
            return gAlgebra.Gt(x, y);
        case kLT:
            return gAlgebra.Lt(x, y);
        case kGE:
            return gAlgebra.Ge(x, y);
        case kLE:
            return gAlgebra.Le(x, y);
        case kEQ:
            return gAlgebra.Eq(x, y);
        case kNE:
            return gAlgebra.Ne(x, y);
        case kAND:
            return x & y;
        case kOR:
            return x | y;
        case kXOR:
            return x ^ y;
        default:
            cerr << "ASSERT : unrecognized opcode : " << opcode << endl;
            faustassert(false);
            return itv::empty();
    }

    return itv::empty();
}

// Uncomment to activate type inferrence tracing
#define TRACE(x)
static bool gTrace = false;  ///< global trace flag
// #define TRACE(x)  \
//     if (gTrace) { \
//         x;        \
//     }

/**
 * Verify the coherence of recursive signal types.
 * Check that when a recursive group is assigned a tuplet type T0×T1×T2×...,
 * the individual signals S0, S1, S2, ... in the group have the corresponding types T0, T1, T2, ...
 * Also verify that projections proj0(recSig), proj1(recSig), etc. are coherent
 *
 * @param recSig the recursive signal (Tree representing the recursive group)
 * @param defList the definition list of signals in the recursive group
 * @param expectedTupletType the expected tuplet type assigned to the group
 * @param groupIndex index of the group (for error reporting)
 * @return true if all checks pass, false if errors were found
 */
static bool checkRecType(Tree recSig, Tree defList, Type expectedTupletType, int groupIndex)
{
    bool hasErrors = false;

    // Extract recursive symbol name for better error reporting
    Tree   var, body;
    string recSymbol = "unknown";
    if (isRec(recSig, var, body)) {
        stringstream ss;
        ss << *var;
        recSymbol = ss.str();
    }

    TupletType* tupletType = isTupletType(expectedTupletType);
    faustassert(tupletType != nullptr);  // expectedTupletType must be a tuplet type

    int signalIndex = 0;
    for (Tree l = defList; isList(l); l = tl(l), signalIndex++) {
        Tree individualSignal = hd(l);

        // Check that the individual signal has a type
        Type actualType = getCertifiedSigType(individualSignal);  // Will assert if no type

        // Check that the signal index is within bounds
        faustassert(signalIndex <
                    tupletType->arity());  // Signal index must be within tuplet bounds

        // Get expected type from tuplet
        Type expectedType = (*tupletType)[signalIndex];

        // Check type equality
        if (actualType != expectedType) {
            cerr << "WARNING : checkRecType, type mismatch for signal " << signalIndex
                 << " in recursive symbol " << recSymbol << " (group " << groupIndex << ")" << endl
                 << "        Expected type: " << *expectedType << endl
                 << "        Actual type:   " << *actualType << endl
                 << "        Signal: " << ppsig(individualSignal, MAX_ERROR_SIZE) << endl;
            hasErrors = true;
        }
    }

    // Verify that we have the expected number of signals
    faustassert(signalIndex == tupletType->arity());  // Exact arity match required

    // Verify that the body of the recursive signal matches the definition list
    faustassert(isRec(recSig, var, body));  // recSig must be a recursive signal
    faustassert(body == defList);           // body must match defList exactly

    // Verify that used projections have correct types (unused projections may not have types)
    for (int projIndex = 0; projIndex < tupletType->arity(); projIndex++) {
        Tree projection = sigProj(projIndex, recSig);
        Type projType   = getSigType(projection);

        if (projType) {
            // Only check type coherence for projections that have been typed (i.e., used)
            Type expectedProjType = (*tupletType)[projIndex];
            if (projType != expectedProjType) {
                cerr << "WARNING : checkRecType, projection type mismatch for proj" << projIndex
                     << "(" << recSymbol << ") in group " << groupIndex << endl
                     << "        Expected type: " << *expectedProjType << endl
                     << "        Projection type: " << *projType << endl;
                hasErrors = true;
            }
        }
        // Note: Projections without types are assumed to be unused, which is normal
    }

    return !hasErrors;
}

/**
 * Do one step of type inference on the recursive signal groups of a signal
 * The types of the recursive signals are updated to vtype and then vtype is updated to the next
 * step.
 *
 * @param vrec array of all the recursive signal groups
 * @param vdef definitions of all the recursive signal groups (vector of _lists_)
 * @param vdefSizes number of signals in each recursive signal groups
 * @param vtype types of the recursive signals
 * @param inter if set to false, the interval of the new type is the union of the old one and the
 * computed one, otherwise it is the intersection
 */
static void updateRecTypes(const vector<Tree>& vrec, const vector<Tree>& vdef,
                           const vector<int>& vdefSizes, vector<Type>& vtype, const bool inter)
{
    const int numRecGroups = vdef.size();

    CTree::startNewVisit();

    // init recursive types
    for (int g = 0; g < numRecGroups; g++) {
        setSigType(vrec[g], vtype[g]);
        // std::cerr << gGlobal->TABBER << "set type for " << *vrec[g] << " to " << *vtype[g]
        //           << std::endl;
        vrec[g]->setVisited();
    }

    // cerr << "compute recursive types" << endl;
    for (int g = 0; g < numRecGroups; g++) {
        // std::cerr << gGlobal->TABBER << "computing type for " << *vrec[i] << std::endl;
        TupletType oldRecType = derefRecCert(getSigType(vrec[g]));
        TupletType newRecType = derefRecCert(T(vdef[g], gGlobal->NULLTYPEENV));

        vector<Type> newTuplet;
        for (int j = 0; j < vdefSizes[g]; j++) {
            newTuplet.push_back(newRecType[j]);
            interval newI = newRecType[j]->getInterval();
            interval oldI = oldRecType[j]->getInterval();

            newI         = inter ? intersection(newI, oldI) : itv::reunion(newI, oldI);
            newTuplet[j] = newTuplet[j]->promoteInterval(newI);
        }
        vtype[g] = new TupletType(newTuplet);
    }
}

/**
 * Fully annotate every subtree of term with type information.
 * @param sig the signal term tree to annotate
 * @param causality when true check causality issues
 */
void typeAnnotation(Tree sig, bool causality)
{
    gGlobal->gCausality    = causality;
    Tree      recGroupList = symlist(sig);
    const int numRecGroups = len(recGroupList);

    // std::cerr << "*****SYMLIST : " << *recGroupList << std::endl;

    // Parse recursive signal groups
    vector<Tree> vrec;       ///< array of all the recursive signal groups
    vector<Tree> vdef;       ///< definitions of all the recursive signal groups (vector of _lists_)
    vector<int>  vdefSizes;  ///< number of signals for each group
    vector<vector<int>> vAgeMin;  ///< age of the minimum of every subsignal of the recursive signal
    vector<vector<int>> vAgeMax;  ///< age of the maximum of every subsignal of the recursive signal

    // cerr << "Symlist " << *recGroupList << endl;
    for (Tree l = recGroupList; isList(l); l = tl(l)) {
        Tree id, body;
        faustassert(isRec(hd(l), id, body));
        // if (!isRec(hd(l), id, body)) {
        //     continue;
        // }
        vrec.push_back(hd(l));
        vdef.push_back(body);

        int size = len(body);
        vdefSizes.push_back(size);
        vAgeMin.push_back(vector<int>(size, 0));
        vAgeMax.push_back(vector<int>(size, 0));
    }

    // Initialize recursive types
    vector<Type> vtype;    ///< type of the recursive signals
    vector<Type> vtypeUp;  ///< an upperbound of the recursive signals type

    for (int i = 0; i < numRecGroups; i++) {
        vtypeUp.push_back(maximalRecType(vdef[i]));
        vtype.push_back(initialRecType(vdef[i]));
    }

    faustassert(int(vrec.size()) == numRecGroups);
    faustassert(int(vdef.size()) == numRecGroups);
    faustassert(int(vtype.size()) == numRecGroups);
    faustassert((int)vAgeMin.size() == numRecGroups);
    faustassert((int)vAgeMax.size() == numRecGroups);

    // cerr << "compute upper bounds for recursive types" << endl;
    for (int k = 0; k < gGlobal->gNarrowingLimit; k++) {
        updateRecTypes(vrec, vdef, vdefSizes, vtypeUp, true);
    }

    vector<TupletType> vUp;  ///< the unfolded version of the variable above
    for (const auto& ty : vtypeUp) {
        vUp.push_back(derefRecCert(ty));
    }

    // cerr << "find an upperbound of the least fixpoint" << endl;
    bool finished = false;
    while (!finished) {
        updateRecTypes(vrec, vdef, vdefSizes, vtype, false);

        // check finished
        finished = true;

        // for each recursive group of index g
        for (int g = 0; g < numRecGroups; g++) {
            // cerr << i << "-" << *vrec[i] << ":" << *getSigType(vrec[i]) << " => " << *vtype[i] <<
            // endl;
            // if (vtype[g] == getSigType(vrec[g])) {
            //     cerr << *vrec[g] << " = " << vdef[g] << "; has converged" << endl;
            //     continue;  // already converged
            // }
            if (vtype[g] != getSigType(vrec[g])) {
                finished = false;

                vector<Type> newTuplet;
                TupletType   newRecType = derefRecCert(vtype[g]);
                TupletType   oldRecType = derefRecCert(getSigType(vrec[g]));

                // for each projection p of recursive group g
                for (int p = 0; p < vdefSizes[g]; p++) {
                    newTuplet.push_back(newRecType[p]);
                    interval newI = newRecType[p]->getInterval();
                    interval oldI = oldRecType[p]->getInterval();

                    TRACE(cerr << gGlobal->TABBER << "inspecting " << newTuplet[p] << endl;)
                    if (newI.lo() != oldI.lo()) {
                        faustassert(newI.lo() < oldI.lo());
                        vAgeMin[g][p]++;
                        if (vAgeMin[g][p] > gGlobal->gWideningLimit) {
                            TRACE(cerr << gGlobal->TABBER << "low widening of " << newTuplet[p]
                                       << endl;)
                            newI = {vUp[g][p]->getInterval().lo(), newI.hi()};
                        }
                    }

                    if (newI.hi() != oldI.hi()) {
                        faustassert(newI.hi() > oldI.hi());
                        vAgeMax[g][p]++;
                        if (vAgeMax[g][p] > gGlobal->gWideningLimit) {
                            TRACE(cerr << gGlobal->TABBER << "up widening of " << newTuplet[p]
                                       << endl;)
                            newI = {newI.lo(), vUp[g][p]->getInterval().hi()};
                        }
                    }

                    newTuplet[p] = newTuplet[p]->promoteInterval(newI);
                    TRACE(cerr << gGlobal->TABBER << "widening ended : " << newTuplet[p] << endl;)
                }
                vtype[g] = new TupletType(newTuplet);
            }
        }
    }

    // verify coherence of recursive types after convergence
    // cerr << "Verifying type coherence after convergence..." << endl;
    // bool allCoherent = true;
    // for (int i = 0; i < numRecGroups; i++) {
    //     bool isCoherent = checkRecType(vrec[i], vdef[i], vtype[i], i);
    //     if (!isCoherent) {
    //         cerr << "WARNING : Type coherence issues detected in recursive group " << i
    //              << " after convergence" << endl;
    //         allCoherent = false;
    //     }
    // }
    // if (allCoherent) {
    //     cerr << "Type coherence verification: OK" << endl;
    // }

    // type full term
    T(sig, gGlobal->NULLTYPEENV);
    TRACE(cerr << "type success : " << endl << "BYE" << endl;)
}

/**
 * Print annotation statistics.
 */
static void annotationStatistics()
{
    cerr << gGlobal->TABBER << "COUNT INFERENCE  " << gGlobal->gCountInferences << " AT TIME "
         << clock() / CLOCKS_PER_SEC << 's' << endl;
    cerr << gGlobal->TABBER << "COUNT ALLOCATION " << gGlobal->gAllocationCount << endl;
    cerr << gGlobal->TABBER << "COUNT MAXIMAL " << gGlobal->gCountMaximal << endl;
}

/**
 * Retrieve the type of sig and check it exists. Produces an
 * error if the signal has no type associated
 * @param sig the signal we want to know the type
 * @return the type of the signal
 */
::Type getCertifiedSigType(Tree sig)
{
    Type ty = getSigType(sig);
    if (!ty) {
        std::cerr << "ERROR: getCertifiedSigType called on signal WITHOUT type!" << std::endl;
        std::cerr << "  Signal ptr: " << sig << std::endl;

        // Try to identify the signal type
        int  i;
        Tree x;
        if (isProj(sig, &i, x)) {
            std::cerr << "  Signal is proj(" << i << ", ...)" << std::endl;
            std::cerr << "  Projection source ptr: " << x << std::endl;
            Type xType = getSigType(x);
            std::cerr << "  Projection source has type? " << (xType ? "YES" : "NO") << std::endl;
        } else if (isList(sig)) {
            std::cerr << " NO type for list " << ppsig(sig) << std::endl;
        } else {
            std::cerr << " NO type for signal " << ppsig(sig) << std::endl;
        }
    }
    faustassert(ty);
    return ty;
}

/***********************************************
 * Set and get the type property of a signal
 * (we suppose the signal have been previously
 * annotated with type information)
 ***********************************************/

/**
 * Set the type annotation of sig
 * @param sig the signal we want to type
 * @param t the type of the signal
 */
void setSigType(Tree sig, Type t)
{
    TRACE(cerr << gGlobal->TABBER << "SET FIX TYPE OF " << ppsig(sig, MAX_ERROR_SIZE) << " TO TYPE "
               << *t << endl;)
    sig->setType(t);
}

/**
 * Retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
Type getSigType(Tree sig)
{
    AudioType* ty = (AudioType*)sig->getType();
    if (ty == nullptr) {
        TRACE(cerr << gGlobal->TABBER << "GET FIX TYPE OF " << ppsig(sig, MAX_ERROR_SIZE)
                   << " HAS NO TYPE YET" << endl;)
    } else {
        TRACE(cerr << gGlobal->TABBER << "GET FIX TYPE OF " << ppsig(sig, MAX_ERROR_SIZE)
                   << " IS TYPE " << *ty << endl;)
    }
    return ty;
}

/**************************************************************************

                        Type Inference System

***************************************************************************/

/**************************************************************************

                        Inferred Type property

***************************************************************************/

/**
 * Shortcut to getOrInferType, retrieve or infer the type of a term according to its surrounding
 * type environment
 * @param sig the signal to analyze
 * @param env the type environment
 * @return the type of sig according to environment env
 * @see getCertifiedSigType
 */
static Type T(Tree term, Tree ignoreenv)
{
    TRACE(cerr << ++gGlobal->TABBER << "ENTER T() " << ppsig(term, MAX_ERROR_SIZE) << endl;)

    if (term->isAlreadyVisited()) {
        Type ty = getSigType(term);
        TRACE(cerr << --gGlobal->TABBER << "EXIT 1 T() " << ppsig(term, MAX_ERROR_SIZE)
                   << " AS TYPE " << *ty << endl);
        return ty;

    } else {
        Type ty = inferSigType(term, ignoreenv);
        setSigType(term, ty);
        term->setVisited();
        TRACE(cerr << --gGlobal->TABBER << "EXIT 2 T() " << ppsig(term, MAX_ERROR_SIZE)
                   << " AS TYPE " << *ty << endl);
        return ty;
    }
}

static void checkPartInterval(Tree s, Type t)
{
    interval i = t->getInterval();
    if (!i.isValid() || (i.lo() < 0) || (i.hi() >= MAX_SOUNDFILE_PARTS)) {
        stringstream error;
        error << "ERROR : out of range soundfile part number (" << i << " instead of interval(0,"
              << MAX_SOUNDFILE_PARTS - 1 << ")) in expression : " << ppsig(s, MAX_ERROR_SIZE)
              << endl;
        throw faustexception(error.str());
    }
}

/**
 * Infer the type of a term according to its surrounding type environment
 * @param sig the signal to analyse
 * @param env the type environment
 * @return the type of sig according to environment env
 */
static Type inferSigType(Tree sig, Tree env)
{
    gGlobal->gCountInferences++;

    if (getUserData(sig)) {
        return inferXType(sig, env);
    }

    if (int i; isSigInt(sig, &i)) {
        Type t = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, gAlgebra.IntNum(i));
        return t;
    }

    if (int64_t i64; isSigInt64(sig, &i64)) {
        Type t = makeSimpleType(kInt, kKonst, kComp, kVect, kNum, gAlgebra.Int64Num(i64));
        return t;
    }

    if (double r; isSigReal(sig, &r)) {
        Type t = makeSimpleType(kReal, kKonst, kComp, kVect, kNum, gAlgebra.FloatNum(r));
        return t;
    }

    if (isSigWaveform(sig)) {
        return inferWaveformType(sig, env);
    }

    if (int i; isSigInput(sig, &i)) {
        return gGlobal->TINPUT;
    }

    {
        int chan;
        if (Tree s1; isSigOutput(sig, &chan, s1)) {
            return sampCast(T(s1, env));
        }
    }

    if (Tree s1; isSigDelay1(sig, s1)) {
        Type t = T(s1, env);
        return castInterval(sampCast(t), itv::reunion(t->getInterval(), interval(0)));
    }

    if (Tree s1, s2; isSigPrefix(sig, s1, s2)) {
        Type t1 = T(s1, env);
        Type t2 = T(s2, env);
        checkInit(t1);
        return castInterval(sampCast(t1 | t2), itv::reunion(t1->getInterval(), t2->getInterval()));
    }

    if (Tree s1, s2; isSigDelay(sig, s1, s2)) {
        Type     t1 = T(s1, env);
        Type     t2 = T(s2, env);
        interval i1 = t2->getInterval();

        // cerr << "for sig fix delay : s1 = "
        //      << t1 << ':' << ppsig(s1) << ", s2 = "
        //      << t2 << ':' << ppsig(s2) << endl;
        if (gGlobal->gCausality) {
            if (!(i1.isValid()) || !(i1.isBounded())) {
                stringstream error, st1, st2;
                // Prepare two separated streams for MAX_ERROR_SIZE model to work properly
                st1 << ppsig(s1, MAX_ERROR_SIZE);
                st2 << ppsig(s2, MAX_ERROR_SIZE);
                error << "ERROR : can't compute the min and max values of : " << st2.str() << endl
                      << "        used in delay expression : " << st1.str() << endl
                      << "        (probably a recursive signal)" << endl;
                throw faustexception(error.str());
            } else if (i1.lo() < 0) {
                stringstream error, st1, st2;
                // Prepare two separated streams for MAX_ERROR_SIZE model to work properly
                st1 << ppsig(s1, MAX_ERROR_SIZE);
                st2 << ppsig(s2, MAX_ERROR_SIZE);
                error << "ERROR : possible negative values of : " << st2.str() << endl
                      << "        used in delay expression : " << st1.str() << endl
                      << "        " << i1 << endl;
                throw faustexception(error.str());
            }
        }

        return castInterval(sampCast(t1), itv::reunion(t1->getInterval(), interval(0)));
    }

    {
        int op;
        if (Tree s1, s2; isSigBinOp(sig, &op, s1, s2)) {
            Type t1 = T(s1, env);
            Type t2 = T(s2, env);
            Type t3 = castInterval(t1 | t2, arithmetic(op, t1->getInterval(), t2->getInterval()));

            if (op == kDiv) {
                return floatCast(t3);  // division always result in a float even with int arguments
            } else if ((op >= kGT) && (op <= kNE)) {
                return boolCast(t3);  // comparison always result in a boolean int
            } else if (((op >= kLsh) && (op <= kLRsh)) || ((op >= kAND) && (op <= kXOR))) {
                return intCast(t3);  // boolean and logical operators always result in an int
            } else {
                return t3;  //  otherwise most general of t1 and t2
            }
        }
    }

    if (Tree s1; isSigIntCast(sig, s1)) {
        return intCast(T(s1, env));
    }

    if (Tree s1; isSigBitCast(sig, s1)) {
        return bitCast(T(s1, env));
    }

    if (Tree s1; isSigFloatCast(sig, s1)) {
        return floatCast(T(s1, env));
    }

    if (Tree ff, ls; isSigFFun(sig, ff, ls)) {
        return inferFFType(ff, ls, env);
    }

    if (Tree type, name, file; isSigFConst(sig, type, name, file)) {
        return inferFConstType(type);
    }

    if (Tree type, name, file; isSigFVar(sig, type, name, file)) {
        return inferFVarType(type);
    }

    if (isSigButton(sig)) {
        return castInterval(gGlobal->TGUI,
                            gAlgebra.Button(interval(0)));  // TODO: replace the name
    }

    if (isSigCheckbox(sig)) {
        return castInterval(gGlobal->TGUI,
                            gAlgebra.Checkbox(interval(0)));  // TODO: replace the name
    }

    if (Tree label, cur, min, max, step; isSigVSlider(sig, label, cur, min, max, step)) {
        Type t1 = T(cur, env);
        Type t2 = T(min, env);
        Type t3 = T(max, env);
        Type t4 = T(step, env);
        return castInterval(gGlobal->TGUI, gAlgebra.VSlider(interval(0),  // TODO: replace the name
                                                            t1->getInterval(), t2->getInterval(),
                                                            t3->getInterval(), t4->getInterval()));
    }

    if (Tree label, cur, min, max, step; isSigHSlider(sig, label, cur, min, max, step)) {
        Type t1 = T(cur, env);
        Type t2 = T(min, env);
        Type t3 = T(max, env);
        Type t4 = T(step, env);
        return castInterval(gGlobal->TGUI, gAlgebra.HSlider(interval(0),  // TODO: replace the name
                                                            t1->getInterval(), t2->getInterval(),
                                                            t3->getInterval(), t4->getInterval()));
    }

    if (Tree label, cur, min, max, step; isSigNumEntry(sig, label, cur, min, max, step)) {
        Type t1 = T(cur, env);
        Type t2 = T(min, env);
        Type t3 = T(max, env);
        Type t4 = T(step, env);
        return castInterval(gGlobal->TGUI,
                            gAlgebra.NumEntry(interval(0),  // TODO: replace the name
                                              t1->getInterval(), t2->getInterval(),
                                              t3->getInterval(), t4->getInterval()));
    }

    if (Tree l, x, y, s1; isSigHBargraph(sig, l, x, y, s1)) {
        Type t1 = T(x, env);
        Type t2 = T(y, env);
        return T(s1, env)->promoteVariability(kBlock);
    }

    if (Tree l, x, y, s1; isSigVBargraph(sig, l, x, y, s1)) {
        Type t1 = T(x, env);
        Type t2 = T(y, env);
        return T(s1, env)->promoteVariability(kBlock);
    }

    if (Tree l; isSigSoundfile(sig, l)) {
        // computability should be kExec if the soundfile can be changed at runtime with the GUI
        // (which is not implemented yet), so kInit for now
        return makeSimpleType(kInt, kBlock, kInit, kVect, kNum, interval(0, INT32_MAX));
    }

    if (Tree sf, part; isSigSoundfileLength(sig, sf, part)) {
        Type t1 = T(sf, env);
        Type t2 = T(part, env);
        checkPartInterval(sig, t2);
        int c = std::max(int(kBlock), t2->variability());
        // computability should be kExec if the soundfile can be changed at runtime with the GUI
        // (which is not implemented yet), so kInit for now
        return makeSimpleType(kInt, c, kInit, kVect, kNum, interval(0, INT32_MAX));
    }

    if (Tree sf, part; isSigSoundfileRate(sig, sf, part)) {
        Type t1 = T(sf, env);
        Type t2 = T(part, env);
        checkPartInterval(sig, t2);
        int c = std::max(int(kBlock), t2->variability());
        // computability should be kExec if the soundfile can be changed at runtime with the GUI
        // (which is not implemented yet), so kInit for now
        return makeSimpleType(kInt, c, kInit, kVect, kNum, interval(0, INT32_MAX));
    }

    if (Tree sf, x, part, z; isSigSoundfileBuffer(sig, sf, x, part, z)) {
        T(sf, env);
        T(x, env);
        Type tp = T(part, env);
        T(z, env);
        checkPartInterval(sig, tp);
        // computability should be kExec if the soundfile can be changed at runtime with the GUI
        // (which is not implemented yet), so kInit for now
        return makeSimpleType(kReal, kSamp, kInit, kVect, kNum, interval(-1, 1));
    }

    if (Tree s1, s2; isSigAttach(sig, s1, s2)) {
        T(s2, env);
        return T(s1, env);
    }

    if (Tree s1, s2; isSigEnable(sig, s1, s2)) {
        T(s2, env);
        return T(s1, env);
    }

    if (Tree s1, s2; isSigControl(sig, s1, s2)) {
        T(s2, env);
        return T(s1, env);
    }

    if (Tree var, body; isRec(sig, var, body)) {
        return inferRecType(sig, body, env);
    }

    {
        int pnum;  // projection number
        if (Tree recgroup; isProj(sig, &pnum, recgroup)) {
            Tree var, body;
            isRec(recgroup, var, body);

            // std::stringstream ss;
            // ss << *var;
            // std::cerr << "the var is " << ss.str() << std::endl;
            // if (ss.str() == "WS6") {
            //     std::cerr << "the var is WS6, i = " << i << std::endl;
            //     gTrace = true;  // activate trace for this case
            // }

            return inferProjType(T(recgroup, env), pnum, kScal);
        }
    }

    if (Tree s1, s2, s3, s4; isSigWRTbl(sig, s1, s2, s3, s4)) {
        if (s3 == gGlobal->nil) {
            // rdtable
            return inferTableType(s1, s2, env);
        } else {
            // rwtable
            return inferWriteTableType(inferTableType(s1, s2, env), T(s3, env), T(s4, env));
        }
    }

    if (Tree s1, s2; isSigRDTbl(sig, s1, s2)) {
        return inferReadTableType(T(s1, env), T(s2, env));
    }

    if (Tree s1; isSigGen(sig, s1)) {
        return T(s1, gGlobal->NULLTYPEENV);
    }

    if (Tree x, y; isSigDocConstantTbl(sig, x, y)) {
        return inferDocConstantTblType(T(x, env), T(y, env));
    }
    if (Tree x, y, z, u; isSigDocWriteTbl(sig, x, y, z, u)) {
        return inferDocWriteTblType(T(x, env), T(y, env), T(z, env), T(u, env));
    }
    if (Tree x, y; isSigDocAccessTbl(sig, x, y)) {
        return inferDocAccessTblType(T(x, env), T(y, env));
    }

    if (Tree sel, s1, s2; isSigSelect2(sig, sel, s1, s2)) {
        SimpleType *st1, *st2, *stsel;

        st1   = isSimpleType(T(s1, env));
        st2   = isSimpleType(T(s2, env));
        stsel = isSimpleType(T(sel, env));

        return makeSimpleType(st1->nature() | st2->nature(),
                              st1->variability() | st2->variability() | stsel->variability(),
                              st1->computability() | st2->computability() | stsel->computability(),
                              st1->vectorability() | st2->vectorability() | stsel->vectorability(),
                              st1->boolean() | st2->boolean(),
                              itv::reunion(st1->getInterval(), st2->getInterval()));
    }

    if (isSigFIR(sig)) {
        return inferFIRType(sig, env);
    }

    if (isSigIIR(sig)) {
        return inferIIRType(sig, env);
    }

    if (tvec subs; isSigSum(sig, subs)) {
        faustassert(!subs.empty());
        Type t = T(subs[0], env);
        for (size_t ii = 1; ii < subs.size(); ii++) {
            Type u = T(subs[ii], env);
            t      = castInterval(t | u, arithmetic(kAdd, t->getInterval(), u->getInterval()));
        }
        return t;
    }

    // OnDemand types
    if (Tree x; isSigTempVar(sig, x)) {
        return T(x, env);
    }
    if (Tree x; isSigPermVar(sig, x)) {
        Type t1 = T(x, env);
        return castInterval(sampCast(t1), itv::reunion(t1->getInterval(), interval(0)));
    }
    if (Tree x, y; isSigZeroPad(sig, x, y)) {
        Type t1 = T(x, env);
        return castInterval(sampCast(t1), itv::reunion(t1->getInterval(), interval(0)));
    }
    if (Tree x, y; isSigSeq(sig, x, y)) {
        T(x, env);
        return T(y, env);
    }
    if (Tree h, y; isSigClocked(sig, h, y)) {
        return T(y, env);
    }
    if (tvec subs; isSigOD(sig, subs)) {
        // an OD block don't have a proper type,
        // but we need to type its subsignals
        for (size_t ii = 0; ii < subs.size(); ii++) {
            T(subs[ii], env);
        }
        // we lack a bottom type ! But is must NOT be a constant type, otherwise it will be
        // optimized by the constant propagation phase
        return makeSimpleType(kReal, kSamp, kExec, kScal, kNum, interval(-1, 1));
    }

    if (tvec subs; isSigUS(sig, subs)) {
        // an US block don't have a proper type,
        // but we need to type its subsignals
        for (size_t ii = 0; ii < subs.size(); ii++) {
            T(subs[ii], env);
        }
        // we lack a bottom type ! But is must NOT be a constant type, otherwise it will be
        // optimized by the constant propagation phase
        return makeSimpleType(kReal, kSamp, kExec, kScal, kNum, interval(-1, 1));
    }

    if (tvec subs; isSigDS(sig, subs)) {
        // an DS block don't have a proper type,
        // but we need to type its subsignals
        for (size_t ii = 0; ii < subs.size(); ii++) {
            T(subs[ii], env);
        }
        // we lack a bottom type ! But is must NOT be a constant type, otherwise it will be
        // optimized by the constant propagation phase
        return makeSimpleType(kReal, kSamp, kExec, kScal, kNum, interval(-1, 1));
    }

    if (isNil(sig)) {
        Type t = new TupletType();
        return t;
    }

    if (isList(sig)) {
        return T(hd(sig), env) * T(tl(sig), env);
    }

    if (Tree min, max, cur; isSigAssertBounds(sig, min, max, cur)) {
        Type     t1 = T(min, env);
        Type     t2 = T(max, env);
        Type     t3 = T(cur, env);
        interval i3 = t3->getInterval();
        interval iEnd(NAN, NAN);
        constSig2double(min);
        if (i3.isValid()) {
            iEnd = interval(std::max(i3.lo(), constSig2double(min)),
                            std::min(i3.hi(), constSig2double(max)));
        } else {
            iEnd = interval(constSig2double(min), constSig2double(max));
        }
        return t3->promoteInterval(iEnd);
    }

    if (Tree s1; isSigLowest(sig, s1)) {
        interval i1 = T(s1, env)->getInterval();
        return makeSimpleType(kReal, kKonst, kComp, kVect, kNum, interval(i1.lo()));
        // change this part   ^^^^^ once there are interval bounds depending on signal type
    }

    if (Tree s1; isSigHighest(sig, s1)) {
        interval i1 = T(s1, env)->getInterval();
        return makeSimpleType(kReal, kKonst, kComp, kVect, kNum, interval(i1.hi()));
        // change this part   ^^^^^ once there are interval bounds depending on signal type
    }

    {
        int i;
        if (Tree s1; isSigRegister(sig, &i, s1)) {
            return T(s1, env);
        }
    }

    // unrecognized signal here
    cerr << "ASSERT : when compiling, unrecognized signal : " << ppsig(sig, MAX_ERROR_SIZE) << endl;
    faustassert(false);
    return nullptr;
}

/**
 *	Infer the type of a projection (selection) of a tuplet element
 */
static Type inferProjType(Type t, int i, int vec)
{
    TupletType* tt = isTupletType(t);
    if (tt == nullptr) {
        stringstream error;
        error << "ERROR : inferring projection type, not a tuplet type : " << t << endl;
        throw faustexception(error.str());
    }
    Type temp = (*tt)[i]
                    ->promoteVariability(t->variability())
                    ->promoteComputability(t->computability())
                    ->promoteVectorability(vec /*t->vectorability()*/);

    if (vec == kVect) {
        temp = vecCast(temp);
    }
    return temp;
}

/**
 *    Infer the type of a table
 */
static Type inferTableType(Tree size, Tree gen, Tree env)
{
    checkInt(checkInit(T(size, env)));
    return makeTableType(checkInit(T(gen, env)));
}

/**
 *    Infer the type of the result of writing into a table
 */
static Type inferWriteTableType(Type tbl, Type wi, Type ws)
{
    TableType* tt = isTableType(tbl);
    if (tt == nullptr) {
        stringstream error;
        error << "ERROR : inferring write table type, wrong table type : " << tbl << endl;
        throw faustexception(error.str());
    }
    SimpleType* st = isSimpleType(wi);
    if (st == nullptr) {
        stringstream error;
        error << "ERROR : inferring write table type, wrong write index type : " << wi << endl;
        throw faustexception(error.str());
    }
    TRACE(cerr << gGlobal->TABBER << "inferring write table type : wi type = " << wi << endl);
    TRACE(cerr << gGlobal->TABBER << "inferring write table type : wd type = " << ws << endl);

    int n   = ws->nature();
    int b   = ws->boolean();
    int v   = wi->variability() | ws->variability();
    int c   = wi->computability() | ws->computability();
    int vec = wi->vectorability() | ws->vectorability();
    // Interval is the reunion of tbl (and its init signal) and ws
    interval i = itv::reunion(tbl->getInterval(), ws->getInterval());
    TRACE(cerr << gGlobal->TABBER << "infering write table type : n=" << "NR"[n]
               << ", v=" << "KB?S"[v] << ", c=" << "CI?E"[c] << ", vec=" << "VS?TS"[vec]
               << ", b=" << "N?B"[b] << ", i=" << i << endl);
    Type tbltype = makeTableType(tt->content(), n, v, c, vec, b, i);
    TRACE(cerr << gGlobal->TABBER << "infering write table type : result = " << tbltype << endl);
    return tbltype;
}

/**
 *	Infer the type of the result of reading a table
 */
static Type inferReadTableType(Type tbl, Type ri)
{
    TableType* tt = isTableType(tbl);
    if (tt == nullptr) {
        stringstream error;
        error << "ERROR : inferring read table type, no table type : " << tbl << endl;
        throw faustexception(error.str());
    }
    SimpleType* st = isSimpleType(ri);
    if (st == nullptr) {
        stringstream error;
        error << "ERROR : inferring read table type, no read index type : " << ri << endl;
        throw faustexception(error.str());
    }

    Type temp = makeSimpleType(tbl->nature(), tbl->variability() | ri->variability(),
                               tbl->computability() | ri->computability(),
                               tbl->vectorability() | ri->vectorability(), tbl->boolean(),
                               tbl->getInterval());

    return temp;
}

static Type inferDocConstantTblType(Type size, Type init)
{
    checkKonst(checkInt(checkInit(size)));
    return init;
}

static Type inferDocWriteTblType(Type size, Type init, Type widx, Type wsig)
{
    checkKonst(checkInt(checkInit(size)));
    Type temp =
        init->promoteVariability(kSamp)  // difficult to tell, therefore kSamp to be safe
            ->promoteComputability(widx->computability() | wsig->computability())
            ->promoteVectorability(kScal)       // difficult to tell, therefore kScal to be safe
            ->promoteNature(wsig->nature())     // nature of the initial and written signal
            ->promoteBoolean(wsig->boolean());  // booleanity of the initial and written signal
    return temp;
}

static Type inferDocAccessTblType(Type tbl, Type ridx)
{
    Type temp = tbl->promoteVariability(ridx->variability())
                    ->promoteComputability(ridx->computability())
                    ->promoteVectorability(ridx->vectorability());
    return temp;
}

/**
 * Compute an initial type solution for a recursive block
 * E1,E2,...En -> TREC,TREC,...TREC
 */
static TupletType* initialRecType(Tree t)
{
    faustassert(isList(t));
    return new TupletType(vector<Type>(len(t), gGlobal->TREC));
}

/**
 * Compute a maximal type solution for a recursive block
 * useful for widening approx
 * E1,E2,...En -> TRECMAX,TRECMAX,...TRECMAX
 */
static TupletType* maximalRecType(Tree t)
{
    faustassert(isList(t));
    return new TupletType(vector<Type>(len(t), gGlobal->TRECMAX));
}

/**
 * Infer the type of a recursive block by trying solutions of
 * increasing generality
 */
static Type inferRecType(Tree var, Tree body, Tree env)
{
    faustassert(false);  // we should not come here
    return nullptr;
}

/**
 *	Infer the type of a foreign function call
 */
static Type inferFFType(Tree ff, Tree ls, Tree env)
{
    // An external primitive can't be computed earlier than at initialization.
    // Its variability depends on the variability of its arguments unless it has no arguments,
    // in which case it is considered as rand(), i.e. the result varies at each call.

    if (ffarity(ff) == 0) {
        // case of functions like rand()
        return makeSimpleType(ffrestype(ff), kSamp, kInit, kVect, kNum, interval());
    } else {
        // otherwise variability and computability depends
        // arguments (OR of all arg types)
        Type t = makeSimpleType(kInt, kKonst, kInit, kVect, kNum, interval());
        while (isList(ls)) {
            t  = t | T(hd(ls), env);
            ls = tl(ls);
        }
        // but the result type is defined by the function
        return makeSimpleType(ffrestype(ff), t->variability(), t->computability(),
                              t->vectorability(), t->boolean(), interval());
    }
}

/**
 *  Infer the type of a foreign constant
 */
static Type inferFConstType(Tree type)
{
    // An external constant cannot be calculated at the earliest possible time the initialization.
    // It is constant, in which case it is considered a rand() i.e. the result varies at each call.
    return makeSimpleType(tree2int(type), kKonst, kInit, kVect, kNum, interval());
}

/**
 *  Infer the type of a foreign variable
 */
static Type inferFVarType(Tree type)
{
    // An external variable cannot be calculated as soon as it is executed.
    // It varies by blocks like the user interface elements.
    return makeSimpleType(tree2int(type), kBlock, kExec, kVect, kNum, interval());
}

/**
 *  Infer the type of a waveform:
 *  - the nature is int if all values are int, otherwise it is float
 *  - the variability is by samples
 *  - the waveform is known at compile time
 *  - it can be vectorized because all values are known
 *  - knum ???
 *  - the resulting interval is the reunion of all values
 *    intervals
 *  - ONDEMAND/UPSAMPLING/DOWNSAMPLING: The first value of the waveform is now
 *    sigClocked so that the sample production is in the right
 *    time reference.
 */
static Type inferWaveformType(Tree wfsig, Tree env)
{
    // start with the first item interval
    Tree v = wfsig->branch(0);
    T(v, env);
    // remove possible clock signal on the first item
    // TODO: all this could be simplified !
    if (Tree h, x; isSigClocked(v, h, x)) {
        v = x;
    }
    bool iflag1 = isInt(v->node());

    int      n   = wfsig->arity();
    interval res = (iflag1) ? gAlgebra.IntNum(tree2int(v)) : gAlgebra.FloatNum(tree2double(v));
    T(v, env);

    // loop for remaining items
    for (int i = 1; i < n; i++) {
        v = wfsig->branch(i);
        T(v, env);
        // compute interval
        bool iflag2 = isInt(v->node());
        res         = itv::reunion(
            res, iflag2 ? gAlgebra.IntNum(tree2int(v)) : gAlgebra.FloatNum(tree2double(v)));
        iflag1 &= iflag2;
    }

    return makeSimpleType((iflag1) ? kInt : kReal, kSamp, kComp, kScal, kNum, res);
}

/**
 *	Infer the type of an extended (primitive) block
 */
static Type inferXType(Tree sig, Tree env)
{
    xtended*     p = (xtended*)getUserData(sig);
    vector<Type> vt;

    for (int i = 0; i < sig->arity(); i++) {
        vt.push_back(T(sig->branch(i), env));
    }
    return p->inferSigType(vt);
}

static Type inferFIRType(Tree sig, Tree env)
{
    // we assume a normal FIR with at least a Ci != 0 (i>0)
    tvec         coef;
    vector<Type> vt;

    faustassert(isSigFIR(sig, coef));

    for (Tree b : coef) {
        vt.push_back(T(b, env));
    }

    int       nature        = vt[0]->nature();  //= kInt;
    const int variability   = kSamp;            // because we have delays
    const int computability = kExec;
    int       vectorability = kVect;
    const int booleanity    = kNum;
    // const itv::interval X             = vt[0]->getInterval();
    // const itv::interval XZ            = reunion(X, interval(0));
    // itv::interval       R             = gAlgebra.Mul(X, vt[1]->getInterval());
    for (unsigned int i = 1; i < vt.size(); i++) {
        nature        = nature | vt[i]->nature();
        vectorability = vectorability | vt[i]->vectorability();
    }
    std::vector<double> numcoefs;
    for (unsigned int i = 1; i < vt.size(); i++) {
        itv::interval C = vt[i]->getInterval();
        numcoefs.push_back((C.lo() + C.hi()) / 2.0);
    }
    double gain = FIRWorstPeakGain(numcoefs);
    // std::cerr << "FIR gain = " << gain << " for " << ppsig(sig) << endl;
    itv::interval R2 = gAlgebra.Mul(vt[0]->getInterval(), itv::interval(gain));

    return makeSimpleType(nature, variability, computability, vectorability, booleanity, R2);
}

static Type inferIIRType(Tree sig, Tree env)
{
    // we assume a normal IIR with at least a Ci != 0 (i>0)
    // IIR[W,X,0,C1,C2,...,Cn] we assume a normal IIR Cn != 0
    //     0,1,2,3 ,4...
    tvec coef;
    faustassert(isSigIIR(sig, coef) && (coef.size() >= 4) && isNil(coef[0]) && isZero(coef[2]));

    // We ignore we visit
    Type         tx = T(coef[1], env);  // this is the input signal X
    Type         t0 = T(coef[2], env);  // this is C0, zero and ignored
    vector<Type> ct;                    // vector of coefficient types starting from C1..Cn
    for (unsigned int i = 3; i < coef.size(); i++) {
        ct.push_back(T(coef[i], env));
    }
    // For worst-case gain analysis with variable coefficients, we need to test
    // all 2^nz combinations where nz is the number of variable coefficients
    double gain = 0.0;
    int    n    = ct.size();  // total number of coefficients

    // Extract coefficient intervals and count variable coefficients
    std::vector<itv::interval> coef_intervals;
    int                        nz = 0;  // number of variable coefficients (hi > lo)
    for (Type t : ct) {
        itv::interval C = t->getInterval();
        coef_intervals.push_back(C);
        if (C.hi() > C.lo()) {
            nz++;
        }
    }

    // Test all 2^nz corner cases (only for variable coefficients)
    int num_combinations = (nz == 0) ? 1 : (1 << nz);  // 2^nz
    for (int mask = 0; mask < num_combinations; mask++) {
        std::vector<double> numcoefs;
        int                 bit_index = 0;

        for (int i = 0; i < n; i++) {
            double coef;
            if (coef_intervals[i].hi() > coef_intervals[i].lo()) {
                // Variable coefficient: use the corresponding bit
                coef = (mask & (1 << bit_index)) ? coef_intervals[i].hi() : coef_intervals[i].lo();
                bit_index++;
            } else {
                // Constant coefficient: use the unique value
                coef = coef_intervals[i].lo();
            }
            numcoefs.push_back(coef);
        }

        double g = IIRWorstPeakGain(numcoefs);
        if (g > gain) {
            gain = g;
        }
    }

    // std::cerr << "IIR worst-case gain = " << gain << " (tested " << num_combinations
    //           << " combinations, " << nz << " variable out of " << n << " coefficients)"
    //           << std::endl;

    // for (unsigned int i = 2; i < 16; i++) {
    //     double g = IIRWorstPeakGain(numcoefs, 1 << i);
    //     std::cerr << "points: " << (1 << i) << " IIR gain = " << g << " for " << ppsig(sig) <<
    //     endl;
    // }

    int       nature        = tx->nature();
    const int variability   = kSamp;  // because we have delays
    int       computability = tx->computability();
    const int vectorability = kScal;  // because we are recursive
    const int booleanity    = kNum;   // probably not a boolean value

    // Distinguish between integer and floating-point IIR filters
    // See compiler/transform/iirgain.md for detailed explanation
    bool isIntegerIIR = (tx->nature() == kInt);
    for (Type t : ct) {
        if (t->nature() != kInt) {
            isIntegerIIR = false;
            break;
        }
    }

    itv::interval R2;
    if (isIntegerIIR) {
        // Integer IIR filter: high/infinite gain means wrapping or unbounded accumulation
        // Use full int range to represent all possible wrapped values
        itv::interval input_range = tx->getInterval();
        double        max_output =
            std::max(std::abs(input_range.lo() * gain), std::abs(input_range.hi() * gain));

        const double INT_MAX_THRESHOLD = 2147483647.0;  // 2^31 - 1

        if (max_output > INT_MAX_THRESHOLD || std::isinf(gain) || gain > 1e9) {
            // IIR can produce any integer (wrapping or unlimited accumulation)
            R2 = itv::interval(-INT_MAX_THRESHOLD, INT_MAX_THRESHOLD);
            // std::cerr << "IIR integer filter with high/infinite gain: using full int range"
            //           << std::endl;
        } else {
            R2 = gAlgebra.Mul(input_range, itv::interval(gain));
        }
    } else {
        // Floating-point IIR filter: high/infinite gain means instability
        if (std::isinf(gain) || gain > 1e12) {
            // Unstable filter: can diverge to ±∞
            R2 = itv::interval(-INFINITY, INFINITY);
            // std::cerr << "WARNING: IIR floating-point filter is unstable (gain = " << gain << ")"
            //           << std::endl;
        } else {
            R2 = gAlgebra.Mul(tx->getInterval(), itv::interval(gain));
        }
    }

    Type tr = makeSimpleType(nature, variability, computability, vectorability, booleanity, R2);
    // std::cerr << "IIR type is " << *tr << " for signal " << ppsig(sig) << std::endl;
    return tr;
}
