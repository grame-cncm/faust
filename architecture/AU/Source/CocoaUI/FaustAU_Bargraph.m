#import "FaustAU_Bargraph.h"

@implementation FaustAU_Bargraph

@synthesize labelTextField =_labelTextField;
@synthesize valueTextField =_valueTextField;


- (FaustAU_Bargraph*)init :(NSRect)frame :(auBargraph*)fBargraph :(int)controlId {
    return self;
}

- (void)setDoubleValue:(double)aDouble
{
    [super setDoubleValue: aDouble];
    NSString *stringValue = [NSString stringWithFormat:@"%9.2f", aDouble];
    [_valueTextField setStringValue:stringValue];
}

@end

