/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include "garbageable.hh"
#include "instructions.hh"
#include "klass.hh"
#include "lateq.hh"
#include "sigtype.hh"
#include "sigvisitor.hh"
#include "tlib.hh"

class CodeContainer;

/**
 * @brief xtended: abstract class that can be derived to add new primitives to the language
 *
 */
class xtended : public virtual Garbageable {
   private:
    Symbol* fSymbol;  ///< the symbol the xtended is attached to

   public:
    /**
     * @brief xtended(const char* name): Construct a new xtended object
     *
     * @param name
     */
    xtended(const char* name) : fSymbol(::symbol(name)) { setUserData(fSymbol, (void*)this); }

    /**
     * @brief Destroy the xtended object
     *
     */
    virtual ~xtended() {}

    /**
     * @brief symbol(): the symbol attached to this primitive
     *
     * @return Sym
     */
    Sym symbol() { return fSymbol; }

    /**
     * @brief name(): the string attached to the symbol of this primitive
     *
     * @return const char*
     */
    const char* name() { return ::name(fSymbol); }

    /**
     * @brief create a box primitive from this signal primitive
     *
     * @return Tree
     */
    Tree box()
    {
        Tree b = tree(fSymbol);
        faustassert(getUserData(b) != 0);
        return b;
    }

    //------------------------ virtual methods to implement ------------------------

    /**
     * @brief arity(): number of expected arguments for this function
     *
     * @return unsigned int
     */
    virtual unsigned int arity() = 0;

    /**
     * @brief generateCode(): generate code new backends
     *
     * @param container
     * @param args
     * @param result_type
     * @param types
     * @return ValueInst*
     */
    virtual ValueInst* generateCode(CodeContainer* container, const list<ValueInst*>& args, ::Type result_type,
                                    vector<::Type> const& types) = 0;

    /**
     * @brief old_generateCode(): generate code for the old cpp backend
     *
     * @param klass where to add statements
     * @param args
     * @param types
     * @return string the resulting code
     */
    virtual string old_generateCode(Klass* klass, const vector<string>& args, const vector<Type>& types) = 0;

    /**
     * @brief generateLateq(): generate latex code
     *
     * @param lateq
     * @param args
     * @param types
     * @return string
     */
    virtual string generateLateq(Lateq* lateq, const vector<string>& args, const vector<::Type>& types) = 0;

    /**
     * @brief infereSigOrder():
     *
     * @param args
     * @return int
     */
    virtual int infereSigOrder(const vector<int>& args) = 0;

    /**
     * @brief infereSigType(): type of the resulting signal according to the type of the arguments
     *
     * @param args
     * @return ::Type
     */
    virtual ::Type infereSigType(const vector<::Type>& args) = 0;

    /**
     * @brief computeSigOutput(): create resulting signal expression (used during propagation)
     *
     * @param args
     * @return Tree
     */
    virtual Tree computeSigOutput(const vector<Tree>& args) = 0;

    /**
     * @brief needCache(): do we potentially need to cache this expression ?
     *
     * @return true
     * @return false
     */
    virtual bool needCache() = 0;

    /**
     * @brief isSpecialInfix(): generally false, but true for binary op # such that #(x) == _#x
     *
     * @return true
     * @return false
     */
    virtual bool isSpecialInfix() { return false; }

    // Some kind of pattern matching for the extended primitives
    virtual bool is(Tree t) { return false; }
    virtual bool is(Tree t, Tree& x) { return false; }
    virtual bool is(Tree t, Tree& x, Tree& y) { return false; }

    /**
     * @brief prepareTypeArgsResult():
     *
     * @param result
     * @param args
     * @param types
     * @param result_type
     * @param arg_types
     * @param casted_args
     */
    void prepareTypeArgsResult(::Type result, const list<ValueInst*>& args, vector<::Type> const& types,
                               Typed::VarType& result_type, vector<Typed::VarType>& arg_types,
                               list<ValueInst*>& casted_args);
};

// True if two floating point numbers are close enough to be considered identical.
// It is used to recognize PI/n and 0 in some symbolic simplifications.
inline bool comparable(double x, double y)
{
    return fabs(x - y) < 0.00001;
}

inline ValueInst* promote2real(int type, ValueInst* val)
{
    return (type == kReal) ? val : InstBuilder::genCastFloatInst(val);
}
inline ValueInst* promote2int(int type, ValueInst* val)
{
    return (type == kInt) ? val : InstBuilder::genCastInt32Inst(val);
}

inline ValueInst* cast2real(int type, ValueInst* val)
{
    return (type == kReal) ? InstBuilder::genCastFloatInst(val) : val;
}
inline ValueInst* cast2int(int type, ValueInst* val)
{
    return (type == kInt) ? InstBuilder::genCastInt32Inst(val) : val;
}

#endif
