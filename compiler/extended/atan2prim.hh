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
#include "floats.hh"
#include "xtended.hh"

class Atan2Prim : public xtended {
   public:
    Atan2Prim() : xtended("atan2") {}

    virtual unsigned int arity() override { return 2; }

    virtual bool needCache() override { return true; }

    virtual ::Type inferSigType(ConstTypes args) override
    {
        faustassert(args.size() == 2);
        Type t = args[0];
        Type u = args[1];
        interval i = t->getInterval();
        interval j = u->getInterval();
        return castInterval(floatCast(t | u), gAlgebra.Atan2(i, j));
    }

    virtual int inferSigOrder(const std::vector<int>& args) override { return std::max(args[0], args[1]); } 

    virtual Tree computeSigOutput(const std::vector<Tree>& args) override
    {
        faustassert(args.size() == 2);
        num n, m;
        if (isNum(args[0], n) && isNum(args[1], m)) {
            return tree(atan2(double(n), double(m)));
        } else {
            return tree(symbol(), args[0], args[1]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return generateFun(container, subst("atan2$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("atan2$2($0,$1)", args[0], args[1], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\arctan\\frac{$0}{$1}", args[0], args[1]);
    }
};
