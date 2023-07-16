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

class RemainderPrim : public xtended {
   public:
    RemainderPrim() : xtended("remainder") {}

    virtual unsigned int arity() { return 2; }

    virtual bool needCache() { return true; }

    virtual ::Type inferSigType(ConstTypes args)
    {
        faustassert(args.size() == arity());

        interval i = args[0]->getInterval();
        interval j = args[1]->getInterval();
        if (j.isValid() && gGlobal->gMathExceptions && j.hasZero()) {
            std::stringstream error;
            error << "WARNING : potential division by zero in remainder(" << i << ", " << j << ")" << std::endl;
            gWarningMessages.push_back(error.str());
        }

        return castInterval(floatCast(args[0] | args[1]), gAlgebra.Remainder(i));  // temporary rule !!!
    }

    virtual int inferSigOrder(const std::vector<int>& args)
    {
        faustassert(args.size() == arity());
        return std::max(args[0], args[1]);
    }

    virtual Tree computeSigOutput(const std::vector<Tree>& args)
    {
        num n, m;
        faustassert(args.size() == arity());
        if (isZero(args[1])) {
            std::stringstream error;
            error << "ERROR : remainder by 0 in remainder(" << ppsig(args[0], MAX_ERROR_SIZE) << ", " << ppsig(args[1], MAX_ERROR_SIZE) << ")" << std::endl;
            throw faustexception(error.str());
        } else if (isNum(args[0], n) && isNum(args[1], m)) {
            return tree(remainder(double(n), double(m)));
        } else {
            if (gGlobal->gMathApprox) {
                // res = x - (y * T(int(0.5f + x / y)));
                return sigSub(
                    args[0],
                    sigBinOp(kMul, args[1], sigFloatCast(sigIntCast(sigAdd(sigReal(0.5), sigDiv(args[0], args[1]))))));
            } else {
                return tree(symbol(), args[0], args[1]);
            }
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return generateFun(container, subst("remainder$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("remainder$2($0,$1)", args[0], args[1], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("$0\\pmod{$1}", args[0], args[1]);  // Same as fmodprim.cpp.
    }
};
