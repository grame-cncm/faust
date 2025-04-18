/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    Copyright (C) 2024-2024 INRIA
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
#undef TRACE

/**
 * \file eval.cpp
 * Implementation of the Block diagram evaluator.
 *
 * A strict lambda-calculus evaluator for block diagram expressions.
 *
 **/

#include <stdio.h>
#include <cstdlib>

#include "boxIdentity.hh"
#include "boxModulationImplanter.hh"
#include "compatibility.hh"
#include "environment.hh"
#include "errormsg.hh"
#include "eval.hh"
#include "exception.hh"
#include "global.hh"
#include "labels.hh"
#include "names.hh"
#include "patternmatcher.hh"
#include "ppbox.hh"
#include "propagate.hh"
#include "property.hh"
#include "simplify.hh"
#include "xtended.hh"

using namespace std;

// History
// 23/05/2005 : New environment management

//-------------- prototypes ---------------------------------------------------------
static Tree   a2sb(Tree exp);
static Tree   eval(Tree exp, Tree visited, Tree localValEnv);
static Tree   realeval(Tree exp, Tree visited, Tree localValEnv);
static Tree   revEvalList(Tree lexp, Tree visited, Tree localValEnv);
static Tree   applyList(Tree fun, Tree larg);
static Tree   iteratePar(Tree var, int num, Tree body, Tree visited, Tree localValEnv);
static Tree   iterateSeq(Tree id, int num, Tree body, Tree visited, Tree localValEnv);
static Tree   iterateSum(Tree id, int num, Tree body, Tree visited, Tree localValEnv);
static Tree   iterateProd(Tree id, int num, Tree body, Tree visited, Tree localValEnv);
static Tree   larg2par(Tree larg);
static int    eval2int(Tree exp, Tree visited, Tree localValEnv);
static double eval2double(Tree exp, Tree visited, Tree localValEnv);
static string evalLabel(const char* l, Tree visited, Tree localValEnv);

static Tree evalIdDef(Tree id, Tree visited, Tree env);

static Tree evalCase(Tree rules, Tree env);
static Tree evalRuleList(Tree rules, Tree env);
static Tree evalRule(Tree rule, Tree env);
static Tree evalPatternList(Tree patterns, Tree env);
static Tree evalPattern(Tree pattern, Tree env);

static Tree patternSimplification(Tree pattern);
static bool isBoxNumeric(Tree in, Tree& out);

static Tree vec2list(const vector<Tree>& v);
static void list2vec(Tree l, vector<Tree>& v);
static Tree listn(int n, Tree e);

static Tree boxSimplification(Tree box);

static void setNumericProperty(Tree t, Tree num);
static bool getNumericProperty(Tree t, Tree& num);

//------------------
// Public Interface
//------------------

/**
 * Eval "process" from a list of definitions.
 *
 * Strict evaluation of a block diagram expression by applying beta reduction.
 * @param eqlist a list of Faust definitions forming the global environment
 * @return the process block diagram in normal form
 */
Tree evalprocess(Tree eqlist)
{
    // Init stack overflow detector
    gGlobal->gStackOverflowDetector = stackOverflowDetector(MAX_STACK_SIZE);
    Tree b = a2sb(eval(boxIdent(gGlobal->gProcessName.c_str()), gGlobal->nil,
                       pushMultiClosureDefs(eqlist, gGlobal->nil, gGlobal->nil)));

    if (gGlobal->gSimplifyDiagrams) {
        b = boxSimplification(b);
    }

    return b;
}

/* Eval a documentation expression. */
Tree evaldocexpr(Tree docexpr, Tree eqlist)
{
    // Init stack overflow detector
    gGlobal->gStackOverflowDetector = stackOverflowDetector(MAX_STACK_SIZE);
    return a2sb(
        eval(docexpr, gGlobal->nil, pushMultiClosureDefs(eqlist, gGlobal->nil, gGlobal->nil)));
}

/**
 * Simplify a block-diagram pattern by computing its numerical sub-expressions
 * \param pattern an evaluated block-diagram
 * \return a simplified pattern
 *
 */
/* uncomment for debugging output */
// #define DEBUG
Tree simplifyPattern(Tree value)
{
    Tree num;
    if (!getNumericProperty(value, num)) {
        if (!isBoxNumeric(value, num)) {
            num = value;
        }
        setNumericProperty(value, num);
    }
    return num;
}

//------------------------
// Private Implementation
//------------------------

/**
 * Transform unused (unapplied) closures into symbolic boxes.
 *
 * @param exp the expression to transform
 * @return an expression where abstractions have been replaced by symbolic boxes
 */

static Tree real_a2sb(Tree exp);

static Tree a2sb(Tree exp)
{
    Tree result;
    Tree id;

    if (gGlobal->gSymbolicBoxProperty->get(exp, result)) {
        return result;
    }

    result = real_a2sb(exp);
    if (result != exp && getDefNameProperty(exp, id)) {
        // Propagate definition name property when needed
        setDefNameProperty(result, id);
    }
    gGlobal->gSymbolicBoxProperty->set(exp, result);
    return result;
}

static Tree real_a2sb(Tree exp)
{
    Tree abstr, visited, unusedEnv, localValEnv, var, name, body;

    if (isClosure(exp, abstr, unusedEnv, visited, localValEnv)) {
        if (isBoxIdent(abstr)) {
            // Special case introduced with access and components
            Tree result = a2sb(eval(abstr, visited, localValEnv));

            // Propagate definition name property when needed
            if (getDefNameProperty(exp, name)) {
                setDefNameProperty(result, name);
            }
            return result;

        } else if (isBoxAbstr(abstr, var, body)) {
            // Here we have remaining abstraction that we will try to
            // transform in a symbolic box by applying it to a slot

            Tree         slot = boxSlot(++gGlobal->gBoxSlotNumber);
            stringstream s;
            s << boxpp(var);
            setDefNameProperty(slot, s.str());

            // Apply the abstraction to the slot
            Tree result =
                boxSymbolic(slot, a2sb(eval(body, visited, pushValueDef(var, slot, localValEnv))));

            // Propagate definition name property when needed
            if (getDefNameProperty(exp, name)) {
                setDefNameProperty(result, name);
            }
            return result;

        } else if (isBoxEnvironment(abstr)) {
            return abstr;

        } else {
            evalerror(FAUSTfilename, -1,
                      "a2sb : internal error : not an abstraction inside closure (1)", exp);
            // Never reached since evalerror throws an exception
            return 0;
        }

    } else if (isBoxPatternMatcher(exp)) {
        // Here we have remaining PM rules that we will try to
        // transform in a symbolic box by applying it to a slot

        Tree         slot = boxSlot(++gGlobal->gBoxSlotNumber);
        stringstream s;
        s << "PM" << gGlobal->gBoxSlotNumber;
        setDefNameProperty(slot, s.str());

        // Apply the PM rules to the slot and transfoms the result in a symbolic box
        Tree result = boxSymbolic(slot, a2sb(applyList(exp, cons(slot, gGlobal->nil))));

        // Propagate definition name property when needed
        if (getDefNameProperty(exp, name)) {
            setDefNameProperty(result, name);
        }
        return result;

    } else if (isBoxWaveform(exp)) {
        // A waveform is always in Normal Form, nothing to evaluate
        return exp;

    } else {
        // It is a constructor : transform each branches
        unsigned int ar = exp->arity();
        tvec         B(ar);
        bool         modified = false;
        for (unsigned int i = 0; i < ar; i++) {
            Tree b = exp->branch(i);
            Tree m = a2sb(b);
            B[i]   = m;
            if (b != m) {
                modified = true;
            }
        }
        Tree r = (modified) ? tree(exp->node(), B) : exp;
        return r;
    }
}

