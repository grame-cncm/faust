#include "xtended.hh"
#include "compatibility.hh"
#include "Text.hh"
#include <math.h>

class RemainderPrim : public xtended
{

 public:
 
 	RemainderPrim() : xtended("remainder") {}
	
	virtual unsigned int arity () { return 2; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == arity());
		return floatCast(args[0]|args[1]);
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
			return tree(fmodf(float(n), float(m)));
		} else {
			return tree(symbol(), args[0], args[1]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		return subst("remainderf($0, $1)", args[0], args[1]);
	}
	
};


xtended* gRemainderPrim = new RemainderPrim();


