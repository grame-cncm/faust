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

/********************************************************************************************

FTZ is a special primitive injected in recursive signals when the -ftz option is on.
The injected code allows to flush to zero denormalized number. This option should be used only 
when it is not available on the CPU.

*********************************************************************************************/

class FtzPrim : public xtended
{

 public:

 	FtzPrim() : xtended("ftz") {}

	virtual unsigned int arity () { return 1; }

	virtual bool needCache() { return true; }

	virtual Type infereSigType(const vector<Type>& types)
	{
		faustassert(types.size() == arity());
		return types[0];
	}

	virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

	virtual int infereSigOrder(const vector<int>& args)
	{
		faustassert(args.size() == arity());
		return args[0];
	}

	virtual Tree computeSigOutput(const vector<Tree>& args)
	{
		faustassert(args.size() == arity());
		return tree(symbol(), args[0]);
	}

	virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type> const & types)
	{
		faustassert(args.size() == arity());
		faustassert(types.size() == arity());

		Type t = infereSigType(types);
		if (t->nature() == kReal) {
            
            // "fabs" function has to be declared
            list<NamedTyped*> args_types;
            args_types.push_back(InstBuilder::genNamedTyped("dummy", InstBuilder::genBasicTyped(itfloat())));
            FunTyped* fun_type = InstBuilder::genFunTyped(args_types, InstBuilder::genBasicTyped(itfloat()));
            container->pushGlobalDeclare(InstBuilder::genDeclareFunInst(subst("fabs$0", isuffix()), fun_type));
            
			// we need to create a temporary variable to store the expression
			string vname = gGlobal->getFreshID("fTempFTZ");
            container->addIncludeFile("<float.h>");
            container->pushComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(itfloat()), *args.begin()));
            ValueInst* real_min;
            if (gGlobal->gFloatSize == 1) {
                real_min = InstBuilder::genFloatNumInst(inummin());
            } else {
                real_min = InstBuilder::genDoubleNumInst(inummin());
            }
            
            list<ValueInst*> args_value;
            args_value.push_back(InstBuilder::genLoadStackVar(vname));
            return InstBuilder::genSelect2Inst(InstBuilder::genGreaterThan(InstBuilder::genFunCallInst(subst("fabs$0", isuffix()), args_value), real_min),
                                               InstBuilder::genLoadStackVar(vname),
                                               InstBuilder::genTypedZero(itfloat()));
      	} else {
			// No ftz code for integer signals
			return *args.begin();
		}
	}
	
	virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		faustassert(args.size() == arity());
		faustassert(types.size() == arity());
		return args[0];
	}
};



