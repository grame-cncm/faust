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

#include "sigTypeChecker.hh"
#include "sigTransform.hh"
#include "sigtyperules.hh"
#include "signals.hh"
#include "ppsig.hh"
#include <iostream>

using namespace std;

/**
 * @brief Identity transformation that checks all signals have types
 *
 * This is a debugging transformation that doesn't modify the signal tree
 * but verifies that every signal visited has a valid type annotation.
 */
class TypeChecker : public RewriteRule {
public:
    string getRuleName() const override { return "TypeChecker"; }

    optional<Tree> applyRule(Tree signal) override {
        // Check if signal has a type
        Type ty = getSigType(signal);
        if (!ty) {
            cerr << "ERROR: Signal without type detected!" << endl;
            cerr << "  Signal ptr: " << signal << endl;
            cerr << "  Signal: " << ppsig(signal, 200) << endl;

            // Try to identify the signal type
            int i;
            Tree x, y, z;

            if (isProj(signal, &i, x)) {
                cerr << "  Signal is proj(" << i << ", rec_group)" << endl;
                cerr << "  Rec group ptr: " << x << endl;
                Type xType = getSigType(x);
                cerr << "  Rec group has type? " << (xType ? "YES" : "NO") << endl;

                // Check the rec group's body
                Tree var, body;
                if (isRec(x, var, body)) {
                    cerr << "  Rec var: " << var << endl;
                    cerr << "  Rec body: " << body << endl;
                }
            }

            // Don't assert, just return nullopt to continue
            // This allows us to see ALL signals without types
        }

        // Return nullopt = no transformation, just checking
        return nullopt;
    }
};

/**
 * @brief Check that all signals in the tree have types
 *
 * @param siglist The signal list to check
 * @return Tree The same signal list (identity transformation)
 */
Tree checkAllSignalsHaveTypes(Tree siglist)
{
    fprintf(stderr, "\n\n************ TYPE CHECKER CALLED ************\n\n");
    cerr << "\n=== Starting type checking traversal ===" << endl;

    Normalize normalize(TypeChecker{});

    // Use sigListTransform which will visit all signals recursively
    Tree result = sigListTransform(normalize, siglist, true);

    cerr << "=== Type checking complete ===" << endl;

    // Result should be identical to input since TypeChecker never transforms
    faustassert(result == siglist);

    return siglist;
}
