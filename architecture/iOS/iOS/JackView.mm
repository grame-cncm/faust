//
//  JackView.m
//  iOS
//
//  Created by Olivier Guillerminet on 02/04/13.
//
//

#import <QuartzCore/QuartzCore.h>
#import "JackView.h"

@implementation JackViewButton

@synthesize jackViewClient;
@synthesize jackView;
@synthesize audioMidi;
@synthesize inputOutput;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self)
    {
        self.jackViewClient = nil;
        self.jackView = nil;
        self.audioMidi = 0;
        self.inputOutput = 0;
        
        _singleTapRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(buttonClicked)];
        _singleTapRecognizer.numberOfTapsRequired = 1;
        [self addGestureRecognizer:_singleTapRecognizer];
        
        _doubleTapRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(buttonDoubleClicked)];
        _doubleTapRecognizer.numberOfTapsRequired = 2;
        [self addGestureRecognizer:_doubleTapRecognizer];
        
        [_singleTapRecognizer requireGestureRecognizerToFail:_doubleTapRecognizer];
        
        _longPressRecognizer = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(buttonLongPressed)];
        [self addGestureRecognizer:_longPressRecognizer];
        
        self.backgroundColor = [UIColor clearColor];
        self.frame = frame;
    }
    
    return self;
}

- (void)dealloc
{
    [jackView.portsView removeFromSuperview];
    [jackView.portsView release];
    jackView.portsView = nil;
    [jackView.superview setNeedsDisplay];
    
    [super dealloc];
}

- (void)buttonClicked
{
    if (jackView.portsView) [jackView dismissPortsView];
    else [self fastConnect];
}

- (void)buttonDoubleClicked
{    
    [self fastSwitch];
}

- (void)buttonLongPressed
{
    [self displayPortsView];
}

