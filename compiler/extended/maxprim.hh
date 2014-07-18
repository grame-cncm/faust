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

class MaxPrim : public xtended
{

 public:

 	MaxPrim() : xtended("max") {}

	virtual unsigned int arity () { return 2; }

	virtual bool needCache ()	{ return true; }

	virtual ::Type infereSigType(const vector< ::Type>& types)
	{
		assert (types.size() == arity());
		interval i = types[0]->getInterval();
		interval j = types[1]->getInterval();
		return castInterval(types[0]|types[1], max(i,j));
	}

	virtual void sigVisit (Tree sig, sigvisitor* visitor) {}

	virtual int infereSigOrder(const vector<int>& args)
	{
		assert (args.size() == arity());
		return max(args[0], args[1]);
	}

	virtual Tree computeSigOutput(const vector<Tree>& args)
	{
		double f,g; int i,j;

		assert (args.size() == arity());

		if (isDouble(args[0]->node(), &f)) {

			if (isDouble(args[1]->node(), &g)) {
				return tree(max(f, g));
			} else if (isInt(args[1]->node(), &j)) {
				return tree(max(f, double(j)));
			} else {
				return tree(symbol(), args[0], args[1]);
			}

		} else if (isInt(args[0]->node(), &i)) {

			if (isDouble(args[1]->node(), &g)) {
				return tree(max(double(i), g));
			} else if (isInt(args[1]->node(), &j)) {
				return tree(max(i, j));
			} else {
				return tree(symbol(), args[0], args[1]);
			}

		} else {

			return tree(symbol(), args[0], args[1]);
		}
	}

    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type> const &types)
    {
        assert(args.size() == arity());
		assert(types.size() == arity());
        
        Typed::VarType result_type;
        vector<Typed::VarType> arg_types;
        list<ValueInst*> casted_args;
        
        result_type = (result->nature() == kInt) ? Typed::kInt : itfloat();
        
        // generates code compatible with overloaded max
		int n0 = types[0]->nature();
		int n1 = types[1]->nature();
        if (n0 == kReal) {
        
            // prepare args types
            arg_types.push_back(itfloat());
            arg_types.push_back(itfloat());
            
            if (n1 == kReal) {
                // both are floats, no need to cast
                return container->pushFunction("max", result_type, arg_types, args);
            } else {
                assert(n1 == kInt); // second argument is not float, cast it to float
                // prepare args values
                list<ValueInst*>::const_iterator it2 = args.begin();
                casted_args.push_back((*it2));
                it2++;
                casted_args.push_back(InstBuilder::genCastNumFloatInst(*it2));
                return container->pushFunction("max", result_type, arg_types, casted_args);
            }
        } else if (n1 == kReal) {
            assert(n0 == kInt); // first not float but second is, cast first to float
            
            // prepare args types
            arg_types.push_back(itfloat());
            arg_types.push_back(itfloat()); 
            
            // prepare args values
            list<ValueInst*>::const_iterator it2 = args.begin();
            casted_args.push_back(InstBuilder::genCastNumFloatInst(*it2));
            it2++;
            casted_args.push_back((*it2));
            return container->pushFunction("max", result_type, arg_types, casted_args);
        } else {
            assert(n0 == kInt);  assert(n1 == kInt);   // both are integers, check for booleans
            int b0 = types[0]->boolean();
            int b1 = types[1]->boolean();
            
            // prepare args types
            arg_types.push_back(Typed::kInt);
            arg_types.push_back(Typed::kInt); 

            if (b0 == kNum) {
                if (b1 == kNum) {
                    // both are integers, no need to cast
                    return container->pushFunction("max", result_type, arg_types, args);
                } else {
                    assert(b1 == kBool);    // second is boolean, cast to int
                    // prepare args values
                    list<ValueInst*>::const_iterator it2 = args.begin();
                    casted_args.push_back((*it2));
                    it2++;
                    casted_args.push_back(InstBuilder::genCastNumIntInst(*it2));
                    return container->pushFunction("max", result_type, arg_types, casted_args);
                }
            } else if (b1 == kNum) {
                assert(b0 == kBool);    // first is boolean, cast to int
                // prepare args values
                list<ValueInst*>::const_iterator it2 = args.begin();
                casted_args.push_back(InstBuilder::genCastNumIntInst(*it2));
                it2++;
                casted_args.push_back((*it2));
                return container->pushFunction("max", result_type, arg_types, casted_args);
            } else {
                assert(b0 == kBool); assert(b1 == kBool);   // both are booleans, cast both
                list<ValueInst*>::const_iterator it2 = args.begin();
                casted_args.push_back(InstBuilder::genCastNumIntInst(*it2));
                it2++;
                casted_args.push_back(InstBuilder::genCastNumIntInst(*it2));
                return container->pushFunction("max", result_type, arg_types, casted_args);
            }
        }
    }
  	
	virtual string generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());

		::Type t = infereSigType(types);
		return subst("\\max\\left( $0, $1 \\right)", args[0], args[1]);
	}

};

