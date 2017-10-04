/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 
 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.
 
 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

/************************************************************************
 ************************************************************************
 Based on DCControls - https://github.com/domesticcatsoftware/DCControls
 Copyright (C) 2011 by Patrick Richards - http://domesticcat.com.au/
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ************************************************************************
 ************************************************************************/

#import <UIKit/UIKit.h>

#define FIDegreesToRadians(x) (M_PI * (x) / 180.0)
#define FIRadiansToDegrees(x) ((x) * 180.0 / M_PI)

@protocol FIResponderDelegate <NSObject>

@required

- (void)responderValueDidChange:(float)value sender:(id)sender;

@end

@interface FIResponder : UIControl

@property (nonatomic, assign) id delegate;
@property (nonatomic, retain) UIColor *color;			// default: black
@property CGFloat backgroundColorAlpha;					// default: 0.3

@property (nonatomic, retain) UIFont *labelFont;		// default: bold, system, 12.5
@property (nonatomic, retain) UIColor *labelColor;		// default: use self.color
@property CGPoint labelOffset;							// default: CGPointZero

@property CGFloat min;									// default: 0.0
@property CGFloat max;									// default: 1.0
@property (nonatomic) CGFloat value;					// default: 0.0
@property (nonatomic) CGFloat step;                     // default: 0.1
@property (assign, nonatomic) NSString* suffixe;        // default: @""

@property BOOL displaysValue;							// default: YES
@property BOOL allowsGestures;							// default: YES
@property BOOL responderSelected;                       // default: NO
@property BOOL motionBlocked;                           // default: NO
@property BOOL assignated;                              // default: NO
@property BOOL hideOnGUI;                               // default: NO

- (id)initWithDelegate:(id)aDelegate;

- (void)context:(CGContextRef)context addRoundedRect:(CGRect)rect cornerRadius:(float)cornerRadius;

@end
