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

/*****************************************************************************
******************************************************************************
							FAUST SIGNAL COMPILER
						Y. Orlarey, (c) Grame 2002
------------------------------------------------------------------------------
Compile a list of FAUST signals into a C++ class .

 History :
 ---------
 	2002-02-08 : First version

******************************************************************************
*****************************************************************************/

#include <stdio.h>

#include "timing.hh"
#include "compile.hh"
#include "floats.hh"
#include "sigtype.hh"
#include "sigprint.hh"
#include "ppsig.hh"
#include "sigtyperules.hh"
#include "simplify.hh"
#include "privatise.hh"

/*****************************************************************************
******************************************************************************

							    	API

******************************************************************************
*****************************************************************************/

/*****************************************************************************
******************************************************************************

						  GENERAL COMPILER METHODS

******************************************************************************
*****************************************************************************/


/*****************************************************************************
							   constructor
*****************************************************************************/

Compiler::Compiler(const string& name, const string& super, int numInputs, int numOutputs, bool vec)
                : fClass(new Klass(name, super, numInputs, numOutputs, vec)),
                fNeedToDeleteClass(true), 
                fUIRoot(uiFolder(cons(tree(0), tree("")))),
                fDescription(0),fJSON(numInputs, numOutputs)
{
    fClass->addIncludeFile("<math.h>");
}

Compiler::Compiler(Klass* k)
                : fClass(k),
                  fNeedToDeleteClass(false), 
                  fUIRoot(uiFolder(cons(tree(0), tree("")))),
                  fDescription(0),fJSON(k->inputs(), k->outputs())
{}

Compiler::~Compiler()
{ 
	if (fNeedToDeleteClass) delete fClass;
    // SL : 28/09/17 : use garbageable class ?
    // delete fDescription;
}

/*****************************************************************************
							user interface elements
*****************************************************************************/

/**
 * Add a widget with a certain path to the user interface tree
 */
void Compiler::addUIWidget(Tree path, Tree widget)
{
	fUIRoot = putSubFolder(fUIRoot, path, widget);
}

/**
 * Remove fake root folder if not needed (that is if the UI
 * is completely enclosed in one folder)
 */
Tree Compiler::prepareUserInterfaceTree(Tree t)
{
	Tree root, elems;
	if (isUiFolder(t, root, elems) && isList(elems) && isNil(tl(elems)) ) {
		Tree folder = right(hd(elems));
		return (isUiFolder(folder)) ? folder : t;
	}
	return t;
}

//================================= some string processing utilities =================================

/**
 * Removes enclosing whitespaces : '  toto  ' -> 'toto'
 */
static string wdel(const string& s)
{
    size_t i = 0;
    size_t j = s.size();
    while (i<j && s[i]==' ') i++;
    while (j>i && s[j-1] == ' ') j--;
    return s.substr(i,j-i);
}

//================================= BUILD USER INTERFACE METHOD =================================

void Compiler::generateMetaData()
{
    // Add global metadata
    for (map<Tree, set<Tree> >::iterator i = gGlobal->gMetaDataSet.begin(); i != gGlobal->gMetaDataSet.end(); i++) {
        if (i->first != tree("author")) {
            stringstream str1, str2;
            str1 << *(i->first);
            str2 << **(i->second.begin());
            string res1 = str1.str();
            string res2 = unquote(str2.str());
            fJSON.declare(res1.c_str(), res2.c_str());
        } else {
            for (set<Tree>::iterator j = i->second.begin(); j != i->second.end(); j++) {
                if (j == i->second.begin()) {
                    stringstream str1, str2;
                    str1 << *(i->first);
                    str2 << **j;
                    string res1 = str1.str();
                    string res2 = unquote(str2.str());
                    fJSON.declare(res1.c_str(), res2.c_str());
                } else {
                    stringstream str2;
                    str2 << **j;
                    string res2 = unquote(str2.str());
                    fJSON.declare("contributor", res2.c_str());
                }
            }
        }
    }
}

/**
 * Generate buildUserInterface C++ lines of code corresponding 
 * to user interface element t
 */
