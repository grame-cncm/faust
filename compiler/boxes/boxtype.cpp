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
 * The type of a block diagram is defined by a number of inputs and outputs.
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

using namespace std;

static bool inferBoxType(Tree box, int* inum, int* onum);

/**
 * Return the type (number of inputs and outputs) of a box or false if undefined
 * \param box the box we want to know the type
 * \param inum the place to return the number of inputs
 * \param onum the place to return the number of outputs
 * \return true if type is defined, false if undefined
 */

LIBFAUST_API bool getBoxType(Tree box, int* inum, int* onum)
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
        if (inferBoxType(box, inum, onum)) {
            setProperty(box, gGlobal->BOXTYPEPROP, cons(tree(*inum), tree(*onum)));
            return true;
        } else {
            setProperty(box, gGlobal->BOXTYPEPROP, gGlobal->nil);
            return false;
        }
    }
}

/**
 * Compute a parametric type error message
 * \param a the LHS expression
 * \param b the RHS expression
 * \param o the number of outputs of a
 * \param i the number of inputs of b
 * \param opcode the composition operation sign
 * \param opname the full name of the composition operation
 * \param msg indication for the user (ie " must be equal to ")
 * \return the error message as a string
 */

static string computeTypeErrorMessage(Tree a, Tree b, int o, int i, const string& opcode, const string& opname,
                                    const string& msg)
{
    stringstream error;
    string       aStr("A"), bStr("B");
    Tree         aID, bID;
    
    if (getDefNameProperty(a, aID)) aStr = tree2str(aID);
    if (getDefNameProperty(b, bID)) bStr = tree2str(bID);
      
    error << "ERROR : " << opname << " " << aStr << opcode << bStr << endl
          << "The number of outputs [" << o << "] of " << aStr << msg << "the number of inputs [" << i << "] of "
          << bStr << endl << endl
          << "Here  " << aStr << " = " << mBox(a, MAX_ERROR_SIZE) << ";" << endl << "has " << outputs(o) << endl << endl
          << "while " << bStr << " = " << mBox(b, MAX_ERROR_SIZE) << ";" << endl << "has " << inputs(i) << endl;
    return error.str();
}

/**
 * Compute a parametric type error message for recursions
 * \param a the LHS expression
 * \param b the RHS expression
 * \param u the number of inputs of a
 * \param v the number of outputs of a
 * \param x the number of inputs of b
 * \param y the number of outputs of b
 * \return the error message as a string
 */

static string computeTypeRecErrorMessage(Tree a, Tree b, int u, int v, int x, int y)
{
    stringstream error;
    string       aStr("A"), bStr("B");
    Tree         aID, bID;

    if (getDefNameProperty(a, aID)) aStr = tree2str(aID);
    if (getDefNameProperty(b, bID)) bStr = tree2str(bID);
    
    error << "ERROR : recursive composition " << aStr << '~' << bStr << endl;
    if (v < x)
        error << "The number of outputs [" << v << "] of " << aStr << " must be at least the number of inputs [" << x << "] of " << bStr << ". ";
    if (u < y)
        error << "The number of inputs [" << u << "] of " << aStr << " must be at least the number of outputs [" << y << "] of " << bStr << ". " << endl << endl;

    error << "Here  " << aStr << " = " << mBox(a, MAX_ERROR_SIZE) << ";" << endl << "has " << inputs(u) << " and " << outputs(v) << endl << endl
          << "while " << bStr << " = " << mBox(b, MAX_ERROR_SIZE) << ";" << endl << "has " << inputs(x) << " and " << outputs(y) << endl;
    return error.str();
}

/**
 * Infer the type (number of inputs and outputs) of a box.
 * The box expression is assumed to be in 'propagation normal form'
 * that is to have been evaluated and residual abstractions to have been
 * converted to symbolic boxes (using a2sb()).
 * \param box the box we want to know the type
 * \param inum the place to return the number of inputs
 * \param onum the place to return the number of outputs
 * \return true if the box expression has a type
 */

