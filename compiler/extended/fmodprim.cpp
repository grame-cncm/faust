#include <math.h>
#include "Text.hh"
#include "xtended.hh"

#include "floats.hh"

class FmodPrim : public xtended {
   public:
    FmodPrim() : xtended("fmod") {}

    virtual unsigned int arity() { return 2; }

    virtual bool needCache() { return true; }

    virtual Type infereSigType(const vector<Type>& args)
    {
        assert(args.size() == arity());
        interval i = args[0]->getInterval();
        interval j = args[1]->getInterval();

        if (j.haszero()) {
            // potential division by zero
            // std::cerr << "potential division by zero in fmod(" << i << ", " << j << ")" << std::endl;
        }
        return castInterval(floatCast(args[0] | args[1]), fmod(i, j));
    }

    virtual void sigVisit(Tree sig, sigvisitor* visitor) {}

    virtual int infereSigOrder(const vector<int>& args)
    {
        assert(args.size() == arity());
        return max(args[0], args[1]);
    }

    virtual Tree computeSigOutput(const vector<Tree>& args)
    {
        num n, m;
        assert(args.size() == arity());
        if (isNum(args[0], n) & isNum(args[1], m)) {
            return tree(fmod(double(n), double(m)));
        } else {
            return tree(symbol(), args[0], args[1]);
        }
    }

    virtual string generateCode(Klass* klass, const vector<string>& args, const vector<Type>& types)
    {
        assert(args.size() == arity());
        assert(types.size() == arity());

        return subst("fmod$2($0,$1)", args[0], args[1], isuffix());
    }

    virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector<Type>& types)
    {
        assert(args.size() == arity());
        assert(types.size() == arity());

        return subst("$0\\pmod{$1}", args[0], args[1]);
    }
};

xtended* gFmodPrim = new FmodPrim();
