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


@class JackViewClient;
@class JackView;

@interface JackViewButton : UIControl
{
    UITapGestureRecognizer* _singleTapRecognizer;
    UITapGestureRecognizer* _doubleTapRecognizer;
}

@property (assign, nonatomic) JackViewClient* jackViewClient;
@property (assign, nonatomic) JackView* jackView;
@property (assign, nonatomic) int audioMidi;        // 0: undefined, 1: audio; 2: midi
@property (assign, nonatomic) int inputOutput;      // 0: undefined, 1: input, 2:

- (void)buttonClicked;
- (void)buttonDoubleClicked;

@end


@interface JackViewPort : NSObject

@property (assign, nonatomic) NSString* name;
@property (assign, nonatomic) int audioMidi;        // 0: undefined, 1: audio; 2: midi
@property (assign, nonatomic) int inputOutput;      // 0: undefined, 1: input, 2: output

@end



@interface JackViewClient : NSObject

@property (assign, nonatomic) NSString* name;
@property (assign, nonatomic) UIImage* icon;
@property (assign, readwrite) NSMutableArray* ports;
@property (assign, nonatomic) JackViewButton* audioInputButton;
@property (assign, nonatomic) JackViewButton* audioOutputButton;
@property (assign, nonatomic) JackViewButton* midiInputButton;
@property (assign, nonatomic) JackViewButton* midiOutputButton;

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
- (jack_client_t*)jackClient;

- (BOOL)doesClientExist:(NSString*)clientName;
- (JackViewClient*)clientWithName:(NSString*)clientName;

- (void)quicklyConnectApp:(BOOL)connectApp
                 toClient:(NSString*)clientName
              inputOutput:(int)inputOutput
                audioMidi:(int)audioMidi;

@end