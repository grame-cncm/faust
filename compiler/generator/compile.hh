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

#ifndef _COMPILE_
#define _COMPILE_

#include "signals.hh"
#include "klass.hh"
#include "Text.hh"
#include "uitree.hh"
#include <string>
#include <list>
#include <stack>
#include <map>

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

class Compiler
{
protected:
    
	Klass*			fClass;
	bool			fNeedToDeleteClass;
	Tree			fUIRoot;
	Description*	fDescription;
    JSONUI          fJSON;

public:
    
	Compiler (const string& name, const string& super, int numInputs, int numOutputs, bool vec);
	Compiler (Klass* k);

	virtual ~Compiler();

	virtual void		compileMultiSignal  (Tree lsig) = 0;
	virtual void		compileSingleSignal (Tree lsig) = 0;

	Klass*				getClass() { return (Klass*)fClass; }

	void				setDescription(Description* descr)	{ fDescription = descr; }
	Description*		getDescription()					{ return fDescription; }

protected:
    
  virtual Tree 		prepare(Tree L0) = 0;
  virtual Tree 		prepare2(Tree L0) = 0;

    // gestion des includes et librairies
	void 		addIncludeFile(const string& str) 	{ fClass->addIncludeFile(str); 	}
	void 		addLibrary(const string& str) 		{ fClass->addLibrary(str); 		}

    // gestion de la description arborescente de l'IU
    void 		addUIWidget(Tree path, Tree widget);
    void 		generateWidgetCode(Tree fulllabel, Tree varname, Tree sig);
    void        generateMetaData();
    void 		generateUserInterfaceTree(Tree t, bool root = false);
    void 		generateUserInterfaceElements(Tree elements);
    Tree 		prepareUserInterfaceTree(Tree t);
	void        generateMacroInterfaceTree(const string& pathname, Tree t);
    void        generateMacroInterfaceElements(const string& pathname, Tree elements);
    void        generateWidgetMacro(const string& pathname, Tree fulllabel, Tree varname, Tree sig);

};

#define generateEquivRecGroup generateRecGroup

void compileSignals(const string& name, const string& super, int numInputs, int numOutputs, Tree lsig);

#endif
