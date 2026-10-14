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

#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>

#include "aterm.hh"
#include "global.hh"
#include "sigs-state.hh"
#include "ppsig.hh"
#include "xtended.hh"
#include "sigtype.hh"
#include "exception.hh"

using namespace std;

typedef map<Tree, mterm, treeorder> SM;

aterm::aterm()
{
}

/**
 * Create a aterm from a tree expression
 */
aterm::aterm(Tree t)
{
#ifdef TRACE
    cerr << "aterm::aterm (" << ppsig(t) << ")" << endl;
#endif
    *this += t;
#ifdef TRACE
    cerr << "aterm::aterm (" << ppsig(t) << ") : -> " << *this << endl;
#endif
}

/**
 * Add two terms trying to simplify the result
 */
Tree simplifyingAdd(Tree t1, Tree t2)
{
    faustassert(t1);
    faustassert(t2);

    if (isNum(t1) && isNum(t2)) {
        return addNums(t1, t2);

    } else if (isZero(t1)) {
        return t2;

    } else if (isZero(t2)) {
        return t1;

    } else if (t1->serial() <= t2->serial()) {
        return sigAdd(t1, t2);

    } else {
        return sigAdd(t2, t1);
    }
}

/**
 * The taps c[k] * x@k of FIR[x, c0, c1, ...], the null coefficients left out : what the
 * normal form reads of a FIR, which it writes again from them
 */
static std::vector<Tree> firTaps(const tvec& fir)
{
    std::vector<Tree> taps;
    Tree              x = fir[0];
    for (size_t k = 1; k < fir.size(); k++) {
        if (isZero(fir[k])) {
            continue;
        }
        int  i;
        Tree g;
        if (k == 1 && !isProj(x, &i, g)) {
            Tree t = sigMul(fir[k], x);
            taps.push_back(t);
        } else {
            // x@k, a recursive projection read at delay 0 written x@0 as the normal form does
            Tree d = sigDelay(x, sigInt(int(k) - 1));
            Tree t = sigMul(fir[k], d);
            taps.push_back(t);
        }
    }
    return taps;
}

/**
 * The FIRs of a sum : the terms c * x@k of a same source x, and the terms k * FIR[x, ...]
 * (k a number, a scaled FIR read as its taps k * c[j] * x@j), are written as one
 * FIR[x, c0, c1, ...] when there are two of them or more : the source then appears once
 * (a factorization that kept a number out of a FIR left x in two terms). The coefficient
 * of a delay is the sum of its contributions, the missing delays a null coefficient.
 * Records in taken the key of each term that a FIR takes ; the other written terms are
 * returned in written.
 */
static std::vector<Tree> writeFirs(const std::map<Tree, mterm, NormalFormTreeLess>& terms,
                                   std::set<Tree>& taken, std::vector<Tree>& written)
{
    // the contributions of each source, in the order of the terms (the sources in the
    // order of their first contribution)
    std::vector<Tree>                                        sources;
    std::map<Tree, std::map<int, aterm>, NormalFormTreeLess> coefs;
    std::map<Tree, std::vector<Tree>, NormalFormTreeLess>    keys;
    auto contribution = [&](Tree x, Tree key) {
        if (coefs.find(x) == coefs.end()) {
            sources.push_back(x);
        }
        keys[x].push_back(key);
        return &coefs[x];
    };
    for (const auto& p : terms) {
        Tree  x, k, f;
        int   d;
        mterm c;
        tvec  fir;
        if (p.second.isScaledFactor(k, f) && isSigFIR(f, fir)) {
            auto* cx = contribution(fir[0], p.first);
            for (size_t j = 1; j < fir.size(); j++) {
                if (isZero(fir[j])) {
                    continue;
                }
                Tree t = sigMul(k, fir[j]);
                (*cx)[int(j) - 1] += t;
            }
        } else if (p.second.tapOf(x, d, c)) {
            auto* cx = contribution(x, p.first);
            (*cx)[d] += c;
        }
    }
    std::vector<Tree> firs;
    for (Tree x : sources) {
        if (keys[x].size() < 2) {
            continue;  // a single tap, or a single scaled FIR : nothing to gather
        }
        taken.insert(keys[x].begin(), keys[x].end());
        // the coefficients, the trailing null ones left out
        std::map<int, Tree> cs;
        for (const auto& q : coefs[x]) {
            Tree c = q.second.normalizedTree();
            if (!isZero(c)) {
                cs[q.first] = c;
            }
        }
        if (cs.empty()) {
            continue;
        }
        if (cs.size() == 1) {
            // one tap left : the term c * x@d
            int  d  = cs.begin()->first;
            Tree c  = cs.begin()->second;
            Tree xd = (d == 0) ? x : sigDelay(x, sigInt(d));
            Tree t  = sigMul(c, xd);
            written.push_back(t);
            continue;
        }
        const int n = cs.rbegin()->first;
        tvec      fir{x};
        for (int d = 0; d <= n; d++) {
            auto it = cs.find(d);
            fir.push_back(it == cs.end() ? tree(0) : it->second);
        }
        firs.push_back(sigFIR(fir));
    }
    return firs;
}

