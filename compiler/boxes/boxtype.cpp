/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

/*****************************************************************************
******************************************************************************

                              Box Type System

******************************************************************************
*****************************************************************************/

/**\file boxtype.cpp
 * \author Yann Orlarey
 * \version 1.0
 * \date 2003
 * \brief A simple type system for block diagram expressions.
 *  The type of a block diagram is defined by a number of inputs and outputs.
 */

#include <stdio.h>
#include <string.h>
#include "boxes.hh"
#include "exception.hh"
#include "global.hh"
#include "names.hh"
#include "ppbox.hh"
#include "prim2.hh"
#include "xtended.hh"

static bool infereBoxType(Tree box, int* inum, int* onum);

/**
 * Return the type (number of inputs and outputs) of a box or false if undefined
 * \param box the box we want to know the type
 * \param inum the place to return the number of inputs
 * \param onum the place to return the number of outputs
 * \return true if type is defined, false if undefined
 */

bool getBoxType(Tree box, int* inum, int* onum)
{
    Tree t;
    if (getProperty(box, gGlobal->BOXTYPEPROP, t)) {
        if (isNil(t)) {
            return false;
        } else {
            *inum = hd(t)->node().getInt();
            *onum = tl(t)->node().getInt();
            return true;
        }

    } else {
        if (infereBoxType(box, inum, onum)) {
            setProperty(box, gGlobal->BOXTYPEPROP, cons(tree(*inum), tree(*onum)));
            return true;
        } else {
            setProperty(box, gGlobal->BOXTYPEPROP, gGlobal->nil);
            return false;
        }
    }
}


/**
 * Produces "1 output" or "n outputs" according to n
 * \param n: the number of outputs
 * \return the corresponding string
 */

static string outputs(int n)
{
    stringstream msg;
    msg << n << ((n == 1) ? " output" : " outputs");
    return msg.str();
}


/**
 * Produces "1 input" or "n inputs" according to n
 * \param n: the number of inputs
 * \return the corresponding string
 */

static string inputs(int n)
{
    stringstream msg;
    msg << n << ((n == 1) ? " input" : " inputs");
    return msg.str();
}

/**
 * Compute a parametric type error message
 * \param a: the LHS expression
 * \param b: the RHS expression
 * \param o: the number of outputs of a
 * \param i: the number of inputs of b
 * \param opcode = the composition operation sign
 * \param opname = the full name of the composition operation
 * \param msg  = indication for the user (ie " must be equals to ")
 * \return the error message as a string
 */

static string computeTypeErrorMessage(Tree a, Tree b, int o, int i, const string opcode, const string opname,
                                      const string msg)
{
    stringstream error;
    string       aStr("A"), bStr("B");
    Tree         aID, bID;
    if (getDefNameProperty(a, aID)) aStr = tree2str(aID);
    if (getDefNameProperty(b, bID)) bStr = tree2str(bID);
    error << "ERROR in " << opname << " " << aStr << opcode << bStr << endl
          << "The number of outputs [" << o << "] of " << aStr << msg << "the number of inputs [" << i << "] of "
          << bStr << endl
          << endl
          << "Here  " << aStr << " = " << boxpp(a) << "; has " << outputs(o) << endl
          << "while " << bStr << " = " << boxpp(b) << "; has " << inputs(i) << endl;
    return error.str();
}


/**
 * Compute a parametric type error message for recursions
 * \param a: the LHS expression
 * \param b: the RHS expression
 * \param u: the number of inputs of a
 * \param v: the number of outputs of a
 * \param x: the number of inputs of b
 * \param y: the number of outputs of b
 * \return the error message as a string
 */

static string computeTypeRecErrorMessage(Tree a, Tree b, int u, int v, int x, int y)
{
    stringstream msg;
    string       aStr("A"), bStr("B");
    Tree         aID, bID;

    if (getDefNameProperty(a, aID)) aStr = tree2str(aID);
    if (getDefNameProperty(b, bID)) bStr = tree2str(bID);

    
    msg << "ERROR in recursive composition " << aStr << '~' << bStr << endl;
    if (v < x)
        msg << "The number of outputs [" << v << "] of " << aStr << " must be at least the number of inputs [" << x << "] of " << bStr << ". ";
    if (u < y)
        msg << "The number of inputs [" << u << "] of " << aStr << " must be at least the number of outputs [" << y << "] of " << bStr << ". ";

    msg << endl << endl << "Here  " << aStr << " = " << boxpp(a) << "; has " << inputs(u) << " and " << outputs(v) << "," << endl << "while " << bStr << " = " << boxpp(b) << "; has " << inputs(x) << " and " << outputs(y) << "." << endl;
    return msg.str();
}

