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

/**
 * @file normalform.cpp
 * @brief Implementation of complete signal normalization to normal form
 * 
 * This file implements the highest-level interface for signal normalization,
 * combining all optimization techniques into a unified process. The complete
 * normalization process includes:
 * 
 * 1. De Bruijn to symbolic recursion conversion
 * 2. Type annotation and analysis
 * 3. UI range constraint generation  
 * 4. Mathematical function typing
 * 5. Signal simplification and algebraic optimization
 * 6. Type promotion and casting
 * 7. Final cleanup and validation
 * 
 * This produces signals in complete normal form, ready for efficient
 * code generation by subsequent compiler phases.
 * 
 * @see normalform.hh for public interface documentation
 * @see simplify.cpp for algebraic simplification implementation
 */

#include <stdio.h>
#include <map>

#include "global.hh"
#include "ppbox.hh"
#include "ppsig.hh"
#include "sigPromotion.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "timing.hh"
#include "tree.hh"

using namespace std;

/*****************************************************************************
 * IMPLEMENTATION 
 *****************************************************************************/

/**
 * @brief Internal helper function for complete signal normalization.
 * 
 * This function implements the core normalization pipeline, applying
 * all optimization and type analysis steps in the correct order.
 * Each step is timed for performance analysis.
 * 
 * @param LS Input signal list to normalize
 * @return Completely normalized signal list
 */
static Tree simplifyToNormalFormAux(Tree LS)
{
    // Step 1: Convert deBruijn recursion into symbolic recursion
    // This transforms recursive references from numeric indices to symbolic names
    startTiming("deBruijn2Sym");
    Tree L1 = deBruijn2Sym(LS);
    endTiming("deBruijn2Sym");

    // Step 2: Annotate signals with type information
    // Performs type inference and causality checking
    startTiming("L1 typeAnnotation");
    typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
    endTiming("L1 typeAnnotation");

    // Step 3: Generate range constraints for UI elements (optional)
    if (gGlobal->gRangeUI) {
        // Generate safe values for range UI items (sliders and nentry)
        startTiming("Safe values for range UI items");
        L1 = signalUIPromote(L1);
        endTiming("Safe values for range UI items");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    if (gGlobal->gFreezeUI) {
        // Freeze range UI items (sliders and nentry)to their init value
        startTiming("Freeze values for range UI items");
        L1 = signalUIFreezePromote(L1);
        endTiming("Freeze values for range UI items");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    if (gGlobal->gFTZMode > 0) {
        // Wrap real signals with FTZ
        startTiming("FTZ on recursive signals");
        L1 = signalFTZPromote(L1);
        endTiming("FTZ on recursive signals");

        // Annotate L1 with type information
        startTiming("L1 typeAnnotation");
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
        endTiming("L1 typeAnnotation");
    }

    // Auto differentiation
    if (gGlobal->gAutoDifferentiate) {
        L1 = signalAutoDifferentiate(L1);
        typeAnnotation(L1, gGlobal->gLocalCausalityCheck);
    }

    // Needed before 'simplify' (see sigPromotion.hh)
    startTiming("Cast and Promotion");
    Tree L2 = signalPromote(L1);
    endTiming("Cast and Promotion");

    // Simplify by executing every computable operation
    startTiming("L2 simplification");
    Tree L3 = simplify(L2);
    endTiming("L2 simplification");

    // Annotate L3 with type information
    startTiming("L3 typeAnnotation");
    typeAnnotation(L3, gGlobal->gLocalCausalityCheck);
    endTiming("L3 typeAnnotation");

    startTiming("Cast and Promotion");
    Tree L4 = signalPromote(L3);
    endTiming("Cast and Promotion");

    startTiming("L4 typeAnnotation");
    typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
    endTiming("L4 typeAnnotation");

    // Must be done after simplification so that 'size' signal is properly simplified to a constant
    if (gGlobal->gCheckTable) {
        // Check and generate safe access to rdtable/rwtable
        startTiming("Safe access to rdtable/rwtable");
        L4 = signalTablePromote(L4);
        endTiming("Safe access to rdtable/rwtable");

        // Annotate L4 with type information
        startTiming("L4 typeAnnotation");
        typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
        endTiming("L4 typeAnnotation");
    }

    if (gGlobal->gCheckIntRange) {
        // Check and generate safe float to integer range conversion
        startTiming("Safe float to integer conversion");
        L4 = signalIntCastPromote(L4);
        endTiming("Safe float to integer conversion");

        // Annotate L4 with type information
        startTiming("L4 typeAnnotation");
        typeAnnotation(L4, gGlobal->gLocalCausalityCheck);
        endTiming("L4 typeAnnotation");
    }

    // Check signal tree
    startTiming("L4 signalChecker");
    SignalChecker checker(L4);
    endTiming("L4 signalChecker");
    return L4;
}

// Public API
LIBFAUST_API Tree simplifyToNormalForm(Tree sig)
{
    if (isList(sig)) {
        Tree t2 = sig->getProperty(gGlobal->NORMALFORM);
        if (!t2) {
            t2 = simplifyToNormalFormAux(sig);
            sig->setProperty(gGlobal->NORMALFORM, t2);
        }
        return t2;
    } else {
        return simplifyToNormalForm(cons(sig, gGlobal->nil));
    }
}

LIBFAUST_API tvec simplifyToNormalForm2(tvec siglist)
{
    tvec res;
    for (const auto& it : siglist) {
        res.push_back(simplifyToNormalForm(it));
    }
    return res;
}

LIBFAUST_API string printSignal(Tree sig, bool shared, int max_size)
{
    // Clear print state
    gGlobal->clear();
    stringstream str;
    if (shared) {
        ppsigShared(sig, str, max_size);
    } else {
        str << ppsig(sig, max_size) << endl;
    }
    return str.str();
}

LIBFAUST_API string printBox(Tree box, bool shared, int max_size)
{
    // Clear print state
    gGlobal->clear();
    stringstream str;
    if (shared) {
        boxppShared(box, str);
    } else {
        str << mBox(box, max_size) << endl;
    }
    return str.str();
}
