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

class AsinPrim : public xtended {
   public:
    AsinPrim() : xtended("asin") {}

    virtual unsigned int arity() { return 1; }

    virtual bool needCache() { return true; }

    virtual ::Type inferSigType(ConstTypes args)
    {
        faustassert(args.size() == 1);
        Type     t = args[0];
        interval i = t->getInterval();
        if (i.isValid() && gGlobal->gMathExceptions && (i.lo() < -1 || i.hi() > 1)) {
            std::stringstream error;
            error << "WARNING : potential out of domain in asin(" << i << ")" << std::endl;
            gWarningMessages.push_back(error.str());
        }
        return castInterval(t, gAlgebra.Asin(i));
    }

    virtual int inferSigOrder(const std::vector<int>& args) { return args[0]; }

    virtual Tree computeSigOutput(const std::vector<Tree>& args)
    {
        num n;
        if (isNum(args[0], n)) {
            if ((double(n) < -1) || (double(n) > 1)) {
                std::stringstream error;
                error << "ERROR : out of domain in asin(" << ppsig(args[0], MAX_ERROR_SIZE) << ")" << std::endl;
                throw faustexception(error.str());
            } else {
                return tree(asin(double(n)));
            }
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return generateFun(container, subst("asin$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("asin$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\arcsin\\left($0\\right)", args[0]);
    }
    
    Tree diff(const std::vector<Tree> &args) override
    {
        // (asin(x))' = 1 / sqrt(1 - x^2), -1 < x < 1
        return sigDiv(sigReal(1.0), sigSqrt(sigSub(sigReal(1.0), sigPow(args[0], sigReal(2.0)))));
    }
};
