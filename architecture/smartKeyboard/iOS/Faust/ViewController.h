//
//  ViewController.h
//  iOSKeyboard
//
//  Created by Romain Michon on 6/6/16.
//  Copyright © 2016 CCRMA. All rights reserved.
//

#define MULTI_KEYBOARD_ONLY 1

#import <UIKit/UIKit.h>
#if MULTI_KEYBOARD_ONLY == 0
#import "InstrumentInterface.h"
#import "PresetMenu.h"
#endif
#import "DspFaust.h"
#import "MultiKeyboard.h"

@interface ViewController : UIViewController

@end
