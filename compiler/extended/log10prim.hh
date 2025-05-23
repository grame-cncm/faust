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

class Log10Prim : public xtended {
   public:
    Log10Prim() : xtended("log10") {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }

    virtual ::Type inferSigType(ConstTypes args) override
    {
        faustassert(args.size() == arity());
        Type     t = args[0];
        interval i = t->getInterval();
        if (i.isValid() && i.lo() < 0 && gGlobal->gMathExceptions) {
            std::stringstream error;
            error << "WARNING : potential out of domain in log10(" << i << ")" << std::endl;
            gWarningMessages.push_back(error.str());
        }
        return castInterval(floatCast(t), gAlgebra.Log10(i));
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

        // log10(exp10(sig)) ==> sig
        xtended* xt = (xtended*)getUserData(args[0]);
        if (xt == gGlobal->gExp10Prim) {
            return args[0]->branch(0);
        } else if (isNum(args[0], n)) {
            if (double(n) < 0) {
                std::stringstream error;
                error << "ERROR : out of domain in log10(" << ppsig(args[0], MAX_ERROR_SIZE) << ")"
                      << std::endl;
                throw faustexception(error.str());
            } else {
                return tree(log10(double(n)));
            }
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return generateFun(container, subst("log10$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("log10$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\log_{10}\\left( $0 \\right)", args[0]);
    }

    Tree diff(const std::vector<Tree>& args) override
    {
        // (log_10(x))' = 1/(x * ln(10))
        // TODO: handle division by zero
        return sigDiv(sigReal(1.0), sigMul(args[0], sigLog(sigReal(10.0))));
    }

    double compute(const std::vector<Node>& args) override { return log10(args[0].getDouble()); }
};
