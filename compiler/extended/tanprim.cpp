#include "xtended.hh"
#include "Text.hh"
#include <math.h>

#include "floats.hh"
#include "code_container.hh"

class TanPrim : public xtended
{

 public:

 	TanPrim() : xtended("tan") {}

	virtual unsigned int arity () { return 1; }

	virtual bool	needCache ()	{ return true; }

	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == 1);
        interval srcInterval = args[0]->getInterval();
        const double halfpi = M_PI/2;
        interval resultInterval;

        // the check can be improved to ensure that no infinity is in the range
        if (srcInterval.valid) {
            if ( (-halfpi < srcInterval.lo ) && (srcInterval.hi < halfpi) )
                resultInterval = interval(tan(srcInterval.lo), tan(srcInterval.hi));
        }
		return castInterval(floatCast(args[0]), resultInterval);
	}

	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}

	virtual int infereSigOrder (const vector<int>& args) {
		return args[0];
	}

	virtual Tree	computeSigOutput (const vector<Tree>& args) {
		num n;
		if (isNum(args[0],n)) {
			return tree(tan(double(n)));
		} else {
			return tree(symbol(), args[0]);
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

        return container->pushFunction(subst("tan$0", isuffix()), result_type, arg_types, args);
    }

	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());

        return subst("\\tan\\left($0\\right)", args[0]);
	}

};


xtended* gTanPrim = new TanPrim();


