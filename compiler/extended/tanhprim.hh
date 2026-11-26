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
#include "xtendedCodegen.hh"
#include "exception.hh"

// tanh has no word in the language : the primitive is reached through the declaration of the
// C function as a foreign function (propagate.cpp, hyperbolicPrimitive).
class TanhPrim : public xtendedCodegen {
   public:
    TanhPrim() : xtendedCodegen("tanh") {}

    virtual unsigned int arity() override { return 1; }

    virtual bool needCache() override { return true; }

    virtual Tree computeSigOutput(const std::vector<Tree>& args) override
    {
        num n;
        if (isNum(args[0], n)) {
            return tree(tanh(double(n)));
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, Values& args, ::Type result,
                                    ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        // the version without a call (xtendedCodegen.hh)
        if (ValueInst* v = generateInlineMath(container, "tanh", args, types)) {
            return v;
        }
        return generateFun(container, subst("tanh$0", isuffix()), args, result, types);
    }

    virtual std::string generateCode(Klass* klass, const std::vector<std::string>& args,
                                     ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        const std::string v = inlineMathFunction("tanh", types);
        if (!v.empty()) {
            return subst("$1($0)", args[0], v);
        }
        return subst("tanh$1($0)", args[0], isuffix());
    }

    virtual std::string generateLateq(Lateq* lateq, const std::vector<std::string>& args,
                                      ConstTypes types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\tanh\\left($0\\right)", args[0]);
    }

    double compute(const std::vector<Node>& args) override { return tanh(args[0].getDouble()); }
};
