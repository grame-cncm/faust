#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"

class CosPrim : public xtended
{

 public:
 
 	CosPrim() : xtended("cos") {}
	
	virtual unsigned int 	arity () { return 1; }
	
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
			// Symbolic computation of cos(n)
			double x = fmod(n, 2*M_PI);
			if (comparable(x,0)) { // cos(0)
				return tree(1.0);					// cos(0) = 1
			} else if (comparable(x,2*M_PI)){ 		
				return tree(1.0);					// cos(2.PI) = 1
			} else if (comparable(x,M_PI)) {
				return tree(-1.0);					// cos(PI) = -1
			} else if (comparable(x,M_PI/2)) {
				return tree(0.0);					// cos(PI/2) = 0
			} else if (comparable(x,3*M_PI/2)) {
				return tree(0.0);					// cos(3.PI/2) = 0
			} else {
				return tree(cos(x));				// cos(x) 
			}
		} else {
			return tree(symbol(), args[0]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("cos$1($0)", args[0], isuffix());
	}
	
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
        return subst("\\cos\\left($0\\right)", args[0]);
	}
	
};


xtended* gCosPrim = new CosPrim();


