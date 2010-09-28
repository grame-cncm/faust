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



#ifndef _COGEN_H
#define _COGEN_H

/**********************************************************************
			- code_gen.h : generic code generator (projet FAUST) -


		Historique :
		-----------

***********************************************************************/
using namespace std;

#include <string>
#include <list>
#include <set>
#include <map>
#include "sigtype.hh"
#include "smartpointer.hh"
#include "tlib.hh"
#include "uitree.hh"
#include "property.hh"

#define kMaxCategory 32

#include "loop.hh"
#include "graphSorting.hh"

#include <llvm/Value.h>
#include <llvm/Constants.h>
#include <llvm/Support/IRBuilder.h>

typedef llvm::Value* LlvmValue;

class CodeLlvmScalarCompiler;

class CodeGen 
{

protected:
    // we make it global because several classes may need
    // power def but we want the code to be generated only once
    static bool     fNeedPowerDef;              ///< true when faustpower definition is needed

 //protected:
 public:
    
	string			fKlassName;
	string			fSuperKlassName;
	int				fNumInputs;
	int				fNumOutputs;
    int             fNumActives;                ///< number of active controls in the UI (sliders, buttons, etc.)
    int             fNumPassives;               ///< number of passive widgets in the UI (bargraphs, etc.)

    set<string>			fIncludeFileSet;
	set<string>			fLibrarySet;
    
    list<string>		fUIMacro;
    list<string>		fUICode;

	list<CodeGen* >		fSubClassList;

    Loop*               fTopLoop;               ///< active loops currently open
    property<Loop*>     fLoopProperty;          ///< loops used to compute some signals

    bool                fVec;

 public:

	CodeGen (const string& name, const string& super, int numInputs, int numOutputs, bool __vec = false, Loop* loop = new Loop(0, "count"))
	  : 	fKlassName(name), fSuperKlassName(super), fNumInputs(numInputs), fNumOutputs(numOutputs),
            fNumActives(0), fNumPassives(0),
            fTopLoop(loop), fVec(__vec)
	{}
 
	virtual ~CodeGen() 						{}

    virtual void    openLoop(const string& size)
    {}
    virtual void    openLoop(Tree recsymbol, const string& size)
    {}
    virtual void    closeLoop(Tree sig = 0)
    {}

    void    setLoopProperty(Tree sig, Loop* l) {}                   ///< Store the loop used to compute a signal
    bool    getLoopProperty(Tree sig, Loop*& l) { return false;}    ///< Returns the loop used to compute a signal

    Loop*   topLoop()   { return fTopLoop; }
    
    virtual llvm::IRBuilder<>* getInitCodeBuilder() { return NULL; }
    virtual llvm::IRBuilder<>* getBlockCodeBuilder() { return NULL; }
    virtual llvm::IRBuilder<>* getExecCodeBuilder() { return NULL; }
    virtual llvm::IRBuilder<>* getPostCodeBuilder() { return NULL; }
    
    virtual LlvmValue genInt32(int number) { return NULL; }
    virtual LlvmValue genInt64(int number) { return NULL; }
    virtual LlvmValue genFloat(const string& number) { return NULL; }
    virtual LlvmValue genFloat(float number) { return NULL; }
    
    // External stuff
    virtual LlvmValue generateFun(llvm::IRBuilder<>* builder, const string& function, const vector<LlvmValue>& args, const vector<Type>& types) { return NULL;}
    virtual LlvmValue generateFConst(llvm::IRBuilder<>* builder, const string& file, const string& exp) { return NULL; }
   
    // Inputs/outputs 
    virtual void generateLoadInputs() {}
    virtual void generateLoadOutputs() {}
    
    virtual LlvmValue generateLoadInput(int input) { return NULL; }
    virtual void generateStoreOutput(int output, LlvmValue val) {}
   
    // DSP loop
    //virtual void generateCompute() {}
    //virtual void generateComputeLoopBegin() {}
    //virtual void generateComputeLoopEnd() {}
    
    virtual LlvmValue generateBinOp(llvm::IRBuilder<>* builder, int opcode, LlvmValue arg1, LlvmValue arg2) { return NULL; }
    virtual LlvmValue generateIntCast(llvm::IRBuilder<>* builder, LlvmValue arg) { return NULL; }
    virtual LlvmValue generateFloatCast(llvm::IRBuilder<>* builder, LlvmValue arg) { return NULL; }
    
