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
    _widgetPreferencesView.hidden = YES;
    _viewLoaded = NO;
    _currentOrientation = UIDeviceOrientationUnknown;
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
    interface->saveAbstractLayout();
    _refreshTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(refreshObjects:) userInfo:nil repeats:YES];
    
    contentView = [[[UIView alloc] initWithFrame:CGRectMake(0., 0., 10., 10.)] autorelease];
    [_dspView addSubview:contentView];
    
    _dspScrollView.delegate = self;
    
    _tapGesture =[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleTap)];
    _tapGesture.numberOfTapsRequired = 2;
    [_dspScrollView addGestureRecognizer:_tapGesture];
    
    _lockedBox = interface->getMainBox();
    
    _locationManager = nil;
    [UIAccelerometer sharedAccelerometer].delegate = nil;
    _selectedWidget = nil;
    [self loadMotionPreferences];
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
}

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
        [_dspScrollView zoomToRect:CGRectMake(absolutePosition(_lockedBox).x,
                                              absolutePosition(_lockedBox).y,
                                              _lockedBox->getW(),
                                              _lockedBox->getH())
                          animated:YES];
    }
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
    
    // No double click : lose locked box
    if (_dspScrollView.pinchGestureRecognizer.scale != 1.
        || _dspScrollView.pinchGestureRecognizer.velocity != 0.f)
    {
        _lockedBox = interface->getMainBox();
    }
}

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

- (void)showWidgetPreferencesView:(UILongPressGestureRecognizer *)gesture
{
    if ([gesture.view isKindOfClass:[FIKnob class]])
    {
        uiKnob* knob = findCorrespondingUiItem<uiKnob*>((FIResponder*)gesture.view);
        if (knob)
        {
            _selectedWidget = knob;
            knob->setSelected(YES);
            _widgetPreferencesTitleLabel.text = dynamic_cast<uiKnob*>(_selectedWidget)->fLabel.text;
            _gyroAxisSegmentedControl.selectedSegmentIndex = _selectedWidget->assignationType;
            _gyroInvertedSwitch.on = _selectedWidget->assignationInverse;
            
            _widgetPreferencesView.hidden = NO;
        }
    }
    
    else if ([gesture.view isKindOfClass:[FISlider class]])
    {
        uiSlider* slider = findCorrespondingUiItem<uiSlider*>((FIResponder*)gesture.view);
        if (slider)
        {
            _selectedWidget = slider;
            slider->setSelected(YES);
            _widgetPreferencesTitleLabel.text = dynamic_cast<uiSlider*>(_selectedWidget)->fLabel.text;
            _gyroAxisSegmentedControl.selectedSegmentIndex = _selectedWidget->assignationType;
            _gyroInvertedSwitch.on = _selectedWidget->assignationInverse;
            
            _widgetPreferencesView.hidden = NO;
        }
    }
}

- (IBAction)dismissWidgetPreferencesView:(id)sender;
{    
    _widgetPreferencesView.hidden = YES;
    
    // No selected widget
    _selectedWidget->setSelected(NO);
    _selectedWidget = NULL;
    
}

- (IBAction)widgetPreferencesChanged:(id)sender
{
    list<uiCocoaItem*>::iterator    i;
    NSString*                       key;
    
    _selectedWidget->assignationType = _gyroAxisSegmentedControl.selectedSegmentIndex;
    _selectedWidget->assignationInverse = _gyroInvertedSwitch.on;
    
    // If assignated : add widget in list
    if (_gyroAxisSegmentedControl.selectedSegmentIndex != 0)
    {
        _assignatedWidgets.push_back(_selectedWidget);
    }
    
    // If not assignated : remove widget from list
    else
    {
        for (i = _assignatedWidgets.begin(); i != _assignatedWidgets.end(); i++)
        {
            if (*i == _selectedWidget)
            {
                _assignatedWidgets.erase(i);
            }
        }
    }
    
    key = [NSString stringWithFormat:@"%@-assignation-type", _widgetPreferencesTitleLabel.text];
    [[NSUserDefaults standardUserDefaults] setInteger:_selectedWidget->assignationType forKey:key];
    
    key = [NSString stringWithFormat:@"%@-assignation-inverse", _widgetPreferencesTitleLabel.text];
    [[NSUserDefaults standardUserDefaults] setInteger:_selectedWidget->assignationInverse forKey:key];
    
    if (_assignatedWidgets.size() > 0) [self startMotion];
    else [self stopMotion];
   
}

