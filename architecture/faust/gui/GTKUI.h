/************************** BEGIN GTKUI.h ****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_GTKUI_H
#define FAUST_GTKUI_H

/******************************************************************************
 *******************************************************************************

 GRAPHIC USER INTERFACE
 gtk interface

 *******************************************************************************
 *******************************************************************************/
#include <set>
#include <string>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gdk/gdktypes.h>
#include <gdk/gdkkeysyms.h>

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
    if (n < 0.009999)
        return 3;
    else if (n < 0.099999)
        return 2;
    else if (n < 0.999999)
        return 1;
    else
        return 0;
}

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
    static const bool expand   = true;
    static const bool fill     = true;
    static const bool homogene = false;
    static bool       gInitialized;

    GTKUI(char* name, int* pargc, char*** pargv);

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
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max,
                                   FAUSTFLOAT step);
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min,
                                     FAUSTFLOAT max, FAUSTFLOAT step);
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max,
                             FAUSTFLOAT step);

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
    virtual void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max,
                         FAUSTFLOAT step);

    // -- passive display widgets - internal

    virtual void addNumDisplay(const char* label, FAUSTFLOAT* zone, int precision);
    virtual void addTextDisplay(const char* label, FAUSTFLOAT* zone, const char* names[], FAUSTFLOAT min,
                                FAUSTFLOAT max);

    virtual bool run();
    virtual void stop();
};

/******************************************************************************
 *******************************************************************************

 GRAPHIC USER INTERFACE (v2)
 gtk implementation

 *******************************************************************************
 *******************************************************************************/

// global static fields
bool GTKUI::gInitialized = false;

static bool delete_event(GtkWidget* widget, GdkEvent* event, gpointer data)
{
    return false;
}

static void destroy_event(GtkWidget* widget, gpointer data)
{
    if (GTKUI::gInitialized) {
        gtk_main_quit();
        GTKUI::gInitialized = false;
    }
}

