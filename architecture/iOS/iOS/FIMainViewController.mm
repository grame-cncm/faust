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
#include "faust/gui/OSCUI.h"

#define kMenuBarsHeight             66
#define kMotionUpdateRate           30

#define kRefreshTimerInterval       0.04

// Test Jack
#define kJackViewHeight 130
#define kJackViewAnimationDuration 0.2

@implementation FIMainViewController

@synthesize flipsidePopoverController = _flipsidePopoverController;
@synthesize dspView = _dspView;
@synthesize dspScrollView = _dspScrollView;
audio* audio_device = NULL;
CocoaUI* interface = NULL;
FUI* finterface = NULL;
GUI* oscinterface = NULL;
MY_Meta metadata;
char rcfilename[256];

int sampleRate = 0;
int	bufferSize = 0;
BOOL openWidgetPanel = YES;
int uiCocoaItem::gItemCount = 0;

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)loadView
{
    [super loadView];
}

#ifdef JACK_IOS

static void jack_shutdown_callback(const char* message, void* arg)
{
    FIMainViewController* self = (FIMainViewController*)arg;
    dispatch_async(dispatch_get_main_queue(), ^{
        [self closeJack :message];
    });
}

#endif

- (void)viewDidLoad
{
    // General UI initializations
    _widgetPreferencesView.hidden = YES;
    _viewLoaded = NO;
    _currentOrientation = UIDeviceOrientationUnknown;
    UIView *contentView;
    [super viewDidLoad];
    ((FIAppDelegate*)[UIApplication sharedApplication].delegate).mainViewController = self;
    _openPanelChanged = YES;
    
    // Faust initialization
    DSP.metadata(&metadata);
    
    // Read parameters values
    const char* home = getenv("HOME");
    if (home == 0) {
        home = ".";
    }
 
    if ((*metadata.find("name")).second) {
        _name = (*metadata.find("name")).second;
    } else {
        _name = [[[NSProcessInfo processInfo] processName] UTF8String];
    }
    
    interface = new CocoaUI([UIApplication sharedApplication].keyWindow, self, &metadata, &DSP);
    finterface = new FUI();
    
    // Read user preferences
    sampleRate = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"sampleRate"];
    bufferSize = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@"bufferSize"];
    openWidgetPanel = [[NSUserDefaults standardUserDefaults] boolForKey:@"openWidgetPanel"];
    
    [self openAudio];
    [self displayTitle];
    
    // Build Faust interface
    DSP.init(int(sampleRate));
	DSP.buildUserInterface(interface);
    DSP.buildUserInterface(finterface);
    
    char* argv[3];
    
    argv[0] = (char*)_name;
    argv[1] = "-xmit";
    argv[2] = "1";
    
    oscinterface = new OSCUI(_name, 3, argv);
    DSP.buildUserInterface(oscinterface);
    
    oscinterface->run();
    
    snprintf(rcfilename, 256, "%s/Library/Caches/%s", home, _name);
    finterface->recallState(rcfilename);
    
    [self updateGui];
    
    // Notification when device orientation changed
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationChanged:)
                                        name:UIDeviceOrientationDidChangeNotification object:nil];
    
    // Abstract layout is the layout computed without regarding screen dimensions. To be displayed, we adapt it to the device and orientation
    interface->saveAbstractLayout();
    
    // Used to refresh bargraphes
    _refreshTimer = [NSTimer scheduledTimerWithTimeInterval:kRefreshTimerInterval target:self selector:@selector(refreshObjects:) userInfo:nil repeats:YES];
    
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
    _motionManager = nil;
    _selectedWidget = nil;
    [self loadWidgetsPreferences];
    if (_assignatedWidgets.size() > 0) [self startMotion];

