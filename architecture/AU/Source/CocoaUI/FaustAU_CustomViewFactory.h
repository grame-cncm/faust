#import <Cocoa/Cocoa.h>
#import <AudioUnit/AUCocoaUIView.h>

@class FaustAU_CustomView;

@interface FaustAU_CustomViewFactory : NSObject <AUCocoaUIBase>
{
    IBOutlet FaustAU_CustomView *uiFreshlyLoadedView;	// This class is the File's Owner of the CocoaView 
}															// This data member needs to be the same class as the view class the factory will return

- (NSString *) description;	

@end