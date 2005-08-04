#include "xtended.hh"
#include "Text.hh"
#include <math.h>
#include "sigtyperules.hh"

class MinPrim : public xtended
{

 public:
 
 	MinPrim() : xtended("min") {}
	
	virtual int 	arity () { return 2; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& types)
	{
		assert (types.size() == arity());
		return types[0]|types[1];
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
				return tree(min(f, g));
			} else if (isInt(args[1]->node(),&j)) {
				return tree(min(f, float(j)));
			} else {
				return tree(symbol(), args[0], args[1]);
			}
				
		} else if (isInt(args[0]->node(),&i)) {
		
			if (isFloat(args[1]->node(), &g)) {
				return tree(min(float(i), g));
			} else if (isInt(args[1]->node(),&j)) {
				return tree(min(i, j));
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
			return subst("min($0, $1)", args[0], args[1]);
		} else {
			return subst("min($0, $1)", args[0], args[1]);
		} 			
	}
	
};


xtended* gMinPrim = new MinPrim();


