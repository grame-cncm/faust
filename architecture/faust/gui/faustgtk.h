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

#ifndef FAUST_GTKUI_H
#define FAUST_GTKUI_H

#include "faust/gui/GUI.h"
#include "faust/gui/MetaDataUI.h"

/******************************************************************************
*******************************************************************************

                                GRAPHIC USER INTERFACE
                                  gtk interface

*******************************************************************************
*******************************************************************************/
#include <string>
#include <set>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <assert.h>

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
        GtkWidget* gtk_knob_new_with_adjustment(GtkAdjustment *_adjustment);
	
};

#define GTK_TYPE_KNOB          (gtk_knob_get_type())
#define GTK_KNOB(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_KNOB, GtkKnob))
#define GTK_IS_KNOB(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_KNOB))
#define GTK_KNOB_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GTK_TYPE_KNOB, GtkKnobClass))
#define GTK_IS_KNOB_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GTK_TYPE_KNOB))

GtkKnob::GtkKnob()
// GtkKnob constructor
{}

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

static void knob_expose(GtkWidget* widget, int knob_x, int knob_y, GdkEventExpose *event, int arc_offset)
{
	/** check resize **/
	int grow;
	if(widget->allocation.width > widget->allocation.height) {
		grow = widget->allocation.height;
	} else {
		grow = widget->allocation.width;
	}
	knob_x = grow-4;
	knob_y = grow-4;
	/** get values for the knob **/
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	int knobx = (widget->allocation.x+2 + (widget->allocation.width-4 - knob_x) * 0.5);
	int knoby = (widget->allocation.y+2 + (widget->allocation.height-4 - knob_y) * 0.5);
	int knobx1 = (widget->allocation.x+2 + (widget->allocation.width-4) * 0.5);
	int knoby1 = (widget->allocation.y+2 + (widget->allocation.height-4) * 0.5);
	double knobstate = (adj->value - adj->lower) / (adj->upper - adj->lower);
	double angle = scale_zero + knobstate * 2 * (M_PI - scale_zero);
	double knobstate1 = (0. - adj->lower) / (adj->upper - adj->lower);
	double pointer_off = knob_x/6;
	double radius = std::min<double>(knob_x-pointer_off, knob_y-pointer_off) / 2;
	double lengh_x = (knobx+radius+pointer_off/2) - radius * sin(angle);
	double lengh_y = (knoby+radius+pointer_off/2) + radius * cos(angle);
	double radius1 = std::min<double>(knob_x, knob_y) / 2;

	/** get widget forground color convert to cairo **/
	GtkStyle *style = gtk_widget_get_style (widget);
	double r = std::min<double>(0.6, style->fg[gtk_widget_get_state(widget)].red/65535.0),
		   g = std::min<double>(0.6, style->fg[gtk_widget_get_state(widget)].green/65535.0),
		   b = std::min<double>(0.6, style->fg[gtk_widget_get_state(widget)].blue/65535.0);

	/** paint focus **/
	if (GTK_WIDGET_HAS_FOCUS(widget)) {
		gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
		                knobx-2, knoby-2, knob_x+4, knob_y+4);
	}
	/** create clowing knobs with cairo **/
	cairo_t *cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	GdkRegion *region;
	region = gdk_region_rectangle(&widget->allocation);
	gdk_region_intersect(region, event->region);
	gdk_cairo_region(cr, region);
	cairo_clip(cr);
	
	cairo_arc(cr,knobx1+arc_offset, knoby1+arc_offset, knob_x/2.1, 0, 2 * M_PI );
	cairo_pattern_t*pat =
		cairo_pattern_create_radial (knobx1+arc_offset-knob_x/6,knoby1+arc_offset-knob_x/6, 1,knobx1+arc_offset,knoby1+arc_offset,knob_x/2.1 );
	if (adj->lower<0 && adj->value>0.) {
		cairo_pattern_add_color_stop_rgb(pat, 0, r+0.4, g+0.4 + knobstate-knobstate1, b+0.4);
		cairo_pattern_add_color_stop_rgb(pat, 0.7, r+0.15, g+0.15 + (knobstate-knobstate1)*0.5, b+0.15);
		cairo_pattern_add_color_stop_rgb(pat, 1, r, g, b);
	} else if(adj->lower<0 && adj->value<=0.) {
		cairo_pattern_add_color_stop_rgb(pat, 0, r+0.4 +knobstate1- knobstate, g+0.4, b+0.4);
		cairo_pattern_add_color_stop_rgb(pat, 0.7, r+0.15 +(knobstate1- knobstate)*0.5, g+0.15, b+0.15);
		cairo_pattern_add_color_stop_rgb(pat, 1, r, g, b);
	} else {
		cairo_pattern_add_color_stop_rgb(pat, 0, r+0.4, g+0.4 +knobstate, b+0.4);
		cairo_pattern_add_color_stop_rgb(pat, 0.7, r+0.15, g+0.15 + knobstate*0.5, b+0.15);
		cairo_pattern_add_color_stop_rgb(pat, 1, r, g, b);
	}
	cairo_set_source(cr, pat);
	cairo_fill_preserve(cr);
	gdk_cairo_set_source_color(cr, gtk_widget_get_style (widget)->fg);
	cairo_set_line_width(cr, 2.0);
	cairo_stroke(cr);

	/** create a rotating pointer on the kob**/
	cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
	cairo_set_line_width(cr, std::max<double>(3, std::min<double>(7, knob_x/15)));
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND); 
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
	cairo_move_to(cr, knobx+radius1, knoby+radius1);
	cairo_line_to(cr, lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
	cairo_set_line_width(cr, std::min<double>(5, std::max<double>(1, knob_x/30)));
	cairo_move_to(cr, knobx+radius1, knoby+radius1);
	cairo_line_to(cr,lengh_x, lengh_y);
	cairo_stroke(cr);
	cairo_pattern_destroy(pat);
	gdk_region_destroy (region);
	cairo_destroy(cr);
}