#ifdef JACK_IOS
    // Test Jack
    _swipeRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(openJackView)];
    _swipeRecognizer.direction = UISwipeGestureRecognizerDirectionUp;
    _swipeRecognizer.numberOfTouchesRequired = 3;
    [_dspScrollView addGestureRecognizer:_swipeRecognizer];
    
    _tapRecognizerToDismissJackView = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(closeJackView)];
    _tapRecognizerToDismissJackView.numberOfTapsRequired = 1;
    _tapRecognizerToDismissJackView.numberOfTouchesRequired = 1;
    [_dspScrollView addGestureRecognizer:_tapRecognizerToDismissJackView];
    
    _jackButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_jackButton setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Icon-Jack" ofType:@"png"]]
                 forState:UIControlStateNormal];
    [_jackButton addTarget:self action:@selector(openJackView) forControlEvents:UIControlEventTouchUpInside];

    _jackButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin & UIViewAutoresizingFlexibleTopMargin;
    [self.view addSubview:_jackButton];
    
    [self.view bringSubviewToFront:_widgetPreferencesView];
    
    _jackView = nil;
    _orientationIsChanging = NO;
#endif
}

#ifdef JACK_IOS

- (BOOL)checkJack
{
    jackaudio audio;
    
    if (audio.init("dummy", &DSP)) {
        audio.stop();
        return TRUE;
    } else {
        return FALSE;
    }
}

- (BOOL)openJack
{
    if (!audio_device) {
        
        NSString* iconFile;
        if (DSP.getNumInputs() > 0 && DSP.getNumOutputs() > 0) {
            iconFile = [[NSBundle mainBundle] pathForResource:@"Icon-Fx136" ofType:@"png"];
        } else if (DSP.getNumOutputs() > 0) {
            iconFile = [[NSBundle mainBundle] pathForResource:@"Icon-Output136" ofType:@"png"];
        } else {
            iconFile = [[NSBundle mainBundle] pathForResource:@"Icon-Analyzer136" ofType:@"png"];
        }
        NSFileHandle* fileHandle = [NSFileHandle fileHandleForReadingAtPath:iconFile];
        NSData* data = [fileHandle readDataToEndOfFile];
        const void* icon_data = [data bytes];
        const size_t size = [data length];
        NSLog(@"publishAppIcon rawDataSize = %ld", size);
        [fileHandle closeFile];
        
        audio_device = new jackaudio(icon_data, size, true);
        if (!audio_device->init((_name) ? _name : "Faust", &DSP)) {
            printf("Cannot connect to JACK server\n");
            goto error;
        }
        
        if (audio_device->start() < 0) {
            printf("Cannot start JACK client\n");
            goto error;
        }
    }
    
    audio_device->shutdown(jack_shutdown_callback, self);
    return TRUE;
    
error:
    
    UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Audio warning"
                                                        message:@"JACK server is not running !" delegate:self
                                              cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alertView show];
    [alertView release];
    
    [self closeAudio];
    return FALSE;
}

// Save widgets values
- (void)closeJack:(const char*)reason 
{
    NSString* errorString = [[NSString alloc] initWithCString:reason encoding:NSASCIIStringEncoding];
    
    if ([errorString compare:@"Client closed from JACK server!"] != NSOrderedSame)
    {
        UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Audio error"
                                                            message:errorString delegate:self
                                                            cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
        [alertView release];
    }

    [self closeAudio];
}

- (BOOL)isJackAudio
{
    return (dynamic_cast<jackaudio*>(audio_device) != NULL);
}

#endif

- (BOOL)openCoreAudio:(int)bufferSize :(int)sampleRate
{
    if (!audio_device) {
        audio_device = new iosaudio(sampleRate, bufferSize);
        
        if (!audio_device->init((_name) ? _name : "Faust", &DSP)) {
            printf("Cannot init iOS audio device\n");
            goto error;
        }
        
        if (audio_device->start() < 0) {
            printf("Cannot start iOS audio device\n");
            goto error;
        }
    }
    
    return TRUE;
    
error:
    
    UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Audio error"
                                                        message:@"CoreAudio device cannot be opened with the needed in/out parameters" delegate:self
                                              cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alertView show];
    [alertView release];
    
    [self closeAudio];
    return FALSE;
}

