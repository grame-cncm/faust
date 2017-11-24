/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2008-2011 Kjetil Matheussen <k.s.matheussen@notam02.no>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
    published by the Free Software Foundation; either version 2.1 of the 
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA. 
 ************************************************************************
 ************************************************************************/

/* link with  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#ifdef MAKE_GUI

#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <pthread.h> 
#include <sys/wait.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <libgen.h>

#endif

#include <list>
#include <map>

#include <rt-various.h> // realtime memory allocation in Snd.

using namespace std;

struct Meta : map<const char*, const char*>
{
  void declare (const char* key, const char* value) { (*this)[key]=value; }
};
	 	 
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

// g++ -O3 -lm -ljack `gtk-config --cflags --libs` ex2.cpp
 
// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }

inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int 		int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }

<<includeIntrinsic>>

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

#ifdef MAKE_GUI // It's enough to compile GUI code once.

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

	// -- registerZone(z,c) : zone management

        bool containsUI;
	void registerZone(float* z, uiItem* c)
	{
	        containsUI=true;
		if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
		fZoneMap[z]->push_back(c);
	} 	

	// -- saveState(filename) : save the value of every zone to a file
	
	void saveState(const char* filename)	
	{
		ofstream f(filename);
		
		for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) { 
			f << *(i->first) << ' ';
		} 
		
		f << endl;
		f.close();
	}

	// -- recallState(filename) : load the value of every zone from a file
	
	void recallState(const char* filename)	
	{
		ifstream f(filename);
		if (f.good()) {
			for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) { 
				f >> *(i->first);
			} 
		}
		f.close();
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
	
	virtual void addButton(const char* label, float* zone) = 0;
	virtual void addToggleButton(const char* label, float* zone) = 0;
	virtual void addCheckButton(const char* label, float* zone) = 0;
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
	
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
	
	void addCallback(float* zone, uiCallback foo, void* data);
	
	// -- widget's layouts
	
	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;
	virtual void closeBox() = 0;
	
	virtual void show() = 0;
	virtual void run() = 0;
	
        virtual void declare(float* zone, const char* key, const char* value) {}

	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }
};

/**
 * User Interface Item: abstract definition
 */

class uiItem
{
  protected :
		  
	UI*		fGUI;
	float*		fZone;
	float		fCache;
	
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

// en cours d'installation de call back. a finir!!!!!

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

/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE
								  gtk interface

*******************************************************************************
*******************************************************************************/

#include <gtk/gtk.h>

#define stackSize 256

// Insertion modes

#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

class GTKUI : public UI
{
 private :
  static bool		fInitialized;
  static list<UI*>	fGuiList;
	
 protected :
	GtkWidget* 	fWindow;
	int			fTop;
	GtkWidget* 	fBox[stackSize];
	int 		fMode[stackSize];
	bool		fStopped;

	GtkWidget* addWidget(const char* label, GtkWidget* w);
	virtual void pushBox(int mode, GtkWidget* w);

 public :
	
 	static const gboolean expand = TRUE;
	static const gboolean fill = TRUE;
	static const gboolean homogene = FALSE;
		 
	GTKUI(char * name, int* pargc, char*** pargv);
    GTKUI(){}
	
	// -- layout groups
	
	virtual void openFrameBox(const char* label);	
	virtual void openTabBox(const char* label = "");
	virtual void openHorizontalBox(const char* label = "");
	virtual void openVerticalBox(const char* label = "");
	
	virtual void closeBox();
	
	// -- active widgets
	
	virtual void addButton(const char* label, float* zone);
	virtual void addToggleButton(const char* label, float* zone);
	virtual void addCheckButton(const char* label, float* zone);
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);	
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);	
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
	
	// -- passive display widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision);
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max);
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);
	
	virtual void show();
	virtual void run();

    virtual void declare(float* zone, const char* key, const char* value) {}

};

/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  gtk implementation

*******************************************************************************
*******************************************************************************/

// global static fields

bool		GTKUI::fInitialized = false;
list<UI*>	UI::fGuiList;

static gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data )
{
    return FALSE; 
}

static void destroy_event( GtkWidget *widget, gpointer data )
{
    gtk_main_quit ();
}