/**
 * Set the value of box in the environment env.
 *
 * @param box the block diagram we have evaluated
 * @param env the evaluation environment
 * @param value the evaluated block diagram
 */
static void setEvalProperty(Tree box, Tree env, Tree value)
{
    setProperty(box, tree(gGlobal->EVALPROPERTY, env), value);
}

/**
 * Retrieve the value of box in the environment env.
 *
 * @param box the expression we want to retrieve the value
 * @param env the lexical environment
 * @param value the returned value if any
 * @return true if a value already exist
 */
static bool getEvalProperty(Tree box, Tree env, Tree& value)
{
    return getProperty(box, tree(gGlobal->EVALPROPERTY, env), value);
}

/**
 * Eval a block diagram expression.
 *
 * Wrap the realeval function in order to propagate the name property
 * @param exp the expression to evaluate
 * @param visited list of visited definitions to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree eval(Tree exp, Tree visited, Tree localValEnv)
{
    Tree id;
    Tree result;

    // cerr << "eval : " << boxpp(exp) << " in env " << envpp(localValEnv) << endl;

    if (!getEvalProperty(exp, localValEnv, result)) {
        gGlobal->gLoopDetector.detect(cons(exp, localValEnv));
        gGlobal->gStackOverflowDetector.detect();
        result = realeval(exp, visited, localValEnv);
        setEvalProperty(exp, localValEnv, result);
        if (getDefNameProperty(exp, id)) {
            setDefNameProperty(result, id);  // propagate definition name property
        }
    }
    return result;
}

/**
 * Check numerical tuple.
 *
 * Check if a box is a parallel construction of numbers
 * @param box the expression to analyse
 * @param L the resulting flat list of numbers
 * @return true if box is a parallel construction of numbers
 */
static bool isNumericalTuple(Tree box, siglist& L)
{
    Tree l, r;

    if (isBoxInt(box) || isBoxReal(box)) {
        L.push_back(box);
        return true;
    } else if (isBoxPar(box, l, r) && isNumericalTuple(l, L)) {
        return isNumericalTuple(r, L);
    } else {
        return false;
    }
}

