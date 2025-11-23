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

#include <iostream>
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "recursiveness.hh"
#include "sigRecursivenessChecker.hh"
#include "sigTransform.hh"
#include "signals.hh"

using namespace std;

/**
 * @brief Identity transformation that checks all signals have recursiveness annotations
 *
 * This is a debugging transformation that doesn't modify the signal tree
 * but verifies that every signal visited has a valid recursiveness annotation.
 */
class RecursivenessChecker : public RewriteRule {
   public:
    string getRuleName() const override { return "RecursivenessChecker"; }

    optional<Tree> applyRule(Tree signal) override
    {
        // Check if signal has a recursiveness annotation
        Tree recProp;
        if (!getProperty(signal, gGlobal->RECURSIVNESS, recProp)) {
            cerr << "ERROR: Signal without RECURSIVNESS detected!" << endl;
            cerr << "  Signal ptr: " << signal << endl;
            cerr << "  Signal: " << ppsig(signal, 200) << endl;

            // Try to identify the signal type
            int  i;
            Tree x, y, z;

            if (isProj(signal, &i, x)) {
                cerr << "  Signal is proj(" << i << ", rec_group)" << endl;
                cerr << "  Rec group ptr: " << x << endl;
                Tree xRecProp;
                cerr << "  Rec group has recursiveness? "
                     << (getProperty(x, gGlobal->RECURSIVNESS, xRecProp) ? "YES" : "NO") << endl;
            }

            // Don't assert, just report to see ALL signals without recursiveness
        }

        // Return nullopt = no transformation, just checking
        return nullopt;
    }
};

/**
 * @brief Check that all signals in the tree have recursiveness annotations
 *
 * @param siglist The signal list to check
 * @return Tree The same signal list (identity transformation)
 */
Tree checkAllSignalsHaveRecursiveness(Tree siglist)
{
    fprintf(stderr, "\n\n************ RECURSIVNESS CHECKER CALLED ************\n\n");
    cerr << "\n=== Starting recursiveness checking traversal ===" << endl;

    Normalize normalize(RecursivenessChecker{});

    // Use sigListTransform which will visit all signals recursively
    Tree result = sigListTransform(normalize, siglist, true);

    cerr << "=== Recursiveness checking complete ===" << endl;

    // Result should be identical to input since RecursivenessChecker never transforms
    faustassert(result == siglist);

    return siglist;
}