GTKUI::GTKUI(char* name, int* pargc, char*** pargv)
{
    if (!gInitialized) {
        gtk_init(pargc, pargv);
        gInitialized = true;
    }
    fWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // gtk_container_set_border_width (GTK_CONTAINER (fWindow), 10);
    gtk_window_set_title(GTK_WINDOW(fWindow), name);
    g_signal_connect(fWindow, "delete_event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(fWindow, "destroy", G_CALLBACK(destroy_event), NULL);


    fTop        = 0;
    fBox[fTop]  = gtk_vbox_new(homogene, 4);
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

int GTKUI::checkLabelOptions(GtkWidget* widget, const std::string& fullLabel, std::string& simplifiedLabel)
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
    // no adjustement of the stack needed
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
    GtkWidget* box = gtk_frame_new(label);
    // gtk_container_set_border_width (GTK_CONTAINER (box), 10);

    pushBox(kSingleMode, addWidget(label, box));
}

void GTKUI::openTabBox(const char* fullLabel)
{
    std::string label;
    GtkWidget*  widget = gtk_notebook_new();

    int adjust = checkLabelOptions(widget, fullLabel, label);

    pushBox(kTabMode, addWidget(label.c_str(), widget));

    // adjust stack because otherwise Handlebox will remain open
    adjustStack(adjust);
}

void GTKUI::openHorizontalBox(const char* fullLabel)
{
    std::string label;
    GtkWidget*  box    = gtk_hbox_new(homogene, 4);
    int         adjust = checkLabelOptions(box, fullLabel, label);

    gtk_container_set_border_width(GTK_CONTAINER(box), 10);
    label = startWith(label, "0x") ? "" : label;

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label.c_str(), gtk_frame_new(label.c_str()));
        gtk_container_add(GTK_CONTAINER(frame), box);
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
    GtkWidget*  box    = gtk_vbox_new(homogene, 4);
    int         adjust = checkLabelOptions(box, fullLabel, label);

    gtk_container_set_border_width(GTK_CONTAINER(box), 10);
    label = startWith(label, "0x") ? "" : label;

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label.c_str(), gtk_frame_new(label.c_str()));
        gtk_container_add(GTK_CONTAINER(frame), box);
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
    GtkWidget* box = gtk_hbox_new(homogene, 4);
    gtk_container_set_border_width(GTK_CONTAINER(box), 2);
    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label, gtk_handle_box_new());
        gtk_container_add(GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openEventBox(const char* label)
{
    GtkWidget* box = gtk_hbox_new(homogene, 4);
    gtk_container_set_border_width(GTK_CONTAINER(box), 2);
    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label, gtk_event_box_new());
        gtk_container_add(GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

struct uiExpanderBox : public uiItem {
    GtkExpander* fButton;
    uiExpanderBox(GUI* ui, FAUSTFLOAT* zone, GtkExpander* b) : uiItem(ui, zone), fButton(b) {}
    static void expanded(GtkWidget* widget, gpointer data)
    {
        FAUSTFLOAT v = gtk_expander_get_expanded(GTK_EXPANDER(widget));
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
    GtkWidget* box = gtk_hbox_new(homogene, 4);
    gtk_container_set_border_width(GTK_CONTAINER(box), 2);
    label = startWith(label, "0x") ? "" : label;
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget* frame = addWidget(label, gtk_expander_new(label));
        gtk_container_add(GTK_CONTAINER(frame), box);
        uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
        g_signal_connect_swapped(frame, "activate", G_CALLBACK(uiExpanderBox::expanded), c);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

GtkWidget* GTKUI::addWidget(const char* label, GtkWidget* w)
{
    switch (fMode[fTop]) {
        case kSingleMode:
            gtk_container_add(GTK_CONTAINER(fBox[fTop]), w);
            break;
        case kBoxMode:
            gtk_box_pack_start(GTK_BOX(fBox[fTop]), w, expand, fill, 0);
            break;
        case kTabMode:
            gtk_notebook_append_page(GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label));
            break;
    }
    gtk_widget_show(w);
    return w;
}

// --------------------------- Press button ---------------------------

struct uiButton : public uiItem {
    GtkButton* fButton;

    uiButton(GUI* ui, FAUSTFLOAT* zone, GtkButton* b) : uiItem(ui, zone), fButton(b) {}

    static void pressed(GtkWidget* widget, gpointer data)
    {
        uiItem* c = (uiItem*)data;
        c->modifyZone(1.0);
    }

    static void released(GtkWidget* widget, gpointer data)
    {
        uiItem* c = (uiItem*)data;
        c->modifyZone(0.0);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        if (v > 0.0)
            gtk_button_pressed(fButton);
        else
            gtk_button_released(fButton);
    }
};

void GTKUI::addButton(const char* label, FAUSTFLOAT* zone)
{
    *zone             = 0.0;
    GtkWidget* button = gtk_button_new_with_label(label);
    addWidget(label, button);

    uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));

    g_signal_connect_swapped(button, "pressed", G_CALLBACK(uiButton::pressed), c);
    g_signal_connect_swapped(button, "released", G_CALLBACK(uiButton::released), c);

    checkForTooltip(zone, button);
}

// ---------------------------  Toggle Buttons ---------------------------

struct uiToggleButton : public uiItem {
    GtkToggleButton* fButton;

    uiToggleButton(GUI* ui, FAUSTFLOAT* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}

    static void toggled(GtkToggleButton* widget, gpointer data)
    {
        FAUSTFLOAT v = (gtk_toggle_button_get_active(widget)) ? 1.0 : 0.0;
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
    g_signal_connect_swapped(button, "toggled", G_CALLBACK(uiToggleButton::toggled), c);

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
    } else
        gtk_widget_hide(GTK_WIDGET(data));
}

static bool deleteevent(GtkWidget* widget, gpointer data)
{
    return true;
}

void GTKUI::openDialogBox(const char* label, FAUSTFLOAT* zone)
{
    // create toplevel window and set properties
    GtkWidget* dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(dialog), true);
    gtk_window_set_deletable(GTK_WINDOW(dialog), false);
    gtk_window_set_resizable(GTK_WINDOW(dialog), false);
    gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
    gtk_window_set_keep_below(GTK_WINDOW(dialog), false);
    gtk_window_set_title(GTK_WINDOW(dialog), label);
    g_signal_connect(G_OBJECT(dialog), "delete_event", G_CALLBACK(deleteevent), NULL);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), true);

    GtkWidget* box = gtk_hbox_new(homogene, 4);

    *zone             = 0.0;
    GtkWidget* button = gtk_toggle_button_new();
    g_signal_connect_swapped(button, "toggled", G_CALLBACK(show_dialog), dialog);

    gtk_container_add(GTK_CONTAINER(fBox[fTop]), button);
    gtk_container_add(GTK_CONTAINER(dialog), box);
    gtk_widget_show(button);
    gtk_widget_show(box);
    pushBox(kBoxMode, box);
}