/**
 * Eval a block diagram expression.
 *
 * Strict evaluation of a block diagram expression by applying beta reduction.
 * @param exp the expression to evaluate
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree realeval(Tree exp, Tree visited, Tree localValEnv)
{
    Tree fun;
    Tree arg;
    Tree var, num, chan, body, ldef, ins, outs, routes;
    Tree label;
    Tree cur, lo, hi, step;
    Tree e1, e2, exp2, notused, visited2, lenv2;
    Tree rules;
    Tree id;

    xtended* xt = (xtended*)getUserData(exp);

    // cerr << "realeval : " << boxpp(exp) << " in env " << envpp(localValEnv) << endl;

    // Constants
    //-----------

    if (xt || isBoxInt(exp) || isBoxReal(exp) || isBoxWire(exp) || isBoxCut(exp) ||
        isBoxPrim0(exp) || isBoxPrim1(exp) || isBoxPrim2(exp) || isBoxPrim3(exp) ||
        isBoxPrim4(exp) || isBoxPrim5(exp) || isBoxFFun(exp) || isBoxFConst(exp) ||
        isBoxFVar(exp) || isBoxWaveform(exp)) {
        return exp;

        // Block-diagram constructors
        //---------------------------

    } else if (isBoxSeq(exp, e1, e2)) {
        Tree a1 = eval(e1, visited, localValEnv);
        Tree a2 = eval(e2, visited, localValEnv);
        Tree re = boxSeq(a1, a2);

        xtended* xxt = (xtended*)getUserData(a2);
        siglist  lsig;
        // Try a numerical simplification of expressions of type 2,3:+
        if (isNumericalTuple(a1, lsig) &&
            (xxt || isBoxWire(a2) || isBoxPrim1(a2) || isBoxPrim2(a2))) {
            // check that re is well typed before trying to simplify it
            int n, m;
            getBoxType(re, &n, &m);

            Tree lres = boxPropagateSig(gGlobal->nil, a2, lsig);
            if (isList(lres) && isNil(tl(lres))) {
                Tree r = simplify(hd(lres));
                if (isNum(r)) {
                    return r;
                }
            }
        }
        // No numerical simplification
        return re;

    } else if (isBoxPar(exp, e1, e2)) {
        return boxPar(eval(e1, visited, localValEnv), eval(e2, visited, localValEnv));

    } else if (isBoxRec(exp, e1, e2)) {
        return boxRec(eval(e1, visited, localValEnv), eval(e2, visited, localValEnv));

    } else if (isBoxSplit(exp, e1, e2)) {
        return boxSplit(eval(e1, visited, localValEnv), eval(e2, visited, localValEnv));

    } else if (isBoxMerge(exp, e1, e2)) {
        return boxMerge(eval(e1, visited, localValEnv), eval(e2, visited, localValEnv));

        // Modules
        //--------

    } else if (isBoxAccess(exp, body, var)) {
        Tree val = eval(body, visited, localValEnv);
        if (isClosure(val, exp2, notused, visited2, lenv2)) {
            // It is a closure, we have an environment to access
            return eval(closure(var, notused, visited2, lenv2), visited, localValEnv);
        } else {
            evalerror(getDefFileProp(exp), getDefLineProp(exp), "no environment to access", exp);
        }

        //////////////////////en chantier////////////////////////////

    } else if (isBoxModifLocalDef(exp, body, ldef)) {
        Tree val = eval(body, visited, localValEnv);
        if (isClosure(val, exp2, notused, visited2, lenv2)) {
            // We rebuild the closure using a copy of the original environment
            // modified with some new definitions
            Tree lenv3 = copyEnvReplaceDefs(lenv2, ldef, visited2, localValEnv);
            return eval(closure(exp2, notused, visited2, lenv3), visited, localValEnv);
        } else {
            evalerror(getDefFileProp(exp), getDefLineProp(exp), "not a closure", val);
            evalerror(getDefFileProp(exp), getDefLineProp(exp), "no environment to access", exp);
        }

        ///////////////////////////////////////////////////////////////////

    } else if (isBoxComponent(exp, label)) {
        const char* fname = tree2str(label);
        Tree        eqlst = gGlobal->gReader.expandList(gGlobal->gReader.getList(fname));
        Tree        res   = closure(boxIdent("process"), gGlobal->nil, gGlobal->nil,
                                    pushMultiClosureDefs(eqlst, gGlobal->nil, gGlobal->nil));
        setDefNameProperty(res, label);
        return res;

    } else if (isBoxLibrary(exp, label)) {
        const char* fname = tree2str(label);
        Tree        eqlst = gGlobal->gReader.expandList(gGlobal->gReader.getList(fname));
        Tree        res   = closure(boxEnvironment(), gGlobal->nil, gGlobal->nil,
                                    pushMultiClosureDefs(eqlst, gGlobal->nil, gGlobal->nil));
        setDefNameProperty(res, label);
        return res;

        // User interface elements
        //------------------------

    } else if (isBoxButton(exp, label)) {
        const char* l1 = tree2str(label);
        string      s1 = evalLabel(l1, visited, localValEnv);
        Tree        l2 = tree(s1.c_str());
        Tree        w  = boxButton(l2);
        return w;

    } else if (isBoxCheckbox(exp, label)) {
        const char* l1 = tree2str(label);
        string      s1 = evalLabel(l1, visited, localValEnv);
        Tree        l2 = tree(s1.c_str());
        Tree        w  = boxCheckbox(l2);
        return w;

    } else if (isBoxVSlider(exp, label, cur, lo, hi, step)) {
        const char* l1 = tree2str(label);
        string      s1 = evalLabel(l1, visited, localValEnv);
        Tree        l2 = tree(s1.c_str());
        Tree        w  = (boxVSlider(l2, tree(eval2double(cur, visited, localValEnv)),
                                     tree(eval2double(lo, visited, localValEnv)),
                                     tree(eval2double(hi, visited, localValEnv)),
                                     tree(eval2double(step, visited, localValEnv))));
        return w;

    } else if (isBoxHSlider(exp, label, cur, lo, hi, step)) {
        const char* l1 = tree2str(label);
        string      s1 = evalLabel(l1, visited, localValEnv);
        Tree        l2 = tree(s1.c_str());
        Tree        w  = (boxHSlider(l2, tree(eval2double(cur, visited, localValEnv)),
                                     tree(eval2double(lo, visited, localValEnv)),
                                     tree(eval2double(hi, visited, localValEnv)),
                                     tree(eval2double(step, visited, localValEnv))));
        return w;

    } else if (isBoxNumEntry(exp, label, cur, lo, hi, step)) {
        const char* l1 = tree2str(label);
        string      s1 = evalLabel(l1, visited, localValEnv);
        Tree        l2 = tree(s1.c_str());
        Tree        w  = (boxNumEntry(l2, tree(eval2double(cur, visited, localValEnv)),
                                      tree(eval2double(lo, visited, localValEnv)),
                                      tree(eval2double(hi, visited, localValEnv)),
                                      tree(eval2double(step, visited, localValEnv))));
        return w;

    } else if (isBoxSoundfile(exp, label, chan)) {
        const char* l1 = tree2str(label);
        string      l2 = evalLabel(l1, visited, localValEnv);
        return boxSoundfile(tree(l2.c_str()), tree(eval2int(chan, visited, localValEnv)));

    } else if (isBoxVGroup(exp, label, arg)) {
        const char* l1 = tree2str(label);
        string      l2 = evalLabel(l1, visited, localValEnv);
        return boxVGroup(tree(l2.c_str()), eval(arg, visited, localValEnv));

    } else if (isBoxHGroup(exp, label, arg)) {
        const char* l1 = tree2str(label);
        string      l2 = evalLabel(l1, visited, localValEnv);
        return boxHGroup(tree(l2.c_str()), eval(arg, visited, localValEnv));

    } else if (isBoxTGroup(exp, label, arg)) {
        const char* l1 = tree2str(label);
        string      l2 = evalLabel(l1, visited, localValEnv);
        return boxTGroup(tree(l2.c_str()), eval(arg, visited, localValEnv));

    } else if (isBoxHBargraph(exp, label, lo, hi)) {
        const char* l1 = tree2str(label);
        string      l2 = evalLabel(l1, visited, localValEnv);
        return boxHBargraph(tree(l2.c_str()), tree(eval2double(lo, visited, localValEnv)),
                            tree(eval2double(hi, visited, localValEnv)));

    } else if (isBoxMetadata(exp, e1, e2)) {
        gGlobal->gMetaDataSet[hd(e2)].insert(tl(e2));
        return eval(e1, visited, localValEnv);

    } else if (isBoxVBargraph(exp, label, lo, hi)) {
        const char* l1 = tree2str(label);
        string      l2 = evalLabel(l1, visited, localValEnv);
        return boxVBargraph(tree(l2.c_str()), tree(eval2double(lo, visited, localValEnv)),
                            tree(eval2double(hi, visited, localValEnv)));

        // Lambda calculus
        //----------------

    } else if (isBoxIdent(exp)) {
        return evalIdDef(exp, visited, localValEnv);

    } else if (isBoxWithLocalDef(exp, body, ldef)) {
        Tree expandedldef = gGlobal->gReader.expandList(ldef);
        return eval(body, visited, pushMultiClosureDefs(expandedldef, visited, localValEnv));

    } else if (isBoxAppl(exp, fun, arg)) {
        return applyList(eval(fun, visited, localValEnv), revEvalList(arg, visited, localValEnv));

    } else if (isBoxAbstr(exp)) {
        // it is an abstraction : return a closure
        return closure(exp, gGlobal->nil, visited, localValEnv);

    } else if (isBoxEnvironment(exp)) {
        // environment : return also a closure
        return closure(exp, gGlobal->nil, visited, localValEnv);

    } else if (isClosure(exp, exp2, notused, visited2, lenv2)) {
        if (isBoxAbstr(exp2)) {
            // a 'real' closure
            return closure(exp2, gGlobal->nil, setUnion(visited, visited2), lenv2);
        } else if (isBoxEnvironment(exp2)) {
            // a 'real' closure
            return closure(exp2, gGlobal->nil, setUnion(visited, visited2), lenv2);
        } else {
            // it was a suspended evaluation
            return eval(exp2, setUnion(visited, visited2), lenv2);
        }

        // Algorithmic constructions
        //--------------------------

    } else if (isBoxIPar(exp, var, num, body)) {
        int n = eval2int(num, visited, localValEnv);
        return iteratePar(var, n, body, visited, localValEnv);

    } else if (isBoxISeq(exp, var, num, body)) {
        int n = eval2int(num, visited, localValEnv);
        return iterateSeq(var, n, body, visited, localValEnv);

    } else if (isBoxISum(exp, var, num, body)) {
        int n = eval2int(num, visited, localValEnv);
        return iterateSum(var, n, body, visited, localValEnv);

    } else if (isBoxIProd(exp, var, num, body)) {
        int n = eval2int(num, visited, localValEnv);
        return iterateProd(var, n, body, visited, localValEnv);

        // Static
    } else if (isBoxInputs(exp, body)) {
        int  ins1, outs1;
        Tree b = a2sb(eval(body, visited, localValEnv));
        if (getBoxType(b, &ins1, &outs1)) {
            return boxInt(ins1);
        } else {
            stringstream error;
            error << "ERROR : can't evaluate : " << *exp << endl;
            throw faustexception(error.str());
        }

    } else if (isBoxOutputs(exp, body)) {
        int  ins1, outs1;
        Tree b = a2sb(eval(body, visited, localValEnv));
        if (getBoxType(b, &ins1, &outs1)) {
            return boxInt(outs1);
        } else {
            stringstream error;
            error << "ERROR : can't evaluate : " << *exp << endl;
            throw faustexception(error.str());
        }

    } else if (isBoxSlot(exp)) {
        return exp;

    } else if (isBoxSymbolic(exp)) {
        return exp;

        // Pattern matching extension
        //---------------------------

    } else if (isBoxCase(exp, rules)) {
        return evalCase(rules, localValEnv);

    } else if (isBoxPatternVar(exp, id)) {
        return exp;
        // return evalIdDef(id, visited, localValEnv);

    } else if (isBoxPatternMatcher(exp)) {
        return exp;

    } else if (isBoxRoute(exp, ins, outs, routes)) {
        // Evaluate the route description
        Tree v1 = a2sb(eval(ins, visited, localValEnv));
        Tree v2 = a2sb(eval(outs, visited, localValEnv));
        Tree vr = a2sb(eval(routes, visited, localValEnv));

        // Check that we have constant numerical descriptions
        int i1, o1, i2, o2, i3, o3;

        getBoxType(v1, &i1, &o1);
        getBoxType(v2, &i2, &o2);
        getBoxType(vr, &i3, &o3);

        if ((i1 == 0) & (o1 == 1) & (i2 == 0) & (o2 == 1) & (i3 == 0) & (o3 > 1) &
            ((o3 % 2) == 0)) {
            // We are in good shape
            Tree ls1 = boxPropagateSig(gGlobal->nil, v1, makeSigInputList(0));
            Tree ls2 = boxPropagateSig(gGlobal->nil, v2, makeSigInputList(0));
            Tree lsr = boxPropagateSig(gGlobal->nil, vr, makeSigInputList(0));

            // All these lists should be list of constant numerical signals
            // that we need to convert back to box expressions
            vector<int> w1, w2, wr;
            if (sigList2vecInt(ls1, w1) && sigList2vecInt(ls2, w2) && sigList2vecInt(lsr, wr)) {
                // Convert wr into a parallel boxes of ints b
                Tree b = boxInt(wr[o3 - 1]);
                for (int j = o3 - 2; j >= 0; j--) {
                    b = boxPar(boxInt(wr[j]), b);
                }
                return boxRoute(boxInt(w1[0]), boxInt(w2[0]), b);
            } else {
                evalerror(getDefFileProp(exp), getDefLineProp(exp),
                          "invalid route expression, parameters should be numbers", exp);
            }
        } else {
            evalerror(getDefFileProp(exp), getDefLineProp(exp),
                      "invalid route expression, first two parameters should be blocks producing a "
                      "value, third "
                      "parameter a list of input/output pairs",
                      exp);
        }

    } else if (isBoxModulation(exp, var, body)) {
        // Evaluation of a box modulation expression. The body will be rewriten to introduce
        // modulation circuits.

        // Var is a pair (label, modulation circuit). The modulation circuit can be NIL if was not
        // specified
        faustassert(isList(var));

        // Evaluate the label and the modulation circuit to be used
        Tree   ulabel   = hd(var);
        string s1       = evalLabel(tree2str(ulabel), visited, localValEnv);
        Tree   elabel   = target2path(s1);
        Tree   mcircuit = tl(var);
        Tree   emcircuit =
            isNil(mcircuit) ? boxPrim2(sigMul) : a2sb(eval(mcircuit, visited, localValEnv));

        // Check the number of inputs (<= 2) and outputs (1) of the modulation circuit
        int inum, onum;
        if (getBoxType(emcircuit, &inum, &onum)) {
            if (inum > 2) {
                evalerror(getDefFileProp(exp), getDefLineProp(exp),
                          "invalid modulation circuit, should have no more than 2 inputs", exp);
            } else if (onum != 1) {
                evalerror(getDefFileProp(exp), getDefLineProp(exp),
                          "invalid modulation circuit, it should have exactly 1 output", exp);
            }
        } else {
            evalerror(getDefFileProp(exp), getDefLineProp(exp),
                      "invalid modulation circuit, should be a block diagram", exp);
        }

        // If needed, create a new slot named after the evaluated label
        Tree slot;

        if (inum == 2) {
            // we need a slot for the modulation signal
            slot = boxSlot(++gGlobal->gBoxSlotNumber);
            stringstream s;
            s << *elabel;
            setDefNameProperty(slot, s.str());
        } else {
            // no need for a slot
            slot = gGlobal->nil;
        }

        // Fully evaluate the body we are going to rewrite
        Tree ebody = a2sb(eval(body, visited, localValEnv));

        // rewrite the body
        BoxModulationImplanter bm(elabel, slot, inum, emcircuit);
        bm.trace(false);

        Tree mbody = bm.self(ebody);

        if (mbody == ebody) {
            stringstream error;
            error << "WARNING : no modulation of: '" << *elabel
                  << "' took place in: " << boxpp(ebody) << endl;
            gWarningMessages.push_back(error.str());
        }

        // if we have a slot, we need to wrap the modulation body in a symbolic box
        if (inum == 2) {
            return boxSymbolic(slot, mbody);
        } else {
            return mbody;
        }

    } else {
        cerr << "ASSERT : eval doesn't intercept : " << *exp << endl;
        faustassert(false);
    }

    return nullptr;
}

/* Deconstruct a (BDA) op pattern */
static inline bool isBoxPatternOp(Tree box, Node& n, Tree& t1, Tree& t2)
{
    if (isBoxPar(box, t1, t2) || isBoxSeq(box, t1, t2) || isBoxSplit(box, t1, t2) ||
        isBoxMerge(box, t1, t2) || isBoxRec(box, t1, t2)) {
        n = box->node();
        return true;
    } else {
        return false;
    }
}