- (void)fastSwitch
{
    // Switch to Jack server
    if ([self.jackViewClient.name compare:@"system"] == NSOrderedSame
        || [self.jackViewClient.name compare:@"system_midi"] == NSOrderedSame)
    {
        jack_gui_switch_to_client([jackView jackClient], "jack");
    }
    
    // Switch to other client
    else
    {
        jack_gui_switch_to_client([jackView jackClient], [self.jackViewClient.name cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

- (void)fastConnect
{
    // Connect
    if (!self.isSelected)
    {
        if ([self.jackView quicklyConnectAppToClient:self.jackViewClient.name
                                         inputOutput:inputOutput
                                           audioMidi:audioMidi])
        {
            self.selected = YES;
        }
    }
    
    // Disconnect
    else
    {
        if ([self.jackView quicklyDisconnectAppToClient:self.jackViewClient.name
                                            inputOutput:inputOutput
                                              audioMidi:audioMidi])
        {
            self.selected = NO;
        }
    }
    
    [self setNeedsDisplay];
}

- (void)displayPortsView
{
    float x = 0.f;
    float y = 0.f;
    float w = 0.f;
    float h = 0.f;
    float utilH = 0.f;
    int i = 0;
    NSArray* compatiblePorts = [self.jackViewClient compatiblePortsWithInputOutput:self.inputOutput audioMidi:self.audioMidi];
    CGPoint pt = [self convertPoint:CGPointMake(0., 0.) toView:jackView.superview];
    CGPoint defPt;
    
    x = 0;
    w = jackView.frame.size.width;
    utilH = fmaxf([compatiblePorts count] * kPortsViewItemHeight,
                  [jackView numberOfCurrentAppPortsWithInputOutput:self.inputOutput audioMidi:self.audioMidi] * kPortsViewItemHeight);
    h = fminf(utilH, kPortsViewMaxHeight) + kPortsViewArrowHeight + kPortsViewFSButtonHeight;
    y = 0. - h;
    
    if (jackView.portsView)
    {
        [jackView.portsView removeFromSuperview];
        [jackView.portsView release];
        jackView.portsView = nil;
        [jackView.superview setNeedsDisplay];
        
        if (self == self.jackView.currentClientButton) return;
    }
    else if (self == self.jackView.currentClientButton) return;
    
    defPt = [self convertPoint:CGPointMake(x, y) toView:jackView.superview];
    
    jackView.portsView = [[JackViewPortsView alloc] initWithFrame:CGRectMake(x, defPt.y, w, h)];
    [jackView.portsView setUtilHeight:utilH];
    jackView.portsView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;
    jackView.portsView.clientButton = self;
    
    if (pt.x + kPortsViewItemWidth < jackView.frame.size.width) jackView.portsView.clientX = pt.x;
    else jackView.portsView.clientX = jackView.frame.size.width - kPortsViewItemWidth;
    
    jackView.portsView.currentAppX = [jackView convertPoint:jackView.currentClientButton.frame.origin toView:jackView.superview].x;
    
    for (i = 0; i < [compatiblePorts count]; ++i)
    {
        if ([[compatiblePorts objectAtIndex:i] isKindOfClass:[JackViewPort class]])
        {            
            JackViewPortsViewItem* item = [[JackViewPortsViewItem alloc] initWithFrame:CGRectMake(jackView.portsView.clientX,
                                                                                                  i * kPortsViewItemHeight,
                                                                                                  kPortsViewItemWidth,
                                                                                                  kPortsViewItemHeight)];
        
            item.longName = ((JackViewPort*)([compatiblePorts objectAtIndex:i])).name;
            item.selected = [jackView isPort:((JackViewPort*)([compatiblePorts objectAtIndex:i]))
         connectedToCurrentClientInputOutput:((JackViewPort*)([compatiblePorts objectAtIndex:i])).inputOutput
                                   audioMidi:((JackViewPort*)([compatiblePorts objectAtIndex:i])).audioMidi];
        
            [jackView.portsView addItem:item];
        }
    }
    
    if (self.inputOutput == 1) [jackView displayCurrentAppPortsWithInputOutput:2 audioMidi:self.audioMidi];
    else if (self.inputOutput == 2) [jackView displayCurrentAppPortsWithInputOutput:1 audioMidi:self.audioMidi];
    
    [jackView resizePortsView];
    
    jackView.portsView.fsButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [jackView.portsView.fsButton setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Icon-Expand" ofType:@"png"]]
                                 forState:UIControlStateNormal];
    [jackView.portsView.fsButton setFrame:CGRectMake(jackView.portsView.clientX,
                                                     jackView.portsView.frame.size.height - kPortsViewArrowHeight - kPortsViewFSButtonHeight,
                                                     kPortsViewFSButtonWidth,
                                                     kPortsViewFSButtonHeight)];
    [jackView.portsView.fsButton addTarget:jackView action:@selector(fsToClient) forControlEvents:UIControlEventTouchUpInside];
    
    [jackView.portsView addSubview:jackView.portsView.fsButton];
    
    [jackView.superview addSubview:jackView.portsView];
    [jackView.portsView refreshLinks];
    [jackView.portsView setNeedsDisplay];
    [jackView.portsView.backgroundView setNeedsDisplay];
    
    // Fade in
    CATransition *animation = [CATransition animation];
    [animation setDuration:0.3];
    [animation setType:kCATransitionFade];
    [animation setSubtype:kCATransitionFromLeft];
    [animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut]];
    
    [[self.window layer] addAnimation:animation forKey:@"DisplayPortsView"];
}


// Refresh view
- (void)drawRect:(CGRect)rect
{
    UIFont* font = [UIFont systemFontOfSize:11.0f];
    CGRect iconRect = CGRectMake(rect.origin.x + 1,
                                 rect.origin.y + 1,
                                 kJackViewButtonWidth - 2,
                                 kJackViewButtonWidth - 2);
    
    // Draw selection
    if (self.selected)
    {
        UIBezierPath* path = [UIBezierPath bezierPath];
        
        [[UIColor blueColor] set];
        
        [path moveToPoint:CGPointMake(rect.origin.x, rect.origin.y)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height)];
        [path addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height)];
        [path closePath];
        path.lineWidth = 2;
        [path fillWithBlendMode:kCGBlendModeNormal alpha:0.7];
    }
    
    // Translucent background
    self.backgroundColor = [UIColor clearColor];
    
    // Draw icon
    if (self.jackViewClient)
    {
        if (self.enabled) [self.jackViewClient.icon drawInRect:iconRect];
        else [self.jackViewClient.icon drawInRect:iconRect blendMode:kCGBlendModeNormal alpha:0.5];
    }
    
    // Draw text
    if (self.jackViewClient.name)
    {
        if (self.selected) [[UIColor whiteColor] set];
        else [[UIColor blackColor] set];
        CGSize stringBoundingBox = [self.jackViewClient.name sizeWithFont:font];
        [self.jackViewClient.name drawAtPoint:CGPointMake(rect.origin.x + (kJackViewButtonWidth - stringBoundingBox.width) / 2.,
                                                          rect.origin.y - 1. + kJackViewButtonWidth)
                                     withFont:font];
    }
}


@end


@implementation JackViewPort

@synthesize name;
@synthesize audioMidi;
@synthesize inputOutput;

- (id)init
{
    self = [super init];
    
    if (self)
    {
        self.name = nil;
        self.audioMidi = 0;
        self.inputOutput = 0;
    }
    
    return self;
}


- (void)dealloc
{
    [super dealloc];
}

@end


@implementation JackViewClient

@synthesize name;
@synthesize icon;
@synthesize ports;
@synthesize audioInputButton;
@synthesize audioOutputButton;
@synthesize midiInputButton;
@synthesize midiOutputButton;

- (id)init
{
    self = [super init];
    
    if (self)
    {
        self.name = nil;
        self.icon = nil;
        self.ports = [[NSMutableArray alloc] initWithCapacity:0];
        self.audioInputButton = nil;
        self.audioOutputButton = nil;
        self.midiInputButton = nil;
        self.midiOutputButton = nil;
    }
    
    return self;
}


- (void)dealloc
{
    [self.ports release];
    [super dealloc];
}

- (NSArray*)compatiblePortsWithInputOutput:(int)inputOutput audioMidi:(int)audioMidi
{
    JackViewPort* port = nil;
    int nbPorts = [self.ports count];
    int i = 0;
    NSMutableArray* portsArray = [NSMutableArray arrayWithCapacity:0];
        
    for (i = 0; i < nbPorts; ++i)
    {
        port = [self.ports objectAtIndex:i];

        if (((port.inputOutput == 1 && inputOutput == 2) || (port.inputOutput == 2 && inputOutput == 1))
            && port.audioMidi == audioMidi)
        {
            [portsArray addObject:port];
        }
    }
    
    return portsArray;
}

@end


@implementation JackView

@synthesize srcPt;
@synthesize dstPt;
@synthesize portsView;
@synthesize currentClientButton;
@synthesize audioButton;
@synthesize midiButton;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self)
    {
        self.portsView = nil;
        _jackClient = nil;
        self.currentClientButton = nil;
        self.backgroundColor = [UIColor clearColor];
        
        _singleTapRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(viewClicked)];
        _singleTapRecognizer.numberOfTapsRequired = 1;
        [self addGestureRecognizer:_singleTapRecognizer];
        
        float w = (frame.size.width - kJackViewButtonWidth - 2. * kJackViewIntHMargins - 2. * kJackViewExtHMargins) / 2.;
        
        self.audioButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.audioButton setFrame:CGRectMake((frame.size.width - kJackViewTabsWidth) / 2.,
                                              kJackViewTabsY,
                                              kJackViewTabsWidth / 2.,
                                              kJackViewTabsHeight)];
        [self.audioButton setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"jackview-audio-off" ofType:@"png"]]
                          forState:UIControlStateNormal];
        [self.audioButton setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"jackview-audio-on" ofType:@"png"]]
                          forState:UIControlStateSelected];
        [self.audioButton addTarget:self action:@selector(audioButtonClicked) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.audioButton];
        
        self.midiButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.midiButton setFrame:CGRectMake((frame.size.width - kJackViewTabsWidth) / 2. + kJackViewTabsWidth / 2.,
                                              kJackViewTabsY,
                                              kJackViewTabsWidth / 2.,
                                              kJackViewTabsHeight)];
        [self.midiButton setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"jackview-midi-off" ofType:@"png"]]
                         forState:UIControlStateNormal];
        [self.midiButton setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"jackview-midi-on" ofType:@"png"]]
                         forState:UIControlStateSelected];
        [self.midiButton addTarget:self action:@selector(midiButtonClicked) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.midiButton];
        
        self.audioButton.selected = YES;
        self.midiButton.selected = NO;
                
        _audioInputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(kJackViewExtHMargins,
                                                                                kJackViewExtTopVMargins,
                                                                                w,
                                                                                kJackViewButtonHeight + 2. * kJackViewIconMargins)];
        
        _audioOutputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(kJackViewExtHMargins + 2. * kJackViewIntHMargins + kJackViewButtonWidth + w,
                                                                                 kJackViewExtTopVMargins,
                                                                                 w,
                                                                                 kJackViewButtonHeight + 2. * kJackViewIconMargins)];
        
        _midiInputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(kJackViewExtHMargins,
                                                                               kJackViewExtTopVMargins,
                                                                               w,
                                                                               kJackViewButtonHeight + 2. * kJackViewIconMargins)];
        
        _midiOutputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(kJackViewExtHMargins + 2. * kJackViewIntHMargins + kJackViewButtonWidth + w,
                                                                                kJackViewExtTopVMargins,
                                                                                w,
                                                                                kJackViewButtonHeight + 2. * kJackViewIconMargins)];
        
        UIColor* color = [UIColor clearColor];
        _audioInputsScrollView.backgroundColor = color;
        _audioOutputsScrollView.backgroundColor = color;
        _midiInputsScrollView.backgroundColor = color;
        _midiOutputsScrollView.backgroundColor = color;
        
        _audioInputsScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        _audioOutputsScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        _midiInputsScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        _midiOutputsScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        
        _audioInputsScrollView.hidden = NO;
        _audioOutputsScrollView.hidden = NO;
        _midiInputsScrollView.hidden = YES;
        _midiOutputsScrollView.hidden = YES;
        
        _audioInputsScrollView.delegate = self;
        _audioOutputsScrollView.delegate = self;
        _midiInputsScrollView.delegate = self;
        _midiOutputsScrollView.delegate = self;
        
        [self addSubview:_audioInputsScrollView];
        [self addSubview:_audioOutputsScrollView];
        [self addSubview:_midiInputsScrollView];
        [self addSubview:_midiOutputsScrollView];
        
        _clients = [[NSMutableArray alloc] initWithCapacity:0];
        
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationChanged:)
                                                     name:UIDeviceOrientationDidChangeNotification object:nil];
        
        [self setNeedsDisplay];
    }
    
    return self;
}

