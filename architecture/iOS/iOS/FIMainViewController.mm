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

#import <QuartzCore/QuartzCore.h>
#import "FIMainViewController.h"
#import "ios-faust.h"
#import "FIFlipsideViewController.h"
#import "FIAppDelegate.h"
#import "FICocoaUI.h"

#define kMenuBarsHeight             66
#define kMotionUpdateRate           30

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
    // General UI initializations
    _widgetPreferencesView.hidden = YES;
    _viewLoaded = NO;
    _currentOrientation = UIDeviceOrientationUnknown;
    UIView *contentView;
    [super viewDidLoad];
    ((FIAppDelegate*)[UIApplication sharedApplication].delegate).mainViewController = self;

    // Faust initialization
    DSP.metadata(&metadata);
    interface = new CocoaUI([UIApplication sharedApplication].keyWindow, self, &metadata);
    finterface = new FUI();
    audio_device = new TiPhoneCoreAudioRenderer(DSP.getNumInputs(), DSP.getNumOutputs());
    
    [self displayTitle];
    
    int sampleRate = 0;
    int	bufferSize = 0;
    
    // Read audio user preferences
    sampleRate = [[NSUserDefaults standardUserDefaults] integerForKey:@"sampleRate"];
    if (sampleRate == 0) sampleRate = 44100;
    
    bufferSize = [[NSUserDefaults standardUserDefaults] integerForKey:@"bufferSize"];
    if (bufferSize == 0) bufferSize = 256;
    
    // Build Faust interface
    DSP.init(long(sampleRate));
	DSP.buildUserInterface(interface);
    DSP.buildUserInterface(finterface);
    
    // Read parameters values
    const char* home = getenv ("HOME");
    const char* name = (*metadata.find("name")).second;
    if (home == 0)
        home = ".";
    snprintf(rcfilename, 256, "%s/Library/Caches/%s", home, name);
    finterface->recallState(rcfilename);
    [self updateGui];
    
    // Start CoreAudio
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
    
    // Notification when device orientation changed
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationChanged:)
                                                 name:UIDeviceOrientationDidChangeNotification object:nil];
    
    // Abstract layout is the layout computed without regarding screen dimensions. To be displayed, we adapt it to the device and orientition
    interface->saveAbstractLayout();
    
    // Used to refresh bargraphes
    _refreshTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(refreshObjects:) userInfo:nil repeats:YES];
    
    // Views initilizations
    contentView = [[[UIView alloc] initWithFrame:CGRectMake(0., 0., 10., 10.)] autorelease];
    [_dspView addSubview:contentView];
    _dspScrollView.delegate = self;
    
    // Double tap registration : used to zoom in the UI
    _tapGesture =[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleTap)];
    _tapGesture.numberOfTapsRequired = 2;
    [_dspScrollView addGestureRecognizer:_tapGesture];
    
    // Locked box is the currently zoomed in box. At launch time, this box is the main box
    _lockedBox = interface->getMainBox();
    
    // Widgets parameters
    _blockShake = NO;
    _locationManager = nil;
    _motionManager = nil;
    _selectedWidget = nil;
    [self loadWidgetsPreferences];
    if (_assignatedWidgets.size() > 0) [self startMotion];

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
    [self orientationChanged:nil];
    [self zoomToLockedBox];
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
    return YES;
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
    [self stopMotion];
    
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
            // If widget is assigned to a sensor, touch is used to move ref point
            if ((slider->getAssignationType() == 1
                || slider->getAssignationType() == 2
                || slider->getAssignationType() == 3
                || slider->getAssignationType() == 5)
                && (((FIResponder*)sender).motionBlocked))
            {
                slider->setAssignationRefPointY((((float)((FIResponder*)sender).value) - ((FIResponder*)sender).min) / (((FIResponder*)sender).max - ((FIResponder*)sender).min));
                
                if (slider->getAssignationType() == 1) slider->setAssignationRefPointX(_motionManager.accelerometerData.acceleration.x);
                else if (slider->getAssignationType() == 2) slider->setAssignationRefPointX(_motionManager.accelerometerData.acceleration.y);
                else if (slider->getAssignationType() == 3) slider->setAssignationRefPointX(_motionManager.accelerometerData.acceleration.z);
                else if (slider->getAssignationType() == 5)
                {
                    slider->setAssignationRefPointX(0.f);
                    slider->setAssignationRefPointY(slider->getAssignationRefPointY() * 360.f - _locationManager.heading.trueHeading);
                }
                
                NSString* key = [NSString stringWithFormat:@"%@-assignation-refpoint-x", [self urlForWidget:slider]];
                [[NSUserDefaults standardUserDefaults] setFloat:slider->getAssignationRefPointX() forKey:key];
                
                key = [NSString stringWithFormat:@"%@-assignation-refpoint-y", [self urlForWidget:slider]];
                [[NSUserDefaults standardUserDefaults] setFloat:slider->getAssignationRefPointY() forKey:key];
            }
            
            // Otherwise normal behaviour
            else
            {
                slider->modifyZone((float)((FISlider*)sender).value);
            }
        }
    }
    else if ([sender isKindOfClass:[FIButton class]])
    {
        uiButton* button = findCorrespondingUiItem<uiButton*>((FIResponder*)sender);
        if (button)
        {
            button->modifyZone((float)((FIButton*)sender).value);

            // If push button, force to zero just after to avoid an "anti-rebond" bug
            if ((float)((FIButton*)sender).type == kPushButtonType && (float)((FIButton*)sender).value == 1.)
            {
                [self performSelector:@selector(buttonSetToZero:) withObject:sender afterDelay:0.1];
            }
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
            // If widget is assigned to a sensor, touch is used to move ref point
            if ((knob->getAssignationType() == 1
                || knob->getAssignationType() == 2
                 || knob->getAssignationType() == 3
                 || knob->getAssignationType() == 5)
                && (((FIResponder*)sender).motionBlocked))
            {
                knob->setAssignationRefPointY((((float)((FIResponder*)sender).value) - ((FIResponder*)sender).min) / (((FIResponder*)sender).max - ((FIResponder*)sender).min));
                
                if (knob->getAssignationType() == 1) knob->setAssignationRefPointX(_motionManager.accelerometerData.acceleration.x);
                else if (knob->getAssignationType() == 2) knob->setAssignationRefPointX(_motionManager.accelerometerData.acceleration.y);
                else if (knob->getAssignationType() == 3) knob->setAssignationRefPointX(_motionManager.accelerometerData.acceleration.z);
                else if (knob->getAssignationType() == 5)
                {
                    knob->setAssignationRefPointX(0.f);
                    knob->setAssignationRefPointY(knob->getAssignationRefPointY() * 360.f - _locationManager.heading.trueHeading);
                }
                
                NSString* key = [NSString stringWithFormat:@"%@-assignation-refpoint-x", [self urlForWidget:knob]];
                [[NSUserDefaults standardUserDefaults] setFloat:knob->getAssignationRefPointX() forKey:key];
                
                key = [NSString stringWithFormat:@"%@-assignation-refpoint-y", [self urlForWidget:knob]];
                [[NSUserDefaults standardUserDefaults] setFloat:knob->getAssignationRefPointY() forKey:key];
            }
            
            // Otherwise normal behaviour
            else
            {
                knob->modifyZone((float)((FIKnob*)sender).value);
            }
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

// Save widgets values
- (void)saveGui
{
    finterface->saveState(rcfilename);
}

// Reflect the whole patch
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

// Force push button to go back to 0
- (void)buttonSetToZero:(id)sender
{
    uiButton* button = findCorrespondingUiItem<uiButton*>((FIResponder*)sender);
    if (button)
    {
        button->modifyZone(0.f);
        ((FIButton*)sender).value = 0.f;
        [((FIButton*)sender) setNeedsDisplay];
    }
}


#pragma mark - Misc GUI

- (void)orientationChanged:(NSNotification *)notification
{
    float                           width = 0.f;
    float                           height = 0.f;
    UIDeviceOrientation             deviceOrientation = [UIDevice currentDevice].orientation;
    
    [self updateGui];
    
    // Compute layout
    if (deviceOrientation == UIDeviceOrientationPortrait
        || deviceOrientation == UIDeviceOrientationPortraitUpsideDown)
    {
        width = min(_dspScrollView.window.frame.size.width,
                    _dspScrollView.window.frame.size.height);
        height = max(_dspScrollView.window.frame.size.width - kMenuBarsHeight,
                     _dspScrollView.window.frame.size.height - kMenuBarsHeight);
    }
    else if (deviceOrientation == UIDeviceOrientationLandscapeLeft
             || deviceOrientation == UIDeviceOrientationLandscapeRight)
    {
        width = max(_dspScrollView.window.frame.size.width,
                    _dspScrollView.window.frame.size.height);
        height = min(_dspScrollView.window.frame.size.width - kMenuBarsHeight,
                     _dspScrollView.window.frame.size.height - kMenuBarsHeight);
    }
    else
    {
        return;
    }
    
    if (_currentOrientation == deviceOrientation) return;
    _currentOrientation = deviceOrientation;

    interface->adaptLayoutToWindow(width, height);
    
    // Compute min zoom, max zooam and current zoom
    _dspScrollView.minimumZoomScale = width / (*interface->fWidgetList.begin())->getW();
    _dspScrollView.maximumZoomScale = 1.;
    
    // Compute frame of the content size
    [_dspView setFrame:CGRectMake(0.f,
                                  0.f,
                                  2 * (*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                  2 * (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];
    
    [_dspScrollView setContentSize:CGSizeMake((*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                              (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];
    
    if (!_viewLoaded)
    {
        if (_dspScrollView.minimumZoomScale != 1.)
        {
            [_dspScrollView setZoomScale:width / (*interface->fWidgetList.begin())->getW() animated:NO];
        }

        _viewLoaded = YES;
    }
    else
    {
        if (_lockedBox)
        {
            [self performSelector:@selector(zoomToLockedBox) withObject:nil afterDelay:0.1];
        }
    }
    
    // Widget preferences window, iPhone only
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
    {
        if (deviceOrientation == UIDeviceOrientationPortrait
            || deviceOrientation == UIDeviceOrientationPortraitUpsideDown)
        {
            [_colorLabel setFrame:CGRectMake(15., 282., _colorLabel.frame.size.width, _colorLabel.frame.size.height)];
            [_rLabel setFrame:CGRectMake(15., 311., _rLabel.frame.size.width, _rLabel.frame.size.height)];
            [_colorRLabel setFrame:CGRectMake(260., 311., _colorRLabel.frame.size.width, _colorRLabel.frame.size.height)];
            [_colorRSlider setFrame:CGRectMake(41., 311., 223., 23.)];
            [_gLabel setFrame:CGRectMake(15., 341., _gLabel.frame.size.width, _gLabel.frame.size.height)];
            [_colorGLabel setFrame:CGRectMake(259., 341., _colorGLabel.frame.size.width, _colorGLabel.frame.size.height)];
            [_colorGSlider setFrame:CGRectMake(41., 341., 223., 23.)];
            [_bLabel setFrame:CGRectMake(15., 371., _bLabel.frame.size.width, _bLabel.frame.size.height)];
            [_colorBLabel setFrame:CGRectMake(259., 371., _colorBLabel.frame.size.width, _colorBLabel.frame.size.height)];
            [_colorBSlider setFrame:CGRectMake(41., 371., 223., 23.)];
        }
        else if (deviceOrientation == UIDeviceOrientationLandscapeLeft
                 || deviceOrientation == UIDeviceOrientationLandscapeRight)
        {
            [_colorLabel setFrame:CGRectMake(308., 38., _colorLabel.frame.size.width, _colorLabel.frame.size.height)];
            [_rLabel setFrame:CGRectMake(308., 67., _rLabel.frame.size.width, _rLabel.frame.size.height)];
            [_colorRLabel setFrame:CGRectMake(420., 67., _colorRLabel.frame.size.width, _colorRLabel.frame.size.height)];
            [_colorRSlider setFrame:CGRectMake(306., 96., 156., 23.)];
            [_gLabel setFrame:CGRectMake(308., 331., _gLabel.frame.size.width, _gLabel.frame.size.height)];
            [_colorGLabel setFrame:CGRectMake(420., 131., _colorGLabel.frame.size.width, _colorGLabel.frame.size.height)];
            [_colorGSlider setFrame:CGRectMake(306., 160., 156., 23.)];
            [_bLabel setFrame:CGRectMake(308., 190., _bLabel.frame.size.width, _bLabel.frame.size.height)];
            [_colorBLabel setFrame:CGRectMake(420., 190., _colorBLabel.frame.size.width, _colorBLabel.frame.size.height)];
            [_colorBSlider setFrame:CGRectMake(306., 219., 156., 23.)];
        }
    }
}

// Locked box : box currently zoomed in
- (void)zoomToLockedBox
{
    if (_lockedBox == interface->getMainBox())
    {
        [_dspScrollView setZoomScale:_dspScrollView.minimumZoomScale animated:YES];
        [_dspScrollView setContentOffset:CGPointZero animated:YES];
        [_dspView setFrame:CGRectMake(0.f,
                                      0.f,
                                      (*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                      (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];
        
        [_dspScrollView setContentSize:CGSizeMake((*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                                  (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];
    }
    else
    {
        if (_dspView.frame.size.height < _dspScrollView.frame.size.height
            && _dspScrollView.zoomScale == _dspScrollView.maximumZoomScale)
        {
            [_dspScrollView scrollRectToVisible:CGRectMake(absolutePosition(_lockedBox).x,
                                                  absolutePosition(_lockedBox).y,
                                                  _lockedBox->getW(),
                                                  _lockedBox->getH())
                                       animated:YES];
        }
        else
        {
            [_dspScrollView zoomToRect:CGRectMake(absolutePosition(_lockedBox).x,
                                                  absolutePosition(_lockedBox).y,
                                                  _lockedBox->getW(),
                                                  _lockedBox->getH())
                              animated:YES];
        }
    }
}

// Display the title, in the bottom (iPhone) or top (iPad) of the screen
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

// Used to periodically refresh objects
- (void)refreshObjects:(NSTimer*)timer
{
    list<uiCocoaItem*>::iterator i;

    // Loop on uiCocoaItem elements
    for (i = ((CocoaUI*)(interface))->fWidgetList.begin(); i != ((CocoaUI*)(interface))->fWidgetList.end(); i++)
    {
        // Refresh uiBargraph objects
        if (dynamic_cast<uiBargraph*>(*i) != nil)
        {
            (*i)->reflectZone();
        }
    }
}

// Function called just after a pinch or a double click on a box
- (void)scrollViewDidZoom:(UIScrollView *)scrollView
{
    [_dspView setFrame:CGRectMake(  _dspView.frame.origin.x,
                                    _dspView.frame.origin.y,
                                    (*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                    (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];
    [_dspScrollView setContentSize:CGSizeMake(  (*interface->fWidgetList.begin())->getW() * _dspScrollView.zoomScale,
                                                (*interface->fWidgetList.begin())->getH() * _dspScrollView.zoomScale)];

    // No double click : lose locked box
    if (_dspScrollView.pinchGestureRecognizer.scale != 1.
        || _dspScrollView.pinchGestureRecognizer.velocity != 0.f)
    {
        _lockedBox = interface->getMainBox();
    }
}

// Function called just after scroll view scrolled
- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    // No double click : lose locked box
    if ([_dspScrollView.panGestureRecognizer translationInView:_dspView].x != 0.f
        && [_dspScrollView.panGestureRecognizer translationInView:_dspView].y != 0.f)
    {
        _lockedBox = interface->getMainBox();
    }
}

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{    
    return _dspView;
}

// User just double tapped somewhere in the DSP view
- (void)doubleTap
{
    uiBox* tapedBox = interface->getBoxForPoint([_tapGesture locationInView:_dspView]);

    // Avoid a strange bug
    if (tapedBox == interface->getMainBox()
        && _lockedBox == interface->getMainBox())
    {
        return;
    }
    
    // Click on already locked box : zoom out
    if (tapedBox == _lockedBox
        && _lockedBox != interface->getMainBox())
    {
        _lockedBox = interface->getMainBox();
    }
    
    // Else, zoom on clicked box
    else
    {
        _lockedBox = interface->getBoxForPoint([_tapGesture locationInView:_dspView]);   
    }
    
    [self zoomToLockedBox];
}

// Function used when only in one case : a num entry just entered in typing mode
- (void)zoomToWidget:(FIResponder*)widget
{    
    CGRect rect;
    
    if ([widget isKindOfClass:[FITextField class]])
    {
        uiNumEntry* numEntry = findCorrespondingUiItem<uiNumEntry*>((FIResponder*)widget);
        if (numEntry)
        {
            rect = interface->getBoxAbsoluteFrameForWidget(numEntry);
            [_dspScrollView zoomToRect:CGRectMake(rect.origin.x + rect.size.width / 2.f, 
                                                  rect.origin.y + rect.size.height / 2.f + _dspScrollView.window.frame.size.height / 8.f,
                                                  1.f,
                                                  1.f) 
                              animated:YES];
        }
    }
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


#pragma mark - Sensors

// Display widget preferences view
- (void)showWidgetPreferencesView:(UILongPressGestureRecognizer *)gesture
{
    list<uiCocoaItem*>::iterator    i;
    
    // Deselect all widgets
    for (i = ((CocoaUI*)(interface))->fWidgetList.begin(); i != ((CocoaUI*)(interface))->fWidgetList.end(); i++)
    {
        if (dynamic_cast<uiKnob*>(*i)
            || dynamic_cast<uiSlider*>(*i)
            || dynamic_cast<uiButton*>(*i))
        {
            (*i)->setSelected(NO);
        }
    }
    
    // Find corresponding uiCocoaItem
    if ([gesture.view isKindOfClass:[FIKnob class]])
    {
        uiKnob* knob = findCorrespondingUiItem<uiKnob*>((FIResponder*)gesture.view);
        if (knob)
        {
            _selectedWidget = knob;
        }
    }
    else if ([gesture.view isKindOfClass:[FISlider class]])
    {
        uiSlider* slider = findCorrespondingUiItem<uiSlider*>((FIResponder*)gesture.view);
        if (slider)
        {
            _selectedWidget = slider;
        }
    }
    else if ([gesture.view isKindOfClass:[FIButton class]])
    {
        uiButton* button = findCorrespondingUiItem<uiButton*>((FIResponder*)gesture.view);
        if (button)
        {
            _selectedWidget = button;
        }
    }
    
    // If no uiCocoaItem found, it's an error so we don't show the window
    if (!_selectedWidget) return;
    
    // Otherwise, set it selected (for selection display)
    _selectedWidget->setSelected(YES);
    
    // Parameter the windows
    [_gyroAxisSegmentedControl removeAllSegments];
    
    if ([gesture.view isKindOfClass:[FIKnob class]]
        || [gesture.view isKindOfClass:[FISlider class]])
    {
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"None" atIndex:0 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"X" atIndex:1 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"Y" atIndex:2 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"Z" atIndex:3 animated:NO];
        if ([CLLocationManager headingAvailable])
        {
            [_gyroAxisSegmentedControl insertSegmentWithTitle:@"Cmp" atIndex:4 animated:NO];
        }
        _gyroInvertedSwitch.hidden = NO;
        _gyroInvertedTitleLabel.hidden = NO;
        _gyroSensibilityLabel.hidden = NO;
        _gyroSensibilitySlider.hidden = NO;
        _gyroSensibilityTitleLabel.hidden = NO;

        _widgetPreferencesTitleLabel.text = _selectedWidget->getName();
    }
    
    else if ([gesture.view isKindOfClass:[FIButton class]])
    {
        uiButton* button = findCorrespondingUiItem<uiButton*>((FIResponder*)gesture.view);
        if (button)
        {
            [_gyroAxisSegmentedControl insertSegmentWithTitle:@"None" atIndex:0 animated:NO];
            [_gyroAxisSegmentedControl insertSegmentWithTitle:@"Shk" atIndex:1 animated:NO];
            
            _gyroInvertedSwitch.hidden = YES;
            _gyroInvertedTitleLabel.hidden = YES;
            _gyroSensibilityLabel.hidden = YES;
            _gyroSensibilitySlider.hidden = YES;
            _gyroSensibilityTitleLabel.hidden = YES;

            _widgetPreferencesTitleLabel.text = dynamic_cast<uiButton*>(_selectedWidget)->fButton.title;
            
            if (_selectedWidget->getAssignationType() == kAssignationNone) _gyroAxisSegmentedControl.selectedSegmentIndex = 0;
            else if (_selectedWidget->getAssignationType() == kAssignationShake) _gyroAxisSegmentedControl.selectedSegmentIndex = 1;
        }
    }
    
    // Display right values for parameters
    [self updateWidgetPreferencesView];
    
    // Show the window
    _widgetPreferencesView.hidden = NO;
    
    // Fade in
    CATransition *animation = [CATransition animation];
    [animation setDuration:0.5];
    [animation setType:kCATransitionFade];
    [animation setSubtype:kCATransitionFromLeft];
    [animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut]];	
    
    [[_dspView.window layer] addAnimation:animation forKey:@"ShowWidgetPreferences"];    
}

// Display right values for parameters
- (void)updateWidgetPreferencesView
{
    // For knobs and sliders
    if (dynamic_cast<uiKnob*>(_selectedWidget)
        || dynamic_cast<uiSlider*>(_selectedWidget))
    {
        if (_selectedWidget->getAssignationType() == kAssignationCompass) _gyroAxisSegmentedControl.selectedSegmentIndex = 4;
        else _gyroAxisSegmentedControl.selectedSegmentIndex = _selectedWidget->getAssignationType();
    }
    
    // For buttons
    else if (dynamic_cast<uiButton*>(_selectedWidget))
    {
        if (_selectedWidget->getAssignationType() == kAssignationNone) _gyroAxisSegmentedControl.selectedSegmentIndex = 0;
        else if (_selectedWidget->getAssignationType() == kAssignationShake) _gyroAxisSegmentedControl.selectedSegmentIndex = 1;
        _gyroAxisSegmentedControl.selectedSegmentIndex = _selectedWidget->getAssignationType();
        
    }
    
    // Common parameters for all types
    _gyroInvertedSwitch.on = _selectedWidget->getAssignationInverse();
    _gyroSensibilitySlider.value = _selectedWidget->getAssignationSensibility();
    _gyroSensibilityLabel.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getAssignationSensibility()];
    _colorRSlider.value = _selectedWidget->getR();
    _colorRLabel.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getR()];
    _colorGSlider.value = _selectedWidget->getG();
    _colorGLabel.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getG()];
    _colorBSlider.value = _selectedWidget->getB();
    _colorBLabel.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getB()];
}

// Hide widget preferences view
- (IBAction)dismissWidgetPreferencesView:(id)sender;
{
    // Unselect widget
    _selectedWidget->setSelected(NO);
    _selectedWidget = NULL;
    
    // Hide it
    _widgetPreferencesView.hidden = YES;
    
    // Fade out
    CATransition *animation = [CATransition animation];
    [animation setDuration:0.5];
    [animation setType:kCATransitionFade];
    [animation setSubtype:kCATransitionFromLeft];
    [animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut]];	
    
    [[_dspView.window layer] addAnimation:animation forKey:@"DismissWidgetPreferences"];
}

// Function called each time a parameter has been changed
- (IBAction)widgetPreferencesChanged:(id)sender
{
    list<uiCocoaItem*>::iterator    i;
    NSString*                       key;
    NSString*                       str;
    BOOL                            found = false;
    
    // If user changed the sensor assignation, program resets ref point to default values
    if (sender == _gyroAxisSegmentedControl)
    {
        // Get title of selected tab for sensor assignation
        str = [NSString stringWithString:[_gyroAxisSegmentedControl titleForSegmentAtIndex:_gyroAxisSegmentedControl.selectedSegmentIndex]];

        // Set default values regarding assignation type
        if ([str compare:@"None"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationNone);
            _selectedWidget->setAssignationRefPointX(0.);
            _selectedWidget->setAssignationRefPointY(0.);
        }
        else if ([str compare:@"X"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationAccelX);
            _selectedWidget->setAssignationRefPointX(0.);
            _selectedWidget->setAssignationRefPointY(0.5);
        }
        else if ([str compare:@"Y"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationAccelY);
            _selectedWidget->setAssignationRefPointX(0.);
            _selectedWidget->setAssignationRefPointY(0.5);
        }
        else if ([str compare:@"Z"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationAccelZ);
            _selectedWidget->setAssignationRefPointX(0.);
            _selectedWidget->setAssignationRefPointY(0.5);
        }
        else if ([str compare:@"Shk"] == NSOrderedSame)
        {
            NSLog(@"Shk");
            _selectedWidget->setAssignationType(kAssignationShake);
            _selectedWidget->setAssignationRefPointX(0.);
            _selectedWidget->setAssignationRefPointY(0.);
        }
        else if ([str compare:@"Cmp"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationCompass);
            _selectedWidget->setAssignationRefPointX(0.);
            _selectedWidget->setAssignationRefPointY(0.);
        }
        else
        {
            _selectedWidget->setAssignationType(kAssignationNone);
            _selectedWidget->setAssignationRefPointX(0.);
            _selectedWidget->setAssignationRefPointY(0.);
        }
    }
    
    // Write parameters in the widget object
    _selectedWidget->setAssignationInverse(_gyroInvertedSwitch.on);
    _selectedWidget->setAssignationSensibility(_gyroSensibilitySlider.value);
    _gyroSensibilityLabel.text = [NSString stringWithFormat:@"%1.1f", _gyroSensibilitySlider.value];
    
    _selectedWidget->setColor(_colorRSlider.value, _colorGSlider.value, _colorBSlider.value);
    _colorRLabel.text = [NSString stringWithFormat:@"%1.1f", _colorRSlider.value];
    _colorGLabel.text = [NSString stringWithFormat:@"%1.1f", _colorGSlider.value];
    _colorBLabel.text = [NSString stringWithFormat:@"%1.1f", _colorBSlider.value];
    
    // If default parameters : remove widget from list
    if (_selectedWidget->getAssignationType() == kAssignationNone)
    {
        for (i = _assignatedWidgets.begin(); i != _assignatedWidgets.end(); i++)
        {
            if (*i == _selectedWidget)
            {
                _assignatedWidgets.erase(i);
            }
        }
    }
    
    // If assignated : add widget in list if it's not the case already
    else
    {
        for (i = _assignatedWidgets.begin(); i != _assignatedWidgets.end(); i++)
        {
            if (*i == _selectedWidget)
            {
                found = true;
            }
        }
        if (!found) _assignatedWidgets.push_back(_selectedWidget);
    }

    // Save parameters in user defaults
    key = [NSString stringWithFormat:@"%@-assignation-type", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setInteger:_selectedWidget->getAssignationType() forKey:key];
    
    key = [NSString stringWithFormat:@"%@-assignation-inverse", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setInteger:_selectedWidget->getAssignationInverse() forKey:key];
    
    key = [NSString stringWithFormat:@"%@-assignation-sensibility", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getAssignationSensibility() forKey:key];
    
    key = [NSString stringWithFormat:@"%@-assignation-refpoint-x", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getAssignationRefPointX() forKey:key];
    
    key = [NSString stringWithFormat:@"%@-assignation-refpoint-y", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getAssignationRefPointY() forKey:key];
    
    key = [NSString stringWithFormat:@"%@-r", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getR() + 1. forKey:key];
    
    key = [NSString stringWithFormat:@"%@-g", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getG() + 1. forKey:key];
    
    key = [NSString stringWithFormat:@"%@-b", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getB() + 1. forKey:key];
    
    // If assignation type is not kAssignationNone, we start motion
    if (_assignatedWidgets.size() > 0) [self startMotion];
    else [self stopMotion];
}

// Reset widget parameters
- (IBAction)resetWidgetPreferences:(id)sender
{
    _selectedWidget->resetParameters();
    [self updateWidgetPreferencesView];
    [self widgetPreferencesChanged:_gyroAxisSegmentedControl];
}

// At application launch time, loading preferences for all widgets
- (void)loadWidgetsPreferences
{
    list<uiCocoaItem*>::iterator    i;
    NSString*                       key;
    NSString*                       key2;
    NSString*                       key3;
    
    for (i = interface->fWidgetList.begin(); i != interface->fWidgetList.end(); i++)
    {
        if (dynamic_cast<uiKnob*>(*i)
            || dynamic_cast<uiSlider*>(*i)
            || dynamic_cast<uiButton*>(*i))
        {
            // Sensor assignation
            key = [NSString stringWithFormat:@"%@-assignation-type", [self urlForWidget:(*i)]];
            (*i)->setAssignationType([[NSUserDefaults standardUserDefaults] integerForKey:key]);
            key = [NSString stringWithFormat:@"%@-assignation-inverse", [self urlForWidget:(*i)]];
            (*i)->setAssignationInverse([[NSUserDefaults standardUserDefaults] boolForKey:key]);
            key = [NSString stringWithFormat:@"%@-assignation-sensibility", [self urlForWidget:(*i)]];
            (*i)->setAssignationSensibility([[NSUserDefaults standardUserDefaults] floatForKey:key]);
            if ((*i)->getAssignationSensibility() == 0.) (*i)->setAssignationSensibility(1.);
            key = [NSString stringWithFormat:@"%@-assignation-refpoint-x", [self urlForWidget:(*i)]];
            (*i)->setAssignationRefPointX([[NSUserDefaults standardUserDefaults] floatForKey:key]);
            key = [NSString stringWithFormat:@"%@-assignation-refpoint-y", [self urlForWidget:(*i)]];
            (*i)->setAssignationRefPointY([[NSUserDefaults standardUserDefaults] floatForKey:key]);
            
            // Color
            key = [NSString stringWithFormat:@"%@-r", [self urlForWidget:(*i)]];
            key2 = [NSString stringWithFormat:@"%@-g", [self urlForWidget:(*i)]];
            key3 = [NSString stringWithFormat:@"%@-b", [self urlForWidget:(*i)]];
            (*i)->setColor([[NSUserDefaults standardUserDefaults] floatForKey:key] - 1.,
                           [[NSUserDefaults standardUserDefaults] floatForKey:key2] - 1.,
                           [[NSUserDefaults standardUserDefaults] floatForKey:key3] - 1.);
            
            // Default color
            if ((*i)->getR() == -1
                && (*i)->getG() == -1
                && (*i)->getB() == -1)
            {
                (*i)->setColor(0.f, 0.f, 1.f);
            }
            
            // Add in assignation list if there is a sensor assignation and / or color is not default
            if ((*i)->getAssignationType() != 0)
            {
                _assignatedWidgets.push_back(*i);
            }
        }
    }
}

// Start updating sensors
- (void)startMotion
{
    // Motion
    if (_motionManager == nil)
    {
        _motionManager = [[CMMotionManager alloc] init];
        _sensorFilter = [[FISensorFilter alloc] initWithSampleRate:kMotionUpdateRate * 10 cutoffFrequency:100];
        [_motionManager startAccelerometerUpdates];
        _motionTimer = [NSTimer scheduledTimerWithTimeInterval:1./kMotionUpdateRate
                                                        target:self 
                                                      selector:@selector(updateMotion)
                                                      userInfo:nil 
                                                       repeats:YES];
    }
    
    // Location
    if (_locationManager == nil)
    {
        _locationManager = [[CLLocationManager alloc] init];
        _locationManager.delegate = self;
        [_locationManager startUpdatingHeading];
    }
}

// Stop updating sensors
- (void)stopMotion
{
    // Motion
    if (_motionManager != nil)
    {
        [_motionManager stopAccelerometerUpdates];
        [_motionManager release];
        _motionManager = nil;
        [_motionTimer invalidate];
    }
    
    // Location
    if (_locationManager)
    {
        [_locationManager stopUpdatingHeading];
        [_locationManager release];
        _locationManager = nil;
    }
}

- (void)endBlockShake
{
    _blockShake = NO;
}

// The function periodically called to refresh motion sensors
- (void)updateMotion
{
    list<uiCocoaItem*>::iterator    i;
    float                           coef = 0.f;
    float                           value = 0.f;
    float                           a = 0.;
    float                           b = 0.;
    float                           sign = 1.;
    
    [_sensorFilter addAccelerationX:_motionManager.accelerometerData.acceleration.x
                                  y:_motionManager.accelerometerData.acceleration.y
                                  z:_motionManager.accelerometerData.acceleration.z];

    for (i = _assignatedWidgets.begin(); i != _assignatedWidgets.end(); i++)
    {
        if ((dynamic_cast<uiKnob*>(*i) && !dynamic_cast<uiKnob*>(*i)->fKnob.motionBlocked)
            || (dynamic_cast<uiSlider*>(*i) && !dynamic_cast<uiSlider*>(*i)->fSlider.motionBlocked)
            || dynamic_cast<uiButton*>(*i))
        {
            coef = 0.f;
            
            if ((*i)->getAssignationType() == kAssignationAccelX)
            {
                coef = _sensorFilter.x * (*i)->getAssignationSensibility();
            }
            else if ((*i)->getAssignationType() == kAssignationAccelY)
            {
                coef = -_sensorFilter.y * (*i)->getAssignationSensibility();
            }
            else if ((*i)->getAssignationType() == kAssignationAccelZ)
            {
                coef = _sensorFilter.z * (*i)->getAssignationSensibility();
            }
            else if ((*i)->getAssignationType() == kAssignationShake)
            {
                // Shake detection
                if (!_blockShake
                    && (fabsf(_sensorFilter.x) > 1.4
                        || fabsf(_sensorFilter.y) > 1.4
                        || fabsf(_sensorFilter.z) > 1.4))
                {
                    coef = 1.f;
                    _blockShake = YES;
                    [self performSelector:@selector(endBlockShake) withObject:nil afterDelay:0.3];
                }
                else
                {
                    coef = 0.f;
                }
            }
            else
            {
                continue;
            }
            
            if ((*i)->getAssignationInverse()) sign = -1.;
            else sign = 1.;
             
            // Case 1 : the ref point creates 2 line coeficients if sensibility > 1.
            /*
            float                           x1 = 0.;
            float                           y1 = 0.;
            float                           x2 = 0.;
            float                           y2 = 0.;
            
            if ((*i)->assignationSensibility >= 1.)
            {    
                if (coef < (*i)->assignationRefPointX)
                {
                    // Find 2 points
                    x1 = max(- 1.f / (*i)->assignationSensibility, -1.f); // x1 = - 1 / s
                    y1 = sign * ((*i)->assignationSensibility / 2.f) * x1 + 0.5; // y1 = ax1 + b with a = s / 2 and b = 0.5
                    x2 = (*i)->assignationRefPointX;
                    y2 = (*i)->assignationRefPointY;
                    
                    // Find a and b of the line
                    a = (y2 - y1) / (x2 - x1);
                    b = y1 - a * x1;
                }
                else if (coef >= (*i)->assignationRefPointX)
                {
                    // Find 2 points
                    x1 = (*i)->assignationRefPointX;
                    y1 = (*i)->assignationRefPointY;
                    x2 = min(1.f / (*i)->assignationSensibility, 1.f); // x1 = 1 / s
                    y2 = sign * ((*i)->assignationSensibility / 2.f) * x2 + 0.5; // y1 = ax1 + b with a = s / 2 and b = 0.5
                    
                    // Find a and b of the line
                    a = (y2 - y1) / (x2 - x1);
                    b = y1 - a * x1;
                }
            }
            else*/
            
            // Case 2 : the ref point only moves line offset
            a = sign * (*i)->getAssignationSensibility() / 2.; // y = ax + b with a = s / 2 and b = (*i)->assignationRefPointY
            b = (*i)->getAssignationRefPointY();
            
            value = a * coef + b;

            if (dynamic_cast<uiKnob*>(*i))
            {
                value = value * (dynamic_cast<uiKnob*>(*i)->fKnob.max - dynamic_cast<uiKnob*>(*i)->fKnob.min) + dynamic_cast<uiKnob*>(*i)->fKnob.min;
            }
            else if (dynamic_cast<uiSlider*>(*i))
            {
                value = value * (dynamic_cast<uiSlider*>(*i)->fSlider.max - dynamic_cast<uiSlider*>(*i)->fSlider.min) + dynamic_cast<uiSlider*>(*i)->fSlider.min;
            }
            else if (dynamic_cast<uiButton*>(*i))
            {
                if (coef == 0.f)
                {
                    continue;
                }
                else if (coef == 1.f && dynamic_cast<uiButton*>(*i)->fButton.type == kPushButtonType)
                {
                    value = 1.f;
                }
                else if (coef == 1.f && dynamic_cast<uiButton*>(*i)->fButton.type == kToggleButtonType)
                {
                    if (dynamic_cast<uiButton*>(*i)->fButton.value == 1) value = 0;
                    else if (dynamic_cast<uiButton*>(*i)->fButton.value == 0) value = 1;
                }
            }

            (*i)->modifyZone(value);
            (*i)->reflectZone();
            
            // Force button refresh (otherwise nothing happens)
            if (dynamic_cast<uiButton*>(*i) && dynamic_cast<uiButton*>(*i)->fButton.type == kPushButtonType)
            {
                dynamic_cast<uiButton*>(*i)->fButton.value = value;
                [dynamic_cast<uiButton*>(*i)->fButton setNeedsDisplay];
            }
        }
    }
}

// The function called when compass has moved
- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)heading
{
    list<uiCocoaItem*>::iterator    i;
    float                           coef = 0.f;
    float                           value = 0.f;
    
    [_sensorFilter addHeading:heading.magneticHeading];

    for (i = _assignatedWidgets.begin(); i != _assignatedWidgets.end(); i++)
    {
        if (dynamic_cast<uiKnob*>(*i) || dynamic_cast<uiSlider*>(*i) || dynamic_cast<uiButton*>(*i))
        {
            coef = 0.f;
            
            if ((*i)->getAssignationType() == kAssignationCompass)
            {
                coef = (int)round(_sensorFilter.h * (*i)->getAssignationSensibility() + (*i)->getAssignationRefPointY()) % 360;
                value = coef / 360.f;
                if ((*i)->getAssignationInverse()) value = 1.f - value;
                
                if (dynamic_cast<uiKnob*>(*i))
                {
                    value = value * (dynamic_cast<uiKnob*>(*i)->fKnob.max - dynamic_cast<uiKnob*>(*i)->fKnob.min) + dynamic_cast<uiKnob*>(*i)->fKnob.min;
                }
                else if (dynamic_cast<uiSlider*>(*i))
                {
                    value = value * (dynamic_cast<uiSlider*>(*i)->fSlider.max - dynamic_cast<uiSlider*>(*i)->fSlider.min) + dynamic_cast<uiSlider*>(*i)->fSlider.min;
                }
                
                (*i)->modifyZone(value);
                (*i)->reflectZone();
            }
        }
    }
}

// Error updating compass value
- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    if ([error code] == kCLErrorDenied)
    {
        [manager stopUpdatingHeading];
    }
    else if ([error code] == kCLErrorHeadingFailure)
    {
    }
}

- (NSString*)urlForWidget:(uiCocoaItem*)widget
{
    list<uiCocoaItem*>::iterator    i = interface->fWidgetList.end();
    uiCocoaItem*                    currentWidget = widget;
    NSString*                       result = [NSString stringWithString:@""];
    
    while (currentWidget != *interface->fWidgetList.begin())
    {
        if (currentWidget->getParent() == (*i))
        {
            result = [NSString stringWithFormat:@"%@-%@", (*i)->getName(), result];
            currentWidget = (*i);
        }
        
        i--;
    }
    
    result = [NSString stringWithFormat:@"%@-%@", result, widget->getName()];
    
    return result;
}

@end
