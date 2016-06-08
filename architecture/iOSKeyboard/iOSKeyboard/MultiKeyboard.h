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
//#include "misc.h"
//#include "UI.h"
//#include "dsp.h"
#include "mydsp.h"
//#import "poly-dsp.h"

class mydsp_poly;

@interface MultiKeyboard : UIControl{
    CMMotionManager* _motionManager;
    NSTimer* _motionTimer;
    
    @public
    NSMutableDictionary *parameters; // the list of parameters of the interface
}

- (id)initWithFrame:(CGRect)frame withPolyDSP:(mydsp_poly*)dsp;
- (void)buildInterface;

@end
