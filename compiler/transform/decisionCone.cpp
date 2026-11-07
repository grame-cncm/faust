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

#include <vector>

#include "binop.hh"
#include "computeSignals.hh"
#include "decisionCone.hh"
#include "global.hh"
#include "xtended.hh"

namespace {

bool isNumber(Tree t)
{
    double v;
    int    i;
    return isSigReal(t, &v) || isSigInt(t, &i);
}

/// a function that jumps : its result moves by a step when its operand crosses a point
bool isDiscontinuousPrim(Tree t)
{
    void* p = sigXtendedData(t);
    return p != nullptr &&
           (p == gGlobal->gFloorPrim || p == gGlobal->gCeilPrim || p == gGlobal->gRintPrim ||
            p == gGlobal->gFloorApproxPrim || p == gGlobal->gCeilApproxPrim ||
            p == gGlobal->gRoundPrim || p == gGlobal->gFmodPrim || p == gGlobal->gRemainderPrim);
}

}  // namespace

std::unordered_set<Tree> decisionCone(Tree L, bool discontinuities)
{
    std::unordered_set<Tree> seen, cone;
    std::vector<Tree>        work{L}, roots;
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!seen.insert(t).second) {
            continue;
        }
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) {
                work.push_back(body);
            }
            continue;
        }
        for (int i = 0; i < t->arity(); i++) {
            work.push_back(t->branch(i));
        }
        Tree x, y, d, tbl, sz, gen, sf, ch, part;
        if (isSigDelay(t, x, d) && !isNumber(d)) {
            roots.push_back(d);
        }
        if (isSigIntCast(t, x)) {
            roots.push_back(x);
        }
        if (isSigRDTbl(t, tbl, x)) {
            roots.push_back(x);
        }
        if (isSigWRTbl(t, sz, gen, x, d)) {
            roots.push_back(x);
        }
        if (isSigSoundfileBuffer(t, sf, ch, part, x)) {
            roots.push_back(part);
            roots.push_back(x);
        }
        if (isSigSoundfileLength(t, sf, part) || isSigSoundfileRate(t, sf, part)) {
            roots.push_back(part);
        }
        if (!discontinuities) {
            continue;
        }
        int  op;
        Tree sel;
        tvec bt, br;
        if (isSigBinOp(t, &op, x, y) && isBoolOpcode(op)) {
            roots.push_back(x);
            roots.push_back(y);
        } else if (isSigSelect2(t, sel, x, y)) {
            roots.push_back(sel);
        } else if (isFracNode(t, x) || isSigCfrac(t, x)) {
            roots.push_back(x);
        } else if (isPhaseNode(t, x, y)) {
            roots.push_back(x);
            roots.push_back(y);
        } else if (isSigBpf(t, x, bt, br)) {
            roots.push_back(x);
        } else if (isDiscontinuousPrim(t)) {
            for (int i = 0; i < t->arity(); i++) {
                roots.push_back(t->branch(i));
            }
        }
    }
    while (!roots.empty()) {
        Tree t = roots.back();
        roots.pop_back();
        if (!cone.insert(t).second) {
            continue;
        }
        Tree var, body;
        if (isRec(t, var, body)) {
            if (body != nullptr) {
                roots.push_back(body);
            }
            continue;
        }
        for (int i = 0; i < t->arity(); i++) {
            roots.push_back(t->branch(i));
        }
    }
    return cone;
}