/****************************************************************
 ** general expose events for all "knob" controllers
 */

//----------- draw the Knob when moved
static gboolean gtk_knob_expose(GtkWidget* widget, GdkEventExpose *event)
{
	g_assert(GTK_IS_KNOB(widget));
	GtkKnobClass *klass = GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));
	knob_expose(widget, klass->knob_x, klass->knob_y, event, 0);
	return true;
}

/****************************************************************
 ** set initial size for GdkDrawable per type
 */

static void gtk_knob_size_request(GtkWidget* widget, GtkRequisition *requisition)
{
	g_assert(GTK_IS_KNOB(widget));
	GtkKnobClass *klass = GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));
	requisition->width = klass->knob_x;
	requisition->height = klass->knob_y;
}

/****************************************************************
 ** set value from key bindings
 */

static void gtk_knob_set_value(GtkWidget* widget, int dir_down)
{
	g_assert(GTK_IS_KNOB(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

	int oldstep = (int)(0.5f + (adj->value - adj->lower) / adj->step_increment);
	int step;
	int nsteps = (int)(0.5f + (adj->upper - adj->lower) / adj->step_increment);
	if (dir_down) {
		step = oldstep - 1;
	} else {
		step = oldstep + 1;
    }
	FAUSTFLOAT value = adj->lower + step * double(adj->upper - adj->lower) / nsteps;
	gtk_widget_grab_focus(widget);
	gtk_range_set_value(GTK_RANGE(widget), value);
}

/****************************************************************
 ** keyboard bindings
 */

static gboolean gtk_knob_key_press(GtkWidget* widget, GdkEventKey *event)
{
	g_assert(GTK_IS_KNOB(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	switch (event->keyval) {
	case GDK_Home:
		gtk_range_set_value(GTK_RANGE(widget), adj->lower);
		return true;
	case GDK_End:
		gtk_range_set_value(GTK_RANGE(widget), adj->upper);
		return true;
	case GDK_Up:
		gtk_knob_set_value(widget, 0);
		return true;
	case GDK_Right:
		gtk_knob_set_value(widget, 0);
		return true;
	case GDK_Down:
		gtk_knob_set_value(widget, 1);
		return true;
	case GDK_Left:
		gtk_knob_set_value(widget, 1);
		return true;
	}

	return false;
}

/****************************************************************
 ** alternative (radial) knob motion mode (ctrl + mouse pressed)
 */

static void knob_pointer_event(GtkWidget* widget, gdouble x, gdouble y, int knob_x, int knob_y,
                               bool drag, int state)
{
	static double last_y = 2e20;
	GtkKnob *knob = GTK_KNOB(widget);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	double radius = std::min<double>(knob_x, knob_y) / 2;
	int knobx = (widget->allocation.width - knob_x) / 2;
	int knoby = (widget->allocation.height - knob_y) / 2;
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

static gboolean gtk_knob_button_press(GtkWidget* widget, GdkEventButton *event)
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
	return true;
}

/****************************************************************
 ** mouse button release
 */

static gboolean gtk_knob_button_release(GtkWidget* widget, GdkEventButton *event)
{
	g_assert(GTK_IS_KNOB(widget));
	GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget))->button_is = 0;
	if (GTK_WIDGET_HAS_GRAB(widget))
		gtk_grab_remove(widget);
	return false;
}

/****************************************************************
 ** set the value from mouse movement
 */

static gboolean gtk_knob_pointer_motion(GtkWidget* widget, GdkEventMotion *event)
{
	g_assert(GTK_IS_KNOB(widget));
	GtkKnobClass *klass = GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));
	
	gdk_event_request_motions(event);
	
	if (GTK_WIDGET_HAS_GRAB(widget)) {
		knob_pointer_event(widget, event->x, event->y, klass->knob_x, klass->knob_y,
						   true, event->state);
	}
	return false;
}

