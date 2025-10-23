/************************** BEGIN GTK4UI.h ****************************
 FAUST Architecture File
 Copyright (C) 2003-2025 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/

#ifndef FAUST_GTK4UI_H
#define FAUST_GTK4UI_H

/******************************************************************************
 *******************************************************************************

 GRAPHIC USER INTERFACE
 gtk4 interface

 *******************************************************************************
 *******************************************************************************/
#include <set>
#include <string>

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <assert.h>
#include <gtk/gtk.h>
#include <algorithm>

#include "faust/gui/GUI.h"
#include "faust/gui/MetaDataUI.h"

#define kStackSize 256

// Insertion modes

#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

//------------ calculate needed precision
static int precision(double n)
{
    if (n < 0.009999) {
        return 3;
    } else if (n < 0.099999) {
        return 2;
    } else if (n < 0.999999) {
        return 1;
    } else {
        return 0;
    }
}

namespace gtk_knob {

class GtkKnob {
   private:
   public:
    GtkWidget*     widget;
    GtkAdjustment* adjustment;
    int            last_quadrant;
    GtkKnob();
    ~GtkKnob();
    GtkWidget* gtk_knob_new_with_adjustment(GtkAdjustment* _adjustment);
};

GtkKnob::GtkKnob()
{
}

GtkKnob::~GtkKnob()
{
}

//------forward declarations
static void     knob_snapshot(GtkWidget* widget, GtkSnapshot* snapshot, int knob_x, int knob_y,
                              int arc_offset);
static void     knob_pressed_cb(GtkGestureClick* gesture, int n_press, double x, double y,
                                gpointer user_data);
static void     knob_released_cb(GtkGestureClick* gesture, int n_press, double x, double y,
                                 gpointer user_data);
static void     knob_drag_cb(GtkGestureDrag* gesture, double offset_x, double offset_y,
                             gpointer user_data);
static gboolean knob_scroll_cb(GtkEventControllerScroll* controller, double dx, double dy,
                               gpointer user_data);
static void     knob_draw_func(GtkDrawingArea* area, cairo_t* cr, int width, int height,
                               gpointer user_data);

/****************************************************************
 ** calculate the knob pointer with dead zone
 */

const double scale_zero = 20 * (M_PI / 180);  // defines "dead zone" for knobs

static void knob_snapshot(GtkWidget* widget, GtkSnapshot* snapshot, int knob_x, int knob_y,
                          int arc_offset)
{
    int width  = gtk_widget_get_width(widget);
    int height = gtk_widget_get_height(widget);

    /** check resize **/
    int grow = (width > height) ? height : width;
    knob_x   = grow - 4;
    knob_y   = grow - 4;

    /** get values for the knob **/
    GtkAdjustment* adj = (GtkAdjustment*)g_object_get_data(G_OBJECT(widget), "adjustment");
    if (!adj) {
        return;
    }

    int    knobx     = (2 + (width - 4 - knob_x) * 0.5);
    int    knoby     = (2 + (height - 4 - knob_y) * 0.5);
    int    knobx1    = (2 + (width - 4) * 0.5);
    int    knoby1    = (2 + (height - 4) * 0.5);
    double knobstate = (gtk_adjustment_get_value(adj) - gtk_adjustment_get_lower(adj)) /
                       (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj));
    double angle      = scale_zero + knobstate * 2 * (M_PI - scale_zero);
    double knobstate1 = (0. - gtk_adjustment_get_lower(adj)) /
                        (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj));
    double pointer_off = knob_x / 6;
    double radius      = std::min<double>(knob_x - pointer_off, knob_y - pointer_off) / 2;
    double lengh_x     = (knobx + radius + pointer_off / 2) - radius * sin(angle);
    double lengh_y     = (knoby + radius + pointer_off / 2) + radius * cos(angle);
    double radius1     = std::min<double>(knob_x, knob_y) / 2;

    /** get widget colors **/
    GtkStyleContext* context = gtk_widget_get_style_context(widget);
    GdkRGBA          fg_color;
    gtk_style_context_get_color(context, &fg_color);

    double r = std::min<double>(0.6, fg_color.red);
    double g = std::min<double>(0.6, fg_color.green);
    double b = std::min<double>(0.6, fg_color.blue);

    /** create glowing knobs with cairo **/
    graphene_rect_t bounds = GRAPHENE_RECT_INIT(0, 0, (float)width, (float)height);
    cairo_t* cr = gtk_snapshot_append_cairo(snapshot, &bounds);

    cairo_arc(cr, knobx1 + arc_offset, knoby1 + arc_offset, knob_x / 2.1, 0, 2 * M_PI);
    cairo_pattern_t* pat = cairo_pattern_create_radial(
        knobx1 + arc_offset - knob_x / 6, knoby1 + arc_offset - knob_x / 6, 1, knobx1 + arc_offset,
        knoby1 + arc_offset, knob_x / 2.1);

    if (gtk_adjustment_get_lower(adj) < 0 && gtk_adjustment_get_value(adj) > 0.) {
        cairo_pattern_add_color_stop_rgb(pat, 0, r + 0.4, g + 0.4 + knobstate - knobstate1,
                                         b + 0.4);
        cairo_pattern_add_color_stop_rgb(pat, 0.7, r + 0.15,
                                         g + 0.15 + (knobstate - knobstate1) * 0.5, b + 0.15);
        cairo_pattern_add_color_stop_rgb(pat, 1, r, g, b);
    } else if (gtk_adjustment_get_lower(adj) < 0 && gtk_adjustment_get_value(adj) <= 0.) {
        cairo_pattern_add_color_stop_rgb(pat, 0, r + 0.4 + knobstate1 - knobstate, g + 0.4,
                                         b + 0.4);
        cairo_pattern_add_color_stop_rgb(pat, 0.7, r + 0.15 + (knobstate1 - knobstate) * 0.5,
                                         g + 0.15, b + 0.15);
        cairo_pattern_add_color_stop_rgb(pat, 1, r, g, b);
    } else {
        cairo_pattern_add_color_stop_rgb(pat, 0, r + 0.4, g + 0.4 + knobstate, b + 0.4);
        cairo_pattern_add_color_stop_rgb(pat, 0.7, r + 0.15, g + 0.15 + knobstate * 0.5, b + 0.15);
        cairo_pattern_add_color_stop_rgb(pat, 1, r, g, b);
    }
    cairo_set_source(cr, pat);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, fg_color.red, fg_color.green, fg_color.blue);
    cairo_set_line_width(cr, 2.0);
    cairo_stroke(cr);

    /** create a rotating pointer on the knob **/
    cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
    cairo_set_line_width(cr, std::max<double>(3, std::min<double>(7, knob_x / 15)));
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
    cairo_move_to(cr, knobx + radius1, knoby + radius1);
    cairo_line_to(cr, lengh_x, lengh_y);
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
    cairo_set_line_width(cr, std::min<double>(5, std::max<double>(1, knob_x / 30)));
    cairo_move_to(cr, knobx + radius1, knoby + radius1);
    cairo_line_to(cr, lengh_x, lengh_y);
    cairo_stroke(cr);
    cairo_pattern_destroy(pat);
    cairo_destroy(cr);
}

