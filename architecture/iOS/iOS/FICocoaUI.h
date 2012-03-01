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

#import "FIKnob.h"
#import "FISlider.h"
#import "FIButton.h"
#import "FITextField.h"
#import "FIBargraph.h"
#import "FIBox.h"
#import "FITabView.h"

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



#define kWidgetSlice        50.f
#define kOffsetY            20.f

#define kHorizontalLayout   0
#define kVerticalLayout     1
#define kTabLayout          2

#define kStdKnobWidth		100.0
#define kStdKnobHeight      100.0
#define kStdButtonWidth		100.0
#define kStdButtonHeight	40.0



class uiCocoaItem : public uiItem
{
    
protected:
    
    BOOL                fHidden;
    
public:
    
    FIMainViewController* mainViewController;
    
    uiCocoaItem(GUI* ui, float* zone, FIMainViewController* controller)
    : uiItem(ui, zone), mainViewController(controller)
    {
        fHidden = false;
    }
    
    ~uiCocoaItem()
    {
    }
    
    virtual void setHidden(BOOL hidden) = 0;
};


// --------------------------- Box ---------------------------

class uiBox : public uiCocoaItem
{
    
public:
    
    FIBox*              fBox;
    FITabView*          fTabView;
    list <uiCocoaItem*> fWidgetList;
    BOOL                fClosed;
    int                 fBoxType;
    
    uiBox(int index, GUI* ui, FIMainViewController* controller, const char* name, int boxType)
    : uiCocoaItem(ui, NULL, controller)
    {
        float tabOffset = 0;
        fBoxType = boxType;
        
        if (boxType == kTabLayout)
        {
            fTabView = [[[FITabView alloc] initWithDelegate:controller] autorelease];
            float viewWidth = controller.dspView.frame.size.width;
            fTabView.frame = CGRectMake(0.0f, kOffsetY + kWidgetSlice * index, viewWidth, 20.0f);
            
            fTabView.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
            fTabView.labelColor = [UIColor redColor];
            fTabView.backgroundColorAlpha = 0.4;
            fTabView.value = 0.f;
            [controller.dspView addSubview:fTabView];
            
            tabOffset = 20.f;
        }
        else
        {
            fTabView = nil;
        }
        fClosed = FALSE;
        fBox = [[[FIBox alloc] init] autorelease];
        fBox.color = [UIColor blueColor];
        fBox.frame = CGRectMake(0., kOffsetY + kWidgetSlice * index + tabOffset, 1.f, 1.f);
        fBox.autoresizingMask =     UIViewAutoresizingFlexibleWidth |
                                    UIViewAutoresizingFlexibleRightMargin |
                                    UIViewAutoresizingFlexibleLeftMargin;

        [controller.dspView addSubview:fBox];
    }
    
    ~uiBox()
    {
        [fBox release];
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fBox.hidden = hidden;
        
        list<uiCocoaItem*>::iterator i;
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            (*i)->setHidden(hidden);
        }
        
        [fBox setNeedsDisplay];
        if (fTabView)
        {
            fTabView.hidden = hidden;
            [fTabView setNeedsDisplay];
        }
    }
    
    void close(int index)
    {        
        [fBox updateFrame:CGRectMake(fBox.frame.origin.x, fBox.frame.origin.y, mainViewController.dspView.frame.size.width, kOffsetY + kWidgetSlice * index - fBox.frame.origin.y)];
        
        fClosed = TRUE;        
    }
    
    void reflectZone()
    {
        [fBox setNeedsDisplay];
                
        if (fTabView)
        {
            list<uiCocoaItem*>::iterator i;
            int index = 0;
            
            for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
            {
                if (fTabView.value != index)
                {
                    (*i)->setHidden(true);
                }
                else
                {
                    (*i)->setHidden(false);
                }
                ++index;
            }
            [fTabView setNeedsDisplay];
        }
    }
};


// -------------------------- Knob -----------------------------------

class uiKnob : public uiCocoaItem
{   
    
public :
    
    FIKnob*             fKnob;
    UILabel*            fLabel;
    