/****************************************************************
 ** set value from mouseweel
 */

static gboolean gtk_knob_scroll(GtkWidget* widget, GdkEventScroll *event)
{
	usleep(5000);
	gtk_knob_set_value(widget, event->direction);
	return false;
}

/****************************************************************
 ** init the GtkKnobClass
 */

static void gtk_knob_class_init(GtkKnobClass *klass)
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

static void gtk_knob_init(GtkKnob *knob)
{
	GtkWidget* widget = GTK_WIDGET(knob);
	GtkKnobClass *klass = GTK_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget));

	GTK_WIDGET_SET_FLAGS(GTK_WIDGET(knob), GTK_CAN_FOCUS);
	GTK_WIDGET_SET_FLAGS(GTK_WIDGET(knob), GTK_CAN_DEFAULT);

	widget->requisition.width = klass->knob_x;
	widget->requisition.height = klass->knob_y;
}

/****************************************************************
 ** redraw when value changed
 */

static gboolean gtk_knob_value_changed(gpointer obj)
{
	GtkWidget* widget = (GtkWidget* )obj;
	gtk_widget_queue_draw(widget);
	return false;
}

/****************************************************************
 ** create small knob
 */

GtkWidget* GtkKnob::gtk_knob_new_with_adjustment(GtkAdjustment *_adjustment)
{
	GtkWidget* widget = GTK_WIDGET(g_object_new (GTK_TYPE_KNOB, NULL));
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

GType gtk_knob_get_type(void)
{
	static GType kn_type = 0;
	if (!kn_type) {
		static const GTypeInfo kn_info = {
			sizeof(GtkKnobClass), NULL,  NULL, (GClassInitFunc)gtk_knob_class_init, NULL, NULL, sizeof(GtkKnob), 0, (GInstanceInitFunc)gtk_knob_init, NULL
		};
		kn_type = g_type_register_static(GTK_TYPE_RANGE,  "GtkKnob", &kn_info, (GTypeFlags)0);
	}
	return kn_type;
}
}/* end of gtk_knob namespace */

gtk_knob::GtkKnob myGtkKnob;


class GTKUI : public GUI, public MetaDataUI
{
    
private:
    
    static bool fInitialized;
    
protected:
    
    GtkWidget*  fWindow;
    int         fTop;
    GtkWidget*  fBox[stackSize];
    int         fMode[stackSize];
    bool        fStopped;

    GtkWidget* addWidget(const char* label, GtkWidget* w);
    virtual void pushBox(int mode, GtkWidget* w);
    
public:
    
    static const gboolean expand = true;
    static const gboolean fill = true;
    static const gboolean homogene = false;
         
    GTKUI(char * name, int* pargc, char*** pargv);

