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

        // -mapp : the approximation, exact on the certified interval of x (approxRound.hh)
        if (approxRoundApplies(types[0])) {
            return genApproxRound(container, args.front(), true);
        }
        return generateFun(container, subst("ceil$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        if (approxRoundApplies(types[0])) {
            klass->rememberNeedApproxRoundDef();
            return subst("faust_ceil_approx($0)", args[0]);
        }
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