    uiKnob(int index, GUI* ui, FIMainViewController* controller, const char* name, float* zone, float init, float min, float max, float step, BOOL horizontal)
    : uiCocoaItem(ui, zone, controller)
    {
        float viewWidth = controller.dspView.frame.size.width;
        
        CGRect labelFrame = CGRectMake(0.0, kOffsetY + kWidgetSlice * index - 5.f, 80.0, kStdKnobHeight);
        fLabel = [[UILabel alloc] initWithFrame:labelFrame];
        fLabel.font = [UIFont boldSystemFontOfSize:12];
        fLabel.textAlignment = UITextAlignmentRight;
        fLabel.text = [NSString stringWithCString:name encoding:NSASCIIStringEncoding];
        fLabel.textColor = [UIColor whiteColor];
        fLabel.backgroundColor = [UIColor blackColor];
        [controller.dspView addSubview:fLabel];
        
        fKnob = [[[FIKnob alloc] initWithDelegate:controller] autorelease];
        fKnob.frame = CGRectMake(viewWidth / 2 - kStdKnobWidth / 2, kOffsetY + kWidgetSlice * index - 5.f, kStdKnobWidth, kStdKnobHeight);
        fKnob.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        fKnob.labelFont = [UIFont boldSystemFontOfSize:14.0];
        fKnob.labelColor = [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
        fKnob.color = [UIColor blueColor];
        fKnob.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fKnob.min = min;
        fKnob.max = max;
        fKnob.value = init;
        fKnob.backgroundColorAlpha = 0.4;
        [controller.dspView addSubview:fKnob];
    }
    
    ~uiKnob()
    {
        [fLabel release];
        [fKnob release];
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden;
        fKnob.hidden = hidden;
        [fKnob setNeedsDisplay];
    }
    
    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        fKnob.value = v;
    }
    
};

// -------------------------- Slider -----------------------------------

class uiSlider : public uiCocoaItem
{

public :
    
    FISlider*           fSlider;
    UILabel*            fLabel;
    
    uiSlider(int index, GUI* ui, FIMainViewController* controller, const char* name, float* zone, float init, float min, float max, float step, BOOL horizontal)
    : uiCocoaItem(ui, zone, controller)
    {
        float viewWidth = controller.dspView.frame.size.width;
        
        CGRect labelFrame = CGRectMake(0.0, kOffsetY + kWidgetSlice * index - 5.f, 80.0, 30.0);
        fLabel = [[UILabel alloc] initWithFrame:labelFrame];
        fLabel.font = [UIFont boldSystemFontOfSize:12];
        fLabel.textAlignment = UITextAlignmentRight;
        fLabel.text = [NSString stringWithCString:name encoding:NSASCIIStringEncoding];
        fLabel.textColor = [UIColor whiteColor];
        fLabel.backgroundColor = [UIColor blackColor];
        [controller.dspView addSubview:fLabel];
        
        fSlider = [[[FISlider alloc] initWithDelegate:controller] autorelease];
        if ((fSlider.isHorizontalSlider = horizontal))
        {
            fSlider.frame = CGRectMake(85.0f, kOffsetY + kWidgetSlice * index, viewWidth - 85.0f - 5.f, 20.0f);
        }
        else
        {
            fSlider.frame = CGRectMake(85.0f, kOffsetY + kWidgetSlice * index, 20.0f, 170.0f);
        }
        fSlider.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin;
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
        [fLabel release];
        [fSlider release];
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden;
        fSlider.hidden = hidden;
        [fSlider setNeedsDisplay];
    }
    
    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        fSlider.value = v;
    }
};


// --------------------------- Press button ---------------------------

class uiButton : public uiCocoaItem
{
    
public:
    
    FIButton*           fButton;
    
    uiButton(int index, GUI* ui, FIMainViewController* controller, const char* name, float* zone, int type)
    : uiCocoaItem(ui, zone, controller)
    {
        float viewWidth = controller.dspView.frame.size.width;
        
        fButton = [[[FIButton alloc] initWithDelegate:controller] autorelease];
		fButton.frame = CGRectMake(viewWidth / 2 - kStdButtonWidth/2, kOffsetY + kWidgetSlice * index - 5.f, kStdButtonWidth, kStdButtonHeight);
        fButton.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        fButton.title = [[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding];
		fButton.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fButton.labelColor = [UIColor whiteColor];
        fButton.backgroundColorAlpha = 0.4;
        fButton.type = type;
        [controller.dspView addSubview:fButton];
    }
    
    ~uiButton()
    {
        [fButton release];
    }

    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fButton.hidden = hidden;
        [fButton setNeedsDisplay];
    }

    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        if (fButton.type == kToggleButtonType) fButton.value = v;
    }
};