GTKUI::GTKUI(char * name, int* pargc, char*** pargv) 
{
    if (!fInitialized) {
		gtk_init(pargc, pargv);
		fInitialized = true;
	}

	fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//gtk_container_set_border_width (GTK_CONTAINER (fWindow), 10);
	gtk_window_set_title (GTK_WINDOW (fWindow), name);
	gtk_signal_connect (GTK_OBJECT (fWindow), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
	gtk_signal_connect (GTK_OBJECT (fWindow), "destroy", GTK_SIGNAL_FUNC (destroy_event), NULL);

	fTop = 0;
	fBox[fTop] = gtk_vbox_new (homogene, 4);
	fMode[fTop] = kBoxMode;
	gtk_container_add (GTK_CONTAINER (fWindow), fBox[fTop]);
	fStopped = false;
}

// empilement des boites

void GTKUI::pushBox(int mode, GtkWidget* w)
{
	++fTop;
	assert(fTop < stackSize);
	fMode[fTop] 	= mode;
	fBox[fTop] 		= w;
}

void GTKUI::closeBox()
{
	--fTop;
	assert(fTop >= 0);
}

// les differentes boites

void GTKUI::openFrameBox(const char* label)
{
	GtkWidget * box = gtk_frame_new (label);
	//gtk_container_set_border_width (GTK_CONTAINER (box), 10);
			
	pushBox(kSingleMode, addWidget(label, box));
}

void GTKUI::openTabBox(const char* label)
{
	pushBox(kTabMode, addWidget(label, gtk_notebook_new ()));
}

void GTKUI::openHorizontalBox(const char* label)
{	
	GtkWidget * box = gtk_hbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box), 10);
			
	if (fMode[fTop] != kTabMode && label[0] != 0) {
		GtkWidget * frame = addWidget(label, gtk_frame_new (label));
		gtk_container_add (GTK_CONTAINER(frame), box);
		gtk_widget_show(box);
		pushBox(kBoxMode, box);
	} else {
		pushBox(kBoxMode, addWidget(label, box));
	}
}

void GTKUI::openVerticalBox(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box), 10);
			
	if (fMode[fTop] != kTabMode && label[0] != 0) {
		GtkWidget * frame = addWidget(label, gtk_frame_new (label));
		gtk_container_add (GTK_CONTAINER(frame), box);
		gtk_widget_show(box);
		pushBox(kBoxMode, box);
	} else {
		pushBox(kBoxMode, addWidget(label, box));
	}
}
	
GtkWidget* GTKUI::addWidget(const char* label, GtkWidget* w)
{ 
	switch (fMode[fTop]) {
		case kSingleMode	: gtk_container_add (GTK_CONTAINER(fBox[fTop]), w); 							break;
		case kBoxMode 		: gtk_box_pack_start (GTK_BOX(fBox[fTop]), w, expand, fill, 0); 				break;
		case kTabMode 		: gtk_notebook_append_page (GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label)); break;
	}
	gtk_widget_show (w);
	return w;
}

// --------------------------- Press button ---------------------------

struct uiButton : public uiItem
{
	GtkButton* 	fButton;
	
	uiButton (UI* ui, float* zone, GtkButton* b) : uiItem(ui, zone), fButton(b) {}
	
	static void pressed( GtkWidget *widget, gpointer   data )
	{
		uiItem* c = (uiItem*) data;
		c->modifyZone(1.0);
	}

	static void released( GtkWidget *widget, gpointer   data )
	{
		uiItem* c = (uiItem*) data;
		c->modifyZone(0.0);
	}

	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		if (v > 0.0) gtk_button_pressed(fButton); else gtk_button_released(fButton);
	}
};

void GTKUI::addButton(const char* label, float* zone)
{
	*zone = 0.0;
	GtkWidget* 	button = gtk_button_new_with_label (label);
	addWidget(label, button);
	
	uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));
	
	gtk_signal_connect (GTK_OBJECT (button), "pressed", GTK_SIGNAL_FUNC (uiButton::pressed), (gpointer) c);
	gtk_signal_connect (GTK_OBJECT (button), "released", GTK_SIGNAL_FUNC (uiButton::released), (gpointer) c);
}

// ---------------------------	Toggle Buttons ---------------------------

struct uiToggleButton : public uiItem
{
	GtkToggleButton* fButton;
	
	uiToggleButton(UI* ui, float* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}
	
	static void toggled (GtkWidget *widget, gpointer data)
	{
    	float	v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0; 
    	((uiItem*)data)->modifyZone(v);
	}

	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		gtk_toggle_button_set_active(fButton, v > 0.0);	
	}
};

void GTKUI::addToggleButton(const char* label, float* zone)
{
	*zone = 0.0;
	GtkWidget* 	button = gtk_toggle_button_new_with_label (label);
	addWidget(label, button);
	
	uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
	gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);
}

// ---------------------------	Check Button ---------------------------

struct uiCheckButton : public uiItem
{
	GtkToggleButton* fButton;
	
	uiCheckButton(UI* ui, float* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}
	
