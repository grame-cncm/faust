/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <stack>
#include <string>
#include <iostream>
#include <map>

#include "ladspa.h"
#include "faust/gui/GUI.h"
#include "faust/misc.h"
#include "faust/dsp/dsp.h"

#define sym(name) xsym(name)
#define xsym(name) #name

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

//-----------------------------------portCollector--------------------------------------
//
// portCollector is passed to the buildUserInterface method of a dsp object
// in order to build a description of its inputs, outputs and control ports.
// This description is used to fill a LADSPA_Descriptor
//
//--------------------------------------------------------------------------------------

//--------------------------------useful constants--------------------------------------

#define MAXPORT 1024
static const int ICONTROL 	= LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;
static const int OCONTROL 	= LADSPA_PORT_OUTPUT|LADSPA_PORT_CONTROL;
static const int RANGE 		= LADSPA_PORT_INPUT|LADSPA_PORT_CONTROL;

static const char* inames[] = {
					"input00", "input01", "input02", "input03", "input04",
					"input05", "input06", "input07", "input08", "input09",
					"input10", "input11", "input12", "input13", "input14",
					"input15", "input16", "input17", "input18", "input19",
					"input20", "input21", "input22", "input23", "input24",
					"input25", "input26", "input27", "input28", "input29",
					"input30", "input31", "input32", "input33", "input34",
					"input35", "input36", "input37", "input38", "input39"
};

static const char* onames[] = {
					"output00", "output01", "output02", "output03", "output04",
					"output05", "output06", "output07", "output08", "output09",
					"output10", "output11", "output12", "output13", "output14",
					"output15", "output16", "output17", "output18", "output19",
					"output20", "output21", "output22", "output23", "output24",
					"output25", "output26", "output27", "output28", "output29",
					"output30", "output31", "output32", "output33", "output34",
					"output35", "output36", "output37", "output38", "output39"
};

class portCollector : public UI
{
 private:

	//--------------------------------------------------------------------------------------

	const int				fInsCount;					// number of audio input ports
	const int				fOutsCount;					// number of audio output ports
	int						fCtrlCount;					// number of control ports

	LADSPA_PortDescriptor 	fPortDescs[MAXPORT];		// table of port descriptors to be used in a LADSPA_Descriptor
	const char* 			fPortNames[MAXPORT];		// table of port names to be used in a LADSPA_Descriptor
	LADSPA_PortRangeHint 	fPortHints[MAXPORT];		// table of port hints to be used in a LADSPA_Descriptor

    std::string					fPluginName;			// toplevel prefix used as plugin name
    std::stack<std::string>		fPrefix;				// current prefix for controls name


	//--------------------------------------------------------------------------------------
    std::string simplify(const std::string& src)
	{
		int		i = 0;
		int		level = 2;
        std::string	dst;

		while (src[i] ) {

			switch (level) {

				case 0 :
				case 1 :
				case 2 :
					// Skip the begin of the label "--foo-"
					// until 3 '-' have been read
					if (src[i]=='-') { level++; }
					break;

				case 3 :
					// copy the content, but skip non alphnum
					// and content in parenthesis
					switch (src[i]) {
						case '(' :
						case '[' :
							level++;
							break;

						case '-' :
							dst += '-';
							break;

						default :
							if (isalnum(src[i])) {
								dst+= tolower(src[i]);
							}

					}
					break;

				default :
					// here we are inside parenthesis and
					// we skip the content until we are back to
					// level 3
					switch (src[i]) {

						case '(' :
						case '[' :
							level++;
							break;

						case ')' :
						case ']' :
							level--;
							break;

						default :
							break;
					}

			}
			i++;
		}
		return (dst.size() > 0) ? dst :src;
	}

	void addPortDescr(int type, const char* label, int hint, float min = 0.0, float max = 0.0)
	{
        std::string fullname = simplify(fPrefix.top() + "-" + label);
		char* str = strdup(fullname.c_str());

		fPortDescs[fInsCount + fOutsCount + fCtrlCount] = type;
		fPortNames[fInsCount + fOutsCount + fCtrlCount] = str;
		fPortHints[fInsCount + fOutsCount + fCtrlCount].HintDescriptor = hint;
		fPortHints[fInsCount + fOutsCount + fCtrlCount].LowerBound = min;
		fPortHints[fInsCount + fOutsCount + fCtrlCount].UpperBound = max;
		fCtrlCount++;
	}

