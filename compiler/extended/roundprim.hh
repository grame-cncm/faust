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
#include "compatibility.hh"
#include "floats.hh"
#include "xtended.hh"

class RoundPrim : public xtended {
   public:
    RoundPrim() : xtended("round") {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }

    virtual ::Type inferSigType(ConstTypes args) override
    {
        faustassert(args.size() == arity());
        interval i = args[0]->getInterval();
        if (i.isValid()) {
            // TODO: Round is missing in interval library
            return castInterval(floatCast(args[0]), gAlgebra.Rint(i));
        } else {
            return floatCast(args[0]);
        }
    }

    virtual int inferSigOrder(const std::vector<int>& args) override
    {
        faustassert(args.size() == arity());
        return args[0];
    }

    virtual Tree computeSigOutput(const std::vector<Tree>& args) override
    {
        num n;
        faustassert(args.size() == arity());
        if (isNum(args[0], n)) {
            return tree(rint(double(n)));
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return generateFun(container, subst("round$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("round$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\left[ {$0} \\right]", args[0]);
    }
    
    Tree diff(const std::vector<Tree> &args) override
    {
        // (round(x))' = 0, cos(pi * x) != 0
        return getCertifiedSigType(args[0])->nature() == kInt ? sigInt(0) : sigReal(0.0);
    }
};
