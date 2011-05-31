/* link with  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <sys/wait.h>
#include <list>
#include <vector>
#include <map>
#include <set>

#include <iostream>
#include <fstream>

#include <libgen.h>
#include <jack/jack.h>

using namespace std;

// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

//#define BENCHMARKMODE

#ifdef __APPLE__
#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#endif

#ifndef UInt64
typedef long long unsigned int UInt64;
typedef unsigned int UInt32;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

UInt64 DSP_rdtsc(void)
{
	union {
		UInt32 i32[2];
		UInt64 i64;
	} count;

	__asm__ __volatile__("rdtsc" : "=a" (count.i32[0]), "=d" (count.i32[1]));
     return count.i64;
}

#define LOCK "lock ; "

char CAS1(volatile void* addr, volatile int value, int newvalue)
{
    register char ret;
    __asm__ __volatile__ (
						  "# CAS \n\t"
						  LOCK "cmpxchg %2, (%1) \n\t"
						  "sete %0               \n\t"
						  : "=a" (ret)
						  : "c" (addr), "d" (newvalue), "a" (value)
                          : "memory"
						  );
    return ret;
}

int atomic_xadd(volatile int* atomic, int val)
{
    register int result;
    __asm__ __volatile__ ("# atomic_xadd \n\t"
                          LOCK "xaddl %0,%1 \n\t"
                          : "=r" (result), "=m" (*atomic)
                          : "0" (val), "m" (*atomic));
    return result;
}

#ifdef __cplusplus
}
#endif

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};


#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

inline int	lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }
inline int 	int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
//#define IS_DOUBLE 1
#endif

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces

*******************************************************************************
*******************************************************************************/

struct uiItem;
typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

/**
 * Graphic User Interface : abstract definition
 */

class UI
{
	typedef list<uiItem*> clist;
	typedef map<FAUSTFLOAT*, clist*> zmap;

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

	void registerZone(FAUSTFLOAT* z, uiItem* c)
	{
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

	void updateZone(FAUSTFLOAT* z);

	static void updateAllGuis()
	{
		list<UI*>::iterator g;
		for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
			(*g)->updateAllZones();
		}
	}

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addToggleButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

    // -- passive widgets

    virtual void addNumDisplay(const char* label, FAUSTFLOAT* zone, int precision) = 0;
    virtual void addTextDisplay(const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max) = 0;
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

    void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data);

    // -- widget's layouts

    virtual void openFrameBox(const char* label) = 0;
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;

    // -- extra widget's layouts

    virtual void openDialogBox(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void openEventBox(const char* label) = 0;
    virtual void openHandleBox(const char* label) = 0;
    virtual void openExpanderBox(const char* label, FAUSTFLOAT* zone) = 0;

    virtual void closeBox() = 0;

    virtual void show() {};
    virtual void run() {};

	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value) {}
};


/**
 * User Interface Item: abstract definition
 */

class uiItem
{
  protected :

	UI*		fGUI;
	FAUSTFLOAT*		fZone;
	FAUSTFLOAT		fCache;

	uiItem (UI* ui, FAUSTFLOAT* zone) : fGUI(ui), fZone(zone), fCache(-123456.654321)
	{
		ui->registerZone(zone, this);
	}


  public :
	virtual ~uiItem() {}

	void modifyZone(FAUSTFLOAT v)
	{
		fCache = v;
		if (*fZone != v) {
			*fZone = v;
			fGUI->updateZone(fZone);
		}
	}

	FAUSTFLOAT			cache()			{ return fCache; }
	virtual void 	reflectZone() 	= 0;
};


/**
 * Callback Item
 */

struct uiCallbackItem : public uiItem
{
	uiCallback	fCallback;
	void*		fData;

	uiCallbackItem(UI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
			: uiItem(ui, zone), fCallback(foo), fData(data) {}

	virtual void 	reflectZone() {
		FAUSTFLOAT 	v = *fZone;
		fCache = v;
		fCallback(v, fData);
	}
};

// en cours d'installation de call back. a finir!!!!!

/**
 * Update all user items reflecting zone z
 */

inline void UI::updateZone(FAUSTFLOAT* z)
{
	FAUSTFLOAT 	v = *z;
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
		FAUSTFLOAT* 	z = m->first;
		clist*	l = m->second;
		FAUSTFLOAT	v = *z;
		for (clist::iterator c = l->begin(); c != l->end(); c++) {
			if ((*c)->cache() != v) (*c)->reflectZone();
		}
	}
}

inline void UI::addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
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
#include <gdk/gdkkeysyms.h>

#define stackSize 256

// Insertion modes

#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

//------------ calculate needed precision
static int precision(double n)
{
    if (n < 0.009999) return 3;
    else if (n < 0.099999) return 2;
    else if (n < 0.999999) return 1;
    else return 0;
}

