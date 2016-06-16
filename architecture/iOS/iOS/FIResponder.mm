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

@implementation FIResponder

@synthesize delegate;
@synthesize color, backgroundColorAlpha;
@synthesize labelFont, labelColor, labelOffset;
@synthesize min, max, value, step;
@synthesize displaysValue, allowsGestures;
@synthesize suffixe;
@synthesize responderSelected;
@synthesize motionBlocked;
@synthesize assignated;

- (void)dealloc
{
	delegate = nil;
	[color release];
	[labelFont release];
	[labelColor release];
    [suffixe release];
    
	[super dealloc];
}

#pragma mark -

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super init]))
	{
		self.delegate = aDelegate;
        
		// setup defaults
		self.backgroundColor = [UIColor blackColor];
		self.backgroundColorAlpha = 0.3;
		self.color = [UIColor blueColor];
		self.min = 0.0;
		self.max = 1.0;
		self.displaysValue = YES;
		self.allowsGestures = YES;
		self.labelFont = [UIFont boldSystemFontOfSize:12.5];
        self.step = 0.1;
        self.value = 0.0;
		self.clipsToBounds = NO;
		self.opaque = YES;
        self.suffixe = [[NSString alloc] initWithString:@""];
        self.responderSelected = NO;
        self.assignated = NO;
        self.motionBlocked = NO;
        self.hideOnGUI = NO;
	}
    
	return self;
}

- (void)setValue:(CGFloat)newValue
{
    if (newValue > self.max) {
        value = self.max;
    } else if (newValue < self.min) {
        value = self.min;
    } else {
        value = newValue;
    }
    if (self.delegate) {
        [self.delegate responderValueDidChange:self.value sender:self];
    }
    
	[self setNeedsDisplay];
}

#pragma mark -
#pragma mark Helper Methods

- (void)context:(CGContextRef)c addRoundedRect:(CGRect)rect cornerRadius:(float)cornerRadius
{
	rect.size.width += 0.5;
	int x_left = rect.origin.x;
	int x_left_center = rect.origin.x + cornerRadius;
	int x_right_center = rect.origin.x + rect.size.width - cornerRadius;
	int x_right = rect.origin.x + rect.size.width;
	int y_top = rect.origin.y;
	int y_top_center = rect.origin.y + cornerRadius;
	int y_bottom_center = rect.origin.y + rect.size.height - cornerRadius;
	int y_bottom = rect.origin.y + rect.size.height;
    
	/* Begin! */
	CGContextBeginPath(c);
	CGContextMoveToPoint(c, x_left, y_top_center);
    
	/* First corner */
	CGContextAddArcToPoint(c, x_left, y_top, x_left_center, y_top, cornerRadius);
	CGContextAddLineToPoint(c, x_right_center, y_top);
    
	/* Second corner */
	CGContextAddArcToPoint(c, x_right, y_top, x_right, y_top_center, cornerRadius);
	CGContextAddLineToPoint(c, x_right, y_bottom_center);
    
	/* Third corner */
	CGContextAddArcToPoint(c, x_right, y_bottom, x_right_center, y_bottom, cornerRadius);
	CGContextAddLineToPoint(c, x_left_center, y_bottom);
    
	/* Fourth corner */
	CGContextAddArcToPoint(c, x_left, y_bottom, x_left, y_bottom_center, cornerRadius);
	CGContextAddLineToPoint(c, x_left, y_top_center);
    
	/* Done */
	CGContextClosePath(c);	
}

@end
