//
//  JackView.m
//  iOS
//
//  Created by Olivier Guillerminet on 02/04/13.
//
//


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
    float x = 0.f;
    float y = 0.f;
    float w = 0.f;
    float h = 0.f;
    int i = 0;
    NSArray* compatiblePorts = [self.jackViewClient compatiblePortsWithInputOutput:self.inputOutput audioMidi:self.audioMidi];
    CGPoint pt = [self convertPoint:CGPointMake(0., 0.) toView:jackView.superview];
    CGPoint defPt;
    
    x = 0;
    w = jackView.frame.size.width;
    h = fmaxf([compatiblePorts count] * kPortsViewItemHeight + kPortsArrowHeight,
              [jackView numberOfCurrentAppPortsWithInputOutput:self.inputOutput audioMidi:self.audioMidi] * kPortsViewItemHeight + kPortsArrowHeight);
    y = 0. - h;
    
    // TODO : add a max height
    
    if (jackView.portsView)
    {
        if (jackView.portsView.clientButton == self)
        {
            [jackView.portsView removeFromSuperview];
            [jackView.portsView release];
            jackView.portsView = nil;
            [jackView.superview setNeedsDisplay];
            
            return;
        }
        else
        {
            [jackView.portsView removeFromSuperview];
            [jackView.portsView release];
            jackView.portsView = nil;
            [jackView.superview setNeedsDisplay];
        }
    }
    
    defPt = [self convertPoint:CGPointMake(x, y) toView:jackView.superview];
    
    jackView.portsView = [[JackViewPortsView alloc] initWithFrame:CGRectMake(x, defPt.y, w, h)];
    jackView.portsView.clientButton = self;
    
    if (pt.x + kPortsViewWidth < jackView.frame.size.width) jackView.portsView.clientX = pt.x;
    else jackView.portsView.clientX = jackView.frame.size.width - kPortsViewWidth;
    
    jackView.portsView.currentAppX = [jackView convertPoint:jackView.currentClientButton.frame.origin toView:jackView.superview].x;
    
    for (i = 0; i < [compatiblePorts count]; ++i)
    {
        JackViewPortsViewItem* item = [[JackViewPortsViewItem alloc] initWithFrame:CGRectMake(jackView.portsView.clientX,
                                                                                              i * kPortsViewItemHeight,
                                                                                              kPortsViewWidth,
                                                                                              kPortsViewItemHeight)];
        item.longName = ((JackViewPort*)([compatiblePorts objectAtIndex:i])).name;
        item.alias = @"alias";
        
        item.selected = [jackView isPort:((JackViewPort*)([compatiblePorts objectAtIndex:i]))
            connectedToCurrentClientInputOutput:((JackViewPort*)([compatiblePorts objectAtIndex:i])).inputOutput
                               audioMidi:((JackViewPort*)([compatiblePorts objectAtIndex:i])).audioMidi];
        
        [jackView.portsView addSubview:item];
    }
    
    if (self.inputOutput == 1) [jackView displayCurrentAppPortsWithInputOutput:2 audioMidi:self.audioMidi];
    else if (self.inputOutput == 2) [jackView displayCurrentAppPortsWithInputOutput:1 audioMidi:self.audioMidi];
    
    [jackView.superview addSubview:jackView.portsView];
    [jackView.portsView setNeedsDisplay];
}

- (void)buttonDoubleClicked
{
    //if (self == jackView.currentAppPortsView) return;
    
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

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    
    jackView.linking = YES;
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        jackView.srcPt = CGPointMake([touch locationInView:jackView].x, [touch locationInView:jackView].y);
    }
    
    [jackView setNeedsDisplay];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    
    if (jackView.portsView)
    {
        [jackView.portsView removeFromSuperview];
        [jackView.portsView release];
        jackView.portsView = nil;
    }
    
    jackView.linking = YES;
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        jackView.dstPt = CGPointMake([touch locationInView:jackView].x, [touch locationInView:jackView].y);
    }
    
    [jackView setNeedsDisplay];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        // Touch up inside current app icon : connect
        if ([self.jackView isPointInsideCurrentAppIcon:CGPointMake([touch locationInView:jackView].x, [touch locationInView:jackView].y)])
        {
            if (!self.isSelected)
            {
                if ([self.jackView quicklyConnectAppToClient:self.jackViewClient.name
                                                 inputOutput:inputOutput
                                                   audioMidi:audioMidi])
                {
                    self.selected = YES;
                }
            }
            
            [self setNeedsDisplay];
        }
        
        // Touch up outside view : disconnect
        else if (![self.jackView isPointInsideView:CGPointMake([touch locationInView:jackView].x, [touch locationInView:jackView].y)])
        {
            if (self.isSelected)
            {
                // Do nothing
                if ([self.jackView quicklyDisconnectAppToClient:self.jackViewClient.name
                                                    inputOutput:inputOutput
                                                      audioMidi:audioMidi])
                {
                    self.selected = NO;
                }
            }
            
            [self setNeedsDisplay];
        }
    }
    
    jackView.linking = NO;
    [jackView setNeedsDisplay];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    jackView.linking = NO;
    [jackView setNeedsDisplay];    
}