namespace gtk_knob
{

class GtkKnob
{
private:
	double start_x, start_y, max_value;
public:
	GtkRange parent;
	int last_quadrant;
	GtkKnob();
	~GtkKnob();
	GtkWidget *gtk_knob_new_with_adjustment(GtkAdjustment *_adjustment);

};

#define GTK_TYPE_KNOB          (gtk_knob_get_type())
#define GTK_KNOB(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_KNOB, GtkKnob))
#define GTK_IS_KNOB(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_KNOB))
#define GTK_KNOB_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GTK_TYPE_KNOB, GtkKnobClass))
#define GTK_IS_KNOB_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GTK_TYPE_KNOB))

GtkKnob::GtkKnob()
// GtkKnob constructor
{

}

GtkKnob::~GtkKnob()
{
	// Nothing specific to do...
}

struct GtkKnobClass {
	GtkRangeClass parent_class;
	int knob_x;
	int knob_y;
	int knob_step;
	int button_is;

};

//------forward declaration
GType gtk_knob_get_type ();

/****************************************************************
 ** calculate the knop pointer with dead zone
 */

const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs

static void knob_expose(GtkWidget *widget, int knob_x, int knob_y, GdkEventExpose *event, int arc_offset)
{
	/** check resize **/
	int grow;
	if(widget->allocation.width > widget->allocation.height) {
		grow = widget->allocation.height;
	} else {
		grow =  widget->allocation.width;
	}
	knob_x = grow-4;
	knob_y = grow-4;
	/** get values for the knob **/
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	int knobx = (widget->allocation.x+2 + (widget->allocation.width-4 - knob_x) * 0.5);
	int knoby = (widget->allocation.y+2 + (widget->allocation.height-4 - knob_y) * 0.5);
	int knobx1 = (widget->allocation.x+2 + (widget->allocation.width-4)* 0.5);
	int knoby1 = (widget->allocation.y+2 + (widget->allocation.height-4) * 0.5);
	double knobstate = (adj->value - adj->lower) / (adj->upper - adj->lower);
	double angle = scale_zero + knobstate * 2 * (M_PI - scale_zero);
	double knobstate1 = (0. - adj->lower) / (adj->upper - adj->lower);
	double pointer_off = knob_x/6;
	double radius = min(knob_x-pointer_off, knob_y-pointer_off) / 2;
	double lengh_x = (knobx+radius+pointer_off/2) - radius * sin(angle);
	double lengh_y = (knoby+radius+pointer_off/2) + radius * cos(angle);
	double radius1 = min(knob_x, knob_y) / 2 ;

	/** get widget forground color convert to cairo **/
	GtkStyle *style = gtk_widget_get_style (widget);
	double r = min(0.6,style->fg[gtk_widget_get_state(widget)].red/65535.0),
		   g = min(0.6,style->fg[gtk_widget_get_state(widget)].green/65535.0),
		   b = min(0.6,style->fg[gtk_widget_get_state(widget)].blue/65535.0);

	/** paint focus **/
	if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
		gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
		                knobx-2, knoby-2, knob_x+4, knob_y+4);
	}
	/** create clowing knobs with cairo **/
	cairo_t *cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	GdkRegion *region;
	region = gdk_region_rectangle (&widget->allocation);
	gdk_region_intersect (region, event->region);
	gdk_cairo_region (cr, region);
	cairo_clip (cr);

	cairo_arc(cr,knobx1+arc_offset, knoby1+arc_offset, knob_x/2.1, 0, 2 * M_PI );
	cairo_pattern_t*pat =
		cairo_pattern_create_radial (knobx1+arc_offset-knob_x/6,knoby1+arc_offset-knob_x/6, 1,knobx1+arc_offset,knoby1+arc_offset,knob_x/2.1 );
	if(adj->lower<0 && adj->value>0.) {
		cairo_pattern_add_color_stop_rgb (pat, 0, r+0.4, g+0.4 + knobstate-knobstate1, b+0.4);
		cairo_pattern_add_color_stop_rgb (pat, 0.7, r+0.15, g+0.15 + (knobstate-knobstate1)*0.5, b+0.15);
		cairo_pattern_add_color_stop_rgb (pat, 1, r, g, b);
	} else if(adj->lower<0 && adj->value<=0.) {
		cairo_pattern_add_color_stop_rgb (pat, 0, r+0.4 +knobstate1- knobstate, g+0.4, b+0.4);
		cairo_pattern_add_color_stop_rgb (pat, 0.7, r+0.15 +(knobstate1- knobstate)*0.5, g+0.15, b+0.15);
		cairo_pattern_add_color_stop_rgb (pat, 1, r, g, b);
	} else {
		cairo_pattern_add_color_stop_rgb (pat, 0, r+0.4, g+0.4 +knobstate, b+0.4);
		cairo_pattern_add_color_stop_rgb (pat, 0.7, r+0.15, g+0.15 + knobstate*0.5, b+0.15);
		cairo_pattern_add_color_stop_rgb (pat, 1, r, g, b);
	}
	cairo_set_source (cr, pat);
	cairo_fill_preserve (cr);
	gdk_cairo_set_source_color(cr, gtk_widget_get_style (widget)->fg);
	cairo_set_line_width(cr, 2.0);
	cairo_stroke(cr);

	/** create a rotating pointer on the kob**/
	cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
	cairo_set_line_width(cr,max(3, min(7, knob_x/15)));
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
	cairo_move_to(cr, knobx+radius1, knoby+radius1);
	cairo_line_to(cr,lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_set_source_rgb(cr,  0.9, 0.9, 0.9);
	cairo_set_line_width(cr,min(5, max(1,knob_x/30)));
	cairo_move_to(cr, knobx+radius1, knoby+radius1);
	cairo_line_to(cr,lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_pattern_destroy (pat);
	gdk_region_destroy (region);
	cairo_destroy(cr);
}

/****************************************************************
 ** general expose events for all "knob" controllers
 */

//----------- draw the Knob when moved
static gboolean gtk_knob_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GTK_IS_KNOB(widget));
	GtkKnobClass *klass =  GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));
	knob_expose(widget, klass->knob_x, klass->knob_y, event, 0);
	return TRUE;
}

/****************************************************************
 ** set initial size for GdkDrawable per type
 */

static void gtk_knob_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GTK_IS_KNOB(widget));
	GtkKnobClass *klass =  GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));
	requisition->width = klass->knob_x;
	requisition->height = klass->knob_y;
}

/****************************************************************
 ** set value from key bindings
 */

