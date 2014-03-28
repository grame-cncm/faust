#import <Foundation/Foundation.h>

#include "FaustAU.h"

@interface FaustAU_Slider : NSSlider
{
    NSTextField* _labelTextField;
    NSTextField* _valueTextField;
}

- (FaustAU_Slider*)init :(NSRect) frame :(auSlider*)fButton :(int)controlId;

@property (nonatomic, strong) NSTextField* labelTextField;
@property (nonatomic, strong) NSTextField* valueTextField;

- (void)setDoubleValue:(double)aDouble;

@end