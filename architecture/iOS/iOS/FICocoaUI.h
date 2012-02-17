/************************************************************************
 
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2004-2011 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either version 3
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 
 ************************************************************************
 ************************************************************************/

#import <UIKit/UIKit.h>
#import "FIMainViewController.h"

#include "GUI.h"
#include "FUI.h"

#include "misc.h"

#include <list>
#include <map>

#import "FISlider.h"
#import "FIButton.h"
#import "FITextField.h"

using namespace std;

/******************************************************************************
 *******************************************************************************
 
 GRAPHIC USER INTERFACE (v2)
 abstract interfaces
 
 *******************************************************************************
 *******************************************************************************/


//=================
// COCOA part
//=================



#define WIDGET_SLICE    50.f
#define OFFSET_Y        20.f

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   480


class uiCocoaItem : public uiItem
{
public:
    
    FIMainViewController* mainViewController;
    
    uiCocoaItem(GUI* ui, float* zone, FIMainViewController* controller)
    : uiItem(ui, zone), mainViewController(controller)
    {
    }
    
    ~uiCocoaItem()
    {
    }
};


// -------------------------- Slider -----------------------------------

class uiSlider : public uiCocoaItem
{

public :
    
    FISlider* fSlider;
    
    uiSlider(int index, GUI* ui, FIMainViewController* controller, const char* name, float* zone, float init, float min, float max, float step, BOOL horizontal)
    : uiCocoaItem(ui, zone, controller)
    {
        float viewWidth = controller.dspView.frame.size.width;
        
        CGRect labelFrame = CGRectMake(0.0, OFFSET_Y + WIDGET_SLICE * index - 5.f, 80.0, 30.0);
        UILabel *label = [[UILabel alloc] initWithFrame:labelFrame];
        [label setFont:[UIFont boldSystemFontOfSize:12]];
        label.textAlignment = UITextAlignmentRight;
        [label setText:[[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding]];
        label.textColor = [UIColor whiteColor];
        label.backgroundColor = [UIColor blackColor];
        [controller.dspView addSubview:label];
        
        fSlider = [[[FISlider alloc] initWithDelegate:controller] autorelease];
        if ((fSlider.isHorizontalSlider = horizontal))
        {
            fSlider.frame = CGRectMake(85.0f, OFFSET_Y + WIDGET_SLICE * index, viewWidth - 85.0f - 5.f, 20.0f);
        }
        else
        {
            fSlider.frame = CGRectMake(85.0f, OFFSET_Y + WIDGET_SLICE * index, 20.0f, 170.0f);
        }
        fSlider.labelFont = [UIFont boldSystemFontOfSize:14.0];
        fSlider.labelColor = [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
        fSlider.color = [UIColor blueColor];
        fSlider.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fSlider.min = min;
        fSlider.max = max;
        fSlider.value = init;
        fSlider.backgroundColorAlpha = 0.4;
        fSlider.handleSize = 50;
        [controller.dspView addSubview:fSlider];
    }
    
    ~uiSlider()
    {
        [fSlider release];
    }
    
    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        fSlider.value = v;
    }
    
};


// --------------------------- Press button ---------------------------

#define kStdButtonWidth		100.0
#define kStdButtonHeight	40.0

class uiButton : public uiCocoaItem
{
public:
    
    FIButton* fButton;
    
    uiButton(int index, GUI* ui, FIMainViewController* controller, const char* name, float* zone)
    : uiCocoaItem(ui, zone, controller)
    {
        float viewWidth = controller.dspView.frame.size.width;
        
        fButton = [[[FIButton alloc] initWithDelegate:controller] autorelease];
		fButton.frame = CGRectMake(viewWidth / 2 - kStdButtonWidth/2, OFFSET_Y + WIDGET_SLICE * index - 5.f, kStdButtonWidth, kStdButtonHeight);
        fButton.title = [[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding];
		fButton.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fButton.labelColor = [UIColor whiteColor];
        fButton.backgroundColorAlpha = 0.4;
        [controller.dspView addSubview:fButton];
    }
    
    ~uiButton()
    {
        [fButton release];
    }
    
    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
    }
};


// ------------------------------ Num Entry -----------------------------------

class uiNumEntry : public uiCocoaItem
{
public:
    
