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

#import "FIAppDelegate.h"
#import "FIMainViewController.h"

@implementation FIAppDelegate

@synthesize window = _window;
@synthesize mainViewController = _mainViewController;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleBlackOpaque;
    
    [UIApplication sharedApplication].idleTimerDisabled = YES;
    
    // Default setting that have to be in coherence with what is defined in Interface Builder
    NSDictionary *appDefaults = [NSDictionary dictionaryWithObjectsAndKeys:
                                [NSNumber numberWithInteger:44100], @"sampleRate",
                                [NSNumber numberWithInteger:256], @"bufferSize",
                                [NSNumber numberWithBool:TRUE], @"openWidgetPanel",
                                [NSNumber numberWithBool:TRUE], @"concertUI",nil];
    
    
    [[NSUserDefaults standardUserDefaults] registerDefaults:appDefaults];

    
    return YES;
}

// Fast switch testing
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
     [self.mainViewController saveGui];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    [self.mainViewController openAudio];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [self.mainViewController loadGui];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [self.mainViewController closeAudio];
}

@end
