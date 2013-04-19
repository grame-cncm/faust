//
//  JackView.m
//  iOS
//
//  Created by Olivier Guillerminet on 02/04/13.
//
//


#import "JackView.h"

@implementation JackViewClient

- (id)init
{
    self = [super init];
    
    if (self)
    {
        self.name = nil;
        self.icon = nil;
        self.ports = nil;
        self.audioInputButton = nil;
        self.audioOutputButton = nil;
        self.midiInputButton = nil;
        self.midiOutputButton = nil;
    }
    
    return self;
}


- (void)dealloc
{
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
    jack_options_t options = JackNoStartServer;
	const char **ports, **connections;
	int show_aliases = 1;
	int show_con = 1;
	int show_port_latency = 0;
	int show_total_latency = 0;
	int show_properties = 1;
	int show_type = 1;
	char* aliases[2];
	char *server_name = NULL;
	jack_port_t *port;
    int i,j;
    
    int xOffset = 0;
    
    _jackClient = jackClient;
    
    show_aliases = 1;
    show_con = 1;
    show_type = 1;
    
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
        
        _currentClientName = [[[NSString alloc] initWithCString:jack_get_client_name(_jackClient) encoding:NSUTF8StringEncoding] autorelease];
        
        clientName = [NSString stringWithCString:ports[i] encoding:NSUTF8StringEncoding];
        clientName = [[clientName componentsSeparatedByString:@":"] objectAtIndex:0];
        
        // Check if client doesn't exist already
        if (![self doesClientExist:clientName])
        {
            // If needed, create it
            jackViewClient = [[[JackViewClient alloc] init] autorelease];
            
            // Set its name
            jackViewClient.name = [[[NSString alloc] initWithString:clientName] autorelease];
            
            // Set its icon
            res = jack_custom_get_data(_jackClient, [clientName cStringUsingEncoding:NSUTF8StringEncoding], "icon.png", &rawData, &size);
            
            if (res == 0)
            {
                data = [NSData dataWithBytes:rawData length:size];
                jackViewClient.icon = [[[UIImage alloc] initWithData:data] autorelease];

            }
            else if ([clientName compare:@"system"] == NSOrderedSame
                     || [clientName compare:@"system_midi"] == NSOrderedSame)
            {
                jackViewClient.icon = [[[UIImage alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Icon_Apple" ofType:@"png"]] autorelease];
            }
        }
        else
        {
            jackViewClient = [self clientWithName:clientName];
        }

        // TODO : add port
        
        // input / output ?
        int flags = jack_port_flags (port);

        if (flags & JackPortIsInput) inputOutput = 1;
        else if (flags & JackPortIsOutput) inputOutput = 2;
        
        // Audio / midi ?
        portType = [NSString stringWithCString:jack_port_type(port) encoding:NSUTF8StringEncoding];
        
        if ([((NSString*)([[portType componentsSeparatedByString:@" "] lastObject])) compare:@"audio"] == NSOrderedSame) audioMidi = 1;
        else if ([((NSString*)([[portType componentsSeparatedByString:@" "] lastObject])) compare:@"midi"] == NSOrderedSame) audioMidi = 2;
        
        // Put the corresponding button in the right scroll view
        if (inputOutput == 2 && audioMidi == 1 && jackViewClient.audioInputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            UIImageView* button = [[UIImageView alloc] initWithFrame:CGRectMake([[_audioInputsScrollView subviews] count] * kJackViewIconDimension + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewIconDimension,
                                                                                kJackViewIconDimension)];
            button.image = jackViewClient.icon;
            jackViewClient.audioInputButton = button;
            [_audioInputsScrollView addSubview:jackViewClient.audioInputButton];
        }
        else if (inputOutput == 1 && audioMidi == 1 && jackViewClient.audioOutputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            UIImageView* button = [[UIImageView alloc] initWithFrame:CGRectMake([[_audioOutputsScrollView subviews] count] * kJackViewIconDimension + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewIconDimension,
                                                                                kJackViewIconDimension)];
            button.image = jackViewClient.icon;
            jackViewClient.audioOutputButton = button;
            [_audioOutputsScrollView addSubview:jackViewClient.audioOutputButton];
        }
        else if (inputOutput == 2 && audioMidi == 2 && jackViewClient.midiInputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            UIImageView* button = [[UIImageView alloc] initWithFrame:CGRectMake([[_midiInputsScrollView subviews] count] * kJackViewIconDimension + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewIconDimension,
                                                                                kJackViewIconDimension)];
            button.image = jackViewClient.icon;
            jackViewClient.midiInputButton = button;
            [_midiInputsScrollView addSubview:jackViewClient.midiInputButton];
        }
        else if (inputOutput == 1 && audioMidi == 2 && jackViewClient.midiOutputButton == nil && [_currentClientName compare:jackViewClient.name] != NSOrderedSame)
        {
            UIImageView* button = [[UIImageView alloc] initWithFrame:CGRectMake([[_midiOutputsScrollView subviews] count] * kJackViewIconDimension + kJackViewIconMargins,
                                                                                kJackViewIconMargins,
                                                                                kJackViewIconDimension,
                                                                                kJackViewIconDimension)];
            button.image = jackViewClient.icon;
            jackViewClient.midiOutputButton = button;
            [_midiOutputsScrollView addSubview:jackViewClient.midiOutputButton];
        }
        
        
        [_clients addObject:jackViewClient];
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

@end





