/****************************************************************
 ** draw function for knob
 */

static void knob_draw_func(GtkDrawingArea* area, cairo_t* cr, int width, int height,
                           gpointer user_data)
{
    GtkWidget*   widget   = GTK_WIDGET(area);
    GtkSnapshot* snapshot = gtk_snapshot_new();
    knob_snapshot(widget, snapshot, 30, 30, 0);
    GskRenderNode* node = gtk_snapshot_free_to_node(snapshot);
    if (node) {
        gsk_render_node_draw(node, cr);
        gsk_render_node_unref(node);
    }
}

/****************************************************************
 ** set value from key bindings
 */

static void gtk_knob_set_value(GtkWidget* widget, int dir_down)
{
    GtkAdjustment* adj = (GtkAdjustment*)g_object_get_data(G_OBJECT(widget), "adjustment");
    if (!adj) {
        return;
    }

    int oldstep = (int)(0.5f + (gtk_adjustment_get_value(adj) - gtk_adjustment_get_lower(adj)) /
                                   gtk_adjustment_get_step_increment(adj));
    int step;
    int nsteps = (int)(0.5f + (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj)) /
                                  gtk_adjustment_get_step_increment(adj));
    if (dir_down) {
        step = oldstep - 1;
    } else {
        step = oldstep + 1;
    }
    FAUSTFLOAT value =
        gtk_adjustment_get_lower(adj) +
        step * double(gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj)) / nsteps;
    gtk_widget_grab_focus(widget);
    gtk_adjustment_set_value(adj, value);
}

/****************************************************************
 ** keyboard bindings
 */

static gboolean gtk_knob_key_pressed(GtkEventControllerKey* controller, guint keyval, guint keycode,
                                     GdkModifierType state, gpointer user_data)
{
    GtkWidget*     widget = GTK_WIDGET(user_data);
    GtkAdjustment* adj    = (GtkAdjustment*)g_object_get_data(G_OBJECT(widget), "adjustment");
    if (!adj) {
        return FALSE;
    }

    switch (keyval) {
        case GDK_KEY_Home:
            gtk_adjustment_set_value(adj, gtk_adjustment_get_lower(adj));
            return TRUE;
        case GDK_KEY_End:
            gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj));
            return TRUE;
        case GDK_KEY_Up:
        case GDK_KEY_Right:
            gtk_knob_set_value(widget, 0);
            return TRUE;
        case GDK_KEY_Down:
        case GDK_KEY_Left:
            gtk_knob_set_value(widget, 1);
            return TRUE;
    }

    return FALSE;
}

/****************************************************************
 ** alternative (radial) knob motion mode (ctrl + mouse pressed)
 */

