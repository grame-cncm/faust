#import "FaustAU_CustomViewFactory.h"
#import "FaustAU_CustomView.h"

@implementation FaustAU_CustomViewFactory

- (unsigned) interfaceVersion {
	return 0;
}

// string description of the Cocoa UI
- (NSString *) description {
	return @"Grame: FaustAU";
}

- (NSView *)uiViewForAudioUnit:(AudioUnit)inAU withSize:(NSSize)inPreferredSize {
    FaustAU_CustomView *view = [[FaustAU_CustomView alloc] init];
    [view setAU:inAU];
    return [view autorelease];
}


@end
