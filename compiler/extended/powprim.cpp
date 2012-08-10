#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"

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
        //return castInterval(args[0]|args[1], interval()); // temporary !!!
        
        interval i = args[0]->getInterval();
		interval j = args[1]->getInterval();
		return castInterval(args[0]|args[1], pow(i,j));

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


