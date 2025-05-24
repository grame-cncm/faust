/************************************************************************
 ************************************************************************
    FAUST compiler, boxVisitor source code
    Copyright (C) 2025 GRAME
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

#include "boxVisitor.hh"

#include <stdlib.h>
#include <cstdlib>

using namespace std;

//-------------------------BoxVisitor---------------------------
// An identity visit on 'flat' box circuits, after evaluation.
//--------------------------------------------------------------

void BoxVisitor::visit(Tree box)
{
    int    i;
    double r;
    Tree   x, y, z, c, slot, body, label;

    // GENERATORS
    if (isBoxInt(box, &i)) {
        return;
    } else if (isBoxReal(box, &r)) {
        return;
    } else if (isBoxWaveform(box)) {
        return;
    } else if (isBoxSoundfile(box)) {
        return;
    }

    // ROUTING
    else if (isBoxRoute(box, x, y, z)) {
        return;
    } else if (isBoxWire(box)) {
        return;
    } else if (isBoxCut(box)) {
        return;
    }

    // SLOTS AND SYMBOLIC BOXES
    else if (isBoxSlot(box)) {
        return;
    } else if (isBoxSymbolic(box, slot, body)) {
        self(slot);
        self(body);
        return;
    }

    // COMPOSITION ALGEBRA
    else if (isBoxSeq(box, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isBoxPar(box, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isBoxRec(box, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isBoxSplit(box, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isBoxMerge(box, x, y)) {
        self(x);
        self(y);
        return;
    }

    // MODULATION
    else if (isBoxModulation(box, x, y)) {
        self(x);
        self(y);
        return;
    }

    // PRIMITIVE OPERATIONS
    else if (isBoxPrim0(box)) {
        return;
    } else if (isBoxPrim1(box)) {
        return;
    } else if (isBoxPrim2(box)) {
        return;
    } else if (isBoxPrim3(box)) {
        return;
    } else if (isBoxPrim4(box)) {
        return;
    } else if (isBoxPrim5(box)) {
        return;
    }

    // FOREIGN FUNCTIONS
    else if (isBoxFFun(box)) {
        return;
    } else if (isBoxFConst(box)) {
        return;
    } else if (isBoxFVar(box)) {
        return;
    }

    // UI WIDGETS
    else if (isBoxButton(box, label)) {
        return;
    } else if (isBoxCheckbox(box, label)) {
        return;
    } else if (isBoxVSlider(box, label, c, x, y, z)) {
        self(c);
        self(x);
        self(y);
        self(z);
        return;
    } else if (isBoxHSlider(box, label, c, x, y, z)) {
        self(c);
        self(x);
        self(y);
        self(z);
        return;
    } else if (isBoxNumEntry(box, label, c, x, y, z)) {
        self(c);
        self(x);
        self(y);
        self(z);
        return;
    } else if (isBoxVBargraph(box, label, x, y)) {
        self(x);
        self(y);
        return;
    } else if (isBoxHBargraph(box, label, x, y)) {
        self(x);
        self(y);
        return;
    }

    // UI GROUPS
    else if (isBoxVGroup(box, label, x)) {
        self(x);
        return;
    } else if (isBoxHGroup(box, label, x)) {
        self(x);
        return;
    } else if (isBoxTGroup(box, label, x)) {
        self(x);
        return;
    }
}
