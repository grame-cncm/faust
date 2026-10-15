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

#pragma once

#include <string>

#include "floats.hh"
#include "global.hh"
#include "instructions.hh"
#include "sigtype.hh"

/**
 * floor and ceil under -mapp : a lowering at code generation. With r = T(int(x)),
 *
 *     floor(x) = (x == r) ? x : (x >= 0 ? r : r - 1)
 *     ceil(x)  = (x == r) ? x : (x >= 0 ? r + 1 : r)
 *
 * The conversion truncates toward 0 and is exact for |x| < 2^31 : there both formulas give
 * floor and ceil bit for bit. The signals keep floor and ceil, so that the analysis bounds
 * them as such (x - floor(x) is a fractional part in [0, 1[) ; the approximation is emitted
 * only when the certified interval of x lies inside the int32 range, the exact function
 * otherwise. Single and double precision only.
 */
inline bool approxRoundApplies(::Type x)
{
    if (!gGlobal->gMathApprox || x->nature() != kReal) return false;
    if (gGlobal->gFloatSize != 1 && gGlobal->gFloatSize != 2) return false;
    const itv::interval i = x->getInterval();
    return i.isValid() && !i.isEmpty() && i.lo() > -2147483648.0 && i.hi() < 2147483647.0;
}

/// the call of the helper that computes floor (up = false) or ceil (up = true) of arg
inline ValueInst* genApproxRound(CodeContainer* container, ValueInst* arg, bool up)
{
    const Typed::VarType t   = itfloat();
    const std::string    sfx = (t == Typed::kFloat) ? "_f" : "_d";
    const std::string    x   = "approx_x" + sfx;
    const std::string    r   = "approx_r" + sfx;
    const std::string    name = container->getClassName() + (up ? "_faustceil" : "_faustfloor") + sfx;

    Names args;
    args.push_back(IB::genNamedTyped(x, IB::genBasicTyped(t)));
    BlockInst* block = IB::genBlockInst();
    ValueInst* trunc = IB::genCastInt32Inst(IB::genLoadFunArgsVar(x));
    block->pushBackInst(IB::genDecStackVar(r, t, IB::genCastRealInst(trunc)));
    ValueInst* one   = IB::genRealNumInst(t, 1.0);
    ValueInst* zero  = IB::genRealNumInst(t, 0.0);
    ValueInst* step  = up ? IB::genAdd(IB::genLoadStackVar(r), one) : IB::genSub(IB::genLoadStackVar(r), one);
    ValueInst* pos   = IB::genGreaterEqual(IB::genLoadFunArgsVar(x), zero);
    ValueInst* inner = up ? IB::genSelect2Inst(pos, step, IB::genLoadStackVar(r))
                          : IB::genSelect2Inst(pos, IB::genLoadStackVar(r), step);
    ValueInst* isint = IB::genEqual(IB::genLoadFunArgsVar(x), IB::genLoadStackVar(r));
    block->pushBackInst(IB::genRetInst(IB::genSelect2Inst(isint, IB::genLoadFunArgsVar(x), inner)));
    container->pushGlobalDeclare(
        IB::genDeclareFunInst(name, IB::genFunTyped(args, IB::genBasicTyped(t), FunTyped::kLocal), block));

    Values call;
    call.push_back(arg);
    return IB::genFunCallInst(name, call);
}
