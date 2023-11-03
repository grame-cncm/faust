/************************************************************************
 ************************************************************************
    FAUST compiler, boxIdentity source code
    Copyright (C) 2023 INRIA
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

#include "boxIdentity.hh"

#include <stdlib.h>
#include <cstdlib>

#include "Text.hh"
#include "global.hh"
#include "ppbox.hh"
#include "signals.hh"

using namespace std;

//-------------------------BoxIdentity----------------------------------
// An identity transformation on 'flat' box circuits, after evaluation.
//----------------------------------------------------------------------

void BoxIdentity::traceEnter(Tree t)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << boxpp(t, MAX_ERROR_SIZE) << endl;
}

void BoxIdentity::traceExit(Tree t, Tree r)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << boxpp(t, MAX_ERROR_SIZE) << " => " << boxpp(r, MAX_ERROR_SIZE) << endl;
}

Tree BoxIdentity::transformation(Tree box)
{
    int    i;
    double r;
    Tree   x, y, z, c, slot, body, label;

    // GENERATORS
    if (isBoxInt(box, &i)) {
        return box;
    } else if (isBoxReal(box, &r)) {
        return box;
    } else if (isBoxWaveform(box)) {
        return box;
    } else if (isBoxSoundfile(box)) {
        return box;
    }

    // ROUTING
    else if (isBoxRoute(box, x, y, z)) {
        return box;
    } else if (isBoxWire(box)) {
        return box;
    } else if (isBoxCut(box)) {
        return box;
    }

    // SLOTS AND SYMBOLIC BOXES
    else if (isBoxSlot(box)) {
        return box;
    } else if (isBoxSymbolic(box, slot, body)) {
        return boxSymbolic(self(slot), self(body));
    }

    // COMPOSITION ALGEBRA
    else if (isBoxSeq(box, x, y)) {
        return boxSeq(self(x), self(y));
    } else if (isBoxPar(box, x, y)) {
        return boxPar(self(x), self(y));
    } else if (isBoxRec(box, x, y)) {
        return boxRec(self(x), self(y));
    } else if (isBoxSplit(box, x, y)) {
        return boxSplit(self(x), self(y));
    } else if (isBoxMerge(box, x, y)) {
        return boxMerge(self(x), self(y));
    }

    // MODULATION
    else if (isBoxModulation(box, x, y)) {
        return boxModulation(self(x), self(y));
    }

    // PRIMITIVE OPERATIONS
    else if (isBoxPrim0(box)) {
        return box;
    } else if (isBoxPrim1(box)) {
        return box;
    } else if (isBoxPrim2(box)) {
        return box;
    } else if (isBoxPrim3(box)) {
        return box;
    } else if (isBoxPrim4(box)) {
        return box;
    } else if (isBoxPrim5(box)) {
        return box;
    }

    // FOREIGN FUNCTIONS
    else if (isBoxFFun(box)) {
        return box;
    } else if (isBoxFConst(box)) {
        return box;
    } else if (isBoxFVar(box)) {
        return box;
    }

    // UI WIDGETS
    else if (isBoxButton(box, label)) {
        return box;
    } else if (isBoxCheckbox(box, label)) {
        return box;
    } else if (isBoxVSlider(box, label, c, x, y, z)) {
        return boxVSlider(label, self(c), self(x), self(y), self(z));
    } else if (isBoxHSlider(box, label, c, x, y, z)) {
        return boxHSlider(label, self(c), self(x), self(y), self(z));
    } else if (isBoxNumEntry(box, label, c, x, y, z)) {
        return boxNumEntry(label, self(c), self(x), self(y), self(z));
    } else if (isBoxVBargraph(box, label, x, y)) {
        return boxVBargraph(label, self(x), self(y));
    } else if (isBoxHBargraph(box, label, x, y)) {
        return boxHBargraph(label, self(x), self(y));
    }

    // UI GROUPS
    else if (isBoxVGroup(box, label, x)) {
        return boxVGroup(label, self(x));
    } else if (isBoxHGroup(box, label, x)) {
        return boxHGroup(label, self(x));
    } else if (isBoxTGroup(box, label, x)) {
        return boxTGroup(label, self(x));
    }

    // Other boxes here should be extended primitives
    return box;
}