    // -- Labels and metadata

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value);
    virtual int  checkLabelOptions(GtkWidget* widget, const std::string& fullLabel, std::string& simplifiedLabel);
    virtual void checkForTooltip(FAUSTFLOAT* zone, GtkWidget* widget);
    
    // -- layout groups
    
    virtual void openTabBox(const char* label = "");
    virtual void openHorizontalBox(const char* label = "");
    virtual void openVerticalBox(const char* label = "");
    virtual void closeBox();

    // -- active widgets
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone);
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone);
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);   
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step); 
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

    // -- passive display widgets
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
    
    // -- layout groups - internal
    
    virtual void openFrameBox(const char* label);   
   
    // -- extra widget's layouts

    virtual void openDialogBox(const char* label, FAUSTFLOAT* zone);
    virtual void openEventBox(const char* label = "");
    virtual void openHandleBox(const char* label = "");
    virtual void openExpanderBox(const char* label, FAUSTFLOAT* zone);
    
    virtual void adjustStack(int n);
    
    // -- active widgets - internal
    virtual void addToggleButton(const char* label, FAUSTFLOAT* zone);
    virtual void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
    
    // -- passive display widgets - internal
    
    virtual void addNumDisplay(const char* label, FAUSTFLOAT* zone, int precision);
    virtual void addTextDisplay(const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min, FAUSTFLOAT max);
   
    virtual void show();
    virtual bool run();
    
};

/******************************************************************************
*******************************************************************************

                                GRAPHIC USER INTERFACE (v2)
                                  gtk implementation

*******************************************************************************
*******************************************************************************/

// global static fields
bool GTKUI::fInitialized = false;

static gint delete_event(GtkWidget* widget, GdkEvent *event, gpointer data)
{
    return FALSE; 
}

static void destroy_event(GtkWidget* widget, gpointer data)
{
    gtk_main_quit();
}

GTKUI::GTKUI(char * name, int* pargc, char*** pargv) 
{
    if (!fInitialized) {
        gtk_init(pargc, pargv);
        fInitialized = true;
    }
    
    fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    //gtk_container_set_border_width (GTK_CONTAINER (fWindow), 10);
    gtk_window_set_title(GTK_WINDOW (fWindow), name);
    gtk_signal_connect(GTK_OBJECT (fWindow), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
    gtk_signal_connect(GTK_OBJECT (fWindow), "destroy", GTK_SIGNAL_FUNC (destroy_event), NULL);

    fTop = 0;
    fBox[fTop] = gtk_vbox_new (homogene, 4);
    fMode[fTop] = kBoxMode;
    gtk_container_add(GTK_CONTAINER (fWindow), fBox[fTop]);
    fStopped = false;
}

// empilement des boites

void GTKUI::pushBox(int mode, GtkWidget* w)
{
    ++fTop;
    assert(fTop < stackSize);
    fMode[fTop] = mode;
    fBox[fTop] = w;
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
        fBox[fTop] = fBox[fTop+n];
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
    MetaDataUI::declare(zone, key, value);
}
    
/**
 * Analyses a full label and activates the relevant options. returns a simplified
 * label (without options) and an amount of stack adjustement (in case additional
 * containers were pushed on the stack). 
 */

int GTKUI::checkLabelOptions(GtkWidget* widget, const std::string& fullLabel, std::string& simplifiedLabel)
{   
    std::map<std::string, std::string> metadata;
    extractMetadata(fullLabel, simplifiedLabel, metadata);

    if (metadata.count("tooltip")) {
        gtk_tooltips_set_tip (gtk_tooltips_new (), widget, metadata["tooltip"].c_str(), NULL);
    }
    if (metadata["option"] == "detachable") {
        openHandleBox(simplifiedLabel.c_str());
        return 1;
    }

	//---------------------
	if (fGroupTooltip != "") {
		gtk_tooltips_set_tip (gtk_tooltips_new (), widget, fGroupTooltip.c_str(), NULL);
		fGroupTooltip = "";
	}
	
	//----------------------
    // no adjustement of the stack needed
    return 0;
}

/**
 * Check if a tooltip is associated to a zone and add it to the corresponding widget
 */
void GTKUI::checkForTooltip(FAUSTFLOAT* zone, GtkWidget* widget)
{
    if (fTooltip.count(zone)) {
        gtk_tooltips_set_tip(gtk_tooltips_new (), widget, fTooltip[zone].c_str(), NULL);
    }
}

// The different boxes

void GTKUI::openFrameBox(const char* label)
{
    GtkWidget* box = gtk_frame_new (label);
    //gtk_container_set_border_width (GTK_CONTAINER (box), 10);
            
    pushBox(kSingleMode, addWidget(label, box));
}

void GTKUI::openTabBox(const char* fullLabel)
{
    std::string label;
    GtkWidget* widget = gtk_notebook_new();

    int adjust = checkLabelOptions(widget, fullLabel, label);
    
    pushBox(kTabMode, addWidget(label.c_str(), widget));

    // adjust stack because otherwise Handlebox will remain open
    adjustStack(adjust);
}

void GTKUI::openHorizontalBox(const char* fullLabel)
{   
    std::string label;
    GtkWidget* box = gtk_hbox_new (homogene, 4);
    int adjust = checkLabelOptions(box, fullLabel, label);

    gtk_container_set_border_width (GTK_CONTAINER (box), 10);
    label = startWith(label, "0x") ? "" : label;
            
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label.c_str(), gtk_frame_new (label.c_str()));
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
    std::string label;
    GtkWidget* box = gtk_vbox_new (homogene, 4);
    int adjust = checkLabelOptions(box, fullLabel, label);

    gtk_container_set_border_width (GTK_CONTAINER (box), 10);
    label = startWith(label, "0x") ? "" : label;
            
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label.c_str(), gtk_frame_new (label.c_str()));
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
    GtkWidget* box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label, gtk_handle_box_new ());
        gtk_container_add(GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openEventBox(const char* label)
{
    GtkWidget* box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label, gtk_event_box_new ());
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

struct uiExpanderBox : public uiItem
{
    GtkExpander* fButton;
    uiExpanderBox(GUI* ui, FAUSTFLOAT* zone, GtkExpander* b) : uiItem(ui, zone), fButton(b) {}
    static void expanded (GtkWidget* widget, gpointer data)
    {
        FAUSTFLOAT v = gtk_expander_get_expanded  (GTK_EXPANDER(widget));
        if (v == 1.000000) {
            v = 0;
        } else {
            v = 1;
        }
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        gtk_expander_set_expanded(GTK_EXPANDER(fButton), v);
    }
};

void GTKUI::openExpanderBox(const char* label, FAUSTFLOAT* zone)
{
    *zone = 0.0;
    GtkWidget* box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label, gtk_expander_new (label));
        gtk_container_add (GTK_CONTAINER(frame), box);
        uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
        gtk_signal_connect (GTK_OBJECT (frame), "activate", GTK_SIGNAL_FUNC (uiExpanderBox::expanded), (gpointer)c);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
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
    
    uiButton(GUI* ui, FAUSTFLOAT* zone, GtkButton* b) : uiItem(ui, zone), fButton(b) {}
    
    static void pressed(GtkWidget* widget, gpointer data)
    {
        uiItem* c = (uiItem*) data;
        c->modifyZone(1.0);
    }

    static void released(GtkWidget* widget, gpointer data)
    {
        uiItem* c = (uiItem*) data;
        c->modifyZone(0.0);
    }

    virtual void reflectZone()  
    { 
        FAUSTFLOAT v = *fZone;
        fCache = v; 
        if (v > 0.0) gtk_button_pressed(fButton); else gtk_button_released(fButton);
    }
};

