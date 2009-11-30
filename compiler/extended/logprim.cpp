#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"

class LogPrim : public xtended
{

 public:
 
 	LogPrim() : xtended("log") {}
	
	virtual unsigned int arity () { return 1; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == arity());
		interval i = args[0]->getInterval();
		if (i.valid & i.lo>0) {
			return castInterval(floatCast(args[0]), interval(log(i.lo), log(i.hi)));
		} else {
			return floatCast(args[0]);
		}
	}
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) {
		assert (args.size() == arity());
		return args[0];
	}

	
	virtual Tree	computeSigOutput (const vector<Tree>& args) {
		num n;
		assert (args.size() == arity());
		if (isNum(args[0],n)) {
			return tree(log(double(n)));
		} else {
			return tree(symbol(), args[0]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
        
		return subst("log$1($0)", args[0], isuffix());
	}
	
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
        
		return subst("\\ln\\left( $0 \\right)", args[0]);
	}
	
};


xtended* gLogPrim = new LogPrim();