	static void toggled (GtkWidget *widget, gpointer data)
	{
    	float	v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0; 
    	((uiItem*)data)->modifyZone(v);
	}

	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		gtk_toggle_button_set_active(fButton, v > 0.0);	
	}
};

void GTKUI::addCheckButton(const char* label, float* zone)
{
	*zone = 0.0;
	GtkWidget* 	button = gtk_check_button_new_with_label (label);
	addWidget(label, button);
	
	uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
	gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC(uiCheckButton::toggled), (gpointer) c);
}

// ---------------------------	Adjustmenty based widgets ---------------------------

struct uiAdjustment : public uiItem
{
	GtkAdjustment* fAdj;
	
	uiAdjustment(UI* ui, float* zone, GtkAdjustment* adj) : uiItem(ui, zone), fAdj(adj) {}
	
	static void changed (GtkWidget *widget, gpointer data)
	{
    	float	v = GTK_ADJUSTMENT (widget)->value; 
    	((uiItem*)data)->modifyZone(v);
	}

	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		gtk_adjustment_set_value(fAdj, v);	
	}
};

static int precision(double n)
{
	if (n < 0.009999) return 3;
	else if (n < 0.099999) return 2;
	else if (n < 0.999999) return 1;
	else return 0;
}

// -------------------------- Vertical Slider -----------------------------------

void GTKUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
	
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

	gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
	
	GtkWidget* slider = gtk_vscale_new (GTK_ADJUSTMENT(adj));
	gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
	gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
	gtk_widget_set_usize(slider, -1, 160);
	
	openFrameBox(label);
	addWidget(label, slider);
	closeBox();
}

// -------------------------- Horizontal Slider -----------------------------------

void GTKUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
	
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

	gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
	
	GtkWidget* slider = gtk_hscale_new (GTK_ADJUSTMENT(adj));
	gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
	gtk_widget_set_usize(slider, 160, -1);
	
	openFrameBox(label);
	addWidget(label, slider);
	closeBox();
}

// ------------------------------ Num Entry -----------------------------------

void GTKUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, step);
	
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

	gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
	
	GtkWidget* spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), 0.005, precision(step));

	//gtk_widget_set_usize(slider, 160, -1);
	openFrameBox(label);
	addWidget(label, spinner);
	closeBox();
}


// ==========================	passive widgets ===============================

// ------------------------------ Progress Bar -----------------------------------

struct uiBargraph : public uiItem
{
	GtkProgressBar*		fProgressBar;
	float				fMin;
	float				fMax;
	
	uiBargraph(UI* ui, float* zone, GtkProgressBar* pbar, float lo, float hi) 
			: uiItem(ui, zone), fProgressBar(pbar), fMin(lo), fMax(hi) {}

	float scale(float v) 		{ return (v-fMin)/(fMax-fMin); }
	
	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v; 
		gtk_progress_bar_set_fraction(fProgressBar, scale(v));	
	}
};

void GTKUI::addVerticalBargraph(const char* label, float* zone, float lo, float hi)
{
	GtkWidget* pb = gtk_progress_bar_new();
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_BOTTOM_TO_TOP);
	gtk_widget_set_size_request(pb, 8, -1);
	new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
	openFrameBox(label);
	addWidget(label, pb);
	closeBox();
}

void GTKUI::addHorizontalBargraph(const char* label, float* zone, float lo, float hi)
{
	GtkWidget* pb = gtk_progress_bar_new();
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_LEFT_TO_RIGHT);
	gtk_widget_set_size_request(pb, -1, 8);
	new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
	openFrameBox(label);
	addWidget(label, pb);
	closeBox();
}

// ------------------------------ Num Display -----------------------------------

struct uiNumDisplay : public uiItem
{
	GtkLabel* fLabel;
	int	fPrecision;
	
	uiNumDisplay(UI* ui, float* zone, GtkLabel* label, int precision) 
			: uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v;
		char s[64]; 
		if (fPrecision <= 0) { 
			snprintf(s, 63, "%d", int(v)); 
		} else if (fPrecision>3) {
			snprintf(s, 63, "%f", v);
		} else {
			const char* format[] = {"%.1f", "%.2f", "%.3f"};
			snprintf(s, 63, format[fPrecision-1], v);
		}
		gtk_label_set_text(fLabel, s);
	}
};

void GTKUI::addNumDisplay(const char* label, float* zone, int precision )
{
	GtkWidget* lw = gtk_label_new("");
	new uiNumDisplay(this, zone, GTK_LABEL(lw), precision);
	openFrameBox(label);
	addWidget(label, lw);
	closeBox();
}

// ------------------------------ Text Display -----------------------------------

