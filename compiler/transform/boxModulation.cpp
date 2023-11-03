/************************************************************************
 ************************************************************************
    FAUST compiler, boxModulation source code
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

#include "boxModulation.hh"
#include "boxIdentity.hh"
#include "labels.hh"

#include <stdlib.h>
#include <cstdlib>

#include "Text.hh"
#include "global.hh"
#include "ppbox.hh"
#include "signals.hh"

using namespace std;

//-------------------------BoxModulation--------------------------------
// Rewrite a circuit to modulate a slider designated by a path
//----------------------------------------------------------------------

Tree BoxModulation::modulateIfMatch(Tree widget, Tree wLabel)
{
    Tree wPath = superNormalizePath(cons(wLabel, gGlobal->nil));
    // std::cerr << "BoxModulation::modulateIfMatch"
    //           << " fPath = " << *fPath << " widget path = " << *wPath << std::endl;
    if (fPath == wPath) {
        return boxSeq(boxPar(widget, fSlot), boxPrim2(sigMul));
    } else {
        return widget;
    }
}

Tree BoxModulation::modulateIfSameGroup(int gcode, Tree glabel, Tree x)
{
    Tree gPath = superNormalizePath(cons(cons(tree(gcode), glabel), gGlobal->nil));
    // std::cerr << "BoxModulation::modulateIfSameGroup"
    //           << " gPath = " << *gPath << " fPath = " << *fPath << std::endl;
    // Transform group label into a path
    // check if fPath is in this group
    Tree rpath;
    if (matchGroup(gPath, fPath, rpath)) {
        // rewrite x accordingly
        BoxModulation bm(rpath, fSlot);
        return bm.self(x);
    } else {
        // we are flexible and accept any group
        return self(x);
    }
}

Tree BoxModulation::transformation(Tree box)
{
    Tree x, y, z, c, label;

    // MODULATION
    if (isBoxModulation(box, x, y)) {
        return boxModulation(self(x), self(y));
    }

    // UI WIDGETS
    else if (isBoxButton(box, label)) {
        return modulateIfMatch(box, label);
    } else if (isBoxCheckbox(box, label)) {
        return modulateIfMatch(box, label);
    } else if (isBoxVSlider(box, label, c, x, y, z)) {
        return modulateIfMatch(boxVSlider(label, self(c), self(x), self(y), self(z)), label);
    } else if (isBoxHSlider(box, label, c, x, y, z)) {
        return modulateIfMatch(boxHSlider(label, self(c), self(x), self(y), self(z)), label);
    } else if (isBoxNumEntry(box, label, c, x, y, z)) {
        return modulateIfMatch(boxNumEntry(label, self(c), self(x), self(y), self(z)), label);
    } else if (isBoxVBargraph(box, label, x, y)) {
        return modulateIfMatch(boxVBargraph(label, self(x), self(y)), label);
    } else if (isBoxHBargraph(box, label, x, y)) {
        return modulateIfMatch(boxHBargraph(label, self(x), self(y)), label);
    }

    // UI GROUPS
    else if (isBoxVGroup(box, label, x)) {
        return boxVGroup(label, modulateIfSameGroup(0, label, x));
    } else if (isBoxHGroup(box, label, x)) {
        return boxHGroup(label, modulateIfSameGroup(1, label, x));
    } else if (isBoxTGroup(box, label, x)) {
        return boxTGroup(label, modulateIfSameGroup(2, label, x));
    }

    // EVALUATED BOXES SHOULD BE COMPLETE

    else {
        return BoxIdentity::transformation(box);
    }
    return 0;
}
