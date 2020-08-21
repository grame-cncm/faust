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

#include <math.h>

#include "Text.hh"
#include "floats.hh"
#include "xtended.hh"

class DownsamplingPrim : public xtended {
   public:
    DownsamplingPrim() : xtended("downsampling") {}

    virtual unsigned int arity() { return 2; }

    virtual bool needCache() { return true; }

    virtual bool is(Tree t, Tree& x, Tree& y)
    {
        if (getUserData(t) == this) {
            x = t->branch(0);
            y = t->branch(1);
            return true;
        } else {
            return false;
        }
    }

    virtual ::Type infereSigType(const vector<::Type>& args)
    {
        faustassert(args.size() == arity());

        return args[0];  // samplin doesn't change the type of the input signal (but maybe variability ?)
    }

    virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

    virtual int infereSigOrder(const vector<int>& args)
    {
        faustassert(args.size() == arity());
        return max(1, args[0]);  // TEMP: to avoid problems in mterm
    }

    virtual Tree computeSigOutput(const vector<Tree>& args)
    {
        num n, m;
        faustassert(args.size() == arity());
        return tree(symbol(), args[0], args[1]);
    }

    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result,
                                    vector<::Type> const& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        Typed::VarType         result_type;
        vector<Typed::VarType> arg_types;
        list<ValueInst*>       casted_args;
        prepareTypeArgsResult(result, args, types, result_type, arg_types, casted_args);

        return container->pushFunction(subst("sampling$0", isuffix()), result_type, arg_types, casted_args);
    }

    virtual string old_generateCode(Klass* klass, const vector<string>& args, const vector<::Type>& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return args[0];  // nothing to do in principle
    }

    virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector<::Type>& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return args[0];  // TODO: not correct we need to indicate sampling
    }
};