static void knob_pointer_event(GtkWidget* widget, gdouble x, gdouble y, int knob_x, int knob_y,
                               bool drag, GdkModifierType state)
{
    static double  last_y        = 2e20;
    int*           last_quadrant = (int*)g_object_get_data(G_OBJECT(widget), "last_quadrant");
    GtkAdjustment* adj = (GtkAdjustment*)g_object_get_data(G_OBJECT(widget), "adjustment");
    if (!adj || !last_quadrant) {
        return;
    }

    int width  = gtk_widget_get_width(widget);
    int height = gtk_widget_get_height(widget);
    int grow   = (width > height) ? height : width;
    knob_x     = grow - 4;
    knob_y     = grow - 4;

    double radius = std::min<double>(knob_x, knob_y) / 2;
    int    knobx  = (width - knob_x) / 2;
    int    knoby  = (height - knob_y) / 2;
    double posx   = (knobx + radius) - x;
    double posy   = (knoby + radius) - y;
    double value;

    if (!drag) {
        if (state & GDK_CONTROL_MASK) {
            last_y = 2e20;
            return;
        } else {
            last_y = posy;
        }
    }
    if (last_y < 1e20) {
        const double scaling = 0.005;
        double       scal    = (state & GDK_SHIFT_MASK ? scaling * 0.1 : scaling);
        value                = (last_y - posy) * scal;
        last_y               = posy;
        gtk_adjustment_set_value(
            adj, gtk_adjustment_get_value(adj) -
                     value * (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj)));
        return;
    }

    double angle = atan2(-posx, posy) + M_PI;
    if (drag) {
        int quadrant = 1 + int(angle / M_PI_2);
        if (*last_quadrant == 1 && (quadrant == 3 || quadrant == 4)) {
            angle = scale_zero;
        } else if (*last_quadrant == 4 && (quadrant == 1 || quadrant == 2)) {
            angle = 2 * M_PI - scale_zero;
        } else {
            if (angle < scale_zero) {
                angle = scale_zero;
            } else if (angle > 2 * M_PI - scale_zero) {
                angle = 2 * M_PI - scale_zero;
            }
            *last_quadrant = quadrant;
        }
    } else {
        if (angle < scale_zero) {
            angle = scale_zero;
        } else if (angle > 2 * M_PI - scale_zero) {
            angle = 2 * M_PI - scale_zero;
        }
        *last_quadrant = 0;
    }
    angle = (angle - scale_zero) / (2 * (M_PI - scale_zero));
    gtk_adjustment_set_value(
        adj, gtk_adjustment_get_lower(adj) +
                 angle * (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj)));
}

/****************************************************************
 ** mouse button pressed set value
 */

static void knob_pressed_cb(GtkGestureClick* gesture, int n_press, double x, double y,
                            gpointer user_data)
{
    GtkWidget*      widget = GTK_WIDGET(user_data);
    GdkModifierType state =
        gtk_event_controller_get_current_event_state(GTK_EVENT_CONTROLLER(gesture));

    gtk_widget_grab_focus(widget);
    knob_pointer_event(widget, x, y, 30, 30, false, state);
}

static void knob_released_cb(GtkGestureClick* gesture, int n_press, double x, double y,
                             gpointer user_data)
{
    // Nothing specific to do on release
}

/****************************************************************
 ** set the value from mouse movement
 */

static void knob_drag_cb(GtkGestureDrag* gesture, double offset_x, double offset_y,
                         gpointer user_data)
{
    GtkWidget* widget = GTK_WIDGET(user_data);
    double     start_x, start_y;
    gtk_gesture_drag_get_start_point(gesture, &start_x, &start_y);

    GdkModifierType state =
        gtk_event_controller_get_current_event_state(GTK_EVENT_CONTROLLER(gesture));
    knob_pointer_event(widget, start_x + offset_x, start_y + offset_y, 30, 30, true, state);
}

/****************************************************************
 ** set value from mousewheel
 */

static gboolean knob_scroll_cb(GtkEventControllerScroll* controller, double dx, double dy,
                               gpointer user_data)
{
    GtkWidget* widget = GTK_WIDGET(user_data);
    usleep(5000);
    gtk_knob_set_value(widget, dy > 0 ? 1 : 0);
    return TRUE;
}

/****************************************************************
 ** redraw when value changed
 */

static void gtk_knob_value_changed(GtkAdjustment* adjustment, gpointer user_data)
{
    GtkWidget* widget = GTK_WIDGET(user_data);
    gtk_widget_queue_draw(widget);
}

/****************************************************************
 ** create knob
 */

