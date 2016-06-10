//
//  MultiKeyboard.m
//  MultiXYTest
//
//  Created by Romain Michon on 4/15/16.
//  Copyright © 2016 CCRMA. All rights reserved.
//

// TODOs
// - In very rare cases, note-off events are not triggered: this should be fixed
// - If only one cell, should make sure that we use monoMode 0...
// NOTEs
// - The default mode in any case is that if current finger goes away the note is not transfered to another finger on the keyboard: this might have to be fixed
// - For monoMode, slides between keyboards don't get priority over a finger already on the keyboard in any case
// - Later, glissandi should be handled using pitch bend directly from poly-dsp, but we can take care of that later

#import "MultiKeyboard.h"

#define kMotionUpdateRate 30
#define ONE_G 9.81

// TODO, may be should be in the general preferences dictionnary
#define ROUNDING_UPDATE_SPEED 0.06 // speed in ms at which the rounding loop is updated
#define ROUNDING_THRESHOLD_RANGE 0.01

@implementation MultiKeyboard{
    NSMutableArray *zones; // the "keys" of the keyboard matrix (2D)
    CGFloat *zoneWidths; // the width of the different zones of each keyboards
    CGFloat zoneHeight; // the global height of each keyboard (same for all of them)
    Boolean UIon;
    Boolean cancelOnce;
    
    float currentContinuousKey;
    float currentKeyboardY;
    CGPoint *previousTouchPoints; // previous touch points for each finger
    // delayed previous touch points for each finger
    // NOTE: we think that this is necessary to properly dealocate touches when touchesEnded is called. This might have to be checked but it works very well for now.
    CGPoint *previousTouchPoints_;
    int *previousTouchedKeys; // the last key touched by a specific finger on the screen
    int *previousTouchedKeyboards; // the last keyboard touched by a specific finger on the screen
    int *fingersOnKeyboardsCount; // number of fingers present on each keyboard (used to limit polyphony)
    int *monoMode_previousActiveFinger; // last active finger in mono mode (in case touch needs to canceled)
    
    float *rawPitch; // TODO: only used for pitch rounding: may should be propagated
    float *previousRawPitch;
    float *roundedPitch; // the output of pitch rounding
    int *moveCount; // for pitch rounding
    
    MapUI **polyUI;
    mydsp_poly* faustDsp;
    APIUI fAPIUI;
}