static void setNumericProperty(Tree t, Tree num)
{
    setProperty(t, gGlobal->NUMERICPROPERTY, num);
}

static bool getNumericProperty(Tree t, Tree& num)
{
    return getProperty(t, gGlobal->NUMERICPROPERTY, num);
}

static bool isBoxNumeric(Tree in, Tree& out)
{
    int    numInputs, numOutputs;
    double x;
    int    i;
    Tree   v, abstr, genv, vis, lenv, var, body;

    if (isBoxInt(in, &i) || isBoxReal(in, &x)) {
        out = in;
        return true;
    } else if (isClosure(in, abstr, genv, vis, lenv) && isBoxAbstr(abstr, var, body)) {
        return false;
    } else {
        v = a2sb(in);
        if (getBoxType(v, &numInputs, &numOutputs) && (numInputs == 0) && (numOutputs == 1)) {
            // Potential numerical expression
            Tree lsignals = boxPropagateSig(gGlobal->nil, v, makeSigInputList(numInputs));
            Tree res      = simplify(hd(lsignals));
            if (isSigReal(res, &x)) {
                out = boxReal(x);
                return true;
            }
            if (isSigInt(res, &i)) {
                out = boxInt(i);
                return true;
            }
        }
        return false;
    }
}

static Tree patternSimplification(Tree pattern)
{
    Node n(0);
    Tree v, t1, t2;

    if (isBoxNumeric(pattern, v)) {
        return v;
    } else if (isBoxPatternOp(pattern, n, t1, t2)) {
        return tree(n, patternSimplification(t1), patternSimplification(t2));
    } else {
        return pattern;
    }
}

