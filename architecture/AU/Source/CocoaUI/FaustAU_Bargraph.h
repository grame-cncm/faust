#import <Foundation/Foundation.h>

#include "FaustAU.h"

@interface FaustAU_Bargraph : NSSlider
{
    NSTextField* _labelTextField;
    NSTextField* _valueTextField;
}

- (FaustAU_Bargraph*)init :(NSRect) frame :(auBargraph*)fBargraph :(int)controlId;

@property (nonatomic, strong) NSTextField* labelTextField;
@property (nonatomic, strong) NSTextField* valueTextField;

- (void)setDoubleValue:(double)aDouble;

@end