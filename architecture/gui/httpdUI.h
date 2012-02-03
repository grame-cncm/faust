/*
   Copyright (C) 2012 Grame - Lyon
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted.
*/

#ifndef __httpdUI__
#define __httpdUI__

//#include <vector>

#include "HTTPDControler.h"
#include "GUI.h"

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
//	vector<const char*>		fAlias;
	
	const char* tr(const char* label) const;
	
	// add all accumulated alias
	void addalias(float* zone, float init, float min, float max) {}
//	void addalias(float* zone, float init, float min, float max) 
//	{
//		for (unsigned int i=0; i<fAlias.size(); i++) {
//			fCtrl->addfullpathnode(fAlias[i], zone, 0, 1, init, min, max);
//		}
//		fAlias.clear();
//	}
	
 public:
		
	httpdUI(char* /*applicationname*/, int argc, char *argv[]) : GUI() 
    { 
		fCtrl = new httpdfaust::HTTPDControler(argc, argv); 
	}
	
	virtual ~httpdUI() { delete fCtrl; }
	
	// -- active widgets
	virtual void addButton(const char* label, float* zone)																{ addalias(zone, 0, 0, 1); fCtrl->addnode( tr(label), zone, 0, 0, 1); }
	virtual void addToggleButton(const char* label, float* zone)														{ addalias(zone, 0, 0, 1); fCtrl->addnode( tr(label), zone, 0, 0, 1); }
	virtual void addCheckButton(const char* label, float* zone)															{ addalias(zone, 0, 0, 1); fCtrl->addnode( tr(label), zone, 0, 0, 1); }
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float /*step*/) 	{ addalias(zone, init, min, max); fCtrl->addnode( tr(label), zone, init, min, max); }
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float /*step*/) 	{ addalias(zone, init, min, max); fCtrl->addnode( tr(label), zone, init, min, max); }
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float /*step*/) 			{ addalias(zone, init, min, max); fCtrl->addnode( tr(label), zone, init, min, max); }
	
	// -- passive widgets	
	virtual void addNumDisplay(const char* /*label*/, float* /*zone*/, int /*precision*/) {}
	virtual void addTextDisplay(const char* /*label*/, float* /*zone*/, const char* /*names*/[], float /*min*/, float /*max*/) {}
	virtual void addHorizontalBargraph(const char* /*label*/, float* /*zone*/, float /*min*/, float /*max*/) {}
	virtual void addVerticalBargraph(const char* /*label*/, float* /*zone*/, float /*min*/, float /*max*/) {}
		
	virtual void openFrameBox(const char* label)		{ fCtrl->opengroup( tr(label)); }
	virtual void openTabBox(const char* label) 			{ fCtrl->opengroup( tr(label)); }
	virtual void openHorizontalBox(const char* label) 	{ fCtrl->opengroup( tr(label)); }
	virtual void openVerticalBox(const char* label) 	{ fCtrl->opengroup( tr(label)); }
	virtual void closeBox() 							{ fCtrl->closegroup(); }
	
	virtual void declare(float* , const char* key , const char* alias) 
	{ 
//		if (strcasecmp(key,"HTTP")==0) fAlias.push_back(alias);
	}


	virtual void show() {}

	void run()											{ fCtrl->run(); }
//	const char* getRootName()							{ return fCtrl->getRootName(); }
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