// ---------------------------  Check Button ---------------------------

struct uiCheckButton : public uiItem {
    GtkToggleButton* fButton;

    uiCheckButton(GUI* ui, FAUSTFLOAT* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}

    static void toggled(GtkToggleButton* widget, gpointer data)
    {
        FAUSTFLOAT v = (gtk_toggle_button_get_active(widget)) ? 1.0 : 0.0;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        gtk_toggle_button_set_active(fButton, v > 0.0);
    }
};

void GTKUI::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
    *zone             = 0.0;
    GtkWidget* button = gtk_check_button_new_with_label(label);
    addWidget(label, button);

    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    g_signal_connect_swapped(button, "toggled", G_CALLBACK(uiCheckButton::toggled), c);

    checkForTooltip(zone, button);
}

// ---------------------------  Adjustmenty based widgets ---------------------------

struct uiAdjustment : public uiItem {
    GtkAdjustment* fAdj;

    uiAdjustment(GUI* ui, FAUSTFLOAT* zone, GtkAdjustment* adj) : uiItem(ui, zone), fAdj(adj) {}

    static void changed(GtkWidget* widget, gpointer data)
    {
        GtkAdjustment* adj = gtk_range_get_adjustment(GTK_RANGE(widget));
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

void GTKUI::addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max,
                    FAUSTFLOAT step)
{
    *zone          = init;
    GtkAdjustment* adj = gtk_adjustment_new(init, min, max, step, 10 * step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    g_signal_connect_swapped(adj, "value-changed", G_CALLBACK(uiAdjustment::changed), c);

    GtkWidget* slider = gtk_vbox_new(false, 0);
    GtkWidget* fil    = gtk_vbox_new(false, 0);
    GtkWidget* rei    = gtk_vbox_new(false, 0);
    GtkWidget* re     = gtk_spin_button_new(adj, step*10, 0); // todo:
    GtkWidget* lw     = gtk_label_new("");
    new uiValueDisplay(this, zone, GTK_LABEL(lw), precision(step));
    gtk_container_add(GTK_CONTAINER(rei), re);
    if (fGuiSize[zone]) {
        FAUSTFLOAT size = 30 * fGuiSize[zone];
        gtk_widget_set_size_request(rei, size, size);
        gtk_box_pack_start(GTK_BOX(slider), fil, true, true, 0);
        gtk_box_pack_start(GTK_BOX(slider), rei, false, false, 0);
    } else {
        gtk_container_add(GTK_CONTAINER(slider), fil);
        gtk_container_add(GTK_CONTAINER(slider), rei);
    }
    gtk_container_add(GTK_CONTAINER(slider), lw);
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

void GTKUI::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max,
                              FAUSTFLOAT step)
{
    if (isKnob(zone)) {
        addKnob(label, zone, init, min, max, step);
        return;
    }
    *zone          = init;
    GtkAdjustment* adj = gtk_adjustment_new(init, min, max, step, 10 * step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect_swapped(adj, "value-changed", G_CALLBACK(uiAdjustment::changed), c);

    GtkWidget* slider = gtk_vscale_new(GTK_ADJUSTMENT(adj));
    gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
    FAUSTFLOAT size = 160;
    if (fGuiSize[zone]) {
        size = 160 * fGuiSize[zone];
    }
    gtk_widget_set_size_request(slider, -1, size);
    gtk_range_set_inverted(GTK_RANGE(slider), true);

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

void GTKUI::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max,
                                FAUSTFLOAT step)
{
    if (isKnob(zone)) {
        addKnob(label, zone, init, min, max, step);
        return;
    }
    *zone          = init;
    GtkAdjustment* adj = gtk_adjustment_new(init, min, max, step, 10 * step, 0);

    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    g_signal_connect_swapped(adj, "value-changed", G_CALLBACK(uiAdjustment::changed), c);

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

void GTKUI::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max,
                        FAUSTFLOAT step)
{
    if (isKnob(zone)) {
        addKnob(label, zone, init, min, max, step);
        return;
    }
    *zone          = init;
    GtkAdjustment* adj = gtk_adjustment_new(init, min, max, step, 10 * step, step);

    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect_swapped(adj, "value-changed", G_CALLBACK(uiAdjustment::changed), c);
    GtkWidget* spinner = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0.005, precision(step));

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

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;
        gtk_progress_bar_set_fraction(fProgressBar, scale(v));
    }
};

void GTKUI::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_orientable_set_orientation(GTK_ORIENTABLE(pb), GTK_ORIENTATION_VERTICAL);

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

