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


@interface FIFlipsideViewController : UIViewController
{
    IBOutlet UISlider*              _sampleRateSlider;
    IBOutlet UILabel*               _sampleRateLabel;
    IBOutlet UISlider*              _bufferSizeSlider;
    IBOutlet UILabel*               _bufferSizeLabel;
    
    int                             _sampleRate;
    int                             _bufferSize;
}

@property (assign, nonatomic) IBOutlet id <FIFlipsideViewControllerDelegate> delegate;
@property (nonatomic, nonatomic) int sampleRate;
@property (nonatomic, nonatomic) int bufferSize;


- (IBAction)done:(id)sender;
- (IBAction)sampleRateSliderMoved:(id)sender;
- (IBAction)bufferSizeSliderMoved:(id)sender;

- (int)sampleRateToSliderValue:(int)sampleRate;
- (int)sliderValueToSampleRate:(int)sliderValue;
- (int)bufferSizeToSliderValue:(int)bufferSize;
- (int)sliderValueToBufferSize:(int)sliderValue;

@end