void GTKUI::addButton(const char* label, FAUSTFLOAT* zone)
{
    *zone = 0.0;
    GtkWidget* button = gtk_button_new_with_label (label);
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
    
    uiToggleButton(GUI* ui, FAUSTFLOAT* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}
    
    static void toggled(GtkWidget* widget, gpointer data)
    {
        FAUSTFLOAT v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0; 
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()  
    { 
        FAUSTFLOAT v = *fZone;
        fCache = v; 
        gtk_toggle_button_set_active(fButton, v > 0.0); 
    }
};

void GTKUI::addToggleButton(const char* label, FAUSTFLOAT* zone)
{
    *zone = 0.0;
    GtkWidget* button = gtk_toggle_button_new_with_label (label);
    addWidget(label, button);
    
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);

    checkForTooltip(zone, button);
}

void show_dialog(GtkWidget* widget, gpointer data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        gtk_widget_show(GTK_WIDGET(data));
        gint root_x, root_y;
        gtk_window_get_position(GTK_WINDOW(data), &root_x, &root_y);
        root_y -= 120;
        gtk_window_move(GTK_WINDOW(data), root_x, root_y);
    }
    else gtk_widget_hide(GTK_WIDGET(data));
}

static gboolean deleteevent(GtkWidget* widget, gpointer data)
{
    return true;
} 

