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
#define kAssignationGyroX               4
#define kAssignationGyroY               5
#define kAssignationGyroZ               6

#define kCurve1                         0
#define kCurve2                         1
#define kCurve3                         2
#define kCurve4                         3

// Current layout mode
#define kHorizontalLayout               0
#define kVerticalLayout                 1
#define kTabLayout                      2
#define kColorLayout                    3

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
#define kStdLedWidth                    270.0
#define kStdLedHeight                   270.0
#define kStdBargraphLabelWidth          60.0
#define kStdBargraphLabelHeight         20.0

// Routines
CGPoint inBoxPosition2absolutePosition(float x, float y, uiCocoaItem* box);
CGPoint absolutePosition(uiCocoaItem* widget);

// All Cocoa widget classes inheritate from uiCocoaItem, which inheritate from Faust uiItem
class uiCocoaItem : public uiItem
{
    
protected:
    
    static int              gItemCount;
    int                     fItemCount;
    
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
    
    int                     fInitAssignationType;
    int                     fInitAssignationCurve;
    
    float                   fInitR;
    float                   fInitG;
    float                   fInitB;
    
    float                   fInitMinCurve;
    float                   fInitMidCurve;
    float                   fInitMaxCurve;
    
    int                     fAssignationType;
    int                     fAssignationCurve;
    
    float                   fMinCurve;
    float                   fMidCurve;
    float                   fMaxCurve;
    
    float                   fR;
    float                   fG;
    float                   fB;
    BOOL                    fHideOnGUI;
    
public:
    
    UILabel*                fLabel;
    float                   fInit;
    
    // Default widget parameter
    void resetParameters()
    {
        fAssignationType = fInitAssignationType;
        fAssignationCurve = fInitAssignationCurve;
        
        fR = fInitR;
        fG = fInitG;
        fB = fInitB;
        
        fMinCurve = fInitMinCurve;
        fMidCurve = fInitMidCurve;
        fMaxCurve = fInitMaxCurve;
    }
    
    // Constructor / Destuctor
    uiCocoaItem(GUI* ui, float* zone, FIMainViewController* controller, const char* name);
    
    ~uiCocoaItem()
    {
        [fName release];
    }
        
    // Getters, setters
    int getItemCount()                                                  {return fItemCount;}
    
    NSString* getName()                                                 {return fName;}
    
    virtual void resetInitialValue() = 0;
    
    virtual void setHidden(BOOL hidden) = 0;
    BOOL isHidden()                                                     {return fHidden;}
    virtual BOOL isHExpandable() = 0;
    virtual BOOL isVExpandable() = 0;
    
    virtual void enableLongPressGestureRecognizer(BOOL enable) = 0;
    
    float getX()                                                        {return fx;}
    float getY()                                                        {return fy;}
    float getW()                                                        {return fw;}
    float getH()                                                        {return fh;}
    virtual void setFrame(float x, float y, float w, float h)           {fx = x; fy = y; fw = w; fh = h;}
    
    float getAbstractX()                                                {return fAbstractX;}
    float getAbstractY()                                                {return fAbstractY;}
    float getAbstractW()                                                {if (fHideOnGUI) return 0; else return fAbstractW;}
    float getAbstractH()                                                {if (fHideOnGUI) return 0; else return fAbstractH;}
    void setAbstractFrame(float x, float y, float w, float h)           {fAbstractX = x; fAbstractY = y; fAbstractW = w; fAbstractH = h;}
    
    void setParent(uiCocoaItem* parent)                                 {fParent = parent;}
    
    uiCocoaItem* getParent()                                            {return fParent;}
    
    BOOL isSelected()                                                   {return fSelected;}
    virtual void setSelected(BOOL selected)                             {fSelected = selected;}

    int getInitAssignationType()                                        {return fInitAssignationType;}
    void setInitAssignationType(int assignationType)                    {fInitAssignationType = assignationType; setAssignationType(assignationType);}

    int getAssignationType()                                            {return fAssignationType;}
    virtual void setAssignationType(int assignationType)                {fAssignationType = assignationType;}
    
    int getInitAssignationCurve()                                       {return fInitAssignationCurve;}
    void setInitAssignationCurve(int assignationCurve)                  {fInitAssignationCurve = assignationCurve; setAssignationCurve(assignationCurve);}

    int getAssignationCurve()                                           {return fAssignationCurve;}
    virtual void setAssignationCurve(int assignationCurve)              {fAssignationCurve = assignationCurve;}
    
    float getCurveMin()                                                 {return fMinCurve;}
    virtual void setCurveMin(float minCurve)                            {fMinCurve = minCurve;}
    
    float getCurveMid()                                                 {return fMidCurve;}
    virtual void setCurveMid(float midCurve)                            {fMidCurve = midCurve;}
   
    float getCurveMax()                                                 {return fMaxCurve;}
    virtual void setCurveMax(float maxCurve)                            {fMaxCurve = maxCurve;}
    
    float getInitCurveMin()                                             {return fInitMinCurve;}
    float getInitCurveMid()                                             {return fInitMidCurve;}
    float getInitCurveMax()                                             {return fInitMaxCurve;}
    
    virtual void setCurve(float min, float mid, float max)
    {
        fMinCurve = min; fMidCurve = mid; fMaxCurve = max;
    }
    
    virtual void setInitCurve(float min, float mid, float max)
    {
        fInitMinCurve = min; fInitMidCurve = mid; fInitMaxCurve = max;
    }
  
    float getInitR()                                                    {return fInitR;}
    float getInitG()                                                    {return fInitG;}
    float getInitB()                                                    {return fInitB;}
    virtual void setInitColor(float r, float g, float b)                {fInitR = r; fInitG = g; fInitB = b; setColor(r, g, b);}

    float getR()                                                        {return fR;}
    float getG()                                                        {return fG;}
    float getB()                                                        {return fB;}
    virtual void setColor(float r, float g, float b)                    {fR = r; fG = g; fB = b;}
    
    void setHideOnGUI(BOOL hideOnGUI)                                   {fHideOnGUI = hideOnGUI; if (fLabel) fLabel.hidden = hideOnGUI;}
    BOOL getHideOnGUI()                                                 {return fHideOnGUI;}
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
    static float            gDummy;
    
    uiBox(GUI* ui, FIMainViewController* controller, const char* name, int boxType)
    : uiCocoaItem(ui, &gDummy, controller, name)
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
        
