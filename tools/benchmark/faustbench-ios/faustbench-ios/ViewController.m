//
//  ViewController.m
//  faustbench-ios
//
//  Created by Stéphane LETZ on 23/02/2017.
//  Copyright © 2017 Stéphane LETZ. All rights reserved.
//

#import "ViewController.h"

int bench_all(const char* name);

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    bench_all("iOS test");
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