GtkWidget* GtkKnob::gtk_knob_new_with_adjustment(GtkAdjustment* _adjustment)
{
    GtkWidget* drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 30, 30);
    gtk_widget_set_can_focus(drawing_area, TRUE);

    // Store adjustment and last_quadrant
    g_object_set_data(G_OBJECT(drawing_area), "adjustment", _adjustment);
    int* last_quadrant = g_new(int, 1);
    *last_quadrant     = 0;
    g_object_set_data_full(G_OBJECT(drawing_area), "last_quadrant", last_quadrant, g_free);

    // Set up drawing
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), knob_draw_func, NULL, NULL);

    // Add gesture controllers
    GtkGesture* click = gtk_gesture_click_new();
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(click), GDK_BUTTON_PRIMARY);
    g_signal_connect(click, "pressed", G_CALLBACK(knob_pressed_cb), drawing_area);
    g_signal_connect(click, "released", G_CALLBACK(knob_released_cb), drawing_area);
    gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(click));

    GtkGesture* drag = gtk_gesture_drag_new();
    g_signal_connect(drag, "drag-update", G_CALLBACK(knob_drag_cb), drawing_area);
    gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(drag));

    // Add scroll controller
    GtkEventController* scroll =
        gtk_event_controller_scroll_new(GTK_EVENT_CONTROLLER_SCROLL_VERTICAL);
    g_signal_connect(scroll, "scroll", G_CALLBACK(knob_scroll_cb), drawing_area);
    gtk_widget_add_controller(drawing_area, scroll);

    // Add key controller
    GtkEventController* key = gtk_event_controller_key_new();
    g_signal_connect(key, "key-pressed", G_CALLBACK(gtk_knob_key_pressed), drawing_area);
    gtk_widget_add_controller(drawing_area, key);

    // Connect value changed signal
    g_signal_connect(_adjustment, "value-changed", G_CALLBACK(gtk_knob_value_changed),
                     drawing_area);

    return drawing_area;
}

}  // namespace gtk_knob

gtk_knob::GtkKnob myGtkKnob;

class GTKUI : public GUI, public MetaDataUI {
   protected:
    GtkWidget* fWindow;
    GtkWidget* fScrolledWindow;
    int        fTop;
    GtkWidget* fBox[kStackSize];
    int        fMode[kStackSize];

    GtkWidget*   addWidget(const char* label, GtkWidget* w);
    virtual void pushBox(int mode, GtkWidget* w);

   public:
    static const gboolean expand   = TRUE;
    static const gboolean fill     = TRUE;
    static const gboolean homogene = FALSE;
    static gboolean       gInitialized;

    GTKUI(char* name, int* pargc, char*** pargv);

    // -- Labels and metadata

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value);
    virtual int  checkLabelOptions(GtkWidget* widget, const std::string& fullLabel,
                                   std::string& simplifiedLabel);
    virtual void checkForTooltip(FAUSTFLOAT* zone, GtkWidget* widget);

    // -- layout groups

    virtual void openTabBox(const char* label = "");
    virtual void openHorizontalBox(const char* label = "");
    virtual void openVerticalBox(const char* label = "");
    virtual void closeBox();

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone);
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone);
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                                   FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                                     FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                             FAUSTFLOAT max, FAUSTFLOAT step);

    // -- passive display widgets

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min,
                                       FAUSTFLOAT max);
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min,
                                     FAUSTFLOAT max);

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
    virtual void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                         FAUSTFLOAT max, FAUSTFLOAT step);

    // -- passive display widgets - internal

    virtual void addNumDisplay(const char* label, FAUSTFLOAT* zone, int precision);
    virtual void addTextDisplay(const char* label, FAUSTFLOAT* zone, const char* names[],
                                FAUSTFLOAT min, FAUSTFLOAT max);

    virtual bool run();
    virtual void stop();
};

/******************************************************************************
 *******************************************************************************

 GRAPHIC USER INTERFACE (v2)
 gtk4 implementation

 *******************************************************************************
 *******************************************************************************/

// global static fields
gboolean GTKUI::gInitialized = FALSE;

static gboolean close_request_cb(GtkWindow* window, gpointer data)
{
    return FALSE;
}

static void destroy_cb(GtkWidget* widget, gpointer data)
{
    if (GTKUI::gInitialized) {
        // GTK4 doesn't use gtk_main anymore
        GTKUI::gInitialized = FALSE;
    }
}

GTKUI::GTKUI(char* name, int* pargc, char*** pargv)
{
    if (!gInitialized) {
        gtk_init();
        gInitialized = TRUE;
    }
    fWindow = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(fWindow), name);
    g_signal_connect(fWindow, "close-request", G_CALLBACK(close_request_cb), NULL);
    g_signal_connect(fWindow, "destroy", G_CALLBACK(destroy_cb), NULL);

    fTop        = 0;
    fBox[fTop]  = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    fMode[fTop] = kBoxMode;
}

