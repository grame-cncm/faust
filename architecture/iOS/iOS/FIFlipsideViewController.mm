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
@synthesize openWidgetPanel = _openWidgetPanel;

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
    _sampleRate = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"sampleRate"];
    _bufferSize = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"bufferSize"];
    _openWidgetPanel = [[NSUserDefaults standardUserDefaults] boolForKey:@"openWidgetPanel"];
    _oscTransmit = [[NSUserDefaults standardUserDefaults] integerForKey:@"oscTransmit"];
    _oscIPOutputText = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscIPOutputText"];
 #if OSCCTRL
    _oscIPOutputText = (_oscIPOutputText) ? _oscIPOutputText : @"192.168.1.1";
    _oscInputPortText = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscInputPortText"];
    _oscInputPortText = (_oscInputPortText) ? _oscInputPortText : @"5510";
    _oscOutputPortText = [[NSUserDefaults standardUserDefaults] stringForKey:@"oscOutputPortText"];
    _oscOutputPortText = (_oscOutputPortText) ? _oscOutputPortText : @"5511";
#else
    _oscIPOutputText = @"Deactivated";
    _oscInputPortText = @"-1";
    _oscOutputPortText = @"-1";
#endif
    
    [_oscTransmitState removeAllSegments];
    [_oscTransmitState insertSegmentWithTitle:@"No" atIndex:0 animated:NO];
    [_oscTransmitState insertSegmentWithTitle:@"All" atIndex:1 animated:NO];
    [_oscTransmitState insertSegmentWithTitle:@"Alias" atIndex:2 animated:NO];
    
     _oscTransmitState.selectedSegmentIndex = _oscTransmit;
 
#if OSCCTRL
    _oscIPOutput.enabled = TRUE;
    _oscInputPort.enabled = TRUE;
    _oscOutputPort.enabled = TRUE;
    _oscTransmitState.enabled = TRUE;
#else
    _oscIPOutput.enabled = FALSE;
    _oscInputPort.enabled = FALSE;
    _oscOutputPort.enabled = FALSE;
    _oscTransmitState.enabled = FALSE;
#endif
    
    // Update UI
    _sampleRateSlider.value = [self sampleRateToSliderValue:_sampleRate];
    _sampleRateLabel.text = [NSString stringWithFormat:@"%i Hz", _sampleRate];
    
    _bufferSizeSlider.value = [self bufferSizeToSliderValue:_bufferSize];
    _bufferSizeLabel.text = [NSString stringWithFormat:@"%i frames", _bufferSize];

    _oscIPOutput.text = _oscIPOutputText;
    _oscInputPort.text = _oscInputPortText;
    _oscOutputPort.text = _oscOutputPortText;
    
    //_oscIPOutput.keyboardType = UIKeyboardTypeDecimalPad;
    _oscInputPort.keyboardType = UIKeyboardTypeNumberPad;
    _oscOutputPort.keyboardType = UIKeyboardTypeNumberPad;
    
    [_openWidgetPanelSwitch setOn:_openWidgetPanel animated:NO];
}

