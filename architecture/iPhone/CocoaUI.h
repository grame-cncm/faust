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
#import "iPhoneViewController.h"

#include "faust/misc.h"

#include <list>
#include <map>

using namespace std;

/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces

*******************************************************************************
*******************************************************************************/

//typedef void (*uiCallback)(float val, void* data);

//=================
// COCOA part
//=================

class UI;

@interface uiItem : NSObject
{
	UI* fGUI;
	float* fZone;
	float fCache;
}

- (id)initWithValues:(UI*)ui:(float*)zone;
- (void)modifyZone:(float)v;
- (float)cache;
- (void)reflectZone;

@end

/**
 * Graphic User Interface : abstract definition
 */

class UI
{
	typedef list<uiItem*> clist;
	typedef map<float*, clist*> zmap;

 protected:

 	static list<UI*> fGuiList;
	zmap fZoneMap;
	bool fStopped;

 public:

	UI() : fStopped(false)
    {
		fGuiList.push_back(this);
	}

	virtual ~UI()
    {
		// suppression de this dans fGuiList
	}

	// -- registerZone(z,c) : zone management

	void registerZone(float* z, uiItem* c)
	{
        if (fZoneMap.find(z) == fZoneMap.end()) {
            fZoneMap[z] = new clist();
        }
		fZoneMap[z]->push_back(c);
	}

	// -- saveState(filename) : save the value of every zone to a file

	void saveState(const char* filename)
	{
		ofstream f(filename);

        if (!f.is_open()) {
        } else {
            for (zmap::iterator i = fZoneMap.begin(); i != fZoneMap.end(); i++) {
                f << *(i->first) << ' ';
            }
        }

		f << endl;
		f.close();
	}

	// -- recallState(filename) : load the value of every zone from a file

	void recallState(const char* filename)
	{
		ifstream f(filename);
		if (f.good()) {
            for (zmap::iterator i = fZoneMap.begin(); i != fZoneMap.end(); i++) {
				f >> *(i->first);
			}
		}
		f.close();
        updateAllZones();
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

    //void addCallback(float* zone, uiCallback foo, void* data);

    // -- widget's layouts

    virtual void openFrameBox(const char* label) = 0;
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;

    // -- extra widget's layouts

    virtual void openDialogBox(const char* label, float* zone) = 0;
    virtual void openEventBox(const char* label) = 0;
    virtual void openHandleBox(const char* label) = 0;
    virtual void openExpanderBox(const char* label, float* zone) = 0;

    virtual void closeBox() = 0;

    virtual void show() {};
    virtual void run() {};

	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }

    virtual void declare(float* zone, const char* key, const char* value) {}
};

/**
 * Update all user items reflecting zone z
 */

void UI::updateZone(float* z)
{
	float v = *z;
 	clist* l = fZoneMap[z];

	for (clist::iterator c = l->begin(); c != l->end(); c++) {
		if ([(*c) cache] != v) [(*c) reflectZone];
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
			if ([(*c) cache] != v) [(*c) reflectZone];
		}
	}
}

/*
inline void UI::addCallback(float* zone, uiCallback foo, void* data)
{
	new uiCallbackItem(this, zone, foo, data);
};
*/

#define WIDGET_SLICE    50.f
#define OFFSET_Y        80.f

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   480

@implementation uiItem

- (id)initWithValues:(UI*)ui:(float*)zone
{
    fGUI = ui;
    fZone = zone;
    fCache = -123456.654321;
    ui->registerZone(zone, self);
    return self;
}

- (void)modifyZone:(float)v
{
    fCache = v;

    if (*fZone != v) {
        *fZone = v;
        fGUI->updateZone(fZone);
    }
}

- (float)cache
{
    return fCache;
}

// To implement in subclasses

- (void)reflectZone
{}

@end

// -------------------------- Slider -----------------------------------

@interface uiSlider : uiItem
{
    UISlider* fSlider;
    UITextField* fTextField;
}