static void gtk_knob_set_value (GtkWidget *widget, int dir_down)
{
	g_assert(GTK_IS_KNOB(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

	int oldstep = (int)(0.5f + (adj->value - adj->lower) / adj->step_increment);
	int step;
	int nsteps = (int)(0.5f + (adj->upper - adj->lower) / adj->step_increment);
	if (dir_down)
		step = oldstep - 1;
	else
		step = oldstep + 1;
	float value = adj->lower + step * double(adj->upper - adj->lower) / nsteps;
	gtk_widget_grab_focus(widget);
	gtk_range_set_value(GTK_RANGE(widget), value);
}

/****************************************************************
 ** keyboard bindings
 */

static gboolean gtk_knob_key_press (GtkWidget *widget, GdkEventKey *event)
{
	g_assert(GTK_IS_KNOB(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	switch (event->keyval) {
	case GDK_Home:
		gtk_range_set_value(GTK_RANGE(widget), adj->lower);
		return TRUE;
	case GDK_End:
		gtk_range_set_value(GTK_RANGE(widget), adj->upper);
		return TRUE;
	case GDK_Up:
		gtk_knob_set_value(widget, 0);
		return TRUE;
	case GDK_Right:
		gtk_knob_set_value(widget, 0);
		return TRUE;
	case GDK_Down:
		gtk_knob_set_value(widget, 1);
		return TRUE;
	case GDK_Left:
		gtk_knob_set_value(widget, 1);
		return TRUE;
	}

	return FALSE;
}

/****************************************************************
 ** alternative (radial) knob motion mode (ctrl + mouse pressed)
 */

static void knob_pointer_event(GtkWidget *widget, gdouble x, gdouble y, int knob_x, int knob_y,
                               bool drag, int state)
{
	static double last_y = 2e20;
	GtkKnob *knob = GTK_KNOB(widget);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	double radius =  min(knob_x, knob_y) / 2;
	int  knobx = (widget->allocation.width - knob_x) / 2;
	int  knoby = (widget->allocation.height - knob_y) / 2;
	double posx = (knobx + radius) - x; // x axis right -> left
	double posy = (knoby + radius) - y; // y axis top -> bottom
	double value;
	if (!drag) {
		if (state & GDK_CONTROL_MASK) {
			last_y = 2e20;
			return;
		} else {
			last_y = posy;
		}
	}
	if (last_y < 1e20) { // in drag started with Control Key
		const double scaling = 0.005;
		double scal = (state & GDK_SHIFT_MASK ? scaling*0.1 : scaling);
		value = (last_y - posy) * scal;
		last_y = posy;
		gtk_range_set_value(GTK_RANGE(widget), adj->value - value * (adj->upper - adj->lower));
		return;
	}

	double angle = atan2(-posx, posy) + M_PI; // clockwise, zero at 6 o'clock, 0 .. 2*M_PI
	if (drag) {
		// block "forbidden zone" and direct moves between quadrant 1 and 4
		int quadrant = 1 + int(angle/M_PI_2);
		if (knob->last_quadrant == 1 && (quadrant == 3 || quadrant == 4)) {
			angle = scale_zero;
		} else if (knob->last_quadrant == 4 && (quadrant == 1 || quadrant == 2)) {
			angle = 2*M_PI - scale_zero;
		} else {
			if (angle < scale_zero) {
				angle = scale_zero;
			} else if (angle > 2*M_PI - scale_zero) {
				angle = 2*M_PI - scale_zero;
			}
			knob->last_quadrant = quadrant;
		}
	} else {
		if (angle < scale_zero) {
			angle = scale_zero;
		} else if (angle > 2*M_PI - scale_zero) {
			angle = 2*M_PI - scale_zero;
		}
		knob->last_quadrant = 0;
	}
	angle = (angle - scale_zero) / (2 * (M_PI-scale_zero)); // normalize to 0..1
	gtk_range_set_value(GTK_RANGE(widget), adj->lower + angle * (adj->upper - adj->lower));
}

/****************************************************************
 ** mouse button pressed set value
 */

static gboolean gtk_knob_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GTK_IS_KNOB(widget));

	GtkKnobClass *klass =  GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));


	switch (event->button) {
	case 1:  // left button
		gtk_widget_grab_focus(widget);
		gtk_widget_grab_default (widget);
		gtk_grab_add(widget);
		klass->button_is = 1;
		knob_pointer_event(widget, event->x, event->y, klass->knob_x, klass->knob_y,
						   false, event->state);
		break;
	case 2: //wheel
		klass->button_is = 2;
		break;
	case 3:  // right button
		klass->button_is = 3;
		break;
	default: // do nothing
		break;
	}
	return TRUE;
}

/****************************************************************
 ** mouse button release
 */

static gboolean gtk_knob_button_release (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GTK_IS_KNOB(widget));
	GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget))->button_is = 0;
	if (GTK_WIDGET_HAS_GRAB(widget))
		gtk_grab_remove(widget);
	return FALSE;
}

/****************************************************************
 ** set the value from mouse movement
 */

static gboolean gtk_knob_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GTK_IS_KNOB(widget));
	GtkKnobClass *klass =  GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));

	gdk_event_request_motions (event);

	if (GTK_WIDGET_HAS_GRAB(widget)) {
		knob_pointer_event(widget, event->x, event->y, klass->knob_x, klass->knob_y,
						   true, event->state);
	}
	return FALSE;
}

/****************************************************************
 ** set value from mouseweel
 */

static gboolean gtk_knob_scroll (GtkWidget *widget, GdkEventScroll *event)
{
	usleep(5000);
	gtk_knob_set_value(widget, event->direction);
	return FALSE;
}

/****************************************************************
 ** init the GtkKnobClass
 */

static void gtk_knob_class_init (GtkKnobClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

	/** set here the sizes and steps for the used knob **/
//--------- small knob size and steps

	klass->knob_x = 30;
	klass->knob_y = 30;
	klass->knob_step = 86;

//--------- event button
	klass->button_is = 0;

//--------- connect the events with funktions
	widget_class->expose_event = gtk_knob_expose;
	widget_class->size_request = gtk_knob_size_request;
	widget_class->button_press_event = gtk_knob_button_press;
	widget_class->button_release_event = gtk_knob_button_release;
	widget_class->motion_notify_event = gtk_knob_pointer_motion;
	widget_class->key_press_event = gtk_knob_key_press;
	widget_class->scroll_event = gtk_knob_scroll;
}

/****************************************************************
 ** init the Knob type/size
 */

static void gtk_knob_init (GtkKnob *knob)
{
	GtkWidget *widget = GTK_WIDGET(knob);
	GtkKnobClass *klass =  GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));

	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(knob), GTK_CAN_FOCUS);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(knob), GTK_CAN_DEFAULT);

	widget->requisition.width = klass->knob_x;
	widget->requisition.height = klass->knob_y;

}

/****************************************************************
 ** redraw when value changed
 */

static gboolean gtk_knob_value_changed(gpointer obj)
{
	GtkWidget *widget = (GtkWidget *)obj;
	gtk_widget_queue_draw(widget);
	return FALSE;
}

/****************************************************************
 ** create small knob
 */

GtkWidget *GtkKnob::gtk_knob_new_with_adjustment(GtkAdjustment *_adjustment)
{
	GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_KNOB, NULL ));
	GtkKnob *knob = GTK_KNOB(widget);
	knob->last_quadrant = 0;
	if (widget) {
		gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
		g_signal_connect(GTK_OBJECT(widget), "value-changed",
		                 G_CALLBACK(gtk_knob_value_changed), widget);
	}
	return widget;
}

/****************************************************************
 ** get the Knob type
 */

