//
//  JackView.m
//  iOS
//
//  Created by Olivier Guillerminet on 02/04/13.
//
//

#import "JackView.h"

@implementation JackView


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self)
    {
        _jackClient = NULL;
        self.backgroundColor = [UIColor grayColor];
    }
    
    return self;
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
        NSString* tmpStr = nil;
        size_t size = 0;
        void* rawData = NULL;
        NSData* data = nil;
        UIImage* icon = nil;
        UIImageView* iconView = nil;
        
        tmpStr = [NSString stringWithCString:ports[i] encoding:NSUTF8StringEncoding];
        tmpStr = [[tmpStr componentsSeparatedByString:@":"] objectAtIndex:0];
        
        res = jack_custom_get_data(_jackClient, [tmpStr cStringUsingEncoding:NSUTF8StringEncoding], "icon.png", &rawData, &size);
        
        if (res == 0)
        {
            data = [NSData dataWithBytes:rawData length:size];
            icon = [UIImage imageWithData:data];
            
            iconView = [[UIImageView alloc] initWithImage:icon];
            [iconView setFrame:CGRectMake(10 + xOffset, 10, 80, 80)];
            
            [self addSubview:iconView];
            
            xOffset += 80 + 10;
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


@end