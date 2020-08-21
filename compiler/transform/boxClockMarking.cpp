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

#include "boxClockMarking.hh"

#include <stdlib.h>
#include <cstdlib>
#include <map>
#include "Text.hh"
#include "global.hh"
#include "names.hh"
#include "ppbox.hh"
#include "property.hh"
#include "tlib.hh"
#include "tree.hh"
#include "treeTransform.hh"
#include "xtended.hh"

//-------------------------BoxClockMarking------------------------------
// An identity transformation on boxes. Can be used to test
// that everything works, and as a pattern for real transformations.
//----------------------------------------------------------------------
BoxClockMarking::BoxClockMarking()
{
    fClkSlot = boxSlot(++gGlobal->gBoxSlotNumber);
    setDefNameProperty(fClkSlot, subst("CLK$0", T(++gGlobal->gBoxClockNumber)));

    fClkDownSampler = boxSeq(boxPar(boxWire(), fClkSlot), gGlobal->gDownsamplingPrim->box());
    fClkSync        = boxSeq(boxPar(boxWire(), fClkSlot), gGlobal->gClocksyncPrim->box());
    fClkUpSampler   = boxSeq(boxPar(boxWire(), fClkSlot), boxPrim2(sigUpsampling));
}

Tree BoxClockMarking::clockSlot()
{
    return fClkSlot;
}

Tree BoxClockMarking::clockPrefix(Tree box)
{
    int ins  = 0;
    int outs = 0;
    getBoxType(box, &ins, &outs);
    if (ins > 0) {
        Tree parsampler = fClkDownSampler;
        for (int i = 1; i < ins; i++) {
            parsampler = boxPar(fClkDownSampler, parsampler);
        }
        return boxSeq(parsampler, box);
    } else {
        // strange no inputs, therfore nothing to prefix
        return box;
    }
}

Tree BoxClockMarking::clockSync(Tree box)
{
    int ins  = 0;
    int outs = 0;
    getBoxType(box, &ins, &outs);
    if (ins > 0) {
        Tree parsampler = fClkSync;
        for (int i = 1; i < ins; i++) {
            parsampler = boxPar(fClkSync, parsampler);
        }
        return boxSeq(parsampler, box);
    } else {
        // strange no inputs, therfore nothing to prefix
        return box;
    }
}

Tree BoxClockMarking::clockPostfix(Tree box)
{
    int ins  = 0;
    int outs = 0;
    getBoxType(box, &ins, &outs);
    if (outs > 0) {
        Tree parsampler = fClkUpSampler;
        for (int i = 1; i < outs; i++) {
            parsampler = boxPar(fClkUpSampler, parsampler);
        }
        return boxSeq(box, parsampler);
    } else {
        // strange no inputs, therfore nothing to prefix
        return box;
    }
}

/**
 * @brief Transformation sync to clock some box expressions
 *
 * @param box expression
 * @return transformed box
 */
Tree BoxClockMarking::transformation(Tree box)
{
    prim1 p1;
    prim2 p2;

    Tree t1, t2;

    if (isBoxPrim1(box, &p1) && (p1 == &sigDelay1))
        return clockSync(box);
    else if (isBoxPrim2(box, &p2) && (p2 == &sigFixDelay))
        return boxSeq(boxPar(fClkSync, boxWire()), box);
    else if (isBoxRec(box, t1, t2))
        return boxRec(self(t1), clockSync(self(t2)));
    else
        return BoxIdentity::transformation(box);
}
