/*
   Copyright (C) 2011 Grame - Lyon
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted.
*/

#include "OSCControler.h"
#include "UI.h"

/******************************************************************************
*******************************************************************************

					OSC (Open Sound Control) USER INTERFACE

*******************************************************************************
*******************************************************************************/
/*

Note about the OSC addresses and the Faust UI names:
----------------------------------------------------
There are potential conflicts between the Faust UI objects naming scheme and 
the OSC address space. An OSC symbolic names is an ASCII string consisting of
printable characters other than the following:
	space 
#	number sign
*	asterisk
,	comma
/	forward
?	question mark
[	open bracket
]	close bracket
{	open curly brace
}	close curly brace

a simple solution to address the problem consists in replacing 
space or tabulation with '_' (underscore)
all the other osc excluded characters with '-' (hyphen)

This solution is implemented in the proposed OSC UI;
*/

//class oscfaust::OSCIO;
class OSCUI : public UI 
{
	oscfaust::OSCControler*	fCtrl;
	const char* tr(const char* label) const;	
	
 public:
		
	OSCUI(char* applicationname, int argc, char *argv[], oscfaust::OSCIO* io=0) : UI() 
    { 
		fCtrl = new oscfaust::OSCControler(argc, argv, io); 
//		fCtrl->opengroup(applicationname);
	}
	
	virtual ~OSCUI() { delete fCtrl; }
	
	// -- active widgets
	virtual void addButton(const char* label, float* zone) 															{ fCtrl->addnode( tr(label), zone, 0, 0, 1); }
	virtual void addToggleButton(const char* label, float* zone) 													{ fCtrl->addnode( tr(label), zone, 0, 0, 1); }
	virtual void addCheckButton(const char* label, float* zone) 													{ fCtrl->addnode( tr(label), zone, 0, 0, 1); }
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float /*step*/) 	{ fCtrl->addnode( tr(label), zone, init, min, max); }
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float /*step*/) 	{ fCtrl->addnode( tr(label), zone, init, min, max); }
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float /*step*/) 			{ fCtrl->addnode( tr(label), zone, init, min, max); }
	
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

	virtual void show() {}

	void run()											{ fCtrl->run(); }
	const char* getRootName()							{ return fCtrl->getRootName(); }
};

					
const char* OSCUI::tr(const char* label) const
{
	static char buffer[1024];
	char * ptr = buffer; int n=1;
	while (*label && (n++ < 1024)) {
		switch (*label) {
			case ' ': case '	':
				*ptr++ = '_';
				break;
			case '#': case '*': case ',': case '/': case '?':
			case '[': case ']': case '{': case '}':
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
