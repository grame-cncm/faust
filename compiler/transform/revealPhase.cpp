/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

/**
 * revealPhase : a product holding W and 1/P, W the remainder x % P of the same P, is
 * written with phase(x, P) = (x % P) / P. Read as two independent values, W in
 * [0, Pmax - 1] divided by P in [Pmin, Pmax] loses that W stays below P : the ratio of a
 * counter ba.period(P) by its period could reach Pmax / Pmin instead of 1. W is the
 * remainder itself, or a counter W = x % P (a recursion whose definition is the
 * remainder) read at delay 0 ; a product k * W of integers (k a number) is taken when
 * the types prove it does not wrap. A constant P is left alone : the interval of W / P
 * is then exact.
 *
 * Runs on typed signals (the types of the original side decide), after the normal form.
 */

#include "revealPhase.hh"
#include <optional>
#include <unordered_map>
#include "global.hh"
#include "rewrite.hh"
#include "sigtyperules.hh"
#include "signals.hh"
#include "xtended.hh"

namespace {

/// r is the remainder x % p : the integer remainder, or fmod of reals
bool remainderOf(Tree r, Tree& x, Tree& p)
{
    int op;
    if (isSigBinOp(r, &op, x, p) && op == kRem) {
        return true;
    }
    if (r->arity() == 2 && getUserData(r) == static_cast<void*>(gGlobal->gFmodPrim)) {
        x = r->branch(0);
        p = r->branch(1);
        return true;
    }
    return false;
}

/// t is a remainder x % p, or a counter whose definition is one, read at delay 0
bool remainderValue(Tree t, Tree& x, Tree& p)
{
    Tree u, d, rgroup, var, le;
    int  i;
    if (isSigDelay(t, u, d) && isZero(d)) {
        t = u;
    }
    if (isProj(t, &i, rgroup) && isRec(rgroup, var, le) && le != nullptr && !isNil(le)) {
        t = nth(le, i);
    }
    return remainderOf(t, x, p);
}

/// f is W, float(W) or float(k * W) (k an integer number, no wrap) with W a remainder value
bool phaseNumerator(Tree f, Tree& x, Tree& p, int& k)
{
    Tree u, a, b;
    int  op;
    k = 1;
    if (!isSigFloatCast(f, u)) {
        return remainderValue(f, x, p);
    }
    if (remainderValue(u, x, p)) {
        return true;
    }
    tvec fs;
    Tree w = nullptr;
    if (isSigProd(u, fs) && fs.size() == 2 && isSigInt(fs[0], &k)) {
        w = fs[1];
    } else if (isSigBinOp(u, &op, a, b) && op == kMul && isSigInt(a, &k)) {
        w = b;
    }
    if (w == nullptr || !remainderValue(w, x, p)) {
        return false;
    }
    // k * W in int32 : the types of W must prove the product exact
    interval iw = sigInterval(w);
    double   m  = std::max(std::abs(iw.lo()), std::abs(iw.hi())) * std::abs(double(k));
    return iw.isValid() && iw.isBounded() && !iw.moves() && m <= 2147483647.0;
}

/// d is the divisor p, or float(p)
bool isDivisor(Tree d, Tree p)
{
    Tree u;
    return d == p || (isSigFloatCast(d, u) && u == p);
}

/// the factors of a product as the normal form writes it
tvec factorsOf(Tree t)
{
    tvec fs;
    if (isSigProd(t, fs)) {
        return fs;
    }
    return {t};
}

Tree productOf(const tvec& fs)
{
    return fs.size() == 1 ? fs[0] : sigProd(fs);
}

}  // namespace

Tree revealPhase(Tree L)
{
    std::unordered_map<Tree, Tree> memo;

    auto pre     = [](Tree) -> std::optional<Tree> { return std::nullopt; };
    auto defRule = [](Tree, Tree rebuilt) -> Tree { return rebuilt; };
    auto image   = [&](Tree t) -> Tree {
        auto it = memo.find(t);
        return (it != memo.end()) ? it->second : nullptr;
    };

    // Prod[..., W, ..., n / D, ...] with D = P or a product holding P (the original side
    // decides, the rebuilt side is rewritten : same arity, same positions)
    auto rule = [&](Tree orig, Tree rebuilt) -> Tree {
        tvec fo, fr;
        if (!isSigProd(orig, fo) || !isSigProd(rebuilt, fr) || fo.size() != fr.size()) {
            return rebuilt;
        }
        for (size_t i = 0; i < fo.size(); i++) {
            Tree x, p;
            int  k;
            if (!phaseNumerator(fo[i], x, p, k) || isNum(p)) {
                continue;
            }
            for (size_t j = 0; j < fo.size(); j++) {
                Tree n, d;
                int  op;
                if (j == i || !isSigBinOp(fo[j], &op, n, d) || op != kDiv) {
                    continue;
                }
                tvec   ds = factorsOf(d);
                size_t at = ds.size();
                for (size_t m = 0; m < ds.size(); m++) {
                    if (isDivisor(ds[m], p)) {
                        at = m;
                        break;
                    }
                }
                Tree x2 = image(x), p2 = image(p);
                Tree n2, d2;
                if (at == ds.size() || x2 == nullptr || p2 == nullptr ||
                    !isSigBinOp(fr[j], &op, n2, d2)) {
                    continue;
                }
                tvec dr = factorsOf(d2);
                if (dr.size() != ds.size()) {
                    continue;
                }
                dr.erase(dr.begin() + at);
                Tree ph = sigPhase(x2, p2);
                tvec out;
                if (k != 1) {
                    out.push_back(sigReal(double(k)));
                }
                for (size_t m = 0; m < fr.size(); m++) {
                    if (m == i) {
                        out.push_back(ph);
                    } else if (m == j) {
                        if (!dr.empty()) {
                            Tree rest = productOf(dr);
                            out.push_back(sigBinOp(kDiv, n2, rest));
                        } else if (!isOne(n2)) {
                            out.push_back(n2);
                        }
                    } else {
                        out.push_back(fr[m]);
                    }
                }
                return productOf(out);
            }
        }
        return rebuilt;
    };

    return treeRewritePairedMemo(L, pre, rule, memo, defRule);
}
