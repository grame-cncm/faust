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
#import "FIFlipsideViewController.h"
#import "FIAppDelegate.h"

@implementation FIMainViewController

@synthesize flipsidePopoverController = _flipsidePopoverController;
@synthesize dspView = _dspView;

TiPhoneCoreAudioRenderer* audio_device = NULL;
CocoaUI* interface = NULL;
FUI* finterface = NULL;
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
    
    ((FIAppDelegate*)[UIApplication sharedApplication].delegate).mainViewController = self;
    
    DSP.metadata(&metadata);
    
    interface = new CocoaUI([UIApplication sharedApplication].keyWindow, self, &metadata);
    finterface = new FUI();
    audio_device = new TiPhoneCoreAudioRenderer(DSP.getNumInputs(), DSP.getNumOutputs());
    
    int sampleRate = 0;
    int	bufferSize = 0;
    
    // Read user preferences
    sampleRate = [[NSUserDefaults standardUserDefaults] integerForKey:@"sampleRate"];
    if (sampleRate == 0) sampleRate = 44100;
    
    bufferSize = [[NSUserDefaults standardUserDefaults] integerForKey:@"bufferSize"];
    if (bufferSize == 0) bufferSize = 256;
    
    DSP.init(long(sampleRate));
	DSP.buildUserInterface(interface);
    DSP.buildUserInterface(finterface);
    
    const char* home = getenv ("HOME");
    const char* name = (*metadata.find("name")).second;
    if (home == 0)
        home = ".";
    snprintf(rcfilename, 256, "%s/Library/Caches/%s", home, name);
    finterface->recallState(rcfilename);
    [self updateGui];
    
    if (audio_device->Open(bufferSize, sampleRate) < 0)
    {
        printf("Cannot open CoreAudio device\n");
        goto error;
    }
    
    if (audio_device->Start() < 0)
    {
        printf("Cannot start CoreAudio device\n");
        goto error;
    }
    
    return;
    
error:
    delete interface;
    delete finterface;
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
    finterface->saveState(rcfilename);
    
    audio_device->Stop();
    audio_device->Close();
    delete audio_device;
    delete interface;
    delete finterface;
    [super dealloc];
}


#pragma mark - DSP view

// Sends corresponding uiItem subtype object to the UIReponder subtype object passed in argument
// Sends NULL if nothing has been found

template <typename T>
T findCorrespondingUiItem(UIResponder* sender)
{
    list<uiItem*>::iterator i;
    
    // Loop on uiItem elements
    for (i = ((CocoaUI*)(interface))->fWidgetList.begin(); i != ((CocoaUI*)(interface))->fWidgetList.end(); i++)
    {
        // Does current uiItem match T ?
        if (dynamic_cast<T>(*i) != nil)
        {
            // Test sender type
            if (typeid(T) == typeid(uiSlider*))
            {
                if (sender == dynamic_cast<uiSlider*>(*i)->fSlider) return dynamic_cast<T>(*i);
            }
            else if (typeid(T) == typeid(uiButton*))
            {
                if (sender == dynamic_cast<uiButton*>(*i)->fButton) return dynamic_cast<T>(*i);
            }
        }
    }
    
    return NULL;
}


// User actions notifications
// changed : from slider
// pressed / released : from button

- (void)changed:(id)sender
{
    uiSlider* slider = findCorrespondingUiItem<uiSlider*>((UIResponder*)sender);
    if (slider)
    {
        slider->modifyZone((float)((UISlider*)sender).value);
        [slider->fTextField setPlaceholder:[NSString stringWithFormat:@"%1.2f", ((float)((UISlider*)sender).value)]];
    }
}

- (void)pressed:(id)sender
{
    uiButton* button = findCorrespondingUiItem<uiButton*>((UIResponder*)sender);
    if (button)
    {
        button->modifyZone(1.0f);
    }
}

- (void)released:(id)sender
{
    uiButton* button = findCorrespondingUiItem<uiButton*>((UIResponder*)sender);
    if (button)
    {
        button->modifyZone(0.0f);
    }
}

- (void)saveGui
{
    finterface->saveState(rcfilename);
}

- (void)updateGui
{
    list<uiItem*>::iterator i;
    
    // Loop on uiItem elements
    for (i = ((CocoaUI*)(interface))->fWidgetList.begin(); i != ((CocoaUI*)(interface))->fWidgetList.end(); i++)
    {
        (*i)->reflectZone();
    }
}

#pragma mark - Flipside View Controller

- (void)restartAudioWithBufferSize:(int)bufferSize sampleRate:(int)sampleRate
{
    finterface->saveState(rcfilename);
    
    if (audio_device->Stop() < 0)
    {
        printf("Cannot stop CoreAudio device\n");
        goto error;
    }
    
    DSP.init(long(sampleRate));
    
    if (audio_device->SetParameters(bufferSize, sampleRate) < 0)
    {
        printf("Cannot set parameters to CoreAudio device\n");
        goto error;
    }
    
    if (audio_device->Start() < 0)
    {
        printf("Cannot start CoreAudio device\n");
        goto error;
    }
    
    finterface->recallState(rcfilename);
    
    return;
    
error:
    delete audio_device;
}

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
