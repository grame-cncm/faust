#include "xtended.hh"
#include "Text.hh"
#include <math.h>vector<::Type>
#include "sigtyperules.hh"

#include "floats.hh"
#include "code_container.hh"

class MinPrim : public xtended
{

 public:

 	MinPrim() : xtended("min") {}

	virtual unsigned int arity () { return 2; }

	virtual bool needCache ()	{ return true; }

	virtual ::Type infereSigType (const vector< ::Type>& types)
	{
		assert (types.size() == arity());
		interval i = types[0]->getInterval();
		interval j = types[1]->getInterval();
		return castInterval(types[0]|types[1], min(i,j));
	}

	virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

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
				return tree(min(f, g));
			} else if (isInt(args[1]->node(), &j)) {
				return tree(min(f, double(j)));
			} else {
				return tree(symbol(), args[0], args[1]);
			}

		} else if (isInt(args[0]->node(), &i)) {

			if (isDouble(args[1]->node(), &g)) {
				return tree(min(double(i), g));
			} else if (isInt(args[1]->node(), &j)) {
				return tree(min(i, j));
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
        
        if (result->nature() == kInt) {
            result_type = Typed::kInt; 
        } else {
            result_type = itfloat();
        }
        
        // generates code compatible with overloaded max
		int n0 = types[0]->nature();
		int n1 = types[1]->nature();
        if (n0 == kReal) {
        
            // prepare args types
            arg_types.push_back(itfloat());
            arg_types.push_back(itfloat());
            
            if (n1 == kReal) {
                // both are floats, no need to cast
                return container->pushFunction("min", result_type, arg_types, args);
            } else {
                assert(n1 == kInt); // second argument is not float, cast it to float
                // prepare args values
                list<ValueInst*>::const_iterator it2 = args.begin();
                casted_args.push_back((*it2));
                it2++;
                casted_args.push_back(InstBuilder::genCastNumInst((*it2), InstBuilder::genBasicTyped(itfloat())));
                return container->pushFunction("min", result_type, arg_types, casted_args);
            }
        } else if (n1 == kReal) {
            assert(n0 == kInt); // first not float but second is, cast first to float
            
            // prepare args types
            arg_types.push_back(itfloat());
            arg_types.push_back(itfloat()); 
            
            // prepare args values
            list<ValueInst*>::const_iterator it2 = args.begin();
            casted_args.push_back(InstBuilder::genCastNumInst((*it2), InstBuilder::genBasicTyped(itfloat())));
            it2++;
            casted_args.push_back((*it2));
            return container->pushFunction("min", result_type, arg_types, casted_args);
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
                    return container->pushFunction("min", result_type, arg_types, args);
                } else {
                    assert(b1 == kBool);    // second is boolean, cast to int
                    // prepare args values
                    list<ValueInst*>::const_iterator it2 = args.begin();
                    casted_args.push_back((*it2));
                    it2++;
                    casted_args.push_back(InstBuilder::genCastNumInst((*it2), InstBuilder::genBasicTyped(Typed::kInt)));
                    return container->pushFunction("min", result_type, arg_types, casted_args);
                }
            } else if (b1 == kNum) {
                assert(b0 == kBool);    // first is boolean, cast to int
                // prepare args values
                list<ValueInst*>::const_iterator it2 = args.begin();
                casted_args.push_back(InstBuilder::genCastNumInst((*it2), InstBuilder::genBasicTyped(Typed::kInt)));
                it2++;
                casted_args.push_back((*it2));
                return container->pushFunction("min", result_type, arg_types, casted_args);
            } else {
                assert(b0 == kBool); assert(b1 == kBool);   // both are booleans, cast both
                list<ValueInst*>::const_iterator it2 = args.begin();
                casted_args.push_back(InstBuilder::genCastNumInst((*it2), InstBuilder::genBasicTyped(Typed::kInt)));
                it2++;
                casted_args.push_back(InstBuilder::genCastNumInst((*it2), InstBuilder::genBasicTyped(Typed::kInt)));
                return container->pushFunction("min", result_type, arg_types, casted_args);
            }
        }
    }
    
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());

		::Type t = infereSigType(types);
		return subst("\\min\\left( $0, $1 \\right)", args[0], args[1]);
	}

};


xtended* gMinPrim = new MinPrim();


