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
@synthesize dspScrollView = _dspScrollView;

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
    _viewLoaded = NO;
    UIView *contentView;
    
    [super viewDidLoad];
    
    ((FIAppDelegate*)[UIApplication sharedApplication].delegate).mainViewController = self;
    
    DSP.metadata(&metadata);
    
    interface = new CocoaUI([UIApplication sharedApplication].keyWindow, self, &metadata);
    finterface = new FUI();
    audio_device = new TiPhoneCoreAudioRenderer(DSP.getNumInputs(), DSP.getNumOutputs());
    
    [self displayTitle];
    
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
    
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationChanged:)
                                                 name:UIDeviceOrientationDidChangeNotification object:nil];
    interface->adaptLayoutToDevice();
    _refreshTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(refreshObjects:) userInfo:nil repeats:YES];
    
    contentView = [[[UIView alloc] initWithFrame:CGRectMake(0., 0., 10., 10.)] autorelease];
    [_dspView addSubview:contentView];
    
    _dspScrollView.delegate = self;
    _dspScrollView.canCancelContentTouches = NO;
    _dspScrollView.minimumZoomScale = min(  _dspScrollView.frame.size.width / (*interface->fWidgetList.begin())->getW(),
                                            _dspScrollView.frame.size.height / (*interface->fWidgetList.begin())->getH());
    /*if (dynamic_cast<uiBox*>(*interface->fWidgetList.begin())->fMinWidth < _dspScrollView.frame.size.width)
    {
        _dspScrollView.maximumZoomScale = 1.;
    }
    else*/
    {
        _dspScrollView.maximumZoomScale = 1.5;
    }
    [_dspScrollView setZoomScale:_dspScrollView.frame.size.width / (*interface->fWidgetList.begin())->getW() animated:NO];
    _lockedRect = CGRectMake(0.f, 0.f, 0.f, 0.f);
    
    _tapGesture =[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userDidDoubleTap)];
    _tapGesture.numberOfTapsRequired = 2;
    [_dspView addGestureRecognizer:_tapGesture];
    
    return;
    
error:
    delete interface;
    delete finterface;
    delete audio_device;
}

-(void)userDidDoubleTap
{
    CGRect rect = interface->getBoxAbsoluteFrameForPoint([_tapGesture locationInView:_dspView]);
    
    if (_lockedRect.origin.x != 0.f
        && _lockedRect.origin.y != 0.f
        && _lockedRect.size.width != 0.f
        && _lockedRect.size.height != 0.f)
    {
        [_dspScrollView setZoomScale:_dspScrollView.frame.size.width / (*interface->fWidgetList.begin())->getW() animated:YES];
    }
    else
    {
        [_dspScrollView zoomToRect:rect animated:YES];
        _lockedRect = rect;
    }
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
    _viewLoaded = YES;
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
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
    
    [_tapGesture release];
    finterface->saveState(rcfilename);
    
    audio_device->Stop();
    audio_device->Close();
    delete audio_device;
    delete interface;
    delete finterface;
    
    [_refreshTimer invalidate];
    
    [super dealloc];
}


#pragma mark - DSP view

// Sends corresponding uiCocoaItem subtype object to the UIReponder subtype object passed in argument
// Sends NULL if nothing has been found

template <typename T>
T findCorrespondingUiItem(FIResponder* sender)
{
    list<uiCocoaItem*>::iterator i;
    
    // Loop on uiCocoaItem elements
    for (i = ((CocoaUI*)(interface))->fWidgetList.begin(); i != ((CocoaUI*)(interface))->fWidgetList.end(); i++)
    {
        // Does current uiCocoaItem match T ?
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
            else if (typeid(T) == typeid(uiNumEntry*))
            {
                if (sender == dynamic_cast<uiNumEntry*>(*i)->fTextField) return dynamic_cast<T>(*i);
            }
            else if (typeid(T) == typeid(uiKnob*))
            {
                if (sender == dynamic_cast<uiKnob*>(*i)->fKnob) return dynamic_cast<T>(*i);
            }
            else if (typeid(T) == typeid(uiBox*))
            {
                if (sender == dynamic_cast<uiBox*>(*i)->fTabView) return dynamic_cast<T>(*i);
            }
        }
    }
    
    return NULL;
}


// User actions notifications