- (id)initWithFrame:(CGRect)frame withPolyDSP:(mydsp_poly*)dsp{
    self = [super initWithFrame:frame];
    if(self){
        faustDsp = dsp;
        self.multipleTouchEnabled = YES;
        [self setBackgroundColor:[UIColor blackColor]];
        
        // setting default parameters
        /*
         With parameters:
            - monoMode: available only if maxKeyboardPoly = 1
                * 0[default]: First finger keeps priority in any case: any new finger is ignored.
                * 1: Priority goes to last finger: previous fingers are canceled.
                * 2: Priority goes to highest pitch. (TODO)
                * 3: Priority goes to lowest pitch. (TODO)
            - quantizationMode:
                * 0[default]: quantized
                * 1: slide
                * 2: rounded
         */
         
        // TODO: parameters should organized
        parameters = [NSMutableDictionary dictionaryWithDictionary:@{
                                                                     @"nKeyb":[NSNumber numberWithInt:4],
                                                                     @"maxFingers":[NSNumber numberWithInt:10],
                                                                     @"maxKeybPoly":[NSNumber numberWithInt:10],
                                                                     @"monoMode":[NSNumber numberWithInt:1],
                                                                     @"quantizationMode":[NSNumber numberWithInt:2],
                                                                     @"interKeybSlideAllowed":[NSNumber numberWithInt:1],
                                                                     @"arpegiatorOn":[NSNumber numberWithInt:0], // TODO
                                                                     @"keyb0_nKeys":[NSNumber numberWithInt:13],
                                                                     @"keyb1_nKeys":[NSNumber numberWithInt:13],
                                                                     @"keyb2_nKeys":[NSNumber numberWithInt:13],
                                                                     @"keyb3_nKeys":[NSNumber numberWithInt:13],
                                                                     @"keyb0_lowestKey":[NSNumber numberWithInt:48],
                                                                     @"keyb1_lowestKey":[NSNumber numberWithInt:60],
                                                                     @"keyb2_lowestKey":[NSNumber numberWithInt:72],
                                                                     @"keyb3_lowestKey":[NSNumber numberWithInt:84],
                                                                     @"keyb0_scale":[NSNumber numberWithInt:0],
                                                                     @"keyb1_scale":[NSNumber numberWithInt:0],
                                                                     @"keyb2_scale":[NSNumber numberWithInt:0],
                                                                     @"keyb3_scale":[NSNumber numberWithInt:0],
                                                                     @"keyb0_rootPos":[NSNumber numberWithInt:0],
                                                                     @"keyb1_rootPos":[NSNumber numberWithInt:0],
                                                                     @"keyb2_rootPos":[NSNumber numberWithInt:0],
                                                                     @"keyb3_rootPos":[NSNumber numberWithInt:0],
                                                                     @"keyb0_orientation":[NSNumber numberWithInt:0],
                                                                     @"keyb1_orientation":[NSNumber numberWithInt:0],
                                                                     @"keyb2_orientation":[NSNumber numberWithInt:0],
                                                                     @"keyb3_orientation":[NSNumber numberWithInt:0],
                                                                     @"keyb0_keybMode":[NSNumber numberWithInt:1],
                                                                     @"keyb1_keybMode":[NSNumber numberWithInt:1],
                                                                     @"keyb2_keybMode":[NSNumber numberWithInt:1],
                                                                     @"keyb3_keybMode":[NSNumber numberWithInt:1]
                                                                     }];
        
        // TODO all the stuff below might have to be moved to buildInterface
        
        faustDsp->buildUserInterface(&fAPIUI); // for accelerometers
        
        JSONUI jsonUI(faustDsp->getNumInputs(),faustDsp->getNumOutputs());
        faustDsp->metadata(&jsonUI);
        
        NSString *JSONInterface = [NSString stringWithUTF8String:jsonUI.JSON().c_str()];
        // isolating the parameters of SmartKeyboard from the JSON description and checking if the key exist
        NSRange r1 = [JSONInterface rangeOfString:@"SmartKeyboard{"];
        
        if(r1.length>0){
            NSRange r2 = [[JSONInterface substringFromIndex:r1.location] rangeOfString:@"}"];
            NSRange rSub = NSMakeRange(r1.location + r1.length-1, r2.location-r1.length+2);
            NSString *JSONSmartKeyboard = [[JSONInterface substringWithRange:rSub] stringByReplacingOccurrencesOfString:@"'" withString:@"\""];
            
            NSError *error;
            NSDictionary *userParameters = [NSJSONSerialization JSONObjectWithData:[JSONSmartKeyboard dataUsingEncoding:NSUTF8StringEncoding] options:0 error:&error];
        
        
            // updating default parameters with user defined parameters
            if(error == nil){
                for(int i=0; i<[userParameters count]; i++){
                    parameters[[userParameters allKeys][i]] = [NSNumber numberWithInt:[[userParameters valueForKey:[userParameters allKeys][i]] intValue]];
                }
            }
            else{
                printf("Error in the JSON interface descriptiom\n");
            
            }
        }
        
        [self buildInterface];
        [self startMotion]; // TODO, may be only get accel data when needed (voice is on)
        
        if([parameters[@"quantizationMode"] intValue] == 2){
            [NSThread detachNewThreadSelector:@selector(pitchRounding) toTarget:self withObject:nil];
        }
        cancelOnce = true;
    }
    return self;
}

