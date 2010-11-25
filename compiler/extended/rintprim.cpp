#include "xtended.hh"
#include "compatibility.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"
#include "code_container.hh"

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
        
        return container->pushFunction(subst("rint$0", isuffix()), result_type, arg_types, args);
    }

	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
        
		return subst("\\left[ {$0} \\right]", args[0]);
	}
	
};


xtended* gRintPrim = new RintPrim();


