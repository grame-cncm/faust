/*
   Copyright (C) 2012 Grame - Lyon
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted.
*/

#ifndef __httpdUI__
#define __httpdUI__

#include "faust/gui/HTTPDControler.h"
#include "faust/gui/GUI.h"

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

using namespace std;

class httpdUI : public GUI 
{
	httpdfaust::HTTPDControler*	fCtrl;	
	const char* tr(const char* label) const;

 public:
		
	httpdUI(const char* applicationname, int argc, char *argv[]) : GUI() 
    { 
		fCtrl = new httpdfaust::HTTPDControler(argc, argv, applicationname); 
	}
	
	virtual ~httpdUI() { delete fCtrl; }
		
    // -- widget's layouts
	virtual void openTabBox(const char* label) 			{ fCtrl->opengroup( "tabbox", tr(label)); }
	virtual void openHorizontalBox(const char* label) 	{ fCtrl->opengroup( "horizontalbox", tr(label)); }
	virtual void openVerticalBox(const char* label) 	{ fCtrl->opengroup( "verticalbox", tr(label)); }
	virtual void closeBox() 							{ fCtrl->closegroup(); }
	
	// -- active widgets
	virtual void addButton(const char* label, FAUSTFLOAT* zone)			{ fCtrl->addnode( "button", tr(label), zone); }
	virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)	{ fCtrl->addnode( "checkbutton", tr(label), zone); }
	virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)		
									{ fCtrl->addnode( "verticalslider", tr(label), zone, init, min, max, step); }
	virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
									{ fCtrl->addnode( "horizontalslider", tr(label), zone, init, min, max, step); }
	virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
									{ fCtrl->addnode( "numentry", tr(label), zone, init, min, max, step); }
	
	// -- passive widgets	
	virtual void addHorizontalBargraph(const char* /*label*/, FAUSTFLOAT* /*zone*/, FAUSTFLOAT /*min*/, FAUSTFLOAT /*max*/) {}
	virtual void addVerticalBargraph(const char* /*label*/, FAUSTFLOAT* /*zone*/, FAUSTFLOAT /*min*/, FAUSTFLOAT /*max*/) {}
	
	void run()											{ fCtrl->run(); }
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