// builds the user interface, can be called multiple times
- (void)buildInterface{
    // dealocate previous instances first
    [self clean];
    UIon = true;
    
    // allocate memory and initialize the different elements
    previousTouchPoints = new CGPoint [[parameters[@"maxFingers"] intValue]];
    previousTouchPoints_ = new CGPoint [[parameters[@"maxFingers"] intValue]];
    previousTouchedKeys = new int[[parameters[@"maxFingers"] intValue]];
    previousTouchedKeyboards = new int[[parameters[@"maxFingers"] intValue]];
    rawPitch = new float[[parameters[@"maxFingers"] intValue]];
    previousRawPitch = new float[[parameters[@"maxFingers"] intValue]];
    roundedPitch = new float[[parameters[@"maxFingers"] intValue]];
    moveCount = new int[[parameters[@"maxFingers"] intValue]];
    for(int i=0; i<[parameters[@"maxFingers"] intValue]; i++){
        previousTouchPoints[i].x = -1;
        previousTouchPoints[i].y = -1;
        previousTouchPoints_[i].x = -1;
        previousTouchPoints_[i].y = -1;
        previousTouchedKeys[i] = -1;
        previousTouchedKeyboards[i] = -1;
        rawPitch[i] = -1;
        previousRawPitch[i] = -1;
        roundedPitch[i] = -1;
        moveCount[i] = 0;
    }
    polyUI = new MapUI*[[parameters[@"maxFingers"] intValue]];
    
    zoneWidths = new CGFloat [[parameters[@"nKeyb"] intValue]];
    fingersOnKeyboardsCount = new int [[parameters[@"nKeyb"] intValue]];
    monoMode_previousActiveFinger = new int [[parameters[@"nKeyb"] intValue]];
    
    // dimension of the zones, zones cover the entire view
    zoneHeight = (self.frame.size.height)/[parameters[@"nKeyb"] intValue];
    
    // initializing the different keyboards
    zones = [[NSMutableArray alloc] init];
    for(int i=0; i<[parameters[@"nKeyb"] intValue]; i++){
        // default for new keys
        if([parameters[[NSString stringWithFormat:@"keyb%d_nKeys",i]] intValue] == 0){
            parameters[[NSString stringWithFormat:@"keyb%d_nKeys",i]] = [NSNumber numberWithInt:7];
        }
        if(parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",i]] == 0){
            parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",i]] = [NSNumber numberWithInt:60];
        }
        if(parameters[[NSString stringWithFormat:@"keyb%d_scale",i]] == 0){
            parameters[[NSString stringWithFormat:@"keyb%d_scale",i]] = [NSNumber numberWithInt:0];
        }
        if(parameters[[NSString stringWithFormat:@"keyb%d_rootPos",i]] == 0){
            parameters[[NSString stringWithFormat:@"keyb%d_rootPos",i]] = [NSNumber numberWithInt:0];
        }
        if(parameters[[NSString stringWithFormat:@"keyb%d_orientation",i]] == 0){
            parameters[[NSString stringWithFormat:@"keyb%d_orientation",i]] = [NSNumber numberWithInt:0];
        }
        if(parameters[[NSString stringWithFormat:@"keyb%d_keybMode",i]] == 0){
            parameters[[NSString stringWithFormat:@"keyb%d_keybMode",i]] = [NSNumber numberWithInt:1];
        }
        
        // initializing the zones (keys) of the different keyboards
        [zones insertObject:[[NSMutableArray alloc] init] atIndex:i];
        zoneWidths[i] = self.frame.size.width/[parameters[[NSString stringWithFormat:@"keyb%d_nKeys",i]] intValue];
        fingersOnKeyboardsCount[i] = 0;
        monoMode_previousActiveFinger[i] = -1;
        for(int j=0;j<[parameters[[NSString stringWithFormat:@"keyb%d_nKeys",i]] intValue];j++){
            // Zones have 1 pt on each side but touch detection happens on the entire screen. With this strategy we lose 1 pt on the 2 extermities of the interface but it makes things much easier
            [[zones objectAtIndex:i] insertObject:[[Zone alloc] initWithFrame:CGRectMake(zoneWidths[i]*j+1, zoneHeight*i+1, zoneWidths[i]-2, zoneHeight-2)] atIndex:j];
            [[[zones objectAtIndex:i] objectAtIndex:j] setImageOn:[UIImage imageNamed:@"keyDown.png"]];
            [[[zones objectAtIndex:i] objectAtIndex:j] setImageOff:[UIImage imageNamed:@"keyUp.png"]];
            if([parameters[[NSString stringWithFormat:@"keyb%d_keybMode",i]] boolValue]){
                if([parameters[[NSString stringWithFormat:@"keyb%d_orientation",i]] boolValue]){
                    [[[zones objectAtIndex:i] objectAtIndex:j] setNote:[self applyScale:[parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",i]] intValue]+[parameters[[NSString stringWithFormat:@"keyb%d_nKeys",i]] intValue]-j-1]];
                }
                else{
                    [[[zones objectAtIndex:i] objectAtIndex:j] setNote:[self applyScale:j+[parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",i]] intValue]]];
                }
            }
            [[[zones objectAtIndex:i] objectAtIndex:j] setKeyboardMode:[parameters[[NSString stringWithFormat:@"keyb%d_keybMode",i]] boolValue]];
            [self addSubview:[[zones objectAtIndex:i] objectAtIndex:j]];
        }
    }
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    cancelOnce = true;
    /*
    parameters[@"keyb0_nKeys"] = [NSNumber numberWithInt:8];
    [self buildInterface];
    */
    if ([touches count] > 0) {
        for (UITouch *touch in touches) {
            CGPoint touchPoint = [touch locationInView:self];
            for(int i=0; i<[parameters[@"maxFingers"] intValue]; i++){
                // we look for the first available "touch tracker"
                if(previousTouchPoints[i].x == -1){
                    [self processTouchEvent:1 withTouchPoint:touchPoint withFingerId:i];
                     
                    // updating finger tracking
                    previousTouchPoints[i] = [touch locationInView: self];
                    break;
                }
            }
        }
    }
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    if ([touches count] > 0) {
        for (UITouch *touch in touches) {
            CGPoint systemPreviousTouchPoint = [touch previousLocationInView: self];
            CGPoint touchPoint = [touch locationInView:self];
            for(int i=0; i<[parameters[@"maxFingers"] intValue]; i++){
                if(previousTouchPoints[i].x == systemPreviousTouchPoint.x && previousTouchPoints[i].y == systemPreviousTouchPoint.y){
                    
                    [self processTouchEvent:2 withTouchPoint:touchPoint withFingerId:i];
                    
                    // updating the finger tracking system
                    previousTouchPoints_[i] = previousTouchPoints[i];
                    previousTouchPoints[i] = [touch locationInView: self];
                    break;
                }
            }
        }
    }
}

-(void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    if ([touches count] > 0) {
        for (UITouch *touch in touches) {
            CGPoint systemPreviousTouchPoint = [touch previousLocationInView: self];
            CGPoint touchPoint = [touch locationInView:self];
            for(int i=0; i<[parameters[@"maxFingers"] intValue]; i++){
                if((previousTouchPoints[i].x == systemPreviousTouchPoint.x && previousTouchPoints[i].y == systemPreviousTouchPoint.y) || (previousTouchPoints_[i].x == systemPreviousTouchPoint.x && previousTouchPoints_[i].y == systemPreviousTouchPoint.y)){
                    
                    [self processTouchEvent:0 withTouchPoint:touchPoint withFingerId:i];
                    
                    // updating the finger tracking system
                    previousTouchPoints[i].x = -1;
                    previousTouchPoints[i].y = -1;
                    break;
                }
            }
        }
    }
}

-(void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    if(cancelOnce){
        [self resetKeyboard];
        cancelOnce = false;
    }
}

-(void)processTouchEvent:(int)eventType withTouchPoint:(CGPoint)touchPoint withFingerId:(int)fingerId{
    // we calculate the position of the touch on the keyboards matrix
    int currentKeyboard = fmin(int(touchPoint.y/zoneHeight),([parameters[@"nKeyb"] intValue]-1));
    currentContinuousKey = touchPoint.x/zoneWidths[currentKeyboard];
    currentKeyboardY = fmod(touchPoint.y/zoneHeight,1);
    int currentKeyIdInRow = fmin(int(currentContinuousKey),([parameters[[NSString stringWithFormat:@"keyb%d_nKeys",currentKeyboard]] intValue]-1));
    
    // we make sure that the touch happened inside the keyboards matrix area
    if(currentKeyboard >= 0){
        
        // first we track fingers in the different keyboards (this is necessary to control the number of voices of polyphony of each keybaords)
        // if touch up
        if(eventType == 0){
            // counting fingers on the keyboard...
            fingersOnKeyboardsCount[currentKeyboard] = fmax(0,fingersOnKeyboardsCount[currentKeyboard]-1);
        }
        // if touch down
        else if(eventType == 1){
            // counting fingers on the keyboard...
            fingersOnKeyboardsCount[currentKeyboard]++;
        }
        // if move
        else if(eventType == 2 && currentKeyboard != previousTouchedKeyboards[fingerId]){
            // counting fingers on the keyboard...
            fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]] = fmax(0,fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]]-1);
            fingersOnKeyboardsCount[currentKeyboard]++;
        }
        
        // deffault mode if poly keyboards
        if([parameters[@"monoMode"] intValue] == 0 || [parameters[@"maxKeybPoly"] intValue]>1){
            // if touch up
            if(eventType == 0){
                // cancel corresponding previous key (in case of fast move event)
                if(previousTouchedKeyboards[fingerId] != currentKeyboard || previousTouchedKeys[fingerId] != currentKeyIdInRow){
                    [self sendKeyboardAction:0 withKeyboardId:previousTouchedKeyboards[fingerId] withKeyId:previousTouchedKeys[fingerId] withFingerId:fingerId];
                }
                // cancel corresponding key
                [self sendKeyboardAction:0 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                currentKeyboard = -1;
                currentKeyIdInRow = -1;
            }
            // if touch down
            else if(eventType == 1 && fingersOnKeyboardsCount[currentKeyboard]<=[parameters[@"maxKeybPoly"] intValue]){
                [self sendKeyboardAction:1 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
            }
            // if move
            else if(eventType == 2){
                // moved to another keyboard
                if(currentKeyboard != previousTouchedKeyboards[fingerId]){
                    // cancel key in previous keyboard
                    [self sendKeyboardAction:3 withKeyboardId:previousTouchedKeyboards[fingerId] withKeyId:previousTouchedKeys[fingerId] withFingerId:fingerId];
                    // initiate new event only if there are keys available
                    if(fingersOnKeyboardsCount[currentKeyboard]<=[parameters[@"maxKeybPoly"] intValue] && [parameters[@"interKeybSlideAllowed"] boolValue]){
                        [self sendKeyboardAction:4 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                    }
                }
                // moved to another key within the same keyboard
                else if(currentKeyIdInRow != previousTouchedKeys[fingerId] && [[[zones objectAtIndex:previousTouchedKeyboards[fingerId]] objectAtIndex:previousTouchedKeys[fingerId]] getStatus] == 1){
                    // cancel previous key
                    [self sendKeyboardAction:3 withKeyboardId:previousTouchedKeyboards[fingerId] withKeyId:previousTouchedKeys[fingerId] withFingerId:fingerId];
                    // inititate new event
                    [self sendKeyboardAction:4 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                }
                // move within the same key
                else{
                    [self sendKeyboardAction:2 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                }
            }
        }
        
        else if([parameters[@"monoMode"] intValue] == 1){
            // TODO: check if this is the right place for it
            int currentKeyDown = -1;
            for(int i=0; i<[parameters[[NSString stringWithFormat:@"keyb%d_nKeys",currentKeyboard]] intValue]; i++){
                if([[[zones objectAtIndex:currentKeyboard] objectAtIndex:i] getStatus] == 1){
                    currentKeyDown = i;
                }
            }
            
            // if touch up
            if(eventType == 0){
                // cancel corresponding previous key (in case of fast move event)
                if(previousTouchedKeyboards[fingerId] != currentKeyboard || previousTouchedKeys[fingerId] != currentKeyIdInRow){
                    [self sendKeyboardAction:0 withKeyboardId:previousTouchedKeyboards[fingerId] withKeyId:previousTouchedKeys[fingerId] withFingerId:fingerId];
                }
                // cancel corresponding key
                [self sendKeyboardAction:0 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                currentKeyboard = -1;
                currentKeyIdInRow = -1;
            }
            // if touch down
            else if(eventType == 1){
                if(currentKeyDown>=0){
                    [self sendKeyboardAction:0 withKeyboardId:currentKeyboard withKeyId:currentKeyDown withFingerId:monoMode_previousActiveFinger[currentKeyboard]];
                }
                [self sendKeyboardAction:1 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                monoMode_previousActiveFinger[currentKeyboard] = fingerId;
            }
            // if move
            else if(eventType == 2){
                // moved to another keyboard
                if(currentKeyboard != previousTouchedKeyboards[fingerId]){
                    // cancel key in previous keyboard
                    [self sendKeyboardAction:0 withKeyboardId:previousTouchedKeyboards[fingerId] withKeyId:previousTouchedKeys[fingerId] withFingerId:fingerId];
                    // initiate new event only if there are keys available
                    if(fingersOnKeyboardsCount[currentKeyboard]<=[parameters[@"maxKeybPoly"] intValue] && [parameters[@"interKeybSlideAllowed"] boolValue]){
                        [self sendKeyboardAction:1 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                    }
                }
                // moved to another key within the same keyboard
                else if(currentKeyIdInRow != previousTouchedKeys[fingerId] && [[[zones objectAtIndex:previousTouchedKeyboards[fingerId]] objectAtIndex:previousTouchedKeys[fingerId]] getStatus] == 1){
                    // cancel previous key
                    [self sendKeyboardAction:3 withKeyboardId:previousTouchedKeyboards[fingerId] withKeyId:previousTouchedKeys[fingerId] withFingerId:fingerId];
                    // inititate new event
                    [self sendKeyboardAction:4 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                }
                // move within the same key
                else{
                    [self sendKeyboardAction:2 withKeyboardId:currentKeyboard withKeyId:currentKeyIdInRow withFingerId:fingerId];
                }
            }
        }
        
        // updating previous data for comparison
        previousTouchedKeyboards[fingerId] = currentKeyboard;
        previousTouchedKeys[fingerId] = currentKeyIdInRow;
    }
    // if touch is outside the keyboards matrix area
    else if(eventType == 2){
        [[[zones objectAtIndex:previousTouchedKeyboards[fingerId]] objectAtIndex:previousTouchedKeys[fingerId]] setStatus:0];
        fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]] = fmax(0,fingersOnKeyboardsCount[previousTouchedKeyboards[fingerId]]-1);
    }
}

-(void)sendKeyboardAction:(int)eventType withKeyboardId:(int)keyboardId withKeyId:(int)keyId withFingerId:(int)fingerId{
    // key up
    if(eventType == 0 || eventType == 3){
        // make sure that the corresponding key is active
        if([[[zones objectAtIndex:keyboardId] objectAtIndex:keyId] getStatus] == 1){
            // check if another finger is present in the zone
            bool otherFingerInKey = false;
            if([parameters[@"monoMode"] intValue] == 0 || [parameters[@"maxKeybPoly"] intValue]>1){
                for(int i=0; i<[parameters[@"maxFingers"] intValue]; i++){
                    if(keyboardId == previousTouchedKeyboards[i] && keyId == previousTouchedKeys[i] && i != fingerId){
                        otherFingerInKey = true;
                        break;
                    };
                }
            }
            // key physically up only if there are no more fingers in the zone
            if(!otherFingerInKey){
                [[[zones objectAtIndex:keyboardId] objectAtIndex:keyId] setStatus:0];
            }
            [self sendSynthControlAction:eventType withKeyboardId:keyboardId withKeyId:keyId withFingerId:fingerId];
        }
    }
    // key down
    else if(eventType == 1 || eventType == 4){
        [[[zones objectAtIndex:keyboardId] objectAtIndex:keyId] setStatus:1];
        [self sendSynthControlAction:eventType withKeyboardId:keyboardId withKeyId:keyId withFingerId:fingerId];
    }
    // move within the same key
    else if(eventType == 2){
        [self sendSynthControlAction:2 withKeyboardId:keyboardId withKeyId:keyId withFingerId:fingerId];
    }
}

-(void)sendSynthControlAction:(int)eventType withKeyboardId:(int)keyboardId withKeyId:(int)keyId withFingerId:(int)fingerId{
    // delete (note off)
    if((eventType == 0 || (eventType == 3 && [parameters[@"quantizationMode"] intValue] == 0)) && polyUI[fingerId] != NULL){
        rawPitch[fingerId] = -1;
        polyUI[fingerId]->setParamValue("gate", 0);
        faustDsp->deleteVoice(polyUI[fingerId]);
    }
    // new (note on)
    else if (eventType == 1 || (eventType == 4 && [parameters[@"quantizationMode"] intValue] == 0)){
        // allocating new voice to finger
        polyUI[fingerId] = faustDsp->newVoice();
        if(polyUI[fingerId] != NULL){
            polyUI[fingerId]->setParamValue("gate", 1);
        }
        else{
            return;
        }
        
        // setting first pitch (always quantized)
        if([parameters[@"quantizationMode"] intValue] == 0){
            // inverted keyboard
            if([parameters[[NSString stringWithFormat:@"keyb%d_orientation",keyboardId]] boolValue]){
                rawPitch[fingerId] = [self applyScale:[parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",keyboardId]] intValue]+[parameters[[NSString stringWithFormat:@"keyb%d_nKeys",keyboardId]] intValue]-keyId-1];
            }
            // regular keyboard
            else{
                rawPitch[fingerId] = [self applyScale:[parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",keyboardId]] intValue]+keyId];
            }
        }
        else if([parameters[@"quantizationMode"] intValue] == 1 || [parameters[@"quantizationMode"] intValue] == 2){
            // inverted keyboard
            if([parameters[[NSString stringWithFormat:@"keyb%d_orientation",keyboardId]] boolValue]){
                rawPitch[fingerId] = [self applyScale:[parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",keyboardId]] intValue]+[parameters[[NSString stringWithFormat:@"keyb%d_nKeys",keyboardId]] intValue]-currentContinuousKey];
            }
            // regular keyboard
            else{
                rawPitch[fingerId] = [self applyScale:currentContinuousKey+[parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",keyboardId]] intValue]];
            }
        }
        if(polyUI[fingerId] != NULL) polyUI[fingerId]->setParamValue("freq", [self mtof:rawPitch[fingerId]]);
        previousRawPitch[fingerId] = rawPitch[fingerId];
    }
    // update
    else if(eventType == 2 && ([parameters[@"quantizationMode"] intValue] == 1 || [parameters[@"quantizationMode"] intValue] == 2)){
        previousRawPitch[fingerId] = rawPitch[fingerId];
        if([parameters[[NSString stringWithFormat:@"keyb%d_orientation",keyboardId]] boolValue]){
            rawPitch[fingerId] = [self applyScale:[parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",keyboardId]] intValue]+[parameters[[NSString stringWithFormat:@"keyb%d_nKeys",keyboardId]] intValue]-currentContinuousKey];
        }
        // regular keyboard
        else{
            rawPitch[fingerId] = [self applyScale:currentContinuousKey+[parameters[[NSString stringWithFormat:@"keyb%d_lowestKey",keyboardId]] intValue]];
        }
        
        if([parameters[@"quantizationMode"] intValue] == 1){
            if(polyUI[fingerId] != NULL) polyUI[fingerId]->setParamValue("freq", [self mtof:rawPitch[fingerId]]);
        }
        // else sent from the pitch rounding method/thread...
    }
    
    // TODO: continuous x and y values are always sent: this should be optimized
    if(polyUI[fingerId] != NULL) polyUI[fingerId]->setParamValue("keyboard", keyboardId);
    if(polyUI[fingerId] != NULL) polyUI[fingerId]->setParamValue("key", keyId);
    if(polyUI[fingerId] != NULL) polyUI[fingerId]->setParamValue("x", fmod(currentContinuousKey,1));
    if(polyUI[fingerId] != NULL) polyUI[fingerId]->setParamValue("y", currentKeyboardY);
}

// TODO: improve
-(float)applyScale:(float)pitch{
    return pitch;
}

-(float)mtof:(float)note{
    return 440.0 * pow(2.0, (note-69.0)/12.0);
}

-(void)resetKeyboard{
    for(int i=0; i<[parameters[@"nKeyb"] intValue]; i++){
        for(int j=0;j<[parameters[[NSString stringWithFormat:@"keyb%d_nKeys",i]] intValue];j++){
            [[[zones objectAtIndex:i] objectAtIndex:j] setStatus:0];
        }
    }
    for(int i=0; i<[parameters[@"maxFingers"] intValue]; i++){
        if(polyUI[i] != NULL){
            polyUI[i]->setParamValue("gate", 0);
            faustDsp->deleteVoice(polyUI[i]);
        }
        previousTouchPoints[i].x = -1;
        previousTouchPoints[i].y = -1;
        previousTouchPoints_[i].x = -1;
        previousTouchPoints_[i].y = -1;
        previousTouchedKeys[i] = -1;
        previousTouchedKeyboards[i] = -1;
        rawPitch[i] = -1;
        previousRawPitch[i] = -1;
        roundedPitch[i] = -1;
        moveCount[i] = 0;
    }
}

- (void)startMotion
{
    // Motion
    if (_motionManager == nil)
    {
        _motionManager = [[CMMotionManager alloc] init];
        [_motionManager startAccelerometerUpdates];
        [_motionManager startGyroUpdates];
    }
    _motionTimer = [NSTimer scheduledTimerWithTimeInterval:1./kMotionUpdateRate
                                                    target:self
                                                  selector:@selector(updateMotion)
                                                  userInfo:nil
                                                   repeats:YES];
}

// Stop updating sensors
- (void)stopMotion
{
    // Motion
    if (_motionManager != nil)
    {
        [_motionManager stopAccelerometerUpdates];
        [_motionManager stopGyroUpdates];
        //[_motionManager release];
        _motionManager = nil;
        [_motionTimer invalidate];
    }
}

- (void)updateMotion
{
    fAPIUI.propagateAcc(0, _motionManager.accelerometerData.acceleration.x * ONE_G);
    fAPIUI.propagateAcc(1, _motionManager.accelerometerData.acceleration.y * ONE_G);
    fAPIUI.propagateAcc(2, _motionManager.accelerometerData.acceleration.z * ONE_G);
    
    fAPIUI.propagateGyr(0, _motionManager.gyroData.rotationRate.x);
    fAPIUI.propagateGyr(1, _motionManager.gyroData.rotationRate.y);
    fAPIUI.propagateGyr(2, _motionManager.gyroData.rotationRate.z);
}

- (void) pitchRounding{
    while(UIon){
        for(int i=0; i<[parameters[@"maxFingers"] intValue]; i++){
            if(rawPitch[i] != -1){
                if(abs(rawPitch[i]-previousRawPitch[i]) >= ROUNDING_THRESHOLD_RANGE){
                    moveCount[i]++;
                }
                else{
                    moveCount[i] = 0;
                }
                if(moveCount[i]++ > 9){
                    roundedPitch[i] = rawPitch[i]-0.5;
                }
                else{
                    roundedPitch[i] = (int)rawPitch[i];
                }
                if(polyUI[i] != NULL) polyUI[i]->setParamValue("freq", [self mtof:roundedPitch[i]]);
            }
        }
        [NSThread sleepForTimeInterval:ROUNDING_UPDATE_SPEED];
    }
}

-(void)clean{
    UIon = false;
    if([zones count] > 0){
        for(int i=0; i<[zones count]; i++){
            for(int j=0;j<[[zones objectAtIndex:i] count];j++){
                [[[zones objectAtIndex:i] objectAtIndex:j] removeFromSuperview] ;
            }
        }
        [zones removeAllObjects];
    }
    if(previousTouchPoints){
        delete[] previousTouchPoints;
        previousTouchPoints = NULL;
    }
    if(previousTouchPoints_){
        delete[] previousTouchPoints_;
        previousTouchPoints_ = NULL;
    }
    if(previousTouchedKeyboards){
        delete[] previousTouchedKeyboards;
        previousTouchedKeyboards = NULL;
    }
    if(previousTouchedKeys){
        delete[] previousTouchedKeys;
        previousTouchedKeys = NULL;
    }
    if(zoneWidths){
        delete[] zoneWidths;
        zoneWidths = NULL;
    }
    if(monoMode_previousActiveFinger){
        delete[] monoMode_previousActiveFinger;
        monoMode_previousActiveFinger = NULL;
    }
    if(rawPitch){
        delete[] rawPitch;
        rawPitch = NULL;
    }
    if(previousRawPitch){
        delete[] previousRawPitch;
        previousRawPitch = NULL;
    }
    if(roundedPitch){
        delete[] roundedPitch;
        roundedPitch = NULL;
    }
    if(moveCount){
        delete[] moveCount;
        moveCount = NULL;
    }
    if(polyUI){
        delete[] polyUI;
        polyUI = NULL;
    }
}

// TODO: for now, we assume that memory is deallocated here but we're not 100% sure about that: this has to be checked
-(void)dealloc{
    [self clean];
    [self stopMotion];
}

@end
