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

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class TanPrim : public xtended {
   public:
    TanPrim() : xtended("tan") {}

    virtual unsigned int arity() { return 1; }

    virtual bool needCache() { return true; }

    virtual ::Type inferSigType(ConstTypes args)
    {
        faustassert(args.size() == 1);
        interval     i = args[0]->getInterval();
        interval     r = gAlgebra.Tan(i);
        // The check can be improved to ensure that no infinity is in the range
        /*
         if (i.isValid()) {
            if ((-halfpi < i.lo()) && (i.hi() < halfpi)) {
                r = interval(tan(i.lo()), tan(i.hi()));
            }
        }
        */
        return castInterval(floatCast(args[0]), r);
    }

    virtual int inferSigOrder(const std::vector<int>& args) { return args[0]; }

    virtual Tree computeSigOutput(const std::vector<Tree>& args)
    {
        num n;
        if (isNum(args[0], n)) {
            return tree(tan(double(n)));
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return generateFun(container, subst("tan$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("tan$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\tan\\left($0\\right)", args[0]);
    }
    
    Tree diff(const std::vector<Tree> &args) override
    {
        // (tan(x))' = sec^2(x) = 1 / cos^2(x)
        // TODO: handle division by zero
        return sigDiv(sigReal(1.0), sigPow(sigCos(args[0]), sigReal(2.0)));
    }
};
