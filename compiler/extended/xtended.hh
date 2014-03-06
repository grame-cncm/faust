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

#ifndef __XTENDED__
#define __XTENDED__

#include <vector>
#include "tlib.hh"
#include "sigtype.hh"
#include "sigvisitor.hh"
#include "lateq.hh"
#include "garbageable.hh"

struct ValueInst;

class CodeGen;
class CodeContainer;

class xtended : public virtual Garbageable {

	Symbol*		fSymbol;	///< the symbol the xtended is attached to
    
 public:

 	xtended (const char* name) :
		fSymbol(::symbol(name)) 
    {
		setUserData(fSymbol, (void*)this);
	}
	virtual ~xtended() {}

	Sym				symbol() 	{ return fSymbol; }
	const char * 	name () 	{ return ::name(fSymbol); }

	Tree			box () {
						Tree b = tree(fSymbol);
						assert(getUserData(b) != 0);
						return b;
					}

	// virtual method to be implemented by subclasses
	virtual unsigned int 	arity () = 0;

    virtual ValueInst* 	generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result_type, vector< ::Type > const & types) = 0;

	virtual string 	generateLateq(Lateq* lateq, const vector<string>& args, const vector< ::Type>& types) = 0;
	virtual int 	infereSigOrder(const vector<int>& args) = 0;
	virtual ::Type 	infereSigType(const vector< ::Type>& args) = 0;
	virtual Tree	computeSigOutput(const vector<Tree>& args) = 0;
	virtual bool	needCache() = 0;

    virtual bool    isSpecialInfix()    { return false; }   ///< generaly false, but true for binary op # such that #(x) == _#x
    
    void prepareTypeArgsResult(::Type result, 
                                const list<ValueInst*>& args, 
                                vector< ::Type> const& types,
                                Typed::VarType& result_type, 
                                vector<Typed::VarType>& arg_types, 
                                list<ValueInst*>& casted_args);
    
};

#endif

