/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
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
