/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.
 ************************************************************************
 ************************************************************************/

#include "typedAttributes.hh"

#include <cmath>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "computeSignals.hh"
#include "exception.hh"
#include "ppsig.hh"
#include "sigOpcode.hh"

namespace {

/// a signal node : a number, an extended primitive, a projection, a constructor of the
/// signal language or of the computation form (structure : lists, labels, recursive groups)
bool isSignalNode(Tree t, const Signature& signature)
{
    int                i;
    int64_t            i64;
    double             r;
    Tree               g;
    sigs::SignalOpcode op;
    return isSigInt(t, &i) || isSigInt64(t, &i64) || isSigReal(t, &r) || sigXtendedData(t) != nullptr ||
           isProj(t, &i, g) || sigs::signalOpcode(t, signature, op) || isComputeSignal(t);
}

/// the type of a node a lowering built, composed from its operands' (all annotated), as the
/// exact attribute algebras compose them (sigattributes.cpp) : every attribute of an
/// arithmetic operation is the union of its operands' ; a delayed read x@d is at the sample
/// rate, of the nature and the booleanity of x
Type composedType(Tree t)
{
    int    i;
    double r;
    if (isSigInt(t, &i)) {
        return makeSimpleType(kInt, kKonst, kComp, kVect, kNum, itv::interval(i, i));
    }
    if (isSigReal(t, &r)) {
        return makeSimpleType(kReal, kKonst, kComp, kVect, kNum, itv::interval(r, r));
    }
    const itv::interval unbounded(-HUGE_VAL, HUGE_VAL);
    int                 op;
    Tree                x, y;
    tvec                subs;
    if (isSigDelay(t, x, y)) {
        Type tx = getCertifiedSigType(x);
        Type ty = getCertifiedSigType(y);
        return makeSimpleType(tx->nature(), kSamp, tx->computability() | ty->computability(),
                              tx->vectorability() | ty->vectorability(), tx->boolean(), unbounded);
    }
    tvec operands;
    bool taps = false;  // a FIR of two taps or more reads its signal delayed
    if (isSigSum(t, subs) || isSigProd(t, subs)) {
        operands = subs;
    } else if (isSigFIR(t, subs)) {
        operands = subs;
        taps     = subs.size() > 2;
    } else if (isSigIIR(t, subs)) {
        operands = subs;
        taps     = true;  // a recursion : at the sample rate
    } else if (isSigNeg(t, x)) {
        operands = {x};
    } else if (isSigBinOp(t, &op, x, y) && (op == kAdd || op == kSub || op == kMul || op == kDiv)) {
        operands = {x, y};
    } else {
        std::stringstream error;
        error << "ASSERT : completeTypes, a node built by a lowering is neither arithmetic nor "
                 "a delayed read : "
              << ppsig(t, 80) << std::endl;
        throw faustexception(error.str());
    }
    int n = 0, v = 0, c = 0, vec = 0, b = 0;
    for (Tree o : operands) {
        Type to = getCertifiedSigType(o);
        n |= to->nature();
        v |= to->variability();
        c |= to->computability();
        vec |= to->vectorability();
        b |= to->boolean();
    }
    if (taps) {
        v |= kSamp;
    }
    return makeSimpleType(n, v, c, vec, b, unbounded);
}

}  // namespace

namespace {

/// t has no type of this program : none, or for a number, shared by every tree that holds
/// it, the type of another typing that deferred its intervals
bool untyped(Tree t)
{
    int    i;
    double r;
    return t->getType() == nullptr ||
           ((isSigInt(t, &i) || isSigReal(t, &r)) && getSigType(t)->hasDeferredInterval());
}

}  // namespace

void completeTypes(Tree result, const std::unordered_map<Tree, Tree>& memo)
{
    for (const auto& [src, dst] : memo) {
        if (dst != src && untyped(dst) && !untyped(src)) {
            setSigType(dst, getSigType(src));
        }
    }
    // the nodes built of its own, each once its operands are typed : they form no cycle (a
    // recursion is read through its projections, rebuilt from typed sources)
    const Signature          signature = sigs::signalSignature();
    std::unordered_set<Tree> visited;
    std::vector<Tree>        work{result}, pending;
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!visited.insert(t).second) {
            continue;
        }
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) {
                work.push_back(body);
            }
            continue;
        }
        for (int k = 0; k < t->arity(); k++) {
            work.push_back(t->branch(k));
        }
        if (untyped(t) && isSignalNode(t, signature)) {
            pending.push_back(t);
        }
    }
    auto ready = [](Tree t) {
        int  op;
        Tree x, y;
        for (int k = 0; k < t->arity(); k++) {
            if (k == 0 && isSigBinOp(t, &op, x, y)) {
                continue;  // the opcode
            }
            if (untyped(t->branch(k))) {
                return false;
            }
        }
        return true;
    };
    while (!pending.empty()) {
        std::vector<Tree> left;
        for (Tree t : pending) {
            if (!untyped(t)) {
                continue;
            }
            if (ready(t)) {
                setSigType(t, composedType(t));
            } else {
                left.push_back(t);
            }
        }
        if (left.size() == pending.size()) {
            std::stringstream error;
            error << "ASSERT : completeTypes, nodes whose operands stay untyped, as "
                  << ppsig(left.front(), 80) << std::endl;
            throw faustexception(error.str());
        }
        pending = left;
    }
}

void composeImage(std::unordered_map<Tree, Tree>& image, const std::unordered_map<Tree, Tree>& memo)
{
    for (auto& [src, dst] : image) {
        auto it = memo.find(dst);
        if (it != memo.end()) {
            dst = it->second;
        }
    }
}
