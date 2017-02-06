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
#import "MultiKeyboard.h"
#import "DspFaust.h"

@interface ViewController : UIViewController


@end

