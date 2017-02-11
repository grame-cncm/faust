//
//  MultiKeyboard.h
//  MultiXYTest
//
//  Created by Romain Michon on 4/15/16.
//  Copyright © 2016 CCRMA. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#import "Zone.h"
#include "Smooth.h"
#include "DspFaust.h"

@interface MultiKeyboard : UIControl{
    CMMotionManager* _motionManager;
    NSTimer* _motionTimer;
    
    @public
    NSMutableDictionary *keyboardParameters; // the list of parameters of the interface TODO: may be shouldn't be public
    NSMutableDictionary *dspParameters; // TODO: may be shouldn't be public too
}

- (id)initWithFrame:(CGRect)frame withFaustDSP:(DspFaust*)dsp withPreset:(NSString*)presetName;
- (void)buildInterface;
- (void)savePreset;
- (void)clean;

@end
