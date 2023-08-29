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

class LogPrim : public xtended {
   public:
    LogPrim() : xtended("log") {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }

    virtual ::Type inferSigType(ConstTypes args) override
    {
        faustassert(args.size() == arity());
        Type t = args[0];
        interval i = t->getInterval();

        if (i.isValid()) {
            // log(0) gives -INF but is still in the function domain
            if (i.lo() >= 0) {
                return castInterval(floatCast(args[0]), interval(log(i.lo()), log(i.hi())));
            } else if (gGlobal->gMathExceptions) {
                std::stringstream error;
                error << "WARNING : potential out of domain in log(" << i << ")" << std::endl;
                gWarningMessages.push_back(error.str());
            }
        }
        return castInterval(floatCast(t), gAlgebra.Log(i));
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

        // log(exp(sig)) ==> sig
        xtended* xt = (xtended*)getUserData(args[0]);
        if (xt == gGlobal->gExpPrim) {
            return args[0]->branch(0);
        } else if (isNum(args[0], n)) {
            if (double(n) < 0) {
                std::stringstream error;
                error << "ERROR : out of domain in log(" << ppsig(args[0], MAX_ERROR_SIZE) << ")" << std::endl;
                throw faustexception(error.str());
            } else {
                return tree(log(double(n)));
            }
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return generateFun(container, subst("log$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("log$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\ln\\left( $0 \\right)", args[0]);
    }
    
    Tree diff(const std::vector<Tree> &args) override
    {
        // (ln(x))' = 1/x
        // TODO: handle division by zero
        return sigDiv(sigReal(1.0), args[0]);
    }
};
