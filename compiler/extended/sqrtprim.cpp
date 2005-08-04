#include "xtended.hh"
#include "Text.hh"
#include <math.h>


class SqrtPrim : public xtended
{

 public:
 
 	SqrtPrim() : xtended("sqrt") {}
	
	virtual int 	arity () { return 1; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == 1);
		return floatCast(args[0]);
	}
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) {
		return args[0];
	}

	
	virtual Tree	computeSigOutput (const vector<Tree>& args) {
		// verifier les simplifications
		num n;
		if (isNum(args[0],n)) {
			return tree(sqrtf(float(n)));
		} else {
			return tree(symbol(), args[0]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		return subst("sqrtf($0)", args[0]);
	}
	
};


xtended* gSqrtPrim = new SqrtPrim();


