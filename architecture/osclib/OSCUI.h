/*
   Copyright (C) 2011 Grame - Lyon
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted.
*/

#include "OSCControler.h"

/******************************************************************************
*******************************************************************************

					OSC (Open Sound Control) USER INTERFACE

*******************************************************************************
*******************************************************************************/
class OSCUI : public UI 
{
	oscfaust::OSCControler*	fCtrl;
 public:
		
	OSCUI(char* applicationname, int argc, char *argv[]) : UI() 
    { 
		fCtrl = new oscfaust::OSCControler(argc, argv); 
		fCtrl->opengroup(applicationname);
	}
	
	virtual ~OSCUI() { delete fCtrl; }
	
	// -- active widgets
	virtual void addButton(const char* label, float* zone) 															{ fCtrl->addnode(label, zone, 0, 0, 1); }
	virtual void addToggleButton(const char* label, float* zone) 													{ fCtrl->addnode(label, zone, 0, 0, 1); }
	virtual void addCheckButton(const char* label, float* zone) 													{ fCtrl->addnode(label, zone, 0, 0, 1); }
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) 	{ fCtrl->addnode(label, zone, init, min, max); }
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) 	{ fCtrl->addnode(label, zone, init, min, max); }
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) 			{ fCtrl->addnode(label, zone, init, min, max); }
	
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) {}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) {}
		
	virtual void openFrameBox(const char* label)		{ fCtrl->opengroup(label); }
	virtual void openTabBox(const char* label) 			{ fCtrl->opengroup(label); }
	virtual void openHorizontalBox(const char* label) 	{ fCtrl->opengroup(label); }
	virtual void openVerticalBox(const char* label) 	{ fCtrl->opengroup(label); }
	virtual void closeBox() 							{ fCtrl->closegroup(); }

	virtual void show() {}

	void run()											{ fCtrl->run(); }
};

					