#ifdef JACK_IOS

- (void)openAudio
{
    // If CA audio running and JACK server running, will switch to JACK
    if (audio_device && dynamic_cast<iosaudio*>(audio_device) && [self checkJack]) {
        [self closeAudio];
    }
    
    if (![self openJack]) {
        [self openCoreAudio:bufferSize :sampleRate];
    }
}

#else

- (void)openAudio
{
    [self openCoreAudio:bufferSize :sampleRate];
}

#endif

- (void)closeAudio
{
    if (audio_device) {
        audio_device->stop();
        delete audio_device;
        audio_device = NULL;
    }
}

- (void)viewDidUnload
{
    [_curveSegmentedControl release];
    _curveSegmentedControl = nil;
    [_minText release];
    _minText = nil;
    [_maxText release];
    _maxText = nil;
    [_centerText release];
    _centerText = nil;
    [_minSlider release];
    _minSlider = nil;
    [_maxSlider release];
    _maxSlider = nil;
    [_centerSlider release];
    _centerSlider = nil;
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
    if (!interface) return;
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    if (!interface) return;
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
    
    [self closeAudio];
    
    delete interface;
    delete finterface;
    delete oscinterface;
    
    [_refreshTimer invalidate];
    [self stopMotion];

#ifdef JACK_IOS
    // Test Jack
    [_swipeRecognizer release];
#endif
    
    [_curveSegmentedControl release];
    [_minText release];
    [_maxText release];
    [_centerText release];
    [_minSlider release];
    [_maxSlider release];
    [_centerSlider release];
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

            // If push button, force to zero just after to avoid an "anti-rebond" bug
            /*if ((float)((FIButton*)sender).type == kPushButtonType && (float)((FIButton*)sender).value == 1.)
            {
                [self performSelector:@selector(buttonSetToZero:) withObject:sender afterDelay:0.1];
            }*/
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

// Save widgets values
- (void)saveGui
{
    if (finterface) {
        finterface->saveState(rcfilename);
    }
}

// Load widgets values
- (void)loadGui
{
    if (finterface) {
        finterface->recallState(rcfilename);
    }
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
        
        if (_openPanelChanged)
        {
            (*i)->enableLongPressGestureRecognizer(openWidgetPanel);
        }
    }
    
    if (_openPanelChanged) _openPanelChanged = !_openPanelChanged;
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
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone
        && deviceOrientation == UIDeviceOrientationPortraitUpsideDown)
    {
        return;
    }
    
#ifdef JACK_IOS
    _orientationIsChanging = YES;
#endif
    
    [self updateGui];
    
#ifdef JACK_IOS
    _orientationIsChanging = NO;
#endif
    
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
            
            // TO min/mid/max
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
            
            // TO min/mid/max
        }
    }

#ifdef JACK_IOS    
    // Test Jack
    if ([self isJackAudio])
    {
        [self performSelector:@selector(autoResizeJackViews) withObject:nil afterDelay:0.1];
    }
#endif
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
            [dynamic_cast<uiBargraph*>(*i)->fBargraph setNeedsDisplay];
        }
    }
    
    GUI::updateAllGuis();
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

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
#ifdef JACK_IOS
    [self closeJackView];
#endif
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
#ifdef JACK_IOS
    // Test Jack
    [self closeJackView];
#endif
    
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

- (void)setOpenWidgetPanel:(BOOL)openWidgetPanelOnLongTouch
{
    openWidgetPanel = openWidgetPanelOnLongTouch;
    _openPanelChanged = YES;
    [self updateGui];
}

#pragma mark - Audio

