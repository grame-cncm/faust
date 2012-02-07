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

#import "FIMainViewController.h"
#import "ios-faust.h"

@implementation FIMainViewController

@synthesize flipsidePopoverController = _flipsidePopoverController;
@synthesize dspView = _dspView;

TiPhoneCoreAudioRenderer* audio_device = NULL;
UI* interface = NULL;
MY_Meta metadata;
char rcfilename[256];

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - View lifecycle

- (void)loadView
{
    [super loadView];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    DSP.metadata(&metadata);
    
    interface = new CocoaUI([UIApplication sharedApplication].keyWindow, self, &metadata);
    audio_device = new TiPhoneCoreAudioRenderer(DSP.getNumInputs(), DSP.getNumOutputs());
    
    long srate = 44100;
    int	fpb = 256;
    
    DSP.init(long(srate));
	DSP.buildUserInterface(interface);
    
    const char* home = getenv ("HOME");
    const char* name = (*metadata.find("name")).second;
    if (home == 0)
        home = ".";
    snprintf(rcfilename, 256, "%s/Library/Caches/%s", home, name);
    interface->recallState(rcfilename);
    
    if (audio_device->Open(fpb, srate) < 0) {
        printf("Cannot open CoreAudio device\n");
        goto error;
    }
    
    if (audio_device->Start() < 0) {
        printf("Cannot start CoreAudio device\n");
        goto error;
    }
    
    return;
    
error:
    delete interface;
    delete audio_device;
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

- (void)dealloc
{
    interface->saveState(rcfilename);
    
    audio_device->Stop();
    audio_device->Close();
    delete audio_device;
    delete interface;
    [super dealloc];
}


#pragma mark - Flipside View Controller

- (void)flipsideViewControllerDidFinish:(FIFlipsideViewController *)controller
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
    {
        [self dismissModalViewControllerAnimated:YES];
    }
    else
    {
        [self.flipsidePopoverController dismissPopoverAnimated:YES];
        self.flipsidePopoverController = nil;
    }
}

- (void)popoverControllerDidDismissPopover:(UIPopoverController *)popoverController
{
    self.flipsidePopoverController = nil;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([[segue identifier] isEqualToString:@"showAlternate"]) 
    {
        [[segue destinationViewController] setDelegate:self];
        
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
        {
            UIPopoverController *popoverController = [(UIStoryboardPopoverSegue *)segue popoverController];
            self.flipsidePopoverController = popoverController;
            popoverController.delegate = self;
        }
    }
}

- (IBAction)togglePopover:(id)sender
{
    if (self.flipsidePopoverController)
    {
        [self.flipsidePopoverController dismissPopoverAnimated:YES];
        self.flipsidePopoverController = nil;
    }
    else
    {
        [self performSegueWithIdentifier:@"showAlternate" sender:sender];
    }
}

@end
