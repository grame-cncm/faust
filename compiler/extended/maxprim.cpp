#include "xtended.hh"
#include "Text.hh"
#include <math.h>
#include "sigtyperules.hh"

#include "floats.hh"
#include "code_container.hh"

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
		double f,g; int i,j;
		
		assert (args.size() == arity());
		
		if (isDouble(args[0]->node(),&f)) {
		
			if (isDouble(args[1]->node(), &g)) {
				return tree(max(f, g));
			} else if (isInt(args[1]->node(),&j)) {
				return tree(max(f, double(j)));
			} else {
				return tree(symbol(), args[0], args[1]);
			}
				
		} else if (isInt(args[0]->node(),&i)) {
		
			if (isDouble(args[1]->node(), &g)) {
				return tree(max(double(i), g));
			} else if (isInt(args[1]->node(),&j)) {
				return tree(max(i, j));
			} else {
				return tree(symbol(), args[0], args[1]);
			}
				
		} else {
		
			return tree(symbol(), args[0], args[1]);
		}
	}
    
    virtual ValueInst* generateCode(int variability, CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type>& types)
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
        
        Type t = infereSigType(types);
		if (t->nature() == kReal) {
			return container->pushFunction("max", result_type, arg_types, args);
		} else {
			return container->pushFunction("max", result_type, arg_types, args);
		} 
    }
	
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		
		Type t = infereSigType(types);
		return subst("\\max\\left( $0, $1 \\right)", args[0], args[1]);
	}
	
};


xtended* gMaxPrim = new MaxPrim();


