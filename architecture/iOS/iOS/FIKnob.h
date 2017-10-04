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

#import "FIResponder.h"
#import "FIHint.h"

#define kDCKnobRatio (M_PI * ((360.0 - self.cutoutSize) / 360.0))

static inline CGFloat angleBetweenPoints(CGPoint first, CGPoint second)
{
	CGFloat height = second.y - first.y;
	CGFloat width = first.x - second.x;
	CGFloat rads = atan2(height, width);
	return rads;
}

@interface FIKnob : FIResponder
{
	CGAffineTransform initialTransform;
	CGPoint lastPoint;
	CGFloat initialAngle;
    FIHint* _hint;
}

@property BOOL biDirectional;					// default: NO
@property CGFloat arcStartAngle;				// default: 90 (degrees)
@property CGFloat cutoutSize;					// default: 60 (degrees)
@property CGFloat valueArcWidth;				// default: 15.0

@property CGFloat doubleTapValue;				// default: 0%
@property CGFloat tripleTapValue;				// default: 0%

/////////////////////////
// Init/Custom Setters //
/////////////////////////

- (id)initWithDelegate:(id)aDelegate;
- (void)setFrame:(CGRect)frame;

////////////////////
// Touch Handling //
////////////////////

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)updateHint;

////////////////////
// Helper Methods //
////////////////////

- (CGFloat)valueFromPoint:(CGPoint)point;
- (CGAffineTransform)initialTransform;
- (CGFloat)newValueFromTransform:(CGAffineTransform)transform;

@end
