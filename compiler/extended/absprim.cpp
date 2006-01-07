#include "xtended.hh"
#include "Text.hh"
#include <math.h>
#include "sigtyperules.hh"

class AbsPrim : public xtended
{

 public:
 
 	AbsPrim() : xtended("abs") {}
	
	virtual unsigned int 	arity () { return 1; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& types)
	{
		assert (types.size() == arity());
		return types[0];
	}
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) 
	{
		assert (args.size() == arity());
		return args[0];
	}

	
	virtual Tree	computeSigOutput (const vector<Tree>& args) 
	{
		float f; int i;
		
		assert (args.size() == arity());
		
		if (isFloat(args[0]->node(),&f)) {
			return tree(fabs(f));
				
		} else if (isInt(args[0]->node(),&i)) {
			return tree(abs(i));
			
		} else {
			return tree(symbol(), args[0]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
		Type t = infereSigType(types);
		if (t->nature() == kReal) {
			return subst("fabsf($0)", args[0]);
		} else {
			return subst("abs($0)", args[0]);
		} 			
	}
	
};


xtended* gAbsPrim = new AbsPrim();


