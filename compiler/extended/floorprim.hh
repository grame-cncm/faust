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

#include <math.h>
#include "Text.hh"
#include "approxRound.hh"

#include "floats.hh"
#include "sigtyperules.hh"
#include "xtendedCodegen.hh"
#include "global.hh"

class FloorPrim : public xtendedCodegen {
   public:
    FloorPrim() : xtendedCodegen("floor") {}
    /// a primitive that computes floor too : its approximated form (FloorApproxPrim)
    explicit FloorPrim(const char* name) : xtendedCodegen(name) {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }


    virtual Tree computeSigOutput(const std::vector<Tree>& args) override
    {
        num n;
        faustassert(args.size() == arity());
        if (isNum(args[0], n)) {
            return tree(floor(double(n)));
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        // the exact function : the approximation under -mapp is FloorApproxPrim, chosen by the
        // computation form (computeForm.hh)
        return generateFun(container, subst("floor$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("floor$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\left\\lfloor {$0} \\right\\rfloor", args[0]);
    }

    double compute(const std::vector<Node>& args) override { return floor(args[0].getDouble()); }
};

/**
 * floor under -mapp, where the certified interval of the operand lies inside the int32 range
 * (approxRoundApplies) : computed from the integer conversion, the same value bit for bit
 * there (approxRound.hh). The computation form chooses it in place of floor
 * (computeForm.hh) ; the normal form never holds it.
 */
class FloorApproxPrim : public FloorPrim {
   public:
    FloorApproxPrim() : FloorPrim("floor_approx") {}

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        return genApproxRound(container, args.front(), false);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        klass->rememberNeedApproxRoundDef();
        return subst("faust_floor_approx($0)", args[0]);
    }
};