// Stack a box
void GTKUI::pushBox(int mode, GtkWidget* w)
{
    ++fTop;
    assert(fTop < kStackSize);
    fMode[fTop] = mode;
    fBox[fTop]  = w;
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
        fMode[fTop] = fMode[fTop + n];
        fBox[fTop]  = fBox[fTop + n];
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

int GTKUI::checkLabelOptions(GtkWidget* widget, const std::string& fullLabel,
                             std::string& simplifiedLabel)
{
    std::map<std::string, std::string> metadata;
    extractMetadata(fullLabel, simplifiedLabel, metadata);

    if (metadata.count("tooltip")) {
        gtk_widget_set_tooltip_text(widget, metadata["tooltip"].c_str());
    }
    if (metadata["option"] == "detachable") {
        openHandleBox(simplifiedLabel.c_str());
        return 1;
    }

    //---------------------
    if (fGroupTooltip != "") {
        gtk_widget_set_tooltip_text(widget, fGroupTooltip.c_str());
        fGroupTooltip = "";
    }

    //----------------------
    return 0;
}

/**
 * Check if a tooltip is associated to a zone and add it to the corresponding widget
 */
void GTKUI::checkForTooltip(FAUSTFLOAT* zone, GtkWidget* widget)
{
    if (fTooltip.count(zone)) {
        gtk_widget_set_tooltip_text(widget, fTooltip[zone].c_str());
    }
}

// The different boxes
void GTKUI::openFrameBox(const char* label)
{
    GtkWidget* frame = gtk_frame_new(label);
    pushBox(kSingleMode, addWidget(label, frame));
}

void GTKUI::openTabBox(const char* fullLabel)
{
    std::string label;
    GtkWidget*  widget = gtk_notebook_new();

    int adjust = checkLabelOptions(widget, fullLabel, label);

    pushBox(kTabMode, addWidget(label.c_str(), widget));
    adjustStack(adjust);
}

void GTKUI::openHorizontalBox(const char* fullLabel)
{
    std::string label;
    GtkWidget*  box    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    int         adjust = checkLabelOptions(box, fullLabel, label);

    gtk_widget_set_margin_start(box, 10);
    gtk_widget_set_margin_end(box, 10);
    gtk_widget_set_margin_top(box, 10);
    gtk_widget_set_margin_bottom(box, 10);

    label = startWith(label, "0x") ? "" : label;

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label.c_str(), gtk_frame_new(label.c_str()));
        gtk_frame_set_child(GTK_FRAME(frame), box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label.c_str(), box));
    }

    adjustStack(adjust);
}

void GTKUI::openVerticalBox(const char* fullLabel)
{
    std::string label;
    GtkWidget*  box    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    int         adjust = checkLabelOptions(box, fullLabel, label);

    gtk_widget_set_margin_start(box, 10);
    gtk_widget_set_margin_end(box, 10);
    gtk_widget_set_margin_top(box, 10);
    gtk_widget_set_margin_bottom(box, 10);

    label = startWith(label, "0x") ? "" : label;

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label.c_str(), gtk_frame_new(label.c_str()));
        gtk_frame_set_child(GTK_FRAME(frame), box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label.c_str(), box));
    }

    adjustStack(adjust);
}