Tree aterm::normalizedTree() const
{
    // Sum(t0, ..., tn) is the chain ((t0 + t1) + ...) + tn : the order of its terms is its
    // association, for the intervals as for the code. The number first, then the terms by
    // increasing order, the positive ones before the negative ones neg(t) within an order :
    // the terms slower than the sum form a prefix of the chain, computed at their rate.
    // The audio-recursive terms (order 4) come last, negative then positive, the
    // late state-join. Within an order and a sign, the canonical order of the normal form.
    // A sum whose terms are all negative is the negation of the sum of their opposites.
    std::vector<Tree> P[5], N[5];
    Tree              number = tree(0);
    // the FIRs first : a FIR is a positive term of the order of its source
    std::set<Tree>    taken;
    std::vector<Tree> single;  // a gathering left with one tap
    for (Tree f : writeFirs(fSig2MTerms, taken, single)) {
        P[sigs::sigOrder(f)].push_back(f);
    }
    auto place = [&](const mterm& m) {
        if (m.isNegative()) {
            Tree t = m.normalizedTree(false, true);  // its opposite, a positive writing
            if (isNum(t)) {
                number = subNums(number, t);
            } else {
                N[sigs::sigOrder(t)].push_back(t);
            }
        } else {
            Tree t = m.normalizedTree();
            if (isNum(t)) {
                number = addNums(number, t);
            } else {
                P[sigs::sigOrder(t)].push_back(t);
            }
        }
    };
    for (const auto& p : fSig2MTerms) {
        if (!taken.count(p.first)) {
            place(p.second);
        }
    }
    for (Tree t : single) {
        place(mterm(t));
    }
    const bool hasNumber = !isZero(number);
    bool       positive  = hasNumber && !isNegative(number->node());
    for (int order = 0; order < 5; order++) {
        positive = positive || !P[order].empty();
    }
    // the terms, or their opposites when every term is negative
    const bool        opposite = !positive;
    std::vector<Tree> terms;
    auto              negative = [&](Tree t) {
        if (opposite) {
            terms.push_back(t);
        } else {
            Tree n = sigNeg(t);
            terms.push_back(n);
        }
    };
    if (hasNumber) {
        terms.push_back(opposite ? minusNum(number) : number);
    }
    for (int order = 0; order < 4; order++) {
        terms.insert(terms.end(), P[order].begin(), P[order].end());
        for (Tree t : N[order]) negative(t);
    }
    for (Tree t : N[4]) negative(t);
    terms.insert(terms.end(), P[4].begin(), P[4].end());

    if (terms.empty()) {
        return tree(0);
    }
    if (terms.size() == 1 && isNum(terms[0])) {
        return opposite ? minusNum(terms[0]) : terms[0];  // a number stays a number
    }
    Tree sum = (terms.size() == 1) ? terms[0] : sigSum(terms);
    return opposite ? sigNeg(sum) : sum;
}

/**
 * Print an aterm in a human readable format
 */
ostream& aterm::print(ostream& dst) const
{
    if (fSig2MTerms.empty()) {
        dst << "AZERO";
    } else {
        const char* sep = "";
        for (const auto& p : fSig2MTerms) {
            dst << sep << p.second;
            sep = " + ";
        }
    }

    return dst;
}

/**
 * Add in place an additive expression tree. Go down recursively looking
 * for additions and substractions
 */
const aterm& aterm::operator+=(Tree t)
{
    int  op;
    Tree x, y;

    faustassert(t);

    if (isSigBinOp(t, &op, x, y) && (op == kAdd)) {
        *this += x;
        *this += y;

    } else if (isSigBinOp(t, &op, x, y) && (op == kSub)) {
        *this += x;
        *this -= y;

    } else if (isSigNeg(t, x)) {
        *this -= x;

    } else if (tvec subs; isSigSum(t, subs)) {
        for (Tree u : subs) *this += u;

    } else if (tvec fir; isSigFIR(t, fir)) {
        for (Tree u : firTaps(fir)) *this += u;

    } else {
        mterm m(t);
        *this += m;
    }
    return *this;
}

/**
 * Substract in place an additive expression tree. Go down to recursively looking
 * for additions and substractions
 */
const aterm& aterm::operator-=(Tree t)
{
    int  op;
    Tree x, y;

    faustassert(t);

    if (isSigBinOp(t, &op, x, y) && (op == kAdd)) {
        *this -= x;
        *this -= y;

    } else if (isSigBinOp(t, &op, x, y) && (op == kSub)) {
        *this -= x;
        *this += y;

    } else if (tvec subs; isSigSum(t, subs)) {
        for (Tree u : subs) *this -= u;

    } else if (tvec fir; isSigFIR(t, fir)) {
        for (Tree u : firTaps(fir)) *this -= u;

    } else if (isSigNeg(t, x)) {
        *this += x;

    } else {
        mterm m(t);
        *this -= m;
    }
    return *this;
}

/**
 * Add in place an mterm
 */
const aterm& aterm::operator+=(const mterm& m)
{
#ifdef TRACE
    cerr << *this << " aterm::+= " << m << endl;
#endif
    Tree signature = m.signatureTree();
#ifdef TRACE
    cerr << "signature " << *signature << endl;
#endif
    SM::const_iterator p = fSig2MTerms.find(signature);
    if (p == fSig2MTerms.end()) {
        // its a new mterm
        fSig2MTerms.insert(make_pair(signature, m));
    } else {
        // we already have a mterm of same signature, we add them together
        fSig2MTerms[signature] += m;
    }
    return *this;
}

/**
 * Substract in place an mterm
 */
