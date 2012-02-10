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
#define OFFSET_Y        80.f

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
    
    UISlider* fSlider;
    UITextField* fTextField;
    
    uiSlider(int index, GUI* ui, FIMainViewController* controller, const char* name, float* zone, float init, float min, float max, float step)
    : uiCocoaItem(ui, zone, controller)
    {
        CGRect labelFrame = CGRectMake(0.0, OFFSET_Y + WIDGET_SLICE * index - 5.f, 130.0, 30.0);
        UILabel *label = [[UILabel alloc] initWithFrame:labelFrame];
        [label setFont:[UIFont boldSystemFontOfSize:12]];
        label.textAlignment = UITextAlignmentCenter;
        [label setText:[[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding]];
        label.textColor = [UIColor blackColor ];
        label.backgroundColor = [UIColor lightGrayColor];
        [controller.dspView addSubview:label];
        
        CGRect frame = CGRectMake(130.0f, OFFSET_Y + WIDGET_SLICE * index, 110.0f, 7.0f);
        fSlider = [[UISlider alloc] initWithFrame:frame];
        [fSlider addTarget:mainViewController action:@selector(changed:)forControlEvents:UIControlEventValueChanged];
        fSlider.minimumValue = min;
        fSlider.maximumValue = max;
        fSlider.continuous = YES;
        fSlider.value = init;
        [controller.dspView addSubview:fSlider];
        
        CGRect textFieldFrame = CGRectMake(250.0, OFFSET_Y + WIDGET_SLICE * index, 60.0, 20.0);
        fTextField = [[UITextField alloc] initWithFrame:textFieldFrame];
        [fTextField setBorderStyle:UITextBorderStyleLine];
        fTextField.textAlignment = UITextAlignmentCenter;
        [fTextField setEnabled:NO];
        [fTextField setTextColor:[UIColor blackColor]];
        [fTextField setFont:[UIFont systemFontOfSize:14]];
        [fTextField setPlaceholder:[NSString stringWithFormat:@"%1.2f", init]];
        [fTextField setBackgroundColor:[UIColor whiteColor]];
        [fTextField setAdjustsFontSizeToFitWidth:YES];
        fTextField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
        [controller.dspView addSubview:fTextField];
    }
    
    ~uiSlider()
    {
        [fSlider release];
        [fTextField release];
    }
    
    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        fSlider.value = v;
        [fTextField setPlaceholder:[NSString stringWithFormat:@"%1.2f", v]];
    }
    
};


// --------------------------- Press button ---------------------------

#define kStdButtonWidth		100.0
#define kStdButtonHeight	40.0

class uiButton : public uiCocoaItem
{
public:
    
    UIButton* fButton;
    
    uiButton(int index, GUI* ui, FIMainViewController* controller, const char* name, float* zone)
    : uiCocoaItem(ui, zone, controller)
    {
        fButton = [[UIButton buttonWithType:UIButtonTypeRoundedRect] retain];
		fButton.frame = CGRectMake(SCREEN_WIDTH/2 - kStdButtonWidth/2, OFFSET_Y + WIDGET_SLICE * index - 5.f, kStdButtonWidth, kStdButtonHeight);
        [fButton setTitle:[[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding] forState:UIControlStateNormal];
		fButton.backgroundColor = [UIColor clearColor];
	    [fButton addTarget:controller action:@selector(pressed:) forControlEvents:UIControlEventTouchDown];
        [fButton addTarget:controller action:@selector(released:) forControlEvents:UIControlEventTouchUpInside];
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
    
    UITextField* fTextField;
    
    uiNumEntry(int index, GUI* ui, FIMainViewController* controller, const char* label, float* zone, float init, float min, float max, float step)
    : uiCocoaItem(ui, zone, controller)
    {
        CGRect textFieldFrame = CGRectMake(SCREEN_WIDTH/2 - kStdButtonWidth/2, OFFSET_Y + WIDGET_SLICE * index - 5.f, kStdButtonWidth, kStdButtonHeight);
        fTextField = [[UITextField alloc] initWithFrame:textFieldFrame];
        [fTextField setTextColor:[UIColor blackColor]];
        [fTextField setFont:[UIFont systemFontOfSize:14]];
        [fTextField setPlaceholder:@"<enter text>"];
        [fTextField setBackgroundColor:[UIColor whiteColor]];
        fTextField.keyboardType = UIKeyboardTypeDefault;
        
        [controller.dspView addSubview:fTextField];
    }
    
    ~uiNumEntry()
    {
        [fTextField release];
    }
    
    void reflectZone()
    {
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
        
        CGRect titleFrame = CGRectMake(0.0, 0.0f, 320.0, 75.0);
        UIView *titleView = [[UIView alloc] initWithFrame:titleFrame];
        titleView.backgroundColor = [UIColor brownColor];
        [fViewController.dspView addSubview:titleView];
        
        if (fMetadata->find("name") != fMetadata->end()) {
            const char* name = (*fMetadata->find("name")).second;
            CGRect labelFrame = CGRectMake(0.0, 20.0f, 320.0, 30.0);
            UILabel *label = [[UILabel alloc] initWithFrame:labelFrame];
            [label setFont:[UIFont boldSystemFontOfSize:18]];
            label.textAlignment = UITextAlignmentCenter;
            [label setText:[[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding]];
            label.textColor = [UIColor blackColor ];
            label.backgroundColor = [UIColor brownColor];
            [fViewController.dspView addSubview:label];
        }
        
        if (fMetadata->find("author") != fMetadata->end()) {
            const char* name = (*fMetadata->find("author")).second;
            CGRect labelFrame = CGRectMake(0.0, 45.0f, 320.0, 30.0);
            UILabel *label = [[UILabel alloc] initWithFrame:labelFrame];
            [label setFont:[UIFont boldSystemFontOfSize:14]];
            label.textAlignment = UITextAlignmentCenter;
            [label setText:[[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding]];
            label.textColor = [UIColor blackColor ];
            label.backgroundColor = [UIColor brownColor];
            [fViewController.dspView addSubview:label];
        }
        
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
        uiItem* item = new uiSlider(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step);
        insert(label, item);
    }
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        uiItem* item = new uiSlider(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step);
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