void GTKUI::openHandleBox(const char* label)
{
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_set_margin_start(box, 2);
    gtk_widget_set_margin_end(box, 2);
    gtk_widget_set_margin_top(box, 2);
    gtk_widget_set_margin_bottom(box, 2);

    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        // GTK4 doesn't have GtkHandleBox, use a regular frame
        GtkWidget* frame = addWidget(label, gtk_frame_new(label));
        gtk_frame_set_child(GTK_FRAME(frame), box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openEventBox(const char* label)
{
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_set_margin_start(box, 2);
    gtk_widget_set_margin_end(box, 2);
    gtk_widget_set_margin_top(box, 2);
    gtk_widget_set_margin_bottom(box, 2);

    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        // GTK4 doesn't have GtkEventBox, use a regular frame
        GtkWidget* frame = addWidget(label, gtk_frame_new(label));
        gtk_frame_set_child(GTK_FRAME(frame), box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

struct uiExpanderBox : public uiItem {
    GtkExpander* fButton;
    uiExpanderBox(GUI* ui, FAUSTFLOAT* zone, GtkExpander* b) : uiItem(ui, zone), fButton(b) {}

    static void expanded(GObject* expander, GParamSpec* pspec, gpointer data)
    {
        FAUSTFLOAT v = gtk_expander_get_expanded(GTK_EXPANDER(expander));
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
        fCache       = v;
        gtk_expander_set_expanded(GTK_EXPANDER(fButton), v);
    }
};

void GTKUI::openExpanderBox(const char* label, FAUSTFLOAT* zone)
{
    *zone          = 0.0;
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_set_margin_start(box, 2);
    gtk_widget_set_margin_end(box, 2);
    gtk_widget_set_margin_top(box, 2);
    gtk_widget_set_margin_bottom(box, 2);

    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label, gtk_expander_new(label));
        gtk_expander_set_child(GTK_EXPANDER(frame), box);
        uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
        g_signal_connect(frame, "notify::expanded", G_CALLBACK(uiExpanderBox::expanded),
                         (gpointer)c);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

GtkWidget* GTKUI::addWidget(const char* label, GtkWidget* w)
{
    switch (fMode[fTop]) {
        case kSingleMode:
            gtk_frame_set_child(GTK_FRAME(fBox[fTop]), w);
            break;
        case kBoxMode:
            gtk_box_append(GTK_BOX(fBox[fTop]), w);
            break;
        case kTabMode:
            gtk_notebook_append_page(GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label));
            break;
    }
    return w;
}

// --------------------------- Press button ---------------------------

struct uiButton : public uiItem {
    GtkButton* fButton;

    uiButton(GUI* ui, FAUSTFLOAT* zone, GtkButton* b) : uiItem(ui, zone), fButton(b) {}

    static void pressed(GtkGestureClick* gesture, int n_press, double x, double y, gpointer data)
    {
        uiItem* c = (uiItem*)data;
        c->modifyZone(1.0);
    }

    static void released(GtkGestureClick* gesture, int n_press, double x, double y, gpointer data)
    {
        uiItem* c = (uiItem*)data;
        c->modifyZone(0.0);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        // GTK4 doesn't have pressed/released methods for buttons
        // State is managed through CSS classes
    }
};

void GTKUI::addButton(const char* label, FAUSTFLOAT* zone)
{
    *zone             = 0.0;
    GtkWidget* button = gtk_button_new_with_label(label);
    addWidget(label, button);

    uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));

    GtkGesture* gesture = gtk_gesture_click_new();
    g_signal_connect(gesture, "pressed", G_CALLBACK(uiButton::pressed), (gpointer)c);
    g_signal_connect(gesture, "released", G_CALLBACK(uiButton::released), (gpointer)c);
    
    // Run this controller in the "capture" phase (before the widget's default)
    gtk_event_controller_set_propagation_phase(GTK_EVENT_CONTROLLER(gesture), GTK_PHASE_CAPTURE);
    
    gtk_widget_add_controller(button, GTK_EVENT_CONTROLLER(gesture));

    checkForTooltip(zone, button);
}

// ---------------------------  Toggle Buttons ---------------------------

struct uiToggleButton : public uiItem {
    GtkToggleButton* fButton;

    uiToggleButton(GUI* ui, FAUSTFLOAT* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}

    static void toggled(GtkToggleButton* widget, gpointer data)
    {
        FAUSTFLOAT v = gtk_toggle_button_get_active(widget) ? 1.0 : 0.0;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        gtk_toggle_button_set_active(fButton, v > 0.0);
    }
};

void GTKUI::addToggleButton(const char* label, FAUSTFLOAT* zone)
{
    *zone             = 0.0;
    GtkWidget* button = gtk_toggle_button_new_with_label(label);
    addWidget(label, button);

    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    g_signal_connect(button, "toggled", G_CALLBACK(uiToggleButton::toggled), (gpointer)c);

    checkForTooltip(zone, button);
}

static void show_dialog(GtkToggleButton* widget, gpointer data)
{
    if (gtk_toggle_button_get_active(widget)) {
        gtk_widget_set_visible(GTK_WIDGET(data), TRUE);
    } else {
        gtk_widget_set_visible(GTK_WIDGET(data), FALSE);
    }
}

static gboolean close_request_dialog(GtkWindow* window, gpointer data)
{
    return TRUE;  // Prevent closing
}

void GTKUI::openDialogBox(const char* label, FAUSTFLOAT* zone)
{
    // create toplevel window and set properties
    GtkWidget* dialog = gtk_window_new();
    gtk_window_set_decorated(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_deletable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
    gtk_window_set_title(GTK_WINDOW(dialog), label);
    g_signal_connect(dialog, "close-request", G_CALLBACK(close_request_dialog), NULL);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);

    *zone             = 0.0;
    GtkWidget* button = gtk_toggle_button_new();
    g_signal_connect(button, "toggled", G_CALLBACK(show_dialog), (gpointer)dialog);

    gtk_box_append(GTK_BOX(fBox[fTop]), button);
    gtk_window_set_child(GTK_WINDOW(dialog), box);
    pushBox(kBoxMode, box);
}

// ---------------------------  Check Button ---------------------------

struct uiCheckButton : public uiItem {
    GtkCheckButton* fButton;

    uiCheckButton(GUI* ui, FAUSTFLOAT* zone, GtkCheckButton* b) : uiItem(ui, zone), fButton(b) {}

    static void toggled(GtkCheckButton* widget, gpointer data)
    {
        FAUSTFLOAT v = gtk_check_button_get_active(widget) ? 1.0 : 0.0;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        gtk_check_button_set_active(fButton, v > 0.0);
    }
};

void GTKUI::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
    *zone             = 0.0;
    GtkWidget* button = gtk_check_button_new_with_label(label);
    addWidget(label, button);

    uiCheckButton* c = new uiCheckButton(this, zone, GTK_CHECK_BUTTON(button));
    g_signal_connect(button, "toggled", G_CALLBACK(uiCheckButton::toggled), (gpointer)c);

    checkForTooltip(zone, button);
}