const aterm& aterm::operator-=(const mterm& m)
{
    // cerr << *this << " aterm::-= " << m << endl;
    Tree sig = m.signatureTree();
    // cerr << "signature " << *sig << endl;
    SM::const_iterator p = fSig2MTerms.find(sig);
    if (p == fSig2MTerms.end()) {
        // its a new mterm
        fSig2MTerms.insert(make_pair(sig, m * mterm(-1)));
    } else {
        fSig2MTerms[sig] -= m;
    }
    return *this;
}

/**
 * A term k * S^n * R, S a sum and n a small positive power, is developed when one of
 * its developed terms cancels a non constant term of the sum :
 * (f + 4c)^2 - 16c^2 -> f^2 + 8fc. The cancelled value appeared twice, in S and in the
 * other term, and the interval of the difference lost that the two occurrences cancel.
 * Otherwise the term is kept : developing a product by a sum repeats the factors of the
 * product, and a cancelled number is no gain (1 - (1 - x)^2 is better than 2x - x^2).
 * The trial creates no tree : the order of the normal form follows the creation of the
 * trees, a tree created by a trial that is not adopted would reorder other sums.
 */
namespace {
struct Monomial {
    num                                     coef;
    std::map<Tree, int, NormalFormTreeLess> factors;
};

Monomial monomialOf(const mterm& m)
{
    Monomial r;
    isNum(m.coefficient(), r.coef);
    r.factors = m.factors();
    return r;
}

Monomial product(const Monomial& a, const Monomial& b)
{
    Monomial r{a.coef * b.coef, a.factors};
    for (const auto& f : b.factors) {
        if ((r.factors[f.first] += f.second) == 0) {
            r.factors.erase(f.first);
        }
    }
    return r;
}
}  // namespace