- (void)loadMotionPreferences
{
    list<uiCocoaItem*>::iterator    i;
    NSString*                       key;
    
    for (i = interface->fWidgetList.begin(); i != interface->fWidgetList.end(); i++)
    {
        if (dynamic_cast<uiKnob*>(*i))
        {
            key = [NSString stringWithFormat:@"%@-assignation-type", dynamic_cast<uiKnob*>(*i)->fLabel.text];
            (*i)->assignationType = [[NSUserDefaults standardUserDefaults] integerForKey:key];
            key = [NSString stringWithFormat:@"%@-assignation-inverse", dynamic_cast<uiKnob*>(*i)->fLabel.text];
            (*i)->assignationInverse = [[NSUserDefaults standardUserDefaults] boolForKey:key];
            if ((*i)->assignationType != 0)
            {
                _assignatedWidgets.push_back(*i);
            }
        }
        else if (dynamic_cast<uiSlider*>(*i))
        {
            key = [NSString stringWithFormat:@"%@-assignation-type", dynamic_cast<uiSlider*>(*i)->fLabel.text];
            (*i)->assignationType = [[NSUserDefaults standardUserDefaults] integerForKey:key];
            key = [NSString stringWithFormat:@"%@-assignation-inverse", dynamic_cast<uiSlider*>(*i)->fLabel.text];
            (*i)->assignationInverse = [[NSUserDefaults standardUserDefaults] boolForKey:key];
            if ((*i)->assignationType != 0)
            {
                _assignatedWidgets.push_back(*i);
            }
        }
    }
}

- (void)startMotion
{
    if ([UIAccelerometer sharedAccelerometer].delegate == nil)
    {
        [UIAccelerometer sharedAccelerometer].delegate = self;
        _accelerometerFilter = [[FISensorFilter alloc] initWithSampleRate:kMotionUpdateRate cutoffFrequency:100];
    }
    
    if (_locationManager == nil)
    {
        _locationManager = [[CLLocationManager alloc] init];
        _locationManager.delegate = self;
        [_locationManager startUpdatingHeading];
    }
}

- (void)stopMotion
{
    if ([UIAccelerometer sharedAccelerometer].delegate == self)
    {
        [UIAccelerometer sharedAccelerometer].delegate = nil;
        [_accelerometerFilter release];
        _accelerometerFilter = nil;
    }
    
    if (_locationManager)
    {
        [_locationManager stopUpdatingHeading];
        [_locationManager release];
        _locationManager = nil;
    }
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    list<uiCocoaItem*>::iterator    i;
    float                           coef = 0.f;
    float                           value = 0.f;
    
    [_accelerometerFilter addAccelerationX:acceleration.x
                                         y:acceleration.y
                                         z:acceleration.z];

    for (i = _assignatedWidgets.begin(); i != _assignatedWidgets.end(); i++)
    {
        if (dynamic_cast<uiKnob*>(*i) || dynamic_cast<uiSlider*>(*i))
        {
            coef = 0.f;
            
            if ((*i)->assignationType == kAssignationAccelX)
            {
                coef = _accelerometerFilter.x;
            }
            else if ((*i)->assignationType == kAssignationAccelY)
            {
                coef = -_accelerometerFilter.y;
            }
            else if ((*i)->assignationType == kAssignationAccelZ)
            {
                coef = _accelerometerFilter.z;
            }
            else
            {
                continue;
            }
            
            value = (coef + 1.f) / 2.;
            if ((*i)->assignationInverse) value = 1.f - value;
            
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

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)heading
{
    list<uiCocoaItem*>::iterator    i;
    float                           coef = 0.f;
    float                           value = 0.f;
    
    for (i = _assignatedWidgets.begin(); i != _assignatedWidgets.end(); i++)
    {
        if (dynamic_cast<uiKnob*>(*i) || dynamic_cast<uiSlider*>(*i))
        {
            coef = 0.f;
            
            if ((*i)->assignationType == kAssignationCompass)
            {
                coef = heading.trueHeading;
            }
            else
            {
                continue;
            }
            
            value = coef / 360.f;
            if ((*i)->assignationInverse) value = 1.f - value;
            
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

@end
