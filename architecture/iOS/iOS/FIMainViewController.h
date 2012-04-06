/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#import "FIFlipsideViewController.h"
#import "FIResponder.h"

@interface FIMainViewController : UIViewController <    FIFlipsideViewControllerDelegate,
                                                        UIPopoverControllerDelegate,
                                                        FIResponderDelegate,
                                                        UIScrollViewDelegate>
{
    IBOutlet UIView*                _dspView;
    IBOutlet UIScrollView*          _dspScrollView;
    IBOutlet UILabel*               _titleLabel;            // iPhone
    IBOutlet UINavigationItem*      _titleNavigationItem;   // iPad
    
    NSTimer*                        _refreshTimer;          // Used to refresh bargraphes
    
    UITapGestureRecognizer*         _tapGesture;
    CGRect                          _lockedRect;
    BOOL                            _viewLoaded;
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

// Audio
- (void)restartAudioWithBufferSize:(int)bufferSize sampleRate:(int)sampleRate;

@end