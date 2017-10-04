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

#import "FIKnob.h"

#define kStdKnobHintSpace         10

@implementation FIKnob
@synthesize biDirectional, arcStartAngle, cutoutSize, valueArcWidth;
@synthesize doubleTapValue, tripleTapValue;

#pragma mark -
#pragma mark Init

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super initWithDelegate:aDelegate]))
	{
        _hint = nil;
		self.arcStartAngle = 90.0;
		self.cutoutSize = 60.0;
        
		// add the gesture recognizers for double & triple taps
		UITapGestureRecognizer *doubleTapGesture = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleTap:)] autorelease];
		doubleTapGesture.numberOfTapsRequired = 2;
		[self addGestureRecognizer:doubleTapGesture];
        
		UITapGestureRecognizer *tripleTapGesture = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tripleTap:)] autorelease];
		tripleTapGesture.numberOfTapsRequired = 3;
		[self addGestureRecognizer:tripleTapGesture];
	}
    
	return self;
}

- (void)dealloc
{
    if (_hint) [_hint dealloc];
    [super dealloc];
}

// overridden to make sure the frame is always square.
- (void)setFrame:(CGRect)frame
{
	if (frame.size.width != frame.size.height)
	{
		if (frame.size.width > frame.size.height)
			frame = CGRectMake(frame.origin.x, frame.origin.y, frame.size.width, frame.size.width);
		else
			frame = CGRectMake(frame.origin.x, frame.origin.y, frame.size.height, frame.size.height);
	}
    
	[super setFrame:frame];
}

#pragma mark -
#pragma mark Gestures

- (void)doubleTap:(UIGestureRecognizer *)gestureRecognizer
{    
	if (self.allowsGestures)
	{
        CGPoint thisPoint = [gestureRecognizer locationInView:self];
        CGFloat newValue = [self valueFromPoint:thisPoint];
                
        if (newValue > self.value)
        {
            self.value = self.value + self.step;
        }
        else if (newValue < self.value)
        {
            self.value = self.value - self.step;
        }
	}
}

- (void)tripleTap:(UIGestureRecognizer *)gestureRecognizer
{    
}

- (void)setValueFromGesture:(NSNumber *)newValue
{
	self.value = [newValue floatValue];
}

#pragma mark -
#pragma mark Touch Handling

