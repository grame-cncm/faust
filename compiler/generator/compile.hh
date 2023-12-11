/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _COMPILE_
#define _COMPILE_

#include <list>
#include <map>
#include <stack>
#include <string>
#include "Text.hh"
#include "klass.hh"
#include "signals.hh"
#include "uitree.hh"

#include "description.hh"
#include "faust/gui/JSONUI.h"

////////////////////////////////////////////////////////////////////////
/**
 * compileSignals : listOfSignal -> klass
 *
 * Compile a list of FAUST signals into a C++ class
 */
///////////////////////////////////////////////////////////////////////

#define kMaxHeight 1024

enum class DelayType {
    kNotADelay = 0,
    kZeroDelay,         // delay = 0
    kMonoDelay,         // 1 sample delay where 1 single variable can be used (the delay appears once in the expression)
    kSingleDelay,       // 1 sample delay where the delay appears several times in the expression, so a buffer of size 2 is used
    kCopyDelay,         // longer delay with a cache
    kDenseDelay,        // longer delay with a cache, only when the read density is high enough
    kMaskRingDelay,     // sparse delay without cache, using wrapping index (based on a power-of-two size and a mask)
    kSelectRingDelay    // sparse delay without cache, using wrapping index (based on an if/select)
};
std::string nameDelayType(DelayType dt);

class Compiler : public virtual Garbageable {
   protected:
    Klass*       fClass;
    bool         fNeedToDeleteClass;
    Tree         fUIRoot;
    Description* fDescription;
    JSONUI       fJSON;
    UITree       fUITree;

   public:
    Compiler(const std::string& name, const std::string& super, int numInputs, int numOutputs, bool vec);
    Compiler(Klass* k);

    virtual ~Compiler();

    virtual void compileMultiSignal(Tree lsig)  = 0;
    virtual void compileSingleSignal(Tree lsig) = 0;

    Klass* getClass() { return (Klass*)fClass; }

    void         setDescription(Description* descr) { fDescription = descr; }
    Description* getDescription() { return fDescription; }

   protected:
    virtual Tree prepare(Tree L0)  = 0;
    virtual Tree prepare2(Tree L0) = 0;

    // management of includes and libraries
    void addIncludeFile(const std::string& str) { fClass->addIncludeFile(str); }
    void addLibrary(const std::string& str) { fClass->addLibrary(str); }

    // management of the tree-like description of the UI
    void generateWidgetCode(Tree fulllabel, Tree varname, Tree sig);
    void generateMetaData();
    void generateUserInterfaceTree(Tree t, bool root = false);
    void generateUserInterfaceElements(Tree elements);
    void generateMacroInterfaceTree(const std::string& pathname, Tree t);
    void generateMacroInterfaceElements(const std::string& pathname, Tree elements);
    void generateWidgetMacro(const std::string& pathname, Tree fulllabel, Tree varname, Tree sig);

    // Analyze delay type
    virtual DelayType analyzeDelayType(Tree sig) = 0;
};

#define generateEquivRecGroup generateRecGroup

void compileSignals(const std::string& name, const std::string& super, int numInputs, int numOutputs, Tree lsig);

#endif
