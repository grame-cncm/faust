//
//  JackView.h
//  iOS
//
//  Created by Olivier Guillerminet on 02/04/13.
//
//


#import <UIKit/UIKit.h>
#import "jack/jack.h"
#import "jack/custom.h"


@interface JackView : UIView
{
    jack_client_t*          _jackClient;
    
    // Inputs
    UIScrollView*           _inputScrollView;
}

- (void)loadJackClient:(jack_client_t*)jackClient;

@end