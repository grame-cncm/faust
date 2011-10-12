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

#import "iPhoneAppDelegate.h"
#import "iPhoneViewController.h"
#include "iphone-faust.h"


@implementation iPhoneAppDelegate

@synthesize window;
@synthesize viewController;

TiPhoneCoreAudioRenderer* audio_device = NULL;
UI* interface = NULL;
MY_Meta metadata;
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