- (void)orientationChanged:(NSNotification *)notification
{
    [self resizeView];
}

- (void)audioButtonClicked
{
    if (!self.audioButton.selected)
    {
        self.audioButton.selected = YES;
        self.midiButton.selected = NO;
        
        _audioInputsScrollView.hidden = NO;
        _audioOutputsScrollView.hidden = NO;
        _midiInputsScrollView.hidden = YES;
        _midiOutputsScrollView.hidden = YES;
    }
    
    [self showHideScrollViews];
    [self setNeedsDisplay];
}

- (void)midiButtonClicked
{
    if (!self.midiButton.selected)
    {
        self.midiButton.selected = YES;
        self.audioButton.selected = NO;
        
        _audioInputsScrollView.hidden = YES;
        _audioOutputsScrollView.hidden = YES;
        _midiInputsScrollView.hidden = NO;
        _midiOutputsScrollView.hidden = NO;
    }
    
    [self showHideScrollViews];
    [self setNeedsDisplay];
}

- (void)resizeView
{
    CGRect frame = self.frame;
    float w = (frame.size.width - kJackViewButtonWidth - 2. * kJackViewIntHMargins - 2. * kJackViewExtHMargins) / 2.;
    
    [_audioInputsScrollView setFrame:CGRectMake(kJackViewExtHMargins,
                                                kJackViewExtTopVMargins,
                                                w,
                                                kJackViewButtonHeight + 2. * kJackViewIconMargins)];
    
    [_audioOutputsScrollView setFrame:CGRectMake(kJackViewExtHMargins + 2. * kJackViewIntHMargins + kJackViewButtonWidth + w,
                                                 kJackViewExtTopVMargins,
                                                 w,
                                                 kJackViewButtonHeight + 2. * kJackViewIconMargins)];
    
    [_midiInputsScrollView setFrame:CGRectMake(kJackViewExtHMargins,
                                               kJackViewExtTopVMargins,
                                               w,
                                               kJackViewButtonHeight + 2. * kJackViewIconMargins)];
    
    [_midiOutputsScrollView setFrame:CGRectMake(kJackViewExtHMargins + 2. * kJackViewIntHMargins + kJackViewButtonWidth + w,
                                                kJackViewExtTopVMargins,
                                                w,
                                                kJackViewButtonHeight + 2. * kJackViewIconMargins)];
    
    [self.audioButton setFrame:CGRectMake((frame.size.width - kJackViewTabsWidth) / 2.,
                                          kJackViewTabsY,
                                          kJackViewTabsWidth / 2.,
                                          kJackViewTabsHeight)];
    
    [self.midiButton setFrame:CGRectMake((frame.size.width - kJackViewTabsWidth) / 2. + kJackViewTabsWidth / 2.,
                                         kJackViewTabsY,
                                         kJackViewTabsWidth / 2.,
                                         kJackViewTabsHeight)];
    
    if (self.currentClientButton)
    {
        [self.currentClientButton setFrame:CGRectMake(self.frame.size.width / 2. - kJackViewButtonWidth / 2.,
                                                      kJackViewExtTopVMargins + kJackViewIconMargins,
                                                      kJackViewButtonWidth,
                                                      self.frame.size.height - 2. * kJackViewExtBottomVMargins - 2. * kJackViewIconMargins)];
    }
    
    if (self.portsView)
    {
        JackViewButton* clientButton = self.portsView.clientButton;
        [clientButton performSelector:@selector(displayPortsView) withObject:nil afterDelay:0.1];
    }
    
    [self makeButtonsSymetric];
    [self setNeedsDisplay];
}

- (void)resizePortsView
{
    int i = 0;
    CGPoint pt = [self.portsView.clientButton convertPoint:CGPointMake(0., 0.) toView:self.superview];
    float oldClientX = self.portsView.clientX;
    float oldCurrentAppX = self.portsView.currentAppX;
    JackViewPortsViewItem* item = nil;
    
    [self.portsView setFrame:CGRectMake(self.portsView.frame.origin.x,
                                        self.portsView.frame.origin.y,
                                        self.frame.size.width,
                                        self.portsView.frame.size.height)];
    
    if (pt.x + kPortsViewItemWidth < self.frame.size.width) self.portsView.clientX = pt.x;
    else self.portsView.clientX = self.frame.size.width - kPortsViewItemWidth;
    
    self.portsView.currentAppX = [self convertPoint:self.currentClientButton.frame.origin toView:self.superview].x;
    
    for (i = 0; i < [[self.portsView portsItems] count]; ++i)
    {
        if ([[[self.portsView portsItems] objectAtIndex:i] isKindOfClass:[JackViewPortsViewItem class]])
        {
            JackViewPortsViewItem* item = ((JackViewPortsViewItem*)[[self.portsView portsItems] objectAtIndex:i]);
            if (item.frame.origin.x == oldClientX)
            {
                [item setFrame:CGRectMake(self.portsView.clientX,
                                          item.frame.origin.y,
                                          kPortsViewItemWidth,
                                          kPortsViewItemHeight)];
            }
            else if (item.frame.origin.x == oldCurrentAppX)
            {
                [item setFrame:CGRectMake(self.portsView.currentAppX,
                                          item.frame.origin.y,
                                          kPortsViewItemWidth,
                                          kPortsViewItemHeight)];
            }
        }
    }
    
    if (fabs(self.portsView.clientX - self.portsView.currentAppX) <= kPortsViewMinXBetweenItems + kPortsViewItemWidth)
    {
        float newClientX = 0.f;
        float newCurrentAppX = 0.f;
        
        if (self.portsView.currentAppX < self.portsView.clientX)
        {
            // Re-position current app X
            newCurrentAppX = fmaxf(self.portsView.clientX - kPortsViewMinXBetweenItems - kPortsViewItemWidth, 0.);
                        
            for (i = 0; i < [[self.portsView portsItems] count]; ++i)
            {
                item = [[self.portsView portsItems] objectAtIndex:i];
                
                if ([item isKindOfClass:[JackViewPortsViewItem class]])
                {                    
                    if (item.frame.origin.x == self.portsView.currentAppX)
                    {
                        [item setFrame:CGRectMake(newCurrentAppX, item.frame.origin.y, item.frame.size.width, item.frame.size.height)];
                    }
                }
            }
            
            self.portsView.currentAppX = newCurrentAppX;
            
            // If still not enough, re-position client x
            if (fabs(self.portsView.clientX - self.portsView.currentAppX) <= kPortsViewMinXBetweenItems + kPortsViewItemWidth)
            {
                newClientX = fminf(self.portsView.currentAppX + kPortsViewItemWidth + kPortsViewMinXBetweenItems, self.frame.size.width - kPortsViewItemWidth);
                
                for (i = 0; i < [[self.portsView portsItems] count]; ++i)
                {
                    item = [[self.portsView portsItems] objectAtIndex:i];
                    
                    if ([item isKindOfClass:[JackViewPortsViewItem class]])
                    {
                        if (item.frame.origin.x == self.portsView.clientX)
                        {
                            [item setFrame:CGRectMake(newClientX, item.frame.origin.y, item.frame.size.width, item.frame.size.height)];
                        }
                    }
                }
                
                self.portsView.clientX = newClientX;
            }
        }
        
        else if (self.portsView.clientX < self.portsView.currentAppX)
        {
            // Re-position current app X
            newCurrentAppX = fminf(self.portsView.clientX + kPortsViewMinXBetweenItems + kPortsViewItemWidth, self.frame.size.width - kPortsViewItemWidth);
                        
            for (i = 0; i < [[self.portsView portsItems] count]; ++i)
            {
                item = [[self.portsView portsItems] objectAtIndex:i];
                
                if ([item isKindOfClass:[JackViewPortsViewItem class]])
                {
                    if (item.frame.origin.x == self.portsView.currentAppX)
                    {
                        [item setFrame:CGRectMake(newCurrentAppX, item.frame.origin.y, item.frame.size.width, item.frame.size.height)];
                    }
                }
            }
            
            self.portsView.currentAppX = newCurrentAppX;
            
            // If still not enough, re-position client x
            if (fabs(self.portsView.clientX - self.portsView.currentAppX) <= kPortsViewMinXBetweenItems + kPortsViewItemWidth)
            {
                newClientX = fmaxf(self.portsView.currentAppX - kPortsViewMinXBetweenItems - kPortsViewItemWidth, 0.);
                
                for (i = 0; i < [[self.portsView portsItems] count]; ++i)
                {
                    item = [[self.portsView portsItems] objectAtIndex:i];
                    
                    if ([item isKindOfClass:[JackViewPortsViewItem class]])
                    {
                        if (item.frame.origin.x == self.portsView.clientX)
                        {
                            [item setFrame:CGRectMake(newClientX, item.frame.origin.y, item.frame.size.width, item.frame.size.height)];
                        }
                    }
                }
                
                self.portsView.clientX = newClientX;
            }
        }
    }
    
    if (self.portsView.fsButton)
    {
        [self.portsView.fsButton setFrame:CGRectMake(self.portsView.clientX,
                                                     self.portsView.fsButton.frame.origin.y,
                                                     self.portsView.fsButton.frame.size.width,
                                                     self.portsView.fsButton.frame.size.height)];
    }
}

