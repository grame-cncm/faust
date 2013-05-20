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


#define kJackViewExtHMargins 30
#define kJackViewExtVMargins 5
#define kJackViewIntHMargins 100
#define kJackViewIntVMargins 5

#define kJackViewCurrentAppIconDimension 90
#define kJackViewCurrentAppIconBottomMargin 30

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

- (NSArray*)compatiblePortsWithInputOutput:(int)inputOutput audioMidi:(int)audioMidi;

@end


@interface JackViewDrawingView : UIView

@property (assign, nonatomic) JackView* jackView;

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
    
    JackViewDrawingView*    _drawingView;
    
    UITapGestureRecognizer* _singleTapRecognizer;
}

@property (assign, nonatomic) BOOL linking;
@property (assign, readwrite) CGPoint srcPt;
@property (assign, readwrite) CGPoint dstPt;
@property (assign, readwrite) JackViewPortsView* portsView;
@property (assign, readwrite) JackViewButton* currentClientButton;

- (void)loadJackClient:(jack_client_t*)jackClient;
- (jack_client_t*)jackClient;

- (BOOL)doesClientExist:(NSString*)clientName;
- (JackViewClient*)clientWithName:(NSString*)clientName;
- (JackViewPort*)portWithName:(NSString*)portName;

- (BOOL)hasCurrentClientCompatiblePortWithInputOutput:(int)inputOutput audioMidi:(int)audioMidi;

- (BOOL)isClient:(JackViewClient*)client
connectedToCurrentClientInputOutput:(int)inputOutput
       audioMidi:(int)audioMidi;
- (BOOL)isPort:(JackViewPort*)port
connectedToCurrentClientInputOutput:(int)inputOutput
     audioMidi:(int)audioMidi;
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
- (BOOL)isPointInsideCurrentAppPortsView:(CGPoint)pt;
- (NSString*)getPortDefinedAtPoint:(CGPoint)pt;

- (int)numberOfCurrentAppPortsWithInputOutput:(int)inputOutput
                                    audioMidi:(int)audioMidi;
- (void)displayCurrentAppPortsWithInputOutput:(int)inputOutput
                                    audioMidi:(int)audioMidi;

- (void)viewClicked;

@end