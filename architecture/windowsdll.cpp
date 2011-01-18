/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#include <map>
#include <list>

using namespace std;


struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};


/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

<<includeIntrinsic>>

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces

*******************************************************************************
*******************************************************************************/

#include <map>
#include <list>

using namespace std;


struct uiItem;
typedef void (*uiCallback)(float val, void* data);

/**
 * Graphic User Interface : abstract definition
 */

class UI 
{
	typedef list<uiItem*> clist;
	typedef map<float*, clist*> zmap;
	
 private:
 	static list<UI*>	fGuiList;
	zmap				fZoneMap;
	bool				fStopped;
	
 public:
		
	UI() : fStopped(false) {	
		fGuiList.push_back(this);
	}
	
	virtual ~UI() {
		// suppression de this dans fGuiList
	}

	// -- zone management
	
	void registerZone(float* z, uiItem* c)
	{
		if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
		fZoneMap[z]->push_back(c);
	} 	
	
	void updateAllZones();
	
	void updateZone(float* z);
	
	static void updateAllGuis()
	{
		list<UI*>::iterator g;
		for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
			(*g)->updateAllZones();
		}
	}
	
	// -- active widgets
	
	virtual void addButton(char* label, float* zone) = 0;
	virtual void addToggleButton(char* label, float* zone) = 0;
	virtual void addCheckButton(char* label, float* zone) = 0;
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;
	
	// -- passive widgets
	
	virtual void addNumDisplay(char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(char* label, float* zone, float min, float max) = 0;
	
	void addCallback(float* zone, uiCallback foo, void* data);
	
	// -- widget's layouts
	
	virtual void openFrameBox(char* label) = 0;
	virtual void openTabBox(char* label) = 0;
	virtual void openHorizontalBox(char* label) = 0;
	virtual void openVerticalBox(char* label) = 0;
	virtual void closeBox() = 0;

    virtual void declare(float* zone, const char* key, const char* value) {}
};


/**
 * User Interface Item: abstract definition
 */

class uiItem
{
  protected :
		  
	UI*		fGUI;
	float*	fZone;
	float	fCache;
	
	uiItem (UI* ui, float* zone) : fGUI(ui), fZone(zone), fCache(-123456.654321) 
	{ 
		ui->registerZone(zone, this); 
	}	
	
  public :

	virtual ~uiItem() {}
	
	void modifyZone(float v) 	
	{ 
		fCache = v;
		if (*fZone != v) {
			*fZone = v;
			fGUI->updateZone(fZone);
		}
	}
		  	
	float			cache()			{ return fCache; }
	virtual void 	reflectZone() 	= 0;	
};


/**
 * Callback Item
 */

struct uiCallbackItem : public uiItem
{
	uiCallback	fCallback;
	void*		fData;
	
	uiCallbackItem(UI* ui, float* zone, uiCallback foo, void* data) 
			: uiItem(ui, zone), fCallback(foo), fData(data) {}
	
	virtual void 	reflectZone() {		
		float 	v = *fZone;
		fCache = v; 
		fCallback(v, fData);	
	}
};

/**
 * Update all user items reflecting zone z
 */

inline void UI::updateZone(float* z)
{
	float 	v = *z;
	clist* 	l = fZoneMap[z];
	for (clist::iterator c = l->begin(); c != l->end(); c++) {
		if ((*c)->cache() != v) (*c)->reflectZone();
	}
}

/**
 * Update all user items not up to date
 */

inline void UI::updateAllZones()
{
	for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++) {
		float* 	z = m->first;
		clist*	l = m->second;
		float	v = *z;
		for (clist::iterator c = l->begin(); c != l->end(); c++) {
			if ((*c)->cache() != v) (*c)->reflectZone();
		}
	}
}

inline void UI::addCallback(float* zone, uiCallback foo, void* data) 
{ 
	new uiCallbackItem(this, zone, foo, data); 
};		

//----------------------------------------------------------------
//  d�inition du processeur de signal
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}
	
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
 	virtual void conclude() 										{}
};
		
/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/
		
<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					

#define EXPORT __declspec(dllexport)

extern "C" EXPORT dsp*  newDsp() 									{ return new mydsp(); }
extern "C" EXPORT void EXPORT deleteDsp(dsp* self) 						{ delete self; }

extern "C" EXPORT int getNumInputs(dsp* self) 						{ return self->getNumInputs(); }
extern "C" EXPORT int getNumOutputs(dsp* self) 						{ return self->getNumOutputs(); }
extern "C" EXPORT void buildUserInterface(dsp* self,UI* interface) 	{ self->buildUserInterface(interface); }
extern "C" EXPORT void init(dsp* self, int freq) 					{ self->init(freq); }
extern "C" EXPORT void compute(dsp* self, int len, float** inputs, float** outputs) { self->compute(len, inputs, outputs); }
extern "C" EXPORT void conclude(dsp* self)							{ self->conclude(); }

/********************END ARCHITECTURE SECTION (part 2/2)****************/