- (void)dealloc
{
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [_clients release];
    [_audioInputsScrollView release];
    [_audioOutputsScrollView release];
    [_midiInputsScrollView release];
    [_midiOutputsScrollView release];
    
    [self dismissPortsView];
    
    [super dealloc];
}

- (void)loadJackClient:(jack_client_t*)jackClient
{
	jack_status_t status;
	const char **ports;
	int show_aliases = 0;
	char* aliases[2];
	jack_port_t *port;
    int i;
    
    _jackClient = jackClient;
    
    
    if (show_aliases)
    {
        aliases[0] = (char *) malloc (jack_port_name_size());
        aliases[1] = (char *) malloc (jack_port_name_size());
    }
    
    if (_jackClient == NULL)
    {
		if (status & JackServerFailed)
        {
			fprintf (stderr, "JACK server not running\n");
		}
        else
        {
			fprintf (stderr, "jack_client_open() failed, "
                     "status = 0x%2.0x\n", status);
		}
		return;
	}
    
    ports = jack_get_ports (_jackClient, NULL, NULL, 0);
    
    if (!ports)
    {
        NSLog(@"ERROR");
        return;
    }
    
    for (i = 0; ports && ports[i]; ++i)
    {
		port = jack_port_by_name (_jackClient, ports[i]);
        
        int res = 0;
        NSString* clientName = nil;
        size_t size = 0;
        void* rawData = NULL;
        NSData* data = nil;
        JackViewClient* jackViewClient = nil;
        int audioMidi = 0; // 0: undefined, 1: audio; 2: midi
        int inputOutput = 0; // 0: undefined, 1: input, 2: output
        NSString* portType = nil;
        
        _currentClientName = [[NSString alloc] initWithCString:jack_get_client_name(_jackClient) encoding:NSUTF8StringEncoding];
        
        clientName = [NSString stringWithCString:ports[i] encoding:NSUTF8StringEncoding];
        clientName = [[clientName componentsSeparatedByString:@":"] objectAtIndex:0];
        
        // Check if client doesn't exist already
        if (![self doesClientExist:clientName])
        {            
            // If needed, create it
            jackViewClient = [[JackViewClient alloc] init];
            
            // Set its name
            jackViewClient.name = [[NSString alloc] initWithString:clientName];
            
            // Set its icon
            if ([clientName compare:@"system"] == NSOrderedSame
                || [clientName compare:@"system_midi"] == NSOrderedSame)
            {
                res = jack_custom_get_data(_jackClient, "jack", "icon.png", &rawData, &size);
            }
            else
            {
                res = jack_custom_get_data(_jackClient, [clientName cStringUsingEncoding:NSUTF8StringEncoding], "icon.png", &rawData, &size);
            }
            
            if (res == 0)
            {
                data = [NSData dataWithBytes:rawData length:size];
                jackViewClient.icon = [[UIImage alloc] initWithData:data];
                
            }
            else
            {
                jackViewClient.icon = [[UIImage alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Icon_Apple" ofType:@"png"]];
            }
        }
        else
        {
            jackViewClient = [self clientWithName:clientName];
        }
        
        // Input / output ?
        int flags = jack_port_flags (port);

        if (flags & JackPortIsInput) inputOutput = 1;
        else if (flags & JackPortIsOutput) inputOutput = 2;
        
        // Audio / midi ?
        portType = [NSString stringWithCString:jack_port_type(port) encoding:NSUTF8StringEncoding];
        
        if ([((NSString*)([[portType componentsSeparatedByString:@" "] lastObject])) compare:@"audio"] == NSOrderedSame) audioMidi = 1;
        else if ([((NSString*)([[portType componentsSeparatedByString:@" "] lastObject])) compare:@"midi"] == NSOrderedSame) audioMidi = 2;
        
        // Add port
        JackViewPort* jackViewPort = [[JackViewPort alloc] init];
        jackViewPort.name = [[NSString alloc] initWithCString:ports[i] encoding:NSUTF8StringEncoding];
        jackViewPort.inputOutput = inputOutput;
        jackViewPort.audioMidi = audioMidi;
        
        // Put the corresponding button in the right scroll view
        if (inputOutput == 2 && audioMidi == 1 && jackViewClient.audioInputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake([[_audioInputsScrollView subviews] count] * (kJackViewButtonWidth + kJackViewIconMargins) + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewButtonWidth,
                                                                                kJackViewButtonHeight)];
            jackViewClient.audioInputButton = button;
            button.jackViewClient = jackViewClient;
            button.jackView = self;
            button.audioMidi = 1;
            button.inputOutput = 1;
            [_audioInputsScrollView addSubview:jackViewClient.audioInputButton];
        }
        else if (inputOutput == 1 && audioMidi == 1 && jackViewClient.audioOutputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake([[_audioOutputsScrollView subviews] count] * (kJackViewButtonWidth + kJackViewIconMargins) + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewButtonWidth,
                                                                                kJackViewButtonHeight)];
            jackViewClient.audioOutputButton = button;
            button.jackViewClient = jackViewClient;
            button.jackView = self;
            button.audioMidi = 1;
            button.inputOutput = 2;
            [_audioOutputsScrollView addSubview:jackViewClient.audioOutputButton];
        }
        else if (inputOutput == 2 && audioMidi == 2 && jackViewClient.midiInputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake([[_midiInputsScrollView subviews] count] * (kJackViewButtonWidth + kJackViewIconMargins) + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewButtonWidth,
                                                                                kJackViewButtonHeight)];
            jackViewClient.midiInputButton = button;
            button.jackViewClient = jackViewClient;
            button.jackView = self;
            button.audioMidi = 2;
            button.inputOutput = 1;
            [_midiInputsScrollView addSubview:jackViewClient.midiInputButton];
        }
        else if (inputOutput == 1 && audioMidi == 2 && jackViewClient.midiOutputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake([[_midiOutputsScrollView subviews] count] * (kJackViewButtonWidth + kJackViewIconMargins) + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewButtonWidth,
                                                                                kJackViewButtonHeight)];
            jackViewClient.midiOutputButton = button;
            button.jackViewClient = jackViewClient;
            button.jackView = self;
            button.audioMidi = 2;
            button.inputOutput = 2;
            [_midiOutputsScrollView addSubview:jackViewClient.midiOutputButton];
        }
        
        [jackViewClient.ports addObject:jackViewPort];
        
        // Add client
        if (![self doesClientExist:clientName])
        {
            [_clients addObject:jackViewClient];
        }
	}
    
    [_audioInputsScrollView setContentSize:CGSizeMake([[_audioInputsScrollView subviews] count] * (kJackViewButtonWidth + kJackViewIconMargins),
                                                      _audioInputsScrollView.frame.size.height)];
    [_audioOutputsScrollView setContentSize:CGSizeMake([[_audioOutputsScrollView subviews] count] * (kJackViewButtonWidth + kJackViewIconMargins),
                                                       _audioOutputsScrollView.frame.size.height)];
    [_midiInputsScrollView setContentSize:CGSizeMake([[_midiInputsScrollView subviews] count] * (kJackViewButtonWidth + kJackViewIconMargins),
                                                     _midiInputsScrollView.frame.size.height)];
    [_midiOutputsScrollView setContentSize:CGSizeMake([[_midiOutputsScrollView subviews] count] * (kJackViewButtonWidth + kJackViewIconMargins),
                                                      _midiOutputsScrollView.frame.size.height)];
    
    [self makeButtonsSymetric];
    
    // Add current app icon
    JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake(self.frame.size.width / 2. - kJackViewButtonWidth / 2.,
                                                                              kJackViewExtTopVMargins + kJackViewIconMargins,
                                                                              kJackViewButtonWidth,
                                                                              self.frame.size.height - 2. * kJackViewExtBottomVMargins - 2. * kJackViewIconMargins)];
    button.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
    button.jackViewClient = [self clientWithName:_currentClientName];
    button.jackView = self;
    self.currentClientButton = button;
    [self addSubview:button];
    
    // Deactivate uncomaptible buttons and select connected buttons
    NSArray* buttons = nil;
    BOOL compatible = NO;
    BOOL selected = NO;
    
    buttons = [_audioInputsScrollView subviews];
    compatible = [self hasCurrentClientCompatiblePortWithInputOutput:1 audioMidi:1];

    for (i = 0; i < [buttons count]; ++i)
    {
        ((JackViewButton*)([buttons objectAtIndex:i])).enabled = compatible;
        
        selected = [self isClient:((JackViewButton*)([buttons objectAtIndex:i])).jackViewClient connectedToCurrentClientInputOutput:1 audioMidi:1];
        ((JackViewButton*)([buttons objectAtIndex:i])).selected = selected;
    }
    
    buttons = [_audioOutputsScrollView subviews];
    compatible = [self hasCurrentClientCompatiblePortWithInputOutput:2 audioMidi:1];
    for (i = 0; i < [buttons count]; ++i)
    {
        ((JackViewButton*)([buttons objectAtIndex:i])).enabled = compatible;
        
        selected = [self isClient:((JackViewButton*)([buttons objectAtIndex:i])).jackViewClient connectedToCurrentClientInputOutput:2 audioMidi:1];
        ((JackViewButton*)([buttons objectAtIndex:i])).selected = selected;
    }
    
    buttons = [_midiInputsScrollView subviews];
    compatible = [self hasCurrentClientCompatiblePortWithInputOutput:1 audioMidi:2];
    for (i = 0; i < [buttons count]; ++i)
    {
        ((JackViewButton*)([buttons objectAtIndex:i])).enabled = compatible;
        
        selected = [self isClient:((JackViewButton*)([buttons objectAtIndex:i])).jackViewClient connectedToCurrentClientInputOutput:1 audioMidi:2];
        ((JackViewButton*)([buttons objectAtIndex:i])).selected = selected;
    }
    
    buttons = [_midiOutputsScrollView subviews];
    compatible = [self hasCurrentClientCompatiblePortWithInputOutput:2 audioMidi:2];
    for (i = 0; i < [buttons count]; ++i)
    {
        ((JackViewButton*)([buttons objectAtIndex:i])).enabled = compatible;
        
        selected = [self isClient:((JackViewButton*)([buttons objectAtIndex:i])).jackViewClient connectedToCurrentClientInputOutput:2 audioMidi:2];
        ((JackViewButton*)([buttons objectAtIndex:i])).selected = selected;
    }
    
    [self showHideScrollViews];
    
    // Free memory
    jack_free(ports);
    free(aliases[0]);
    free(aliases[1]);
}