GType gtk_knob_get_type (void)
{
	static GType kn_type = 0;
	if (!kn_type) {
		static const GTypeInfo kn_info = {
			sizeof(GtkKnobClass), NULL,  NULL, (GClassInitFunc)gtk_knob_class_init, NULL, NULL, sizeof (GtkKnob), 0, (GInstanceInitFunc)gtk_knob_init
		};
		kn_type = g_type_register_static(GTK_TYPE_RANGE,  "GtkKnob", &kn_info, (GTypeFlags)0);
	}
	return kn_type;
}
}/* end of gtk_knob namespace */

gtk_knob::GtkKnob myGtkKnob;


/**
 * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
 * (but not those in the middle of the string)
 */
static string rmWhiteSpaces(const string& s)
{
    size_t i = s.find_first_not_of(" \t");
    size_t j = s.find_last_not_of(" \t");

    if (i != string::npos & j != string::npos) {
        return s.substr(i, 1+j-i);
    } else {
        return "";
    }
}


/**
 * Extracts metdata from a label : 'vol [unit: dB]' -> 'vol' + metadata
 */
static void extractMetadata(const string& fulllabel, string& label, map<string, string>& metadata)
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
                                    metadata[rmWhiteSpaces(key)] = "";
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
                                    metadata[rmWhiteSpaces(key)]=rmWhiteSpaces(value);
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


class GTKUI : public UI
{
 private :
    static bool                         fInitialized;
    static list<UI*>                    fGuiList;
    static map<FAUSTFLOAT*, FAUSTFLOAT>      fGuiSize;       // map widget zone with widget size coef
    static map<FAUSTFLOAT*, string>          fTooltip;       // map widget zone with tooltip strings
    static set<FAUSTFLOAT*>                  fKnobSet;       // set of widget zone to be knobs

    bool isKnob(float* zone){return fKnobSet.count(zone) > 0;}

 protected :
    GtkWidget*  fWindow;
    int         fTop;
    GtkWidget*  fBox[stackSize];
    int         fMode[stackSize];
    bool        fStopped;

    GtkWidget* addWidget(const char* label, GtkWidget* w);
    virtual void pushBox(int mode, GtkWidget* w);


 public :

    static const gboolean expand = TRUE;
    static const gboolean fill = TRUE;
    static const gboolean homogene = FALSE;

    GTKUI(char * name, int* pargc, char*** pargv);

    // -- Labels and metadata

    virtual void declare (FAUSTFLOAT* zone, const char* key, const char* value);
    virtual int  checkLabelOptions (GtkWidget* widget, const string& fullLabel, string& simplifiedLabel);
    virtual void checkForTooltip (FAUSTFLOAT* zone, GtkWidget* widget);

    // -- layout groups

    virtual void openFrameBox(const char* label);
    virtual void openTabBox(const char* label = "");
    virtual void openHorizontalBox(const char* label = "");
    virtual void openVerticalBox(const char* label = "");

    // -- extra widget's layouts

    virtual void openDialogBox(const char* label, FAUSTFLOAT* zone);
    virtual void openEventBox(const char* label = "");
    virtual void openHandleBox(const char* label = "");
    virtual void openExpanderBox(const char* label, FAUSTFLOAT* zone);

    virtual void closeBox();
    virtual void adjustStack(int n);

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone);
    virtual void addToggleButton(const char* label, FAUSTFLOAT* zone);
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone);
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
    virtual void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

    // -- passive display widgets

    virtual void addNumDisplay(const char* label, FAUSTFLOAT* zone, int precision);
    virtual void addTextDisplay(const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max);
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

    virtual void show();
    virtual void run();

};

/******************************************************************************
*******************************************************************************

                                GRAPHIC USER INTERFACE (v2)
                                  gtk implementation

*******************************************************************************
*******************************************************************************/

// global static fields

list<UI*>                   UI::fGuiList;

bool                             GTKUI::fInitialized = false;
map<FAUSTFLOAT*, FAUSTFLOAT>     GTKUI::fGuiSize;
map<FAUSTFLOAT*, string>         GTKUI::fTooltip;
set<FAUSTFLOAT*>                 GTKUI::fKnobSet;       // set of widget zone to be knobs


/**
* Format tooltip string by replacing some white spaces by
* return characters so that line width doesn't exceed n.
* Limitation : long words exceeding n are not cut
*/
static string formatTooltip(int n, const string& tt)
{
	string  ss = tt;	// ss string we are going to format
	int		lws = 0;	// last white space encountered
	int 	lri = 0;	// last return inserted
	for (int i=0; i<tt.size(); i++) {
		if (tt[i] == ' ') lws = i;
		if (((i-lri) >= n) && (lws > lri)) {
			// insert return here
			ss[lws] = '\n';
			lri = lws;
		}
	}
	cout << ss;
	return ss;
}

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
    fMode[fTop]     = mode;
    fBox[fTop]      = w;
}

/**
 * Remove n levels from the stack S before the top level
 * adjustStack(n): S -> S' with S' = S(0),S(n+1),S(n+2),...
 */
void GTKUI::adjustStack(int n)
{
    if (n > 0) {
        assert(fTop >= n);

        fTop -= n;
        fMode[fTop] = fMode[fTop+n];
        fBox[fTop]  = fBox[fTop+n];
    }
}

void GTKUI::closeBox()
{
    --fTop;
    assert(fTop >= 0);
}

/**
 * Analyses the widget zone metadata declarations and takes
 * appropriate actions
 */
void GTKUI::declare(FAUSTFLOAT* zone, const char* key, const char* value)
{
    if (strcmp(key,"size")==0) {
        fGuiSize[zone]=atof(value);
    }
    else if (strcmp(key,"tooltip")==0) {
        fTooltip[zone] = formatTooltip(30,value) ;
    }
     else if (strcmp(key,"style")==0) {
		if (strcmp(value,"knob") == 0) {
			fKnobSet.insert(zone);
		}
    }

}

/**
 * Analyses a full label and activates the relevant options. returns a simplified
 * label (without options) and an amount of stack adjustement (in case additional
 * containers were pushed on the stack).
 */

int GTKUI::checkLabelOptions(GtkWidget* widget, const string& fullLabel, string& simplifiedLabel)
{
    map<string, string> metadata;
    extractMetadata(fullLabel, simplifiedLabel, metadata);

    if (metadata.count("tooltip")) {
        gtk_tooltips_set_tip (gtk_tooltips_new (), widget, metadata["tooltip"].c_str(), NULL);
    }
    if (metadata["option"] == "detachable") {
        openHandleBox(simplifiedLabel.c_str());
        return 1;
    }

    // no adjustement of the stack needed
    return 0;
}