    uiTextDisplay(GUI* ui, FAUSTFLOAT* zone, GtkLabel* label, const char* names[], FAUSTFLOAT lo, FAUSTFLOAT hi)
        : uiItem(ui, zone), fLabel(label), fNames(names), fMin(lo), fMax(hi)
    {
        fNum = 0;
        while (fNames[fNum] != 0) fNum++;
    }

    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache       = v;

        int idx = int(fNum * (v - fMin) / (fMax - fMin));

        if (idx < 0)
            idx = 0;
        else if (idx >= fNum)
            idx = fNum - 1;

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

/**
 * Update all user items reflecting zone z
 */

gboolean callUpdateAllGuis(gpointer)
{
    GUI::updateAllGuis();
    return true;
}

bool GTKUI::run()
{
    assert(fTop == 0);
    gtk_container_add(GTK_CONTAINER(fWindow), fBox[fTop]);

    gtk_widget_show_all(fWindow);
    gtk_widget_show(fBox[0]);
    gtk_widget_show(fWindow);

    // Discover main screen
    GdkScreen*   screen = gdk_screen_get_default();
    GdkRectangle rect;
    gdk_screen_get_monitor_geometry(screen, gdk_screen_get_primary_monitor(screen), &rect);

    // Possibly setup scroll window
    GtkAllocation* allocation;
    gtk_widget_get_allocation(fWindow, allocation);
    if (allocation->width > rect.width || allocation->height > rect.height) {
        g_object_ref(fBox[fTop]);  // To avoid desallocation with 'gtk_container_remove'
        gtk_container_remove(GTK_CONTAINER(fWindow), fBox[fTop]);
        fScrolledWindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_size_request(fScrolledWindow, rect.width / 2, rect.height / 2);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(fScrolledWindow), GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(fScrolledWindow), fBox[fTop]);
        gtk_container_add(GTK_CONTAINER(fWindow), fScrolledWindow);
    }

    gtk_widget_show_all(fWindow);
    gtk_widget_show(fBox[0]);
    gtk_widget_show(fWindow);

    g_timeout_add(40, callUpdateAllGuis, nullptr);
    gtk_main();
    return true;
}

void GTKUI::stop()
{
    GUI::stop();
    if (gInitialized) {
        gInitialized = false;
        gtk_main_quit();
        g_signal_emit_by_name(fWindow, "destroy");
    }
}

#endif

/**************************  END  GTKUI.h **************************/