- (void)updateHint
{
    if (_hint)
    {
        UIView*     scrollView = self.superview.superview.superview;
        CGRect      absHandleRect = [self convertRect:CGRectMake(0.f, 0.f, self.frame.size.width, self.frame.size.height)
                                               toView:scrollView];

        _hint.title = [NSString stringWithFormat:@"%2.1f%@", self.value, self.suffixe];
        
        // Top
        if (absHandleRect.origin.y >= _hint.frame.size.height + kStdKnobHintSpace
            && absHandleRect.origin.x + (absHandleRect.size.width - _hint.frame.size.width) / 2.f + _hint.frame.size.width <= scrollView.frame.size.width
            && absHandleRect.origin.x + (absHandleRect.size.width - _hint.frame.size.width) / 2.f >= 0.f)
        {
            _hint.position = 0;
            [_hint setFrame:CGRectMake(absHandleRect.origin.x + (absHandleRect.size.width - _hint.frame.size.width) / 2.f,
                                       absHandleRect.origin.y - _hint.frame.size.height - kStdKnobHintSpace,
                                       _hint.frame.size.width,
                                       _hint.frame.size.height)];
        }
        
        // Left
        else if (absHandleRect.origin.x >= _hint.frame.size.width + kStdKnobHintSpace)
        {
            _hint.position = 2;
            [_hint setFrame:CGRectMake(absHandleRect.origin.x - _hint.frame.size.width - kStdKnobHintSpace,
                                       absHandleRect.origin.y,
                                       _hint.frame.size.width,
                                       _hint.frame.size.height)];
        }
        
        // Right
        else if (scrollView.frame.size.width - absHandleRect.origin.x - absHandleRect.size.width >= _hint.frame.size.width + kStdKnobHintSpace)
        {
            _hint.position = 3;
            [_hint setFrame:CGRectMake(absHandleRect.origin.x + absHandleRect.size.width + kStdKnobHintSpace,
                                       absHandleRect.origin.y,
                                       _hint.frame.size.width,
                                       _hint.frame.size.height)];
        }
        
        // Bottom
        else
        {
            _hint.position = 1;
            [_hint setFrame:CGRectMake(absHandleRect.origin.x + (absHandleRect.size.width - _hint.frame.size.width) / 2.f,
                                       absHandleRect.origin.y + absHandleRect.size.height + kStdKnobHintSpace,
                                       _hint.frame.size.width,
                                       _hint.frame.size.height)];
        }
        
        [_hint setNeedsDisplay];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{    
    self.motionBlocked = YES;
    
	CGPoint thisPoint = [[touches anyObject] locationInView:self];
	CGPoint centerPoint = CGPointMake(self.frame.size.width / 2.0, self.frame.size.width / 2.0);
	initialAngle = angleBetweenPoints(thisPoint, centerPoint);
    
	// create the initial angle and initial transform
	initialTransform = [self initialTransform];
    
    if (!_hint)
    {
        _hint = [[FIHint alloc] init];
        [self.superview.superview.superview addSubview:_hint];
    }
    
    if (_hint)
    {
        _hint.title = [NSString stringWithFormat:@"%2.1f%@", self.value, self.suffixe];
        [self updateHint];
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    self.motionBlocked = YES;
    
	CGPoint thisPoint = [[touches anyObject] locationInView:self];
	CGPoint centerPoint = CGPointMake(self.frame.size.width / 2.0, self.frame.size.width / 2.0);
    
	CGFloat currentAngle = angleBetweenPoints(thisPoint, centerPoint);
	CGFloat angleDiff = (initialAngle - currentAngle);
	CGAffineTransform newTransform = CGAffineTransformRotate(initialTransform, angleDiff);
    
	CGFloat newValue = [self newValueFromTransform:newTransform];
    
	// only set the new value if it doesn't flip the knob around
	CGFloat diff = self.value - newValue;
	diff = (diff < 0) ? -diff : diff;
	if (diff < (self.max - self.min) / 10.0)
	{
		self.value = newValue;
	}
	else
	{
		// reset the initial angle & transform using the current value
		initialTransform = [self initialTransform];
		initialAngle = angleBetweenPoints(thisPoint, centerPoint);
	}
    
    [self updateHint];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    self.motionBlocked = NO;
    
    if (_hint)
    {
        [_hint removeFromSuperview];
        [_hint release];
        _hint = nil;
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    self.motionBlocked = NO;
    
    if (_hint)
    {
        [_hint removeFromSuperview];
        [_hint release];
        _hint = nil;
    }
}

#pragma mark -
#pragma mark Helper Methods

- (CGFloat)valueFromPoint:(CGPoint)point
{
    CGPoint centerPoint = CGPointMake(self.frame.size.width / 2.0, self.frame.size.width / 2.0);
    CGFloat currentAngle = 450.f + angleBetweenPoints(point, centerPoint) * 57.29577951308232;
    int normAngle = 360 - ((int)floor(currentAngle) % 360);
	CGFloat newValue;
    float course = 360.f - self.cutoutSize;
    float courseOffset = self.cutoutSize / 2.f;
    
    newValue = normAngle - courseOffset;
    if (newValue < 0.f) newValue = 0.f;
    else if (newValue > course) newValue = course;
    
    newValue = newValue / course;
    newValue = self.min + newValue * (self.max - self.min);
    
	return newValue;
}


- (CGAffineTransform)initialTransform
{
	CGFloat pValue = (self.value - self.min) / (self.max - self.min);
	pValue = (pValue * kDCKnobRatio * 2) - kDCKnobRatio;
	return CGAffineTransformMakeRotation(pValue);
}

- (CGFloat)newValueFromTransform:(CGAffineTransform)transform
{
	CGFloat newValue = atan2(transform.b, transform.a);
	newValue = (newValue + kDCKnobRatio) / (kDCKnobRatio * 2);
	newValue = self.min + (newValue * (self.max - self.min));
	return newValue;
}

#pragma mark -
#pragma mark Drawing

- (void)drawRect:(CGRect)rect
{
    if (self.hideOnGUI) return;
    
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGRect boundsRect = self.bounds;
	CGFloat maxHalf = self.min + (self.max - self.min) / 2;
	float x = boundsRect.size.width / 2;
	float y = boundsRect.size.height / 2;
    
	CGContextSaveGState(context);
	CGContextSetLineWidth(context, self.valueArcWidth);
    
    self.backgroundColor = [UIColor blackColor];
	if (self.backgroundColorAlpha > 0.02)
	{
		// outline semi circle
		UIColor *backgroundColor = [UIColor colorWithRed:0.3 green:0.3 blue:0.3 alpha:1.];
		[backgroundColor set];
        
		CGContextAddArc(context,
						x,
						y,
						(boundsRect.size.width / 2) - self.valueArcWidth / 2,
						FIDegreesToRadians(self.arcStartAngle + self.cutoutSize / 2),
						FIDegreesToRadians(self.arcStartAngle + 360 - self.cutoutSize / 2),
						0);
		CGContextStrokePath(context);
	}
    
    // Gradient
    context = UIGraphicsGetCurrentContext();
    
    UIColor *lightGradientColor = [UIColor colorWithRed:0.7 green:0.7 blue:0.7 alpha:1.];
    UIColor *darkGradientColor = [UIColor colorWithRed:0. green:0. blue:0. alpha:1.];
    
    CGFloat locations[2] = {0.0, 1.0};
    CFArrayRef colors = (CFArrayRef) [NSArray arrayWithObjects:(id)lightGradientColor.CGColor,
                                      (id)darkGradientColor.CGColor, 
                                      nil];
    
    CGColorSpaceRef colorSpc = CGColorSpaceCreateDeviceRGB();
    CGGradientRef gradient = CGGradientCreateWithColors(colorSpc, colors, locations);
    
    CGContextSetBlendMode(context, kCGBlendModeMultiply);
    
    CGContextDrawLinearGradient(context,
                                gradient, 
                                CGPointMake(0.0, 0.0), 
                                CGPointMake(rect.size.width, rect.size.height), 
                                kCGGradientDrawsAfterEndLocation); //Adjust second point according to your view height
    
    CGColorSpaceRelease(colorSpc);
    CGGradientRelease(gradient);
    CGContextSetBlendMode(context, kCGBlendModeNormal);
    // End gradient
    
	// draw the value semi circle
	[self.color set];
	CGFloat valueAdjusted = (self.value - self.min) / (self.max - self.min);
	if (self.biDirectional)
	{
		CGContextAddArc(context,
						x,
						y,
						(boundsRect.size.width / 2) - self.valueArcWidth / 2,
						FIDegreesToRadians(self.arcStartAngle + 180),
						FIDegreesToRadians(self.arcStartAngle + self.cutoutSize / 2 + (360 - self.cutoutSize) * valueAdjusted),
						self.value <= maxHalf);
	}
	else
	{
		CGContextAddArc(context,
						x,
						y,
						(boundsRect.size.width / 2) - self.valueArcWidth / 2,
						FIDegreesToRadians(self.arcStartAngle + self.cutoutSize / 2),
						FIDegreesToRadians(self.arcStartAngle + self.cutoutSize / 2 + (360 - self.cutoutSize) * valueAdjusted),
						0);
	}
	CGContextStrokePath(context);
    
	// draw the value string as needed
	if (self.displaysValue)
	{
		if (self.labelColor)
			[self.labelColor set];
		else
			[self.color set];
		NSString *valueString = nil;
        float multiplier = 1.f;

        if ([self.suffixe compare:@""] == NSOrderedSame)
        {
            if (self.step < 0.01) valueString = [NSString stringWithFormat:@"%2.3f", self.value];
            else if (self.step < 0.1) valueString = [NSString stringWithFormat:@"%2.2f", self.value];
            else valueString = [NSString stringWithFormat:@"%2.1f", self.value];
        }
        else
        {
            if (self.step < 0.01) valueString = [NSString stringWithFormat:@"%2.3f\r%@", self.value, self.suffixe];
            else if (self.step < 0.1) valueString = [NSString stringWithFormat:@"%2.2f\r%@", self.value, self.suffixe];
            else valueString = [NSString stringWithFormat:@"%2.1f\r%@", self.value, self.suffixe];
            multiplier = 2.f;
        }   
		CGSize valueStringSize = [valueString sizeWithFont:self.labelFont
												  forWidth:boundsRect.size.width
											 lineBreakMode:UILineBreakModeTailTruncation];
		[valueString drawInRect:CGRectMake(floorf((boundsRect.size.width - valueStringSize.width) / 2.0 + self.labelOffset.x),
										   floorf((boundsRect.size.height - valueStringSize.height) / 2.0 + self.labelOffset.y),
										   valueStringSize.width,
										   multiplier * valueStringSize.height)
					   withFont:self.labelFont
				  lineBreakMode:UILineBreakModeTailTruncation
                      alignment:UITextAlignmentCenter];		
	}
    
    // Draw assignation
    if (self.assignated)
    {
        CGContextSetLineWidth(context, 3.);
        [self.color set];
        [self context:context addRoundedRect:boundsRect cornerRadius:3.f];
        CGContextStrokePath(context);
    }
    
    // Draw selection
    if (self.responderSelected)
    {
        CGContextSetLineWidth(context, 15.);
        [self.color set];
        [self context:context addRoundedRect:boundsRect cornerRadius:3.f];
        CGContextStrokePath(context);
    }
    
	CGContextRestoreGState(context);
}

@end
