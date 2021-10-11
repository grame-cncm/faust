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

class LogPrim : public xtended {
   public:
    LogPrim() : xtended("log") {}

    virtual unsigned int arity() { return 1; }

    virtual bool needCache() { return true; }

    virtual ::Type infereSigType(const vector<::Type>& args)
    {
        faustassert(args.size() == arity());
        interval i = args[0]->getInterval();
    
        if (i.valid) {
            // log(0) gives -INF but is still in the function domain
            if (i.lo >= 0) {
                return castInterval(floatCast(args[0]), interval(log(i.lo), log(i.hi)));
            } else if (gGlobal->gMathExceptions) {
                cerr << "WARNING : potential out of domain in log(" << i << ")" << endl;
            }
        }
        return floatCast(args[0]);
    }

    virtual int infereSigOrder(const vector<int>& args)
    {
        faustassert(args.size() == arity());
        return args[0];
    }

    virtual Tree computeSigOutput(const vector<Tree>& args)
    {
        num n;
        faustassert(args.size() == arity());
    
        // log(exp(sig)) ==> sig
        xtended* xt = (xtended*)getUserData(args[0]);
        if (xt == gGlobal->gExpPrim) {
            return args[0]->branch(0);
        } else if (isNum(args[0], n)) {
            if (double(n) < 0) {
                stringstream error;
                error << "ERROR : out of domain log(" << ppsig(args[0]) << ")" << endl;
                throw faustexception(error.str());
            } else {
                return tree(log(double(n)));
            }
        } else {
            return tree(symbol(), args[0]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result,
                                    vector< ::Type> const& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        Typed::VarType         result_type;
        vector<Typed::VarType> arg_types;
        list<ValueInst*>       casted_args;
        prepareTypeArgsResult(result, args, types, result_type, arg_types, casted_args);

        return container->pushFunction(subst("log$0", isuffix()), result_type, arg_types, casted_args);
    }

    virtual string old_generateCode(Klass* klass, const vector<string>& args, const vector<::Type>& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("log$1($0)", args[0], isuffix());
    }

    virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector<::Type>& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());

        return subst("\\ln\\left( $0 \\right)", args[0]);
    }
};
