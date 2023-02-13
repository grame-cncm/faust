/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#import <CoreMotion/CoreMotion.h>
#import <CoreLocation/CoreLocation.h>
#import <list>
#import "FIFlipsideViewController.h"
#import "FIResponder.h"
#import "FIScrollView.h"

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
    std::list<uiCocoaItem*>             _assignatedWidgets;
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