- (jack_client_t*)jackClient
{
    return _jackClient;
}

- (BOOL)doesClientExist:(NSString*)clientName
{
    int i = 0;
    int nbClients = [_clients count];
    
    for (i = 0; i < nbClients; ++i)
    {
        if ([((JackViewClient*)[_clients objectAtIndex:i]).name compare:clientName] == NSOrderedSame)
        {
            return YES;
        }
    }
    
    return NO;
}


- (JackViewClient*)clientWithName:(NSString*)clientName
{
    int i = 0;
    int nbClients = [_clients count];
    
    for (i = 0; i < nbClients; ++i)
    {
        if ([((JackViewClient*)[_clients objectAtIndex:i]).name compare:clientName] == NSOrderedSame)
        {
            return ((JackViewClient*)[_clients objectAtIndex:i]);
        }
    }
    
    return nil;
}

- (JackViewPort*)portWithName:(NSString*)portName
{
    int i = 0;
    NSString* clientName = [[portName componentsSeparatedByString:@":"] objectAtIndex:0];
    JackViewClient* client = [self clientWithName:clientName];
    int nbPorts = [client.ports count];
    JackViewPort* port = nil;
    
    for (i = 0; i < nbPorts; ++i)
    {
        port = (JackViewPort*)[client.ports objectAtIndex:i];
        if ([port.name compare:portName] == NSOrderedSame)
        {
            return port;
        }
    }

    return nil;
}