// ------------------------------ Num Entry -----------------------------------

class uiNumEntry : public uiCocoaItem
{
    
public:
    
    FITextField*            fTextField;
    
    uiNumEntry(int index, GUI* ui, FIMainViewController* controller, const char* label, float* zone, float init, float min, float max, float step)
    : uiCocoaItem(ui, zone, controller)
    {
        float viewWidth = controller.dspView.frame.size.width;
        fTextField = [[[FITextField alloc] initWithDelegate:controller] autorelease];
        [fTextField setFrame:CGRectMake(viewWidth / 2 - kStdButtonWidth/2, kOffsetY + kWidgetSlice * index - 5.f, kStdButtonWidth, kStdButtonHeight)];
        fTextField.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
		fTextField.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fTextField.labelColor = [UIColor whiteColor];
        fTextField.backgroundColorAlpha = 0.4;        
        fTextField.min = min;
        fTextField.max = max;
        fTextField.value = init;
        [controller.dspView addSubview:fTextField];
    }
    
    ~uiNumEntry()
    {
        [fTextField release];
    }

    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fTextField.hidden = hidden;
        [fTextField setNeedsDisplay];
    }

    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        fTextField.value = v;
    }
};


// ------------------------------ Num Entry -----------------------------------

class uiBargraph : public uiCocoaItem
{
    
public:
    
    FIBargraph*             fBargraph;
    UILabel*                fLabel;
    
    uiBargraph(int index, GUI* ui, FIMainViewController* controller, const char* name, float* zone, float min, float max, BOOL horizontal)
    : uiCocoaItem(ui, zone, controller)
    {
        float viewWidth = controller.dspView.frame.size.width;
       
        CGRect labelFrame = CGRectMake(0.0, kOffsetY + kWidgetSlice * index - 5.f, 80.0, 30.0);
        fLabel = [[UILabel alloc] initWithFrame:labelFrame];
        fLabel.font = [UIFont boldSystemFontOfSize:12];
        fLabel.textAlignment = UITextAlignmentRight;
        fLabel.text = [NSString stringWithCString:name encoding:NSASCIIStringEncoding];
        fLabel.textColor = [UIColor whiteColor];
        fLabel.backgroundColor = [UIColor blackColor];
        [controller.dspView addSubview:fLabel];
        
        if (horizontal)
        {
            fBargraph = [[[FIBargraph alloc] initWithFrame:CGRectMake(85.0f, kOffsetY + kWidgetSlice * index, viewWidth - 85.0f - 5.f, 20.0f)] autorelease];
        }
        else
        {
            fBargraph = [[[FIBargraph alloc] initWithFrame:CGRectMake(85.0f, kOffsetY + kWidgetSlice * index, 20.0f, 170.0f)] autorelease];
        }
        fBargraph.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin;
        fBargraph.value = 0.f;
        fBargraph.minLimit = min;
        fBargraph.maxLimit = max;
        fBargraph.numBars = 8;
        fBargraph.holdPeak = false;
        [controller.dspView addSubview:fBargraph];
    }
    
    ~uiBargraph()
    {
        [fLabel release];
        [fBargraph release];
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden;
        fBargraph.hidden = hidden;
        [fBargraph setNeedsDisplay];
    }
    
    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        fBargraph.value = v;
    }
};


// ------------------------------ CocoaUI -----------------------------------

class CocoaUI : public GUI
{
    
public:
    list <uiCocoaItem*>             fWidgetList;
    
private:
    
    UIWindow*                       fWindow;
    FIMainViewController*           fViewController;
    MY_Meta*                        fMetadata;
    set<float*>                     fKnobSet;
    int                             fCurrentLayoutType;
    