// Refresh view
- (void)drawRect:(CGRect)rect
{
    // Draw icon
    if (self.jackViewClient)
    {
        if (self.enabled) [self.jackViewClient.icon drawInRect:rect];
        else [self.jackViewClient.icon drawInRect:rect blendMode:kCGBlendModeNormal alpha:0.5];
    }
    
    // Draw selection
    if (self.selected)
    {
        UIBezierPath* path = [UIBezierPath bezierPath];
        
        [[UIColor whiteColor] set];
        
        [path moveToPoint:CGPointMake(rect.origin.x, rect.origin.y)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height)];
        [path addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height)];
        [path closePath];
        path.lineWidth = 2;
        [path strokeWithBlendMode:kCGBlendModeNormal alpha:1.];
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


@implementation JackViewDrawingView : UIView

@synthesize jackView;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self)
    {
    }
    
    return self;
}

- (void)dealloc
{
    
    [super dealloc];
}

- (void)drawRect:(CGRect)rect
{
    CGPoint srcPt = [jackView convertPoint:jackView.srcPt toView:self];
    CGPoint dstPt = [jackView convertPoint:jackView.dstPt toView:self];
    
    self.backgroundColor = [UIColor clearColor];
    
    if (jackView.linking)
    {
        CGContextRef c = UIGraphicsGetCurrentContext();
        
        CGFloat color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        CGContextSetStrokeColor(c, color);
        CGContextBeginPath(c);
        CGContextMoveToPoint(c, srcPt.x, srcPt.y);
        CGContextAddLineToPoint(c, dstPt.x, dstPt.y);
        CGContextStrokePath(c);
    }
}

@end


@implementation JackView

@synthesize linking;
@synthesize srcPt;
@synthesize dstPt;
@synthesize portsView;
@synthesize currentClientButton;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self)
    {
        self.portsView = nil;
        self.linking = NO;
        _jackClient = nil;
        self.currentClientButton = nil;
        self.backgroundColor = [UIColor colorWithWhite:0.1 alpha:0.7];
                
        _audioInputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(kJackViewExtHMargins,
                                                                                kJackViewExtVMargins,
                                                                                frame.size.width / 2. - kJackViewExtHMargins - kJackViewIntHMargins / 2.,
                                                                                frame.size.height / 2. - kJackViewExtVMargins - kJackViewIntVMargins / 2.)];
        
        _audioOutputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(frame.size.width / 2. + kJackViewIntHMargins / 2.,
                                                                                 kJackViewExtVMargins,
                                                                                 frame.size.width / 2. - kJackViewExtHMargins - kJackViewIntHMargins / 2.,
                                                                                 frame.size.height / 2. - kJackViewExtVMargins - kJackViewIntVMargins / 2.)];
        
        _midiInputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(kJackViewExtHMargins,
                                                                               frame.size.height / 2. + kJackViewIntVMargins / 2.,
                                                                               frame.size.width / 2. - kJackViewExtHMargins - kJackViewIntHMargins / 2.,
                                                                               frame.size.height / 2. - kJackViewExtVMargins - kJackViewIntVMargins / 2.)];
        
        _midiOutputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(frame.size.width / 2. + kJackViewIntHMargins / 2.,
                                                                                frame.size.height / 2. + kJackViewIntVMargins / 2.,
                                                                                frame.size.width / 2. - kJackViewExtHMargins - kJackViewIntHMargins / 2.,
                                                                                frame.size.height / 2. - kJackViewExtVMargins - kJackViewIntVMargins / 2.)];
        
        _audioInputsScrollView.backgroundColor = [UIColor colorWithWhite:0.2 alpha:0.7];
        _audioOutputsScrollView.backgroundColor = [UIColor colorWithWhite:0.2 alpha:0.7];
        _midiInputsScrollView.backgroundColor = [UIColor colorWithWhite:0.2 alpha:0.7];
        _midiOutputsScrollView.backgroundColor = [UIColor colorWithWhite:0.2 alpha:0.7];
        
        _audioInputsScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        _audioOutputsScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        _midiInputsScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        _midiOutputsScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        
        [self addSubview:_audioInputsScrollView];
        [self addSubview:_audioOutputsScrollView];
        [self addSubview:_midiInputsScrollView];
        [self addSubview:_midiOutputsScrollView];
        
        _clients = [[NSMutableArray alloc] initWithCapacity:0];
    }
    
    return self;
}