struct uiTextDisplay : public uiItem
{
	GtkLabel* 	fLabel;
	const char**		fNames;
	float		fMin;
	float		fMax;
	int			fNum;
	
	
	uiTextDisplay (UI* ui, float* zone, GtkLabel* label, const char* names[], float lo, float hi) 
			: uiItem(ui, zone), fLabel(label), fNames(names), fMin(lo), fMax(hi)  
	{
		fNum = 0;
		while (fNames[fNum] != 0) fNum++;
	}

	virtual void reflectZone() 	
	{ 
		float 	v = *fZone;
		fCache = v;
		
		int idx = int(fNum*(v-fMin)/(fMax-fMin));
		
		if 		(idx < 0) 		idx = 0; 
		else if (idx >= fNum) 	idx = fNum-1;
				
		gtk_label_set_text(fLabel, fNames[idx]); 
	}
};

void GTKUI::addTextDisplay(const char* label, float* zone, const char* names[], float lo, float hi )
{
	GtkWidget* lw = gtk_label_new("");
	new uiTextDisplay (this, zone, GTK_LABEL(lw), names, lo, hi);
	openFrameBox(label);
	addWidget(label, lw);
	closeBox();
}

void GTKUI::show() 
{
	assert(fTop == 0);
	gtk_widget_show  (fBox[0]);
	gtk_widget_show  (fWindow);
}

/**
 * Update all user items reflecting zone z
 */
	
static gboolean callUpdateAllGuis(gpointer)
{ 
	UI::updateAllGuis(); 
	return TRUE;
}

void GTKUI::run() 
{
	assert(fTop == 0);
	gtk_widget_show  (fBox[0]);
	gtk_widget_show  (fWindow);
	gtk_timeout_add(40, callUpdateAllGuis, 0);
	gtk_main ();
	stop();
}

#else // MAKE_GUI

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
	
	virtual void addButton(const char* label, float* zone) = 0;
	virtual void addToggleButton(const char* label, float* zone) = 0;
	virtual void addCheckButton(const char* label, float* zone) = 0;
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
	
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
	
	void addCallback(float* zone, uiCallback foo, void* data);
	
	// -- widget's layouts
	
	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;
	virtual void closeBox() = 0;
	
	virtual void show() = 0;
	virtual void run() = 0;
	
	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }
};


/**
 * User Interface Item: abstract definition
 */

class uiItem
{
  protected :
		  
	UI*		fGUI;
	float*		fZone;
	float		fCache;
	
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

#endif // MAKE_GUI

/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------
//  définition du processeur de signal
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

    void* operator new(size_t size){
      return clm_malloc_atomic(size,"faust new");
    }

};

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		
<<includeclass>>


#ifdef MAKE_GUI

class SNDRTGTKUI : public GTKUI{
public:

  SNDRTGTKUI(char * name, GtkDialog *window);
  void localRun();
  /*
  bool containUI;
  void registerZone(float* z, uiItem* c){    
    containUI=true;
    GTKUI:registerZone(z,c);
  }
  */
};

SNDRTGTKUI::SNDRTGTKUI(char * name, GtkDialog *window) 
{
    containsUI = false;

	fWindow = GTK_WIDGET(GTK_WINDOW(window));
	fTop = 0;
	fBox[fTop] = window->vbox;
	fMode[fTop] = kBoxMode;
	fStopped = false;
}

void SNDRTGTKUI::localRun(){
  assert(fTop == 0);

  if (!containsUI)
    return;

  gtk_widget_show  (fBox[0]);
  gtk_widget_show  (fWindow);
  gtk_timeout_add(40, callUpdateAllGuis, 0);

}

extern "C" SNDRTGTKUI* newGTKUI(char *name,	void* 	window){
  return new SNDRTGTKUI(name,(GtkDialog*)window);
}

extern "C" void runGTKUI(SNDRTGTKUI* ui){
  ui->localRun();
}

extern "C" int containsUI(SNDRTGTKUI* ui){
  return ui->containsUI==true?1:0;
}

#endif

extern "C" dsp* newDsp() 									{ return new mydsp(); }
extern "C" void deleteDsp(dsp* self) 						{ delete self; }

extern "C" int getNumInputs(dsp* self) 						{ return self->getNumInputs(); }
extern "C" int getNumOutputs(dsp* self) 					{ return self->getNumOutputs(); }
extern "C" void buildUserInterface(dsp* self,UI* interface) { self->buildUserInterface(interface); }
extern "C" void init(dsp* self, int freq) 					{ self->init(freq); }
extern "C" void compute(dsp* self, int len, float** inputs, float** outputs) { self->compute(len, inputs, outputs); }
extern "C" void conclude(dsp* self)							{ self->conclude(); }

