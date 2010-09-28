#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"
#include "code_gen.hh"
#include "code_container.hh"

class PowPrim : public xtended
{

 public:
 
 	PowPrim() : xtended("powf") {}
	
	virtual unsigned int arity () { return 2; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == arity());
        //return castInterval(floatCast(args[0]|args[1]), interval()); // temporary !!!
        return castInterval(args[0]|args[1], interval()); // temporary !!!
    }
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) {
		assert (args.size() == arity());
		return max(args[0], args[1]);
	}

	virtual Tree	computeSigOutput (const vector<Tree>& args) {
		num n,m;
		assert (args.size() == arity());
		if (isNum(args[0],n) & isNum(args[1],m)) {
			return tree(pow(double(n), double(m)));
		} else {
			return tree(symbol(), args[0], args[1]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());

        if (types[1]->nature() == kInt) {
            klass->rememberNeedPowerDef();
            return subst("faustpower<$1>($0)", args[0], args[1]);
        } else {
            return subst("pow$2($0,$1)", args[0], args[1], isuffix());
        }
    }
	
    virtual ValueInst* generateCode(int variability, CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type>& types)
    {
        assert (args.size() == arity());
		assert (types.size() == arity());
        
        /*
        if (types[1] == Typed::kInt) {
            return container->pushFunction("llvm.powi.f32", types, args);
        } else {
            return container->pushFunction(subst("pow$0", isuffix()), types, args);
        }
        */
        
        Typed::VarType result_type;
        if (result->nature() == kInt) result_type = Typed::kInt; else result_type = itfloat();
        vector<Typed::VarType> arg_types;
        vector< ::Type>::const_iterator it1;
        for (it1 = types.begin(); it1 != types.end(); it1++) {
            arg_types.push_back(itfloat());
        }
        
        list<ValueInst*> casted_args;
        list<ValueInst*>::const_iterator it2;
         
        for (it2 = args.begin(); it2 != args.end(); it2++) {
            casted_args.push_back(InstBuilder::genCastNumInst((*it2), InstBuilder::genBasicTyped(itfloat())));
        }
        
        return container->pushFunction(subst("pow$0", isuffix()), result_type, arg_types, casted_args);
        
        /*
        if (types[1] == Typed::kInt) {
            return container->pushFunction("faustpower", result_type, types, args);
        } else {
            // Force float types for both arguments
            types[0] = Typed::kFloat;
            types[1] = Typed::kFloat;
            
            list<ValueInst*> casted_args;
            list<ValueInst*>::const_iterator it;
             
            for (it = args.begin(); it != args.end(); it++) {
                casted_args.push_back(InstBuilder::genCastNumInst((*it), InstBuilder::genBasicTyped(Typed::kFloat)));
            }
            
            return container->pushFunction(subst("pow$0", isuffix()), result_type, types, casted_args);
        }
        */
    }
    
 	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
        
		return subst("{$0}^{$1}", args[0], args[1]);
	}

    // power is now used as an infix binary operator, we return true to
    // indicate that we want ^(n) to be equivalent to _^n
    virtual bool    isSpecialInfix()    { return true; }
	
};


xtended* gPowPrim = new PowPrim();


