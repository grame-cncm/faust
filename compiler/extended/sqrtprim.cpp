#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"


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
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("sqrt$1($0)", args[0], isuffix());
	}
	
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("\\sqrt{$0}", args[0]);
	}
	
};


xtended* gSqrtPrim = new SqrtPrim();


