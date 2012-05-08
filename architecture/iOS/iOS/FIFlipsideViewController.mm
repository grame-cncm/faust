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

#import "FIFlipsideViewController.h"
#import "FIMainViewController.h"

@implementation FIFlipsideViewController

@synthesize delegate = _delegate;
@synthesize sampleRate = _sampleRate;
@synthesize bufferSize = _bufferSize;


- (void)awakeFromNib
{
    self.contentSizeForViewInPopover = CGSizeMake(320.0, 480.0);
    [super awakeFromNib];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Read user preferences
    _sampleRate = [[NSUserDefaults standardUserDefaults] integerForKey:@"sampleRate"];
    if (_sampleRate == 0) _sampleRate = 44100;
    
    _bufferSize = [[NSUserDefaults standardUserDefaults] integerForKey:@"bufferSize"];
    if (_bufferSize == 0) _bufferSize = 256;
    
    // Update UI
    _sampleRateSlider.value = [self sampleRateToSliderValue:_sampleRate];
    _sampleRateLabel.text = [NSString stringWithFormat:@"%i Hz", _sampleRate];
    
    _bufferSizeSlider.value = [self bufferSizeToSliderValue:_bufferSize];
    _bufferSizeLabel.text = [NSString stringWithFormat:@"%i", _bufferSize];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
    {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    }
    else
    {
        return YES;
    }
}


#pragma mark - Actions

- (IBAction)done:(id)sender
{
    // Write user preferences
    [[NSUserDefaults standardUserDefaults] setInteger:_sampleRate forKey:@"sampleRate"];
    [[NSUserDefaults standardUserDefaults] setInteger:_bufferSize forKey:@"bufferSize"];
	[[NSUserDefaults standardUserDefaults] synchronize];
    
    // Update audio preferences
    [((FIMainViewController*)self.delegate) restartAudioWithBufferSize:_bufferSize sampleRate:_sampleRate];
    
    // Dismiss view
    [self.delegate flipsideViewControllerDidFinish:self];
}

- (IBAction)sampleRateSliderMoved:(id)sender
{
    _sampleRate = [self sliderValueToSampleRate:(int)floor(((UISlider*)sender).value)];
    _sampleRateLabel.text = [NSString stringWithFormat:@"%i Hz", _sampleRate];
}

- (IBAction)bufferSizeSliderMoved:(id)sender
{
    _bufferSize = [self sliderValueToBufferSize:(int)floor(((UISlider*)sender).value)];
    _bufferSizeLabel.text = [NSString stringWithFormat:@"%i", _bufferSize];
}

- (int)sampleRateToSliderValue:(int)sampleRate
{
    switch (sampleRate)
    {
        case 8000:
            return 0;
            break;
        case 11025:
            return 1;
            break;
        case 16000:
            return 2;
            break;
        case 22050:
            return 3;
            break;
        case 44100:
            return 4;
            break;
        case 48000:
            return 5;
            break;
        case 96000:
            return 6;
            break;
        default:
            return 4;
            break;
    }
    
    return 4;
}

- (int)sliderValueToSampleRate:(int)sliderValue
{
    switch (sliderValue)
    {
        case 0:
            return 8000;
            break;
        case 1:
            return 11025;
            break;
        case 2:
            return 16000;
            break;
        case 3:
            return 22050;
            break;
        case 4:
            return 44100;
            break;
        case 5:
            return 48000;
            break;
        case 6:
            return 96000;
            break;
        default:
            return 44100;
            break;
    }
    
    return 44100;
}

- (int)bufferSizeToSliderValue:(int)bufferSize
{
    switch (bufferSize)
    {
        case 16:
            return 0;
            break;
        case 32:
            return 1;
            break;
        case 64:
            return 2;
            break;
        case 128:
            return 3;
            break;
        case 256:
            return 4;
            break;
        case 512:
            return 5;
            break;
        case 1024:
            return 6;
            break;
        case 2048:
            return 7;
            break;
        default:
            return 4;
            break;
    }
    
    return 4;
}

- (int)sliderValueToBufferSize:(int)sliderValue
{
    switch (sliderValue)
    {
        case 0:
            return 16;
            break;
        case 1:
            return 32;
            break;
        case 2:
            return 64;
            break;
        case 3:
            return 128;
            break;
        case 4:
            return 256;
            break;
        case 5:
            return 512;
            break;
        case 6:
            return 1024;
            break;
        case 7:
            return 2048;
            break;
        default:
            return 256;
            break;
    }
    
    return 256;
}

@end