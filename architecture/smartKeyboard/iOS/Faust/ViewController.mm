//
//  ViewController.m
//  iOSKeyboard
//
//  Created by Romain Michon on 6/6/16.
//  Copyright © 2016 CCRMA. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController{
    DspFaust* faustDsp;
    NSInteger currentPreset;
    NSString *audioSettingsFile;
    NSDictionary *audioSettings;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    currentPreset = 0;
    
    NSString *documentsDirectory = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    
    // if no presets in documents directory, then upload defaults if they exist    
    NSArray *resourceFiles = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[[NSBundle mainBundle] resourcePath] error:nil];
    NSMutableArray *presetFiles = [[NSMutableArray alloc] init];
    for(int i=0; i<[resourceFiles count]; i++){
        if([[resourceFiles objectAtIndex:i] rangeOfString:@"_keyb"].location != NSNotFound || [[resourceFiles objectAtIndex:i] rangeOfString:@"_dsp"].location != NSNotFound){
            [presetFiles addObject:[resourceFiles objectAtIndex:i]];
        }
    }
    
    if([[[NSFileManager defaultManager] contentsOfDirectoryAtPath:documentsDirectory error:nil] count] == 0){
        for(int i=0; i<[presetFiles count]; i++){
            NSString *resourcePath = [[NSBundle mainBundle] pathForResource:[presetFiles objectAtIndex:i] ofType:nil];
            [[NSFileManager defaultManager] copyItemAtPath:resourcePath toPath:[documentsDirectory stringByAppendingPathComponent:[presetFiles objectAtIndex:i]] error:nil];
        }
    }
    
    // initializing audio settings
    audioSettingsFile = [documentsDirectory stringByAppendingPathComponent:@"audioSettings"];
    audioSettings = [[NSDictionary alloc] initWithContentsOfFile:audioSettingsFile];
    
    // if no saved settings then create defaults
    if([audioSettings count] == 0){
        [self createDefaultAudioSettings];
    }
    
    [self startFaustDsp];
    
    MultiKeyboard *multiKeyboard = [[MultiKeyboard alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.view.frame.size.width, self.view.frame.size.height) withFaustDSP:faustDsp withPreset:nil];
    [self.view addSubview:multiKeyboard];
}

// creates default audio settings
- (void)createDefaultAudioSettings{
    audioSettings = [NSMutableDictionary dictionaryWithDictionary:
                     @{
                       @"SR":[NSNumber numberWithInt:44100],
                       @"bufferLength":[NSNumber numberWithInt:256]
                       }];
    [audioSettings writeToFile:audioSettingsFile atomically:YES];
}

// start the faust dsp object and its associated elements
- (void)startFaustDsp{
    if(!faustDsp){
        faustDsp = new DspFaust([audioSettings[@"SR"] intValue],[audioSettings[@"bufferLength"] intValue]);
        faustDsp->start();
    }
}

// stop the faust dsp object and its associated elements
- (void)stopFaustDsp{
    if(faustDsp){
        faustDsp->stop();
        delete faustDsp;
        faustDsp = NULL;
    }
}

- (void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    [self stopFaustDsp];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (BOOL) shouldAutorotate{
    return NO;
}

@end
