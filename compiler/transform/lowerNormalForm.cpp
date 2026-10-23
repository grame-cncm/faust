/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
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

#include "lowerNormalForm.hh"

#include <map>

#include "global.hh"
#include "sigIdentity.hh"
#include "signals.hh"
#include "sigtyperules.hh"

namespace {

class SignalLowering : public SignalIdentity {
    // the groups of the result, a fresh one for each group met (sig -> its new node)
    std::map<Tree, Tree> fGroups;

   public:
    // the generators of the tables too : their content is a signal of the normal form
    SignalLowering() { fVisitGen = true; }

   protected:
    // the zero of the nature of sig
    static Tree zeroOf(Tree sig)
    {
        return (getCertifiedSigType(sig)->nature() == kInt) ? sigInt(0) : sigReal(0.0);
    }

    // a fresh recursive group of one signal y, its definition computed by def(y) ; the
    // signal is read as y@0, the read of a projection in the normal form
    template <class Def>
    static Tree recursion(Def def)
    {
        Tree var = tree(unique("L"));
        Tree y   = sigProj(0, ref(var));
        Tree d   = def(y);
        rec(var, list1(d));
        return sigDelay(y, sigInt(0));
    }

    Tree transformation(Tree sig) override
    {
        Tree var, le;
        if (isRec(sig, var, le)) {
            // A group becomes a new group : redefining it in place would change a tree that
            // the memoized recursion plans (getRecPlan) take as immutable, and a group that
            // the lowering adds in its body would belong to no plan
            if (auto it = fGroups.find(sig); it != fGroups.end()) {
                return it->second;
            }
            Tree nvar    = tree(unique("LR"));
            Tree group   = ref(nvar);
            fGroups[sig] = group;
            rec(nvar, mapselfRec(le));
            return group;
        }
        if (tvec subs; isSigSum(sig, subs)) {
            // the chain of the node, a negated term subtracted
            Tree acc = nullptr;
            for (Tree t : subs) {
                if (isZero(t)) {
                    continue;
                }
                Tree a;
                bool sub = isSigNeg(t, a) && acc != nullptr;
                Tree x   = self(sub ? a : t);
                acc      = (acc == nullptr) ? x : (sub ? sigSub(acc, x) : sigAdd(acc, x));
            }
            return (acc == nullptr) ? zeroOf(sig) : acc;
        }
        if (tvec fs; isSigProd(sig, fs)) {
            Tree acc = nullptr;
            for (Tree f : fs) {
                Tree x = self(f);
                acc    = (acc == nullptr) ? x : sigMul(acc, x);
            }
            return acc;
        }
        if (Tree x; isSigNeg(sig, x)) {
            Tree z = zeroOf(sig);
            return sigSub(z, self(x));
        }
        if (tvec cs; isSigFIR(sig, cs)) {
            // c1 * x + c2 * x@1 + ... : the coefficients after the source, from delay 0 ;
            // a projection, the bare source of a kernel, is read as x@0
            Tree x   = self(cs[0]);
            int  i;
            Tree g;
            const bool proj = isProj(x, &i, g);
            Tree acc = nullptr;
            for (size_t k = 1; k < cs.size(); k++) {
                if (isZero(cs[k])) {
                    continue;
                }
                Tree c   = self(cs[k]);
                Tree tap = (k == 1 && !proj) ? x : sigDelay(x, sigInt(int(k) - 1));
                Tree term = isOne(c) ? tap : sigMul(c, tap);
                acc       = (acc == nullptr) ? term : sigAdd(acc, term);
            }
            return (acc == nullptr) ? zeroOf(sig) : acc;
        }
        if (tvec cs; isSigIIR(sig, cs)) {
            // y = x + c1 * y@1 + c2 * y@2 + ...
            Tree x = self(cs[0]);
            tvec c;
            for (size_t k = 1; k < cs.size(); k++) {
                c.push_back(self(cs[k]));
            }
            return recursion([&](Tree y) {
                Tree acc = x;
                for (size_t k = 0; k < c.size(); k++) {
                    if (isZero(c[k])) {
                        continue;
                    }
                    Tree tap  = sigDelay(y, sigInt(int(k) + 1));
                    Tree term = isOne(c[k]) ? tap : sigMul(c[k], tap);
                    acc       = sigAdd(acc, term);
                }
                return acc;
            });
        }
        if (Tree tx, tp; isSigIRM(sig, tx, tp)) {
            // y = mix(p, x, y@1) = x + p * (y@1 - x)
            Tree x = self(tx);
            Tree p = self(tp);
            return recursion([&](Tree y) {
                Tree prev = sigDelay(y, sigInt(1));
                Tree dif  = sigSub(prev, x);
                return sigAdd(x, sigMul(p, dif));
            });
        }
        if (Tree tc, ta, tb; isSigMix(sig, tc, ta, tb)) {
            // mix(c, a, b) = a + c * (b - a)
            Tree c   = self(tc);
            Tree a   = self(ta);
            Tree b   = self(tb);
            Tree dif = sigSub(b, a);
            return sigAdd(a, sigMul(c, dif));
        }
        if (Tree tx; isSigFrac(sig, tx)) {
            Tree x = self(tx);
            return sigSub(x, sigFloor(x));
        }
        if (Tree tx; isSigCfrac(sig, tx)) {
            Tree x = self(tx);
            return sigSub(x, sigRint(x));
        }
        if (Tree tx; isSigTpt(sig, tx)) {
            // x / (x + 1)
            Tree x = self(tx);
            Tree d = sigAdd(x, sigReal(1.0));
            return sigDiv(x, d);
        }
        if (Tree tx, tp; isSigPhase(sig, tx, tp)) {
            // (x % p) / p, in reals
            Tree x = self(tx);
            Tree p = self(tp);
            Tree r = sigRem(x, p);
            if (getCertifiedSigType(tx)->nature() == kInt && getCertifiedSigType(tp)->nature() == kInt) {
                Tree fr = sigFloatCast(r);
                return sigDiv(fr, sigFloatCast(p));
            }
            return sigDiv(r, p);
        }
        if (Tree tx; isSigBpf(sig)) {
            // x < t1 ? r0 : (x < t2 ? r1 : ... rn)
            tvec t, r;
            isSigBpf(sig, tx, t, r);
            Tree x = self(tx);
            tvec st, sr;
            for (Tree ti : t) st.push_back(self(ti));
            for (Tree ri : r) sr.push_back(self(ri));
            Tree acc = sr.back();
            for (size_t k = t.size(); k-- > 0;) {
                Tree cond = sigLT(x, st[k]);
                acc       = sigSelect2(cond, acc, sr[k]);
            }
            return acc;
        }
        return SignalIdentity::transformation(sig);
    }
};

}  // namespace

Tree lowerNormalForm(Tree L)
{
    SignalLowering lowering;
    Tree           R = lowering.mapself(L);
    typeAnnotation(R, gGlobal->gLocalCausalityCheck);
    return R;
}
