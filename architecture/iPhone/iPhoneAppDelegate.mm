//
//  Copyright Grame 2010. All rights reserved.
//

#import "iPhoneAppDelegate.h"
#import "iPhoneViewController.h"
#include "iphone-faust.h"

@implementation iPhoneAppDelegate

@synthesize window;
@synthesize viewController;

TiPhoneCoreAudioRenderer* audio_device = NULL;
UI* interface = NULL;
Meta metadata;
char rcfilename[256];

- (void)applicationDidFinishLaunching:(UIApplication *)application 
{    
    DSP.metadata(&metadata);
    
    interface = new CocoaUI(window, viewController, &metadata);
    audio_device = new TiPhoneCoreAudioRenderer(DSP.getNumInputs(), DSP.getNumOutputs());
    
    long srate = 44100;
    int	fpb = 256;
    
    DSP.init(long(srate));
	DSP.buildUserInterface(interface);
    
    const char* home = getenv ("HOME");
    const char* name = (*metadata.find("name")).second;
    if (home == 0) 
        home = ".";
    snprintf(rcfilename, 256, "%s/Library/Caches/%s", home, name);
    interface->recallState(rcfilename);
	
    if (audio_device->Open(fpb, srate) < 0) {
        printf("Cannot open CoreAudio device\n");
        goto error;
    }
    
    if (audio_device->Start() < 0) {
        printf("Cannot start CoreAudio device\n");
        goto error;
    }
    
    return;
    
error:
     delete interface;
     delete audio_device;
}

- (void)applicationWillTerminate:(UIApplication *)application 
{
    interface->saveState(rcfilename);
}

- (void)dealloc
{
    audio_device->Stop();
    audio_device->Close();
    delete audio_device;
    delete interface;
    [super dealloc];
}

@end
