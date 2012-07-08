/************************************************************************
 
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2004-2012 GRAME, Centre National de Creation Musicale
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
class CocoaUI;
class uiCocoaItem;
class uiBox;

/******************************************************************************
 *******************************************************************************
 
 GRAPHIC USER INTERFACE (v2)
 abstract interfaces
 
 *******************************************************************************
 *******************************************************************************/


//=================
// COCOA part
//=================

// Widget assignation type
#define kAssignationNone                0
#define kAssignationAccelX              1
#define kAssignationAccelY              2
#define kAssignationAccelZ              3
#define kAssignationShake               4
#define kAssignationCompass             5

// Current layout mode
#define kHorizontalLayout               0
#define kVerticalLayout                 1
#define kTabLayout                      2

// Global dimensions
#define kWidgetSlice                    50.f
#define kOffsetY                        20.f
#define kSpaceSize                      5.f

// Responders dimensions
// Boxes
#define kStdTabHeight                   40.f
#define kMinBoxWidth                    100.f
#define kMinBoxHeight                   100.f
#define kStdBoxLabelHeight              20.0
#define kStdBoxLabelXOffset             5.0

// Buttons
#define kStdButtonWidth                 100.0
#define kStdButtonHeight                40.0

// Num entry
#define kStdNumEntryWidth               100.0
#define kStdNumEntryHeight              40.0
#define kStdNumEntryLabelWidth          100.0
#define kStdNumEntryLabelHeight         20.0

// Knob
#define kStdKnobWidth                   100.0
#define kStdKnobHeight                  100.0
#define kStdKnobArcWidth                20.0
#define kStdKnobLabelWidth              100.0
#define kStdKnobLabelHeight             20.0

// Slider
#define kMinHorizontalSliderWidth       170.0
#define kStdHorizontalSliderHeight      40.0
#define kStdVerticalSliderWidth         40.0
#define kMinVerticalSliderHeight        170.0
#define kStdSliderLabelWidth            60.0
#define kStdSliderLabelHeight           20.0

// Bargraph
#define kMinHorizontalBargraphWidth     170.0
#define kStdHorizontalBargraphHeight    30.0
#define kStdVerticalBargraphWidth       30.0
#define kMinVerticalBargraphHeight      170.0
#define kStdBargraphLabelWidth          60.0
#define kStdBargraphLabelHeight         20.0

// Routines
CGPoint inBoxPosition2absolutePosition(float x, float y, uiCocoaItem* box);
CGPoint absolutePosition(uiCocoaItem* widget);


// All Cocoa widget classes inheritate from uiCocoaItem, which inheritate from Faust uiItem
class uiCocoaItem : public uiItem
{
    
protected:
    
    NSString*               fName;
    BOOL                    fHidden;
    uiCocoaItem*            fParent;
    float                   fx;
    float                   fy;
    float                   fw;
    float                   fh;
    float                   fAbstractX;
    float                   fAbstractY;
    float                   fAbstractW;
    float                   fAbstractH;
    BOOL                    fSelected;
    int                     fAssignationType;
    float                   fAssignationRefPointX;
    float                   fAssignationRefPointY;
    BOOL                    fAssignationInverse;
    float                   fAssignationSensibility;
    float                   fR;
    float                   fG;
    float                   fB;
    
public:
    
    FIMainViewController*   mainViewController;

    // Default widget parameter
    void resetParameters()
    {
        fAssignationType = kAssignationNone;
        fAssignationRefPointX = 0.;
        fAssignationRefPointY = 0.;
        fAssignationInverse = false;
        fAssignationSensibility = 1.;
        fR = 0.f;
        fG = 0.f;
        fB = 1.f;
    }
    
    // Constructor / Destuctor
    uiCocoaItem(GUI* ui, float* zone, FIMainViewController* controller, const char* name)
    : uiItem(ui, zone), mainViewController(controller)
    {
        fName = [[NSString alloc] initWithString:[NSString stringWithCString:name encoding:NSASCIIStringEncoding]];
        fHidden = false;
        fParent = NULL;
        fx = 0.f;
        fy = 0.f;
        fw = 0.f;
        fh = 0.f;
        fAbstractX = 0.f;
        fAbstractY = 0.f;
        fAbstractW = 0.f;
        fAbstractH = 0.f;
        resetParameters();
        fSelected = false;
    }
    
    ~uiCocoaItem()
    {
        [fName release];
    }
        
    // Getters, setters
    NSString* getName()                                             {return fName;}
    
    virtual void setHidden(BOOL hidden) = 0;
    BOOL isHidden()                                                 {return fHidden;}
    virtual BOOL isHExpandable() = 0;
    virtual BOOL isVExpandable() = 0;
    
    float getX()                                                    {return fx;}
    float getY()                                                    {return fy;}
    float getW()                                                    {return fw;}
    float getH()                                                    {return fh;}
    virtual void setFrame(float x, float y, float w, float h)       {fx = x; fy = y; fw = w; fh = h;}
    
    float getAbstractX()                                            {return fAbstractX;}
    float getAbstractY()                                            {return fAbstractY;}
    float getAbstractW()                                            {return fAbstractW;}
    float getAbstractH()                                            {return fAbstractH;}
    void setAbstractFrame(float x, float y, float w, float h)       {fAbstractX = x; fAbstractY = y; fAbstractW = w; fAbstractH = h;}
    
    void setParent(uiCocoaItem* parent)                             {fParent = parent;}
    
    uiCocoaItem* getParent()                                        {return fParent;}
    
    BOOL isSelected()                                               {return fSelected;}
    virtual void setSelected(BOOL selected)                         {fSelected = selected;}
    
    int getAssignationType()                                        {return fAssignationType;}
    virtual void setAssignationType(int assignationType)            {fAssignationType = assignationType;}
    
    float getAssignationRefPointX()                                 {return fAssignationRefPointX;}
    void setAssignationRefPointX(float assignationRefPointX)        {fAssignationRefPointX = assignationRefPointX;}
    
    float getAssignationRefPointY()                                 {return fAssignationRefPointY;}
    void setAssignationRefPointY(float assignationRefPointY)        {fAssignationRefPointY = assignationRefPointY;}
    
    BOOL getAssignationInverse()                                    {return fAssignationInverse;}
    void setAssignationInverse(BOOL assignationInverse)             {fAssignationInverse = assignationInverse;}
    