    virtual LlvmValue generateSelect2(llvm::IRBuilder<>* builder, CodeLlvmScalarCompiler* compiler, Tree cond_tree, Tree then_tree, Tree else_tree, int comp_val) { return NULL; }
    
    // UI
    virtual LlvmValue generateLoadVar(llvm::IRBuilder<>* builder, const string& varname) { return NULL; }
    virtual void generateStoreVar(llvm::IRBuilder<>* builder, const string& varname, LlvmValue value) {} 
    virtual LlvmValue generateLoadArrayVar(llvm::IRBuilder<>* builder, const string& varname, LlvmValue index) { return NULL; }
    virtual void generateStoreArrayVar(llvm::IRBuilder<>* builder, const string& varname, LlvmValue index, LlvmValue value) {}
    
    
    virtual LlvmValue generateDelayLine(const string& ctype, const string& vname, int mxd, LlvmValue exp)  { return NULL; }
    
    void buildTasksList() {}
    
	void addIncludeFile (const string& str) { fIncludeFileSet.insert(str); }

	void addLibrary (const string& str) 	{ fLibrarySet.insert(str); }

    void rememberNeedPowerDef ()            { fNeedPowerDef = true; }

	void collectIncludeFile(set<string>& S) {}

	void collectLibrary(set<string>& S) {}

    /*
	void addSubKlass (Klass* son)			{ fSubClassList.push_back(son); }
	void addDeclCode (const string& str) 	{ fDeclCode.push_back(str); }
	void addInitCode (const string& str)	{ fInitCode.push_back(str); }
	void addStaticInitCode (const string& str)	{ fStaticInitCode.push_back(str); }
	void addStaticFields (const string& str)	{ fStaticFields.push_back(str); }
    */

	void addUICode (const string& str)		{ fUICode.push_back(str); }
    void addUIMacro (const string& str)     { fUIMacro.push_back(str); }

    void incUIActiveCount ()                { fNumActives++; }
    void incUIPassiveCount ()               { fNumPassives++; }

    // Declarations
    virtual void addConstant (const string& str)
    {}
    string addStringConstant (const string& str)
    {
        return "";
    }
    
    virtual void generateSimpleTypeDecl(const string& name, const string& type)
    {}
    virtual void generateSimpleTypeInit(const string& name, const string& type, float exp)
    {}
    virtual void generateSimpleTypeInit(const string& name, const string& type,  LlvmValue exp)
    {}
    virtual void generateSimpleTypeInit(const string& name, const string& type, int exp)
    {}
    virtual void generateArrayTypeDecl(const string& name, const string& type, int size)
    {}
    virtual void generateArrayTypeInit(const string& name, const string& type, float exp, int size)
    {}
    virtual void generateArrayTypeInit(const string& name, const string& type, int exp, int size)
    {}
    virtual void generateArrayTypeInit(const string& name, const string& type, LlvmValue exp, int size)
    {}

    // UI construction
    virtual void openBox(int orient, const string& name) {}
    virtual void closeBox() {}
    
    virtual void addMetaDeclare(const string& zone, const string& key, const string& value) {}
    
    virtual void addButton(const string& label, const string& zone) {}
    virtual void addCheckButton(const string& label, const string& zone) {}
    virtual void addVerticalSlider(const string& label, const string& zone, float init, float min, float max, float step) {}
    virtual void addHorizontalSlider(const string& label, const string& zone, float init, float min, float max, float step) {}
    virtual void addNumEntry(const string& label, const string& zone, float init, float min, float max, float step) {}
    virtual void addVerticalBargraph(const string& label, const string& zone, float min, float max) {}
    virtual void addHorizontalBargraph(const string& label, const string& zone, float min, float max) {}
		
	int	inputs() 	{ return fNumInputs; }
	int outputs()	{ return fNumOutputs; }
    
    virtual void generateBeginModule() {}
    virtual void generateEndModule() {}
    virtual void print() {}
};

class SigIntGenCodeGen : public CodeGen {
    
 public:

	SigIntGenCodeGen (const string& name) : CodeGen(name, "", 0, 1, false)	{}

};

class SigFloatGenCodeGen : public CodeGen {
    
 public:

	SigFloatGenCodeGen (const string& name) : CodeGen(name, "", 0, 1, false)	{}

};


#endif
