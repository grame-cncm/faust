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

#include "sigDegenerateRecursionElimination.hh"
#include <iostream>
#include "global.hh"
#include "ppsig.hh"
#include "rewriteRule.hh"
#include "ruleAtom.hh"
#include "sigTransform.hh"
#include "signals.hh"

using namespace std;

class InlineRec : public RewriteRule {
    const std::set<Tree>& fDegenerate;  // set of degenerate recursion to inline
   public:
    virtual string getRuleName() const { return "REC"; }
    InlineRec(const std::set<Tree>& degenerate) : fDegenerate(degenerate) {}
    virtual optional<Tree> operator()(Tree signal)
    {
        // Xi @ 0 -> def(Xi) if Xi is a degenerate recursion
        // Xi @ d -> def(Xi) @ d if Xi is a degenerate recursion and d > 0
        if (Tree r, d, def; isSigDelay(signal, r, d) && hasProjDefinition(r, def) &&
                            (fDegenerate.find(r) != fDegenerate.end())) {
            if (isZero(d)) {
                return def;  // case Xi @ 0 -> def(Xi)
            } else {
                return sigDelay(def, d);  // case Xi @ d -> def(Xi) @ d
            }

        } else {
            return nullopt;  // no transformation
        }
    }
};

class InlineClkRec : public RewriteRule {
    const std::set<Tree>& fDegenerate;  // set of degenerate recursion to inline
   public:
    virtual string getRuleName() const { return "CLKREC"; }
    InlineClkRec(const std::set<Tree>& degenerate) : fDegenerate(degenerate) {}
    virtual optional<Tree> operator()(Tree sig)
    {
        // Xi @ 0 -> def(Xi) if Xi is a degenerate recursion
        // Xi @ d -> def(Xi) @ d if Xi is a degenerate recursion and d > 0
        if (Tree r, d, h, def;
            input(sig) >> delayed(d) >> clocked(h) >> recursive(def) >> output(r) &&
            (fDegenerate.find(r) != fDegenerate.end())) {
            if (isZero(d)) {
                return def;  // case Xi @ 0 -> def(Xi)
            } else {
                return sigDelay(def, d);  // case Xi @ d -> def(Xi) @ d
            }

        } else {
            return nullopt;  // no transformation
        }
    }
};

class CombineDelays : public RewriteRule {
   public:
    virtual string         getRuleName() const { return "DLY"; }
    virtual optional<Tree> operator()(Tree signal)
    {
        // (X@d2)@d1 -> X@(d1+d2)
        // clock(H,X@d2)@d1 -> clock(H,X)@(d1+d2)
        if (Tree x, d1; isSigDelay(signal, x, d1) /*&& isNum(d1)*/) {
            // (X@d2)@d1 -> X@(d1+d2)
            if (Tree z, d2; isSigDelay(x, z, d2)) {
                // Combine two delays into one
                if (int i, j; isSigInt(d1, &i) && isSigInt(d2, &j)) {
                    return sigDelay(z, sigInt(i + j));
                } else {
                    std::cerr << "PB1 ADDING DELAYS " << ppsig(d1) << ", " << ppsig(d2) << "\n";
                }
                return sigDelay(z, sigAdd(d1, d2));  // (X@d2)@d1 -> X@(d1+d2)
            }

            // clock(H,X@d1)@d2 -> clock(H,X)@(d1+d2)
            if (Tree h, y, z, d2; isSigClocked(x, h, y) && isSigDelay(y, z, d2)) {
                // Combine clocked signal with delay
                if (Tree z, d2; isSigDelay(x, z, d2)) {
                    // Combine two delays into one
                    if (int i, j; isSigInt(d1, &i) && isSigInt(d2, &j)) {
                        return sigClocked(h, sigDelay(z, sigInt(i + j)));
                    } else {
                        std::cerr << "PB2 ADDING DELAYS " << ppsig(d1) << ", " << ppsig(d2) << "\n";
                    }
                    return sigClocked(h, sigDelay(z, sigAdd(d1, d2)));  // (X@d2)@d1 -> X@(d1+d2)
                }
            }
        }

        return nullopt;  // no transformation
    }
};

class CombineClockDelays : public RewriteRule {
   public:
    virtual string         getRuleName() const { return "CDL"; }
    virtual optional<Tree> operator()(Tree signal)
    {
        if (Tree h1, h2, d1, d2, x, y, z, w; isSigClocked(signal, h1, x) && isSigDelay(x, y, d1) &&
                                             isSigClocked(y, h2, z) && isSigDelay(z, w, d2) &&
                                             (h1 == h2)) {
            if (int i, j; isSigInt(d1, &i) && isSigInt(d2, &j)) {
                return sigClocked(h1, sigDelay(w, sigInt(i + j)));
            }
            if (int j; isSigInt(d2, &j)) {
                return sigClocked(h1, sigDelay(w, sigAdd(d1, d2)));
            }
        }
        return nullopt;  // no transformation
    }
};

//------------------------------------------------------------------------------
// CombineClockDelaysAtom: Same rule using ruleAtom system
//------------------------------------------------------------------------------
class CombineClockDelaysAtom : public RewriteRule {
   public:
    virtual string         getRuleName() const { return "CDL_ATOM"; }
    virtual optional<Tree> operator()(Tree sig)
    {
        // p::in(sig) >> p::clk(h1) >> p::dl(d1) >> p::clk(h2) >> p::dl(d2) >> p::out(w)
        if (Tree h1, h2, d1, d2, w;
            input(sig) >> clocked(h1) >> delayed(d1) >> clocked(h2) >> delayed(d2) >> output(w) &&
            (h1 == h2)) {
            // Same logic as original
            if (int i, j; isSigInt(d1, &i) && isSigInt(d2, &j)) {
                return sigClocked(h1, sigDelay(w, sigInt(i + j)));
            }
            if (int j; isSigInt(d2, &j)) {
                return sigClocked(h1, sigDelay(w, sigAdd(d1, d2)));
            }
        }
        return nullopt;  // no transformation
    }
};

//-------------------------inline Degenerate Recursions-------------------------------
// Eliminates degenerate recursive projections by replacing them with their definitions.
//------------------------------------------------------------------------------------
Tree inlineDegenerateRecursions(Tree siglist, bool trace)
{
    // compute the list of degenerated recursins that can be replaced by their definition
    std::set<Tree> DR = analyzeDegenerateRecursions(recursionGraph(siglist));
    // Normalize      N(InlineRec{DR}, InlineClkRec{DR}, CombineDelays(), CombineClockDelaysAtom());
    Normalize N(InlineRec{DR});

    N.setDebugLevel(DebugLevel::NONE);

    return sigListTransform(N, siglist);
}