        if (boxType == kColorLayout) {
            fBox.backgroundColor = [UIColor whiteColor];
        }
        
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
        if (fTabView) [fTabView release];
        [fBox release];
    }
    
    void resetInitialValue()
    {
    }
    
    BOOL isHExpandable()
    {
        return TRUE;
    }
    
    BOOL isVExpandable()
    {
        return FALSE;
    }
    
    void enableLongPressGestureRecognizer(BOOL enable)
    {
        // Do nothing
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
    
    void setColor(int color)
    {
        CGFloat red = CGFloat(255 & (color >> 16))/255.;
        CGFloat green = CGFloat(255 & (color >> 8))/255.;
        CGFloat blue = CGFloat(255 & (color >> 0))/255.;
        fBox.backgroundColor =  [UIColor colorWithRed:red green:green blue:blue alpha:1.f];
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint                         pt = inBoxPosition2absolutePosition(x, y, fParent);
        list<uiCocoaItem*>::iterator    i;
        float                           labelYOffset = 0.f;

        if (fBoxType == kColorLayout) {
            // Hack to force full screen layout even in 'portrait' only mode
            w = h = std::max(w, h);
        } else {
            uiCocoaItem::setFrame(x, y, w, h);
        }

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
        fBox.hidden = hidden || getHideOnGUI();
        if (fLabel) fLabel.hidden = hidden || getHideOnGUI();
        
        list<uiCocoaItem*>::iterator i;
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            (*i)->setHidden(hidden);
        }
        
        [fBox setNeedsDisplay];
        if (fTabView)
        {
            fTabView.hidden = hidden || getHideOnGUI();
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

// Constructor / Destuctor
uiCocoaItem::uiCocoaItem(GUI* ui, float* zone, FIMainViewController* controller, const char* name)
: uiItem(ui, zone)
{
    fName = [[NSString alloc] initWithString:[NSString stringWithCString:name encoding:NSASCIIStringEncoding]];
    fLabel = nil;
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
    
    fSelected = false;
    
    fInitAssignationType = kAssignationNone;
    fInitAssignationCurve = kAssignationNone;
    
    fInitR = 0.f;
    fInitG = 0.f;
    fInitB = 1.f;
    
    fInitMinCurve = -100.f;
    fInitMidCurve = 0.f;
    fInitMaxCurve = 100.f;
    
    fHideOnGUI = false;
    fInit = 0.f;
    if (zone != &uiBox::gDummy) {
        fItemCount = gItemCount++;
    } else {
        fItemCount = -1;
    }
    
    resetParameters();
}

// -------------------------- Knob -----------------------------------

class uiKnob : public uiCocoaItem
{
    
public :
    
    FIKnob*                         fKnob;
    UILongPressGestureRecognizer*   fLongPressGesture;
    
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
        fInit = init;
        fKnob.value = init;
        fKnob.valueArcWidth = kStdKnobArcWidth;
        fKnob.backgroundColorAlpha = 0.4;
        [controller.dspView addSubview:fKnob];
                
        fLongPressGesture = [[UILongPressGestureRecognizer alloc] initWithTarget:controller action:@selector(showWidgetPreferencesView:)];
        fLongPressGesture.delegate = controller;
		[fKnob addGestureRecognizer:fLongPressGesture];
    }
    
    ~uiKnob()
    {
        [fLabel release];
        [fKnob release];
        [fLongPressGesture release];
    }
    
    void resetInitialValue()
    {
        fKnob.value = fInit;
    }
    
    BOOL isHExpandable()
    {
        return FALSE;
    }
    
    BOOL isVExpandable()
    {
        return FALSE;
    }

    void enableLongPressGestureRecognizer(BOOL enable)
    {
        if (enable)
        {
            [fKnob addGestureRecognizer:fLongPressGesture];
        }
        else
        {
            [fKnob removeGestureRecognizer:fLongPressGesture];
        }
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint         pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);

        fKnob.frame = CGRectMake(pt.x + (w - kStdKnobWidth) / 2.f,
                                pt.y + (h - kStdKnobHeight - kSpaceSize - kStdKnobLabelHeight) / 2.f,
                                kStdKnobWidth,
                                kStdKnobHeight);
        
        fLabel.frame = CGRectMake(pt.x + (w - kStdKnobLabelWidth) / 2.f,
                                pt.y + (h + kStdKnobHeight - kSpaceSize - kStdKnobLabelHeight) / 2.f + kSpaceSize,
                                kStdKnobLabelWidth,
                                kStdKnobLabelHeight);
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden || getHideOnGUI();
        fKnob.hidden = hidden || getHideOnGUI();
    }
    
    void setSelected(BOOL selected)
    {
        uiCocoaItem::setSelected(selected);
        fKnob.responderSelected = selected;
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
    
    FISlider*                       fSlider;
    BOOL                            fHorizontal;
    UILongPressGestureRecognizer*   fLongPressGesture;
    
    uiSlider(GUI* ui, FIMainViewController* controller, const char* name, float* zone, float init, float min, float max, float step, BOOL horizontal, const char* menu = NULL)
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
        fInit = init;
        fSlider.value = init;
        fSlider.backgroundColorAlpha = 0.4;
        fSlider.handleSize = 50;
        fSlider.step = step;
        [controller.dspView addSubview:fSlider];
        fLongPressGesture = [[UILongPressGestureRecognizer alloc] initWithTarget:controller action:@selector(showWidgetPreferencesView:)];
        fLongPressGesture.delegate = controller;
		[fSlider addGestureRecognizer:fLongPressGesture];
        
        // Menu
        if (menu) {
            const char* p = menu;
            vector<string> names;
            vector<double> values;
            parseMenuList(p, names, values);
            fSlider.fMenuItemNames = names;
            fSlider.fMenuItemValues = values;
        }
    }
    
    ~uiSlider()
    {
        [fLabel release];
        [fSlider release];
        [fLongPressGesture release];
    }
    
    void resetInitialValue()
    {
        fSlider.value = fInit;
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
    
    void enableLongPressGestureRecognizer(BOOL enable)
    {        
        if (enable)
        {
            [fSlider addGestureRecognizer:fLongPressGesture];            
        }
        else
        {
            [fSlider removeGestureRecognizer:fLongPressGesture];
        }
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
        fLabel.hidden = hidden || getHideOnGUI();
        fSlider.hidden = hidden || getHideOnGUI();
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
        fSlider.responderSelected = selected;
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
    
    FIButton* fButton;
    float fValue;  // Specific value to be triggered by the button
    //UILongPressGestureRecognizer*   fLongPressGesture;
    
    uiButton(GUI* ui, FIMainViewController* controller, const char* name, float* zone, int type, float value = FLT_MAX)
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
        
        fValue = value;
        
        //fLongPressGesture = [[UILongPressGestureRecognizer alloc] initWithTarget:controller action:@selector(showWidgetPreferencesView:)];
        //fLongPressGesture.delegate = controller;
		//[fButton addGestureRecognizer:fLongPressGesture];
    }
    
    ~uiButton()
    {
        [fButton release];
        //[fLongPressGesture release];
    }

    void resetInitialValue()
    {}
    
    void setOn()
    {
        [fButton setOn];
    }

    BOOL isHExpandable()
    {
        return TRUE;
    }
    
    BOOL isVExpandable()
    {
        return FALSE;
    }
    
    void enableLongPressGestureRecognizer(BOOL enable)
    {
        /*if (enable)
        {
            [fButton addGestureRecognizer:fLongPressGesture];
        }
        else
        {
            [fButton removeGestureRecognizer:fLongPressGesture];
        }*/
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);
        
        fButton.frame = CGRectMake(pt.x + (w - kStdButtonWidth) / 2.f,
                                    pt.y + (h - kStdButtonHeight) / 2.f,
                                    kStdButtonWidth,
                                    kStdButtonHeight);
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fButton.hidden = hidden || getHideOnGUI();
    }

    void setSelected(BOOL selected)
    {
        uiCocoaItem::setSelected(selected);
        fButton.responderSelected = selected;
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
    
    void modifyZone(float value)
    {
        // Radio button mode 
        if (fButton.type == kCheckButtonType && fValue != FLT_MAX) {
            if (value == 1.0f) {
                fCache = fValue;
                if (*fZone != fValue) {
                    *fZone = fValue;
                }
            }
        } else {
            fCache = value;
            if (*fZone != value) {
                *fZone = value;
                fGUI->updateZone(fZone);
            }
        }
    }
    
    void reflectZone()
    {
        float v = *fZone;
        
        // Radio button mode
        if ((fButton.type == kCheckButtonType) && (fValue != FLT_MAX)) {
            fButton.value = (v == fValue) ? 1.f : 0.f;
        } else {
            fCache = v;
            if (fButton.type == kToggleButtonType) fButton.value = v;
        }
    }
   
};

// ------------------------------ Num Entry -----------------------------------

class uiNumEntry : public uiCocoaItem
{
    
public:
    
    FITextField* fTextField;
    
    uiNumEntry(GUI* ui, FIMainViewController* controller, const char* label, float* zone, float init, float min, float max, float step,const char* menu = NULL)
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
        fInit = init;
        fTextField.value = init;
        fTextField.step = step;
        [controller.dspView addSubview:fTextField];
        
        // Menu
        if (menu) {
            const char* p = menu;
            vector<string> names;
            vector<double> values;
            parseMenuList(p, names, values);
            fTextField.fMenuItemNames = names;
            fTextField.fMenuItemValues = values;
        }
    }
    
    ~uiNumEntry()
    {
        [fTextField release];
    }
    
    void resetInitialValue()
    {
        fTextField.value = fInit;
    }
    
    BOOL isHExpandable()
    {
        return FALSE;
    }
    
    BOOL isVExpandable()
    {
        return FALSE;
    }
    
    void enableLongPressGestureRecognizer(BOOL enable)
    {
        // Do nothing
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint         pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);
                
        fTextField.frame = CGRectMake(pt.x + (w - kStdNumEntryWidth) / 2.f,
                                    pt.y + (h - kStdNumEntryHeight - kSpaceSize - kStdNumEntryLabelHeight) / 2.f,
                                    kStdNumEntryWidth,
                                    kStdNumEntryHeight);
        
        fLabel.frame = CGRectMake(pt.x + (w - kStdNumEntryLabelWidth) / 2.f,
                                pt.y + (h + kStdNumEntryHeight - kSpaceSize - kStdNumEntryLabelHeight) / 2.f + kSpaceSize,
                                kStdNumEntryLabelWidth,
                                kStdNumEntryLabelHeight);
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden || getHideOnGUI();
        fTextField.hidden = hidden || getHideOnGUI();
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
    BOOL                    fHorizontal;
    BOOL                    fLed;
    
    uiBargraph(GUI* ui, FIMainViewController* controller, const char* name, float* zone, float min, float max, BOOL horizontal)
    : uiCocoaItem(ui, zone, controller, name)
    {
        fLed = false;
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
    
    void resetInitialValue()
    {
    }
    
    BOOL isHExpandable()
    {
        /*if (fLed) return YES;
        else*/ if (fHorizontal) return TRUE;
        
        return FALSE;
    }
    
    BOOL isVExpandable()
    {
        /*if (fLed) return YES;
        else*/ if (!fHorizontal) return TRUE;
        
        return FALSE;
    }
    
    void enableLongPressGestureRecognizer(BOOL enable)
    {
        // Do nothing
    }
    
    void setFrame(float x, float y, float w, float h)
    {
        CGPoint         pt = inBoxPosition2absolutePosition(x, y, fParent);
        
        uiCocoaItem::setFrame(x, y, w, h);
        
        if (fLed)
        {
            /*fBargraph.frame = CGRectMake(   pt.x + (w - kStdLedWidth) / 2.f,
                                            pt.y + (h - kStdLedHeight - kSpaceSize - kStdBargraphLabelHeight) / 2.f,
                                            kStdLedWidth,
                                            kStdLedHeight);
            
            fLabel.frame = CGRectMake(      pt.x + (w - kStdBargraphLabelWidth) / 2.f,
                                            pt.y + (h + kStdBargraphLabelHeight - kSpaceSize - kStdBargraphLabelHeight) / 2.f + kSpaceSize,
                                            kStdBargraphLabelWidth,
                                            kStdBargraphLabelHeight);*/
            
            if (fHorizontal)
            {
                fBargraph.frame = CGRectMake(pt.x + kStdLedWidth + kSpaceSize,
                                            pt.y + (h - kStdLedHeight) / 2.f,
                                            w - kStdBargraphLabelWidth - kSpaceSize,
                                            kStdLedHeight);
                
                fLabel.frame = CGRectMake(pt.x,
                                        pt.y + (h - kStdBargraphLabelHeight) / 2.f,
                                        kStdBargraphLabelWidth,
                                        kStdBargraphLabelHeight);
            }
            else
            {
                fBargraph.frame = CGRectMake(pt.x + (w - kStdLedWidth) / 2.f,
                                            pt.y,
                                            kStdLedWidth,
                                            h - kSpaceSize - kStdBargraphLabelHeight);
                
                fLabel.frame = CGRectMake(pt.x + (w - kStdBargraphLabelWidth) / 2.f,
                                        pt.y + h - kSpaceSize - kStdBargraphLabelHeight,
                                        kStdBargraphLabelWidth,
                                        kStdBargraphLabelHeight);
            }
        }
        else if (fHorizontal)
        {
            fBargraph.frame = CGRectMake(pt.x + kStdBargraphLabelWidth + kSpaceSize,
                                        pt.y + (h - kStdHorizontalBargraphHeight) / 2.f,
                                        w - kStdBargraphLabelWidth - kSpaceSize,
                                        kStdHorizontalBargraphHeight);
            
            fLabel.frame = CGRectMake(pt.x,
                                    pt.y + (h - kStdBargraphLabelHeight) / 2.f,
                                    kStdBargraphLabelWidth,
                                    kStdBargraphLabelHeight);
        }
        else
        {
            fBargraph.frame = CGRectMake(pt.x + (w - kStdVerticalBargraphWidth) / 2.f,
                                        pt.y,
                                        kStdVerticalBargraphWidth,
                                        h - kSpaceSize - kStdBargraphLabelHeight);
            
            fLabel.frame = CGRectMake(pt.x + (w - kStdBargraphLabelWidth) / 2.f,
                                    pt.y + h - kSpaceSize - kStdBargraphLabelHeight,
                                    kStdBargraphLabelWidth,
                                    kStdBargraphLabelHeight);
        }
    }
    
    void setHidden(BOOL hidden)
    {
        fHidden = hidden;
        fLabel.hidden = hidden || getHideOnGUI();
        fBargraph.hidden = hidden || getHideOnGUI();
    }
    
    void setLed(BOOL led)
    {
        fLed = led;
        fBargraph.led = led;
        
        if (led)
        {
            fLabel.textAlignment = UITextAlignmentCenter;
        }
        else
        {
            if (fHorizontal) fLabel.textAlignment = UITextAlignmentRight;
            else fLabel.textAlignment = UITextAlignmentCenter;
        }
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
    
    void setHidden(bool state)
    {
        map<float*, bool>::iterator it;
        for (it = fHideOnGUI.begin(); it != fHideOnGUI.end(); it++) {
            (*it).second = state;
        }
    }
   
private:
    
    UIWindow*                       fWindow;
    FIMainViewController*           fViewController;
    MY_Meta*                        fMetadata;
    map<float*, string>             fUnit;
    map<float*, float>              fR;
    map<float*, float>              fG;
    map<float*, float>              fB;
    map<float*, int>                fAssignationType;
    map<float*, bool>               fHideOnGUI;
    map<float*, bool>               fLed;
    map<float*, float>              fLedR;
    map<float*, float>              fLedG;
    map<float*, float>              fLedB;
    map<float*, string>             fRadioDescription;
    map<float*, string>             fMenuDescription;
    set<float*>                     fKnobSet;
    int                             fCurrentLayoutType;
    bool                            fNextBoxIsHideOnGUI;
    APIUI                           fAPIUI;
    bool                            fBuildUI;
    uiBox*                          fMonoView;
    
    // Layout management
    uiBox* getActiveBox()
    {
        list<uiCocoaItem*>::reverse_iterator i;
        
        // Loop on each widgets, from the last
        for (i = fWidgetList.rbegin(); i != fWidgetList.rend(); i++)
        {
            uiBox* box = dynamic_cast<uiBox*>(*i);
            if (box && !box->fClosed) {
                return box;
            }
        }
        return NULL;        
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
            uiBox* box = dynamic_cast<uiBox*>(widget);
            if (box && box->fLabel) {
                [box->fLabel removeFromSuperview];
                box->fLabel = nil;
                box->fLastY = box->fLastY - kStdBoxLabelHeight;
            }
        }
        
        // Otherwise, computing (x, y) of the widget within its parent box
        else
        {
            // If the box is a tab content box : no label
            if (parent->fBoxType == kTabLayout)
            {
                uiBox* box = dynamic_cast<uiBox*>(widget);
                if (box && box->fLabel) {
                    [box->fLabel removeFromSuperview];
                    box->fLabel = nil;
                    box->fLastY = box->fLastY - kStdBoxLabelHeight;
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
            if (dynamic_cast<uiBargraph*>(widget)->fLed)
            {
                if (dynamic_cast<uiBargraph*>(widget)->fHorizontal)
                {
                    //w = max(kStdLedWidth, kStdBargraphLabelWidth);
                    //h = kStdLedHeight + kSpaceSize + kStdBargraphLabelHeight;
                    w = kMinHorizontalBargraphWidth + kSpaceSize + kStdBargraphLabelWidth;
                    h = max(kStdLedHeight, kStdBargraphLabelHeight);
                }
                else
                {
                    //w = max(kStdLedWidth, kStdBargraphLabelWidth);
                    //h = kStdLedHeight + kSpaceSize + kStdBargraphLabelHeight;
                    //w = max(kStdLedWidth, kStdBargraphLabelWidth);
                    //h = kMinVerticalBargraphHeight + kSpaceSize + kStdBargraphLabelHeight;
                    w = max(kStdLedWidth, kStdBargraphLabelWidth);
                    h = kMinVerticalBargraphHeight + kSpaceSize + kStdBargraphLabelHeight;
                }
            }
            else if (dynamic_cast<uiBargraph*>(widget)->fHorizontal)
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
        
        if (widget->getHideOnGUI())
        {
            w = 0;
            h = 0;
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
        list<uiCocoaItem*>::reverse_iterator i;
        uiBox* box = NULL;
        
        if (fCurrentLayoutType == kTabLayout)
        {
            for (i = fWidgetList.rbegin(); i != fWidgetList.rend(); i++)
            {
                if ((box = dynamic_cast<uiBox*>(*i)))
                {
                    if (box->fBoxType == kTabLayout
                        && box != widget
                        && !box->fClosed)
                    {   
                        // Add FIButton in the fTabView
                        [box->fTabView addButtonWithLabel:[NSString stringWithCString:label encoding:NSASCIIStringEncoding]];
                        
                        // Add uiCocoaItem in the uiBox (*i)
                        box->fWidgetList.push_back(widget);
                    }
                }
            }
            
            /* SL : 01/09/16 : seems unecessary...
            list<uiCocoaItem*>::iterator i1 = fWidgetList.begin();
            box = dynamic_cast<uiBox*>(*i1);
            
            if (box->fBoxType == kTabLayout
                && box != widget)
            {
                [box->fTabView addButtonWithLabel:[NSString stringWithCString:label encoding:NSASCIIStringEncoding]];
                box->fWidgetList.push_back(widget);
            }
            */
        }
        else
        {
            for (i = fWidgetList.rbegin(); i != fWidgetList.rend(); i++)
            {
                if ((box = dynamic_cast<uiBox*>(*i)))
                {
                    if ((box->fBoxType == kHorizontalLayout
                        || box->fBoxType == kVerticalLayout)
                        && box != widget)
                    {   
                        // Add uiCocoaItem in the uiBox (*i)
                        box->fWidgetList.push_back(widget);
                    }
                }
            }   
       
            list<uiCocoaItem*>::iterator i1 = fWidgetList.begin();
            box = dynamic_cast<uiBox*>(*i1);
            
            if (((box)->fBoxType == kHorizontalLayout
                || box->fBoxType == kVerticalLayout)
                && box != widget)
            {
                box->fWidgetList.push_back(widget);
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
    
    CocoaUI(UIWindow* window, FIMainViewController* viewController, MY_Meta* metadata, dsp* DSP)
    {
        fCurrentLayoutType = kVerticalLayout;
        fViewController = viewController;
        fWindow = window;
        fMetadata = metadata;
        fNextBoxIsHideOnGUI = false;
        
        fViewController.dspView.backgroundColor = [UIColor blackColor];
        fViewController.dspScrollView.indicatorStyle = UIScrollViewIndicatorStyleWhite;
        
        DSP->buildUserInterface(&fAPIUI);
        
        [window addSubview:viewController.view];
        [window makeKeyAndVisible];
        
        fBuildUI = (fAPIUI.getScreenColor() < 0);
        
        if (!fBuildUI) {
            fMonoView = new uiBox(this, fViewController, "ColorBox", kColorLayout);
            insert("ColorBox", fMonoView);
        } else {
            fMonoView = NULL;
        }
    }
    
    ~CocoaUI()
    {
        [fViewController release];
        [fWindow release];
        delete fMonoView;
    }
    
    bool isScreenUI() { return !fBuildUI; }
    
    APIUI::Type getParamType(int index)
    {
        return fAPIUI.getParamType(index);
    }
    
    bool getParamType(APIUI::Type type)
    {
        /* 
            29/11/18: used by startMotion to activate the accelerometer and/or gyroscope
            correction to make it work even if screen mode is activated
        */
        
        /*
         list<uiCocoaItem*>::iterator i;
         for (i = fWidgetList.begin(); i != fWidgetList.end(); i++) {
         if (getParamType((*i)->getItemCount()) == type) {
         return true;
         }
         }
         return false;
         */
        
        for (int i = 0; i < fAPIUI.getParamsCount(); i++) {
            if (fAPIUI.getParamType(i) == type) {
                return true;
            }
        }
        return false;
    }
    
    void setAccValues(float x, float y, float z)
    {
        fAPIUI.propagateAcc(0, x);
        fAPIUI.propagateAcc(1, y);
        fAPIUI.propagateAcc(2, z);
    }
    
    void setGyrValues(float x, float y, float z)
    {
        fAPIUI.propagateGyr(0, x);
        fAPIUI.propagateGyr(1, y);
        fAPIUI.propagateGyr(2, z);
    }
    
    void setAccConverter(int index, int type, int curve, float min, float mid, float max)
    {
        printf("setAccConverter %d %d %d %f %f %f\n", index, type, curve, min, mid, max);
        fAPIUI.setAccConverter(index, type, curve, min, mid, max);
    }
    
    void getAccConverter(int index, int& type, int& curve, float& min, float& mid, float& max)
    {
        double dmin, dmid, dmax;
        fAPIUI.getAccConverter(index, type, curve, dmin, dmid, dmax);
        min = dmin;
        mid = dmid;
        max = dmax;
        printf("getAccConverter %d %d %d %f %f %f\n", index, type, curve, min, mid, max);
    }
    
    void setGyrConverter(int index, int type, int curve, float min, float mid, float max)
    {
        printf("setGyrConverter %d %d %d %f %f %f\n", index, type, curve, min, mid, max);
        fAPIUI.setGyrConverter(index, type, curve, min, mid, max);
    }
    
    void getGyrConverter(int index, int& type, int& curve, float& min, float& mid, float& max)
    {
        double dmin, dmid, dmax;
        fAPIUI.getGyrConverter(index, type, curve, dmin, dmid, dmax);
        min = dmin;
        mid = dmid;
        max = dmax;
        printf("getGyrConverter %d %d %d %f %f %f\n", index, type, curve, min, mid, max);
    }
    
    // Abstract layout : layout computed regardless screen dimensions
    void saveAbstractLayout()
    {
        list<uiCocoaItem*>::iterator i = fWidgetList.begin();
        
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            (*i)->setAbstractFrame((*i)->getX(), (*i)->getY(), (*i)->getW(), (*i)->getH());
        }
    }
    
    void loadAbstractLayout()
    {
        list<uiCocoaItem*>::iterator i = fWidgetList.begin();
        
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            (*i)->setFrame((*i)->getAbstractX(), (*i)->getAbstractY(), (*i)->getAbstractW(), (*i)->getAbstractH());
        }
    }
    
    void setHideOnGUI(BOOL state)
    {
        list<uiCocoaItem*>::iterator i = fWidgetList.begin();
        
        for (i = fWidgetList.begin(); i != fWidgetList.end(); i++)
        {
            (*i)->setHideOnGUI(state);
        }
    }
    
    void updateScreenCorlor() 
    {
        if (fMonoView) {
            fMonoView->setColor(fAPIUI.getScreenColor());
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
                                float y;
                                float h;
                                
                                if (contentSize.height == kSpaceSize)
                                {
                                    y = 0.f;
                                    h = 0.f;
                                }
                                else
                                {
                                    float divider = (contentSize.height - kSpaceSize - labelHeight);
                                    
                                    if(divider != 0.0)
                                    {
                                        y = ((*j)->getY() - kSpaceSize - labelHeight) * ((box->getH() - 2.f * kSpaceSize - labelHeight) / divider) + kSpaceSize + labelHeight;
                                        h = (*j)->getH() * ((box->getH() - 2.f * kSpaceSize - labelHeight) / divider);
                                    }
                                    else
                                    {
                                        y = 0.f;
                                        h = 0.f;
                                    }
                                        
                                }
                                
                                (*j)->setFrame((*j)->getX(),
                                               y,
                                               (*j)->getW(),
                                               h);
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
                                float x;
                                float w;
                                
                                if (contentSize.width == kSpaceSize)
                                {
                                    x = 0.f;
                                    w = 0.f;
                                }
                                else
                                {
                                    x = ((*j)->getX() - kSpaceSize) * ((box->getW() - 2.f * kSpaceSize) / (contentSize.width - kSpaceSize)) + kSpaceSize;
                                    w = (*j)->getW() * ((box->getW() - 2.f * kSpaceSize) / (contentSize.width - kSpaceSize));
                                }
                                
                                (*j)->setFrame(x,
                                               (*j)->getY(),
                                               w,
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
        uiBox*                          box = NULL;
        
        if ((box = dynamic_cast<uiBox*>(*i)))
        {
            // Make main box transparent if it is not a tab box
            if (box->fBoxType != kTabLayout)
            {
                box->fBox.color = [UIColor clearColor];
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
                if ((box = dynamic_cast<uiBox*>(*j)))
                {
                    if (!hExpandable
                        && box->fBoxType == kHorizontalLayout
                        && box->getNumberOfDirectChildren() > 1)
                    {
                        hExpandable = TRUE;
                    }
                    
                    if (!vExpandable
                        && box->fBoxType == kVerticalLayout
                        && box->getNumberOfDirectChildren() > 1)
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
        
       if (!fBuildUI) {
           fMonoView->setFrame(0, 0, width, height);
        }
    }
    
    CGRect getBoxAbsoluteFrameForWidget(uiCocoaItem* widget)
    {
        CGPoint pt = absolutePosition(widget);
        return CGRectMake(pt.x, pt.y, widget->getW(), widget->getH());
    }
    
    // Returns the box containing the point
    uiBox* getBoxForPoint(CGPoint pt)
    {
        list<uiCocoaItem*>::reverse_iterator i;
        uiBox* box = NULL;
        
        // Loop on each widgets, from the last
        for (i = fWidgetList.rbegin(); i != fWidgetList.rend(); i++)
        {
            if ((box = dynamic_cast<uiBox*>(*i)))
            {
                if (!(*i)->isHidden()
                    && pt.x >= absolutePosition(*i).x
                    && pt.x <= absolutePosition(*i).x + (*i)->getW()
                    && pt.y >= absolutePosition(*i).y
                    && pt.y <= absolutePosition(*i).y + (*i)->getH())
                {
                    if (box->getParent())
                    {
                        if (dynamic_cast<uiBox*>(box->getParent())->fBoxType == kTabLayout)
                        {
                            return dynamic_cast<uiBox*>(box->getParent());
                        }
                    }
                    
                    return box;
                }
            }
        }
        
        return NULL;
    }
    
    uiBox* getMainBox()
    {
         return (fWidgetList.size() > 0) ? dynamic_cast<uiBox*>(*fWidgetList.begin()): NULL;
    }
    
    bool isKnob(float* zone)
    {
        return fKnobSet.count(zone) > 0;
    }
    
    bool isRadio(float* zone)
    {
        return fRadioDescription.count(zone) > 0;
    }
    
    bool isMenu(float* zone)
    {
        return fMenuDescription.count(zone) > 0;
    }
    
    virtual void openFrameBox(const char* label)
    {}
    
    virtual void openTabBox(const char* label = "")
    {
        if (!fBuildUI) {
            return;
        }
        
        uiCocoaItem* item = new uiBox(this, fViewController, label, kTabLayout);
        insert(label, item);
        fCurrentLayoutType = kTabLayout;
    }
    
    virtual void openHorizontalBox(const char* label = "")
    {
        if (!fBuildUI) {
            return;
        }
        
        uiCocoaItem* item = new uiBox(this, fViewController, label, kHorizontalLayout);
        
        if (getCurrentOpenedBox()) item->setHideOnGUI(fNextBoxIsHideOnGUI || getCurrentOpenedBox()->getHideOnGUI());
        else item->setHideOnGUI(fNextBoxIsHideOnGUI);
        if (fNextBoxIsHideOnGUI) fNextBoxIsHideOnGUI = false;

        insert(label, item);
        fCurrentLayoutType = kHorizontalLayout;
    }
    
    virtual void openVerticalBox(const char* label = "")
    {
        if (!fBuildUI) {
            return;
        }
        
        uiCocoaItem* item = new uiBox(this, fViewController, label, kVerticalLayout);
        
        if (getCurrentOpenedBox()) item->setHideOnGUI(fNextBoxIsHideOnGUI || getCurrentOpenedBox()->getHideOnGUI());
        else item->setHideOnGUI(fNextBoxIsHideOnGUI);
        if (fNextBoxIsHideOnGUI) fNextBoxIsHideOnGUI = false;
        
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
    
    virtual uiBox* getCurrentOpenedBox()
    {
        list<uiCocoaItem*>::reverse_iterator i;
       
        // Find the last box to close
        for (i = fWidgetList.rbegin(); i != fWidgetList.rend(); i++)
        {
            uiBox* box = dynamic_cast<uiBox*>(*i);
            if (box && !box->fClosed) {
                return box;
            }
        }
        
        return NULL;
    }
    
    virtual void closeBox()
    {
        list<uiCocoaItem*>::reverse_iterator i;
        
        for (i = fWidgetList.rbegin(); i != fWidgetList.rend(); i++) {
            uiBox* box = dynamic_cast<uiBox*>(*i);
            if (box && !box->fClosed) {
                box->close(fWidgetList.size());
                break;
            }
        }
     
        for (i = fWidgetList.rbegin(); i != fWidgetList.rend(); i++) {
            uiBox* box = dynamic_cast<uiBox*>(*i);
            if (box && !box->fClosed) {
                fCurrentLayoutType = box->fBoxType;
                break;
            }
        }
    }
    
    //virtual void adjustStack(int n);
    
    // -- active widgets
    
    virtual void addButton(const char* label, float* zone)
    {
        if (!fBuildUI) {
            return;
        }
        
        uiCocoaItem* item = new uiButton(this, fViewController, label, zone, kPushButtonType);
        
        // Default parameters
        if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
        if (getCurrentOpenedBox())
        {
            if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
        }
        else
        {
            if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
        }
        dynamic_cast<uiButton*>(item)->fButton.hideOnGUI = item->getHideOnGUI();
        
        insert(label, item);
    }
    
    virtual void addToggleButton(const char* label, float* zone)
    {
        if (!fBuildUI) {
            return;
        }
        
        uiCocoaItem* item = new uiButton(this, fViewController, label, zone, kToggleButtonType);
        
        // Default parameters
        if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
        if (getCurrentOpenedBox())
        {
            if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
        }
        else
        {
            if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
        }
        dynamic_cast<uiButton*>(item)->fButton.hideOnGUI = item->getHideOnGUI();
        
        insert(label, item);
    }
    
    virtual void addCheckButton(const char* label, float* zone)
    {
        if (!fBuildUI) {
            return;
        }
        
        uiCocoaItem* item = new uiButton(this, fViewController, label, zone, kToggleButtonType);
        
        // Default parameters
        if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
        if (getCurrentOpenedBox())
        {
            if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
        }
        else
        {
            if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
        }
        dynamic_cast<uiButton*>(item)->fButton.hideOnGUI = item->getHideOnGUI();
        
        insert(label, item);
    }
    
    virtual void addRadioButton(const char* label, float init, float* zone, float value = FLT_MAX)
    {
        if (!fBuildUI) {
            return;
        }
        
        uiButton* item = new uiButton(this, fViewController, label, zone, kCheckButtonType, value);
        
        // Default parameters
        if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
        if (getCurrentOpenedBox())
        {
            if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
        }
        else
        {
            if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
        }
        dynamic_cast<uiButton*>(item)->fButton.hideOnGUI = item->getHideOnGUI();
        
        insert(label, item);
        
        if (init == value) {
            item->setOn();
        }
    }
    
    virtual void addVerticalKnob(const char* label , float* zone, float init, float min, float max, float step)
	{
        uiCocoaItem* item = new uiKnob(this, fViewController, label, zone, init, min, max, step, false);
        if (dynamic_cast<uiKnob*>(item)->fKnob.suffixe) [dynamic_cast<uiKnob*>(item)->fKnob.suffixe release];
        dynamic_cast<uiKnob*>(item)->fKnob.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
        
        // Default parameters
        if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
        if (fAssignationType[zone]) item->setInitAssignationType(fAssignationType[zone]);
        if (getCurrentOpenedBox())
        {
            if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
        }
        else
        {
            if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
        }
        dynamic_cast<uiKnob*>(item)->fKnob.hideOnGUI = item->getHideOnGUI();
        
        insert(label, item);
    }
    
    virtual void addHorizontalKnob(const char* label , float* zone, float init, float min, float max, float step)
	{
        uiCocoaItem* item = new uiKnob(this, fViewController, label, zone, init, min, max, step, true);
        if (dynamic_cast<uiKnob*>(item)->fKnob.suffixe) [dynamic_cast<uiKnob*>(item)->fKnob.suffixe release];
        dynamic_cast<uiKnob*>(item)->fKnob.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
        
        // Default parameters
        if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
        if (fAssignationType[zone]) item->setInitAssignationType(fAssignationType[zone]);
        if (getCurrentOpenedBox())
        {
            if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
        }
        else
        {
            if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
        }
        dynamic_cast<uiKnob*>(item)->fKnob.hideOnGUI = item->getHideOnGUI();
        
        insert(label, item);
    }
    
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        if (!fBuildUI) {
            return;
        }
        
        if (isKnob(zone)) {
            addVerticalKnob(label, zone, init, min, max, step);
        } else if (isRadio(zone)) {
            addVerticalRadioButtons(label, zone, init, min, max, step, fRadioDescription[zone].c_str());
        } else {
            uiCocoaItem* item = new uiSlider(this, fViewController, label, zone, init, min, max, step, false,
                                             ((fMenuDescription.count(zone) ? fMenuDescription[zone].c_str() : NULL)));
            if (dynamic_cast<uiSlider*>(item)->fSlider.suffixe) [dynamic_cast<uiSlider*>(item)->fSlider.suffixe release];
            dynamic_cast<uiSlider*>(item)->fSlider.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
            
            // Default parameters
            if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
            if (fAssignationType[zone]) item->setInitAssignationType(fAssignationType[zone]);
            if (getCurrentOpenedBox())
            {
                if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
            }
            else
            {
                if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
            }
            dynamic_cast<uiSlider*>(item)->fSlider.hideOnGUI = item->getHideOnGUI();
            
            insert(label, item);
        }
    }
    
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        if (!fBuildUI) {
            return;
        }
        
        if (isKnob(zone)){
            addHorizontalKnob(label, zone, init, min, max, step);
        } else if (isRadio(zone)) {
            addHorizontalRadioButtons(label, zone, init, min, max, step, fRadioDescription[zone].c_str());
        } else {
            uiCocoaItem* item = new uiSlider(this, fViewController, label, zone, init, min, max, step, true,
                                             ((fMenuDescription.count(zone) ? fMenuDescription[zone].c_str() : NULL)));
            if (dynamic_cast<uiSlider*>(item)->fSlider.suffixe) [dynamic_cast<uiSlider*>(item)->fSlider.suffixe release];
            dynamic_cast<uiSlider*>(item)->fSlider.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
                        
            // Default parameters
            if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
            if (fAssignationType[zone]) item->setInitAssignationType(fAssignationType[zone]);
            if (getCurrentOpenedBox())
            {
                if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
            }
            else
            {
                if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
            }
            dynamic_cast<uiSlider*>(item)->fSlider.hideOnGUI = item->getHideOnGUI();
            
            insert(label, item);
        }
    }
    
    virtual void addVerticalRadioButtons(const char* label, float* zone, float init, float min, float max, float step, const char* mdescr)
    {
        if (!fBuildUI) {
            return;
        }
        const char* p = mdescr;
        vector<string> names;
        vector<double> values;
        parseMenuList(p, names, values);
        
        openVerticalBox(label);
        for (int i = 0; i < names.size(); i++) {
            addRadioButton(names[i].c_str(), init, zone, values[i]);
        }
        closeBox();
    }
    
    virtual void addHorizontalRadioButtons(const char* label, float* zone, float init, float min, float max, float step, const char* mdescr)
    {
        if (!fBuildUI) {
            return;
        }
        const char* p = mdescr;
        vector<string> names;
        vector<double> values;
        parseMenuList(p, names, values);
        
        openHorizontalBox(label);
        for (int i = 0; i < names.size(); i++) {
            addRadioButton(names[i].c_str(), init, zone, values[i]);
        }
        closeBox();
    }
    
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        if (!fBuildUI) {
            return;
        }
        
        if (isKnob(zone))
        {
            addVerticalKnob(label, zone, init, min, max, step);
        }
        else
        {
            uiCocoaItem* item = new uiNumEntry(this, fViewController, label, zone, init, min, max, step, ((fMenuDescription.count(zone) ? fMenuDescription[zone].c_str() : NULL)));
            if (dynamic_cast<uiNumEntry*>(item)->fTextField.suffixe) [dynamic_cast<uiNumEntry*>(item)->fTextField.suffixe release];
            dynamic_cast<uiNumEntry*>(item)->fTextField.suffixe = [[NSString alloc] initWithCString:fUnit[zone].c_str() encoding:NSUTF8StringEncoding];
            
            // Default parameters
            if (fR[zone] && fG[zone] && fB[zone]) item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
            if (getCurrentOpenedBox())
            {
                if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
            }
            else
            {
                if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
            }
            dynamic_cast<uiNumEntry*>(item)->fTextField.hideOnGUI = item->getHideOnGUI();
            
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
        if (!fBuildUI) {
            return;
        }
        
        uiCocoaItem* item = new uiBargraph(this, fViewController, label, zone, min, max, true);
        
        if (fR[zone] && fG[zone] && fB[zone])
        {
            item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
            dynamic_cast<uiBargraph*>(item)->fBargraph.ledMaxColor = [[UIColor colorWithRed:fR[zone] - 1000.
                                                                                      green:fG[zone] - 1000.
                                                                                       blue:fB[zone] - 1000.
                                                                                      alpha:1.] retain];
        }
        if (getCurrentOpenedBox())
        {
            if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
        }
        else
        {
            if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
        }
        dynamic_cast<uiBargraph*>(item)->setLed(fLed[zone]);
        
        if (fLedR[zone] || fLedG[zone] || fLedB[zone])
        {
            dynamic_cast<uiBargraph*>(item)->fBargraph.ledMinColor = [[UIColor colorWithRed:fLedR[zone]
                                                                                      green:fLedG[zone]
                                                                                       blue:fLedB[zone]
                                                                                      alpha:1.] retain];
        }
        
        insert(label, item);
    }
    
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
    {
        if (!fBuildUI) {
            return;
        }
        
        uiCocoaItem* item = new uiBargraph(this, fViewController, label, zone, min, max, false);
        
        if (fR[zone] && fG[zone] && fB[zone])
        {
            item->setInitColor(fR[zone] - 1000., fG[zone] - 1000., fB[zone] - 1000.);
            dynamic_cast<uiBargraph*>(item)->fBargraph.ledMaxColor = [[UIColor colorWithRed:fR[zone] - 1000.
                                                                                      green:fG[zone] - 1000.
                                                                                       blue:fB[zone] - 1000.
                                                                                      alpha:1.] retain];
        }
        if (getCurrentOpenedBox())
        {
            if (fHideOnGUI[zone] || getCurrentOpenedBox()->getHideOnGUI()) item->setHideOnGUI(TRUE);
        }
        else
        {
            if (fHideOnGUI[zone]) item->setHideOnGUI(TRUE);
        }
        dynamic_cast<uiBargraph*>(item)->setLed(fLed[zone]);
        
        if (fLedR[zone] || fLedG[zone] || fLedB[zone])
        {
            dynamic_cast<uiBargraph*>(item)->fBargraph.ledMinColor = [[UIColor colorWithRed:fLedR[zone]
                                                                                      green:fLedG[zone]
                                                                                       blue:fLedB[zone]
                                                                                      alpha:1.] retain];
        }
        
        insert(label, item);
    }
    
    virtual void show()
    {}
    
    virtual bool run()
    {
        return false;
    }
    
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
            
            if (strcmp(key, "hidden") == 0)
            {
				NSString* str = [NSString stringWithCString:value encoding:NSUTF8StringEncoding];
                NSArray* arr = [str componentsSeparatedByString:@" "];
                
                if ([((NSString*)[arr objectAtIndex:0]) integerValue] == 1)
                {
                    fNextBoxIsHideOnGUI = true;
                }
            }
		}
        else
        {
            if (strcmp(key, "size") == 0)
            {
				//fGuiSize[zone]=atof(value);
			}
			else if (strcmp(key, "tooltip") == 0)
            {
				//fTooltip[zone] = formatTooltip(30, value) ;
			}
			else if (strcmp(key, "unit") == 0)
            {
				fUnit[zone] = value;
			}
            else if (strcmp(key, "hidden") == 0)
            {
				NSString* str = [NSString stringWithCString:value encoding:NSUTF8StringEncoding];
                NSArray* arr = [str componentsSeparatedByString:@" "];
            
                if ([((NSString*)[arr objectAtIndex:0]) integerValue] == 1)
                {
                    fHideOnGUI[zone] = true;
                }
            }
			else if (strcmp(key, "style") == 0)
            {
                NSString* str = [NSString stringWithCString:value encoding:NSUTF8StringEncoding];
                NSArray* arr = [str componentsSeparatedByString:@" "];
                const char* p = value;
                
                if ([arr count] == 0) return;
                
				if ([((NSString*)[arr objectAtIndex:0]) compare:@"knob"] == NSOrderedSame)
                {
					fKnobSet.insert(zone);
				}
                else if ([((NSString*)[arr objectAtIndex:0]) compare:@"led"] == NSOrderedSame)
                {
                    fLed[zone] = true;
                    
                    fLedR[zone] = 0.f;
                    fLedG[zone] = 0.f;
                    fLedB[zone] = 0.f;
                    
                    if ([arr count] == 2)
                    {
                        fLedR[zone] = (float)[((NSString*)[arr objectAtIndex:1]) integerValue] / 255.f;
                    }
                    else if ([arr count] == 3)
                    {
                        fLedR[zone] = (float)[((NSString*)[arr objectAtIndex:1]) integerValue] / 255.f;
                        fLedG[zone] = (float)[((NSString*)[arr objectAtIndex:2]) integerValue] / 255.f;
                    }
                    else if ([arr count] == 4)
                    {
                        fLedR[zone] = (float)[((NSString*)[arr objectAtIndex:1]) integerValue] / 255.f;
                        fLedG[zone] = (float)[((NSString*)[arr objectAtIndex:2]) integerValue] / 255.f;
                        fLedB[zone] = (float)[((NSString*)[arr objectAtIndex:3]) integerValue] / 255.f;
                    }
                } else if (parseWord(p, "radio")) {
                    fRadioDescription[zone] = string(p);
                } else if (parseWord(p, "menu")) {
                    fMenuDescription[zone] = string(p);
                }
            }
            else if (strcmp(key, "color") == 0)
            {
                NSString* str = [NSString stringWithCString:value encoding:NSUTF8StringEncoding];
                NSArray* arr = [str componentsSeparatedByString:@" "];
                
                fR[zone] = (float)[((NSString*)[arr objectAtIndex:0]) integerValue] / 255.f + 1000.;
                fG[zone] = (float)[((NSString*)[arr objectAtIndex:1]) integerValue] / 255.f + 1000.;
                fB[zone] = (float)[((NSString*)[arr objectAtIndex:2]) integerValue] / 255.f + 1000.;
            }
            else if (strcmp(key,"accx") == 0
                     || strcmp(key,"accy") == 0
                     || strcmp(key,"accz") == 0
                     || strcmp(key,"gyrox") == 0
                     || strcmp(key,"gyroy") == 0
                     || strcmp(key,"gyroz") == 0)
            {
                if (strcmp(key,"accx") == 0) fAssignationType[zone] = kAssignationAccelX;
                else if (strcmp(key,"accy") == 0) fAssignationType[zone] = kAssignationAccelY;
                else if (strcmp(key,"accz") == 0) fAssignationType[zone] = kAssignationAccelZ;
                else if (strcmp(key,"gyrox") == 0) fAssignationType[zone] = kAssignationGyroX;
                else if (strcmp(key,"gyroy") == 0) fAssignationType[zone] = kAssignationGyroY;
                else if (strcmp(key,"gyroz") == 0) fAssignationType[zone] = kAssignationGyroZ;
            }
		}
	}
};

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
