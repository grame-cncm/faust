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
#include "xtendedCodegen.hh"
#include "global.hh"
#include "sumLayout.hh"

// abs of an int as the generated code computes it : abs(INT_MIN) is INT_MIN (faust_wrap_abs)
static inline int wrapAbs(int i)
{
    return (i < 0) ? int(0u - (unsigned int)i) : i;
}

class AbsPrim : public xtendedCodegen {
   public:
    AbsPrim() : xtendedCodegen("abs") {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }

    virtual std::string fname(int type) override
    {
        return (type == kInt) ? "abs" : subst("fabs$0", isuffix());
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
            return tree(wrapAbs(i));

        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        /*
         04/25/22 : this optimisation cannot be done because interval computation is buggy: like
         no.noise interval [O..inf] !
         */

        /*
            if (i.isValid() && i.lo() >= 0) {
                return *args.begin();
            } else {
                // Only compute abs when arg is < 0
                if (t->nature() == kReal) {
                    Values cargs;
                    prepareTypeArgsResult(result, args, types, rtype, atypes, cargs);
                    return container->pushFunction(subst("fabs$0", isuffix()), rtype, atypes,
           cargs); } else {
                    // "Int" abs
                    rtype = Typed::kInt32;
                    atypes.push_back(Typed::kInt32);
                    return container->pushFunction("abs", rtype, atypes, args);
                }
            }
        */

        // abs(INT_MIN) is undefined in C and C++ : the defined form of the container, where
        // the argument may be INT_MIN
        const bool  wrap = (gGlobal->gOutputLang == "cpp" || gGlobal->gOutputLang == "c") && absWraps(types[0]);
        std::string fun_name =
            (result->nature() == kInt) ? (wrap ? "faust_wrap_abs" : "abs") : subst("fabs$0", isuffix());
        return generateFun(container, fun_name, args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        if (types[0]->nature() == kReal) {  // abs keeps its argument's nature
            return subst("fabs$1($0)", args[0], isuffix());
        } else {
            return subst(absWraps(types[0]) ? "faust_wrap_abs($0)" : "abs($0)", args[0]);
        }
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\left\\lvert{$0}\\right\\rvert", args[0]);
    }

    double compute(const std::vector<Node>& args) override
    {
        double f;
        int    i;
        if (isDouble(args[0], &f)) {
            return fabs(f);
        } else if (isInt(args[0], &i)) {
            return wrapAbs(i);
        } else {
            faustassert(false);
            return 0;
        }
    }
};
