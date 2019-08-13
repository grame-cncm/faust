/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

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

    unsigned int arity() override { return 1; }

    bool needCache() override { return true; }

    ::Type infereSigType(const vector< ::Type>& args) override
    {
        faustassert(args.size() == 1);
        interval     srcInterval = args[0]->getInterval();
        const double halfpi      = M_PI / 2;
        interval     resultInterval;

        // the check can be improved to ensure that no infinity is in the range
        if (srcInterval.valid) {
            if ((-halfpi < srcInterval.lo) && (srcInterval.hi < halfpi))
                resultInterval = interval(tan(srcInterval.lo), tan(srcInterval.hi));
        }
        return castInterval(floatCast(args[0]), resultInterval);
    }

    virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

    int infereSigOrder(const vector<int>& args) override { return args[0]; }

    Tree computeSigOutput(const vector<Tree>& args) override
    {
        num n;
        if (isNum(args[0], n)) {
            return tree(tan(double(n)));
        } else {
            return tree(symbol(), args[0]);
        }
    }

    ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result,
                            vector< ::Type> const& types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        Typed::VarType         result_type;
        vector<Typed::VarType> arg_types;
        list<ValueInst*>       casted_args;
        prepareTypeArgsResult(result, args, types, result_type, arg_types, casted_args);

        return container->pushFunction(subst("tan$0", isuffix()), result_type, arg_types, casted_args);
    }

    string old_generateCode(Klass* klass, const vector<string>& args, const vector<Type>& types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("tan$1($0)", args[0], isuffix());
    }

    string generateLateq(Lateq* lateq, const vector<string>& args, const vector< ::Type>& types) override
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\tan\\left($0\\right)", args[0]);
    }
};