- (void)responderValueDidChange:(float)value sender:(id)sender
{
    if ([sender isKindOfClass:[FISlider class]])
    {
        uiSlider* slider = findCorrespondingUiItem<uiSlider*>((FIResponder*)sender);
        if (slider)
        {
            slider->modifyZone((float)((FISlider*)sender).value);
        }
    }
    else if ([sender isKindOfClass:[FIButton class]])
    {
        uiButton* button = findCorrespondingUiItem<uiButton*>((FIResponder*)sender);
        if (button)
        {
            button->modifyZone((float)((FIButton*)sender).value);
        }
    }
    else if ([sender isKindOfClass:[FITextField class]])
    {
        uiNumEntry* numEntry = findCorrespondingUiItem<uiNumEntry*>((FIResponder*)sender);
        if (numEntry)
        {
            numEntry->modifyZone((float)((FITextField*)sender).value);
        }
    }
    else if ([sender isKindOfClass:[FIKnob class]])
    {
        uiKnob* knob = findCorrespondingUiItem<uiKnob*>((FIResponder*)sender);
        if (knob)
        {
            knob->modifyZone((float)((FIKnob*)sender).value);
        }
    }
    else if ([sender isKindOfClass:[FITabView class]])
    {
        uiBox* box = findCorrespondingUiItem<uiBox*>((FIResponder*)sender);
        if (box)
        {
            box->reflectZone();
        }
    }
    else NSLog(@"UIItem not implemented yet :)");
    
}

- (void)saveGui
{
    finterface->saveState(rcfilename);
}

- (void)updateGui
{
    list<uiCocoaItem*>::iterator i;
    
    // Loop on uiCocoaItem elements
    for (i = ((CocoaUI*)(interface))->fWidgetList.begin(); i != ((CocoaUI*)(interface))->fWidgetList.end(); i++)
    {
        // Refresh GUI
        (*i)->reflectZone();
    }
}


#pragma mark - Misc GUI

- (void)orientationChanged:(NSNotification *)notification
{
    [self updateGui];
    
    _lockedRect = CGRectMake(0.f, 0.f, 0.f, 0.f);
    
    [_dspView setFrame:CGRectMake(  _dspView.frame.origin.x,
                                    _dspView.frame.origin.y,
                                    5. * (*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                    5. * (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];

    [_dspScrollView setContentSize:CGSizeMake(  (*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                                (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];

}

- (void)displayTitle
{
    NSString*       titleString = nil;
    
    if (*metadata.find("name") != *metadata.end())
    {
        const char* name = (*metadata.find("name")).second;
        titleString = [[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding];
    }
    
    if (*metadata.find("author") != *metadata.end())
    {
        const char* name = (*metadata.find("author")).second;
        if (titleString)
        {
            titleString = [titleString stringByAppendingFormat:@" | %s", name];
        }
        else
        {
            titleString = [[NSString alloc] initWithCString:name encoding:NSASCIIStringEncoding];
        }
    }
    
    if (!titleString) titleString = [[NSString alloc] initWithString:@"Faust | Grame"];
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
    {
        _titleLabel.text = titleString;
    }
    else if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
    {
        _titleNavigationItem.title = titleString;
    }
}


- (void)refreshObjects:(NSTimer*)timer
{
    list<uiCocoaItem*>::iterator i;

    // Loop on uiCocoaItem elements
    for (i = ((CocoaUI*)(interface))->fWidgetList.begin(); i != ((CocoaUI*)(interface))->fWidgetList.end(); i++)
    {
        // Refresh only uiBargraph objects
        if (dynamic_cast<uiBargraph*>(*i) != nil)
        {
            // Refresh GUI
            (*i)->reflectZone();
        }
    }
}

- (void)scrollViewDidZoom:(UIScrollView *)scrollView
{
    [_dspView setFrame:CGRectMake(  _dspView.frame.origin.x,
                                    _dspView.frame.origin.y,
                                    (*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                    (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];
    
    [_dspScrollView setContentSize:CGSizeMake(  (*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                                (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];
    
    _lockedRect = CGRectMake(0.f, 0.f, 0.f, 0.f);
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    _lockedRect = CGRectMake(0.f, 0.f, 0.f, 0.f);
}

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{    
    return _dspView;
}

#pragma mark - Audio

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