/**
 * Check if a tooltip is associated to a zone and add it to the corresponding widget
 */
void GTKUI::checkForTooltip(FAUSTFLOAT* zone, GtkWidget* widget)
{
    if (fTooltip.count(zone)) {
        gtk_tooltips_set_tip (gtk_tooltips_new (), widget, fTooltip[zone].c_str(), NULL);
    }
}

// les differentes boites

void GTKUI::openFrameBox(const char* label)
{
    GtkWidget * box = gtk_frame_new (label);
    //gtk_container_set_border_width (GTK_CONTAINER (box), 10);

    pushBox(kSingleMode, addWidget(label, box));
}

void GTKUI::openTabBox(const char* fullLabel)
{
    string  label;
    GtkWidget* widget = gtk_notebook_new();

    int     adjust = checkLabelOptions(widget, fullLabel, label);

    pushBox(kTabMode, addWidget(label.c_str(), widget));

    // adjust stack because otherwise Handlebox will remain open
    adjustStack(adjust);
}

void GTKUI::openHorizontalBox(const char* fullLabel)
{
    string   label;
    GtkWidget* box = gtk_hbox_new (homogene, 4);
    int     adjust = checkLabelOptions(box, fullLabel, label);

    gtk_container_set_border_width (GTK_CONTAINER (box), 10);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget * frame = addWidget(label.c_str(), gtk_frame_new (label.c_str()));
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label.c_str(), box));
    }

    // adjust stack because otherwise Handlebox will remain open
    adjustStack(adjust);
}

void GTKUI::openVerticalBox(const char* fullLabel)
{
    string  label;
    GtkWidget * box = gtk_vbox_new (homogene, 4);
    int      adjust = checkLabelOptions(box, fullLabel, label);

    gtk_container_set_border_width (GTK_CONTAINER (box), 10);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget * frame = addWidget(label.c_str(), gtk_frame_new (label.c_str()));
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label.c_str(), box));
    }

    // adjust stack because otherwise Handlebox will remain open
    adjustStack(adjust);
}

void GTKUI::openHandleBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_handle_box_new ());
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openEventBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_event_box_new ());
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

struct uiExpanderBox : public uiItem
{
    GtkExpander* fButton;
    uiExpanderBox(UI* ui, FAUSTFLOAT* zone, GtkExpander* b) : uiItem(ui, zone), fButton(b) {}
    static void expanded (GtkWidget *widget, gpointer data)
    {
        FAUSTFLOAT   v = gtk_expander_get_expanded  (GTK_EXPANDER(widget));
        if (v == 1.000000)
        {
            v = 0;
        }
        else v = 1;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT   v = *fZone;
        fCache = v;
        gtk_expander_set_expanded(GTK_EXPANDER(fButton), v);
    }
};

void GTKUI::openExpanderBox(const char* label, FAUSTFLOAT* zone)
{
    *zone = 0.0;
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_expander_new (label));
        gtk_container_add (GTK_CONTAINER(frame), box);
        uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
        gtk_signal_connect (GTK_OBJECT (frame), "activate", GTK_SIGNAL_FUNC (uiExpanderBox::expanded), (gpointer)c);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

GtkWidget* GTKUI::addWidget(const char* label, GtkWidget* w)
{
    switch (fMode[fTop]) {
        case kSingleMode    : gtk_container_add (GTK_CONTAINER(fBox[fTop]), w);                             break;
        case kBoxMode       : gtk_box_pack_start (GTK_BOX(fBox[fTop]), w, expand, fill, 0);                 break;
        case kTabMode       : gtk_notebook_append_page (GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label)); break;
    }
    gtk_widget_show (w);
    return w;
}

// --------------------------- Press button ---------------------------

struct uiButton : public uiItem
{
    GtkButton*  fButton;

    uiButton (UI* ui, FAUSTFLOAT* zone, GtkButton* b) : uiItem(ui, zone), fButton(b) {}

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
        FAUSTFLOAT   v = *fZone;
        fCache = v;
        if (v > 0.0) gtk_button_pressed(fButton); else gtk_button_released(fButton);
    }
};

void GTKUI::addButton(const char* label, FAUSTFLOAT* zone)
{
    *zone = 0.0;
    GtkWidget*  button = gtk_button_new_with_label (label);
    addWidget(label, button);

    uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));

    gtk_signal_connect (GTK_OBJECT (button), "pressed", GTK_SIGNAL_FUNC (uiButton::pressed), (gpointer) c);
    gtk_signal_connect (GTK_OBJECT (button), "released", GTK_SIGNAL_FUNC (uiButton::released), (gpointer) c);

    checkForTooltip(zone, button);
}

// ---------------------------  Toggle Buttons ---------------------------

struct uiToggleButton : public uiItem
{
    GtkToggleButton* fButton;

    uiToggleButton(UI* ui, FAUSTFLOAT* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}

    static void toggled (GtkWidget *widget, gpointer data)
    {
        FAUSTFLOAT   v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT   v = *fZone;
        fCache = v;
        gtk_toggle_button_set_active(fButton, v > 0.0);
    }
};

void GTKUI::addToggleButton(const char* label, FAUSTFLOAT* zone)
{
    *zone = 0.0;
    GtkWidget*  button = gtk_toggle_button_new_with_label (label);
    addWidget(label, button);

    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);

    checkForTooltip(zone, button);
}

void show_dialog(GtkWidget *widget, gpointer data)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(widget)) == TRUE)
    {
        gtk_widget_show(GTK_WIDGET(data));
        gint root_x, root_y;
        gtk_window_get_position (GTK_WINDOW(data), &root_x, &root_y);
        root_y -= 120;
        gtk_window_move(GTK_WINDOW(data), root_x, root_y);
    }
    else gtk_widget_hide(GTK_WIDGET(data));
}

static gboolean deleteevent( GtkWidget *widget, gpointer   data )
{
    return TRUE;
}

void GTKUI::openDialogBox(const char* label, FAUSTFLOAT* zone)
{
    // create toplevel window and set properties
    GtkWidget * dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_deletable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
    gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
    gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
    gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
    gtk_window_set_title (GTK_WINDOW (dialog), label);
    g_signal_connect (G_OBJECT (dialog), "delete_event", G_CALLBACK (deleteevent), NULL);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);

    GtkWidget * box = gtk_hbox_new (homogene, 4);

    *zone = 0.0;
    GtkWidget*  button = gtk_toggle_button_new ();
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (show_dialog), (gpointer) dialog);

    gtk_container_add (GTK_CONTAINER(fBox[fTop]), button);
    gtk_container_add (GTK_CONTAINER(dialog), box);
    gtk_widget_show (button);
    gtk_widget_show(box);
    pushBox(kBoxMode, box);
}