    float getAssignationSensibility()                               {return fAssignationSensibility;}
    void setAssignationSensibility(float assignationSensibility)    {fAssignationSensibility = assignationSensibility;}

    
    float getR()                                                    {return fR;}
    float getG()                                                    {return fG;}
    float getB()                                                    {return fB;}
    virtual void setColor(float r, float g, float b)                {fR = r; fG = g; fB = b;}
};


// --------------------------- Box ---------------------------

class uiBox : public uiCocoaItem
{

public:
    
    FIBox*                  fBox;
    FITabView*              fTabView;
    list <uiCocoaItem*>     fWidgetList;        // if kTabLayout : boxes containing each tab elements ; else : elements within box
    BOOL                    fClosed;
    int                     fBoxType;
    float                   fLastX;
    float                   fLastY;
    UILabel*                fLabel;
    
    uiBox(GUI* ui, FIMainViewController* controller, const char* name, int boxType)
    : uiCocoaItem(ui, NULL, controller, name)
    {
        float tabOffset = 0;
        fBoxType = boxType;
        fLastX = 0.f;
        fLastY = 0.f;
        fTabView = nil;
        fLabel = nil;
        
        if (boxType == kTabLayout)
        {
            fTabView = [[[FITabView alloc] initWithDelegate:controller] autorelease];
            fTabView.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
            fTabView.labelColor = [UIColor blueColor];
            fTabView.backgroundColorAlpha = 0.4;
            fTabView.value = 0.f;
            fTabView.autoresizingMask = UIViewAutoresizingNone;
            [controller.dspView addSubview:fTabView];
            tabOffset = kStdTabHeight;
        }

        fClosed = FALSE;
        fBox = [[[FIBox alloc] init] autorelease];
        fBox.color = [UIColor darkGrayColor];
        fBox.autoresizingMask = UIViewAutoresizingNone;
        
        [controller.dspView addSubview:fBox];
        
        if (boxType != kTabLayout)
        {
            fLabel = [[[UILabel alloc] init] autorelease];
            fLabel.font = [UIFont boldSystemFontOfSize:18];
            fLabel.textAlignment = UITextAlignmentLeft;
            fLabel.autoresizingMask = UIViewAutoresizingNone;
            fLabel.text = [NSString stringWithCString:name encoding:NSASCIIStringEncoding];
            fLabel.textColor = [UIColor colorWithWhite:1. alpha:1.];
            fLabel.backgroundColor = [UIColor clearColor];
            [controller.dspView addSubview:fLabel];
            
            fLastY = kStdBoxLabelHeight;
        }
    }
    
    ~uiBox()
    {
        if (fLabel) [fLabel release];
        [fBox release];
    }
    
    BOOL isHExpandable()
    {
        return TRUE;
    }
    
    BOOL isVExpandable()
    {
        return FALSE;
    }
    
    int getNumberOfDirectChildren()
    {
        list<uiCocoaItem*>::iterator    i;
        int                             cpt = 0;
        
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            if ((*i)->getParent() == this)
            {
                cpt++;
            }
        }
        
        return cpt;
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint                         pt = inBoxPosition2absolutePosition(x, y, fParent);
        list<uiCocoaItem*>::iterator    i;
        float                           labelYOffset = 0.f;

        uiCocoaItem::setFrame(x, y, w, h);

        // For tab views : simply resize the tab corresponding box
        if (fTabView)
        {
            fTabView.frame = CGRectMake(pt.x, pt.y, w, kStdTabHeight);
            fBox.frame = CGRectMake(pt.x, pt.y + kStdTabHeight, w, h - kStdTabHeight);
            
            for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
            {
                if ((*i)->getW() != w || (*i)->getW() != h - kStdTabHeight)
                {
                    (*i)->setFrame((*i)->getX(), (*i)->getY(), w, h - kStdTabHeight);
                }
            }
        }
        