void GTKUI::openDialogBox(const char* label, FAUSTFLOAT* zone)
{
    // create toplevel window and set properties
    GtkWidget* dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(dialog), true);
    gtk_window_set_deletable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
    gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
    gtk_window_set_keep_below(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_title(GTK_WINDOW (dialog), label);
    g_signal_connect(G_OBJECT (dialog), "delete_event", G_CALLBACK (deleteevent), NULL);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), true);

    GtkWidget* box = gtk_hbox_new (homogene, 4);
 
    *zone = 0.0;
    GtkWidget* button = gtk_toggle_button_new ();
    gtk_signal_connect(GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (show_dialog), (gpointer) dialog);
 
    gtk_container_add(GTK_CONTAINER(fBox[fTop]), button);
    gtk_container_add(GTK_CONTAINER(dialog), box);
    gtk_widget_show(button);
    gtk_widget_show(box);
    pushBox(kBoxMode, box);
}

// ---------------------------  Check Button ---------------------------

struct uiCheckButton : public uiItem
{
    GtkToggleButton* fButton;
    
    uiCheckButton(GUI* ui, FAUSTFLOAT* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}
    
    static void toggled(GtkWidget* widget, gpointer data)
    {
        FAUSTFLOAT v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0; 
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()  
    { 
        FAUSTFLOAT v = *fZone;
        fCache = v; 
        gtk_toggle_button_set_active(fButton, v > 0.0); 
    }
};

void GTKUI::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
    *zone = 0.0;
    GtkWidget* button = gtk_check_button_new_with_label (label);
    addWidget(label, button);
    
    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC(uiCheckButton::toggled), (gpointer) c);

    checkForTooltip(zone, button);
}

// ---------------------------  Adjustmenty based widgets ---------------------------

struct uiAdjustment : public uiItem
{
    GtkAdjustment* fAdj;
    
    uiAdjustment(GUI* ui, FAUSTFLOAT* zone, GtkAdjustment* adj) : uiItem(ui, zone), fAdj(adj) {}
    
    static void changed(GtkWidget* widget, gpointer data)
    {
        FAUSTFLOAT v = GTK_ADJUSTMENT (widget)->value; 
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()  
    { 
        FAUSTFLOAT v = *fZone;
        fCache = v; 
        gtk_adjustment_set_value(fAdj, v);  
    }
};

// --------------------------- format knob value display ---------------------------

struct uiValueDisplay : public uiItem
{
	GtkLabel* fLabel;
	int	fPrecision ;

	uiValueDisplay(GUI* ui, FAUSTFLOAT* zone, GtkLabel* label, int precision)
		: uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

	virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        char s[64];
        if (fPrecision <= 0) {
            snprintf(s, 63, "%d", int(v));
        } else if (fPrecision > 3) {
            snprintf(s, 63, "%f", v);
        } else if (fPrecision == 1) {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[1-1], v);
        } else if (fPrecision == 2) {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[2-1], v);
        } else {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[3-1], v);
        }
        gtk_label_set_text(fLabel, s);
    }
};

// ------------------------------- Knob -----------------------------------------

