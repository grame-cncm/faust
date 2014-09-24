/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _BINOP_
#define _BINOP_

#include "node.hh"

typedef const Node	(*comp) (const Node& a, const Node& b);
typedef bool 		(*pred) (const Node& a);

bool falsePredicate(Node const & a);

// Use in in static table so not Garbageable
struct BinOp
{
	const char*	fName;
    const char*	fNameVec;
  	const char*	fNameScal;
    const char*	fNameLLVMInt;
    const char*	fNameLLVMFloat;

    unsigned int fLlvmIntInst;
    unsigned int fLlvmFloatInst;

	comp 		fCompute;
	pred		fLeftNeutral;
	pred		fRightNeutral;
    pred        fLeftAbsorbing;
    pred        fRightAbsorbing;
	int			fPriority;
	//
	BinOp (const char* name, const char* namevec,
            const char* namescal,
            const char* namellvmint,
            const char* namellvmfloat,
            unsigned int llvmint,
            unsigned int llvmfloat,
            comp f,
            pred ln,
            pred rn,
            int priority,
            pred la = falsePredicate,
            pred ra = falsePredicate
          )
			: fName(name), fNameVec(namevec), fNameScal(namescal),
            fNameLLVMInt(namellvmint), fNameLLVMFloat(namellvmfloat),
            fLlvmIntInst(llvmint), fLlvmFloatInst(llvmfloat),
            fCompute(f), fLeftNeutral(ln), fRightNeutral(rn),
            fLeftAbsorbing(la), fRightAbsorbing(ra), fPriority(priority)
    {}

	Node compute(const Node& a, const Node& b) { return fCompute(a,b); 	}

    bool isRightNeutral(const Node& a)      { return fRightNeutral(a); 	    }
	bool isLeftNeutral(const Node& a)       { return fLeftNeutral(a); 	    }
	bool isLeftAbsorbing(const Node& a)     { return fLeftAbsorbing(a);     }
    bool isRightAbsorbing(const Node& a)    { return fRightAbsorbing(a);    }
};

extern BinOp* gBinOpTable[];
extern BinOp* gBinOpLateqTable[];

enum {
	kAdd, kSub, kMul, kDiv, kRem,
	kLsh, kRsh,
	kGT, kLT, kGE, kLE, kEQ, kNE,
	kAND, kOR, kXOR
};

bool isBoolOpcode(int o);
bool isLogicalOpcode(int o);

#endif
