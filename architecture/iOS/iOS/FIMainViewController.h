/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 
 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.
 
 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#import <CoreMotion/CoreMotion.h>
#import <CoreLocation/CoreLocation.h>
#import <list>
#import "FIFlipsideViewController.h"
#import "FIResponder.h"
#import "FIScrollView.h"

using namespace std;
class uiCocoaItem;
class uiBox;

@interface FIMainViewController : UIViewController <    FIFlipsideViewControllerDelegate,
                                                        UIPopoverControllerDelegate,
                                                        FIResponderDelegate,
                                                        UIScrollViewDelegate,
                                                        UIGestureRecognizerDelegate>
{
    IBOutlet UIView*                    _dspView;
    IBOutlet FIScrollView*              _dspScrollView;
    IBOutlet UILabel*                   _titleLabel;                    // iPhone
    IBOutlet UINavigationItem*          _titleNavigationItem;           // iPad
    
    NSTimer*                            _refreshTimer;                  // Used to refresh bargraphes
    
    UITapGestureRecognizer*             _tapGesture;
    uiBox*                              _lockedBox;
    UIDeviceOrientation                 _currentOrientation;
    BOOL                                _viewLoaded;  
    
    IBOutlet UIView*                    _widgetPreferencesView;
    
    IBOutlet UISegmentedControl*        _gyroAxisSegmentedControl;
    
    IBOutlet UILabel*                   _widgetPreferencesTitleLabel;
    uiCocoaItem*                        _selectedWidget;                // Contains label of the widget
    list <uiCocoaItem*>                 _assignatedWidgets;
    CMMotionManager*                    _motionManager;
    NSTimer*                            _motionTimer;
    
    BOOL                                _hasAcc;
    BOOL                                _hasGyr;
    
    IBOutlet UILabel*                   _colorLabel;
    IBOutlet UILabel*                   _rLabel;
    IBOutlet UILabel*                   _gLabel;
    IBOutlet UILabel*                   _bLabel;
    IBOutlet UILabel*                   _colorRLabel;
    IBOutlet UILabel*                   _colorGLabel;
    IBOutlet UILabel*                   _colorBLabel;
    IBOutlet UISlider*                  _colorRSlider;
    IBOutlet UISlider*                  _colorGSlider;
    IBOutlet UISlider*                  _colorBSlider;
    
    const   char*                       _name;
    
    BOOL                                _openPanelChanged;
    
    // New UI
    
    IBOutlet UISegmentedControl*        _curveSegmentedControl;
    
    IBOutlet UITextField*               _minText;
    IBOutlet UITextField*               _maxText;
    IBOutlet UITextField*               _centerText;
    
    IBOutlet UISlider*                  _minSlider;
    IBOutlet UISlider*                  _maxSlider;
    IBOutlet UISlider*                  _centerSlider;
}

@property (strong, nonatomic) UIPopoverController* flipsidePopoverController;
@property (assign, nonatomic) UIView* dspView;
@property (assign, nonatomic) UIScrollView* dspScrollView;

// DSP view
- (void)responderValueDidChange:(float)value sender:(id)sender;
- (void)saveGui;
- (void)loadGui;
- (void)updateGui;

- (BOOL)openCoreAudio:(int)bufferSize :(int)sampleRate;

- (void)openAudio;
- (void)closeAudio;

// Misc GUI
- (void)orientationChanged:(NSNotification *)notification;
- (void)displayTitle;
- (void)refreshObjects:(NSTimer*)timer;
- (void)zoomToLockedBox;
- (void)doubleTap;
- (void)buttonSetToZero:(id)sender;
- (void)zoomToWidget:(FIResponder*)widget;
- (void)setOpenWidgetPanel:(BOOL)openWidgetPanelOnLongTouch;

// Audio
- (void)restartAudioWithBufferSize:(int)bufferSize sampleRate:(int)sampleRate;

// OSC
- (void)setOSCParameters:(int)transmit output:(NSString*)outputIPText inputport:(NSString*)inputPortText outputport:(NSString*)outputPortText;

// Sensors
- (void)showWidgetPreferencesView:(UILongPressGestureRecognizer *)gesture;
- (void)updateWidgetPreferencesView;
- (IBAction)dismissWidgetPreferencesView:(id)sender;
- (IBAction)widgetPreferencesChanged:(id)sender;
- (IBAction)resetWidgetPreferences:(id)sender;
- (void)resetAllWidgetsPreferences;
- (void)loadWidgetsPreferences;
- (void)startMotion;
- (void)stopMotion;
- (void)updateMotion;
- (NSString*)urlForWidget:(uiCocoaItem*)widget;

@end
