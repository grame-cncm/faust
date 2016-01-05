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

#import <UIKit/UIKit.h>

@class FIFlipsideViewController;

@protocol FIFlipsideViewControllerDelegate

- (void)flipsideViewControllerDidFinish:(FIFlipsideViewController *)controller;

@end

//@interface FIFlipsideViewController : UIViewController <UIAlertViewDelegate,UITextFieldDelegate>
@interface FIFlipsideViewController : UIViewController <UIAlertViewDelegate>
{
    IBOutlet UISlider*              _sampleRateSlider;
    IBOutlet UILabel*               _sampleRateLabel;
    IBOutlet UISlider*              _bufferSizeSlider;
    IBOutlet UILabel*               _bufferSizeLabel;
    IBOutlet UISwitch*              _openWidgetPanelSwitch;
    
    int                             _sampleRate;
    int                             _bufferSize;
    BOOL                            _openWidgetPanel;
    
    IBOutlet UITextField*   _oscIPOutput;
    NSString*               _oscIPOutputText;
    
    int                          _oscTransmit;
    IBOutlet UISegmentedControl* _oscTransmitState;
    
    IBOutlet UITextField*  _oscInputPort;
    NSString*              _oscInputPortText;
    
    IBOutlet UITextField*  _oscOutputPort;
    NSString*              _oscOutputPortText;
}

@property (assign, nonatomic) IBOutlet id <FIFlipsideViewControllerDelegate> delegate;
@property (nonatomic, nonatomic) int sampleRate;
@property (nonatomic, nonatomic) int bufferSize;
@property (nonatomic, nonatomic) BOOL openWidgetPanel;
@property (nonatomic, nonatomic) int oscTransmit;

- (IBAction)done:(id)sender;
- (IBAction)sampleRateSliderMoved:(id)sender;
- (IBAction)bufferSizeSliderMoved:(id)sender;
- (IBAction)openWidgetPanelSwitchMoved:(id)sender;
- (IBAction)deleteAssignationsButtonClicked:(id)sender;

- (int)sampleRateToSliderValue:(int)sampleRate;
- (int)sliderValueToSampleRate:(int)sliderValue;
- (int)bufferSizeToSliderValue:(int)bufferSize;
- (int)sliderValueToBufferSize:(int)sliderValue;

- (void)disableAudioWidgets;
- (void)enableAudioWidgets;

@end
