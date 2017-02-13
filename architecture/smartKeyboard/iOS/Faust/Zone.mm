//
//  Zone.m
//  MultiXYTest
//
//  Created by Romain Michon on 4/15/16.
//  Copyright © 2016 CCRMA. All rights reserved.
//
//  This class override a simple UIView to display different states (on/off/move).
//  It can be used as the dynamic background of a controller.
//

#import "Zone.h"

@implementation Zone{
    UILabel *text;
    UIView *layerOn;
    NSArray *notes;
    UIImage *darkImageOn, *darkImageOff, *brightImageOn, *brightImageOff;
    int keyNote;
}

- (id)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if(self){
        self.multipleTouchEnabled = YES; // that's fucked up!
        
		// setting defaults
		notes = @[@"C",@"C#",@"D",@"Eb",@"E",@"F",@"F#",@"G",@"G#",@"A",@"Bb",@"B"];
        status = 0;
        staticMode = true;
        keyNote = 0;
        darkImageOn = [UIImage imageNamed:@"keyDownDark.png"];
        darkImageOff = [UIImage imageNamed:@"keyUpDark.png"];
        brightImageOn = [UIImage imageNamed:@"keyDownBright.png"];
        brightImageOff = [UIImage imageNamed:@"keyUpBright.png"];
		[self setBackgroundColor:[UIColor blackColor]];
        
        // Status "on" layer
        layerOn = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, self.frame.size.width, self.frame.size.height)];
        // Default "on" color is white
        layerOn.multipleTouchEnabled = YES; // that's fucked up too!
        [layerOn setBackgroundColor:[UIColor whiteColor]];
        [layerOn setHidden:true];
        [self addSubview:layerOn];
        
        // Button label placed at the center of the button
        text = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
        text.textAlignment = NSTextAlignmentCenter;
        text.font = [UIFont systemFontOfSize:32];
        [self addSubview:text];
    }
    return self;
}

- (void)setText:(NSString*)label{
    [text setText:label];
}

- (void)setTextSize:(CGFloat)size{
    text.font = [UIFont systemFontOfSize:size];
}

- (void)setNote:(int)note{
    keyNote = note%12;
    [self setText:[notes objectAtIndex:keyNote]];
}

- (void)drawBackground{
    if(keyNote == 1 || keyNote == 3 || keyNote == 6 || keyNote == 8 || keyNote == 10){
        UIGraphicsBeginImageContext(self.frame.size);
        [darkImageOn drawInRect:self.bounds];
        UIImage *picOn = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
        layerOn.backgroundColor = [UIColor colorWithPatternImage:picOn];
        
        UIGraphicsBeginImageContext(self.frame.size);
        [darkImageOff drawInRect:self.bounds];
        UIImage *picOff = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
        self.backgroundColor = [UIColor colorWithPatternImage:picOff];
    }
    else{
        UIGraphicsBeginImageContext(self.frame.size);
        [brightImageOn drawInRect:self.bounds];
        UIImage *picOn = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
        layerOn.backgroundColor = [UIColor colorWithPatternImage:picOn];
        
        UIGraphicsBeginImageContext(self.frame.size);
        [brightImageOff drawInRect:self.bounds];
        UIImage *picOff = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
        self.backgroundColor = [UIColor colorWithPatternImage:picOff];
    }
}

- (void)setStatus:(int)s{
    status = s;
    if(!staticMode){
        if(status == 1){
            [layerOn setHidden:false];
        }
        else{
            [layerOn setHidden:true];
        }
    }
}

- (void)showLabels:(bool)show{
    if(show){
        [text setHidden:false];
    }
    else{
        [text setHidden:true];
    }
}

- (void)setStaticMode:(bool)mode{
    staticMode = mode;
}

- (int)getStatus{
    return status;
}

@end