void Compiler::generateUserInterfaceTree(Tree t, bool root)
{
	Tree label, elements, varname, sig;
    
	if (isUiFolder(t, label, elements)) {
		const int orient = tree2int(left(label));
        // Empty labels will be renamed with a 0xABCD (address) kind of name that is ignored and not displayed by UI architectures
        const char* str = tree2str(right(label));  
        const char* model;
          
        // extract metadata from group label str resulting in a simplifiedLabel
		// and metadata declarations for fictive zone at address 0
        string  simplifiedLabel;
        map<string, set<string> > metadata;
        extractMetadata(str, simplifiedLabel, metadata);

        // add metadata if any
        for (map<string, set<string> >::iterator i = metadata.begin(); i != metadata.end(); i++) {
            const string& key = i->first;
            const set<string>& values = i->second;
            for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
                fClass->addUICode(subst("ui_interface->declare($0, \"$1\", \"$2\");", "0", wdel(key) ,wdel(*j)));
                fJSON.declare(NULL, wdel(key).c_str(), wdel(*j).c_str());
            }
        }
        
        // At rool level and if label is empty, use the name kept in "metadata" (either the one coded in 'declare name "XXX";' line, or the filename)
        string group = (root && (simplifiedLabel == ""))
            ? unquote(tree2str(*(gGlobal->gMetaDataSet[tree("name")].begin())))
            : checkNullLabel(t, simplifiedLabel);
        switch (orient) {
           
            case 0 : model = "ui_interface->openVerticalBox(\"$0\");"; fJSON.openVerticalBox(group.c_str()); break;
            case 1 : model = "ui_interface->openHorizontalBox(\"$0\");"; fJSON.openHorizontalBox(group.c_str()); break;
            case 2 : model = "ui_interface->openTabBox(\"$0\");"; fJSON.openTabBox(group.c_str()); break;
                
            default :
                fprintf(stderr, "error in user interface generation 1\n");
                exit(1);
		}
        
        fClass->addUICode(subst(model, group));
        generateUserInterfaceElements(elements);
        fClass->addUICode("ui_interface->closeBox();");
        fJSON.closeBox();

	} else if (isUiWidget(t, label, varname, sig)) {

		generateWidgetCode(label, varname, sig);

	} else {

		fprintf(stderr, "error in user interface generation 2\n");
		exit(1);

	}
}

/**
 * Iterate generateUserInterfaceTree on a list of user interface elements
 */
void Compiler::generateUserInterfaceElements(Tree elements)
{
	while (!isNil(elements)) {
		generateUserInterfaceTree(right(hd(elements)));
		elements = tl(elements);
	}
}

/////////////////////////////////////////////////

/**
 * Generate buildUserInterface C++ lines of code corresponding 
 * to user interface widget t
 */
void Compiler::generateWidgetCode(Tree fulllabel, Tree varname, Tree sig)
{
	Tree path, c, x, y, z;
    string label;
    map<string, set<string> > metadata;
    string filename;
   
    extractMetadata(tree2str(fulllabel), label, metadata);
    
    // Extract "soundfile" metadata to be given as parameter to 'addSoundfile' function
    if (isSigSoundfile(sig, path)) {
        for (map<string, set<string> >::iterator i = metadata.begin(); i != metadata.end(); i++) {
            string key = i->first;
            set<string> values = i->second;
            for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
                if (key == "filename") {
                    filename = wdel(*j);
                }
            }
        }
    } else {
        // Add metadata if any
        for (map<string, set<string> >::iterator i = metadata.begin(); i != metadata.end(); i++) {
            const string& key = i->first;
            const set<string>& values = i->second;
            for (set<string>::const_iterator j = values.begin(); j != values.end(); j++) {
                fClass->addUICode(subst("ui_interface->declare(&$0, \"$1\", \"$2\");", tree2str(varname), wdel(key), wdel(*j)));
                fJSON.declare(NULL, wdel(key).c_str(), wdel(*j).c_str());
            }
        }
    }

	if (isSigButton(sig, path)) {
        fClass->incUIActiveCount();
		fClass->addUICode(subst("ui_interface->addButton(\"$0\", &$1);", checkNullLabel(varname, label), tree2str(varname)));
        fJSON.addButton(checkNullLabel(varname, label).c_str(), NULL);

	} else if (isSigCheckbox(sig, path)) {
        fClass->incUIActiveCount();
		fClass->addUICode(subst("ui_interface->addCheckButton(\"$0\", &$1);", checkNullLabel(varname, label), tree2str(varname)));
        fJSON.addCheckButton(checkNullLabel(varname, label).c_str(), NULL);

	} else if (isSigVSlider(sig, path,c,x,y,z)) {
        fClass->incUIActiveCount();
		fClass->addUICode(subst("ui_interface->addVerticalSlider(\"$0\", &$1, $2, $3, $4, $5);",
                                checkNullLabel(varname, label),
                                tree2str(varname),
                                T(tree2float(c)),
                                T(tree2float(x)),
                                T(tree2float(y)),
                                T(tree2float(z))));
        fJSON.addVerticalSlider(checkNullLabel(varname, label).c_str(), NULL, tree2float(c), tree2float(x), tree2float(y), tree2float(z));

	} else if (isSigHSlider(sig, path,c,x,y,z)) {
        fClass->incUIActiveCount();
		fClass->addUICode(subst("ui_interface->addHorizontalSlider(\"$0\", &$1, $2, $3, $4, $5);",
                                checkNullLabel(varname, label),
                                tree2str(varname),
                                T(tree2float(c)),
                                T(tree2float(x)),
                                T(tree2float(y)),
                                T(tree2float(z))));
        fJSON.addHorizontalSlider(checkNullLabel(varname, label).c_str(), NULL, tree2float(c), tree2float(x), tree2float(y), tree2float(z));

	} else if (isSigNumEntry(sig, path,c,x,y,z)) {
        fClass->incUIActiveCount();
		fClass->addUICode(subst("ui_interface->addNumEntry(\"$0\", &$1, $2, $3, $4, $5);",
                                checkNullLabel(varname, label),
                                tree2str(varname),
                                T(tree2float(c)),
                                T(tree2float(x)),
                                T(tree2float(y)),
                                T(tree2float(z))));
        fJSON.addNumEntry(checkNullLabel(varname, label).c_str(), NULL, tree2float(c), tree2float(x), tree2float(y), tree2float(z));

	} else if (isSigVBargraph(sig, path,x,y,z)) {
        fClass->incUIPassiveCount();
		fClass->addUICode(subst("ui_interface->addVerticalBargraph(\"$0\", &$1, $2, $3);",
                                checkNullLabel(varname, label, true),
                                tree2str(varname),
                                T(tree2float(x)),
                                T(tree2float(y))));
        fJSON.addVerticalBargraph(checkNullLabel(varname, label).c_str(), NULL, tree2float(x), tree2float(y));

	} else if (isSigHBargraph(sig, path,x,y,z)) {
        fClass->incUIPassiveCount();
		fClass->addUICode(subst("ui_interface->addHorizontalBargraph(\"$0\", &$1, $2, $3);",
                                checkNullLabel(varname, label, true),
                                tree2str(varname),
                                T(tree2float(x)),
                                T(tree2float(y))));
        fJSON.addHorizontalBargraph(checkNullLabel(varname, label).c_str(), NULL, tree2float(x), tree2float(y));

	} else if (isSigSoundfile(sig, path)) {
        fClass->incUIActiveCount();
		fClass->addUICode(subst("ui_interface->addSoundfile(\"$0\", \"$1\", &$2);",
                                checkNullLabel(varname, label),
                                filename,
                                tree2str(varname)));
        fJSON.addSoundfile(checkNullLabel(varname, label).c_str(), filename.c_str(), NULL);
	} else {
		fprintf(stderr, "Error in generating widget code 362\n");
		exit(1);
	}
}

