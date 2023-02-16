//
//  ViewController.m
//  faustbench
//
//  Created by Stéphane LETZ on 23/02/2017.
//  Copyright © 2017 Stéphane LETZ. All rights reserved.
//

#import "ViewController.h"

#import "../Config.h"
#include "faust/gui/Soundfile.h"

// To be used by DSP code if no SoundUI is used
extern Soundfile* defaultsound;

extern "C" int bench_all(const char* name, int run, int buffer_size, bool is_trace, bool is_control, int ds, int us, int filter);

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    defaultsound = new Soundfile(MAX_CHAN, 1024, MAX_CHAN, 1, (sizeof(FAUSTFLOAT) == 8));
    bench_all("Test iOS", 1, 512, true, false, DOWN_SAMPLING, UP_SAMPLING, FILTER_TYPE);
    delete defaultsound;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