static bool developmentCancels(const std::map<Tree, mterm, NormalFormTreeLess>& terms, Tree key,
                               const mterm& m, Tree s, int n)
{
    const size_t maxTerms = 64;
    tvec         subs;
    isSigSum(s, subs);
    std::vector<Monomial> sum;
    for (Tree u : subs) {
        sum.push_back(monomialOf(mterm(u)));
    }
    Monomial rest = monomialOf(m);
    rest.factors.erase(s);
    std::vector<Monomial> dev{rest};
    for (int i = 0; i < n; i++) {
        if (dev.size() * sum.size() > maxTerms) {
            return false;
        }
        std::vector<Monomial> next;
        for (const Monomial& a : dev) {
            for (const Monomial& b : sum) {
                Monomial c = product(a, b);
                auto     it = std::find_if(next.begin(), next.end(), [&](const Monomial& x) {
                    return x.factors == c.factors;
                });
                if (it == next.end()) {
                    next.push_back(c);
                } else {
                    it->coef = it->coef + c.coef;
                }
            }
        }
        dev = next;
    }
    for (const Monomial& d : dev) {
        if (double(d.coef) == 0 || d.factors.empty()) {
            continue;  // a number is not a value that repeats : its cancellation is no gain
        }
        for (const auto& t : terms) {
            if (t.first != key && t.second.isNotZero() && t.second.factors() == d.factors) {
                num c;
                isNum(t.second.coefficient(), c);
                if (double(c + d.coef) == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void aterm::expandCancellations()
{
    const int maxPower = 3;
    for (int budget = 16, changed = 1; changed && budget > 0; budget--) {
        changed = 0;
        for (const auto& p : fSig2MTerms) {
            if (!p.second.isNotZero()) {
                continue;
            }
            for (const auto& q : p.second.factors()) {
                if (q.second < 1 || q.second > maxPower || !isSigSum(q.first) ||
                    !developmentCancels(fSig2MTerms, p.first, p.second, q.first, q.second)) {
                    continue;
                }
                // the development : (k * R) * S * ... * S, added to the other terms, the
                // terms of S read as the trial reads them
                tvec subs;
                isSigSum(q.first, subs);
                std::vector<mterm> dev{p.second.withoutFactorsOf(mterm(q.first))};
                for (int i = 0; i < q.second; i++) {
                    std::vector<mterm> next;
                    for (const mterm& a : dev) {
                        for (Tree u : subs) {
                            next.push_back(a * mterm(u));
                        }
                    }
                    dev = next;
                }
                aterm r(*this);
                r.fSig2MTerms.erase(p.first);
                for (const mterm& m : dev) {
                    r += m;
                }
                *this   = r;
                changed = 1;
                break;
            }
            if (changed) {
                break;
            }
        }
    }
}

/**
 * The conditions : a comparison, or the & and | of two conditions. Their value is 0 or 1.
 */
static bool isCondition(Tree t)
{
    int  op;
    Tree x, y;
    if (!isSigBinOp(t, &op, x, y)) {
        return false;
    }
    if (op == kGT || op == kLT || op == kGE || op == kLE || op == kEQ || op == kNE) {
        return true;
    }
    return (op == kAND || op == kOR) && isCondition(x) && isCondition(y);
}

/**
 * The signals whose values are integers : the integer numbers, the conditions, the
 * buttons and checkboxes (0 or 1), the conversions to an integer, and the conversion to a
 * float of an integer signal
 */
static bool isIntegerValued(Tree t)
{
    int  i;
    Tree x;
    return isSigInt(t, &i) || isCondition(t) || isSigButton(t) || isSigCheckbox(t) ||
           isSigIntCast(t) || (isSigFloatCast(t, x) && isIntegerValued(x));
}

static bool numberValue(Tree t, double& v)
{
    int i;
    if (isSigInt(t, &i)) {
        v = i;
        return true;
    }
    return isSigReal(t, &v);
}

/**
 * A condition on an integer signal x read as a half line of integers : x >= m (upper
 * false) or x <= m (upper true). A condition c is itself c >= 1.
 */
static bool integerHalfLine(Tree t, Tree& x, double& m, bool& upper)
{
    int    op;
    Tree   a, b;
    double k;
    if (isSigBinOp(t, &op, a, b) && op != kAND && op != kOR && op != kEQ && op != kNE) {
        if (numberValue(b, k) && isIntegerValued(a)) {
            x = a;
        } else if (numberValue(a, k) && isIntegerValued(b)) {
            x = b;
            // k op x is x op' k, the comparison mirrored
            op = (op == kGT) ? kLT : (op == kLT) ? kGT : (op == kGE) ? kLE : kGE;
        } else {
            return false;
        }
        switch (op) {
            case kGT: m = std::floor(k) + 1, upper = false; return true;
            case kGE: m = std::ceil(k), upper = false; return true;
            case kLT: m = std::ceil(k) - 1, upper = true; return true;
            default: m = std::floor(k), upper = true; return true;  // kLE
        }
    }
    if (isCondition(t)) {
        x = t, m = 1, upper = false;
        return true;
    }
    return false;
}

/**
 * Whether b is the negation of the condition a, decided on the trees as they are (no
 * tree is created) : a comparison and its negation, the same half line of integers on
 * both sides of a bound (a button is 0 or 1 : trig > 0 and trig < 1), and De Morgan.
 * The negation of a comparison is exact for the values that are not NaN.
 */
static bool isNegation(Tree a, Tree b)
{
    int  opa, opb;
    Tree xa, ya, xb, yb;
    if (isSigBinOp(a, &opa, xa, ya) && isSigBinOp(b, &opb, xb, yb)) {
        auto negated = [](int op) -> int {
            switch (op) {
                case kGT: return kLE;
                case kLT: return kGE;
                case kGE: return kLT;
                case kLE: return kGT;
                case kEQ: return kNE;
                case kNE: return kEQ;
                default: return -1;
            }
        };
        auto mirrored = [](int op) -> int {
            switch (op) {
                case kGT: return kLT;
                case kLT: return kGT;
                case kGE: return kLE;
                case kLE: return kGE;
                default: return op;
            }
        };
        if (negated(opa) >= 0) {
            if (opb == negated(opa) && xa == xb && ya == yb) {
                return true;
            }
            if (opb == negated(mirrored(opa)) && xa == yb && ya == xb) {
                return true;
            }
        }
        // De Morgan : not (p & q) = (not p) | (not q), and the converse
        if ((opa == kAND && opb == kOR) || (opa == kOR && opb == kAND)) {
            if (isCondition(a) && isCondition(b) &&
                ((isNegation(xa, xb) && isNegation(ya, yb)) ||
                 (isNegation(xa, yb) && isNegation(ya, xb)))) {
                return true;
            }
        }
    }
    Tree   x1, x2;
    double m1, m2;
    bool   u1, u2;
    if (integerHalfLine(a, x1, m1, u1) && integerHalfLine(b, x2, m2, u2) && x1 == x2 && u1 != u2) {
        // x >= m and x <= m - 1 share no integer and leave none out
        return u1 ? (m1 == m2 - 1) : (m2 == m1 - 1);
    }
    return false;
}

/**
 * The condition held by a factor of a term : c, or float(c)
 */
static bool conditionOf(Tree f, Tree& c)
{
    Tree x;
    if (isSigFloatCast(f, x)) {
        f = x;
    }
    if (isCondition(f)) {
        c = f;
        return true;
    }
    return false;
}

/**
 * A * [c] + B * [not c], [c] the value 0 or 1 of a condition, is written select2(c, B, A) :
 * the two terms are never both non null, and the interval of the sum no longer adds the
 * two values (asympT60 of instruments.lib : 0.03 * [c] + 0.996 * [not c] stays in [0, 1]).
 * The condition and its negation are found without creating trees.
 */
void aterm::extractSelects()
{
    for (bool changed = true; changed;) {
        changed = false;
        // the first pair of terms A * [c] and B * [not c]
        Tree k1 = nullptr, k2 = nullptr, f1 = nullptr, f2 = nullptr, c1 = nullptr;
        for (const auto& p1 : fSig2MTerms) {
            if (k1 == nullptr && p1.second.isNotZero()) {
                for (Tree g1 : p1.second.unitFactors()) {
                    Tree d1;
                    if (k1 != nullptr || !conditionOf(g1, d1)) {
                        continue;
                    }
                    for (const auto& p2 : fSig2MTerms) {
                        if (k1 != nullptr || p2.first == p1.first || !p2.second.isNotZero()) {
                            continue;
                        }
                        for (Tree g2 : p2.second.unitFactors()) {
                            Tree d2;
                            if (k1 == nullptr && conditionOf(g2, d2) && isNegation(d1, d2)) {
                                k1 = p1.first, f1 = g1, c1 = d1;
                                k2 = p2.first, f2 = g2;
                            }
                        }
                    }
                }
            }
        }
        if (k1 == nullptr) {
            break;
        }
        mterm a  = fSig2MTerms[k1].withoutFactorsOf(mterm(f1));
        mterm b  = fSig2MTerms[k2].withoutFactorsOf(mterm(f2));
        Tree  ta = a.normalizedTree();
        Tree  tb = b.normalizedTree();
        Tree  s  = sigSelect2(c1, tb, ta);
        fSig2MTerms.erase(k1);
        fSig2MTerms.erase(k2);
        *this += mterm(s);
        changed = true;
    }
}

/**
 * The compound operations frac and cfrac. A sum holding k*S and -k*floor(S) (resp.
 * -k*rint(S)), every term of k*S present with its exact coefficient, is rewritten
 * with k*frac(S) (resp. k*cfrac(S)) : the operand then appears once, and its interval
 * no longer loses that S - floor(S) lies in [0, 1] (the dependency problem).
 */
void aterm::extractRemainders()
{
    for (bool changed = true; changed;) {
        changed = false;
        for (const auto& p : fSig2MTerms) {
            Tree coef, f;
            if (!p.second.isScaledFactor(coef, f) || f->arity() != 1) {
                continue;
            }
            xtended*   round   = static_cast<xtended*>(getUserData(f));
            const bool isFloor = round != nullptr && round == gGlobal->gFloorPrim;
            if (!isFloor && (round == nullptr || round != gGlobal->gRintPrim)) {
                continue;
            }
            Tree  x = f->branch(0);
            mterm k(minusNum(coef));
            aterm X(x);
            bool  present = !X.fSig2MTerms.empty();
            for (const auto& q : X.fSig2MTerms) {
                auto it = fSig2MTerms.find(q.first);
                if (it == fSig2MTerms.end() || it->first == p.first) {
                    present = false;
                    break;
                }
                mterm d = it->second;
                d -= q.second * k;
                if (d.isNotZero()) {
                    present = false;
                    break;
                }
            }
            if (!present) {
                continue;
            }
            Tree key = p.first;
            for (const auto& q : X.fSig2MTerms) {
                fSig2MTerms.erase(q.first);
            }
            fSig2MTerms.erase(key);
            Tree r = isFloor ? sigFrac(x) : sigCfrac(x);
            *this += mterm(r) * k;
            changed = true;
            break;
        }
    }
}

/**
 * w is 1 - c, c not a number : a binary 1 - c, or the Sum(1, neg(t1), ..., neg(tn)) of the
 * normal form, c being t1 or the Sum(t1, ..., tn) of the same terms in the same order
 * (the writing of t1 + ... + tn by the normal form)
 */
static bool complementOf(Tree w, Tree& c)
{
    int  op;
    Tree one, x;
    tvec ws;
    if (isSigBinOp(w, &op, one, x) && op == kSub && isOne(one)) {
        c = x;
        return !isNum(c);
    }
    if (!isSigSum(w, ws) || ws.size() < 2 || !isOne(ws[0])) {
        return false;
    }
    tvec ts;
    for (size_t i = 1; i < ws.size(); i++) {
        if (!isSigNeg(ws[i], x)) {
            return false;
        }
        ts.push_back(x);
    }
    c = (ts.size() == 1) ? ts[0] : sigSum(ts);
    return !isNum(c);
}

/**
 * t takes the values 0 and 1 only : a condition, a button, a checkbox, a logical
 * operation of such values, or one of them converted
 */
static bool isBooleanValued(Tree t)
{
    int  op;
    Tree x, y;
    if (isSigFloatCast(t, x) || isSigIntCast(t, x)) {
        return isBooleanValued(x);
    }
    if (isCondition(t) || isSigButton(t) || isSigCheckbox(t)) {
        return true;
    }
    return isSigBinOp(t, &op, x, y) && (op == kAND || op == kOR || op == kXOR) && isBooleanValued(x) &&
           isBooleanValued(y);
}

/**
 * (1 - c) * a + c * b : an interpolation, mix(c, a, b), when the weight c is continuous ; a
 * selection, select2(c, a, b), when c is 0 or 1 (isBooleanValued). Each node is one regime
 * of computation : the selection is exact, keeps the nature of its branches and ignores
 * the branch it does not choose, the interpolation rounds and reads both operands.
 */
static Tree mixOrSelect(Tree c, Tree a, Tree b)
{
    return isBooleanValued(c) ? sigSelect2(c, a, b) : sigMix(c, a, b);
}

/**
 * g, a weight times sign, is a number outside ]0, 1[ : A + g * (B - A) is then an
 * extrapolation (the state 2 * (s + v) - s of a TPT integrator is s + 2v), not a mix
 */
static bool extrapolates(const mterm& g, int sign)
{
    if (!g.factors().empty()) {
        return false;
    }
    num k;
    isNum(g.coefficient(), k);
    return !(double(k) * sign > 0 && double(k) * sign < 1);
}

/**
 * the weight w varies at every sample while A and the other terms of S (B) are slower :
 * A + w * (B - A) is then read with the wrong weight. The smoother written
 * E + y' * (1 - E), a constant E and its state y', is y' + E * (1 - y'), mix(E, y', 1), not
 * mix(y', E, 1) : the rule of the complementary weights (extractMixes) reads it so.
 */
static bool fastWeightOverSlowOperands(const mterm& w, const mterm& a, const tvec& subs, Tree inS)
{
    auto audio = [](const mterm& m) {
        for (const auto& f : m.factors()) {
            if (sigs::isAudioRate(f.first)) return true;
        }
        return false;
    };
    if (!audio(w) || audio(a)) {
        return false;
    }
    for (Tree u : subs) {
        if (u != inS && sigs::isAudioRate(u)) return false;
    }
    return true;
}

/**
 * An interpolation A + g * (B - A) is written mix(g, A, B) = (1 - g) * A + g * B : A, read
 * twice (as a term and, negated, in the difference), is read once, and the mix of a
 * weight g in [0, 1] lies between A and B. A is a term of the sum, g * S another one, S a
 * sum holding the term -A exactly ; B is S without it. A product with a negative
 * coefficient whose S holds +A is the same interpolation with S and g negated :
 * B - (1 - c) * (B - A) is mix(1 - c, B, A). A weight 1 - c is then written as its
 * complement, mix(c, A, B) for mix(1 - c, B, A), so that every writing of an
 * interpolation reaches the same node. The match compares the monomials.
 */
void aterm::extractLerps()
{
    for (;;) {
        Tree ka = nullptr, kg = nullptr, s = nullptr, inS = nullptr;
        bool negated = false;
        for (const auto& pg : fSig2MTerms) {
            if (!pg.second.isNotZero() || kg != nullptr) continue;
            for (const auto& q : pg.second.factors()) {
                tvec subs;
                if (q.second != 1 || !isSigSum(q.first, subs) || subs.size() < 2 || kg != nullptr) continue;
                for (Tree u : subs) {
                    if (kg != nullptr) break;
                    mterm mu(u);
                    for (const auto& pa : fSig2MTerms) {
                        if (pa.first == pg.first || !pa.second.isNotZero()) continue;
                        if (pa.second.factors() != mu.factors()) continue;
                        num ca, cu;
                        isNum(pa.second.coefficient(), ca);
                        isNum(mu.coefficient(), cu);
                        const mterm w = pg.second.withoutFactorsOf(mterm(q.first));
                        if (fastWeightOverSlowOperands(w, pa.second, subs, u)) continue;
                        if (double(ca + cu) == 0 && !extrapolates(w, 1)) {
                            ka = pa.first, kg = pg.first, s = q.first, inS = u, negated = false;
                            break;
                        }
                        if (double(ca - cu) == 0 && pg.second.isNegative() && !extrapolates(w, -1)) {
                            ka = pa.first, kg = pg.first, s = q.first, inS = u, negated = true;
                            break;
                        }
                    }
                }
            }
        }
        if (kg == nullptr) {
            return;
        }
        // the rewrite : A, B = S without the reading of A (negated with S), g = the term
        // without S (negated with S)
        tvec subs;
        isSigSum(s, subs);
        tvec rest;
        for (Tree u : subs) {
            if (u == inS) continue;
            Tree x;
            rest.push_back(!negated ? u : (isSigNeg(u, x) ? x : sigNeg(u)));
        }
        Tree  a  = fSig2MTerms[ka].normalizedTree();
        Tree  b  = (rest.size() == 1) ? rest[0] : sigSum(rest);
        mterm g  = fSig2MTerms[kg].withoutFactorsOf(mterm(s));
        Tree  tg = g.normalizedTree(false, negated);
        Tree  c;
        Tree  m = complementOf(tg, c) ? mixOrSelect(c, b, a) : mixOrSelect(tg, a, b);
        fSig2MTerms.erase(ka);
        fSig2MTerms.erase(kg);
        *this += mterm(m);
    }
}

/**
 * x and y are the same monomial up to the sign : sign * x == y
 */
static bool sameMonomial(const mterm& x, const mterm& y, int sign)
{
    if (x.factors() != y.factors()) {
        return false;
    }
    num cx, cy;
    isNum(x.coefficient(), cx);
    isNum(y.coefficient(), cy);
    return double(cx) * sign == double(cy);
}

/**
 * A mix and its own step : mix(c, A, B) + g * (B - A) is A + (c + g) * (B - A), written
 * mix(c + g, A, B) when g is c up to a constant (the weight stays a monomial). The state
 * s' = y + g * (x - s) of a TPT one-pole filter, whose output y = s + g * (x - s) is
 * revealed as mix(g, s, x), is then the smoother mix(2g, s, x) : each operand read once,
 * the step not repeated outside the mix. A difference A - B is the step negated. A scaled
 * mix is the same step : k * mix(c, A, B) + (1 - k) * A is mix(k * c, A, B) (the state
 * 2y - s of the same filter).
 */
void aterm::extractMixSteps()
{
    for (;;) {
        Tree km = nullptr, kg = nullptr, m = nullptr, s = nullptr;
        int  sign = 0;
        for (const auto& pm : fSig2MTerms) {
            const mterm& tm = pm.second;
            Tree         c, a, b;
            if (km != nullptr || !tm.isNotZero() || tm.factors().size() != 1 ||
                tm.factors().begin()->second != 1 || !isSigMix(tm.factors().begin()->first, c, a, b)) {
                continue;
            }
            num cm;
            if (!isNum(tm.coefficient(), cm)) {
                continue;
            }
            const Tree mn = tm.factors().begin()->first;
            mterm      ma(a), mb(b), mc(c);
            if (double(cm) != 1) {
                // k * mix(c, A, B) + (1 - k) * A
                mterm rest(ma);
                rest *= mterm(1.0 - double(cm));
                mterm w(c);
                w *= mterm(tm.coefficient());
                for (const auto& pa : fSig2MTerms) {
                    if (pa.first != pm.first && pa.second.isNotZero() && sameMonomial(rest, pa.second, 1) &&
                        !extrapolates(w, 1)) {
                        km = pm.first, kg = pa.first, m = mn, s = nullptr;
                        break;
                    }
                }
                continue;
            }
            for (const auto& pg : fSig2MTerms) {
                if (pg.first == pm.first || !pg.second.isNotZero() || km != nullptr) continue;
                for (const auto& q : pg.second.factors()) {
                    tvec subs;
                    if (q.second != 1 || !isSigSum(q.first, subs) || subs.size() != 2) continue;
                    mterm u0(subs[0]), u1(subs[1]);
                    int   sg = 0;
                    if ((sameMonomial(mb, u0, 1) && sameMonomial(ma, u1, -1)) ||
                        (sameMonomial(mb, u1, 1) && sameMonomial(ma, u0, -1))) {
                        sg = 1;
                    } else if ((sameMonomial(ma, u0, 1) && sameMonomial(mb, u1, -1)) ||
                               (sameMonomial(ma, u1, 1) && sameMonomial(mb, u0, -1))) {
                        sg = -1;
                    }
                    mterm g = pg.second.withoutFactorsOf(mterm(q.first));
                    if (sg == 0 || g.factors() != mc.factors()) continue;
                    if (sg < 0) {
                        g *= mterm(-1);
                    }
                    mterm w(c);
                    w += g;
                    if (w.isNotZero() && extrapolates(w, 1)) continue;
                    km = pm.first, kg = pg.first, m = mn, s = q.first, sign = sg;
                    break;
                }
            }
        }
        if (km == nullptr) {
            return;
        }
        Tree c, a, b;
        isSigMix(m, c, a, b);
        mterm w(c);
        if (s == nullptr) {
            w *= mterm(fSig2MTerms[km].coefficient());
        } else {
            mterm g = fSig2MTerms[kg].withoutFactorsOf(mterm(s));
            if (sign < 0) {
                g *= mterm(-1);
            }
            w += g;
        }
        fSig2MTerms.erase(km);
        fSig2MTerms.erase(kg);
        if (!w.isNotZero()) {
            *this += mterm(a);
            continue;
        }
        Tree tw = w.normalizedTree();
        Tree cc;
        *this += mterm(complementOf(tw, cc) ? mixOrSelect(cc, b, a) : mixOrSelect(tw, a, b));
    }
}

/**
 * The compound operation mix. A sum holding k*(1 - c)*A and k*c*B is rewritten with
 * mix(c, k*A, k*B) : the weight then appears once, and the interval of the mix no
 * longer loses that it lies between k*A and k*B (the dependency problem).
 */
void aterm::extractMixes()
{
    for (;;) {
        // find one pair (k*(1 - c)*A, k*c*B), then rewrite it outside of the iteration
        Tree  k1 = nullptr, k2 = nullptr, c = nullptr;
        mterm q1, q2;
        for (const auto& p1 : fSig2MTerms) {
            for (Tree f : p1.second.unitFactors()) {
                // c : what f complements, a divisor of the other term (a product or a
                // ratio as well : the mterm of 44.1/SR is 44.1 * SR^-1)
                Tree x;
                if (!complementOf(f, x)) {
                    continue;
                }
                const mterm mx(x);
                for (const auto& p2 : fSig2MTerms) {
                    // the other term divided by c : a ratio c = k/SR gives the target
                    // of the smoother c * (SR * d) + (1 - c) * y', which the normal form
                    // wrote 44.1 * d, back as d * SR
                    if (p2.first == p1.first || !p2.second.hasDivisorUpToReciprocals(mx)) {
                        continue;
                    }
                    const mterm r1 = p1.second / mterm(f);
                    const mterm r2 = p2.second / mx;
                    if (isZero(subNums(r1.coefficient(), r2.coefficient()))) {
                        k1 = p1.first, k2 = p2.first, c = x, q1 = r1, q2 = r2;
                        break;
                    }
                }
                if (k1) {
                    break;
                }
            }
            if (k1) {
                break;
            }
        }
        if (!k1) {
            return;
        }
        // mix is linear in its two operands : two negative operands give the negation of
        // the mix of their opposites, the sign carried by the sum (see the normal form of a
        // sum : the sign is carried by neg)
        const bool neg = q1.isNegative() && q2.isNegative();
        Tree       a   = q1.normalizedTree(false, neg);
        Tree       b   = q2.normalizedTree(false, neg);
        fSig2MTerms.erase(k1);
        fSig2MTerms.erase(k2);
        mterm m(mixOrSelect(c, a, b));
        if (neg) {
            *this -= m;
        } else {
            *this += m;
        }
    }
}

/**
 * The compound operation tpt. A term holding g and (g + 1)^-k is rewritten with
 * tpt(g) * (g + 1)^-(k-1) : g then appears once, and the interval of g / (g + 1) no
 * longer loses that it lies in [0, 1[ for g >= 0 (the dependency problem).
 */
void aterm::extractTpts()
{
    for (;;) {
        Tree  key = nullptr, g = nullptr, d = nullptr;
        mterm m;
        for (const auto& p : fSig2MTerms) {
            if (p.second.tptFactors(g, d)) {
                key = p.first;
                m   = p.second;
                break;
            }
        }
        if (key == nullptr) {
            return;
        }
        fSig2MTerms.erase(key);
        mterm ratio(g);
        ratio /= mterm(d);
        mterm rest = m / ratio;
        mterm node(sigTpt(g));
        *this += rest * node;
    }
}

/**
 * The recursive sources a term reads otherwise than as a tap (the product of two audio
 * factors, a power) : a recursion read so is not linear, and never becomes an IIR.
 */
static std::unordered_set<Tree> nonlinearSources(const std::map<Tree, mterm, NormalFormTreeLess>& terms)
{
    std::unordered_set<Tree> sources;
    for (const auto& p : terms) {
        Tree  src;
        int   d;
        mterm c;
        if (!p.second.isNotZero() || p.second.tapOf(src, d, c)) {
            continue;
        }
        for (const auto& f : p.second.factors()) {
            Tree x = f.first, y, n;
            int  i;
            Tree g;
            if (isSigDelay(x, y, n)) {
                x = y;
            }
            if (isProj(x, &i, g)) {
                sources.insert(x);
            }
        }
    }
    return sources;
}

/**
 * A term c * y@k whose source y is a recursion : the feedback of a linear recursion, which
 * the normal form keeps as it is, so that the taps of a recursion gather into a FIR and the
 * recursion is revealed as an IIR (bounded by its gain, where a factor taken out of its
 * feedback would hide it). A source the sum also reads in a nonlinear term is not
 * protected : its recursion is no IIR, and the factorization reads it once
 * (y - p * w * y = y * (1 - p * w), within [0, y] for y >= 0 and p * w in [0, 1]).
 */
static bool isRecursiveTap(const mterm& m, const std::unordered_set<Tree>& nonlinear)
{
    Tree  src;
    int   d;
    mterm c;
    int   i;
    Tree  g;
    return m.tapOf(src, d, c) && isProj(src, &i, g) && nonlinear.count(src) == 0;
}

mterm aterm::greatestDivisor() const
{
    // The greatest common divisor of two terms, of the highest complexity, kept only for
    // its factors that leave every quotient : a factor still present in a quotient (y in
    // y + 3y^2 = y (1 + 3y)) is read as often after the factorization as before, and its
    // power, exact for an interval, would be lost. Never a number alone (complexity 0).
    // A term that cancelled (x - x, a null coefficient) divides nothing and is skipped.
    // The taps of a recursion are left out (isRecursiveTap).
    const std::unordered_set<Tree> nonlinear = nonlinearSources(fSig2MTerms);
    int                            maxComplexity = 0;
    mterm                          maxGCD(1);
    for (auto p1 = fSig2MTerms.begin(); p1 != fSig2MTerms.end(); p1++) {
        if (!p1->second.isNotZero() || isRecursiveTap(p1->second, nonlinear)) {
            continue;
        }
        for (auto p2 = std::next(p1); p2 != fSig2MTerms.end(); p2++) {
            if (!p2->second.isNotZero() || isRecursiveTap(p2->second, nonlinear)) {
                continue;
            }
            mterm g = gcd(p1->second, p2->second);
            for (bool changed = true; changed && g.complexity() > 0;) {
                changed = false;
                for (const auto& p : fSig2MTerms) {
                    if (!p.second.isNotZero() || !p.second.hasDivisor(g) || isRecursiveTap(p.second, nonlinear)) {
                        continue;
                    }
                    const mterm q  = p.second / g;
                    const mterm g2 = g.withoutFactorsOf(q);
                    if (g2.complexity() < g.complexity()) {
                        g       = g2;
                        changed = true;
                        break;
                    }
                }
            }
            int complexity = g.complexity();
            if (complexity > maxComplexity) {
                maxComplexity = complexity;
                maxGCD        = g;
            }
        }
    }
    return maxGCD;
}

/**
 * Reorganize the aterm by factorizing d
 */
aterm aterm::factorize(const mterm& d)
{
    // cerr << "factorize : " << *this << " with " << d << endl;
    aterm A;
    aterm Q;

    // separate the multiple of m from the others
    const std::unordered_set<Tree> nonlinear = nonlinearSources(fSig2MTerms);
    for (const auto& p1 : fSig2MTerms) {
        mterm t = p1.second;
        if (t.hasDivisor(d) && !isRecursiveTap(t, nonlinear)) {
            mterm q = t / d;
            // cerr << "q = " << q << endl;
            Q += q;
            // cerr << "step Q = " << Q << endl;
        } else {
            A += t;
            // cerr << "step A = " << A << endl;
        }
    }

    // combines the two parts
    // cerr << "d.normalizedTree() " << ppsig(d.normalizedTree()) << endl;
    // cerr << "Q.normalizedTree() " << ppsig(Q.normalizedTree()) << endl;
    // Tree tt = sigMul(d.normalizedTree(), Q.normalizedTree());
    // cerr << "tt " << *tt << endl;

    // Tree ttt = sigAdd(
    Tree dn = d.normalizedTree();
    Tree qn = Q.normalizedTree();
    A += sigMul(dn, qn);
    // cerr << "Final A = " << A << endl;
    // cerr << "Final Tree " << *(A.normalizedTree()) << endl;
    return A;
}