    FITextField* fTextField;
    
    uiNumEntry(int index, GUI* ui, FIMainViewController* controller, const char* label, float* zone, float init, float min, float max, float step)
    : uiCocoaItem(ui, zone, controller)
    {
        float viewWidth = controller.dspView.frame.size.width;
        fTextField = [[[FITextField alloc] initWithDelegate:controller] autorelease];
        [fTextField setFrame:CGRectMake(viewWidth / 2 - kStdButtonWidth/2, OFFSET_Y + WIDGET_SLICE * index - 5.f, kStdButtonWidth, kStdButtonHeight)];
		fTextField.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fTextField.labelColor = [UIColor whiteColor];
        fTextField.backgroundColorAlpha = 0.4;
        [controller.dspView addSubview:fTextField];
    }
    
    ~uiNumEntry()
    {
        [fTextField release];
    }
    
    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        fTextField.value = v;
    }
};


// ------------------------------ CocoaUI -----------------------------------

class CocoaUI : public GUI
{
public:
    list <uiItem*> fWidgetList;
    
private:
    
    UIWindow* fWindow;
    FIMainViewController* fViewController;
    MY_Meta* fMetadata;
    
    void insert(const char* label, uiItem* widget)
	{
        fWidgetList.push_back(widget);
        [fViewController.dspView setContentSize:CGSizeMake(320, WIDGET_SLICE * fWidgetList.size() + 100.f)];
    }
    
public:
    
    // -- Labels and metadata
    
    // virtual void declare (float* zone, const char* key, const char* value);
    // virtual int checkLabelOptions (GtkWidget* widget, const string& fullLabel, string& simplifiedLabel);
    // virtual void checkForTooltip (float* zone, GtkWidget* widget);
    
    // -- layout groups
    
    CocoaUI(UIWindow* window, FIMainViewController* viewController, MY_Meta* metadata)
    {
        fViewController = viewController;
        fWindow = window;
        fMetadata = metadata;
        
        fViewController.dspView.backgroundColor = [UIColor blackColor];
        fViewController.dspView.indicatorStyle = UIScrollViewIndicatorStyleWhite;
                
        [window addSubview:viewController.view];
        [window makeKeyAndVisible];
    }
    
    ~CocoaUI()
    {
        [fViewController release];
        [fWindow release];
    }
    
    virtual void openFrameBox(const char* label)
    {}
    virtual void openTabBox(const char* label = "")
    {}
    virtual void openHorizontalBox(const char* label = "")
    {}
    virtual void openVerticalBox(const char* label = "")
    {}
    
    // -- extra widget's layouts
    
    virtual void openDialogBox(const char* label, float* zone)
    {}
    virtual void openEventBox(const char* label = "")
    {}
    virtual void openHandleBox(const char* label = "")
    {}
    virtual void openExpanderBox(const char* label, float* zone)
    {}
    
    virtual void closeBox()
    {}
    
    //virtual void adjustStack(int n);
    
    // -- active widgets
    
    virtual void addButton(const char* label, float* zone)
    {
        uiItem* item = new uiButton(fWidgetList.size(), this, fViewController, label, zone);
        insert(label, item);
    }
    virtual void addToggleButton(const char* label, float* zone)
    {}
    virtual void addCheckButton(const char* label, float* zone)
    {}
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        uiItem* item = new uiSlider(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step, false);
        insert(label, item);
    }
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        uiItem* item = new uiSlider(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step, true);
        insert(label, item);
    }
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        uiItem* item = new uiNumEntry(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step);
        insert(label, item);
    }
    
    // -- passive display widgets
    
    virtual void addNumDisplay(const char* label, float* zone, int precision)
    {}
    virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max)
    {}
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max)
    {}
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
    {}
    
    virtual void show()
    {}
    virtual void run()
    {}
    
    virtual void declare(float* zone, const char* key, const char* value)
    {}
    
};


// global static fields

list<GUI*>                   GUI::fGuiList;

/*
 bool                        GTKUI::fInitialized = false;
 map<float*, float>          GTKUI::fGuiSize;
 map<float*, string>         GTKUI::fTooltip;
 */