- (void)makeButtonsSymetric
{
    int i = 0;
    float offset = 0.;
    
    // Re-organize audio output scroll view icons
    if (_audioOutputsScrollView.contentSize.width < _audioOutputsScrollView.frame.size.width)
    {
        offset = _audioOutputsScrollView.frame.size.width - _audioOutputsScrollView.contentSize.width;
        
        for (i = 0; i < [[_audioOutputsScrollView subviews] count]; ++i)
        {
            JackViewButton* button = ((JackViewButton*)[[_audioOutputsScrollView subviews] objectAtIndex:i]);
            [button setFrame:CGRectMake(i * kJackViewButtonWidth + offset,
                                        button.frame.origin.y,
                                        button.frame.size.width,
                                        button.frame.size.height)];
        }
    }
    
    // Re-organize midi output scroll view icons
    if (_midiOutputsScrollView.contentSize.width < _midiOutputsScrollView.frame.size.width)
    {
        offset = _midiOutputsScrollView.frame.size.width - _midiOutputsScrollView.contentSize.width;
        
        for (i = 0; i < [[_midiOutputsScrollView subviews] count]; ++i)
        {
            JackViewButton* button = ((JackViewButton*)[[_midiOutputsScrollView subviews] objectAtIndex:i]);
            [button setFrame:CGRectMake(i * kJackViewButtonWidth + offset,
                                        button.frame.origin.y,
                                        button.frame.size.width,
                                        button.frame.size.height)];
        }
    }
}

- (BOOL)hasCurrentClientCompatiblePortWithInputOutput:(int)inputOutput audioMidi:(int)audioMidi
{
    JackViewClient* currentClient = [self clientWithName:_currentClientName];
    JackViewPort* port = nil;
    int nbPorts = [currentClient.ports count];
    int i = 0;
    
    for (i = 0; i < nbPorts; ++i)
    {
        port = [currentClient.ports objectAtIndex:i];
        
        if (port.inputOutput == inputOutput
            && port.audioMidi == audioMidi)
        {
            return YES;
        }
    }
    
    return NO;
}

- (BOOL)isClient:(JackViewClient*)client connectedToCurrentClientInputOutput:(int)inputOutput audioMidi:(int)audioMidi
{
    JackViewClient* jackViewAppClient = [self clientWithName:_currentClientName];
    int nbAppClientPorts = [jackViewAppClient.ports count];
    int i = 0;
    int j = 0;
    JackViewPort* port = nil;
    const char **connections;
    NSString* connection = nil;
    NSString* connectedClient = nil;
        
    // Find app client ports connected to client
    for (i = 0; i < nbAppClientPorts; ++i)
    {
        port = [jackViewAppClient.ports objectAtIndex:i];
                
        if (port.audioMidi == audioMidi
            && port.inputOutput == inputOutput)
        {
            if ((connections = jack_port_get_all_connections(_jackClient,
                                                             jack_port_by_name(_jackClient,
                                                                               [port.name cStringUsingEncoding:NSUTF8StringEncoding]))) != 0)
            {
				for (j = 0; connections[j]; j++)
                {
                    connection = [NSString stringWithCString:connections[j] encoding:NSUTF8StringEncoding];
                    connectedClient = [[connection componentsSeparatedByString:@":"] objectAtIndex:0];
                                        
                    if ([connectedClient compare:client.name] == NSOrderedSame)
                    {
                        jack_free (connections);
                        return YES;
                    }
				}
				jack_free (connections);
			}
        }
    }
    
    return NO;
}

- (BOOL)isPort:(JackViewPort*)port connectedToCurrentClientInputOutput:(int)inputOutput audioMidi:(int)audioMidi
{
    const char **connections;
    NSString* connection = nil;
    NSString* connectedClient = nil;
    int i = 0;
        
    if ((connections = jack_port_get_all_connections(_jackClient,
                                                     jack_port_by_name(_jackClient,
                                                                       [port.name cStringUsingEncoding:NSUTF8StringEncoding]))) != 0)
    {
        for (i = 0; connections[i]; i++)
        {
            connection = [NSString stringWithCString:connections[i] encoding:NSUTF8StringEncoding];
            connectedClient = [[connection componentsSeparatedByString:@":"] objectAtIndex:0];
                        
            if ([connectedClient compare:_currentClientName] == NSOrderedSame)
            {
                jack_free (connections);
                return YES;
            }
        }
        jack_free (connections);
    }
    
    return NO;
}

- (BOOL)isPort:(NSString*)portName1
connectedWithPort:(NSString*)portName2
{
    const char **connections;
    NSString* connection = nil;
    int i = 0;
    
    if ((connections = jack_port_get_all_connections(_jackClient,
                                                     jack_port_by_name(_jackClient,
                                                                       [portName1 cStringUsingEncoding:NSUTF8StringEncoding]))) != 0)
    {
        for (i = 0; connections[i]; i++)
        {
            connection = [NSString stringWithCString:connections[i] encoding:NSUTF8StringEncoding];
            
            if ([connection compare:portName2] == NSOrderedSame)
            {
                jack_free (connections);
                return YES;
            }
        }
        jack_free (connections);
    }
    
    return NO;
}

- (NSArray*)getCurrentClientPortConnectedTo:(NSString*)portName
{
    const char **connections;
    NSString* connection = nil;
    NSString* connectedClient = nil;
    int i = 0;
    NSMutableArray* array = [NSMutableArray arrayWithCapacity:0];
    
    if ((connections = jack_port_get_all_connections(_jackClient,
                                                     jack_port_by_name(_jackClient,
                                                                       [portName cStringUsingEncoding:NSUTF8StringEncoding]))) != 0)
    {
        for (i = 0; connections[i]; i++)
        {
            connection = [NSString stringWithCString:connections[i] encoding:NSUTF8StringEncoding];
            connectedClient = [[connection componentsSeparatedByString:@":"] objectAtIndex:0];
            
            if ([connectedClient compare:_currentClientName] == NSOrderedSame)
            {
                [array addObject:connection];
            }
        }
        jack_free (connections);
    }
    
    return array;
}

