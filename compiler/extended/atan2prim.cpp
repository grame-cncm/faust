#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"

class Atan2Prim : public xtended
{

 public:
 
 	Atan2Prim() : xtended("atan2") {}
	
	virtual unsigned int 	arity () { return 2; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == 2);
		return floatCast(args[0]|args[1]);
	}
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) {
		return max(args[0], args[1]);
	}

	
	virtual Tree	computeSigOutput (const vector<Tree>& args) 
	{
		assert (args.size() == 2);
		num n,m;
		if (isNum(args[0],n) && isNum(args[1],m)) {
			return tree(atan2(double(n), double(m)));
		} else {
			return tree(symbol(), args[0], args[1]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("atan2$2($0,$1)", args[0], args[1], isuffix());
	}
	
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("\\arctan\\frac{$0}{$1}", args[0], args[1]);
	}
	
};


xtended* gAtan2Prim = new Atan2Prim();


