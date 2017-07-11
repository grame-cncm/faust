#include "xtended.hh"
#include "Text.hh"
#include <math.h>
#include "sigtyperules.hh"

#include "floats.hh"
/********************************************************************************************

FTZ is a special primitive injected in recursive signals when the -ftz option is on.
The injected code allows to flush to zero denormalized number. This option should be used only 
when it is not available on the CPU.

*********************************************************************************************/

extern int gFTZMode;
extern int gFloatSize;

const char* FTZPattern[4][3] = {	{"???", "???", "???" },				// not a float
									{"$0", "((fabsf($0)> FLT_MIN) ? $0 : 0.0f)", "((*(int*)&$0) & 0x7F800000) ? $0 : 0.0f" },				// float  (1)
									{"$0", "((fabs ($0)> DBL_MIN) ? $0 : 0.0 )", "((*(long int*)&$0) & 0x7FF0000000000000) ? $0 : 0.0" },	// double (2)
									{"$0", "((fabsl($0)>LDBL_MIN) ? $0 : 0.0L)", "((fabsl($0)>LDBL_MIN) ? $0 : 0.0L)" }						// quad   (3)
							   };

// 0x7FF0000000000000
class FtzPrim : public xtended
{

	static int freshnum;		// counter for fTempFTZxxx fresh variables
	
 public:

 	FtzPrim() : xtended("ftz") {}

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
		assert (args.size() == arity());
		return tree(symbol(), args[0]);
	}


	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());

		Type t = infereSigType(types);
		if ((t->nature() == kReal) && (gFTZMode > 0)) {
			// we need to create a temporary variable to store the expression
			string ctype = ifloat(); 
			string vname = subst("fTempFTZ$0", T(++freshnum));
			klass->addIncludeFile("<float.h>");
            klass->addExecCode(subst("$0 $1 = $2;", ctype, vname, args[0]));
			return subst(FTZPattern[gFloatSize][gFTZMode], vname);
		} else {
			// No ftz code for integer signals
			return args[0];
		}
	}
	
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types)
	{
		assert (args.size() == arity());
		assert (types.size() == arity());
		return args[0];
	}
};


xtended* gFtzPrim = new FtzPrim();
int FtzPrim::freshnum = 0;



