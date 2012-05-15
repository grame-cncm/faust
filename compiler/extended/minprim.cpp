#include "xtended.hh"
#include "Text.hh"
#include <math.h>
#include "sigtyperules.hh"

#include "floats.hh"

class MinPrim : public xtended
{

 public:
 
 	MinPrim() : xtended("min") {}
	
	virtual unsigned int arity () { return 2; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& types)
	{
		assert (types.size() == arity());
		interval i = types[0]->getInterval();
		interval j = types[1]->getInterval();
		return castInterval(types[0]|types[1], min(i,j));
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
				return tree(min(f, g));
			} else if (isInt(args[1]->node(),&j)) {
				return tree(min(f, double(j)));
			} else {
				return tree(symbol(), args[0], args[1]);
			}
				
		} else if (isInt(args[0]->node(),&i)) {
		
			if (isDouble(args[1]->node(), &g)) {
				return tree(min(double(i), g));
			} else if (isInt(args[1]->node(),&j)) {
				return tree(min(i, j));
			} else {
				return tree(symbol(), args[0], args[1]);
			}
				
		} else {
		
			return tree(symbol(), args[0], args[1]);
		}
	}
		
//	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
//	{
//		assert (args.size() == arity());
//		assert (types.size() == arity());
////
////		Type t = infereSigType(types);
////		if (t->nature() == kReal) {
////			return subst("min($0, $1)", args[0], args[1]);
////		} else {
////			return subst("min($0, $1)", args[0], args[1]);
////		}

//		// generates code compatible with overloaded min
//		int n0 = types[0]->nature();
//		int n1 = types[1]->nature();
//		if (n0==n1) {
//			return subst("min($0, $1)", args[0], args[1]);
//		} else {
//			if (n0==kInt) {
//				return subst("min($2$0, $1)", args[0], args[1], icast());
//			} else {
//				return subst("min($0, $2$1)", args[0], args[1], icast());
//			}
//		}
//	}

    virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
    {
        assert (args.size() == arity());
        assert (types.size() == arity());

        // generates code compatible with overloaded min
        int n0 = types[0]->nature();
        int n1 = types[1]->nature();
        if (n0==kReal) {
            if (n1==kReal) {
                // both are floats, no need to cast
                return subst("min($0, $1)", args[0], args[1]);
            } else {
                assert(n1==kInt); // second argument is not float, cast it to float
                return subst("min($0, $2$1)", args[0], args[1], icast());
            }
        } else if (n1==kReal) {
            assert(n0==kInt); // first not float but second is, cast first to float
            return subst("min($2$0, $1)", args[0], args[1], icast());
        } else {
            assert(n0==kInt);  assert(n1==kInt);   // both are integers, check for booleans
            int b0 = types[0]->boolean();
            int b1 = types[1]->boolean();
            if (b0==kNum) {
                if (b1==kNum) {
                    // both are integers, no need to cast
                    return subst("min($0, $1)", args[0], args[1]);
                } else {
                    assert(b1==kBool);    // second is boolean, cast to int
                    return subst("min($0, (int)$1)", args[0], args[1]);
                }
            } else if (b1==kNum) {
                assert(b0==kBool);    // first is boolean, cast to int
                return subst("min((int)$0, $1)", args[0], args[1], icast());
            } else {
                assert(b0==kBool); assert(b1==kBool);   // both are booleans, no need to cast
                return subst("min((int)$0, (int)$1)", args[0], args[1]);
            }
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


