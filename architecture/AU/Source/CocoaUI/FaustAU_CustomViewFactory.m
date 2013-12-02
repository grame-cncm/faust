
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
    
	NSRect rect;
	rect.origin.x    = 0;
	rect.origin.y    = 0;
	rect.size.width  = 600;
	rect.size.height = 600;
	
    FaustAU_CustomView *view = [[FaustAU_CustomView alloc] initWithFrame: rect];
    
    [view setAU:inAU];
    
    return [view autorelease];
}


@end