- (void)dealloc
{
    [_clients release];
    [_audioInputsScrollView release];
    [_audioOutputsScrollView release];
    [_midiInputsScrollView release];
    [_midiOutputsScrollView release];
    [_drawingView release];
    
    if (self.portsView)
    {
        [self.portsView removeFromSuperview];
        [self.portsView release];
        self.portsView = nil;
        [self.superview setNeedsDisplay];
    }
    
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
            JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake([[_audioInputsScrollView subviews] count] * kJackViewIconDimension + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewIconDimension,
                                                                                kJackViewIconDimension)];
            jackViewClient.audioInputButton = button;
            button.jackViewClient = jackViewClient;
            button.jackView = self;
            button.audioMidi = 1;
            button.inputOutput = 1;
            [_audioInputsScrollView addSubview:jackViewClient.audioInputButton];
        }
        else if (inputOutput == 1 && audioMidi == 1 && jackViewClient.audioOutputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake([[_audioOutputsScrollView subviews] count] * kJackViewIconDimension + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewIconDimension,
                                                                                kJackViewIconDimension)];
            jackViewClient.audioOutputButton = button;
            button.jackViewClient = jackViewClient;
            button.jackView = self;
            button.audioMidi = 1;
            button.inputOutput = 2;
            [_audioOutputsScrollView addSubview:jackViewClient.audioOutputButton];
        }
        else if (inputOutput == 2 && audioMidi == 2 && jackViewClient.midiInputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake([[_midiInputsScrollView subviews] count] * kJackViewIconDimension + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewIconDimension,
                                                                                kJackViewIconDimension)];
            jackViewClient.midiInputButton = button;
            button.jackViewClient = jackViewClient;
            button.jackView = self;
            button.audioMidi = 2;
            button.inputOutput = 1;
            [_midiInputsScrollView addSubview:jackViewClient.midiInputButton];
        }
        else if (inputOutput == 1 && audioMidi == 2 && jackViewClient.midiOutputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake([[_midiOutputsScrollView subviews] count] * kJackViewIconDimension + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewIconDimension,
                                                                                kJackViewIconDimension)];
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
    
    // Add current app icon
    JackViewButton* button = [[JackViewButton alloc] initWithFrame:CGRectMake(self.frame.size.width / 2. - kJackViewCurrentAppIconDimension / 2.,
                                                                              self.frame.size.height - kJackViewCurrentAppIconBottomMargin - kJackViewCurrentAppIconDimension,
                                                                              kJackViewCurrentAppIconDimension,
                                                                              kJackViewCurrentAppIconDimension)];
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

    // Load drawing view
    _drawingView = [[JackViewDrawingView alloc] initWithFrame:CGRectMake(0., -self.frame.origin.y, 2000, 2000)];
    //_drawingView.autoresizingMask = self.autoresizingMask;
    _drawingView.jackView = self;
    [self addSubview:_drawingView];
    [_drawingView setNeedsDisplay];
    
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

- (BOOL)isPointInsideCurrentAppPortsView:(CGPoint)pt
{    
    /*return (pt.x >= self.currentAppPortsView.frame.origin.x
            && pt.x <= self.currentAppPortsView.frame.origin.x + self.currentAppPortsView.frame.size.width
            && pt.y >= self.currentAppPortsView.frame.origin.y
            && pt.y <= self.currentAppPortsView.frame.origin.y + self.currentAppPortsView.frame.size.height);*/
    return NO;
}

- (NSString*)getPortDefinedAtPoint:(CGPoint)pt
{
    NSArray* items = nil;
    JackViewPortsViewItem* item = nil;
    int i = 0;
    CGRect frame;
    
    /*if (self.currentAppPortsView)
    {
        NSLog(@"scan %f %f", pt.x, pt.y);
        items = [self.currentAppPortsView subviews];
        
        for (i = 0; i < [items count]; ++i)
        {
            item = (JackViewPortsViewItem*)([items objectAtIndex:i]);
            frame = [item convertRect:item.frame toView:self.superview];
            
            NSLog(@"  %@", item.longName);
            NSLog(@"  %f %f %f %f", frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
            
            if (pt.x >= frame.origin.x
                && pt.x <= frame.origin.x + frame.size.width
                && pt.y >= frame.origin.y
                && pt.y <= frame.origin.y + frame.size.height)
            {
                NSLog(@"      >> connect");
                return item.longName;
            }
        }
    }*/
    
    return nil;
}

// Refresh view
- (void)drawRect:(CGRect)rect
{
    if (linking)
    {
        _drawingView.hidden = NO;
        [_drawingView setNeedsDisplay];
    }
    else
    {
        _drawingView.hidden = YES;
        [_drawingView setNeedsDisplay];
    }
}

- (int)numberOfCurrentAppPortsWithInputOutput:(int)inputOutput
                                    audioMidi:(int)audioMidi
{
    JackViewClient* client = [self clientWithName:_currentClientName];
    JackViewPort* port = nil;
    int nbPorts = [client.ports count];
    int i = 0;
    NSMutableArray* portsArray = [NSMutableArray arrayWithCapacity:0];
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
        JackViewPortsViewItem* item = [[JackViewPortsViewItem alloc] initWithFrame:CGRectMake(self.portsView.currentAppX, i * kPortsViewItemHeight, kPortsViewWidth, kPortsViewItemHeight)];
        item.longName = ((JackViewPort*)([portsArray objectAtIndex:i])).name;
        item.alias = @"alias";
        
        item.selected = [self isPort:((JackViewPort*)([portsArray objectAtIndex:i]))
     connectedToCurrentClientInputOutput:((JackViewPort*)([portsArray objectAtIndex:i])).inputOutput
                               audioMidi:((JackViewPort*)([portsArray objectAtIndex:i])).audioMidi];
        
        [self.portsView addSubview:item];
    }
}


@end





