- (void)restartAudioWithBufferSize:(int)bufferSize sampleRate:(int)sampleRate
{
    finterface->saveState(rcfilename);
    
    if (dynamic_cast<iosaudio*>(audio_device)) {
        
        audio_device->stop();
        audio_device = NULL;
        
        [self openCoreAudio:bufferSize :sampleRate];
        
        DSP.init(long(sampleRate));
    }
   
    finterface->recallState(rcfilename);
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
    #if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
        id<NSFileManagerDelegate> tmp = [segue destinationViewController];
        [tmp setDelegate:self];
    #else
        [[segue destinationViewController] setDelegate:self];
    #endif
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
    // If running in CoreAudio mode...
    //if (dynamic_cast<iosaudio*>(audio_device))
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
    
    // SL : 04/09/14 was added for the SF concert ? deactivated for now
    
    /*
    // If widget is hidden we don't show the window
    if (_selectedWidget->getHideOnGUI()) return;
    */
    
    // Otherwise, set it selected (for selection display)
    _selectedWidget->setSelected(YES);
    
    // Parameter the windows
    [_gyroAxisSegmentedControl removeAllSegments];
    [_curveSegmentedControl removeAllSegments];
    
    if ([gesture.view isKindOfClass:[FIKnob class]]
        || [gesture.view isKindOfClass:[FISlider class]])
    {
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"0" atIndex:0 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"aX" atIndex:1 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"aY" atIndex:2 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"aZ" atIndex:3 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"gX" atIndex:4 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"gY" atIndex:5 animated:NO];
        [_gyroAxisSegmentedControl insertSegmentWithTitle:@"gZ" atIndex:6 animated:NO];
        
        // TODO
        
        if (SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"6.0")) {
            [_curveSegmentedControl insertSegmentWithImage:
             [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ic_accelnormon" ofType:@"png"]]
                                                   atIndex:0
                                                  animated:NO];
            
            [_curveSegmentedControl insertSegmentWithImage:
             [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ic_accelinverton" ofType:@"png"]]
                                                   atIndex:1
                                                  animated:NO];
            
            [_curveSegmentedControl insertSegmentWithImage:
             [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ic_accelcurveon" ofType:@"png"]]
                                                   atIndex:2
                                                  animated:NO];
            
            [_curveSegmentedControl insertSegmentWithImage:
             [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ic_accelinvertcurveon" ofType:@"png"]]
                                                   atIndex:3
                                                  animated:NO];
        } else {
            [_curveSegmentedControl insertSegmentWithTitle:@"Curve1" atIndex:0 animated:NO];
            [_curveSegmentedControl insertSegmentWithTitle:@"Curve2" atIndex:1 animated:NO];
            [_curveSegmentedControl insertSegmentWithTitle:@"Curve3" atIndex:2 animated:NO];
            [_curveSegmentedControl insertSegmentWithTitle:@"Curve4" atIndex:3 animated:NO];
        }
    
        _widgetPreferencesTitleLabel.text = _selectedWidget->getName();
    }
    
    else if ([gesture.view isKindOfClass:[FIButton class]])
    {
        // SL : 03/12/2015 : obsolete code
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
 
#ifdef JACK_IOS
    [self closeJackView];
#endif
}

// Display right values for parameters
- (void)updateWidgetPreferencesView
{
    // For knobs and sliders
    if (dynamic_cast<uiKnob*>(_selectedWidget) || dynamic_cast<uiSlider*>(_selectedWidget))
    {
        _curveSegmentedControl.selectedSegmentIndex = _selectedWidget->getAssignationCurve();
        _gyroAxisSegmentedControl.selectedSegmentIndex = _selectedWidget->getAssignationType();
    }
    
    // For buttons
    else if (dynamic_cast<uiButton*>(_selectedWidget))
    {
        // SL : 03/12/2015 : obsolete code
    }
    
    // Common parameters for all types
    _colorRSlider.value = _selectedWidget->getR();
    _colorRLabel.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getR()];
    _colorGSlider.value = _selectedWidget->getG();
    _colorGLabel.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getG()];
    _colorBSlider.value = _selectedWidget->getB();
    _colorBLabel.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getB()];
    
    _minSlider.value = _selectedWidget->getCurveMin();
    _minText.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getCurveMin()];
    _centerSlider.value = _selectedWidget->getCurveMid();
    _centerText.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getCurveMid()];
    _maxSlider.value = _selectedWidget->getCurveMax();
    _maxText.text = [NSString stringWithFormat:@"%1.1f", _selectedWidget->getCurveMax()];
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
   
    if (sender == _curveSegmentedControl) {
        _selectedWidget->setAssignationCurve(_curveSegmentedControl.selectedSegmentIndex);
        printf("_curveSegmentedControl\n");
    } else if (sender == _minSlider) {
        // Range limitation
        if (_minSlider.value >= _maxSlider.value) {
            _minSlider.value = _maxSlider.value;
        }
        _selectedWidget->setCurveMin(_minSlider.value);
        printf("_minSlider\n");
    } else if (sender == _maxSlider) {
        // Range limitation
        if (_maxSlider.value <= _minSlider.value) {
            _maxSlider.value = _minSlider.value;
        }
        _selectedWidget->setCurveMax(_maxSlider.value);
        printf("_maxSlider\n");
    } else if (sender == _centerSlider) {
        // Range limitation
        if (_centerSlider.value <= _minSlider.value) {
            _centerSlider.value = _minSlider.value;
        } else if (_centerSlider.value >= _maxSlider.value) {
            _centerSlider.value = _maxSlider.value;
        }
        _selectedWidget->setCurveMid(_centerSlider.value);
        printf("_centerSlider\n");
    
    // If user changed the sensor assignation, program resets ref point to default values
    } else if (sender == _gyroAxisSegmentedControl) {
        
        printf("_gyroAxisSegmentedControl\n");
        
        // Get title of selected tab for sensor assignation
        str = [NSString stringWithString:[_gyroAxisSegmentedControl titleForSegmentAtIndex:_gyroAxisSegmentedControl.selectedSegmentIndex]];

        // Set default values regarding assignation type
        if ([str compare:@"0"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationNone);
        }
        else if ([str compare:@"aX"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationAccelX);
         }
        else if ([str compare:@"aY"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationAccelY);
        }
        else if ([str compare:@"aZ"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationAccelZ);
        }
        else if ([str compare:@"gX"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationGyroX);
        }
        else if ([str compare:@"gY"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationGyroY);
        }
        else if ([str compare:@"gZ"] == NSOrderedSame)
        {
            _selectedWidget->setAssignationType(kAssignationGyroZ);
        }
        else
        {
            _selectedWidget->setAssignationType(kAssignationNone);
        }
    }
    
    // Write parameters in the widget object
    _selectedWidget->setColor(_colorRSlider.value, _colorGSlider.value, _colorBSlider.value);
    _colorRLabel.text = [NSString stringWithFormat:@"%1.1f", _colorRSlider.value];
    _colorGLabel.text = [NSString stringWithFormat:@"%1.1f", _colorGSlider.value];
    _colorBLabel.text = [NSString stringWithFormat:@"%1.1f", _colorBSlider.value];
    
    _selectedWidget->setCurve(_minSlider.value, _centerSlider.value, _maxSlider.value);
    _minText.text = [NSString stringWithFormat:@"%1.1f", _minSlider.value];
    _centerText.text = [NSString stringWithFormat:@"%1.1f", _centerSlider.value];
    _maxText.text = [NSString stringWithFormat:@"%1.1f", _maxSlider.value];
    
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
    
    // Update mappings
    int index = _selectedWidget->getItemCount();
    printf("getItemCount %d\n", index);
    
    if (_selectedWidget->getAssignationType() == kAssignationNone) {
        interface->setAccConverter(index, -1, 0, 0, 0, 0);  // -1 means no mapping
        interface->setGyrConverter(index, -1, 0, 0, 0, 0);  // -1 means no mapping
    } else if (_selectedWidget->getAssignationType() <= 3) {
        interface->setAccConverter(index,
                                   _selectedWidget->getAssignationType() - 1,
                                   _selectedWidget->getAssignationCurve(),
                                   _selectedWidget->getCurveMin(),
                                   _selectedWidget->getCurveMid(),
                                   _selectedWidget->getCurveMax());
    } else {
        interface->setGyrConverter(index,
                                   _selectedWidget->getAssignationType() - 4,
                                   _selectedWidget->getAssignationCurve(),
                                   _selectedWidget->getCurveMin(),
                                   _selectedWidget->getCurveMid(),
                                   _selectedWidget->getCurveMax());
        
    }
   
    // Save parameters in user defaults
    key = [NSString stringWithFormat:@"%@-assignation-type", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setInteger:_selectedWidget->getAssignationType() + 1000 forKey:key];
    
    key = [NSString stringWithFormat:@"%@-assignation-curve", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setInteger:_selectedWidget->getAssignationCurve() + 1000 forKey:key];
    
    key = [NSString stringWithFormat:@"%@-assignation-min", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getCurveMin() + 1000. forKey:key];
  
    key = [NSString stringWithFormat:@"%@-assignation-mid", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getCurveMid() + 1000. forKey:key];
  
    key = [NSString stringWithFormat:@"%@-assignation-max", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getCurveMax() + 1000. forKey:key];
    
    key = [NSString stringWithFormat:@"%@-r", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getR() + 1000. forKey:key];
    
    key = [NSString stringWithFormat:@"%@-g", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getG() + 1000. forKey:key];
    
    key = [NSString stringWithFormat:@"%@-b", [self urlForWidget:_selectedWidget]];
    [[NSUserDefaults standardUserDefaults] setFloat:_selectedWidget->getB() + 1000. forKey:key];
    
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    // If assignation type is not kAssignationNone, we start motion
    if (_assignatedWidgets.size() > 0) [self startMotion];
    else [self stopMotion];
}

