#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"

class SinPrim : public xtended
{

 public:
 
 	SinPrim() : xtended("sin") {}
	
	virtual unsigned int arity () { return 1; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == 1);
		return castInterval(floatCast(args[0]), interval(-1,1));
	}
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) {
		return args[0];
	}

	virtual Tree	computeSigOutput (const vector<Tree>& args) {
		num n;
		if (isNum(args[0],n)) {
			// Symbolic computation of sin(n)
			double x = fmod(n, 2*M_PI);
			if (comparable(x,0)) { // sin(0)
				return tree(0.0);					// sin(0) = 0
			} else if (comparable(x,2*M_PI)){ 		
				return tree(0.0);					// sin(2.PI) = 0
			} else if (comparable(x,M_PI)) {
				return tree(0.0);					// sin(PI) = 0
			} else if (comparable(x,M_PI/2)) {
				return tree(1.0);					// sin(PI/2) = 1
			} else if (comparable(x,3*M_PI/2)) {
				return tree(-1.0);					// sin(3*PI/2) = -1
			} else {
				return tree(sin(x));				// sin(x) 
			}
		} else {
			return tree(symbol(), args[0]);
		}
	}
	
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("sin$1($0)", args[0], isuffix());
	}
	
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("\\sin\\left($0\\right)", args[0]);
	}
	
};


xtended* gSinPrim = new SinPrim();