    void insert(const char* label, uiCocoaItem* widget)
	{
        list<uiCocoaItem*>::iterator i;
        
        fWidgetList.push_back(widget);
        [fViewController.dspView setContentSize:CGSizeMake(320, kWidgetSlice * fWidgetList.size() + 100.f)];
        
        // Manage boxes and current layout type
        if (fCurrentLayoutType == kTabLayout)
        {                        
            for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
            {
                if (dynamic_cast<uiBox*>(*i))
                {
                    if (dynamic_cast<uiBox*>(*i)->fBoxType == kTabLayout
                        && dynamic_cast<uiBox*>(*i) != widget)
                    {   
                        // Add FIButton in the fTabView
                        [dynamic_cast<uiBox*>(*i)->fTabView addButtonWithLabel:[NSString stringWithCString:label encoding:NSASCIIStringEncoding]];
                        
                        // Add uiCocoaItem in the uiBox (*i)
                        dynamic_cast<uiBox*>(*i)->fWidgetList.push_back(widget);
                        
                        return;
                    }
                }
            }   
            i = fWidgetList.begin();
            if (dynamic_cast<uiBox*>(*i)->fBoxType == kTabLayout
                && dynamic_cast<uiBox*>(*i) != widget)
            {
                [dynamic_cast<uiBox*>(*i)->fTabView addButtonWithLabel:[NSString stringWithCString:label encoding:NSASCIIStringEncoding]];
                
                dynamic_cast<uiBox*>(*i)->fWidgetList.push_back(widget);
            }
        }
        else
        {            
            for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
            {
                if (dynamic_cast<uiBox*>(*i))
                {
                    if ((dynamic_cast<uiBox*>(*i)->fBoxType == kHorizontalLayout
                        || dynamic_cast<uiBox*>(*i)->fBoxType == kVerticalLayout)
                        && dynamic_cast<uiBox*>(*i) != widget)
                    {   
                        // Add uiCocoaItem in the uiBox (*i)
                        dynamic_cast<uiBox*>(*i)->fWidgetList.push_back(widget);
                        
                        return;
                    }
                }
            }   
            i = fWidgetList.begin();
            if ((dynamic_cast<uiBox*>(*i)->fBoxType == kHorizontalLayout
                 || dynamic_cast<uiBox*>(*i)->fBoxType == kVerticalLayout)
                && dynamic_cast<uiBox*>(*i) != widget)
            {
                dynamic_cast<uiBox*>(*i)->fWidgetList.push_back(widget);
            }
        }
    }
    
public:
    
    // -- Labels and metadata
    
    // virtual void declare (float* zone, const char* key, const char* value);
    // virtual int checkLabelOptions (GtkWidget* widget, const string& fullLabel, string& simplifiedLabel);
    // virtual void checkForTooltip (float* zone, GtkWidget* widget);
    
    // -- layout groups
    
