#include "xtended.hh"
#include "compatibility.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"

#if defined(WIN32) && ! defined(__MINGW32__) 
/* missing on Windows : see http://bugs.mysql.com/bug.php?id=15936 */
inline double rint(double nr)
{
    double f = floor(nr);
    double c = ceil(nr);
    return (((c -nr) >= (nr - f)) ? f : c);
}
#endif

class RintPrim : public xtended
{

 public:
 
 	RintPrim() : xtended("rint") {}
	
	virtual unsigned int arity () { return 1; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == arity());
		interval i = args[0]->getInterval();
		if (i.valid) {
			return castInterval(floatCast(args[0]), interval(rint(i.lo), rint(i.hi)));
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
			return tree(rint(double(n)));
		} else {
			return tree(symbol(), args[0]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());

		return subst("rint$1($0)", args[0], isuffix());
	}
	
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
        
		return subst("\\left[ {$0} \\right]", args[0]);
	}
	
};


xtended* gRintPrim = new RintPrim();


