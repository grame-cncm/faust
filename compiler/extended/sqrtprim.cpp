#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"
#include "code_container.hh"

class SqrtPrim : public xtended
{

 public:
 
 	SqrtPrim() : xtended("sqrt") {}
	
	virtual unsigned int arity () { return 1; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == 1);
		Type 		t = args[0];
		interval 	i = t->getInterval();
		if (i.valid && i.lo >=0) {
			return castInterval(floatCast(t), interval(sqrt(i.lo), sqrt(i.hi)));
		} else {
			return castInterval(floatCast(t), interval());
		}
	}
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) {
		return args[0];
	}

	virtual Tree	computeSigOutput (const vector<Tree>& args) {
		// verifier les simplifications
		num n;
		if (isNum(args[0],n)) {
			return tree(sqrt(double(n)));
		} else {
			return tree(symbol(), args[0]);
		}
	}
	
    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type>& types)
    {
        assert (args.size() == arity());
		assert (types.size() == arity());
        
        Typed::VarType result_type;
        if (result->nature() == kInt) result_type = Typed::kInt; else result_type = itfloat();
        vector<Typed::VarType> arg_types;
        vector< ::Type>::const_iterator it;
        for (it = types.begin(); it != types.end(); it++) {
            Typed::VarType t1;
            if (((*it)->nature() == kInt)) t1 = Typed::kInt; else t1 = itfloat();
            arg_types.push_back(t1);
        }
        
        return container->pushFunction(subst("sqrt$0", isuffix()), result_type, arg_types, args);
    }

	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("\\sqrt{$0}", args[0]);
	}
	
};


xtended* gSqrtPrim = new SqrtPrim();


