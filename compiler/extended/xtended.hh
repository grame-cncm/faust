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

#include "klass.hh"
#include "tlib.hh"
#include "sigtype.hh"
#include "sigvisitor.hh"
#include "lateq.hh"
#include "garbageable.hh"
#include "instructions.hh"

class CodeGen;
class CodeContainer;

class xtended : public virtual Garbageable {

    private:

        Symbol*	fSymbol;	///< the symbol the xtended is attached to

    public:

        xtended(const char* name):fSymbol(::symbol(name))
        {
            setUserData(fSymbol, (void*)this);
        }
        virtual ~xtended() {}

        Sym	symbol() { return fSymbol; }
        const char* name() { return ::name(fSymbol); }

        Tree box()
        {
            Tree b = tree(fSymbol);
            faustassert(getUserData(b) != 0);
            return b;
        }

        // virtual method to be implemented by subclasses
        virtual unsigned int arity() = 0;

        virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result_type, vector< ::Type> const& types) = 0;

        // SL : 28/09/17
        // Old CPP backend
        virtual string old_generateCode(Klass* klass, const vector<string>& args, const vector<Type>& types) = 0;

        virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector< ::Type>& types) = 0;
        virtual int infereSigOrder(const vector<int>& args) = 0;
        virtual ::Type infereSigType(const vector< ::Type>& args) = 0;
        virtual Tree computeSigOutput(const vector<Tree>& args) = 0;
        virtual bool needCache() = 0;

        virtual bool isSpecialInfix() { return false; }   ///< generaly false, but true for binary op # such that #(x) == _#x

        void prepareTypeArgsResult(::Type result, 
                                    const list<ValueInst*>& args, 
                                    vector< ::Type> const& types,
                                    Typed::VarType& result_type, 
                                    vector<Typed::VarType>& arg_types, 
                                    list<ValueInst*>& casted_args);
    
};

// True if two floating point numbers are close enough to be considered identical. It is used to recognize PI/n and 0 in some symbolic simplifications
inline bool comparable(double x, double y) { return fabs(x-y) < 0.00001; }

inline ValueInst* promote2real(int type, ValueInst* val) { return (type == kReal) ? val : InstBuilder::genCastNumFloatInst(val); }
inline ValueInst* promote2int(int type, ValueInst* val) { return (type == kInt) ? val : InstBuilder::genCastNumIntInst(val); }

inline ValueInst* cast2real(int type, ValueInst* val) { return (type == kReal) ? InstBuilder::genCastNumFloatInst(val) : val; }
inline ValueInst* cast2int(int type, ValueInst* val) { return (type == kInt) ? InstBuilder::genCastNumIntInst(val) : val; }

#endif