/**
 * Eval a block diagram to a double.
 *
 * Eval a block diagram that represent a double constant. This function first eval
 * a block diagram to its normal form, then check it represent a numerical value (a
 * block diagram of type : 0->1) then do a symbolic propagation and try to convert the
 * resulting signal to a double.
 * @param exp the expression to evaluate
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static double eval2double(Tree exp, Tree visited, Tree localValEnv)
{
    Tree diagram = a2sb(eval(exp, visited, localValEnv));  // For getBoxType
    int  numInputs, numOutputs;
    getBoxType(diagram, &numInputs, &numOutputs);
    if ((numInputs > 0) || (numOutputs != 1)) {
        evalerror(FAUSTfilename, FAUSTlineno, "not a constant expression of type : (0->1)", exp);
        // Never reached since evalerror throws an exception
        return 1;
    } else {
        Tree lsignals = boxPropagateSig(gGlobal->nil, diagram, makeSigInputList(numInputs));
        Tree val      = simplify(hd(lsignals));
        return tree2double(val);
    }
}

/**
 * Eval a block diagram to an int.
 *
 * Eval a block diagram that represent an integer constant. This function first eval
 * a block diagram to its normal form, then check it represent a numerical value (a
 * block diagram of type : 0->1) then do a symbolic propagation and try to convert the
 * resulting signal to an int.
 * @param exp the expression to evaluate
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static int eval2int(Tree exp, Tree visited, Tree localValEnv)
{
    Tree diagram = a2sb(eval(exp, visited, localValEnv));  // pour getBoxType()
    int  numInputs, numOutputs;
    getBoxType(diagram, &numInputs, &numOutputs);
    if ((numInputs > 0) || (numOutputs != 1)) {
        evalerror(FAUSTfilename, FAUSTlineno, "not a constant expression of type : (0->1)", exp);
        // Never reached since evalerror throws an exception
        return 1;
    } else {
        Tree lsignals = boxPropagateSig(gGlobal->nil, diagram, makeSigInputList(numInputs));
        Tree val      = simplify(hd(lsignals));
        return tree2int(val);
    }
}

static bool isDigitChar(char c)
{
    return (c >= '0') & (c <= '9');
}

static bool isIdentChar(char c)
{
    return ((c >= 'a') & (c <= 'z')) || ((c >= 'A') & (c <= 'Z')) || ((c >= '0') & (c <= '9')) ||
           (c == '_');
}

static const char* Formats[] = {"%d", "%1d", "%2d", "%3d", "%4d"};

static void writeIdentValue(string& dst, const string& format, const string& ident, Tree visited,
                            Tree localValEnv)
{
    int  f = std::atoi(format.c_str());
    int  n = eval2int(boxIdent(ident.c_str()), visited, localValEnv);
    int  i = std::min(4, std::max(f, 0));
    char val[256];

    snprintf(val, 250, Formats[i], n);
    dst += val;
}

/**
 * evallabel replace "...%2i..." occurences in label with value of i
 */
static string evalLabel(const char* src, Tree visited, Tree localValEnv)
{
    // cerr << "Eval Label : " << src;
    int    state = 0;  // current state
    string dst;        // label once evaluated
    string ident;      // current identifier
    string format;     // current format

    while (state != -1) {
        if (state == 0) {
            if (*src == 0) {
                state = -1;
            } else if (*src == '%') {
                ident  = "";
                format = "";
                state  = 1;
                src++;
            } else {
                dst += *src++;
                state = 0;
            }

        } else if (state == 1) {
            if (*src == 0) {
                // End and no identifier, stops
                dst += '%';
                dst += format;
                state = -1;
            } else if (isDigitChar(*src)) {
                format += *src++;
                state = 1;
            } else if (isIdentChar(*src)) {
                ident += *src++;
                state = 2;
            } else if (*src == '{') {
                src++;
                state = 3;
            } else {
                // Punctuation character and no identifier, stops
                dst += '%';
                dst += format;
                state = 0;
            }

        } else if (state == 2) {
            if (isIdentChar(*src)) {
                ident += *src++;
                state = 2;
            } else {
                writeIdentValue(dst, format, ident, visited, localValEnv);
                state = 0;
            }

        } else if (state == 3) {
            if (isIdentChar(*src)) {
                ident += *src++;
                state = 3;
            } else if (*src == '}') {
                writeIdentValue(dst, format, ident, visited, localValEnv);
                src++;
                state = 0;
            } else {
                // End and no identifier, stops
                dst += '%';
                dst += format;
                state = -1;
            }

        } else {
            cerr << "ASSERT : evallabel, undefined state : " << state << endl;
            faustassert(false);
        }
    }

    return dst;
}

/**
 * Iterate a parallel construction.
 *
 * Iterate a parallel construction such that :
 * par(i,10,E) --> E(i<-0),(E(i<-1),...,E(i<-9))
 * @param id the formal parameter of the iteration
 * @param num the number of iterations
 * @param body the body expression of the iteration
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree iteratePar(Tree id, int num, Tree body, Tree visited, Tree localValEnv)
{
    if (num == 0) {
        // zero iteration: return neutral circuit (0->0) for parallel composition
        return boxRoute(boxInt(0), boxInt(0), boxPar(boxInt(0), boxInt(0)));
    } else {
        Tree res = eval(body, visited, pushValueDef(id, tree(num - 1), localValEnv));
        for (int i = num - 2; i >= 0; i--) {
            res = boxPar(eval(body, visited, pushValueDef(id, tree(i), localValEnv)), res);
        }
        return res;
    }
}

/**
 * @brief Compute the neutral element for sequential composition modeled after body.
 *
 * @param id
 * @param body
 * @param visited
 * @param localValEnv
 * @return a bus: _,...,_
 */
static Tree neutralExpSeq(Tree id, Tree body, Tree visited, Tree localValEnv)
{
    // We need to find the number of inputs and outputs of body
    // We eval body with binding id to 0
    Tree res = a2sb(eval(body, visited, pushValueDef(id, tree(0), localValEnv)));

    int ins, outs;
    getBoxType(res, &ins, &outs);
    if (ins != outs) {
        stringstream error;
        error << "ERROR in seq() expressions. The iterated function must have the same number of "
                 "inputs and outputs. "
                 "Here "
              << boxpp(res) << " has " << ins << " inputs and " << outs << " outputs" << endl;
        throw faustexception(error.str());
    } else if (outs > 0) {
        Tree bus = boxWire();
        for (int j = 1; j < outs; j++) {
            bus = boxPar(bus, boxWire());
        }
        return bus;
    } else {
        return boxRoute(boxInt(0), boxInt(0), boxPar(boxInt(0), boxInt(0)));
    }
}

