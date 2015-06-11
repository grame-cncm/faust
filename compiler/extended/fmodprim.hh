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

class FmodPrim : public xtended
{

 public:

 	FmodPrim() : xtended("fmod") {}

	virtual unsigned int arity () { return 2; }

	virtual bool needCache ()	{ return true; }

	virtual ::Type infereSigType (const vector< ::Type>& args)
	{
		assert (args.size() == arity());
        interval i = args[0]->getInterval();
        interval j = args[1]->getInterval();

        if (j.haszero()) {
            // potential division by zero
            //std::cerr << "potential division by zero in fmod(" << i << ", " << j << ")" << std::endl;
        }
        
		return castInterval(floatCast(args[0]|args[1]), fmod(i,j));
	}

	virtual void sigVisit (Tree sig, sigvisitor* visitor) {}

	virtual int infereSigOrder (const vector<int>& args) {
		assert (args.size() == arity());
		return max(args[0], args[1]);
	}

	virtual Tree computeSigOutput (const vector<Tree>& args) {
		num n,m;
		assert (args.size() == arity());
		if (isNum(args[0],n) & isNum(args[1],m)) {
			return tree(fmod(double(n), double(m)));
		} else {
			return tree(symbol(), args[0], args[1]);
		}
	}

    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type> const& types)
    {
        assert(args.size() == arity());
		assert(types.size() == arity());
        
        Typed::VarType result_type;
        vector<Typed::VarType> arg_types;
        list<ValueInst*> casted_args;
        prepareTypeArgsResult(result, args, types, result_type, arg_types, casted_args);
     
        return container->pushFunction(subst("fmod$0", isuffix()), result_type, arg_types, casted_args);
    }

	virtual string generateLateq (Lateq* lateq, const vector<string>& args, const vector< ::Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());

		return subst("$0\\pmod{$1}", args[0], args[1]);
	}

};

