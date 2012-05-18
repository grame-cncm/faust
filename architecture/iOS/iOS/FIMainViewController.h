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
#import "FISensorFilter.h"

using namespace std;
class uiCocoaItem;
class uiBox;

@interface FIMainViewController : UIViewController <    FIFlipsideViewControllerDelegate,
                                                        UIPopoverControllerDelegate,
                                                        FIResponderDelegate,
                                                        UIScrollViewDelegate,
                                                        UIGestureRecognizerDelegate,
                                                        UIAccelerometerDelegate,
                                                        CLLocationManagerDelegate>
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
    IBOutlet UISwitch*                  _gyroInvertedSwitch;
    IBOutlet UILabel*                   _widgetPreferencesTitleLabel;
    uiCocoaItem*                        _selectedWidget;                // Contains label of the widget
    list <uiCocoaItem*>                 _assignatedWidgets;
    FISensorFilter*                     _accelerometerFilter;
    CLLocationManager*                  _locationManager;
}

@property (strong, nonatomic) UIPopoverController* flipsidePopoverController;
@property (assign, nonatomic) UIView* dspView;
@property (assign, nonatomic) UIScrollView* dspScrollView;

// DSP view
- (void)responderValueDidChange:(float)value sender:(id)sender;
- (void)saveGui;
- (void)updateGui;

// Misc GUI
- (void)orientationChanged:(NSNotification *)notification;
- (void)displayTitle;
- (void)refreshObjects:(NSTimer*)timer;
- (void)zoomToLockedBox;
- (void)doubleTap;

// Audio
- (void)restartAudioWithBufferSize:(int)bufferSize sampleRate:(int)sampleRate;

// Sensors
- (void)showWidgetPreferencesView:(UILongPressGestureRecognizer *)gesture;
- (IBAction)dismissWidgetPreferencesView:(id)sender;
- (IBAction)widgetPreferencesChanged:(id)sender;
- (void)loadMotionPreferences;
- (void)startMotion;
- (void)stopMotion;

@end