/**
 * Iterate a sequential construction.
 *
 * Iterate a sequential construction such that :
 * seq(i,10,E) --> E(i<-0):(E(i<-1):...:E(i<-9))
 * @param id the formal parameter of the iteration
 * @param num the number of iterations
 * @param body the body expression of the iteration
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree iterateSeq(Tree id, int num, Tree body, Tree visited, Tree localValEnv)
{
    if (num == 0) {
        Tree neutral = neutralExpSeq(id, body, visited, localValEnv);
        return neutral;
    } else {
        Tree res = eval(body, visited, pushValueDef(id, tree(num - 1), localValEnv));
        for (int i = num - 2; i >= 0; i--) {
            res = boxSeq(eval(body, visited, pushValueDef(id, tree(i), localValEnv)), res);
        }
        return res;
    }
}

/**
 * Iterate an addition construction.
 *
 * Iterate an addition construction such that :
 * par(i,10,E) --> E(i<-0)+E(i<-1)+...+E(i<-9)
 * @param id the formal parameter of the iteration
 * @param num the number of iterations
 * @param body the body expression of the iteration
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree iterateSum(Tree id, int num, Tree body, Tree visited, Tree localValEnv)
{
    if (num == 0) {
        return boxRoute(boxInt(0), boxInt(0), boxPar(boxInt(0), boxInt(0)));
    } else {
        Tree res = eval(body, visited, pushValueDef(id, tree(0), localValEnv));
        for (int i = 1; i < num; i++) {
            res = boxSeq(boxPar(res, eval(body, visited, pushValueDef(id, tree(i), localValEnv))),
                         boxPrim2(sigAdd));
        }
        return res;
    }
}

/**
 * Iterate a product construction.
 *
 * Iterate a product construction such that :
 * par(i,10,E) --> E(i<-0)*E(i<-1)*...*E(i<-9)
 * @param id the formal parameter of the iteration
 * @param num the number of iterations
 * @param body the body expression of the iteration
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return a block diagram in normal form
 */
static Tree iterateProd(Tree id, int num, Tree body, Tree visited, Tree localValEnv)
{
    if (num == 0) {
        return boxRoute(boxInt(0), boxInt(0), boxPar(boxInt(0), boxInt(0)));
    } else {
        Tree res = eval(body, visited, pushValueDef(id, tree(0), localValEnv));
        for (int i = 1; i < num; i++) {
            res = boxSeq(boxPar(res, eval(body, visited, pushValueDef(id, tree(i), localValEnv))),
                         boxPrim2(sigMul));
        }
        return res;
    }
}

/**
 * Compute the sum of outputs of a list of boxes. The sum is
 * valid if all the boxes have a valid boxType.
 *
 * @param boxlist the list of boxes
 * @param outputs sum of outputs of the boxes
 * @return true if outputs is valid, false otherwise
 */
#if 1
static bool boxlistOutputs(Tree boxlist, int* outputs)
{
    int ins, outs;

    *outputs = 0;
    while (!isNil(boxlist)) {
        Tree b = a2sb(hd(boxlist));  // For getBoxType, suppose list of evaluated boxes
        if (getBoxType(b, &ins, &outs)) {
            *outputs += outs;
        } else {
            // Arbitrary output arity set to 1
            // when can't be determined
            *outputs += 1;
        }
        boxlist = tl(boxlist);
    }
    return isNil(boxlist);
}
#else
static bool boxlistOutputs(Tree boxlist, int* outputs)
{
    int ins, outs;

    *outputs = 0;
    while (!isNil(boxlist) && getBoxType(hd(boxlist), &ins, &outs)) {
        *outputs += outs;
        boxlist = tl(boxlist);
    }
    return isNil(boxlist);
}
#endif

/**
 * Repeat a wire n times.
 */
static Tree nwires(int n)
{
    Tree l = gGlobal->nil;
    while (n--) {
        l = cons(boxWire(), l);
    }
    return l;
}

/**
 * Apply a function to a list of arguments.
 * Apply a function F to a list of arguments (a,b,c,...).
 * F can be either a closure over an abstraction, or a
 * pattern matcher. If it is not the case then we have :
 * F(a,b,c,...) ==> (a,b,c,...):F
 *
 * @param fun the function to apply
 * @param larg the list of arguments
 * @return the resulting expression in normal form
 */
static Tree applyList(Tree fun, Tree larg)
{
    Tree abstr;
    Tree globalDefEnv;
    Tree visited;
    Tree localValEnv;
    Tree envList;
    Tree originalRules;
    Tree revParamList;

    Tree id;
    Tree body;

    PM::Automaton* automat;
    int            state;

    prim2 p2;

    if (isNil(larg)) {
        return fun;
    }

    if (isBoxError(fun) || isBoxError(larg)) {
        return boxError();
    }

    if (isBoxPatternMatcher(fun, automat, state, envList, originalRules, revParamList)) {
        Tree         result;
        int          state2;
        vector<Tree> envVect;

        list2vec(envList, envVect);
        state2 = PM::apply_pattern_matcher(automat, state, hd(larg), result, envVect);
        if (state2 >= 0 && isNil(result)) {
            // We need to continue the pattern matching
            return applyList(boxPatternMatcher(automat, state2, vec2list(envVect), originalRules,
                                               cons(hd(larg), revParamList)),
                             tl(larg));
        } else if (state2 < 0) {
            stringstream error;
            error << "ERROR : pattern matching failed, no rule of " << boxpp(boxCase(originalRules))
                  << " matches argument list " << boxpp(reverse(cons(hd(larg), revParamList)))
                  << endl;
            throw faustexception(error.str());
        } else {
            // Pattern Matching was succesful
            // the result is a closure that we need to evaluate.
            if (isClosure(result, body, globalDefEnv, visited, localValEnv)) {
                // why ??? return simplifyPattern(eval(body, nil, localValEnv));
                // return eval(body, nil, localValEnv);
                return applyList(eval(body, gGlobal->nil, localValEnv), tl(larg));
            } else {
                cerr << "ERROR : wrong result from pattern matching (not a closure) : "
                     << boxpp(result) << endl;
                return boxError();
            }
        }
    }
    if (!isClosure(fun, abstr, globalDefEnv, visited, localValEnv)) {
        // principle : f(a,b,c,...) ==> (a,b,c,...):f
        int ins, outs;

        // Check arity of function
        Tree efun = a2sb(fun);
        if (!getBoxType(efun, &ins, &outs)) {  // we leave it that way for now
            // We can't determine the input arity of the expression,
            // hope for the best
            return boxSeq(larg2par(larg), fun);
        }

        // Check arity of arg list
        if (!boxlistOutputs(larg, &outs)) {
            // We don't know yet the output arity of larg. Therefore we can't
            // do any arity checking nor add _ to reach the required number of arguments
            return boxSeq(larg2par(larg), fun);
        }

        if (outs > ins) {
            stringstream error;
            error << "ERROR : too much arguments : " << outs << ", instead of : " << ins << endl;
            error << "when applying : " << boxpp(fun) << endl << "to : " << boxpp(larg) << endl;
            throw faustexception(error.str());
        }

        if ((outs == 1) && ((isBoxPrim2(fun, &p2) && (p2 != sigPrefix)) ||
                            (getUserData(fun) && ((xtended*)getUserData(fun))->isSpecialInfix()))) {
            // special case : /(3) ==> _,3 : /
            Tree larg2 = concat(nwires(ins - outs), larg);
            return boxSeq(larg2par(larg2), fun);

        } else {
            Tree larg2 = concat(larg, nwires(ins - outs));
            return boxSeq(larg2par(larg2), fun);
        }
    }

    // Here fun is a closure, we can test the content of abstr
    if (isBoxEnvironment(abstr)) {
        evalerrorbox(FAUSTfilename, -1, "an environment can't be used as a function", fun);
    }

    if (isBoxIdent(abstr)) {
        // We have an unevaluated Ident inside a closure
        Tree fff = eval(abstr, visited, localValEnv);
        return applyList(fff, larg);
    }

    if (!isBoxAbstr(abstr, id, body)) {
        evalerror(FAUSTfilename, -1, "(internal) not an abstraction inside closure (2)", fun);
    }

    // Here abstr is an abstraction, we can test the content of abstr.
    // Try to synthetise a name from the function name and the argument name
    {
        Tree arg = eval(hd(larg), visited, localValEnv);
        Tree narg;
        if (isBoxNumeric(arg, narg)) {
            arg = narg;
        }
        Tree f = eval(body, visited, pushValueDef(id, arg, localValEnv));

        Tree fname;
        if (getDefNameProperty(fun, fname)) {
            stringstream s;
            s << tree2str(fname);
            if (!gGlobal->gSimpleNames) {
                s << "(" << boxpp(arg) << ")";
            }
            setDefNameProperty(f, s.str());
        }
        return applyList(f, tl(larg));
    }
}

