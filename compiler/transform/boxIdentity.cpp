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

#include "boxIdentity.hh"

#include <stdlib.h>
#include <cstdlib>
#include <map>
#include "Text.hh"
#include "global.hh"
#include "ppbox.hh"
#include "property.hh"
#include "tlib.hh"
#include "tree.hh"
#include "treeTransform.hh"

//-------------------------BoxIdentity-------------------------------
// An identity transformation on boxes. Can be used to test
// that everything works, and as a pattern for real transformations.
//----------------------------------------------------------------------

void BoxIdentity::traceEnter(Tree t)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << boxpp(t) << endl;
}

void BoxIdentity::traceExit(Tree t, Tree r)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << boxpp(t) << " => " << boxpp(r) << endl;
}

/**
 * @brief Transformation of evaluated boxe expressions
 *
 * @param box expression
 * @return transformed box
 */
Tree BoxIdentity::transformation(Tree box)
{
    int    i, id;
    double r;
    prim0  p0;
    prim1  p1;
    prim2  p2;
    prim3  p3;
    prim4  p4;
    prim5  p5;

    Tree t1, t2, ff, label, cur, min, max, step, type, name, file, body,
        slot, chan, ins, outs, lroutes;


    xtended *xt = (xtended *)getUserData(box);

    // primitive elements
    if (xt)
        return box;
    else if (isBoxInt(box, &i))
        return box;
    else if (isBoxReal(box, &r))
        return box;
    else if (isBoxCut(box))
        return box;
    else if (isBoxWire(box))
        return box;
    else if (isBoxPrim0(box, &p0))
        return box;
    else if (isBoxPrim1(box, &p1))
        return box;
    else if (isBoxPrim2(box, &p2))
        return box;
    else if (isBoxPrim3(box, &p3))
        return box;
    else if (isBoxPrim4(box, &p4))
        return box;
    else if (isBoxPrim5(box, &p5))
        return box;

    // foreign elements
    else if (isBoxFFun(box, ff)) {
        return box;
    } else if (isBoxFConst(box, type, name, file))
        return box;
    else if (isBoxFVar(box, type, name, file))
        return box;

    // block diagram binary operator
    else if (isBoxSeq(box, t1, t2))
        return boxSeq(self(t1), self(t2));
    else if (isBoxSplit(box, t1, t2))
        return boxSplit(self(t1), self(t2));
    else if (isBoxMerge(box, t1, t2))
        return boxMerge(self(t1), self(t2));
    else if (isBoxPar(box, t1, t2))
        return boxPar(self(t1), self(t2));
    else if (isBoxRec(box, t1, t2))
        return boxRec(self(t1), self(t2));

    // on demand
    else if (isBoxOndemand(box, t1))
        return box;

    // UI elements
    else if (isBoxButton(box, label))
        return box;
    else if (isBoxCheckbox(box, label))
        return box;
    else if (isBoxVSlider(box, label, cur, min, max, step)) {
        return boxVSlider(label, self(cur), self(min), self(max), self(step));
    } else if (isBoxHSlider(box, label, cur, min, max, step)) {
        return boxHSlider(label, self(cur), self(min), self(max), self(step));
    } else if (isBoxNumEntry(box, label, cur, min, max, step)) {
        return boxNumEntry(label, self(cur), self(min), self(max), self(step));
    }
    // UI groups
    else if (isBoxVGroup(box, label, t1)) {
        return boxVGroup(label, self(t1));
    } else if (isBoxHGroup(box, label, t1)) {
        return boxHGroup(label, self(t1));
    } else if (isBoxTGroup(box, label, t1)) {
        return boxTGroup(label, self(t1));
    }
    // UI bargraphs
    else if (isBoxHBargraph(box, label, min, max)) {
        return boxHBargraph(label, self(min), self(max));
    } else if (isBoxMetadata(box, t1, t2)) {
        return box;
    } else if (isBoxVBargraph(box, label, min, max)) {
        return boxVBargraph(label, self(min), self(max));

        // soundfiles and waveforms
    } else if (isBoxSoundfile(box, label, chan)) {
        return box;
    } else if (isBoxWaveform(box)) {
        return box;
    }

    // routing
    else if (isBoxSlot(box, &id)) {
        return box;
    } else if (isBoxSymbolic(box, slot, body)) {
        return boxSymbolic(slot, self(body));
    } else if (isBoxRoute(box, ins, outs, lroutes)) {
        return box;
    }

    // errors
    else if (isBoxError(box)) {
        stringstream error;
        error << "ERROR : we got an error box : " << *box << endl;
        std::cerr << error.str() << std::endl;
        throw faustexception(error.str());
    }

    else {
        stringstream error;
        error << "ERROR : unrecognized box : " << *box << endl;
        std::cerr << error.str() << std::endl;
        throw faustexception(error.str());
    }
    return 0;
}
