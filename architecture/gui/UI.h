/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces

*******************************************************************************
*******************************************************************************/

#ifndef __UI__
#define __UI__

#include <fstream>
#include <list>
#include <map>

struct uiItem;
typedef void (*uiCallback)(float val, void* data);

/**
 * Graphic User Interface : abstract definition
 */

class UI
{
	typedef std::list<uiItem*> clist;
	typedef std::map<float*, clist*> zmap;
	
 private:
 	static std::list<UI*>	fGuiList;
	zmap				fZoneMap;
	bool				fStopped;
	
 public:
		
			 UI() : fStopped(false)	{ fGuiList.push_back(this); }
	virtual ~UI()	{ /* suppression de this dans fGuiList */ }

	// -- registerZone(z,c) : zone management	
	void registerZone(float* z, uiItem* c)
	{
		if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
		fZoneMap[z]->push_back(c);
	} 	

	// -- saveState(filename) : save the value of every zone to a file
	void saveState(const char* filename)	
	{
		std::ofstream f(filename);		
		for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
			f << *(i->first) << ' ';
		f << std::endl;
		f.close();
	}

	// -- recallState(filename) : load the value of every zone from a file	
	void recallState(const char* filename)	
	{
		std::ifstream f(filename);
		if (f.good()) {
			for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++)
				f >> *(i->first);
		}
		f.close();
	}
	
	void updateAllZones();
	
	void updateZone(float* z);
	
	static void updateAllGuis()
	{
		std::list<UI*>::iterator g;
		for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
			(*g)->updateAllZones();
		}
	}
        
        // -- active widgets
        
        virtual void addButton(const char* label, float* zone) = 0;
        virtual void addToggleButton(const char* label, float* zone) = 0;
        virtual void addCheckButton(const char* label, float* zone) = 0;
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        //virtual void addKnob(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
        
        // -- passive widgets
        
        virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
        //virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) = 0;
        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
        
        void addCallback(float* zone, uiCallback foo, void* data);
        
        // -- widget's layouts
        
        //virtual void openFrameBox(const char* label) = 0;
        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;

        // -- extra widget's layouts
    
        //virtual void openDialogBox(const char* label, float* zone) = 0;
        //virtual void openEventBox(const char* label) = 0;
        //virtual void openHandleBox(const char* label) = 0;
        //virtual void openExpanderBox(const char* label, float* zone) = 0;

        virtual void closeBox() = 0;
        
        virtual void show() {};
        virtual void run() {};
	
	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }

    virtual void declare(float* /*zone*/, const char* /*key*/, const char* /*value*/) {}
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

#endif