// ---------------------------  Adjustment based widgets ---------------------------

struct uiAdjustment : public uiItem {
    GtkAdjustment* fAdj;

    uiAdjustment(GUI* ui, FAUSTFLOAT* zone, GtkAdjustment* adj) : uiItem(ui, zone), fAdj(adj) {}

    static void changed(GtkAdjustment* adj, gpointer data)
    {
        FAUSTFLOAT v = gtk_adjustment_get_value(adj);
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        gtk_adjustment_set_value(fAdj, v);
    }
};

// --------------------------- format knob value display ---------------------------

struct uiValueDisplay : public uiItem {
    GtkLabel* fLabel;
    int       fPrecision;

    uiValueDisplay(GUI* ui, FAUSTFLOAT* zone, GtkLabel* label, int precision)
        : uiItem(ui, zone), fLabel(label), fPrecision(precision)
    {
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        char s[64];
        if (fPrecision <= 0) {
            snprintf(s, 63, "%d", int(v));
        } else if (fPrecision > 3) {
            snprintf(s, 63, "%f", v);
        } else if (fPrecision == 1) {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[1 - 1], v);
        } else if (fPrecision == 2) {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[2 - 1], v);
        } else {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[3 - 1], v);
        }
        gtk_label_set_text(fLabel, s);
    }
};

// ------------------------------- Knob -----------------------------------------

void GTKUI::addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                    FAUSTFLOAT max, FAUSTFLOAT step)
{
    *zone              = init;
    GtkAdjustment* adj = gtk_adjustment_new(init, min, max, step, 10 * step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, adj);
    g_signal_connect(adj, "value-changed", G_CALLBACK(uiAdjustment::changed), (gpointer)c);

    GtkWidget* slider = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* fil    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* rei    = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* re     = myGtkKnob.gtk_knob_new_with_adjustment(adj);
    GtkWidget* lw     = gtk_label_new("");

    new uiValueDisplay(this, zone, GTK_LABEL(lw), precision(step));

    gtk_box_append(GTK_BOX(rei), re);

    if (fGuiSize[zone]) {
        FAUSTFLOAT size = 30 * fGuiSize[zone];
        gtk_widget_set_size_request(rei, size, size);
        gtk_box_append(GTK_BOX(slider), fil);
        gtk_widget_set_vexpand(fil, TRUE);
        gtk_box_append(GTK_BOX(slider), rei);
    } else {
        gtk_box_append(GTK_BOX(slider), fil);
        gtk_widget_set_vexpand(fil, TRUE);
        gtk_box_append(GTK_BOX(slider), rei);
    }
    gtk_box_append(GTK_BOX(slider), lw);

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

void GTKUI::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                              FAUSTFLOAT max, FAUSTFLOAT step)
{
    if (isKnob(zone)) {
        addKnob(label, zone, init, min, max, step);
        return;
    }
    *zone              = init;
    GtkAdjustment* adj = gtk_adjustment_new(init, min, max, step, 10 * step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, adj);
    g_signal_connect(adj, "value-changed", G_CALLBACK(uiAdjustment::changed), (gpointer)c);

    GtkWidget* slider = gtk_scale_new(GTK_ORIENTATION_VERTICAL, adj);
    gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
    FAUSTFLOAT size = 160;
    if (fGuiSize[zone]) {
        size = 160 * fGuiSize[zone];
    }
    gtk_widget_set_size_request(slider, -1, size);
    gtk_range_set_inverted(GTK_RANGE(slider), TRUE);

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

void GTKUI::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init,
                                FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    if (isKnob(zone)) {
        addKnob(label, zone, init, min, max, step);
        return;
    }
    *zone              = init;
    GtkAdjustment* adj = gtk_adjustment_new(init, min, max, step, 10 * step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, adj);
    g_signal_connect(adj, "value-changed", G_CALLBACK(uiAdjustment::changed), (gpointer)c);

    GtkWidget* slider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
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

void GTKUI::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                        FAUSTFLOAT max, FAUSTFLOAT step)
{
    if (isKnob(zone)) {
        addKnob(label, zone, init, min, max, step);
        return;
    }
    *zone              = init;
    GtkAdjustment* adj = gtk_adjustment_new(init, min, max, step, 10 * step, step);

    uiAdjustment* c = new uiAdjustment(this, zone, adj);
    g_signal_connect(adj, "value-changed", G_CALLBACK(uiAdjustment::changed), (gpointer)c);
    GtkWidget* spinner = gtk_spin_button_new(adj, 0.005, precision(step));

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

struct uiBargraph : public uiItem {
    GtkProgressBar* fProgressBar;
    FAUSTFLOAT      fMin;
    FAUSTFLOAT      fMax;

    uiBargraph(GUI* ui, FAUSTFLOAT* zone, GtkProgressBar* pbar, FAUSTFLOAT lo, FAUSTFLOAT hi)
        : uiItem(ui, zone), fProgressBar(pbar), fMin(lo), fMax(hi)
    {
    }

    FAUSTFLOAT scale(FAUSTFLOAT v) { return (v - fMin) / (fMax - fMin); }
    FAUSTFLOAT clip(FAUSTFLOAT v) { return std::max<double>(0.0, std::min<double>(1.0, v)); }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        gtk_progress_bar_set_fraction(fProgressBar, clip(scale(v)));
    }
};