//==================================== USER INTERFACE MACROS ==================================

/**
 * Generate user interface macros corresponding 
 * to user interface element t
 */
void Compiler::generateMacroInterfaceTree(const string& pathname, Tree t)
{
	Tree label, elements, varname, sig;

	if (isUiFolder(t, label, elements)) {
		string pathname2 = pathname;
		//string str = unquote(tree2str(right(label)));
		string str = tree2str(right(label));
		if (str.length()>0) pathname2 += str + "/";
		generateMacroInterfaceElements(pathname2, elements);

	} else if (isUiWidget(t, label, varname, sig)) {

		generateWidgetMacro(pathname, label, varname, sig);

	} else {

		fprintf(stderr, "error in user interface macro generation 2\n");
		exit(1);

	}
}

/**
 * Iterate generateMacroInterfaceTree on a list of user interface elements
 */
void Compiler::generateMacroInterfaceElements(const string& pathname, Tree elements)
{
	while (!isNil(elements)) {
		generateMacroInterfaceTree(pathname, right(hd(elements)));
		elements = tl(elements);
	}
}

/**
 * Generate user interface macros corresponding 
 * to a user interface widget
 */
void Compiler::generateWidgetMacro(const string& pathname, Tree fulllabel, Tree varname, Tree sig)
{
	Tree path, c, x, y, z;
    string label;
    map<string, set<string> > metadata;

    extractMetadata(tree2str(fulllabel), label, metadata);

    //string pathlabel = pathname+unquote(label);
	string pathlabel = pathname+label;

	if (isSigButton(sig, path)) {
		fClass->addUIMacro(subst("FAUST_ADDBUTTON(\"$0\", $1);", pathlabel, tree2str(varname)));

	} else if (isSigCheckbox(sig, path)) 			{
		fClass->addUIMacro(subst("FAUST_ADDCHECKBOX(\"$0\", $1);", pathlabel, tree2str(varname)));

	} else if (isSigVSlider(sig, path,c,x,y,z) )	{
		fClass->addUIMacro(subst("FAUST_ADDVERTICALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
				pathlabel,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if (isSigHSlider(sig, path,c,x,y,z)) {
		fClass->addUIMacro(subst("FAUST_ADDHORIZONTALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
				pathlabel,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if (isSigNumEntry(sig, path,c,x,y,z)) {
		fClass->addUIMacro(subst("FAUST_ADDNUMENTRY(\"$0\", $1, $2, $3, $4, $5);",
				pathlabel,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if (isSigVBargraph(sig, path,x,y,z)) {
		fClass->addUIMacro(subst("FAUST_ADDVERTICALBARGRAPH(\"$0\", $1, $2, $3);",
				pathlabel,
				tree2str(varname),
				T(tree2float(x)),
				T(tree2float(y))));

	} else if (isSigHBargraph(sig, path,x,y,z)) {
		fClass->addUIMacro(subst("FAUST_ADDHORIZONTALBARGRAPH(\"$0\", $1, $2, $3);",
				pathlabel,
				tree2str(varname),
				T(tree2float(x)),
				T(tree2float(y))));

	} else if (isSigSoundfile(sig, path)) {
		fClass->addUIMacro(subst("FAUST_ADDSOUNDFILE(\"$0\", $1);",
				pathlabel,
				tree2str(varname)));

	} else {
		fprintf(stderr, "Error in generating widget macro\n");
		exit(1);
	}
}