// ---------------------------  Check Button ---------------------------

struct uiCheckButton : public uiItem
{
    GtkToggleButton* fButton;

    uiCheckButton(UI* ui, FAUSTFLOAT* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}

    static void toggled (GtkWidget *widget, gpointer data)
    {
        FAUSTFLOAT   v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT   v = *fZone;
        fCache = v;
        gtk_toggle_button_set_active(fButton, v > 0.0);
    }
};

void GTKUI::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
    *zone = 0.0;
    GtkWidget*  button = gtk_check_button_new_with_label (label);
    addWidget(label, button);

    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC(uiCheckButton::toggled), (gpointer) c);

    checkForTooltip(zone, button);
}

// ---------------------------  Adjustmenty based widgets ---------------------------

struct uiAdjustment : public uiItem
{
    GtkAdjustment* fAdj;

    uiAdjustment(UI* ui, FAUSTFLOAT* zone, GtkAdjustment* adj) : uiItem(ui, zone), fAdj(adj) {}

    static void changed (GtkWidget *widget, gpointer data)
    {
        FAUSTFLOAT   v = GTK_ADJUSTMENT (widget)->value;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT   v = *fZone;
        fCache = v;
        gtk_adjustment_set_value(fAdj, v);
    }
};

// --------------------------- format knob value display ---------------------------

struct uiValueDisplay : public uiItem
{
	GtkLabel* fLabel;
	int	fPrecision ;

	uiValueDisplay(UI* ui, float* zone, GtkLabel* label, int precision)
		: uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

	virtual void reflectZone()
		{
			float v = *fZone;
			fCache = v;
			char s[64];
			if (fPrecision <= 0)
				snprintf(s, 63, "%d", int(v));

			else if (fPrecision > 3)
				snprintf(s, 63, "%f", v);

			else if (fPrecision == 1)
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[1-1], v);
			}
			else if (fPrecision == 2)
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[2-1], v);
			}
			else
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[3-1], v);
			}
			gtk_label_set_text(fLabel, s);
		}
};

// ------------------------------- Knob -----------------------------------------

void GTKUI::addKnob(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);

	GtkWidget* slider = gtk_vbox_new (FALSE, 0);
	GtkWidget* fil = gtk_vbox_new (FALSE, 0);
	GtkWidget* rei = gtk_vbox_new (FALSE, 0);
	GtkWidget* re =myGtkKnob.gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(adj));
	GtkWidget* lw = gtk_label_new("");
	new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
	gtk_container_add (GTK_CONTAINER(rei), re);
	if(fGuiSize[zone]) {
		float size = 30 * fGuiSize[zone];
		gtk_widget_set_size_request(rei, size, size );
		gtk_box_pack_start (GTK_BOX(slider), fil, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX(slider), rei, FALSE, FALSE, 0);
	} else {
		gtk_container_add (GTK_CONTAINER(slider), fil);
		gtk_container_add (GTK_CONTAINER(slider), rei);
	}
	gtk_container_add (GTK_CONTAINER(slider), lw);
	gtk_widget_show_all(slider);

	if (label && label[0]!=0) {
        openFrameBox(label);
        addWidget(label, slider);
        closeBox();
    } else {
        addWidget(label, slider);
    }

    checkForTooltip(zone, slider);
}

// -------------------------- Vertical Slider -----------------------------------

void GTKUI::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    if (isKnob(zone)) {
		addKnob(label, zone, init, min, max, step);
		return;
	}
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);

    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);

	GtkWidget* slider = gtk_vscale_new (GTK_ADJUSTMENT(adj));
	gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
	FAUSTFLOAT size = 160;
	if(fGuiSize[zone]) {
		size = 160 * fGuiSize[zone];
	}
	gtk_widget_set_size_request(slider, -1, size);

    gtk_range_set_inverted (GTK_RANGE(slider), TRUE);

    if (label && label[0]!=0) {
        openFrameBox(label);
        addWidget(label, slider);
        closeBox();
    } else {
        addWidget(label, slider);
    }

    checkForTooltip(zone, slider);
}

// -------------------------- Horizontal Slider -----------------------------------

void GTKUI::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    if (isKnob(zone)) {
		addKnob(label, zone, init, min, max, step);
		return;
	}
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);

    GtkWidget* slider = gtk_hscale_new (GTK_ADJUSTMENT(adj));
	gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
	FAUSTFLOAT size = 160;
	if(fGuiSize[zone]) {
		size = 160 * fGuiSize[zone];
	}
	gtk_widget_set_size_request(slider, size, -1);


    if (label && label[0]!=0) {
        openFrameBox(label);
        addWidget(label, slider);
        closeBox();
    } else {
        addWidget(label, slider);
    }

    checkForTooltip(zone, slider);
}

// ------------------------------ Num Entry -----------------------------------

void GTKUI::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    if (isKnob(zone)) {
		addKnob(label, zone, init, min, max, step);
		return;
	}
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, step);

    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);

    GtkWidget* spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), 0.005, precision(step));

    openFrameBox(label);
    addWidget(label, spinner);
    closeBox();

    checkForTooltip(zone, spinner);
}

// ==========================   passive widgets ===============================

// ------------------------------ Progress Bar -----------------------------------

struct uiBargraph : public uiItem
{
    GtkProgressBar*     fProgressBar;
    FAUSTFLOAT               fMin;
    FAUSTFLOAT               fMax;

    uiBargraph(UI* ui, FAUSTFLOAT* zone, GtkProgressBar* pbar, FAUSTFLOAT lo, FAUSTFLOAT hi)
            : uiItem(ui, zone), fProgressBar(pbar), fMin(lo), fMax(hi) {}

    FAUSTFLOAT scale(FAUSTFLOAT v)        { return (v-fMin)/(fMax-fMin); }

    virtual void reflectZone()
    {
        FAUSTFLOAT   v = *fZone;
        fCache = v;
        gtk_progress_bar_set_fraction(fProgressBar, scale(v));
    }
};



