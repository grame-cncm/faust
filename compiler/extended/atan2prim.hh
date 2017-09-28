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
#include "floats.hh"

class Atan2Prim : public xtended
{

 public:

 	Atan2Prim() : xtended("atan2") {}

	virtual unsigned int arity() { return 2; }

	virtual bool needCache() { return true; }

	virtual ::Type infereSigType(const vector< ::Type>& args)
	{
		faustassert(args.size() == 2);
		return floatCast(args[0]|args[1]);
	}

	virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

	virtual int infereSigOrder(const vector<int>& args) {
		return max(args[0], args[1]);
	}

	virtual Tree computeSigOutput(const vector<Tree>& args)
	{
		faustassert(args.size() == 2);
		num n,m;
		if (isNum(args[0],n) && isNum(args[1],m)) {
			return tree(atan2(double(n), double(m)));
		} else {
			return tree(symbol(), args[0], args[1]);
		}
	}

    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type> const & types)
    {
        faustassert(args.size() == arity());
		faustassert(types.size() == arity());
        
        Typed::VarType result_type;
        vector<Typed::VarType> arg_types;
        list<ValueInst*> casted_args;
        prepareTypeArgsResult(result, args, types, result_type, arg_types, casted_args);

        return container->pushFunction(subst("atan2$0", isuffix()), result_type, arg_types, casted_args);
    }
    
    virtual string 	old_generateCode(Klass* klass, const vector<string>& args, const vector<Type>& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        
        return subst("atan2$2($0,$1)", args[0], args[1], isuffix());
    }

	virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector< ::Type>& types)
	{
		faustassert(args.size() == arity());
		faustassert(types.size() == arity());

        return subst("\\arctan\\frac{$0}{$1}", args[0], args[1]);
	}

};