static bool inferBoxType(Tree box, int* inum, int* onum)
{
    Tree a, b, ff, l, s, c, ins, outs, lroutes;
    // Tree abstr, genv, vis, lenv;

    xtended* p = (xtended*)getUserData(box);

    if (p) {
        *inum = p->arity();
        *onum = 1;
    } else if (isBoxInt(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxReal(box)) {
        *inum = 0;
        *onum = 1;
    }

    else if (isBoxWaveform(box)) {
        *inum = 0;
        *onum = 2;
    }

    else if (isBoxWire(box)) {
        *inum = 1;
        *onum = 1;
    } else if (isBoxCut(box)) {
        *inum = 1;
        *onum = 0;
    }

    else if (isBoxSlot(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxSymbolic(box, s, b)) {
        if (!getBoxType(b, inum, onum)) return false;
        *inum += 1;
    }

    else if (isBoxPatternVar(box, a)) {
        return false;
    }

    else if (isBoxPrim0(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxPrim1(box)) {
        *inum = 1;
        *onum = 1;
    } else if (isBoxPrim2(box)) {
        *inum = 2;
        *onum = 1;
    } else if (isBoxPrim3(box)) {
        *inum = 3;
        *onum = 1;
    } else if (isBoxPrim4(box)) {
        *inum = 4;
        *onum = 1;
    } else if (isBoxPrim5(box)) {
        *inum = 5;
        *onum = 1;
    }

    else if (isBoxFFun(box, ff)) {
        *inum = ffarity(ff);
        *onum = 1;
    } else if (isBoxFConst(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxFVar(box)) {
        *inum = 0;
        *onum = 1;
    }

    else if (isBoxButton(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxCheckbox(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxVSlider(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxHSlider(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxNumEntry(box)) {
        *inum = 0;
        *onum = 1;
    } else if (isBoxVGroup(box, l, a)) {
        return getBoxType(a, inum, onum);
    } else if (isBoxHGroup(box, l, a)) {
        return getBoxType(a, inum, onum);
    } else if (isBoxTGroup(box, l, a)) {
        return getBoxType(a, inum, onum);
    }

    else if (isBoxVBargraph(box)) {
        *inum = 1;
        *onum = 1;
    } else if (isBoxHBargraph(box)) {
        *inum = 1;
        *onum = 1;
    } else if (isBoxSoundfile(box, l, c)) {
        *inum = 2;
        *onum = 2 + tree2int(c);
    } else if (isBoxSeq(box, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;

        if (v != x) {
            throw faustexception(
                computeTypeErrorMessage(a, b, v, x, ":", "sequential composition", " must be equal to "));
        } else {
            *inum = u;
            *onum = y;
        }

    } else if (isBoxPar(box, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;

        *inum = u + x;
        *onum = v + y;

    } else if (isBoxSplit(box, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;

        if ((v == 0) || (x == 0) || (x % v != 0)) {
            throw faustexception(
                (computeTypeErrorMessage(a, b, v, x, "<:", "split composition", " must be a divisor of ")));
        }

        *inum = u;
        *onum = y;

    } else if (isBoxMerge(box, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;

        if ((v == 0) || (x == 0) || (v % x != 0)) {
            throw faustexception(
                computeTypeErrorMessage(a, b, v, x, ":>", "merge composition", " must be a multiple of "));
        }

        *inum = u;
        *onum = y;

    } else if (isBoxRec(box, a, b)) {
        int u, v, x, y;
        if (!getBoxType(a, &u, &v)) return false;
        if (!getBoxType(b, &x, &y)) return false;
        if ((x > v) || (y > u)) {
            throw faustexception(computeTypeRecErrorMessage(a, b, u, v, x, y));
        }
        *inum = std::max(0, u - y);
        *onum = v;

    } else if (isBoxEnvironment(box)) {
        *inum = 0;
        *onum = 0;

    } else if (isBoxMetadata(box, a, b)) {
        return getBoxType(a, inum, onum);

    } else if (isBoxRoute(box, ins, outs, lroutes)) {
        return isBoxInt(ins, inum) && isBoxInt(outs, onum);

    } else {
        stringstream error;
        error << "boxType() internal error : unrecognized box expression " << boxpp(box) << endl;
        throw faustexception(error.str());
    }
    return true;
}
