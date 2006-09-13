#include "xtended.hh"
#include "Text.hh"
#include <math.h>
#include "sigtyperules.hh"

class MaxPrim : public xtended
{

 public:
 
 	MaxPrim() : xtended("max") {}
	
	virtual unsigned int arity () { return 2; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& types)
	{
		assert (types.size() == arity());
		interval i = types[0]->getInterval();
		interval j = types[1]->getInterval();
		return castInterval(types[0]|types[1], max(i,j));
	}
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) 
	{
		assert (args.size() == arity());
		return max(args[0], args[1]);
	}

	
	virtual Tree	computeSigOutput (const vector<Tree>& args) 
	{
		float f,g; int i,j;
		
		assert (args.size() == arity());
		
		if (isFloat(args[0]->node(),&f)) {
		
			if (isFloat(args[1]->node(), &g)) {
				return tree(max(f, g));
			} else if (isInt(args[1]->node(),&j)) {
				return tree(max(f, float(j)));
			} else {
				return tree(symbol(), args[0], args[1]);
			}
				
		} else if (isInt(args[0]->node(),&i)) {
		
			if (isFloat(args[1]->node(), &g)) {
				return tree(max(float(i), g));
			} else if (isInt(args[1]->node(),&j)) {
				return tree(max(i, j));
			} else {
				return tree(symbol(), args[0], args[1]);
			}
				
		} else {
		
			return tree(symbol(), args[0], args[1]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
		Type t = infereSigType(types);
		if (t->nature() == kReal) {
			return subst("max($0, $1)", args[0], args[1]);
		} else {
			return subst("max($0, $1)", args[0], args[1]);
		} 			
	}
	
};


xtended* gMaxPrim = new MaxPrim();