// Returns YES if software was able to connect, NO otherwise
- (BOOL)quicklyConnectAppToClient:(NSString*)clientName
                      inputOutput:(int)inputOutput
                        audioMidi:(int)audioMidi
{
    JackViewClient* jackViewAppClient = [self clientWithName:_currentClientName];
    int nbAppClientPorts = [jackViewAppClient.ports count];
    
    JackViewClient* jackViewClient = [self clientWithName:clientName];
    int nbClientPorts = [jackViewClient.ports count];
    
    int i = 0;
    JackViewPort* port = nil;
    
    NSMutableArray* jackViewAppClientAvailablePorts = [NSMutableArray arrayWithCapacity:0];
    NSMutableArray* jackViewClientAvailablePorts = [NSMutableArray arrayWithCapacity:0];
    
    // Find connectable ports for app client
    for (i = 0; i < nbAppClientPorts; ++i)
    {
        port = [jackViewAppClient.ports objectAtIndex:i];
        
        if (port.audioMidi == audioMidi
            && port.inputOutput == inputOutput)
        {
            [jackViewAppClientAvailablePorts addObject:port];
        }
    }
    
    // Find connectable ports for client
    for (i = 0; i < nbClientPorts; ++i)
    {
        port = [jackViewClient.ports objectAtIndex:i];
        
        if (port.audioMidi == audioMidi
            && ((inputOutput == 1 && port.inputOutput == 2)
                || (inputOutput == 2 && port.inputOutput == 1)))
        {
            [jackViewClientAvailablePorts addObject:port];
        }
    }
    
    if ([jackViewAppClientAvailablePorts count] == 0
        || [jackViewClientAvailablePorts count] == 0)
    {
        return NO;
    }
    
    // Connect rules
    // Audio
    if (audioMidi == 1)
    {
        // Input or output, Same number of inputs for app client and client
        if ([jackViewAppClientAvailablePorts count] == [jackViewClientAvailablePorts count])
        {
            for (i = 0; i < [jackViewAppClientAvailablePorts count]; ++i)
            {
                if (inputOutput == 1)
                {
                    jack_connect(_jackClient,
                                 [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:i])).name cStringUsingEncoding:NSUTF8StringEncoding],
                                 [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:i])).name cStringUsingEncoding:NSUTF8StringEncoding]);
                }
                else if (inputOutput == 2)
                {
                    jack_connect(_jackClient,
                                 [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:i])).name cStringUsingEncoding:NSUTF8StringEncoding],
                                 [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:i])).name cStringUsingEncoding:NSUTF8StringEncoding]);
                }
            }
        }
        
        // Input, 2 inputs for app client, 1 output for client
        else if (inputOutput == 1
            && [jackViewAppClientAvailablePorts count] == 2
            && [jackViewClientAvailablePorts count] == 1)
        {
            jack_connect(_jackClient,
                         [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding],
                         [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding]);
            
            jack_connect(_jackClient,
                         [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding],
                         [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:1])).name cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        
        // Input, 1 input for app client, 2 outputs for client
        else if (inputOutput == 1
                 && [jackViewAppClientAvailablePorts count] == 1
                 && [jackViewClientAvailablePorts count] == 2)
        {
            
            jack_connect(_jackClient,
                         [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding],
                         [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding]);
            
            jack_connect(_jackClient,
                         [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:1])).name cStringUsingEncoding:NSUTF8StringEncoding],
                         [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        
        // Other input cases
        else if (inputOutput == 1)
        {
            
            jack_connect(_jackClient,
                         [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding],
                         [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        
        // Other output cases
        else
        {
            
            jack_connect(_jackClient,
                         [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding],
                         [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding]);
        }
    }
    
    // Midi
    else if (audioMidi == 2)
    {
        // Input cases
        if (inputOutput == 1)
        {
            
            jack_connect(_jackClient,
                         [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding],
                         [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        
        // Output cases
        else
        {
            
            jack_connect(_jackClient,
                         [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding],
                         [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:0])).name cStringUsingEncoding:NSUTF8StringEncoding]);
        }
    }
    
    return YES;
}

// Returns YES if software was able to disconnect, NO otherwise
- (BOOL)quicklyDisconnectAppToClient:(NSString*)clientName
                         inputOutput:(int)inputOutput
                           audioMidi:(int)audioMidi
{
    JackViewClient* jackViewAppClient = [self clientWithName:_currentClientName];
    int nbAppClientPorts = [jackViewAppClient.ports count];
    int i = 0;
    int j = 0;
    JackViewPort* port = nil;
    const char **connections;
    NSString* connection = nil;
    NSString* client = nil;
    
    // Find app client ports connected to client
    for (i = 0; i < nbAppClientPorts; ++i)
    {
        port = [jackViewAppClient.ports objectAtIndex:i];
        
        if (port.audioMidi == audioMidi
            && port.inputOutput == inputOutput)
        {            
            if ((connections = jack_port_get_all_connections(_jackClient,
                                                             jack_port_by_name(_jackClient,
                                                                               [port.name cStringUsingEncoding:NSUTF8StringEncoding]))) != 0)
            {
				for (j = 0; connections[j]; j++)
                {
                    connection = [NSString stringWithCString:connections[j] encoding:NSUTF8StringEncoding];
                    client = [[connection componentsSeparatedByString:@":"] objectAtIndex:0];
                                        
                    if ([client compare:_currentClientName])
                    {
                        if (inputOutput == 1)
                        {
                            jack_disconnect(_jackClient,
                                            connections[j],
                                            [port.name cStringUsingEncoding:NSUTF8StringEncoding]);
                        }
                        else if (inputOutput == 2)
                        {
                            jack_disconnect(_jackClient,
                                            [port.name cStringUsingEncoding:NSUTF8StringEncoding],
                                            connections[j]);
                        }
                    }
				}
				jack_free (connections);
			}
        }
    }
    
    return YES;
}

- (void)connectPort:(NSString*)inputPort
           withPort:(NSString*)outputPort
{    
    jack_connect(_jackClient,
                 [inputPort cStringUsingEncoding:NSUTF8StringEncoding],
                 [outputPort cStringUsingEncoding:NSUTF8StringEncoding]);
}

- (void)disconnectPort:(NSString*)inputPort
              withPort:(NSString*)outputPort
{
    jack_disconnect(_jackClient,
                    [inputPort cStringUsingEncoding:NSUTF8StringEncoding],
                    [outputPort cStringUsingEncoding:NSUTF8StringEncoding]);
}

- (BOOL)isPointInsideCurrentAppIcon:(CGPoint)pt
{
    return (pt.x >= self.currentClientButton.frame.origin.x
            && pt.x <= self.currentClientButton.frame.origin.x + self.currentClientButton.frame.size.width
            && pt.y >= self.currentClientButton.frame.origin.y
            && pt.y <= self.currentClientButton.frame.origin.y + self.currentClientButton.frame.size.height);
}

- (BOOL)isPointInsideView:(CGPoint)pt
{
    return (pt.x >= 0
            && pt.x <= self.frame.size.width
            && pt.y >= 0
            && pt.y <= self.frame.size.height);
}


// Refresh view
- (void)drawRect:(CGRect)rect
{
    UIBezierPath* path = [UIBezierPath bezierPath];
    CGPoint pt;
    UIFont* font = [UIFont systemFontOfSize:11.0f];
    NSString* str = nil;
    
    [[UIColor colorWithWhite:0.8 alpha:0.95] set];
    
    [path moveToPoint:CGPointMake(rect.origin.x, rect.origin.y)];
    [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y)];
    [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height)];
    [path addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height)];
    [path closePath];
    [path fillWithBlendMode:kCGBlendModeNormal alpha:1.];
    
    // In / Out
    [[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"jackview-in" ofType:@"png"]] drawAtPoint:CGPointMake(kJackViewExtHMargins, 0)];
    [[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"jackview-out" ofType:@"png"]] drawAtPoint:CGPointMake(rect.origin.x + rect.size.width - 75 - kJackViewExtHMargins, 0)];
    
    // Left section
    //   Input(s)
    if (!_audioInputsScrollView.hidden
        || !_midiInputsScrollView.hidden)
    {
        [path removeAllPoints];
        [[UIColor colorWithWhite:0. alpha:0.6] set];
        [path moveToPoint:CGPointMake(0, kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins)];
        [path addLineToPoint:CGPointMake(rect.size.width / 2., kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins)];
        [path stroke];
        
        [[UIColor blackColor] set];
        pt = CGPointMake(currentClientButton.frame.origin.x,
                         kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins);
        [path removeAllPoints];
        [path moveToPoint:CGPointMake(pt.x - 8, pt.y - 2.5)];
        [path addLineToPoint:CGPointMake(pt.x + 2, pt.y)];
        [path addLineToPoint:CGPointMake(pt.x - 8, pt.y + 2.5)];
        [path closePath];
        [path fill];
    }
    
    //   No input
    else
    {
        if (self.audioButton.selected) str = @"no audio input";
        else str = @"no midi input";
        pt = CGPointMake((float)kJackViewExtHMargins,
                         (float)(kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins));
        [[UIColor blackColor] set];
        [str drawAtPoint:pt
                withFont:font];
    }
    
    
    // Right section
    //   Output(s)
    if (!_audioInputsScrollView.hidden
        || !_midiInputsScrollView.hidden)
    {
        [path removeAllPoints];
        [[UIColor colorWithWhite:0. alpha:0.6] set];
        [path moveToPoint:CGPointMake(rect.size.width / 2., kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins)];
        [path addLineToPoint:CGPointMake(rect.size.width, kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins)];
        [path stroke];
        
        [[UIColor blackColor] set];
        pt = CGPointMake(currentClientButton.frame.origin.x + currentClientButton.frame.size.width + 10,
                         kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins);
        [path removeAllPoints];
        [path moveToPoint:CGPointMake(pt.x - 11, pt.y - 2.5)];
        [path addLineToPoint:CGPointMake(pt.x - 1, pt.y)];
        [path addLineToPoint:CGPointMake(pt.x - 11, pt.y + 2.5)];
        [path closePath];
        [path fill];
    }
    
    //   No output
    else
    {
        if (self.audioButton.selected) str = @"no audio output";
        else str = @"no midi output";
        CGSize stringBoundingBox = [str sizeWithFont:font];
        pt = CGPointMake(self.frame.size.width - stringBoundingBox.width - kJackViewExtHMargins,
                         kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins);
        [[UIColor blackColor] set];
        [str drawAtPoint:pt
                withFont:font];
    }
    
    // Right section
    
    /*[path removeAllPoints];
    [path moveToPoint:CGPointMake(0, kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins)];
    [path addLineToPoint:CGPointMake(rect.size.width, kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins)];
    [path stroke];

    [[UIColor blackColor] set];
    
    pt = CGPointMake(currentClientButton.frame.origin.x,
                     kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins);
    [path removeAllPoints];
    [path moveToPoint:CGPointMake(pt.x - 8, pt.y - 2.5)];
    [path addLineToPoint:CGPointMake(pt.x + 2, pt.y)];
    [path addLineToPoint:CGPointMake(pt.x - 8, pt.y + 2.5)];
    [path closePath];
    [path fill];
    
    pt = CGPointMake(currentClientButton.frame.origin.x + currentClientButton.frame.size.width + 10,
                     kJackViewExtTopVMargins + kJackViewButtonWidth / 2. + kJackViewIconMargins);
    [path removeAllPoints];
    [path moveToPoint:CGPointMake(pt.x - 11, pt.y - 2.5)];
    [path addLineToPoint:CGPointMake(pt.x - 1, pt.y)];
    [path addLineToPoint:CGPointMake(pt.x - 11, pt.y + 2.5)];
    [path closePath];
    [path fill];*/
}