    CocoaUI(UIWindow* window, FIMainViewController* viewController, MY_Meta* metadata)
    {
        fCurrentLayoutType = kVerticalLayout;
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
    
    bool isKnob(float* zone)
    {
        return fKnobSet.count(zone) > 0;
    }
    
    virtual void openFrameBox(const char* label)
    {}
    virtual void openTabBox(const char* label = "")
    {
        uiCocoaItem* item = new uiBox(fWidgetList.size(), this, fViewController, label, kTabLayout);
        insert(label, item);
        fCurrentLayoutType = kTabLayout;
    }
    virtual void openHorizontalBox(const char* label = "")
    {
        uiCocoaItem* item = new uiBox(fWidgetList.size(), this, fViewController, label, kHorizontalLayout);
        insert(label, item);
        fCurrentLayoutType = kHorizontalLayout;
    }
    virtual void openVerticalBox(const char* label = "")
    {
        uiCocoaItem* item = new uiBox(fWidgetList.size(), this, fViewController, label, kVerticalLayout);
        insert(label, item);
        fCurrentLayoutType = kVerticalLayout;
    }
    
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
    {
        list<uiCocoaItem*>::iterator i;
        BOOL found = false;
        
        for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
        {
            if (dynamic_cast<uiBox*>(*i))
            {
                if (!dynamic_cast<uiBox*>(*i)->fClosed)
                {
                    dynamic_cast<uiBox*>(*i)->close(fWidgetList.size());
                    found = true;
                }
            }
        }

        if (!found && dynamic_cast<uiBox*>(*i))
        {
            dynamic_cast<uiBox*>(*i)->close(fWidgetList.size());
            found = true;
        }
        
        // Find previous mode
        found = false;
        for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
        {
            if (dynamic_cast<uiBox*>(*i))
            {
                if (!dynamic_cast<uiBox*>(*i)->fClosed)
                {
                    dynamic_cast<uiBox*>(*i)->close(fWidgetList.size());
                    found = true;
                }
            }
        }
        
        if (!found && dynamic_cast<uiBox*>(*i)) 
        {
            dynamic_cast<uiBox*>(*i)->close(fWidgetList.size());
            found = true;
        }
        
        if (found && dynamic_cast<uiBox*>(*i)) fCurrentLayoutType = dynamic_cast<uiBox*>(*i)->fBoxType;
        else fCurrentLayoutType = kVerticalLayout;
    }
    
    //virtual void adjustStack(int n);
    
    // -- active widgets
    
    virtual void addButton(const char* label, float* zone)
    {
        uiCocoaItem* item = new uiButton(fWidgetList.size(), this, fViewController, label, zone, kPushButtonType);
        insert(label, item);
    }
    virtual void addToggleButton(const char* label, float* zone)
    {
        uiCocoaItem* item = new uiButton(fWidgetList.size(), this, fViewController, label, zone, kToggleButtonType);
        insert(label, item);
    }
    virtual void addCheckButton(const char* label, float* zone)
    {
        uiCocoaItem* item = new uiButton(fWidgetList.size(), this, fViewController, label, zone, kToggleButtonType);
        insert(label, item);
    }
    virtual void addVerticalKnob(const char* label , float* zone, float init, float min, float max, float step)
	{
        uiCocoaItem* item = new uiKnob(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step, false);
        insert(label, item);
    }
    virtual void addHorizontalKnob(const char* label , float* zone, float init, float min, float max, float step)
	{
        uiCocoaItem* item = new uiKnob(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step, true);
        insert(label, item);
    }
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        if (isKnob(zone))
        {
            addVerticalKnob(label, zone, init, min, max, step);
        }
        else
        {
            uiCocoaItem* item = new uiSlider(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step, false);
            insert(label, item);
        }
    }
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        if (isKnob(zone))
        {
            addHorizontalKnob(label, zone, init, min, max, step);
        }
        else
        {
            uiCocoaItem* item = new uiSlider(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step, true);
            insert(label, item);
        }
    }
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        if (isKnob(zone))
        {
            addVerticalKnob(label, zone, init, min, max, step);
        }
        else
        {
            uiCocoaItem* item = new uiNumEntry(fWidgetList.size(), this, fViewController, label, zone, init, min, max, step);
            insert(label, item);
        }
    }
    
    // -- passive display widgets
    
    virtual void addNumDisplay(const char* label, float* zone, int precision)
    {}
    virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max)
    {}
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max)
    {
        uiCocoaItem* item = new uiBargraph(fWidgetList.size(), this, fViewController, label, zone, min, max, true);
        insert(label, item);
    }
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
    {
        uiCocoaItem* item = new uiBargraph(fWidgetList.size(), this, fViewController, label, zone, min, max, false);
        insert(label, item);
    }
    
    virtual void show()
    {}
    virtual void run()
    {}
    
    virtual void declare(float* zone, const char* key, const char* value)
    {
		if (zone == 0)
        {
			// special zone 0 means group metadata
			/*if (strcmp(key,"tooltip")==0)
            {
				// only group tooltip are currently implemented
				gGroupTooltip = formatTooltip(30, value);
			}*/
		}
        else
        {
			if (strcmp(key,"size") == 0)
            {
				//fGuiSize[zone]=atof(value);
			}
			else if (strcmp(key,"tooltip") == 0)
            {
				//fTooltip[zone] = formatTooltip(30, value) ;
			}
			else if (strcmp(key,"unit") == 0)
            {
				//fUnit[zone] = value ;
			}
			else if (strcmp(key,"style") == 0)
            {
                // else if ((strcmp(key,"style")==0) || (strcmp(key,"type")==0)) {
				if (strcmp(value,"knob") == 0)
                {
					fKnobSet.insert(zone);
				}
                else if (strcmp(value,"led") == 0)
                {
					//fLedSet.insert(zone);
				}
			}
		}
	}
    
};


// global static fields

list<GUI*>                   GUI::fGuiList;

/*
 bool                        GTKUI::fInitialized = false;
 map<float*, float>          GTKUI::fGuiSize;
 map<float*, string>         GTKUI::fTooltip;
 */
