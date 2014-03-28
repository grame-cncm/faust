#import "FaustAU_Slider.h"

@implementation FaustAU_Slider

@synthesize labelTextField =_labelTextField;
@synthesize valueTextField =_valueTextField;


- (FaustAU_Slider*)init :(NSRect)frame :(auSlider*)fSlider :(int)controlId {
    return self;
}

- (void)setDoubleValue:(double)aDouble
{
    [super setDoubleValue: aDouble];
    NSString *stringValue = [NSString stringWithFormat:@"%9.2f", aDouble];
    [_valueTextField setStringValue:stringValue];
}

@end

