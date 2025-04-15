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

#include "boxModulationImplanter.hh"
#include "boxIdentity.hh"
#include "labels.hh"

#include <stdlib.h>
#include <cstdlib>

#include "Text.hh"
#include "global.hh"
#include "ppbox.hh"
#include "signals.hh"

using namespace std;

//-------------------------BoxModulationImplanter--------------------------------
// A box transformer that rewrites a circuit to modulate a widget designated
// by a path and according to a modulation circuit.
//----------------------------------------------------------------------

/**
 * @brief Checks if all elements of a given path are present in a label in the same order.
 *
 * This function verifies whether all elements of the `path` are contained in the `wLabel`
 * in the same order, but not necessarily consecutively. The `wLabel` can contain additional
 * elements before, between, or after the elements of the `path`.
 *
 * For example:
 * - `path = (b, d, e)` and `wLabel = (a, b, c, d, e, f)` will return `true`.
 * - `path = (b, d, e)` and `wLabel = (a, b, c, e, d, f)` will return `false`
 *   because the order of elements in `path` is not preserved in `wLabel`.
 *
 * @param path The sequence of elements to match (a linked list-like structure).
 * @param wLabel The sequence in which to search for the elements of `path` (a linked list-like
 * structure).
 * @return `true` if all elements of `path` are found in `wLabel` in the same order, otherwise
 * `false`.
 */

static bool isPathMatchingLabel(Tree path, Tree wLabel)
{
    // we need to find all elements of path in label
    // in the same order
    // std::cerr << "isPathMatchingLabel (";
    // std::cerr << "path = " << *path << "; wLabel = " << *wLabel << ") -> ";
    while (path != gGlobal->nil) {
        if (wLabel == gGlobal->nil) {
            // wLabel is exhausted before path
            // => path and label do not match
            // std::cerr << " NO" << std::endl;
            return false;
        }

        // search for s in wLabel
        Tree s = hd(path);
        while ((wLabel != gGlobal->nil) && (s != hd(wLabel))) {
            wLabel = tl(wLabel);
        }

        if (wLabel == gGlobal->nil) {
            // s wat not found => path and label do not match
            // std::cerr << " NO" << std::endl;
            return false;
        }
        // s was found, we continue
        wLabel = tl(wLabel);
        path   = tl(path);
    }
    // all elements of path were found in label
    // in the same order => path and label match
    // std::cerr << " YES" << std::endl;
    return true;
}

/**
 * @brief Implant a modulation circuit around a widget matching a given path.
 *
 * @param widget The widget to modulate if it matches the path
 * @param wLabel The path we are looking for
 * @return Tree The widget either untouched or with the modulation circuit around it
 */
Tree BoxModulationImplanter::implantWidgetIfMatch(Tree widget, Tree wLabel)
{
    Tree wPath = superNormalizePath(cons(wLabel, gGlobal->nil));
    // std::cerr << "BoxModulationImplanter::implantWidgetIfMatch"
    //           << " fPath = " << *fPath << "; wPath = " << *wPath << ";  wLabel = " << *wLabel
    //           << std::endl;
    if (!isPathMatchingLabel(fPath, wPath)) {
        return widget;  // not the widget we are looking therefore no transformation
    }

    // std::cerr << "We have a MATCH! " << std::endl;
    // We have a matching widget to modulate. Depending on the number of inputs
    // of the modulation circuit we have three cases to consider:
    switch (fInputsNumber) {
        case 0:
            // The modulation circuit has no input, it fully replaces the widget
            return fModCircuit;
        case 1:
            // The modulation circuit has one input, we connect the widget thru it
            return boxSeq(widget, fModCircuit);
        default:
            faustassert(fInputsNumber == 2);
            // The modulation circuit has two inputs. The second one it is used to
            // modulate the widget with an external signal
            return boxSeq(boxPar(widget, fSlot), fModCircuit);
    }
}

/**
 * @brief Implant inside a UI group. If the group label matches the top of path,
 * we remove it from the path before proceeding
 *
 * @param gcode the group code: 0,1, or 2
 * @param glabel the group label
 * @param x the circuit inside the group
 * @return Tree the transformed circuit
 */
Tree BoxModulationImplanter::implantInsideGroup(int gcode, Tree glabel, Tree x)
{
    Tree gPath = superNormalizePath(cons(cons(tree(gcode), glabel), gGlobal->nil));
    // std::cerr << "BoxModulationImplanter::implantInsideGroup"
    //           << " fPath = " << *fPath << "; gPath = " << *gPath << std::endl;
    // Transform group label into a path
    // check if fPath is in this group
    Tree rpath;
    if (matchGroup(gPath, fPath, rpath)) {
        // rewrite x accordingly
        BoxModulationImplanter bm(rpath, fSlot, fInputsNumber, fModCircuit);
        return bm.self(x);
    } else {
        // we are flexible and accept any group
        return self(x);
    }
}

/**
 * @brief The main transformation function
 *
 * @param box the box to transform
 * @return Tree the transformed box
 */
Tree BoxModulationImplanter::transformation(Tree box)
{
    Tree x, y, z, c, label;

    // // MODULATION
    // if (isBoxModulation(box, x, y)) {
    //     return boxModulation(self(x), self(y));
    // }

    // // UI WIDGETS
    // else

    if (isBoxButton(box, label)) {
        return implantWidgetIfMatch(box, label);
    } else if (isBoxCheckbox(box, label)) {
        return implantWidgetIfMatch(box, label);
    } else if (isBoxVSlider(box, label, c, x, y, z)) {
        return implantWidgetIfMatch(boxVSlider(label, self(c), self(x), self(y), self(z)), label);
    } else if (isBoxHSlider(box, label, c, x, y, z)) {
        return implantWidgetIfMatch(boxHSlider(label, self(c), self(x), self(y), self(z)), label);
    } else if (isBoxNumEntry(box, label, c, x, y, z)) {
        return implantWidgetIfMatch(boxNumEntry(label, self(c), self(x), self(y), self(z)), label);
    } else if (isBoxVBargraph(box, label, x, y)) {
        return implantWidgetIfMatch(boxVBargraph(label, self(x), self(y)), label);
    } else if (isBoxHBargraph(box, label, x, y)) {
        return implantWidgetIfMatch(boxHBargraph(label, self(x), self(y)), label);
    }

    // UI GROUPS
    else if (isBoxVGroup(box, label, x)) {
        return boxVGroup(label, implantInsideGroup(0, label, x));
    } else if (isBoxHGroup(box, label, x)) {
        return boxHGroup(label, implantInsideGroup(1, label, x));
    } else if (isBoxTGroup(box, label, x)) {
        return boxTGroup(label, implantInsideGroup(2, label, x));
    }

    // EVALUATED BOXES SHOULD BE COMPLETE

    else {
        return BoxIdentity::transformation(box);
    }
    return 0;
}