// Reset widget parameters
- (IBAction)resetWidgetPreferences:(id)sender
{
    _selectedWidget->resetParameters();
    
    // Reset acc/gyr mapping
    int index =_selectedWidget->getItemCount();
    interface->setAccConverter(index, -1, 0, 0, 0, 0);  // -1 means no mapping
    interface->setGyrConverter(index, -1, 0, 0, 0, 0);  // -1 means no mapping
    
    [self updateWidgetPreferencesView];
    [self widgetPreferencesChanged:_gyroAxisSegmentedControl];
    [self widgetPreferencesChanged:_curveSegmentedControl];
}

- (void)resetAllWidgetsPreferences
{
    list<uiCocoaItem*>::iterator    i;
    
    for (i = _assignatedWidgets.begin(); i != _assignatedWidgets.end(); i++)
    {
        (*i)->resetParameters();
        
        // Reset acc/gyr mapping
        int index = (*i)->getItemCount();
        interface->setAccConverter(index, -1, 0, 0, 0, 0);  // -1 means no mapping
        interface->setGyrConverter(index, -1, 0, 0, 0, 0);  // -1 means no mapping
        
        _assignatedWidgets.erase(i);
    }
    
    [self loadWidgetsPreferences];
    
    for (i = interface->fWidgetList.begin(); i != interface->fWidgetList.end(); i++)
    {
        (*i)->resetInitialValue();
    }
}