- (void)changed:(UISlider*)sender;
- (void)reflectZone;
- (id)initWithValues:(int)index:(UI*)ui:(iPhoneViewController*)controler:(const char*)label:(float*)zone:(float)init:(float)min:(float)max:(float)step;

@end

@implementation uiSlider

- (id)initWithValues:(int)index:(UI*)ui:(iPhoneViewController*)controler:(const char*)name:(float*)zone:(float)init:(float)min:(float)max:(float)step
{
    if (self = [super initWithValues:ui:zone]) {

        CGRect labelFrame = CGRectMake(0.0, OFFSET_Y + WIDGET_SLICE * index - 5.f, 130.0, 30.0);
        UILabel *label = [[UILabel alloc] initWithFrame:labelFrame];
        [label setFont:[UIFont boldSystemFontOfSize:12]];
        label.textAlignment = UITextAlignmentCenter;
        [label setText:[[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding]];
        label.textColor = [UIColor blackColor ];
        label.backgroundColor = [UIColor lightGrayColor];
        [controler.view addSubview:label];

        CGRect frame = CGRectMake(130.0f, OFFSET_Y + WIDGET_SLICE * index, 110.0f, 7.0f);
        fSlider = [[UISlider alloc] initWithFrame:frame];
        [fSlider addTarget:self action:@selector(changed:)forControlEvents:UIControlEventValueChanged];
        fSlider.minimumValue = min;
        fSlider.maximumValue = max;
        fSlider.continuous = YES;
        fSlider.value = init;
        [controler.view addSubview:fSlider];

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
        [controler.view addSubview:fTextField];
    }
    return self;
}

- (void)changed:(UISlider*)sender
{
    [self modifyZone:sender.value];
    [fTextField setPlaceholder:[NSString stringWithFormat:@"%1.2f", sender.value]];
}

- (void)reflectZone;
{
    float v = *fZone;
    fCache = v;
    fSlider.value = v;
    [fTextField setPlaceholder:[NSString stringWithFormat:@"%1.2f", v]];
}

- (void)dealloc
{
    [fSlider release];
    [fTextField release];
    [super dealloc];
}

@end

// --------------------------- Press button ---------------------------

#define kStdButtonWidth		100.0
#define kStdButtonHeight	40.0

@interface uiButton : uiItem
{
    UIButton* fButton;
}

- (void)pressed:(UIButton*)sender;
- (void)released:(UIButton*)sender;
- (void)reflectZone;
- (id)initWithValues:(int)index:(UI*)ui:(iPhoneViewController*)controler:(const char*)label:(float*)zone;

@end

@implementation uiButton

- (id)initWithValues:(int)index:(UI*)ui:(iPhoneViewController*)controler:(const char*)name:(float*)zone
{
     if (self = [super initWithValues:ui:zone]) {
        fButton = [[UIButton buttonWithType:UIButtonTypeRoundedRect] retain];
		fButton.frame = CGRectMake(SCREEN_WIDTH/2 - kStdButtonWidth/2, OFFSET_Y + WIDGET_SLICE * index - 5.f, kStdButtonWidth, kStdButtonHeight);
        [fButton setTitle:[[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding] forState:UIControlStateNormal];
		fButton.backgroundColor = [UIColor clearColor];
	    [fButton addTarget:self action:@selector(pressed:) forControlEvents:UIControlEventTouchDown];
        [fButton addTarget:self action:@selector(released:) forControlEvents:UIControlEventTouchUpInside];
        [controler.view addSubview:fButton];
    }
    return self;
}

- (void)pressed:(UIButton*)sender
{
   [self modifyZone:1.0f];
}

- (void)released:(UIButton*)sender
{
   [self modifyZone:0.0f];
}

- (void)reflectZone
{
    float v = *fZone;
    fCache = v;
    //if (v > 0.0) gtk_button_pressed(fButton); else gtk_button_released(fButton);
}

- (void)dealloc
{
    [fButton release];
    [super dealloc];
}

@end

// ------------------------------ Num Entry -----------------------------------

@interface uiNumEntry : uiItem
{
    UITextField* fTextField;
}

- (id)initWithValues:(int)index:(UI*)ui:(iPhoneViewController*)controler:(const char*)label:(float*)zone:(float)init:(float)min:(float)max:(float)step;

@end

@implementation uiNumEntry

- (id)initWithValues:(int)index:(UI*)ui:(iPhoneViewController*)controler:(const char*)label:(float*)zone:(float)init:(float)min:(float)max:(float)step
{
    if (self = [super initWithValues:ui:zone]) {
        CGRect textFieldFrame = CGRectMake(SCREEN_WIDTH/2 - kStdButtonWidth/2, OFFSET_Y + WIDGET_SLICE * index - 5.f, kStdButtonWidth, kStdButtonHeight);
        fTextField = [[UITextField alloc] initWithFrame:textFieldFrame];
        [fTextField setTextColor:[UIColor blackColor]];
        [fTextField setFont:[UIFont systemFontOfSize:14]];
        [fTextField setPlaceholder:@"<enter text>"];
        [fTextField setBackgroundColor:[UIColor whiteColor]];
        fTextField.keyboardType = UIKeyboardTypeDefault;

        [controler.view addSubview:fTextField];
    }
    return self;
}

- (void)dealloc
{
    [fTextField release];
    [super dealloc];
}

@end


class CocoaUI : public UI
{

private:

    UIWindow* fWindow;
    iPhoneViewController* fViewController;
    MY_Meta* fMetadata;

    list <uiItem*> fWidgetList;

    void insert(const char* label, uiItem* widget)
	{
         fWidgetList.push_back(widget);
         [fViewController.view setContentSize:CGSizeMake(320, WIDGET_SLICE * fWidgetList.size() + 100.f)];
    }

public:

    // -- Labels and metadata

    // virtual void declare (float* zone, const char* key, const char* value);
    // virtual int checkLabelOptions (GtkWidget* widget, const string& fullLabel, string& simplifiedLabel);
    // virtual void checkForTooltip (float* zone, GtkWidget* widget);

    // -- layout groups

    CocoaUI(UIWindow* window, iPhoneViewController* viewController, MY_Meta* metadata)
    {
        fViewController = viewController;
        fWindow = window;
        fMetadata = metadata;

         CGRect titleFrame = CGRectMake(0.0, 0.0f, 320.0, 75.0);
         UIView *titleView = [[UIView alloc] initWithFrame:titleFrame];
         titleView.backgroundColor = [UIColor brownColor];
         [fViewController.view addSubview:titleView];

        if (fMetadata->find("name") != fMetadata->end()) {
            const char* name = (*fMetadata->find("name")).second;
            CGRect labelFrame = CGRectMake(0.0, 20.0f, 320.0, 30.0);
            UILabel *label = [[UILabel alloc] initWithFrame:labelFrame];
            [label setFont:[UIFont boldSystemFontOfSize:18]];
            label.textAlignment = UITextAlignmentCenter;
            [label setText:[[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding]];
            label.textColor = [UIColor blackColor ];
            label.backgroundColor = [UIColor brownColor];
            [fViewController.view addSubview:label];
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
            [fViewController.view addSubview:label];
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
        uiItem* item = [[uiButton alloc] initWithValues:fWidgetList.size():this:fViewController:label:zone];
        insert(label, item);
    }
    virtual void addToggleButton(const char* label, float* zone)
    {}
    virtual void addCheckButton(const char* label, float* zone)
    {}
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        uiItem* item = [[uiSlider alloc] initWithValues:fWidgetList.size():this:fViewController:label:zone:init:min:max:step];
        insert(label, item);
    }
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        uiItem* item = [[uiSlider alloc] initWithValues:fWidgetList.size():this:fViewController:label:zone:init:min:max:step];
        insert(label, item);
    }
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        uiItem* item = [[uiNumEntry alloc] initWithValues:fWidgetList.size():this:fViewController:label:zone:init:min:max:step];
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

list<UI*>                   UI::fGuiList;

/*
bool                        GTKUI::fInitialized = false;
map<float*, float>          GTKUI::fGuiSize;
map<float*, string>         GTKUI::fTooltip;
*/