	void openAnyBox(const char* label)
	{
		if (fPrefix.size() == 0) {
			// top level label is used as plugin name
			fPluginName = label;
			fPrefix.push(label);

		} else {
            std::string s;
			if (label && label[0]) {
				s = fPrefix.top() + "-" + label;
			} else {
				s = fPrefix.top();
			}
			fPrefix.push(s);
		}
	}

 public:

	//--------------------------------Collect the audio ports-------------------------------

	portCollector(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0)
	{
		for (int i = 0; i < ins; i++) {
			fPortDescs[i] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
			fPortNames[i] = inames[i];
			fPortHints[i].HintDescriptor = 0;
		}
		for (int j = 0; j < outs; j++) {
			fPortDescs[ins + j] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
			fPortNames[ins + j] = onames[j];
			fPortHints[ins + j].HintDescriptor = 0;
		}
	};

	virtual ~portCollector() {}

	//------------------------------Collect the control ports-------------------------------

	virtual void addButton(const char* label, float* zone) {
		addPortDescr(ICONTROL, label, LADSPA_HINT_TOGGLED);
	}

	virtual void addToggleButton(const char* label, float* zone) {
		addPortDescr(ICONTROL, label, LADSPA_HINT_TOGGLED);
	}

	virtual void addCheckButton(const char* label, float* zone) {
		addPortDescr(ICONTROL, label, LADSPA_HINT_TOGGLED);
	}

	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) {
		addPortDescr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
	}

	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) {
		addPortDescr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
	}

	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) {
		addPortDescr(ICONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
	}

	// -- passive widgets

	virtual void addNumDisplay(const char* label, float* zone, int precision) {
		addPortDescr(OCONTROL, label, 0, -10000, +10000);
	}
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) {
		addPortDescr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
	}
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {
		addPortDescr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
	}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max){
		addPortDescr(OCONTROL, label, LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE, min, max);
	}
    
	virtual void openFrameBox(const char* label)	{ openAnyBox(label); }
	virtual void openTabBox(const char* label)		{ openAnyBox(label); }
	virtual void openHorizontalBox(const char* label)	{ openAnyBox(label); }
	virtual void openVerticalBox(const char* label)	{ openAnyBox(label); }

	virtual void closeBox() 					{ fPrefix.pop(); }

	virtual void show() {}
	virtual void run() 	{}

	//---------------------------------Fill the LADSPA descriptor---------------------------

	// generate an ID from a plugin name
	int makeID (const char* s) {
		int h = 0;
		for (int i = 0; s[i]; i++) {
			h = (h << 3) + (s[i] & 7);
		}
		return 1+h%1000;
	}

	// fill a ladspa descriptor with the information collected on ports
	void fillPortDescription (LADSPA_Descriptor * descriptor) {
		const char* name = sym(mydsp);
		descriptor->PortCount 			= fCtrlCount+fInsCount+fOutsCount;
		descriptor->PortDescriptors 	= fPortDescs;
		descriptor->PortNames 			= fPortNames;
		descriptor->PortRangeHints 		= fPortHints;

		descriptor->Label = strdup(name);
		descriptor->UniqueID = makeID(name);
//		descriptor->Label = strdup(fPluginName.c_str());
//		descriptor->UniqueID = makeID(fPluginName.c_str());
		descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
		descriptor->Name = name;
//		descriptor->Name = strdup(fPluginName.c_str());
		descriptor->Maker = "undefined";
		descriptor->Copyright = "undefined";
	}
};

//--------------------------------------portData----------------------------------------
//
// portData : a user interface used to associate the data buffers and the ports
//
//--------------------------------------------------------------------------------------

class portData : public UI
{

 private:

	//--------------------------------------------------------------------------------------

	const int				fInsCount;					// number of audio input ports
	const int				fOutsCount;					// number of audio output ports
	int						fCtrlCount;					// number of control ports

	float* 					fPortZone[MAXPORT];			//
	float* 					fPortData[MAXPORT];

	//--------------------------------------------------------------------------------------

	void addZone(float* zone)
	{
		fPortZone[fInsCount + fOutsCount + fCtrlCount] = zone;
		fCtrlCount++;
	}

 public:

	//--------------------------------Collect the audio ports-------------------------------

	portData(int ins, int outs) : UI(), fInsCount(ins), fOutsCount(outs), fCtrlCount(0) {};
	virtual ~portData() {}

	//------------------------------Collect the control zones-------------------------------