/**
 * Eval a list of expressions returning the list of results in reverse order.
 *
 * @param lexp list of expressions to evaluate
 * @param globalDefEnv the global environment
 * @param visited list of visited definition to detect recursive definitions
 * @param localValEnv the local environment
 * @return list of evaluated expressions in reverse order
 */
static Tree revEvalList(Tree lexp, Tree visited, Tree localValEnv)
{
    Tree result = gGlobal->nil;
    while (!isNil(lexp)) {
        result = cons(eval(hd(lexp), visited, localValEnv), result);
        lexp   = tl(lexp);
    }

    return result;
}

/**
 * Transform a list of expressions in a parallel construction.
 *
 * @param larg list of expressions
 * @return parallel construction
 */
static Tree larg2par(Tree larg)
{
    if (isNil(larg)) {
        evalerror(FAUSTfilename, -1, "empty list of arguments", larg);
    }
    if (isNil(tl(larg))) {
        return hd(larg);
    }
    return boxPar(hd(larg), larg2par(tl(larg)));
}

/**
 * Search the environment for the definition of a symbol
 * ID and evaluate it. Detects recursive definitions using
 * a set of visited IDxENV. Associates the symbol as a definition name
 * property of the definition.
 *
 * @param id the symbol ID to search
 * @param visited set of visited symbols (used for recursive definition detection)
 * @param lenv the environment where to search
 * @return the evaluated definition of ID
 */
static Tree evalIdDef(Tree id, Tree visited, Tree lenv)
{
    Tree def  = nullptr;
    Tree name = nullptr;

    // Search the environment env for a definition of symbol id
    while (!isNil(lenv) && !getProperty(lenv, id, def)) {
        faustassert(lenv->arity() > 0);
        lenv = lenv->branch(0);
    }

    // Check that the definition exists
    if (isNil(lenv)) {
        if (hasDefProp(id)) {
            stringstream error;
            error << "ERROR : " << *id << " is defined here : " << getDefFileProp(id) << ":"
                  << getDefLineProp(id) << endl;
            throw faustexception(error.str());
        } else {
            evalerror(getUseFileProp(id), getUseLineProp(id), "undefined symbol", id);
        }
    }

    // Check that it is not a recursive definition
    Tree p = cons(id, lenv);
    // Set the definition name property
    faustassert(def);
    if (!getDefNameProperty(def, name)) {
        // iIf the definition has no name use the identifier
        stringstream s;
        s << boxpp(id);
        // XXXXXX setDefNameProperty(def, s.str());
    }

    // Return the evaluated definition
    return eval(def, addElement(p, visited), gGlobal->nil);
}

/**
 * Creates a list of n elements.
 *
 * @param n number of elements
 * @param e element to be repeated
 * @return [e e e ...] n times
 */
static Tree listn(int n, Tree e)
{
    return (n <= 0) ? gGlobal->nil : cons(e, listn(n - 1, e));
}

/**
 * A property to store the pattern matcher corresponding to a set of rules
 * in a specific environement
 */
static void setPMProperty(Tree t, Tree env, Tree pm)
{
    setProperty(t, tree(gGlobal->PMPROPERTYNODE, env), pm);
}

static bool getPMProperty(Tree t, Tree env, Tree& pm)
{
    return getProperty(t, tree(gGlobal->PMPROPERTYNODE, env), pm);
}

/**
 * Eval a case expression containing a list of pattern matching rules.
 * Creates a boxPatternMatcher containing a pm autamaton a state
 * and a list of environments.
 *
 * @param rules the list of rules
 * @param env the environment uused to evaluate the patterns and closure the rhs
 * @return a boxPatternMatcher ready to be applied
 */
static Tree evalCase(Tree rules, Tree env)
{
    Tree pm;
    if (!getPMProperty(rules, env, pm)) {
        PM::Automaton* a = PM::make_pattern_matcher(evalRuleList(rules, env));
        pm = boxPatternMatcher(a, 0, listn(len(rules), pushEnvBarrier(env)), rules, gGlobal->nil);
        setPMProperty(rules, env, pm);
    }
    return pm;
}

/**
 * Evaluates each rule of the list.
 */
static Tree evalRuleList(Tree rules, Tree env)
{
    if (isNil(rules)) {
        return gGlobal->nil;
    } else {
        return cons(evalRule(hd(rules), env), evalRuleList(tl(rules), env));
    }
}

/**
 * Evaluates the list of patterns and closure the rhs.
 */
static Tree evalRule(Tree rule, Tree env)
{
    return cons(evalPatternList(left(rule), env), right(rule));
}

/**
 * Evaluates each pattern of the list.
 */
static Tree evalPatternList(Tree patterns, Tree env)
{
    if (isNil(patterns)) {
        return gGlobal->nil;
    } else {
        return cons(evalPattern(hd(patterns), env), evalPatternList(tl(patterns), env));
    }
}

