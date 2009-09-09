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



#include "timing.hh"
#include "compile.hh"
#include "floats.hh"
#include "sigtype.hh"

#include <stdio.h>
//#include <iostream>

#include "sigprint.hh"
#include "ppsig.hh"

#include "sigtyperules.hh"
#include "simplify.hh"
#include "privatise.hh"
//#include "factorize.hh"

//#include "grouper.hh"
//#include "sigvisitor.hh"




/*****************************************************************************
******************************************************************************

							    	API

******************************************************************************
*****************************************************************************/

extern int 		gDetailsSwitch;
extern string 	gMasterName;




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
		  fUIRoot(uiFolder(cons(tree(0), tree(subst("$0", gMasterName))))),
		  fDescription(0)
{}

Compiler::Compiler(Klass* k)
		: fClass(k),
		  fUIRoot(uiFolder(cons(tree(0), tree(subst("$0", gMasterName))))),
		  fDescription(0)
{}


Compiler::~Compiler()
{}



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
 * is completely enclosed in one folder
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



/**
 * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
 * (but not those in the middle of the string)
 */
static string rmWhiteSpaces(const string& s)
{
    size_t i = s.find_first_not_of(" \t");
    size_t j = s.find_last_not_of(" \t");

    if ( (i != string::npos) & (j != string::npos) ) {
        return s.substr(i, 1+j-i);
    } else {
        return "";
    }
}

/**
 * Extracts metdata from a label : 'vol [unit: dB]' -> 'vol' + metadata
 */
static void extractMetadata(const string& fulllabel, string& label, map<string, set<string> >& metadata)
{
    enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
    int state = kLabel; int deep = 0;
    string key, value;

    for (unsigned int i=0; i < fulllabel.size(); i++) {
        char c = fulllabel[i];
        switch (state) {
            case kLabel :
                assert (deep == 0);
                switch (c) {
                    case '\\' : state = kEscape1; break;
                    case '[' : state = kKey; deep++; break;
                    default : label += c;
                }
                break;

            case kEscape1 :
                label += c;
                state = kLabel;
                break;

            case kEscape2 :
                key += c;
                state = kKey;
                break;

            case kEscape3 :
                value += c;
                state = kValue;
                break;

            case kKey :
                assert (deep > 0);
                switch (c) {
                    case '\\' :  state = kEscape2;
                                break;

                    case '[' :  deep++;
                                key += c;
                                break;

                    case ':' :  if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                    case ']' :  deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)].insert("");
                                    state = kLabel;
                                    key="";
                                    value="";
                                } else {
                                    key += c;
                                }
                                break;
                    default :   key += c;
                }
                break;

            case kValue :
                assert (deep > 0);
                switch (c) {
                    case '\\' : state = kEscape3;
                                break;

                    case '[' :  deep++;
                                value += c;
                                break;

                    case ']' :  deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)].insert(rmWhiteSpaces(value));
                                    state = kLabel;
                                    key="";
                                    value="";
                                } else {
                                    value += c;
                                }
                                break;
                    default :   value += c;
                }
                break;

            default :
                cerr << "ERROR unrecognized state " << state << endl;
        }
    }
    label = rmWhiteSpaces(label);
}


//================================= BUILD USER INTERFACE METHOD =================================

/**
 * Generate buildUserInterface C++ lines of code corresponding 
 * to user interface element t
 */