void GTKUI::addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
	*zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    gtk_signal_connect(GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
    
	GtkWidget* slider = gtk_vbox_new (FALSE, 0);
	GtkWidget* fil = gtk_vbox_new (FALSE, 0);
	GtkWidget* rei = gtk_vbox_new (FALSE, 0);
	GtkWidget* re = myGtkKnob.gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(adj));
	GtkWidget* lw = gtk_label_new("");
	new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
	gtk_container_add (GTK_CONTAINER(rei), re);
	if (fGuiSize[zone]) {
		FAUSTFLOAT size = 30 * fGuiSize[zone];
		gtk_widget_set_size_request(rei, size, size);
		gtk_box_pack_start (GTK_BOX(slider), fil, true, true, 0);
		gtk_box_pack_start (GTK_BOX(slider), rei, FALSE, FALSE, 0);
	} else {
		gtk_container_add (GTK_CONTAINER(slider), fil);
		gtk_container_add (GTK_CONTAINER(slider), rei);
	}
	gtk_container_add (GTK_CONTAINER(slider), lw);
	gtk_widget_show_all(slider);
	
    label = startWith(label, "0x") ? "" : label;
	if (label && label[0] != 0) {
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
    
	GtkWidget* slider = gtk_vscale_new (GTK_ADJUSTMENT(adj));
	gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
	FAUSTFLOAT size = 160;
	if (fGuiSize[zone]) {
		size = 160 * fGuiSize[zone];
	}
	gtk_widget_set_size_request(slider, -1, size);
	
    gtk_range_set_inverted (GTK_RANGE(slider), true);
    
    label = startWith(label, "0x") ? "" : label;
    if (label && label[0] != 0) {
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
    
    GtkWidget* slider = gtk_hscale_new(GTK_ADJUSTMENT(adj));
	gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
	FAUSTFLOAT size = 160;
	if (fGuiSize[zone]) {
		size = 160 * fGuiSize[zone];
	}
	gtk_widget_set_size_request(slider, size, -1);
    
    label = startWith(label, "0x") ? "" : label;
    if (label && label[0] != 0) {
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
    
    label = startWith(label, "0x") ? "" : label;
    if (label && label[0] != 0) {
        openFrameBox(label);
        addWidget(label, spinner);
        closeBox();
    } else {
        addWidget(label, spinner);
    }

    checkForTooltip(zone, spinner);
}

// ==========================   passive widgets ===============================

// ------------------------------ Progress Bar -----------------------------------

struct uiBargraph : public uiItem
{
    GtkProgressBar*     fProgressBar;
    FAUSTFLOAT          fMin;
    FAUSTFLOAT          fMax;
    
    uiBargraph(GUI* ui, FAUSTFLOAT* zone, GtkProgressBar* pbar, FAUSTFLOAT lo, FAUSTFLOAT hi) 
            : uiItem(ui, zone), fProgressBar(pbar), fMin(lo), fMax(hi) {}

    FAUSTFLOAT scale(FAUSTFLOAT v) { return (v-fMin)/(fMax-fMin); }
    
    virtual void reflectZone()  
    { 
        FAUSTFLOAT v = *fZone;
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
    
    label = startWith(label, "0x") ? "" : label;
    if (label && label[0] != 0) {
        openFrameBox(label);
        addWidget(label, pb);
        closeBox();
    } else {
        addWidget(label, pb);
    }

    checkForTooltip(zone, pb);
}
    
void GTKUI::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_LEFT_TO_RIGHT);
    gtk_widget_set_size_request(pb, -1, 8);
    new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
    
    label = startWith(label, "0x") ? "" : label;
    if (label && label[0] != 0) {
        openFrameBox(label);
        addWidget(label, pb);
        closeBox();
    } else {
        addWidget(label, pb);
    }

    checkForTooltip(zone, pb);
}

// ------------------------------ Num Display -----------------------------------

struct uiNumDisplay : public uiItem
{
    GtkLabel* fLabel;
    int fPrecision;
    
    uiNumDisplay(GUI* ui, FAUSTFLOAT* zone, GtkLabel* label, int precision) 
            : uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

    virtual void reflectZone()  
    { 
        FAUSTFLOAT v = *fZone;
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

void GTKUI::addNumDisplay(const char* label, FAUSTFLOAT* zone, int precision)
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
    FAUSTFLOAT      fMin;
    FAUSTFLOAT      fMax;
    int             fNum;
    
    uiTextDisplay(GUI* ui, FAUSTFLOAT* zone, GtkLabel* label, const char* names[], FAUSTFLOAT lo, FAUSTFLOAT hi)
                    : uiItem(ui, zone), fLabel(label), fNames(names), fMin(lo), fMax(hi)
    {
        fNum = 0;
        while (fNames[fNum] != 0) fNum++;
    }

    virtual void reflectZone()  
    { 
        FAUSTFLOAT v = *fZone;
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
    new uiTextDisplay(this, zone, GTK_LABEL(lw), names, lo, hi);
    openFrameBox(label);
    addWidget(label, lw);
    closeBox();

    checkForTooltip(zone, lw);
}

void GTKUI::show() 
{
    assert(fTop == 0);
    gtk_widget_show(fBox[0]);
    gtk_widget_show(fWindow);
}

/**
 * Update all user items reflecting zone z
 */
    
static gboolean callUpdateAllGuis(gpointer)
{ 
    GUI::updateAllGuis(); 
    return true;
}

bool GTKUI::run()
{
    assert(fTop == 0);
    gtk_widget_show(fBox[0]);
    gtk_widget_show(fWindow);
    gtk_timeout_add(40, callUpdateAllGuis, 0);
    gtk_main();
    stop();
    return true;
}

#endif