	virtual void addButton(const char* label, float* zone) 			{ addZone(zone); }
	virtual void addToggleButton(const char* label, float* zone)  	{ addZone(zone); }
	virtual void addCheckButton(const char* label, float* zone)  		{ addZone(zone); }

	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) 		{ addZone(zone); }
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) 	{ addZone(zone); }
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)  			{ addZone(zone); }

	// -- passive widgets

	virtual void addNumDisplay(const char* label, float* zone, int precision) 						{ addZone(zone); }
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) 	{ addZone(zone); }
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) 			{ addZone(zone); }
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)			{ addZone(zone); }

    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

	virtual void openFrameBox(const char* label)		{ }
	virtual void openTabBox(const char* label)		{ }
	virtual void openHorizontalBox(const char* label)	{ }
	virtual void openVerticalBox(const char* label)	{ }
	virtual void closeBox() 					{ }

	virtual void show() {}
	virtual void run() 	{}

	//---------------------------------interaction with LADSPA------------------------------

	void setPortData (unsigned long port, LADSPA_Data* data) {
		fPortData[port] = data;
	}

	void updateCtrlZones() {
		for (int i = fInsCount+fOutsCount; i < fInsCount+fOutsCount+fCtrlCount; i++)	*fPortZone[i] = *fPortData[i];
	}

	float** getInputs() {
		return &fPortData[0];
	}

	float** getOutputs() {
		return &fPortData[fInsCount];
	}
};

//--------------------------------Faust-LADSPA plugin-----------------------------------
//
// Plugin structure, callbacks and LADSPA_descriptor(i) entry point
//
//--------------------------------------------------------------------------------------

LADSPA_Descriptor* 	gDescriptor = 0;

struct PLUGIN
{
	unsigned long	fSampleRate;
	portData*		fPortData;
	dsp*			fDsp;

	PLUGIN(unsigned long r, portData* d, dsp* p) : fSampleRate(r), fPortData(d), fDsp(p) {}
};

LADSPA_Handle instantiate_method (const struct _LADSPA_Descriptor* Descriptor, unsigned long SampleRate)
{
	dsp*		p = new mydsp();
	portData* 	d = new portData(p->getNumInputs(), p->getNumOutputs());

	p->buildUserInterface(d);
	return new PLUGIN (SampleRate, d, p);
}

void connect_method (LADSPA_Handle Instance, unsigned long Port, LADSPA_Data* DataLocation)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->setPortData(Port, DataLocation);
}

void activate_method (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fDsp->init(p->fSampleRate);
}

void run_method (LADSPA_Handle Instance, unsigned long SampleCount)
{
	PLUGIN* p = (PLUGIN*) Instance;
	p->fPortData->updateCtrlZones();
	AVOIDDENORMALS;
	p->fDsp->compute(SampleCount, p->fPortData->getInputs(), p->fPortData->getOutputs());
}

void deactivate_method (LADSPA_Handle Instance)
{}

void cleanup_method (LADSPA_Handle Instance)
{
	PLUGIN* p = (PLUGIN*) Instance;
	delete p->fPortData;
	delete p->fDsp;
	delete p;
}

//--------------------------------------------------------------------------------------

void init_descriptor(LADSPA_Descriptor* descriptor)
{
	descriptor->UniqueID = 123456;
	descriptor->Label = "none";
	descriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
	descriptor->Name = "none";
	descriptor->Maker = "Yann Orlarey";
	descriptor->Copyright = "GPL";

	descriptor->ImplementationData = 0;

	// description des methods
	descriptor->instantiate = instantiate_method;
	descriptor->connect_port = connect_method;
	descriptor->activate = activate_method;
	descriptor->run = run_method;
	descriptor->run_adding = 0;
	descriptor->set_run_adding_gain = 0;
	descriptor->deactivate = deactivate_method;
	descriptor->cleanup = cleanup_method;
}

//--------------------------------------------------------------------------------------

const LADSPA_Descriptor* ladspa_descriptor(unsigned long Index)
{
    if (Index == 0) {
		if (gDescriptor == 0)
		{
			// allocate temporaries dsp and portCollector to build the plugin description
			mydsp* p = new mydsp();
			if (p) {
				portCollector*	c=new portCollector(p->getNumInputs(), p->getNumOutputs());
				p->buildUserInterface(c);
				gDescriptor = new LADSPA_Descriptor;
				init_descriptor(gDescriptor);
				c->fillPortDescription(gDescriptor);
				delete p;
			} else {
				printf("Memory Error : unable to allocate the dsp object\n");
			}
		}
		return gDescriptor;
	} else {
		return NULL;
	}
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
