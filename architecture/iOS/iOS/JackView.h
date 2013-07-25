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
#import "JackViewPortsView.h"


#define kJackViewExtHMargins 5
#define kJackViewExtTopVMargins 30
#define kJackViewExtBottomVMargins 5
#define kJackViewIntHMargins 10

#define kJackViewBottomMargin 20
#define kJackViewTitlesYOffset 3
#define kJackViewStrokeYOffset 16

#define kJackViewCurrentAppIconBottomMargin 30

#define kJackViewButtonWidth 70
#define kJackViewButtonHeight 85
#define kJackViewIconMargins 4

#define kJackViewTabsX 5
#define kJackViewTabsY 1
#define kJackViewTabsWidth 150
#define kJackViewTabsHeight 28

@class JackViewClient;
@class JackView;

@interface JackViewButton : UIControl
{
    UITapGestureRecognizer*             _singleTapRecognizer;
    UITapGestureRecognizer*             _doubleTapRecognizer;
    UILongPressGestureRecognizer*       _longPressRecognizer;
}

@property (assign, nonatomic) JackViewClient* jackViewClient;
@property (assign, nonatomic) JackView* jackView;
@property (assign, nonatomic) int audioMidi;        // 0: undefined, 1: audio; 2: midi
@property (assign, nonatomic) int inputOutput;      // 0: undefined, 1: input, 2:

- (void)buttonClicked;
- (void)buttonDoubleClicked;
- (void)buttonLongPressed;

- (void)fastSwitch;
- (void)fastConnect;
- (void)displayPortsView;

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

- (NSArray*)compatiblePortsWithInputOutput:(int)inputOutput audioMidi:(int)audioMidi;

@end


@interface JackView : UIView <UIScrollViewDelegate>
{
    jack_client_t*          _jackClient;
    
    NSMutableArray*         _clients;
    NSString*               _currentClientName;
    
    UIScrollView*           _audioInputsScrollView;
    UIScrollView*           _audioOutputsScrollView;
    UIScrollView*           _midiInputsScrollView;
    UIScrollView*           _midiOutputsScrollView;
        
    UITapGestureRecognizer* _singleTapRecognizer;    
}

@property (assign, readwrite) CGPoint srcPt;
@property (assign, readwrite) CGPoint dstPt;
@property (assign, readwrite) JackViewPortsView* portsView;
@property (assign, readwrite) JackViewButton* currentClientButton;
@property (assign, readwrite) UIButton* audioButton;
@property (assign, readwrite) UIButton* midiButton;

- (void)orientationChanged:(NSNotification *)notification;
- (void)resizeView;
- (void)resizePortsView;

- (void)audioButtonClicked;
- (void)midiButtonClicked;

- (void)loadJackClient:(jack_client_t*)jackClient;
- (jack_client_t*)jackClient;

- (BOOL)doesClientExist:(NSString*)clientName;
- (JackViewClient*)clientWithName:(NSString*)clientName;
- (JackViewPort*)portWithName:(NSString*)portName;
- (void)makeButtonsSymetric;

- (BOOL)hasCurrentClientCompatiblePortWithInputOutput:(int)inputOutput audioMidi:(int)audioMidi;

- (BOOL)isClient:(JackViewClient*)client
connectedToCurrentClientInputOutput:(int)inputOutput
       audioMidi:(int)audioMidi;
- (BOOL)isPort:(JackViewPort*)port
connectedToCurrentClientInputOutput:(int)inputOutput
     audioMidi:(int)audioMidi;
- (BOOL)isPort:(NSString*)portName1
connectedWithPort:(NSString*)portName2;
- (NSArray*)getCurrentClientPortConnectedTo:(NSString*)portName;

- (BOOL)quicklyConnectAppToClient:(NSString*)clientName
                      inputOutput:(int)inputOutput
                        audioMidi:(int)audioMidi;
- (BOOL)quicklyDisconnectAppToClient:(NSString*)clientName
                         inputOutput:(int)inputOutput
                           audioMidi:(int)audioMidi;
- (void)connectPort:(NSString*)inputPort
           withPort:(NSString*)outputPort;
- (void)disconnectPort:(NSString*)inputPort
              withPort:(NSString*)outputPort;


- (BOOL)isPointInsideCurrentAppIcon:(CGPoint)pt;
- (BOOL)isPointInsideView:(CGPoint)pt;

- (int)numberOfCurrentAppPortsWithInputOutput:(int)inputOutput
                                    audioMidi:(int)audioMidi;
- (void)displayCurrentAppPortsWithInputOutput:(int)inputOutput
                                    audioMidi:(int)audioMidi;

- (void)viewClicked;
- (void)dismissPortsView;

- (void)fsToClient;

- (void)showHideScrollViews;

@end