void GTKUI::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_orientable_set_orientation(GTK_ORIENTABLE(pb), GTK_ORIENTATION_VERTICAL);
    gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(pb), TRUE);
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
    gtk_orientable_set_orientation(GTK_ORIENTABLE(pb), GTK_ORIENTATION_HORIZONTAL);
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

struct uiNumDisplay : public uiItem {
    GtkLabel* fLabel;
    int       fPrecision;

    uiNumDisplay(GUI* ui, FAUSTFLOAT* zone, GtkLabel* label, int precision)
        : uiItem(ui, zone), fLabel(label), fPrecision(precision)
    {
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        char s[64];
        if (fPrecision <= 0) {
            snprintf(s, 63, "%d", int(v));
        } else if (fPrecision > 3) {
            snprintf(s, 63, "%f", v);
        } else {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[fPrecision - 1], v);
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

struct uiTextDisplay : public uiItem {
    GtkLabel*    fLabel;
    const char** fNames;
    FAUSTFLOAT   fMin;
    FAUSTFLOAT   fMax;
    int          fNum;

    uiTextDisplay(GUI* ui, FAUSTFLOAT* zone, GtkLabel* label, const char* names[], FAUSTFLOAT lo,
                  FAUSTFLOAT hi)
        : uiItem(ui, zone), fLabel(label), fNames(names), fMin(lo), fMax(hi)
    {
        fNum = 0;
        while (fNames[fNum] != 0) {
            fNum++;
        }
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;

        int idx = int(fNum * (v - fMin) / (fMax - fMin));

        if (idx < 0) {
            idx = 0;
        } else if (idx >= fNum) {
            idx = fNum - 1;
        }

        gtk_label_set_text(fLabel, fNames[idx]);
    }
};

void GTKUI::addTextDisplay(const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT lo,
                           FAUSTFLOAT hi)
{
    GtkWidget* lw = gtk_label_new("");
    new uiTextDisplay(this, zone, GTK_LABEL(lw), names, lo, hi);
    openFrameBox(label);
    addWidget(label, lw);
    closeBox();
    checkForTooltip(zone, lw);
}

/**
 * Update all user items reflecting zone z
 */

static gboolean callUpdateAllGuis(gpointer)
{
    GUI::updateAllGuis();
    return TRUE;
}

bool GTKUI::run()
{
    assert(fTop == 0);
    gtk_window_set_child(GTK_WINDOW(fWindow), fBox[fTop]);
    
    gtk_widget_set_visible(fWindow, TRUE);
    
    // Discover main screen
    GdkDisplay* display = gdk_display_get_default();
    GdkMonitor* monitor =
    gdk_display_get_monitor_at_surface(display, gtk_native_get_surface(GTK_NATIVE(fWindow)));
    GdkRectangle rect;
    gdk_monitor_get_geometry(monitor, &rect);
    
    // Get natural size of the window
    int nat_width, nat_height;
    gtk_widget_measure(fWindow, GTK_ORIENTATION_HORIZONTAL, -1, NULL, &nat_width, NULL, NULL);
    gtk_widget_measure(fWindow, GTK_ORIENTATION_VERTICAL, -1, NULL, &nat_height, NULL, NULL);
    
    // Possibly setup scroll window
    if (nat_width > rect.width || nat_height > rect.height) {
        g_object_ref(fBox[fTop]);
        gtk_window_set_child(GTK_WINDOW(fWindow), NULL);
        fScrolledWindow = gtk_scrolled_window_new();
        gtk_widget_set_size_request(fScrolledWindow, rect.width / 2, rect.height / 2);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(fScrolledWindow), GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(fScrolledWindow), fBox[fTop]);
        gtk_window_set_child(GTK_WINDOW(fWindow), fScrolledWindow);
        g_object_unref(fBox[fTop]);
    }
    
    g_timeout_add(40, callUpdateAllGuis, NULL);
    
    // GTK4 uses GMainLoop instead of gtk_main
    GMainLoop* loop = g_main_loop_new(NULL, FALSE);
    g_signal_connect_swapped(fWindow, "destroy", G_CALLBACK(g_main_loop_quit), loop);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);
    
    return true;
}

void GTKUI::stop()
{
    GUI::stop();
    if (gInitialized) {
        gInitialized = FALSE;
        gtk_window_destroy(GTK_WINDOW(fWindow));
    }
}

#endif

/**************************  END  GTK4UI.h ***************************/