/**
 * Evaluates a pattern and simplify it to numerical value
 * if possible.
 */
static Tree evalPattern(Tree pattern, Tree env)
{
    Tree p = eval(pattern, gGlobal->nil, env);
    return patternSimplification(p);
}

static void list2vec(Tree l, vector<Tree>& v)
{
    while (!isNil(l)) {
        v.push_back(hd(l));
        l = tl(l);
    }
}

static Tree vec2list(const vector<Tree>& v)
{
    Tree l = gGlobal->nil;
    int  n = (int)v.size();

    while (n--) {
        l = cons(v[n], l);
    }
    return l;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Further simplification : replace bloc-diagrams that denote constant number by this number
/////////////////////////////////////////////////////////////////////////////////////////////////////////

static Tree numericBoxSimplification(Tree box);
static Tree insideBoxSimplification(Tree box);

/**
 * boxSimplification(box) : simplify a block-diagram by replacing expressions
 * denoting a constant number by this number.
 */
static Tree boxSimplification(Tree box)
{
    Tree simplified;

    if (gGlobal->gSimplifiedBoxProperty->get(box, simplified)) {
        return simplified;

    } else {
        simplified = numericBoxSimplification(box);

        // Transfers name property if any
        Tree name;
        if (getDefNameProperty(box, name)) {
            setDefNameProperty(simplified, name);
        }

        // Attach simplified expression as a property of original box
        gGlobal->gSimplifiedBoxProperty->set(box, simplified);

        return simplified;
    }
}

/**
 * Try to do a numeric simplification of a block-diagram.
 */
static Tree numericBoxSimplification(Tree box)
{
    int    ins, outs;
    Tree   result;
    int    i;
    double x;

    if (!getBoxType(box, &ins, &outs)) {
        stringstream error;
        error << "ERROR : file " << __FILE__ << ':' << __LINE__
              << ", can't compute the box type of : ";
        error << *box << endl;
        throw faustexception(error.str());
    }

    if (ins == 0 && outs == 1) {
        // This box can potentially denote a number
        if (isBoxInt(box, &i) || isBoxReal(box, &x)) {
            result = box;
        } else {
            // Propagate signals to discover if it simplifies to a number
            int    i1;
            double x1;
            Tree   lsignals = boxPropagateSig(gGlobal->nil, box, makeSigInputList(0));
            Tree   s        = simplify(hd(lsignals));

            if (isSigReal(s, &x1)) {
                result = boxReal(x1);
            } else if (isSigInt(s, &i1)) {
                result = boxInt(i1);
            } else {
                result = insideBoxSimplification(box);
            }
        }
    } else {
        // This box can't denote a number
        result = insideBoxSimplification(box);
    }
    return result;
}

/**
 *  Simplify inside a block-diagram : S[A*B] => S[A]*S[B]
 */
static Tree insideBoxSimplification(Tree box)
{
    int    i;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    Tree t1, t2, ff, label, cur, min, max, step, type, name, file, slot, body;
    Tree ins, outs, routes;

    xtended* xt = (xtended*)getUserData(box);

    // Extended Primitives
    if (xt) {
        return box;
    }

    // Numbers and Constants
    else if (isBoxInt(box, &i)) {
        return box;
    } else if (isBoxReal(box, &r)) {
        return box;
    }

    else if (isBoxFConst(box, type, name, file)) {
        return box;
    }

    else if (isBoxFVar(box, type, name, file)) {
        return box;
    }

    // Wire and Cut
    else if (isBoxCut(box)) {
        return box;
    }

    else if (isBoxWire(box)) {
        return box;
    }

    // Primitives
    else if (isBoxPrim0(box, &p0)) {
        return box;
    }

    else if (isBoxPrim1(box, &p1)) {
        return box;
    }

    else if (isBoxPrim2(box, &p2)) {
        return box;
    }

    else if (isBoxPrim3(box, &p3)) {
        return box;
    }

    else if (isBoxPrim4(box, &p4)) {
        return box;
    }

    else if (isBoxPrim5(box, &p5)) {
        return box;
    }

    else if (isBoxFFun(box, ff)) {
        return box;
    }

    // User Interface Widgets
    else if (isBoxButton(box, label)) {
        return box;
    }

    else if (isBoxCheckbox(box, label)) {
        return box;
    }

    else if (isBoxVSlider(box, label, cur, min, max, step)) {
        return box;
    }

    else if (isBoxHSlider(box, label, cur, min, max, step)) {
        return box;
    }

    else if (isBoxNumEntry(box, label, cur, min, max, step)) {
        return box;
    }

    else if (isBoxVBargraph(box, label, min, max)) {
        return box;
    }

    else if (isBoxHBargraph(box, label, min, max)) {
        return box;
    }

    // User Interface Groups
    else if (isBoxVGroup(box, label, t1)) {
        return boxVGroup(label, boxSimplification(t1));
    }

    else if (isBoxHGroup(box, label, t1)) {
        return boxHGroup(label, boxSimplification(t1));
    }

    else if (isBoxTGroup(box, label, t1)) {
        return boxTGroup(label, boxSimplification(t1));
    }

    // Slots and Symbolic Boxes
    else if (isBoxSlot(box)) {
        return box;
    }

    else if (isBoxSymbolic(box, slot, body)) {
        Tree b = boxSimplification(body);
        return boxSymbolic(slot, b);
    }

    // Block Diagram Composition Algebra
    else if (isBoxSeq(box, t1, t2)) {
        Tree s1 = boxSimplification(t1);
        Tree s2 = boxSimplification(t2);
        return boxSeq(s1, s2);
    }

    else if (isBoxPar(box, t1, t2)) {
        Tree s1 = boxSimplification(t1);
        Tree s2 = boxSimplification(t2);
        return boxPar(s1, s2);
    }

    else if (isBoxSplit(box, t1, t2)) {
        Tree s1 = boxSimplification(t1);
        Tree s2 = boxSimplification(t2);
        return boxSplit(s1, s2);
    }

    else if (isBoxMerge(box, t1, t2)) {
        Tree s1 = boxSimplification(t1);
        Tree s2 = boxSimplification(t2);
        return boxMerge(s1, s2);
    }

    else if (isBoxRec(box, t1, t2)) {
        Tree s1 = boxSimplification(t1);
        Tree s2 = boxSimplification(t2);
        return boxRec(s1, s2);
    }

    else if (isBoxMetadata(box, t1, t2)) {
        Tree s1 = boxSimplification(t1);
        return boxMetadata(s1, t2);

    }

    else if (isBoxWaveform(box)) {
        // A waveform is always in Normal Form, nothing to simplify
        return box;
    }

    else if (isBoxRoute(box, ins, outs, routes)) {
        Tree s1 = boxSimplification(ins);
        Tree s2 = boxSimplification(outs);
        return boxRoute(s1, s2, routes);
    }

    cerr << "ASSERT : in file " << __FILE__ << ':' << __LINE__
         << ", unrecognised box expression : " << *box << endl;
    faustassert(false);
    return nullptr;
}
