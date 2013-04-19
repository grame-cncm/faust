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

#define kJackViewExtLRMargins 30
#define kJackViewExtTopBottomMargins 5
#define kJackViewIntMargins 5

#define kJackViewIconDimension 70
#define kJackViewIconMargins 5

@interface JackViewClient : NSObject

@property (assign, nonatomic) NSString* name;
@property (assign, nonatomic) UIImage* icon;
@property (assign, nonatomic) NSArray* ports;
@property (assign, nonatomic) UIImageView* audioInputButton;
@property (assign, nonatomic) UIImageView* audioOutputButton;
@property (assign, nonatomic) UIImageView* midiInputButton;
@property (assign, nonatomic) UIImageView* midiOutputButton;

@end


@interface JackView : UIView
{
    jack_client_t*          _jackClient;
    
    NSMutableArray*         _clients;
    NSString*               _currentClientName;
    
    UIScrollView*           _audioInputsScrollView;
    UIScrollView*           _audioOutputsScrollView;
    UIScrollView*           _midiInputsScrollView;
    UIScrollView*           _midiOutputsScrollView;
}

- (void)loadJackClient:(jack_client_t*)jackClient;

- (BOOL)doesClientExist:(NSString*)clientName;
- (JackViewClient*)clientWithName:(NSString*)clientName;

@end