#include "xtended.hh"
#include "Text.hh"
#include <math.h>
#include "sigtyperules.hh"

#include "floats.hh"
#include "code_container.hh"

class MinPrim : public xtended
{

 public:

 	MinPrim() : xtended("min") {}

	virtual unsigned int arity () { return 2; }

	virtual bool needCache ()	{ return true; }

	virtual Type infereSigType (const vector<Type>& types)
	{
		assert (types.size() == arity());
		interval i = types[0]->getInterval();
		interval j = types[1]->getInterval();
		return castInterval(types[0]|types[1], min(i,j));
	}

	virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

	virtual int infereSigOrder(const vector<int>& args)
	{
		assert (args.size() == arity());
		return max(args[0], args[1]);
	}

	virtual Tree computeSigOutput(const vector<Tree>& args)
	{
		double f,g; int i,j;

		assert (args.size() == arity());

		if (isDouble(args[0]->node(), &f)) {

			if (isDouble(args[1]->node(), &g)) {
				return tree(min(f, g));
			} else if (isInt(args[1]->node(), &j)) {
				return tree(min(f, double(j)));
			} else {
				return tree(symbol(), args[0], args[1]);
			}

		} else if (isInt(args[0]->node(), &i)) {

			if (isDouble(args[1]->node(), &g)) {
				return tree(min(double(i), g));
			} else if (isInt(args[1]->node(), &j)) {
				return tree(min(i, j));
			} else {
				return tree(symbol(), args[0], args[1]);
			}

		} else {

			return tree(symbol(), args[0], args[1]);
		}
	}

    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result, vector< ::Type> const & types)
    {
        assert(args.size() == arity());
		assert(types.size() == arity());
        
        Typed::VarType result_type;
        vector<Typed::VarType> arg_types;
        list<ValueInst*> casted_args;
        prepareTypeArgsResult(result, args, types, result_type, arg_types, casted_args);
         
        // generates code compatible with overloaded min
		int n0 = types[0]->nature();
		int n1 = types[1]->nature();
		if (n0 == n1) {
	        return container->pushFunction("min", result_type, arg_types, args);	
		} else {
            return container->pushFunction("min", result_type, arg_types, casted_args);	
		}	
    }

	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());

		Type t = infereSigType(types);
		return subst("\\min\\left( $0, $1 \\right)", args[0], args[1]);
	}

};


xtended* gMinPrim = new MinPrim();