- (int)numberOfCurrentAppPortsWithInputOutput:(int)inputOutput
                                    audioMidi:(int)audioMidi
{
    JackViewClient* client = [self clientWithName:_currentClientName];
    JackViewPort* port = nil;
    int nbPorts = [client.ports count];
    int i = 0;
    int cpt = 0;
    
    // Find ports to display
    for (i = 0; i < nbPorts; ++i)
    {
        port = [client.ports objectAtIndex:i];
        
        if (((port.inputOutput == 1 && inputOutput == 2) || (port.inputOutput == 2 && inputOutput == 1))
            && port.audioMidi == audioMidi)
        {
            cpt++;
        }
    }
    
    return cpt;
}

- (void)displayCurrentAppPortsWithInputOutput:(int)inputOutput audioMidi:(int)audioMidi
{
    JackViewClient* client = [self clientWithName:_currentClientName];
    JackViewPort* port = nil;
    int nbPorts = [client.ports count];
    int i = 0;
    NSMutableArray* portsArray = [NSMutableArray arrayWithCapacity:0];
    
    // Find ports to display
    for (i = 0; i < nbPorts; ++i)
    {
        port = [client.ports objectAtIndex:i];
        
        if (((port.inputOutput == 1 && inputOutput == 2) || (port.inputOutput == 2 && inputOutput == 1))
            && port.audioMidi == audioMidi)
        {
            [portsArray addObject:port];
        }
    }

    for (i = 0; i < [portsArray count]; ++i)
    {
        JackViewPortsViewItem* item = [[JackViewPortsViewItem alloc] initWithFrame:CGRectMake(self.portsView.currentAppX, i * kPortsViewItemHeight, kPortsViewItemWidth, kPortsViewItemHeight)];
        
        item.longName = ((JackViewPort*)([portsArray objectAtIndex:i])).name;
        item.selected = [self isPort:((JackViewPort*)([portsArray objectAtIndex:i]))
     connectedToCurrentClientInputOutput:((JackViewPort*)([portsArray objectAtIndex:i])).inputOutput
                               audioMidi:((JackViewPort*)([portsArray objectAtIndex:i])).audioMidi];
        
        [self.portsView addItem:item];
    }
}

- (void)viewClicked
{
    [self dismissPortsView];
}

- (void)dismissPortsView
{
    if (portsView)
    {
        [portsView removeFromSuperview];
        [portsView release];
        portsView = nil;
        [self.superview setNeedsDisplay];
        
        // Fade in
        CATransition *animation = [CATransition animation];
        [animation setDuration:0.3];
        [animation setType:kCATransitionFade];
        [animation setSubtype:kCATransitionFromLeft];
        [animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut]];
        
        [[self.window layer] addAnimation:animation forKey:@"DismissPortsView"];
    }
}

- (void)fsToClient
{    
    if (!self.portsView) return;
    
    NSString* clientName = self.portsView.clientButton.jackViewClient.name;
    
    // Switch to Jack server
    if ([clientName compare:@"system"] == NSOrderedSame
        || [clientName compare:@"system_midi"] == NSOrderedSame)
    {
        jack_gui_switch_to_client([self jackClient], "jack");
    }
    
    // Switch to other client
    else
    {
        jack_gui_switch_to_client([self jackClient], [clientName cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
    [self dismissPortsView];
}

- (void)showHideScrollViews
{
    if (self.audioButton.selected)
    {
        _audioInputsScrollView.hidden = ![self hasCurrentClientCompatiblePortWithInputOutput:1 audioMidi:1];
        _audioOutputsScrollView.hidden = ![self hasCurrentClientCompatiblePortWithInputOutput:2 audioMidi:1];
        _midiInputsScrollView.hidden = YES;
        _midiOutputsScrollView.hidden = YES;
    }
    else if (self.midiButton.selected)
    {
        _audioInputsScrollView.hidden = YES;
        _audioOutputsScrollView.hidden = YES;
        _midiInputsScrollView.hidden = ![self hasCurrentClientCompatiblePortWithInputOutput:1 audioMidi:2];
        _midiOutputsScrollView.hidden = ![self hasCurrentClientCompatiblePortWithInputOutput:2 audioMidi:2];
    }
}

@end





