        // For vertical and horizontal boxes
        else
        {
            fBox.frame = CGRectMake(pt.x, pt.y, w, h);
            if (fLabel)
            {
                labelYOffset = kStdBoxLabelHeight;
                fLabel.frame = CGRectMake(pt.x + kStdBoxLabelXOffset, pt.y, w - kStdBoxLabelXOffset, labelYOffset);
            }

            for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
            {
                if (fBoxType == kVerticalLayout
                    && (*i)->getW() < w - 2 * kSpaceSize
                    && (*i)->getParent() == this)
                {
                    (*i)->setFrame((*i)->getX(), (*i)->getY(), w - 2 * kSpaceSize, (*i)->getH());
                }
                else if (fBoxType == kHorizontalLayout
                         && (*i)->getH() < h - 2 * kSpaceSize - labelYOffset
                         && (*i)->getParent() == this)
                {
                    (*i)->setFrame((*i)->getX(), (*i)->getY(), (*i)->getW(), h - 2 * kSpaceSize - labelYOffset);
                }
            }
        }
    }
    
    // Returns minimum size used by widgets within the box
    CGSize getContentSize()
    {
        list<uiCocoaItem*>::iterator    i;
        float                           maxW = 0.f;
        float                           maxH = 0.f;
        
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            if ((*i)->getParent() == this)
            {
                maxW = max((*i)->getX() + (*i)->getW(), maxW);
                maxH = max((*i)->getY() + (*i)->getH(), maxH);
            }
        }

        return CGSizeMake(maxW, maxH);
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fBox.hidden = hidden;
        if (fLabel) fLabel.hidden = hidden;
        
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
    
    uiKnob(GUI* ui, FIMainViewController* controller, const char* name, float* zone, float init, float min, float max, float step, BOOL horizontal)
    : uiCocoaItem(ui, zone, controller, name)
    {
        fLabel = [[[UILabel alloc] init] autorelease];
        fLabel.font = [UIFont boldSystemFontOfSize:12];
        fLabel.textAlignment = UITextAlignmentCenter;
        fLabel.text = [NSString stringWithCString:name encoding:NSASCIIStringEncoding];
        fLabel.textColor = [UIColor whiteColor];
        fLabel.backgroundColor = [UIColor clearColor];
        [controller.dspView addSubview:fLabel];
        
        fKnob = [[[FIKnob alloc] initWithDelegate:controller] autorelease];
        fKnob.autoresizingMask = UIViewAutoresizingNone;
        fKnob.labelFont = [UIFont boldSystemFontOfSize:14.0];
        fKnob.labelColor = [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
        fKnob.color = [UIColor colorWithRed:fR green:fG blue:fB alpha:1.f];
        fKnob.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fKnob.min = min;
        fKnob.max = max;
        fKnob.step = step;
        fKnob.value = init;
        fKnob.valueArcWidth = kStdKnobArcWidth;
        fKnob.backgroundColorAlpha = 0.4;
        [controller.dspView addSubview:fKnob];
        
        UILongPressGestureRecognizer *longPressGesture = [[[UILongPressGestureRecognizer alloc] initWithTarget:controller action:@selector(showWidgetPreferencesView:)] autorelease];
        longPressGesture.delegate = controller;
		[fKnob addGestureRecognizer:longPressGesture];
    }
    
    ~uiKnob()
    {
        [fLabel release];
        [fKnob release];
    }
    
    BOOL isHExpandable()
    {
        return FALSE;
    }
    
    BOOL isVExpandable()
    {
        return FALSE;
    }

    void setFrame(float x, float y, float w, float h)
    {
        CGPoint         pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);

        fKnob.frame = CGRectMake(   pt.x + (w - kStdKnobWidth) / 2.f,
                                    pt.y + (h - kStdKnobHeight - kSpaceSize - kStdKnobLabelHeight) / 2.f,
                                    kStdKnobWidth,
                                    kStdKnobHeight);
        
        fLabel.frame = CGRectMake(  pt.x + (w - kStdKnobLabelWidth) / 2.f,
                                    pt.y + (h + kStdKnobHeight - kSpaceSize - kStdKnobLabelHeight) / 2.f + kSpaceSize,
                                    kStdKnobLabelWidth,
                                    kStdKnobLabelHeight);
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden;
        fKnob.hidden = hidden;
    }
    
    void setSelected(BOOL selected)
    {
        uiCocoaItem::setSelected(selected);
        fKnob.selected = selected;
        [fKnob setNeedsDisplay];
    }
    
    void setColor(float r, float g, float b)
    {
        uiCocoaItem::setColor(r, g, b);
        
        fKnob.color = [UIColor colorWithRed:fR green:fG blue:fB alpha:1.f];
        [fKnob setNeedsDisplay];
    }
    
    void setAssignationType(int assignationType)
    {
        uiCocoaItem::setAssignationType(assignationType);
        if (assignationType != kAssignationNone)
        {
            fKnob.assignated = true;
        }
        else
        {
            fKnob.assignated = false;
        }
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
    
    FISlider*               fSlider;
    UILabel*                fLabel;
    BOOL                    fHorizontal;
    
    uiSlider(GUI* ui, FIMainViewController* controller, const char* name, float* zone, float init, float min, float max, float step, BOOL horizontal)
    : uiCocoaItem(ui, zone, controller, name)
    {        
        fLabel = [[[UILabel alloc] init] autorelease];
        fLabel.font = [UIFont boldSystemFontOfSize:12];
        if (horizontal) fLabel.textAlignment = UITextAlignmentRight;
        else fLabel.textAlignment = UITextAlignmentCenter;
        fLabel.text = [NSString stringWithCString:name encoding:NSASCIIStringEncoding];
        fLabel.textColor = [UIColor whiteColor];
        fLabel.backgroundColor = [UIColor clearColor];
        [controller.dspView addSubview:fLabel];
        
        fSlider = [[[FISlider alloc] initWithDelegate:controller] autorelease];
        fSlider.isHorizontalSlider = horizontal;
        fHorizontal = horizontal;
        fSlider.autoresizingMask = UIViewAutoresizingNone;
        fSlider.labelFont = [UIFont boldSystemFontOfSize:14.0];
        fSlider.labelColor = [UIColor colorWithRed:1.0 green:1.0 blue:1.0 alpha:1.0];
        fSlider.color = [UIColor colorWithRed:fR green:fG blue:fB alpha:1.f];
        fSlider.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fSlider.min = min;
        fSlider.max = max;
        fSlider.value = init;
        fSlider.backgroundColorAlpha = 0.4;
        fSlider.handleSize = 50;
        fSlider.step = step;
        [controller.dspView addSubview:fSlider];
        
        UILongPressGestureRecognizer *longPressGesture = [[[UILongPressGestureRecognizer alloc] initWithTarget:controller action:@selector(showWidgetPreferencesView:)] autorelease];
        longPressGesture.delegate = controller;
		[fSlider addGestureRecognizer:longPressGesture];
    }
    
    ~uiSlider()
    {
        [fLabel release];
        [fSlider release];
    }
    
    BOOL isHExpandable()
    {
        if (fHorizontal)
        {
            return TRUE;
        }
        return FALSE;
    }
    
    BOOL isVExpandable()
    {
        if (fHorizontal)
        {
            return FALSE;
        }
        return TRUE;
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint         pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);

        if (fHorizontal)
        {
            fLabel.frame = CGRectMake(  pt.x,
                                        pt.y + (h - kStdSliderLabelHeight) / 2.f,
                                        kStdSliderLabelWidth,
                                        kStdSliderLabelHeight);
            
            fSlider.frame = CGRectMake( pt.x + kStdSliderLabelWidth + kSpaceSize,
                                        pt.y + (h - kStdHorizontalSliderHeight) / 2.f,
                                        w - kStdSliderLabelWidth - kSpaceSize,
                                        kStdHorizontalSliderHeight);
        }
        else
        {
            fSlider.frame = CGRectMake( pt.x + (w - kStdVerticalSliderWidth) / 2.f,
                                        pt.y,
                                        kStdVerticalSliderWidth,
                                        h - kSpaceSize - kStdSliderLabelHeight);
            
            fLabel.frame = CGRectMake(  pt.x + (w - kStdSliderLabelWidth) / 2.f,
                                        pt.y + h - kSpaceSize - kStdSliderLabelHeight,
                                        kStdSliderLabelWidth,
                                        kStdSliderLabelHeight);
        }
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden;
        fSlider.hidden = hidden;
    }
    
    void setColor(float r, float g, float b)
    {
        uiCocoaItem::setColor(r, g, b);
        
        fSlider.color = [UIColor colorWithRed:fR green:fG blue:fB alpha:1.f];
        [fSlider setNeedsDisplay];
    }
    
    void setAssignationType(int assignationType)
    {
        uiCocoaItem::setAssignationType(assignationType);
        if (assignationType != kAssignationNone)
        {
            fSlider.assignated = true;
        }
        else
        {
            fSlider.assignated = false;
        }
        [fSlider setNeedsDisplay];
    }
    
    void setSelected(BOOL selected)
    {
        uiCocoaItem::setSelected(selected);
        fSlider.selected = selected;
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
    
    uiButton(GUI* ui, FIMainViewController* controller, const char* name, float* zone, int type)
    : uiCocoaItem(ui, zone, controller, name)
    {
        fButton = [[[FIButton alloc] initWithDelegate:controller] autorelease];
        fButton.autoresizingMask =  UIViewAutoresizingNone;
        fButton.title = [[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding];
		fButton.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
        fButton.labelColor = [UIColor whiteColor];
        fButton.backgroundColorAlpha = 0.4;
        fButton.type = type;
        fButton.color = [UIColor colorWithRed:fR green:fG blue:fB alpha:1.f];
        [controller.dspView addSubview:fButton];
        
        UILongPressGestureRecognizer *longPressGesture = [[[UILongPressGestureRecognizer alloc] initWithTarget:controller action:@selector(showWidgetPreferencesView:)] autorelease];
        longPressGesture.delegate = controller;
		[fButton addGestureRecognizer:longPressGesture];
    }
    
    ~uiButton()
    {
        [fButton release];
    }

    BOOL isHExpandable()
    {
        return TRUE;
    }
    
    BOOL isVExpandable()
    {
        return FALSE;
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint         pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);
        
        fButton.frame = CGRectMake( pt.x + (w - kStdButtonWidth) / 2.f,
                                    pt.y + (h - kStdButtonHeight) / 2.f,
                                    kStdButtonWidth,
                                    kStdButtonHeight);
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fButton.hidden = hidden;
    }

    void setSelected(BOOL selected)
    {
        uiCocoaItem::setSelected(selected);
        fButton.selected = selected;
        [fButton setNeedsDisplay];
    }
    
    void setColor(float r, float g, float b)
    {
        uiCocoaItem::setColor(r, g, b);
        
        fButton.color = [UIColor colorWithRed:fR green:fG blue:fB alpha:1.f];
        [fButton setNeedsDisplay];
    }
    
    void setAssignationType(int assignationType)
    {
        uiCocoaItem::setAssignationType(assignationType);
        if (assignationType != kAssignationNone)
        {
            fButton.assignated = true;
        }
        else
        {
            fButton.assignated = false;
        }
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
    
    FITextField*        fTextField;
    UILabel*            fLabel;
    
    uiNumEntry(GUI* ui, FIMainViewController* controller, const char* label, float* zone, float init, float min, float max, float step)
    : uiCocoaItem(ui, zone, controller, label)
    {
        fLabel = [[[UILabel alloc] init] autorelease];
        fLabel.font = [UIFont boldSystemFontOfSize:12];
        fLabel.textAlignment = UITextAlignmentCenter;
        fLabel.text = [NSString stringWithCString:label encoding:NSASCIIStringEncoding];
        fLabel.textColor = [UIColor whiteColor];
        fLabel.backgroundColor = [UIColor clearColor];
        [controller.dspView addSubview:fLabel];

        fTextField = [[[FITextField alloc] initWithDelegate:controller] autorelease];
        fTextField.autoresizingMask = UIViewAutoresizingNone;
		fTextField.backgroundColor = [UIColor lightGrayColor];
        fTextField.textColor = [UIColor whiteColor];
        fTextField.labelColor = [UIColor whiteColor];
        fTextField.backgroundColorAlpha = 0.4;
        fTextField.min = min;
        fTextField.max = max;
        fTextField.value = init;
        fTextField.step = step;
        [controller.dspView addSubview:fTextField];
    }
    
    ~uiNumEntry()
    {
        [fTextField release];
    }
    
    BOOL isHExpandable()
    {
        return FALSE;
    }
    
    BOOL isVExpandable()
    {
        return FALSE;
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint         pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);
                
        fTextField.frame = CGRectMake(  pt.x + (w - kStdNumEntryWidth) / 2.f,
                                        pt.y + (h - kStdNumEntryHeight - kSpaceSize - kStdNumEntryLabelHeight) / 2.f,
                                        kStdNumEntryWidth,
                                        kStdNumEntryHeight);
        
        fLabel.frame = CGRectMake(      pt.x + (w - kStdNumEntryLabelWidth) / 2.f,
                                        pt.y + (h + kStdNumEntryHeight - kSpaceSize - kStdNumEntryLabelHeight) / 2.f + kSpaceSize,
                                        kStdNumEntryLabelWidth,
                                        kStdNumEntryLabelHeight);
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden;
        fTextField.hidden = hidden;
    }

    void reflectZone()
    {
        float v = *fZone;
        fCache = v;
        fTextField.value = v;
    }
};


