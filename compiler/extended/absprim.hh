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
#include "code_container.hh"
#include "floats.hh"
#include "sigtyperules.hh"
#include "xtended.hh"

class AbsPrim : public xtended {
   public:
    AbsPrim() : xtended("abs") {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }

    virtual ::Type inferSigType(ConstTypes args) override
    {
        faustassert(args.size() == arity());
        Type t = args[0];
        interval i = t->getInterval();
        return castInterval(t, gAlgebra.Abs(i));
    }

    virtual int inferSigOrder(const std::vector<int>& args) override
    {
        faustassert(args.size() == arity());
        return args[0];
    }

    virtual Tree computeSigOutput(const std::vector<Tree>& args) override
    {
        double f;
        int    i;
        faustassert(args.size() == arity());

        // abs(abs(sig)) ==> abs(sig)
        xtended* xt = (xtended*)getUserData(args[0]);
        if (xt == gGlobal->gAbsPrim) {
            return args[0];

        } else if (isDouble(args[0]->node(), &f)) {
            return tree(fabs(f));

        } else if (isInt(args[0]->node(), &i)) {
            return tree(abs(i));

        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        /*
         04/25/22 : this optimisation cannot be done because interval computation is buggy: like no.noise interval
         [O..inf] !
         */

        /*
            if (i.isValid() && i.lo() >= 0) {
                return *args.begin();
            } else {
                // Only compute abs when arg is < 0
                if (t->nature() == kReal) {
                    Values cargs;
                    prepareTypeArgsResult(result, args, types, rtype, atypes, cargs);
                    return container->pushFunction(subst("fabs$0", isuffix()), rtype, atypes, cargs);
                } else {
                    // "Int" abs
                    rtype = Typed::kInt32;
                    atypes.push_back(Typed::kInt32);
                    return container->pushFunction("abs", rtype, atypes, args);
                }
            }
        */

        std::string fun_name = (result->nature() == kInt) ? "abs" : subst("fabs$0", isuffix());
        return generateFun(container, fun_name, args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        Type t = inferSigType(types);
        if (t->nature() == kReal) {
            return subst("fabs$1($0)", args[0], isuffix());
        } else {
            return subst("abs($0)", args[0]);
        }
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args, ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        ::Type t = inferSigType(types);
        return subst("\\left\\lvert{$0}\\right\\rvert", args[0]);
    }
    
    Tree diff(const std::vector<Tree> &args) override
    {
        // |x|' = x / |x|, x != 0
        return sigSelect2(sigEQ(args[0], sigReal(0.0)),
                          sigReal(0.0),
                          sigDiv(args[0], sigAbs(args[0]))
        );
    }
};