- (void)viewDidUnload
{
    [_oscIPOutput release];
    _oscIPOutput = nil;
    [_oscTransmitState release];
    _oscTransmitState = nil;
    [_oscInputPort release];
    _oscInputPort = nil;
    [_oscOutputPort release];
    _oscOutputPort = nil;
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

/*
- (BOOL)textFieldShouldReturn:(UITextField *)textField;              // called when 'return' key pressed. return NO to ignore.
{
    [textField resignFirstResponder];
    return YES;
}
*/

#pragma mark - Actions

- (IBAction)done:(id)sender
{
    // Read IP and in/out ports
#if OSCCTRL
    _oscIPOutputText = _oscIPOutput.text;
    _oscInputPortText = _oscInputPort.text;
    _oscOutputPortText = _oscOutputPort.text;
#endif
    _oscTransmit = _oscTransmitState.selectedSegmentIndex;
    
    // Write user preferences
    [[NSUserDefaults standardUserDefaults] setInteger:_sampleRate forKey:@"sampleRate"];
    [[NSUserDefaults standardUserDefaults] setInteger:_bufferSize forKey:@"bufferSize"];
    [[NSUserDefaults standardUserDefaults] setBool:_openWidgetPanel forKey:@"openWidgetPanel"];
    [[NSUserDefaults standardUserDefaults] setInteger:_oscTransmit forKey:@"oscTransmit"];
#if OSCCTRL
    [[NSUserDefaults standardUserDefaults] setObject:_oscIPOutputText forKey:@"oscIPOutputText"];
    [[NSUserDefaults standardUserDefaults] setObject:_oscInputPortText forKey:@"oscInputPortText"];
    [[NSUserDefaults standardUserDefaults] setObject:_oscOutputPortText forKey:@"oscOutputPortText"];
#endif
    
	[[NSUserDefaults standardUserDefaults] synchronize];
        
    // Update preferences
    [((FIMainViewController*)self.delegate) restartAudioWithBufferSize:_bufferSize sampleRate:_sampleRate];
    [((FIMainViewController*)self.delegate) setOpenWidgetPanel:_openWidgetPanel];
    [((FIMainViewController*)self.delegate) setOSCParameters:_oscTransmit output:_oscIPOutputText inputport:_oscInputPortText outputport:_oscOutputPortText];
    
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
    _bufferSizeLabel.text = [NSString stringWithFormat:@"%i frames", _bufferSize];
}

- (IBAction)openWidgetPanelSwitchMoved:(id)sender
{
    _openWidgetPanel = ((UISwitch*)sender).on;
}

- (IBAction)deleteAssignationsButtonClicked:(id)sender
{
    UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Attention"
                                                        message:@"Are you sure you want to delete all your custom assignations and parameters?"
                                                       delegate:self
                                              cancelButtonTitle:@"Cancel"
                                              otherButtonTitles:@"OK", nil];
    [alertView show];
    [alertView release];
}

#pragma mark - UIAlertView Delegate Methods

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    // Cancel clicked
	if (buttonIndex == 0)
    {
		// Do nothing
	}
    
    // OK clicked
    else
    {
        NSDictionary* dict = [[NSUserDefaults standardUserDefaults] dictionaryRepresentation];
        NSArray* keysArray = [dict allKeys];
        int i = 0;
        NSString* key = nil;
        
        for (i = 0; i < [keysArray count]; ++i)
        {
            key = ((NSString*)[keysArray objectAtIndex:i]);
            if ([key compare:@"sampleRate"] != NSOrderedSame
                && [key compare:@"bufferSize"] != NSOrderedSame
                && [key compare:@"openWidgetPanel"] != NSOrderedSame
                && [key compare:@"oscTransmit"] != NSOrderedSame
                && [key compare:@"oscIPOutputText"] != NSOrderedSame)
            {
                [[NSUserDefaults standardUserDefaults] removeObjectForKey:key];
            }
        }
        
        [((FIMainViewController*)self.delegate) resetAllWidgetsPreferences];
        
        [[NSUserDefaults standardUserDefaults] synchronize];
	}
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

- (void)disableAudioWidgets
{
    _sampleRateSlider.enabled = NO;
    _sampleRateLabel.enabled = NO;
    _bufferSizeSlider.enabled = NO;
    _bufferSizeLabel.enabled = NO;
}

- (void)enableAudioWidgets
{
    _sampleRateSlider.enabled = YES;
    _sampleRateLabel.enabled = YES;
    _bufferSizeSlider.enabled = YES;
    _bufferSizeLabel.enabled = YES;
}

- (void)dealloc
{
    [_oscIPOutput release];
    [_oscTransmitState release];
    [_oscInputPort release];
    [_oscOutputPort release];
    [super dealloc];
}

@end