// ------------------------------ Bargraph -----------------------------------

class uiBargraph : public uiCocoaItem
{
    
public:
    
    FIBargraph*             fBargraph;
    UILabel*                fLabel;
    BOOL                    fHorizontal;
    
    uiBargraph(GUI* ui, FIMainViewController* controller, const char* name, float* zone, float min, float max, BOOL horizontal)
    : uiCocoaItem(ui, zone, controller, name)
    {        
        fLabel = [[[UILabel alloc] init] autorelease];
        fLabel.font = [UIFont boldSystemFontOfSize:12];
        if (horizontal) fLabel.textAlignment = UITextAlignmentRight;
        else fLabel.textAlignment = UITextAlignmentCenter;
        fLabel.text = [NSString stringWithCString:name encoding:NSASCIIStringEncoding];
        fLabel.textColor = [UIColor whiteColor];
        fLabel.backgroundColor = [UIColor blackColor];
        [controller.dspView addSubview:fLabel];
        
        fBargraph = [[[FIBargraph alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        fBargraph.autoresizingMask = UIViewAutoresizingNone;
        fHorizontal = horizontal;
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
    
    BOOL isHExpandable()
    {
        if (fHorizontal)
        {
            return TRUE;
        }
        return FALSE;
    }
    
    BOOL isVExpandable()
    {
        if (fHorizontal)
        {
            return FALSE;
        }
        return TRUE;
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint         pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);
        
        if (fHorizontal)
        {
            fLabel.frame = CGRectMake(      pt.x,
                                            pt.y + (h - kStdBargraphLabelHeight) / 2.f,
                                            kStdBargraphLabelWidth,
                                            kStdBargraphLabelHeight);
            
            fBargraph.frame = CGRectMake(   pt.x + kStdBargraphLabelWidth + kSpaceSize,
                                            pt.y + (h - kStdHorizontalBargraphHeight) / 2.f,
                                            w - kStdBargraphLabelWidth - kSpaceSize,
                                            kStdHorizontalBargraphHeight);
        }
        else
        {
            fBargraph.frame = CGRectMake(   pt.x + (w - kStdVerticalBargraphWidth) / 2.f,
                                            pt.y,
                                            kStdVerticalBargraphWidth,
                                            h - kSpaceSize - kStdBargraphLabelHeight);
            
            fLabel.frame = CGRectMake(      pt.x + (w - kStdBargraphLabelWidth) / 2.f,
                                            pt.y + h - kSpaceSize - kStdBargraphLabelHeight,
                                            kStdBargraphLabelWidth,
                                            kStdBargraphLabelHeight);
        }
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden;
        fBargraph.hidden = hidden;
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
    map<float*, string>             fUnit;
    set<float*>                     fKnobSet;
    int                             fCurrentLayoutType;
    
    // Layout management
    
    uiBox* getActiveBox()
    {
        list<uiCocoaItem*>::iterator i;
        
        // Loop on each widgets, from the last
        for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
        {
            if (dynamic_cast<uiBox*>(*i))
            {
                if (!dynamic_cast<uiBox*>(*i)->fClosed)
                {
                    return dynamic_cast<uiBox*>(*i);
                }
            }
        }
        
        i = fWidgetList.begin();
        return dynamic_cast<uiBox*>(*i);
    }
    
    // General rules to place objet
    void computeWidgetFrame(uiCocoaItem* widget)
    {
        uiBox*      parent = dynamic_cast<uiBox*>(widget->getParent());
        float       x = 0.f;
        float       y = 0.f;
        float       w = 0.f;
        float       h = 0.f;
                
        // If no parent : the widget is the main container and is placed at the origin of the view
        if (!parent)
        {
            x = 0.f;
            y = 0.f;
            
            // If main box : no label
            if (dynamic_cast<uiBox*>(widget))
            {
                if (dynamic_cast<uiBox*>(widget)->fLabel)
                {
                    [dynamic_cast<uiBox*>(widget)->fLabel removeFromSuperview];
                    dynamic_cast<uiBox*>(widget)->fLabel = nil;
                    dynamic_cast<uiBox*>(widget)->fLastY = dynamic_cast<uiBox*>(widget)->fLastY - kStdBoxLabelHeight;
                }
            }
        }
        
        // Otherwise, computing (x, y) of the widget within its parent box
        else
        {
            // If the box is a tab content box : no label
            if (parent->fBoxType == kTabLayout)
            {
                if (dynamic_cast<uiBox*>(widget))
                {
                    if (dynamic_cast<uiBox*>(widget)->fLabel)
                    {
                        [dynamic_cast<uiBox*>(widget)->fLabel removeFromSuperview];
                        dynamic_cast<uiBox*>(widget)->fLabel = nil;
                        dynamic_cast<uiBox*>(widget)->fLastY = dynamic_cast<uiBox*>(widget)->fLastY - kStdBoxLabelHeight;
                    }
                }
            }
            
            // Check the current layout mode (eg : the layout mode of widget's parent)
            switch (fCurrentLayoutType)
            {
                // Tab layout mode : widget is the box containing the content of a tab
                case kTabLayout:
                    x = 0.f;
                    y = kStdTabHeight;
                    break;
                    
                // Vertical layout mode
                case kVerticalLayout:
                    x = kSpaceSize;
                    y = parent->fLastY + kSpaceSize;
                    break;
                   
                // Horizontal layout mode
                case kHorizontalLayout:
                    x = parent->fLastX + kSpaceSize;
                    if (parent->fLabel) y = kSpaceSize + kStdBoxLabelHeight;
                    else y = kSpaceSize;
                    break;
                    
                // Shouldn't happen, but if there is a bug, behaves like in vertical default mode
                default:
                    x = kSpaceSize;
                    y = parent->fLastY + kSpaceSize;
                    break;
            }
        }
        
        // Set minimum size to widget, regarding its type
        if (dynamic_cast<uiBox*>(widget))
        {
            if (dynamic_cast<uiBox*>(widget)->fBoxType == kTabLayout)
            {
                w = kMinBoxWidth;
                h = kMinBoxHeight + kStdTabHeight;
            }
            else
            {
                w = kMinBoxWidth;
                if (parent && parent->fLabel)
                {
                    h = kMinBoxHeight + kStdBoxLabelHeight;
                }
                else h = kMinBoxHeight;
            }
        }
        else if (dynamic_cast<uiButton*>(widget))
        {
            w = kStdButtonWidth;
            h = kStdButtonHeight;
        }
        else if (dynamic_cast<uiNumEntry*>(widget))
        {
            w = max(kStdNumEntryWidth, kStdNumEntryLabelWidth);
            h = kStdNumEntryHeight + kSpaceSize + kStdNumEntryLabelHeight;
        }
        else if (dynamic_cast<uiKnob*>(widget))
        {
            w = max(kStdKnobWidth, kStdKnobLabelWidth);
            h = kStdKnobHeight + kSpaceSize + kStdKnobLabelHeight;
        }
        else if (dynamic_cast<uiSlider*>(widget))
        {
            if (dynamic_cast<uiSlider*>(widget)->fHorizontal)
            {
                w = kMinHorizontalSliderWidth + kSpaceSize + kStdSliderLabelWidth;
                h = max(kStdHorizontalSliderHeight, kStdSliderLabelHeight);
            }
            else
            {
                w = max(kStdVerticalSliderWidth, kStdSliderLabelWidth);
                h = kMinVerticalSliderHeight + kSpaceSize + kStdSliderLabelHeight;
            }
        }
        else if (dynamic_cast<uiBargraph*>(widget))
        {
            if (dynamic_cast<uiBargraph*>(widget)->fHorizontal)
            {
                w = kMinHorizontalBargraphWidth + kSpaceSize + kStdBargraphLabelWidth;
                h = max(kStdHorizontalBargraphHeight, kStdBargraphLabelHeight);
            }
            else
            {
                w = max(kStdVerticalBargraphWidth, kStdBargraphLabelWidth);
                h = kMinVerticalBargraphHeight + kSpaceSize + kStdBargraphLabelHeight;
            }
        }
        
        // Place widget in the box
        widget->setFrame(x, y, w, h);
        
        // Refresh last x and last y of the parent box
        if (parent)
        {
            parent->fLastX = x + w;
            parent->fLastY = y + h;            
        }
    }
    
    void refreshLayout(uiCocoaItem* widget)
    {
        uiBox*      parent = dynamic_cast<uiBox*>(widget->getParent());
        CGSize      contentSize;

        if (parent)
        {
            contentSize = parent->getContentSize();

            parent->setFrame(parent->getX(),
                             parent->getY(),
                             contentSize.width + kSpaceSize,
                             contentSize.height + kSpaceSize);
            
            parent->fLastX = widget->getX() + widget->getW();
            parent->fLastY = widget->getY() + widget->getH();
                        
            refreshLayout(parent);
        }
    }
    
    void updateBoxChildren(const char* label, uiCocoaItem* widget)
    {
        list<uiCocoaItem*>::iterator i;
        
        if (fCurrentLayoutType == kTabLayout)
        {
            for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
            {
                if (dynamic_cast<uiBox*>(*i))
                {
                    if (dynamic_cast<uiBox*>(*i)->fBoxType == kTabLayout
                        && dynamic_cast<uiBox*>(*i) != widget
                        && !dynamic_cast<uiBox*>(*i)->fClosed)
                    {   
                        // Add FIButton in the fTabView
                        [dynamic_cast<uiBox*>(*i)->fTabView addButtonWithLabel:[NSString stringWithCString:label encoding:NSASCIIStringEncoding]];
                        
                        // Add uiCocoaItem in the uiBox (*i)
                        dynamic_cast<uiBox*>(*i)->fWidgetList.push_back(widget);                        
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
                    if (    (dynamic_cast<uiBox*>(*i)->fBoxType == kHorizontalLayout
                                || dynamic_cast<uiBox*>(*i)->fBoxType == kVerticalLayout)
                            && dynamic_cast<uiBox*>(*i) != widget)
                    {   
                        // Add uiCocoaItem in the uiBox (*i)
                        dynamic_cast<uiBox*>(*i)->fWidgetList.push_back(widget);
                    }
                }
            }   
            i = fWidgetList.begin();
            if (    (dynamic_cast<uiBox*>(*i)->fBoxType == kHorizontalLayout
                        || dynamic_cast<uiBox*>(*i)->fBoxType == kVerticalLayout)
                    && dynamic_cast<uiBox*>(*i) != widget)
            {
                dynamic_cast<uiBox*>(*i)->fWidgetList.push_back(widget);
            }
        }
    }
    
    void insert(const char* label, uiCocoaItem* widget)
	{
        // Link widget to its parent
        widget->setParent(getActiveBox());
        
        // Add widget in the widgts list
        fWidgetList.push_back(widget);
        
        // Set position of the widget
        computeWidgetFrame(widget);
        
        // Manage boxes and current layout type
        updateBoxChildren(label, widget);        
        
        // Refresh whole layout
        refreshLayout(widget);        
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
        fViewController.dspScrollView.indicatorStyle = UIScrollViewIndicatorStyleWhite;
        
        [window addSubview:viewController.view];
        [window makeKeyAndVisible];
    }
    
    ~CocoaUI()
    {
        [fViewController release];
        [fWindow release];
    }
    
    // Abstract layout : layout computed regardless screen dimensions
    void saveAbstractLayout()
    {
        list<uiCocoaItem*>::iterator    i = fWidgetList.begin();
        
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            (*i)->setAbstractFrame((*i)->getX(), (*i)->getY(), (*i)->getW(), (*i)->getH());
        }
    }
    
    void loadAbstractLayout()
    {
        list<uiCocoaItem*>::iterator    i = fWidgetList.begin();
        
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            (*i)->setFrame((*i)->getAbstractX(), (*i)->getAbstractY(), (*i)->getAbstractW(), (*i)->getAbstractH());
        }
    }
    
    // Function used to place widgets within a box when the horizontal box is too large or vertical box is too high
    void expandBoxesContent()
    {
        list<uiCocoaItem*>::iterator    i = fWidgetList.begin();
        list<uiCocoaItem*>::iterator    j = fWidgetList.begin();
        uiBox*                          box = NULL;
        CGSize                          contentSize;
        float                           labelHeight = 0.f;
        float                           extensibleElementsTotalSize = 0.f;
        float                           fixedElementsTotalSize = 0.f;
        float                           rx = 1.f;
        float                           cpt = 0.f;
        float                           newVal = 0.f;

        // Loop on every boxes of the layout
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            if ((box = dynamic_cast<uiBox*>(*i)))
            {
                // Compute content size, ie minimum size used by widgets within the box
                contentSize = box->getContentSize();
                
                // Expand objects if content height is < than box height (vertical box)
                if (box->fBoxType == kVerticalLayout
                    && contentSize.height + kSpaceSize < box->getH())
                {
                    // Init values
                    extensibleElementsTotalSize = 0.f;
                    fixedElementsTotalSize = 0.f;
                    rx = 1.f;
                    cpt = 0.f;
                    newVal = 0.f;
                    
                    // Compute extensible and fixed heights
                    for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
                    {
                        if ((*j)->getParent() == box)
                        {
                            if ((*j)->isVExpandable())
                            {
                                extensibleElementsTotalSize += (*j)->getH();
                            }
                            else
                            {
                                fixedElementsTotalSize += (*j)->getH();
                            }
                        }
                    }
                    
                    // If there is at least 1 extensible element, elements will take the whole box height
                    if (extensibleElementsTotalSize > 0.)
                    {
                        // Compute extension ratio
                        rx = (box->getH() - fixedElementsTotalSize - (box->getNumberOfDirectChildren() + 1) * kSpaceSize - labelHeight) / extensibleElementsTotalSize;
                        
                        // Replace elements
                        for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
                        {
                            if ((*j)->getParent() == box)
                            {                                
                                if ((*j)->isVExpandable())
                                {
                                    newVal = (*j)->getH() * rx;
                                }
                                else
                                {
                                    newVal = (*j)->getH();
                                }
                                
                                (*j)->setFrame((*j)->getX(),
                                               cpt + kSpaceSize + labelHeight,
                                               (*j)->getW(),
                                               newVal);
                                
                                cpt += newVal + kSpaceSize + labelHeight;
                            }
                        }
                    }
                    
                    // There is no extensible element
                    else
                    {
                        for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
                        {
                            if ((*j)->getParent() == box)
                            {
                                if (box->fLabel) labelHeight = kStdBoxLabelHeight;
                                else labelHeight = 0.f;
                                
                                // Place objects on all the height of the box
                                (*j)->setFrame((*j)->getX(),
                                               ((*j)->getY() - kSpaceSize - labelHeight) * ((box->getH() - 2.f * kSpaceSize - labelHeight) / (contentSize.height - kSpaceSize - labelHeight)) + kSpaceSize + labelHeight,
                                               (*j)->getW(),
                                               (*j)->getH() * ((box->getH() - 2.f * kSpaceSize - labelHeight) / (contentSize.height - kSpaceSize - labelHeight)));
                            }
                        }
                    }
                }
                
                // Expand objects if content width is < than box width (horizontal box)
                else if (box->fBoxType == kHorizontalLayout
                         && contentSize.width + kSpaceSize < box->getW())
                {
                    // Init values
                    extensibleElementsTotalSize = 0.f;
                    fixedElementsTotalSize = 0.f;
                    rx = 1.f;
                    cpt = 0.f;
                    newVal = 0.f;
                    
                    // Compute extensible and fixed widths
                    for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
                    {
                        if ((*j)->getParent() == box)
                        {
                            if ((*j)->isHExpandable())
                            {
                                extensibleElementsTotalSize += (*j)->getW();
                            }
                            else
                            {
                                fixedElementsTotalSize += (*j)->getW();
                            }
                        }
                    }
                    
                    // There is at least 1 extensible element, elements will take the whole box width
                    if (extensibleElementsTotalSize > 0.)
                    {
                        // Compute extension ratio
                        rx = (box->getW() - fixedElementsTotalSize - (box->getNumberOfDirectChildren() + 1) * kSpaceSize) / extensibleElementsTotalSize;
                        
                        // Replace elements
                        for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
                        {
                            if ((*j)->getParent() == box)
                            {                                
                                if ((*j)->isHExpandable())
                                {
                                    newVal = (*j)->getW() * rx;
                                }
                                else
                                {
                                    newVal = (*j)->getW();
                                }
                                
                                (*j)->setFrame(cpt + kSpaceSize,
                                               (*j)->getY(),
                                               newVal,
                                               (*j)->getH());
                                
                                cpt += newVal + kSpaceSize;
                            }
                        }
                    }
                    
                    // There is no extensible element
                    else
                    {
                        for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
                        {
                            if ((*j)->getParent() == box)
                            {
                                // Place objects on all the width of the box
                                (*j)->setFrame(((*j)->getX() - kSpaceSize) * ((box->getW() - 2.f * kSpaceSize) / (contentSize.width - kSpaceSize)) + kSpaceSize,
                                               (*j)->getY(),
                                               (*j)->getW() * ((box->getW() - 2.f * kSpaceSize) / (contentSize.width - kSpaceSize)),
                                               (*j)->getH());
                            }
                        }
                    }
                }
            }
        }
    }
    
    // This function takes abstract layout and adapt it to current screen dimensions
    void adaptLayoutToWindow(float width, float height)
    {
        list<uiCocoaItem*>::iterator    i = fWidgetList.begin();
        list<uiCocoaItem*>::iterator    j = fWidgetList.begin();
        BOOL                            hExpandable = NO;
        BOOL                            vExpandable = NO;
        float                           newWidth = 0.f;
        float                           newHeight = 0.f;
        int                             cpt = 0;
        
        if (dynamic_cast<uiBox*>(*i))
        {
            // Make main box transparent if it is not a tab box
            if (dynamic_cast<uiBox*>(*i)->fBoxType != kTabLayout)
            {
                dynamic_cast<uiBox*>(*i)->fBox.color = [UIColor clearColor];
            }
            
            // Load abstract layout
            loadAbstractLayout();
            
            // Algo : window is h exp if (a) there is at least 1 h exp element in the patch
            // or (b) there is more than 1 column
            // AND window is v exp if (a) there is at least 1 v exp element in the patch
            // or (b) there is more than 1 line
            for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
            {
                if (!dynamic_cast<uiBox*>(*j))
                {
                    if ((*j)->isHExpandable()) hExpandable = TRUE;
                    if ((*j)->isVExpandable()) vExpandable = TRUE;
                }
            }
            
            for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
            {
                if (dynamic_cast<uiBox*>(*j))
                {
                    if (!hExpandable
                        && dynamic_cast<uiBox*>(*j)->fBoxType == kHorizontalLayout
                        && dynamic_cast<uiBox*>(*j)->getNumberOfDirectChildren() > 1)
                    {
                        hExpandable = TRUE;
                    }
                    
                    if (!vExpandable
                        && dynamic_cast<uiBox*>(*j)->fBoxType == kVerticalLayout
                        && dynamic_cast<uiBox*>(*j)->getNumberOfDirectChildren() > 1)
                    {
                        vExpandable = TRUE;
                    }
                }
            }
            
            if (hExpandable) newWidth = max((*i)->getAbstractW(), width);
            else newWidth = (*i)->getAbstractW();
            
            if (vExpandable) newHeight = max((*i)->getAbstractH(), height);
            else newHeight = (*i)->getAbstractH();
            
            // Adapt abstract layout to device and orientation
            (*i)->setFrame((*i)->getX(),
                           (*i)->getY(),
                           newWidth,
                           newHeight);
            
            // Finally, if there's only 1 widget in the whole patch, center it
            for (j = fWidgetList.begin(); j != fWidgetList.end(); j++)
            {
                if (!dynamic_cast<uiBox*>(*j))
                {
                    cpt++;
                }
            }
            
            if (cpt == 1)
            {
                (*i)->setFrame((*i)->getX(),
                               (*i)->getY(),
                               width,
                               height);
            }
        }
        
        expandBoxesContent();
    }
    
    CGRect getBoxAbsoluteFrameForWidget(uiCocoaItem* widget)
    {
        CGPoint pt = absolutePosition(widget);
        return CGRectMake(pt.x, pt.y, widget->getW(), widget->getH());
    }
    
    // Returns the box containing the point
    uiBox* getBoxForPoint(CGPoint pt)
    {
        list<uiCocoaItem*>::iterator i = fWidgetList.begin();
        
        // Loop on each widgets, from the last
        for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
        {
            if (dynamic_cast<uiBox*>(*i))
            {
                if (!(*i)->isHidden()
                    && pt.x >= absolutePosition(*i).x
                    && pt.x <= absolutePosition(*i).x + (*i)->getW()
                    && pt.y >= absolutePosition(*i).y
                    && pt.y <= absolutePosition(*i).y + (*i)->getH())
                {
                    if (dynamic_cast<uiBox*>(*i)->getParent())
                    {
                        if (dynamic_cast<uiBox*>(dynamic_cast<uiBox*>(*i)->getParent())->fBoxType == kTabLayout)
                        {
                            return dynamic_cast<uiBox*>(dynamic_cast<uiBox*>(*i)->getParent());
                        }
                    }
                    
                    return dynamic_cast<uiBox*>(*i);
                }
            }
        }
        
        return dynamic_cast<uiBox*>(*i);
    }
    
    uiBox* getMainBox()
    {
        list<uiCocoaItem*>::iterator i = fWidgetList.begin();
        
        return dynamic_cast<uiBox*>(*i);
    }
    
    bool isKnob(float* zone)
    {
        return fKnobSet.count(zone) > 0;
    }
    
    virtual void openFrameBox(const char* label)
    {}
    virtual void openTabBox(const char* label = "")
    {
        uiCocoaItem* item = new uiBox(this, fViewController, label, kTabLayout);
        insert(label, item);
        fCurrentLayoutType = kTabLayout;
    }
    virtual void openHorizontalBox(const char* label = "")
    {
        uiCocoaItem* item = new uiBox(this, fViewController, label, kHorizontalLayout);
        insert(label, item);
        fCurrentLayoutType = kHorizontalLayout;
    }
    virtual void openVerticalBox(const char* label = "")
    {
        uiCocoaItem* item = new uiBox(this, fViewController, label, kVerticalLayout);
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
        list<uiCocoaItem*>::iterator        i;
        uiBox*                              box = NULL;
        BOOL                                found = false;
        uiBox*                              parent = NULL;
                        
        // Find the last box to close
        for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
        {
            if (dynamic_cast<uiBox*>(*i))
            {
                if (!found)
                {
                    if (!dynamic_cast<uiBox*>(*i)->fClosed)
                    {
                        box = dynamic_cast<uiBox*>(*i);
                        box->close(fWidgetList.size());
                        found = true;
                    }
                }
            }            
        }
        
        if (!found && dynamic_cast<uiBox*>(*i))
        {
            box = dynamic_cast<uiBox*>(*i);
            box->close(fWidgetList.size());
        }
        
        // Find the last layout type
        found = false;
        for (i = fWidgetList.end(); i != fWidgetList.begin(); i--)
        {
            if (dynamic_cast<uiBox*>(*i))
            {
                if (!found)
                {
                    if (!dynamic_cast<uiBox*>(*i)->fClosed)
                    {
                        fCurrentLayoutType = dynamic_cast<uiBox*>(*i)->fBoxType;
                        found = true;
                    }
                }
            }            
        }
        
        if (!found && dynamic_cast<uiBox*>(*i))
        {
            fCurrentLayoutType = dynamic_cast<uiBox*>(*i)->fBoxType;
        }
                
        if (box) parent = dynamic_cast<uiBox*>(box->getParent());    
    }
    
    //virtual void adjustStack(int n);
    
    // -- active widgets
    
    virtual void addButton(const char* label, float* zone)
    {
        uiCocoaItem* item = new uiButton(this, fViewController, label, zone, kPushButtonType);
        insert(label, item);
    }
    virtual void addToggleButton(const char* label, float* zone)
    {
        uiCocoaItem* item = new uiButton(this, fViewController, label, zone, kToggleButtonType);
        insert(label, item);
    }
    virtual void addCheckButton(const char* label, float* zone)
    {
        uiCocoaItem* item = new uiButton(this, fViewController, label, zone, kToggleButtonType);
        insert(label, item);
    }
    virtual void addVerticalKnob(const char* label , float* zone, float init, float min, float max, float step)
	{
        uiCocoaItem* item = new uiKnob(this, fViewController, label, zone, init, min, max, step, false);
        if (dynamic_cast<uiKnob*>(item)->fKnob.suffixe) [dynamic_cast<uiKnob*>(item)->fKnob.suffixe release];
        dynamic_cast<uiKnob*>(item)->fKnob.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
        insert(label, item);
    }
    virtual void addHorizontalKnob(const char* label , float* zone, float init, float min, float max, float step)
	{
        uiCocoaItem* item = new uiKnob(this, fViewController, label, zone, init, min, max, step, true);
        if (dynamic_cast<uiKnob*>(item)->fKnob.suffixe) [dynamic_cast<uiKnob*>(item)->fKnob.suffixe release];
        dynamic_cast<uiKnob*>(item)->fKnob.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
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
            uiCocoaItem* item = new uiSlider(this, fViewController, label, zone, init, min, max, step, false);
            if (dynamic_cast<uiSlider*>(item)->fSlider.suffixe) [dynamic_cast<uiSlider*>(item)->fSlider.suffixe release];
            dynamic_cast<uiSlider*>(item)->fSlider.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
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
            uiCocoaItem* item = new uiSlider(this, fViewController, label, zone, init, min, max, step, true);
            if (dynamic_cast<uiSlider*>(item)->fSlider.suffixe) [dynamic_cast<uiSlider*>(item)->fSlider.suffixe release];
            dynamic_cast<uiSlider*>(item)->fSlider.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
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
            uiCocoaItem* item = new uiNumEntry(this, fViewController, label, zone, init, min, max, step);
            if (dynamic_cast<uiNumEntry*>(item)->fTextField.suffixe) [dynamic_cast<uiNumEntry*>(item)->fTextField.suffixe release];
            dynamic_cast<uiNumEntry*>(item)->fTextField.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
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
        uiCocoaItem* item = new uiBargraph(this, fViewController, label, zone, min, max, true);
        insert(label, item);
    }
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
    {
        uiCocoaItem* item = new uiBargraph(this, fViewController, label, zone, min, max, false);
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
				fUnit[zone] = value ;
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

CGPoint inBoxPosition2absolutePosition(float x, float y, uiCocoaItem* box)
{
    CGPoint     parentBoxOrigin = CGPointMake(0.f, 0.f);
    CGPoint     absolutePosition = CGPointMake(0.f, 0.f);
    uiBox*      parent = NULL;
        
    if (box)
    {
        parent = dynamic_cast<uiBox*>(box->getParent());
        
        if (parent)
        {
            parentBoxOrigin = inBoxPosition2absolutePosition(box->getX(), box->getY(), parent);
        }
    }
    
    absolutePosition = CGPointMake(x + parentBoxOrigin.x, y + parentBoxOrigin.y);
    
    return absolutePosition;
}
                      
CGPoint absolutePosition(uiCocoaItem* widget)
{
    return inBoxPosition2absolutePosition(widget->getX(), widget->getY(), widget->getParent());
}