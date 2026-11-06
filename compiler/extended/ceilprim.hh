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
#include "xtendedCodegen.hh"
#include "global.hh"

class CeilPrim : public xtendedCodegen {
   public:
    CeilPrim() : xtendedCodegen("ceil") {}
    /// a primitive that computes ceil too : its approximated form (CeilApproxPrim)
    explicit CeilPrim(const char* name) : xtendedCodegen(name) {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }


    virtual Tree computeSigOutput(const std::vector<Tree>& args) override
    {
        num n;
        faustassert(args.size() == arity());
        if (isNum(args[0], n)) {
            return tree(ceil(double(n)));
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    std::vector< ::Type> const& types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        // the exact function : the approximation under -mapp is CeilApproxPrim, chosen by the
        // computation form (computeForm.hh)
        return generateFun(container, subst("ceil$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("ceil$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\left\\lceil $0 \\right\\rceil", args[0]);
    }

    double compute(const std::vector<Node>& args) override { return ceil(args[0].getDouble()); }
};

/**
 * ceil under -mapp, where the certified interval of the operand lies inside the int32 range
 * (approxRoundApplies) : computed from the integer conversion, the same value bit for bit
 * there (approxRound.hh). The computation form chooses it in place of ceil
 * (computeForm.hh) ; the normal form never holds it.
 */
class CeilApproxPrim : public CeilPrim {
   public:
    CeilApproxPrim() : CeilPrim("ceil_approx") {}

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        return genApproxRound(container, args.front(), true);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        klass->rememberNeedApproxRoundDef();
        return subst("faust_ceil_approx($0)", args[0]);
    }
};