// At application launch time, loading preferences for all widgets
- (void)loadWidgetsPreferences
{
    list<uiCocoaItem*>::iterator    i;
    NSString*                       key;
    NSString*                       key2;
    NSString*                       key3;
    int                             intValue = 0;
    float                           floatValue = 0.;
    
    for (i = interface->fWidgetList.begin(); i != interface->fWidgetList.end(); i++)
    {
        if (dynamic_cast<uiKnob*>(*i)
            || dynamic_cast<uiSlider*>(*i)
            || dynamic_cast<uiButton*>(*i))
        {
            
            // Get current values
            int index = (*i)->getItemCount();
            int type, curve;
            float min, mid, max;
            
            interface->getAccConverter(index, type, curve, min, mid, max);
            
            // Sensor assignation
            key = [NSString stringWithFormat:@"%@-assignation-type", [self urlForWidget:(*i)]];
            intValue = [[NSUserDefaults standardUserDefaults] integerForKey:key];
            if (intValue != 0) {
                (*i)->setAssignationType(intValue - 1000);
            } else {
                (*i)->setAssignationType(type + 1); // kAssignationAccelX starting from 1, type from 0
            }
            
            key = [NSString stringWithFormat:@"%@-assignation-curve", [self urlForWidget:(*i)]];
            intValue = [[NSUserDefaults standardUserDefaults] integerForKey:key];
            if (intValue != 0) {
                (*i)->setAssignationCurve(intValue - 1000);
            } else {
                (*i)->setAssignationCurve(curve);
            }
            
            key = [NSString stringWithFormat:@"%@-assignation-min", [self urlForWidget:(*i)]];
            floatValue = [[NSUserDefaults standardUserDefaults] floatForKey:key];
            if (floatValue != 0.f) {
                (*i)->setCurveMin(floatValue - 1000.);
            } else {
                (*i)->setCurveMin(min);
            }
            
            key = [NSString stringWithFormat:@"%@-assignation-mid", [self urlForWidget:(*i)]];
            floatValue = [[NSUserDefaults standardUserDefaults] floatForKey:key];
            if (floatValue != 0.f) {
                (*i)->setCurveMid(floatValue - 1000.);
            } else  {
                (*i)->setCurveMid(mid);
            }
            
            key = [NSString stringWithFormat:@"%@-assignation-max", [self urlForWidget:(*i)]];
            floatValue = [[NSUserDefaults standardUserDefaults] floatForKey:key];
            if (floatValue != 0.f) {
                (*i)->setCurveMax(floatValue - 1000.);
            } else {
                (*i)->setCurveMax(max);
            }
            
            // Color
            key = [NSString stringWithFormat:@"%@-r", [self urlForWidget:(*i)]];
            key2 = [NSString stringWithFormat:@"%@-g", [self urlForWidget:(*i)]];
            key3 = [NSString stringWithFormat:@"%@-b", [self urlForWidget:(*i)]];
            (*i)->setColor([[NSUserDefaults standardUserDefaults] floatForKey:key] - 1000.,
                           [[NSUserDefaults standardUserDefaults] floatForKey:key2] - 1000.,
                           [[NSUserDefaults standardUserDefaults] floatForKey:key3] - 1000.);
            
            // Default color
            if ((*i)->getR() == -1000
                && (*i)->getG() == -1000
                && (*i)->getB() == -1000)
            {
                (*i)->setColor((*i)->getInitR(), (*i)->getInitG(), (*i)->getInitB());
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
        //_sensorFilter = [[FISensorFilter alloc] initWithSampleRate:kMotionUpdateRate * 10 cutoffFrequency:100];
        [_motionManager startAccelerometerUpdates];
        [_motionManager startGyroUpdates];
        _motionTimer = [NSTimer scheduledTimerWithTimeInterval:1./kMotionUpdateRate
                                                        target:self 
                                                      selector:@selector(updateMotion)
                                                      userInfo:nil 
                                                       repeats:YES];
    }
}

// Stop updating sensors
- (void)stopMotion
{
    // Motion
    if (_motionManager != nil)
    {
        [_motionManager stopAccelerometerUpdates];
        [_motionManager stopGyroUpdates];
        [_motionManager release];
        _motionManager = nil;
        [_motionTimer invalidate];
    }
}

// The function periodically called to refresh motion sensors
- (void)updateMotion
{
    //printf("motionManager.accelerometerData.acceleration.x %f\n", _motionManager.accelerometerData.acceleration.x);
    
    interface->setAccValues(_motionManager.accelerometerData.acceleration.x,
                            _motionManager.accelerometerData.acceleration.y,
                            _motionManager.accelerometerData.acceleration.z);
    
    interface->setGyrValues(_motionManager.gyroData.rotationRate.x,
                            _motionManager.gyroData.rotationRate.y,
                            _motionManager.gyroData.rotationRate.z);
    
}

- (NSString*)urlForWidget:(uiCocoaItem*)widget
{
    list<uiCocoaItem*>::iterator    i = interface->fWidgetList.end();
    uiCocoaItem*                    currentWidget = widget;
    NSString*                       result = @"";
    
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

#ifdef JACK_IOS
// Test Jack
- (void)openJackView
{
    if (_jackView) return;
    
    // Construct view
    _jackView = [[JackView alloc] initWithFrame:CGRectMake(0,
                                                           _dspScrollView.frame.size.height,
                                                           _dspScrollView.frame.size.width,
                                                           kJackViewHeight)];
    _jackView.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    
    // Load client in view
    [_jackView loadJackClient:dynamic_cast<jackaudio*>(audio_device)->get_client()];
    
    // Insert view in super view
    [_dspScrollView.superview addSubview:_jackView];
    
    // Gesture recognizers
    [_swipeRecognizer removeTarget:self action:@selector(openJackView)];
    [_swipeRecognizer addTarget:self action:@selector(closeJackView)];
    _swipeRecognizer.direction = UISwipeGestureRecognizerDirectionDown;
    
    // Animation
    [UIView animateWithDuration:kJackViewAnimationDuration
                    delay:0.0
                    options:UIViewAnimationOptionCurveLinear
                    animations:^
     {
         [_jackView setFrame:CGRectMake(0,
                                        _dspScrollView.frame.size.height - kJackViewHeight + 44,
                                        _dspScrollView.frame.size.width,
                                        kJackViewHeight)];
     }
                     completion:^(BOOL finished)
     {
     }];
}

- (void)closeJackView
{
    if (!_jackView) return;
    
    // Gesture recognizers
    [_swipeRecognizer removeTarget:self action:@selector(closeJackView)];
    [_swipeRecognizer addTarget:self action:@selector(openJackView)];
    _swipeRecognizer.direction = UISwipeGestureRecognizerDirectionUp;
        
    // Animation
    [UIView animateWithDuration:kJackViewAnimationDuration
                          delay:0.0
                        options:UIViewAnimationOptionCurveLinear
                     animations:^
     {
         [_jackView setFrame:CGRectMake(0,
                                        _dspScrollView.frame.size.height + 44,
                                        _dspScrollView.frame.size.width,
                                        kJackViewHeight)];
     }
                     completion:^(BOOL finished)
     {
         [_jackView removeFromSuperview];
         [_jackView release];
         _jackView = nil;
     }];
}

- (void)autoResizeJackViews
{
    if (_jackView)
    {
        [_jackView setFrame:CGRectMake(0,
                                       _dspScrollView.frame.size.height - kJackViewHeight + 44,
                                       _dspScrollView.frame.size.width,
                                       kJackViewHeight)];
    }
    
    if (_jackButton)
    {
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
        {
            [_jackButton setFrame:CGRectMake(_dspScrollView.frame.size.width - 70 - 50,
                                             _dspScrollView.frame.size.height,
                                             70,
                                             32)];
        }
        else
        {
            [_jackButton setFrame:CGRectMake(_dspScrollView.frame.size.width - 70 - 10,
                                             _dspScrollView.frame.size.height,
                                             70,
                                             32)];
        }
    }
}

#endif
@end