void Compiler::generateUserInterfaceTree(Tree t)
{
	Tree 	label, elements, varname, sig;

	if (isUiFolder(t, label, elements)) {
		const int		orient = tree2int(left(label));
		const char * 	str = tree2str(right(label));
		const char * 	model;

		switch (orient) {
			case 0 : model = "interface->openVerticalBox(\"$0\");"; break;
			case 1 : model = "interface->openHorizontalBox(\"$0\");"; break;
			case 2 : model = "interface->openTabBox(\"$0\");"; break;
			default :
					fprintf(stderr, "error in user interface generation 1\n");
				exit(1);
		}
		fClass->addUICode(subst(model, str));
		generateUserInterfaceElements(elements);
		fClass->addUICode("interface->closeBox();");

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

/**
 * Generate buildUserInterface C++ lines of code corresponding 
 * to user interface widget t
 */
void Compiler::generateWidgetCode(Tree fulllabel, Tree varname, Tree sig)
{
	Tree path, c, x, y, z;
    string label;
    map<string, set<string> >   metadata;

    extractMetadata(tree2str(fulllabel), label, metadata);

    // add metadata if any
    for (map<string, set<string> >::iterator i = metadata.begin(); i != metadata.end(); i++) {
        const string& key = i->first;
        const set<string>& values = i->second;
        for (set<string>::iterator j = values.begin(); j != values.end(); j++) {
            fClass->addUICode(subst("interface->declare(&$0, \"$1\", \"$2\");", tree2str(varname), wdel(key) ,wdel(*j)));
        }
    }

	if ( isSigButton(sig, path) ) 					{
        fClass->incUIActiveCount();
		fClass->addUICode(subst("interface->addButton(\"$0\", &$1);", label, tree2str(varname)));

	} else if ( isSigCheckbox(sig, path) ) 			{
        fClass->incUIActiveCount();
		fClass->addUICode(subst("interface->addCheckButton(\"$0\", &$1);", label, tree2str(varname)));

	} else if ( isSigVSlider(sig, path,c,x,y,z) )	{
        fClass->incUIActiveCount();
		fClass->addUICode(subst("interface->addVerticalSlider(\"$0\", &$1, $2, $3, $4, $5);",
				label,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if ( isSigHSlider(sig, path,c,x,y,z) )	{
        fClass->incUIActiveCount();
		fClass->addUICode(subst("interface->addHorizontalSlider(\"$0\", &$1, $2, $3, $4, $5);",
				label,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if ( isSigNumEntry(sig, path,c,x,y,z) )	{
        fClass->incUIActiveCount();
		fClass->addUICode(subst("interface->addNumEntry(\"$0\", &$1, $2, $3, $4, $5);",
				label,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if ( isSigVBargraph(sig, path,x,y,z) )	{
        fClass->incUIPassiveCount();
		fClass->addUICode(subst("interface->addVerticalBargraph(\"$0\", &$1, $2, $3);",
				label,
				tree2str(varname),
				T(tree2float(x)),
				T(tree2float(y))));

	} else if ( isSigHBargraph(sig, path,x,y,z) )	{
        fClass->incUIPassiveCount();
		fClass->addUICode(subst("interface->addHorizontalBargraph(\"$0\", &$1, $2, $3);",
                label,
				tree2str(varname),
				T(tree2float(x)),
				T(tree2float(y))));

	} else {
		fprintf(stderr, "Error in generating widget code\n");
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
	Tree 	label, elements, varname, sig;

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
    map<string, set<string> >   metadata;

    extractMetadata(tree2str(fulllabel), label, metadata);

    //string pathlabel = pathname+unquote(label);
	string pathlabel = pathname+label;


	if ( isSigButton(sig, path) ) 					{
		fClass->addUIMacro(subst("FAUST_ADDBUTTON(\"$0\", $1);", pathlabel, tree2str(varname)));

	} else if ( isSigCheckbox(sig, path) ) 			{
		fClass->addUIMacro(subst("FAUST_ADDCHECKBOX(\"$0\", $1);", pathlabel, tree2str(varname)));

	} else if ( isSigVSlider(sig, path,c,x,y,z) )	{
		fClass->addUIMacro(subst("FAUST_ADDVERTICALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
				pathlabel,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if ( isSigHSlider(sig, path,c,x,y,z) )	{
		fClass->addUIMacro(subst("FAUST_ADDHORIZONTALSLIDER(\"$0\", $1, $2, $3, $4, $5);",
				pathlabel,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if ( isSigNumEntry(sig, path,c,x,y,z) )	{
		fClass->addUIMacro(subst("FAUST_ADDNUMENTRY(\"$0\", $1, $2, $3, $4, $5);",
				pathlabel,
				tree2str(varname),
				T(tree2float(c)),
				T(tree2float(x)),
				T(tree2float(y)),
				T(tree2float(z))));

	} else if ( isSigVBargraph(sig, path,x,y,z) )	{
		fClass->addUIMacro(subst("FAUST_ADDVERTICALBARGRAPH(\"$0\", $1, $2, $3);",
				pathlabel,
				tree2str(varname),
				T(tree2float(x)),
				T(tree2float(y))));

	} else if ( isSigHBargraph(sig, path,x,y,z) )	{
		fClass->addUIMacro(subst("FAUST_ADDHORIZONTALBARGRAPH(\"$0\", $1, $2, $3);",
				pathlabel,
				tree2str(varname),
				T(tree2float(x)),
				T(tree2float(y))));

	} else {
		fprintf(stderr, "Error in generating widget code\n");
		exit(1);
	}
}