void GTKUI::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_BOTTOM_TO_TOP);
    gtk_widget_set_size_request(pb, 8, -1);
    new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
    openFrameBox(label);
    addWidget(label, pb);
    closeBox();

    checkForTooltip(zone, pb);
}


void GTKUI::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_LEFT_TO_RIGHT);
    gtk_widget_set_size_request(pb, -1, 8);
    new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
    openFrameBox(label);
    addWidget(label, pb);
    closeBox();

    checkForTooltip(zone, pb);
}


// ------------------------------ Num Display -----------------------------------

struct uiNumDisplay : public uiItem
{
    GtkLabel* fLabel;
    int fPrecision;

    uiNumDisplay(UI* ui, FAUSTFLOAT* zone, GtkLabel* label, int precision)
            : uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

    virtual void reflectZone()
    {
        FAUSTFLOAT   v = *fZone;
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

void GTKUI::addNumDisplay(const char* label, FAUSTFLOAT* zone, int precision )
{
    GtkWidget* lw = gtk_label_new("");
    new uiNumDisplay(this, zone, GTK_LABEL(lw), precision);
    openFrameBox(label);
    addWidget(label, lw);
    closeBox();

    checkForTooltip(zone, lw);
}

// ------------------------------ Text Display -----------------------------------

struct uiTextDisplay : public uiItem
{
    GtkLabel*       fLabel;
    const char**    fNames;
    FAUSTFLOAT           fMin;
    FAUSTFLOAT           fMax;
    int             fNum;

    uiTextDisplay (UI* ui, FAUSTFLOAT* zone, GtkLabel* label, const char* names[], FAUSTFLOAT lo, FAUSTFLOAT hi)
                    : uiItem(ui, zone), fLabel(label), fNames(names), fMin(lo), fMax(hi)
    {
        fNum = 0;
        while (fNames[fNum] != 0) fNum++;
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT   v = *fZone;
        fCache = v;

        int idx = int(fNum*(v-fMin)/(fMax-fMin));

        if      (idx < 0)       idx = 0;
        else if (idx >= fNum)   idx = fNum-1;

        gtk_label_set_text(fLabel, fNames[idx]);
    }
};

void GTKUI::addTextDisplay(const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT lo, FAUSTFLOAT hi)
{
    GtkWidget* lw = gtk_label_new("");
    new uiTextDisplay (this, zone, GTK_LABEL(lw), names, lo, hi);
    openFrameBox(label);
    addWidget(label, lw);
    closeBox();

    checkForTooltip(zone, lw);
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

/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------
//  Definition of an abstract signal processor
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
 	virtual void compute(int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 	= 0;
};

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------


#ifdef __cplusplus
extern "C" {
#endif

// -- layout groups

typedef void (* openFrameBoxFun) (void* interface, const char* label);
typedef void (* openTabBoxFun) (void* interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* interface, const char* label);
typedef void (* openVerticalBoxFun) (void* interface, const char* label);
typedef void (*closeBoxFun) (void* interface);

// -- active widgets

typedef void (* addButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addToggleButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive display widgets

typedef void (* addNumDisplayFun) (void* interface, const char* label, FAUSTFLOAT* zone, int precision);
typedef void (* addTextDisplayFun) (void* interface, const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addHorizontalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

typedef void (* declareFun) (void* interface, FAUSTFLOAT* zone, const char* key, const char* value);

struct UIGlue {

    void* uiInterface;

    openFrameBoxFun openFrameBox;
    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addToggleButtonFun addToggleButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addNumDisplayFun addNumDisplay;
    addTextDisplayFun addTextDisplay;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    declareFun declare;

};

typedef struct llvm_dsp {};

llvm_dsp* new_mydsp();
void delete_mydsp(llvm_dsp*);

int getNumInputs_mydsp(llvm_dsp*);
int getNumOutputs_mydsp(llvm_dsp*);

void init_mydsp(llvm_dsp*, int);
void classInit_mydsp(int);
void instanceInit_mydsp(llvm_dsp*, int);
void buildUserInterface_mydsp(llvm_dsp*, UIGlue*);

void compute_mydsp(llvm_dsp*, int, FAUSTFLOAT**, FAUSTFLOAT**);

void openFrameBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openFrameBox(label);
}

void openTabBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openTabBox(label);
}

void openHorizontalBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openHorizontalBox(label);
}

void openVerticalBoxGlue(void* cpp_interface, const char* label)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->openVerticalBox(label);
}

void closeBoxGlue(void* cpp_interface)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->closeBox();
}

void addButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addButton(label, zone);
}

void addToggleButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addToggleButton(label, zone);
}

void addCheckButtonGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addCheckButton(label, zone);
}

void addVerticalSliderGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addVerticalSlider(label, zone, init, min, max, step);
}

void addHorizontalSliderGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addHorizontalSlider(label, zone, init, min, max, step);
}

void addNumEntryGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addNumEntry(label, zone, init, min, max, step);
}

void addNumDisplayGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, int precision)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addNumDisplay(label, zone, precision);
}

void addTextDisplayGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addTextDisplay(label, zone, names, min, max);
}

void addHorizontalBargraphGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addHorizontalBargraph(label, zone, min, max);
}

void addVerticalBargraphGlue(void* cpp_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->addVerticalBargraph(label, zone, min, max);
}

void declareGlue(void* cpp_interface, FAUSTFLOAT* zone, const char* key, const char* value)
{
    UI* interface = static_cast<UI*>(cpp_interface);
    interface->declare(zone, key, value);
}

#ifdef __cplusplus
}
#endif


class llvmdsp : public dsp {

  private:

	llvm_dsp* fDsp;

  public:

	llvmdsp()
	{
        fDsp = new_mydsp();
    }

	virtual ~llvmdsp()
	{
		delete_mydsp(fDsp);
	}

	virtual int getNumInputs() 	{ return getNumInputs_mydsp(fDsp); }
	virtual int getNumOutputs() { return getNumOutputs_mydsp(fDsp); }

	static void classInit(int samplingFreq)
    {
        classInit_mydsp(samplingFreq);
    }

	virtual void instanceInit(int samplingFreq)
    {
		instanceInit_mydsp(fDsp, samplingFreq);
	}

	virtual void init(int samplingFreq) {
		init_mydsp(fDsp, samplingFreq);
	}

