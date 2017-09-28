/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#include "xtended.hh"
#include "Text.hh"
#include "sigtyperules.hh"
#include "floats.hh"
#include "code_container.hh"

class AbsPrim : public xtended
{

 public:

 	AbsPrim() : xtended("abs") {}

	virtual unsigned int arity() { return 1; }

	virtual bool needCache() { return true; }

	virtual ::Type infereSigType(const vector< ::Type>& types)
	{
		faustassert(types.size() == arity());
		Type t = types[0];
		return castInterval(t, abs(t->getInterval()));
		return t;
	}

	virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

	virtual int infereSigOrder(const vector<int>& args)
	{
		faustassert(args.size() == arity());
		return args[0];
	}

	virtual Tree computeSigOutput(const vector<Tree>& args)
	{
		double f; int i;

		faustassert(args.size() == arity());

		if (isDouble(args[0]->node(),&f)) {
			return tree(fabs(f));

		} else if (isInt(args[0]->node(),&i)) {
			return tree(abs(i));

		} else {
			return tree(symbol(), args[0]);
		}
	}
    
    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type> const & types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        
        Typed::VarType result_type;
        vector<Typed::VarType> arg_types;
       
        ::Type t = infereSigType(types);
        if (t->nature() == kReal) {
            list<ValueInst*> casted_args;
            prepareTypeArgsResult(result, args, types, result_type, arg_types, casted_args);
            return container->pushFunction(subst("fabs$0", isuffix()), result_type, arg_types, casted_args);
        } else {
            // "Int" abs
            result_type = Typed::kInt32;
            arg_types.push_back(Typed::kInt32);
            return container->pushFunction("abs", result_type, arg_types, args);
        }
    }
    
    virtual string old_generateCode(Klass* klass, const vector<string>& args, const vector<Type>& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        
        Type t = infereSigType(types);
        if (t->nature() == kReal) {
            return subst("fabs$1($0)", args[0], isuffix());
        } else {
            return subst("abs($0)", args[0]);
        }
    }

	virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector< ::Type>& types)
	{
		faustassert(args.size() == arity());
		faustassert(types.size() == arity());

		::Type t = infereSigType(types);
		return subst("\\left\\lvert{$0}\\right\\rvert", args[0]);
	}
    
};


