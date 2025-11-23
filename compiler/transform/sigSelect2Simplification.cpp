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

#include "sigSelect2Simplification.hh"
#include "rewriteRule.hh"
#include "sigTransform.hh"
#include "signals.hh"
#include "sigtyperules.hh"

using namespace std;

class SimplifySelect2 : public RewriteRule {
   public:
    virtual string getRuleName() const override { return "SELECT2"; }

    virtual optional<Tree> applyRule(Tree signal) override
    {
        Tree sel, s1, s2;
        if (!isSigSelect2(signal, sel, s1, s2)) {
            return nullopt;
        }

        // Case 1: Both branches are identical → return the branch
        if (s1 == s2) {
            return s1;
        }

        // Case 2 & 3: Analyze selector interval
        Type tsel = getSigType(sel);
        if (tsel) {
            interval ivsel = tsel->getInterval();

            // Case 2: selector interval is [0, 0] → always s1
            if (ivsel.isZero()) {
                return s1;
            }

            // Case 3: selector interval doesn't contain 0 → always s2
            if (!ivsel.hasZero()) {
                return s2;
            }
        }

        // No simplification possible
        return nullopt;
    }
};

//------------------------------------------------------------------------------
// simplifySelect2: Apply SimplifySelect2 rule to a signal list
//------------------------------------------------------------------------------
Tree simplifySelect2(Tree siglist, bool trace)
{
    Normalize N(SimplifySelect2{});

    if (trace) {
        N.setDebugLevel(DebugLevel::BASIC);
    } else {
        N.setDebugLevel(DebugLevel::NONE);
    }

    return sigListTransform(N, siglist);
}
