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
    [super dealloc];
}

- (void)buttonClicked
{
    if (self.isSelected) self.selected = NO;
    else self.selected = YES;
    
    [self.jackView quicklyConnectApp:self.selected
                            toClient:self.jackViewClient.name
                         inputOutput:inputOutput
                           audioMidi:audioMidi];
    
    [self setNeedsDisplay];
}

- (void)buttonDoubleClicked
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

// Refresh view
- (void)drawRect:(CGRect)rect
{
    // Draw icon
    if (self.jackViewClient)
    {
        [self.jackViewClient.icon drawInRect:rect];
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

@end




@implementation JackView


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self)
    {
        _jackClient = NULL;
        self.backgroundColor = [UIColor colorWithWhite:0.1 alpha:0.7];
                
        _audioInputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(kJackViewExtLRMargins,
                                                                                kJackViewExtTopBottomMargins,
                                                                                frame.size.width / 2. - kJackViewExtLRMargins - kJackViewIntMargins / 2.,
                                                                                frame.size.height / 2. - kJackViewExtTopBottomMargins - kJackViewIntMargins / 2.)];
        
        _audioOutputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(frame.size.width / 2. + kJackViewIntMargins / 2.,
                                                                                 kJackViewExtTopBottomMargins,
                                                                                 frame.size.width / 2. - kJackViewExtLRMargins - kJackViewIntMargins / 2.,
                                                                                 frame.size.height / 2. - kJackViewExtTopBottomMargins - kJackViewIntMargins / 2.)];
        
        _midiInputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(kJackViewExtLRMargins,
                                                                               frame.size.height / 2. + kJackViewIntMargins / 2.,
                                                                               frame.size.width / 2. - kJackViewExtLRMargins - kJackViewIntMargins / 2.,
                                                                               frame.size.height / 2. - kJackViewExtTopBottomMargins - kJackViewIntMargins / 2.)];
        
        _midiOutputsScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(frame.size.width / 2. + kJackViewIntMargins / 2.,
                                                                                frame.size.height / 2. + kJackViewIntMargins / 2.,
                                                                                frame.size.width / 2. - kJackViewExtLRMargins - kJackViewIntMargins / 2.,
                                                                                frame.size.height / 2. - kJackViewExtTopBottomMargins - kJackViewIntMargins / 2.)];
        
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
    [super dealloc];
}

- (void)loadJackClient:(jack_client_t*)jackClient
{
	jack_status_t status;
	const char **ports, **connections;
	int show_aliases = 0;
	int show_con = 0;
	int show_port_latency = 0;
	int show_total_latency = 0;
	int show_properties = 0;
	int show_type = 0;
	char* aliases[2];
	jack_port_t *port;
    int i,j;
    
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
		printf ("PORT [%i] - %s\n", i, ports[i]);
		port = jack_port_by_name (_jackClient, ports[i]);
        
        
        
        ////
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
            res = jack_custom_get_data(_jackClient, [clientName cStringUsingEncoding:NSUTF8StringEncoding], "icon.png", &rawData, &size);
            
            if (res == 0)
            {
                data = [NSData dataWithBytes:rawData length:size];
                jackViewClient.icon = [[UIImage alloc] initWithData:data];

            }
            else if ([clientName compare:@"system"] == NSOrderedSame
                     || [clientName compare:@"system_midi"] == NSOrderedSame)
            {
                jackViewClient.icon = [[UIImage alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Icon_Apple" ofType:@"png"]];
            }
            
            NSLog(@"Create client %@", jackViewClient.name);
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
        
        
        ////
        
        
        
        
		if (show_aliases)
        {
			int cnt;
            
			cnt = jack_port_get_aliases (port, aliases);
			for (j = 0; j < cnt; ++j)
            {
				printf ("   ALIAS [%i] - %s\n", j, aliases[j]);
			}
		}
        
		if (show_con)
        {
			if ((connections = jack_port_get_all_connections (_jackClient, jack_port_by_name(_jackClient, ports[i]))) != 0)
            {
				for (j = 0; connections[j]; j++)
                {
					printf ("   CONNECTION [%i] - %s\n", j, connections[j]);
				}
				free (connections);
			}
		}
        
		if (show_port_latency)
        {
			if (port)
            {
				jack_latency_range_t range;
				printf ("	port latency = %" PRIu32 " frames\n",
                        jack_port_get_latency (port));
                
				jack_port_get_latency_range (port, JackPlaybackLatency, &range);
				printf ("	port playback latency = [ %" PRIu32 " %" PRIu32 " ] frames\n",
                        range.min, range.max);
                
				jack_port_get_latency_range (port, JackCaptureLatency, &range);
				printf ("	port capture latency = [ %" PRIu32 " %" PRIu32 " ] frames\n",
                        range.min, range.max);
			}
		}
        
		if (show_total_latency)
        {
			if (port)
            {
				printf ("	total latency = %d frames\n", jack_port_get_total_latency (_jackClient, port));
			}
		}
        
		if (show_properties)
        {
			if (port)
            {
				int flags = jack_port_flags (port);
				printf ("	properties: ");
                
				if (flags & JackPortIsInput)
                {
					fputs ("input,", stdout);
				}
                
				if (flags & JackPortIsOutput)
                {
					fputs ("output,", stdout);
				}
                
				if (flags & JackPortCanMonitor)
                {
					fputs ("can-monitor,", stdout);
				}
                
				if (flags & JackPortIsPhysical)
                {
					fputs ("physical,", stdout);
				}
                
				if (flags & JackPortIsTerminal)
                {
					fputs ("terminal,", stdout);
				}
                
				putc ('\n', stdout);
			}
		}
        
		if (show_type)
        {
			if (port)
            {
				putc ('\t', stdout);
				fputs (jack_port_type (port), stdout);
				putc ('\n', stdout);
			}
		}
	}
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

- (void)quicklyConnectApp:(BOOL)connectApp toClient:(NSString*)clientName inputOutput:(int)inputOutput audioMidi:(int)audioMidi
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
    
    // Connect rules
    // Audio
    if (audioMidi == 1)
    {
        // Input or output, Same number of inputs for app client and client
        if ([jackViewAppClientAvailablePorts count] == [jackViewClientAvailablePorts count])
        {
            for (i = 0; i < [jackViewAppClientAvailablePorts count]; ++i)
            {
                jack_connect(_jackClient,
                             [((JackViewPort*)([jackViewClientAvailablePorts objectAtIndex:i])).name cStringUsingEncoding:NSUTF8StringEncoding],
                             [((JackViewPort*)([jackViewAppClientAvailablePorts objectAtIndex:i])).name cStringUsingEncoding:NSUTF8StringEncoding]);
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
}

@end





































