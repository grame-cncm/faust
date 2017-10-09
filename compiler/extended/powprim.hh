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
#include "global.hh"

class PowPrim : public xtended
{

 public:

 	PowPrim() : xtended("pow") {}
   
	virtual unsigned int arity() { return 2; }

	virtual bool needCache() { return true; }

	virtual Type infereSigType(const vector<Type>& args)
	{
		faustassert(args.size() == arity());
    
        interval i = args[0]->getInterval();
		interval j = args[1]->getInterval();
		return castInterval(args[0]|args[1], pow(i,j));
    }

	virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

	virtual int infereSigOrder (const vector<int>& args)
    {
		faustassert(args.size() == arity());
		return max(args[0], args[1]);
	}

    virtual Tree computeSigOutput(const vector<Tree>& args)
    {
        num n,m;
        faustassert(args.size() == arity());
        if (isNum(args[0],n) && isNum(args[1],m)) {
            return tree(pow(double(n), double(m)));
        } else if (isNum(args[0],n) && (double(n) == 10.) && gGlobal->gHasExp10) {
            // pow(10, x) ==> exp10(x)
            return tree(::symbol("exp10"), args[1]);
        } else {
            return tree(symbol(), args[0], args[1]);
        }
    }

    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type> const & types)
    {
        faustassert(args.size() == arity());
		faustassert(types.size() == arity());

        vector<Typed::VarType> arg_types(2);
        vector< ::Type>::const_iterator it1;
        Typed::VarType result_type = (result->nature() == kInt) ? Typed::kInt32 : itfloat();
       
        list<ValueInst*>::const_iterator it = args.begin();
        it++;
        Int32NumInst* arg1 = dynamic_cast<Int32NumInst*>(*it);

        if ((types[1]->nature() == kInt)
            && (types[1]->variability() == kKonst)
            && (types[1]->computability() == kComp)
            && arg1
            && (gGlobal->gOutputLang != "interp")
            && (gGlobal->gOutputLang != "ajs")
            && !(startWith(gGlobal->gOutputLang, "wast"))
            && !(startWith(gGlobal->gOutputLang, "wasm"))) { // In 'interpreter' and 'wast/wasm' backends, do not generate 'faustpower' function call, fallback to 'pow'

            arg_types[0] = (types[0]->nature() == kInt) ? Typed::kInt32 : itfloat();
            arg_types[1] = Typed::kInt32;
            return container->pushFunction(container->getFaustPowerName(), result_type, arg_types, args);

        } else {

            // Both arguments forced to itfloat()
            arg_types[0] = itfloat();
            arg_types[1] = itfloat();
  
            list<ValueInst*> casted_args;
            list<ValueInst*>::const_iterator it2 = args.begin();
    
            for (it1 = types.begin(); it1 != types.end(); it1++, it2++) {
                casted_args.push_back(promote2real((*it1)->nature(), (*it2))); 
            }
            
            return cast2int(result->nature(), container->pushFunction(subst("pow$0", isuffix()), itfloat(), arg_types, casted_args));
        }
    }
    
    virtual string old_generateCode(Klass* klass, const vector<string>& args, const vector<Type>& types)
    {
        faustassert(args.size() == arity());
        faustassert(types.size() == arity());
        
        if ((types[1]->nature() == kInt) && (types[1]->variability() == kKonst) && (types[1]->computability() == kComp)) {
            klass->rememberNeedPowerDef();
            return subst("faustpower<$1>($0)", args[0], args[1]);
        } else {
            return subst("pow$2($0,$1)", args[0], args[1], isuffix());
        }
    }

 	virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector< ::Type>& types)
	{
		faustassert(args.size() == arity());
		faustassert(types.size() == arity());

		return subst("{$0}^{$1}", args[0], args[1]);
	}

    // power is now used as an infix binary operator, we return true to
    // indicate that we want ^(n) to be equivalent to _^n
    virtual bool isSpecialInfix()    { return true; }

};

