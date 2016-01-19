/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

/*
   Copyright (C) 2012 Grame - Lyon
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted.
*/

#ifndef __httpdUI__
#define __httpdUI__

#include "faust/gui/HTTPDControler.h"
#include "faust/gui/UI.h"

/******************************************************************************
*******************************************************************************

					HTTPD USER INTERFACE

*******************************************************************************
*******************************************************************************/
/*

Note about URLs and the Faust UI names:
----------------------------------------------------
Characters in a url could be:
1. Reserved: ; / ? : @ & = + $ ,
   These characters delimit URL parts.
2. Unreserved: alphanum - _ . ! ~ * ' ( )
   These characters have no special meaning and can be used as is.
3. Excluded: control characters, space, < > # % ", { } | \ ^ [ ] `

To solve potential conflicts between the Faust UI objects naming scheme and
the URL allowed characters, the reserved and excluded characters are replaced
with '-' (hyphen).
Space or tabulation are replaced with '_' (underscore)
*/

//using namespace std;

class httpdUI : public UI 
{
	httpdfaust::HTTPDControler*	fCtrl;	
	const char* tr(const char* label) const;

 public:
		
	httpdUI(const char* applicationname, int inputs, int outputs, int argc, char *argv[], bool init = true) 
    { 
		fCtrl = new httpdfaust::HTTPDControler(argc, argv, applicationname, init); 
        fCtrl->setInputs(inputs);
        fCtrl->setOutputs(outputs);
	}
	
	virtual ~httpdUI() { delete fCtrl; }
		
    // -- widget's layouts
	virtual void openTabBox(const char* label) 			{ fCtrl->opengroup( "tgroup", tr(label)); }
	virtual void openHorizontalBox(const char* label) 	{ fCtrl->opengroup( "hgroup", tr(label)); }
	virtual void openVerticalBox(const char* label) 	{ fCtrl->opengroup( "vgroup", tr(label)); }
	virtual void closeBox() 							{ fCtrl->closegroup(); }
	
	// -- active widgets
	virtual void addButton(const char* label, FAUSTFLOAT* zone)			{ fCtrl->addnode( "button", tr(label), zone); }
	virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)	{ fCtrl->addnode( "checkbox", tr(label), zone); }
	virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
									{ fCtrl->addnode( "vslider", tr(label), zone, init, min, max, step); }
	virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
									{ fCtrl->addnode( "hslider", tr(label), zone, init, min, max, step); }
	virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
									{ fCtrl->addnode( "nentry", tr(label), zone, init, min, max, step); }
	
	// -- passive widgets	
	virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
									{ fCtrl->addnode( "hbargraph", tr(label), zone, min, max); }
	virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
									{ fCtrl->addnode( "vbargraph", tr(label), zone, min, max); }
	
    virtual void declare (FAUSTFLOAT*, const char* key, const char* val) { fCtrl->declare(key, val); }

	void run()						{ fCtrl->run(); }
	int getTCPPort()                { return fCtrl->getTCPPort(); }
    
    std::string getJSONInterface(){ return fCtrl->getJSONInterface(); }

};
					
const char* httpdUI::tr(const char* label) const
{
	static char buffer[1024];
	char * ptr = buffer; int n=1;
	while (*label && (n++ < 1024)) {
		switch (*label) {
			case ' ': case '	':
				*ptr++ = '_';
				break;
			case ';': case '/': case '?': case ':': case '@': 
			case '&': case '=': case '+': case '$': case ',':
			case '<': case '>': case '#': case '%': case '"': 
			case '{': case '}': case '|': case '\\': case '^': 
			case '[': case ']': case '`':
				*ptr++ = '_';
				break;
			default: 
				*ptr++ = *label;
		}
		label++;
	}
	*ptr = 0;
	return buffer;
}

#endif