	virtual void buildUserInterface(UI* interface)
    {
        UIGlue glue;
        glue.uiInterface = interface;
        glue.openFrameBox = openFrameBoxGlue;
        glue.openTabBox = openTabBoxGlue;
        glue.openHorizontalBox = openHorizontalBoxGlue;
        glue.openVerticalBox = openVerticalBoxGlue;
        glue.closeBox = closeBoxGlue;
        glue.addButton = addButtonGlue;
        glue.addToggleButton = addToggleButtonGlue;
        glue.addCheckButton = addCheckButtonGlue;
        glue.addVerticalSlider = addVerticalSliderGlue;
        glue.addHorizontalSlider = addHorizontalSliderGlue;
        glue.addNumEntry = addNumEntryGlue;
        glue.addNumDisplay = addNumDisplayGlue;
        glue.addTextDisplay = addTextDisplayGlue;
        glue.addHorizontalBargraph = addHorizontalBargraphGlue;
        glue.addVerticalBargraph = addVerticalBargraphGlue;
        glue.declare = declareGlue;
        buildUserInterface_mydsp(fDsp, &glue);
 	}

	virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
    {
		compute_mydsp(fDsp, count, input, output);
	}
};

llvmdsp* DSP;

/******************************************************************************
*******************************************************************************

							JACK AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
// 	number of input and output channels
//----------------------------------------------------------------------------

int		gNumInChans;
int		gNumOutChans;

//----------------------------------------------------------------------------
// Jack ports
//----------------------------------------------------------------------------

jack_port_t *input_ports[256];
jack_port_t *output_ports[256];

//----------------------------------------------------------------------------
// tables of noninterleaved input and output channels for FAUST
//----------------------------------------------------------------------------

float* 	gInChannel[256];
float* 	gOutChannel[256];

#ifdef IS_DOUBLE
double* gInDoubleChannel[256];
double* gOutDoubleChannel[256];
#endif

//----------------------------------------------------------------------------
// Jack Callbacks
//----------------------------------------------------------------------------

int srate(jack_nframes_t nframes, void *arg)
{
	printf("the sample rate is now %u/sec\n", nframes);
	return 0;
}

void jack_shutdown(void *arg)
{
	exit(1);
}

int process (jack_nframes_t nframes, void *arg)
{
    AVOIDDENORMALS;

	for (int i = 0; i < gNumInChans; i++) {
	    gInChannel[i] = (float *)jack_port_get_buffer(input_ports[i], nframes);
	}
	for (int i = 0; i < gNumOutChans; i++) {
	    gOutChannel[i] = (float *)jack_port_get_buffer(output_ports[i], nframes);
	}

    #ifdef IS_DOUBLE
        // Copy float to double
        for (int chan = 0; chan < gNumInChans; chan++) {
            for (int frames = 0; frames < nframes; frames++) {
                gInDoubleChannel[chan][frames] = double(gInChannel[chan][frames]);
            }
        }

        // Compute
        DSP->compute(nframes, (FAUSTFLOAT**)gInDoubleChannel, (FAUSTFLOAT**)gOutDoubleChannel);

        // Copy double to float
        for (int chan = 0; chan < gNumOutChans; chan++) {
            for (int frames = 0; frames < nframes; frames++) {
                gOutChannel[chan][frames] = float(gOutDoubleChannel[chan][frames]);
            }
        }
    #else
        DSP->compute(nframes, gInChannel, gOutChannel);
    #endif

	return 0;
}


/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/


//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

int main(int argc, char *argv[] )
{
	UI* 				interface;
	jack_client_t*		client;
    char                buf [256];
	char				rcfilename[256];
    jack_status_t       jackstat;
	const char*         home;
    char*               pname;
    char*               jname;

    jname = basename (argv [0]);
    client = jack_client_open (jname, (jack_options_t) 0, &jackstat);
    if (client == 0) {
        fprintf (stderr, "Can't connect to JACK, is the server running ?\n");
        exit(1);
    }
    if (jackstat & JackNameNotUnique) {
        jname = jack_get_client_name (client);
    }

	jack_set_process_callback(client, process, 0);
	jack_set_sample_rate_callback(client, srate, 0);
	jack_on_shutdown(client, jack_shutdown, 0);

    DSP = new llvmdsp();

	gNumInChans = DSP->getNumInputs();
	gNumOutChans = DSP->getNumOutputs();

	for (int i = 0; i < gNumInChans; i++) {
	    char buf[256];
	    snprintf(buf, 256, "in_%d", i);
	    input_ports[i] = jack_port_register(client, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    #ifdef IS_DOUBLE
        gInDoubleChannel[i] = (double*)malloc(sizeof(double) * jack_get_buffer_size(client));
    #endif
 	}
	for (int i = 0; i < gNumOutChans; i++) {
	    char buf[256];
	    snprintf(buf, 256, "out_%d", i);
	    output_ports[i] = jack_port_register(client, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    #ifdef IS_DOUBLE
        gOutDoubleChannel[i] = (double*)malloc(sizeof(double) * jack_get_buffer_size(client));
    #endif
	}

	interface = new GTKUI(jname, &argc, &argv);
    DSP->init(jack_get_sample_rate(client));
    DSP->buildUserInterface(interface);

	home = getenv ("HOME");
    if (home == 0) home = ".";
    snprintf(rcfilename, 256, "%s/.%src", home, jname);
    interface->recallState(rcfilename);

    if (jack_activate(client)) {
        fprintf(stderr, "Can't activate JACK client\n");
        return 1;
    }

    pname = getenv("FAUST2JACK_INPUTS");
    if (pname && *pname) {
       for (int i = 0; i < gNumInChans; i++) {
            snprintf(buf, 256, pname, i + 1);
            jack_connect(client, buf, jack_port_name(input_ports[i]));
        }
    }

    pname = getenv("FAUST2JACK_OUTPUTS");
    if (pname && *pname) {
        for (int i = 0; i < gNumOutChans; i++) {
            snprintf(buf, 256, pname, i + 1);
            jack_connect(client, jack_port_name(output_ports[i]), buf);
        }
    }

	interface->run();
	jack_deactivate(client);

	for (int i = 0; i < gNumInChans; i++) {
	    jack_port_unregister(client, input_ports[i]);
	}
	for (int i = 0; i < gNumOutChans; i++) {
	    jack_port_unregister(client, output_ports[i]);
	}

	jack_client_close(client);
	interface->saveState(rcfilename);

	delete DSP;
  	return 0;
}

