//
//  Copyright Grame 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

@class iPhoneViewController;

@interface iPhoneAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    iPhoneViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet iPhoneViewController *viewController;

@end

