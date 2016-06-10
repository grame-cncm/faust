//
//  ViewController.m
//  iOSKeyboard
//
//  Created by Romain Michon on 6/6/16.
//  Copyright © 2016 CCRMA. All rights reserved.
//

#import "ViewController.h"

// TODO: this is so dirty plus we don't know what this does
std::list<GUI*> GUI::fGuiList;

@interface ViewController ()

@end

@implementation ViewController{
    audio* audioDevice;
    mydsp_poly* synthDSP;
    dsp* mainDSP;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    int SR = 44100;
    int bufferSize = 256;
    audioDevice = new iosaudio(SR, bufferSize);
    synthDSP = new mydsp_poly(10,true,false);
    
    #if POLY2
    mainDSP = new dsp_sequencer(synthDSP, new effect());
    audioDevice->init("Faust", mainDSP);
    #else
    audioDevice->init("Faust", synthDSP);
    #endif
    
    audioDevice->start();
    
    // For now, just interface...
    //KeyboardView *myZone = [[KeyboardView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.view.frame.size.width, self.view.frame.size.height) withPolyDSP:DSP];
    
    MultiKeyboard *myZone = [[MultiKeyboard alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.view.frame.size.width, self.view.frame.size.height) withPolyDSP:synthDSP];
    [self.view addSubview:myZone];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    if(audioDevice) {
        audioDevice->stop();
        delete audioDevice;
        audioDevice = NULL;
    }
    if(synthDSP){
        delete synthDSP;
        synthDSP = NULL;
    }
    if(mainDSP){
        delete mainDSP;
        mainDSP = NULL;
    }
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (BOOL) shouldAutorotate{
    return NO;
}

@end