/**
 * Infere the type (number of inputs and outputs) of a box.
 * The box expression is assumed to be in 'propagation normal form'
 * that is to have been evaluated and residual abstractions to have been
 * converted to symbolic boxes (using a2sb()).
 * \param box the box we want to know the type
 * \param inum the place to return the number of inputs
 * \param onum the place to return the number of outputs
 * \return true if the box expression has a type
 */

static bool infereBoxType(Tree t, int* inum, int* onum)
{
    Tree a, b, ff, l, s, c, ins, outs, lroutes;
    // Tree abstr, genv, vis, lenv;

    xtended* p = (xtended*)getUserData(t);

    if (p) {
        *inum = p->arity();
        *onum = 1;
    } else if (isBoxInt(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxReal(t)) {
        *inum = 0;
        *onum = 1;
    }

    else if (isBoxWaveform(t)) {
        *inum = 0;
        *onum = 2;
    }

    else if (isBoxWire(t)) {
        *inum = 1;
        *onum = 1;
    } else if (isBoxCut(t)) {
        *inum = 1;
        *onum = 0;
    }

    else if (isBoxSlot(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxSymbolic(t, s, b)) {
        if (!getBoxType(b, inum, onum)) return false;
        *inum += 1;
    }

    else if (isBoxPatternVar(t, a)) {
        return false;
    }

    else if (isBoxPrim0(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxPrim1(t)) {
        *inum = 1;
        *onum = 1;
    } else if (isBoxPrim2(t)) {
        *inum = 2;
        *onum = 1;
    } else if (isBoxPrim3(t)) {
        *inum = 3;
        *onum = 1;
    } else if (isBoxPrim4(t)) {
        *inum = 4;
        *onum = 1;
    } else if (isBoxPrim5(t)) {
        *inum = 5;
        *onum = 1;
    }

    else if (isBoxFFun(t, ff)) {
        *inum = ffarity(ff);
        *onum = 1;
    } else if (isBoxFConst(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxFVar(t)) {
        *inum = 0;
        *onum = 1;
    }

    else if (isBoxButton(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxCheckbox(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxVSlider(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxHSlider(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxNumEntry(t)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxVGroup(t, l, a)) {
        return getBoxType(a, inum, onum);
    } else if (isBoxHGroup(t, l, a)) {
        return getBoxType(a, inum, onum);
    } else if (isBoxTGroup(t, l, a)) {
        return getBoxType(a, inum, onum);
    }

    else if (isBoxVBargraph(t)) {
        *inum = 1;
        *onum = 1;
    } else if (isBoxHBargraph(t)) {
        *inum = 1;
        *onum = 1;
    } else if (isBoxSoundfile(t, l, c)) {
        *inum = 2;
        *onum = 2 + tree2int(c);
    } else if (isBoxSeq(t, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;

        if (v != x) {
            throw faustexception(
                computeTypeErrorMessage(a, b, v, x, ":", "sequential composition", " must be equals to "));
        } else {
            *inum = u;
            *onum = y;
        }

    } else if (isBoxPar(t, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;

        *inum = u + x;
        *onum = v + y;

    } else if (isBoxSplit(t, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;

        if ((v == 0) || (x == 0) || (x % v != 0)) {
            throw faustexception(
                (computeTypeErrorMessage(a, b, v, x, "<:", "split composition", " must be a divisor of ")));
        }

        *inum = u;
        *onum = y;

    } else if (isBoxMerge(t, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;

        if ((v == 0) || (x == 0) || (v % x != 0)) {
            throw faustexception(
                computeTypeErrorMessage(a, b, v, x, ":>", "merge composition", " must be a multiple of "));
        }

        *inum = u;
        *onum = y;

    } else if (isBoxRec(t, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;
        if ((x > v) || (y > u)) {
            throw faustexception(computeTypeRecErrorMessage(a, b, u, v, x, y));
        }
        *inum = max(0, u - y);
        *onum = v;

    } else if (isBoxEnvironment(t)) {
        *inum = 0;
        *onum = 0;

    } else if (isBoxMetadata(t, a, b)) {
        return getBoxType(a, inum, onum);

    } else if (isBoxRoute(t, ins, outs, lroutes)) {
        return isBoxInt(ins, inum) & isBoxInt(outs, onum);

    } else {
        stringstream error;
        error << "boxType() internal error : unrecognized box expression " << boxpp(t) << endl;
        throw faustexception(error.str());
    }
    return true;
}
