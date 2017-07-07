#ifndef __XTENDED__
#define __XTENDED__

// xtended
#include "tlib.hh"
#include "sigtype.hh"
#include "klass.hh"
#include "sigvisitor.hh"
#include <vector>
#include "lateq.hh"

class xtended 
{
	Symbol*		fSymbol;	///< the symbol the xtended is attached to
 public:
 
 	
 	xtended (const char* name) : 
		fSymbol(::symbol(name)) { 
		setUserData(fSymbol, (void*)this); 
	}
	virtual ~xtended() { setUserData(fSymbol, 0); }
	
	Sym				symbol() 	{ return fSymbol; }
	const char * 	name () 	{ return ::name(fSymbol); }
	
	Tree			box () { 
						Tree b = tree(fSymbol); 
						assert(getUserData(b) != 0); 
						return b; 
					}
	
	// virtual method to be implemented by subclasses
	virtual unsigned int 	arity () = 0;
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types) = 0;
	virtual string 	generateLateq (Lateq* lateq, const vector<string>& args, const vector<Type>& types) = 0;
	virtual int 	infereSigOrder (const vector<int>& args) = 0;
	virtual Type 	infereSigType (const vector<Type>& args) = 0;
	virtual Tree	computeSigOutput (const vector<Tree>& args) = 0;
	virtual bool	needCache () = 0;

    virtual bool    isSpecialInfix()    { return false; }   ///< generaly false, but true for binary op # such that #(x) == _#x
};

// -- Trigonometric Functions

extern xtended* gAcosPrim;
extern xtended* gAsinPrim;
extern xtended* gAtanPrim;
extern xtended* gAtan2Prim;

extern xtended* gSinPrim;
extern xtended* gCosPrim;
extern xtended* gTanPrim;


// -- Exponential Functions

extern xtended* gExpPrim; 		
extern xtended* gLogPrim; 		
extern xtended* gLog10Prim; 
extern xtended* gPowPrim; 
		
extern xtended* gSqrtPrim; 	
extern xtended* gCbrtPrim; 	
extern xtended* gHypotPrim; 
extern xtended* gLdexpPrim; 
extern xtended* gScalbPrim; 
extern xtended* gLog1pPrim; 
extern xtended* gLogbPrim; 	
extern xtended* gIlogbPrim; 
extern xtended* gExpm1Prim; 


// -- Hyperbolic Functions

extern xtended* gAcoshPrim;
extern xtended* gAsinhPrim;
extern xtended* gAtanhPrim;

extern xtended* gSinhPrim;
extern xtended* gCoshPrim;
extern xtended* gTanhPrim;


// -- Remainder Functions

extern xtended* gFmodPrim;
extern xtended* gRemainderPrim;

// -- Nearest Integer Functions

extern xtended* gFloorPrim;
extern xtended* gCeilPrim; 
extern xtended* gRintPrim; 


// -- Miscellaneous Functions

extern xtended* gAbsPrim;
extern xtended* gMaxPrim;
extern xtended* gMinPrim;

extern xtended* gFtzPrim;

#endif
