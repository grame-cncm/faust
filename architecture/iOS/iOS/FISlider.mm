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

#import "FISlider.h"

#define kStdSliderHintSpace 10

@implementation FISlider
@synthesize handleSize, cornerRadius, isHorizontalSlider, biDirectional, fMenuItemNames, fMenuItemValues;

#pragma mark -
#pragma mark Init

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super initWithDelegate:aDelegate]))
	{
        _hint = nil;
		// add the double tap gesture for jumping the value straight to that point
		UITapGestureRecognizer *doubleTapGesture = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleTap:)] autorelease];
		doubleTapGesture.numberOfTapsRequired = 2;
		[self addGestureRecognizer:doubleTapGesture];
        
		self.cornerRadius = 3.0;
	}
	
	return self;
}

- (void)dealloc
{
    if (_hint) [_hint dealloc];
    [super dealloc];
}

// to setup handle size
- (void)setFrame:(CGRect)frame
{
	[super setFrame:frame];

	if (self.handleSize < 35.0)
		self.handleSize = 35.0;
}

#pragma mark -
#pragma mark Touch Handling

- (void)updateHint
{
    if (_hint)
    {
        UIView*     scrollView = self.superview.superview.superview;
        CGRect      handleRect = [self rectForHandle];
        CGRect      absHandleRect = [self convertRect:handleRect
                                               toView:scrollView];
        
        _hint.title = [NSString stringWithFormat:@"%2.1f%@", self.value, self.suffixe];
        
        // Top
        if (absHandleRect.origin.y >= _hint.frame.size.height + kStdSliderHintSpace
            && absHandleRect.origin.x + (absHandleRect.size.width - _hint.frame.size.width) / 2.f + _hint.frame.size.width <= scrollView.frame.size.width
            && absHandleRect.origin.x + (absHandleRect.size.width - _hint.frame.size.width) / 2.f >= 0.f)
        {
            _hint.position = 0;
            [_hint setFrame:CGRectMake(absHandleRect.origin.x + (absHandleRect.size.width - _hint.frame.size.width) / 2.f,
                                       absHandleRect.origin.y - _hint.frame.size.height - kStdSliderHintSpace,
                                       _hint.frame.size.width,
                                       _hint.frame.size.height)];
        }
        
        // Left
        else if (absHandleRect.origin.x >= _hint.frame.size.width + kStdSliderHintSpace)
        {
            _hint.position = 2;
            [_hint setFrame:CGRectMake(absHandleRect.origin.x - _hint.frame.size.width - kStdSliderHintSpace,
                                       absHandleRect.origin.y,
                                       _hint.frame.size.width,
                                       _hint.frame.size.height)];
        }
        
        // Right
        else if (scrollView.frame.size.width - absHandleRect.origin.x - absHandleRect.size.width >= _hint.frame.size.width + kStdSliderHintSpace)
        {
            _hint.position = 3;
            [_hint setFrame:CGRectMake(absHandleRect.origin.x + absHandleRect.size.width + kStdSliderHintSpace,
                                       absHandleRect.origin.y,
                                       _hint.frame.size.width,
                                       _hint.frame.size.height)];
        }
        
        // Bottom
        else
        {
            _hint.position = 1;
            [_hint setFrame:CGRectMake(absHandleRect.origin.x + (absHandleRect.size.width - _hint.frame.size.width) / 2.f,
                                       absHandleRect.origin.y + absHandleRect.size.height + kStdSliderHintSpace,
                                       _hint.frame.size.width,
                                       _hint.frame.size.height)];
        }
        
        [_hint setNeedsDisplay];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.hideOnGUI) return;
    
	UITouch *touch = [touches anyObject];
	CGPoint touchPosition = [touch locationInView:self];
	CGFloat handleOrigin;
	CGFloat valueInternal = (self.value - self.min) / (self.max - self.min);
        
    self.motionBlocked = YES;
    
	if (self.isHorizontalSlider)
		handleOrigin = (self.bounds.size.width - self.handleSize) * valueInternal;
	else
		handleOrigin = self.bounds.size.height - self.handleSize - (self.bounds.size.height - self.handleSize) * valueInternal;
    
	// if the touch is inside the handle then save the offset of the touch from the handle
	if ((self.isHorizontalSlider && touchPosition.x > handleOrigin && touchPosition.x < handleOrigin + handleSize)
		|| (!self.isHorizontalSlider && touchPosition.y > handleOrigin && touchPosition.y < handleOrigin + handleSize))
	{
		touchHandleOffset = (self.isHorizontalSlider) ? touchPosition.x - handleOrigin : touchPosition.y - handleOrigin;
	}
	else
	{
		// set the handle offset to -1 so touchesmoved events are ignored
		touchHandleOffset = -1;
	}
    
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
	if (touchHandleOffset == -1)
		return;

    self.motionBlocked = YES;
    
	UITouch *touch = [touches anyObject];
	CGPoint touchPosition = [touch locationInView:self];
    
	CGFloat newValue;
    
	if (self.isHorizontalSlider)
		newValue = (touchPosition.x - touchHandleOffset) / (self.bounds.size.width - self.handleSize);
	else
		newValue = 1 - (touchPosition.y - touchHandleOffset) / (self.bounds.size.height - self.handleSize);

	[self setValue:self.min + newValue * (self.max - self.min)];

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

- (void)doubleTap:(UIGestureRecognizer *)gesture
{
	if (!self.allowsGestures)
		return;
	
	CGPoint tapPoint = [gesture locationInView:self];	
    CGRect handleRect = [self rectForHandle];
    
    if (self.isHorizontalSlider)
    {
        if (tapPoint.x > handleRect.origin.x + handleRect.size.width / 2.f)
        {
            self.value = self.value + self.step;
        }
        else if (tapPoint.x < handleRect.origin.x + handleRect.size.width / 2.f)
        {
            self.value = self.value - self.step;
        }
    }
    else
    {
        if (tapPoint.y < handleRect.origin.y + handleRect.size.height / 2.f)
        {
            self.value = self.value + self.step;
        }
        else if (tapPoint.y > handleRect.origin.y + handleRect.size.height / 2.f)
        {
            self.value = self.value - self.step;
        }
    }
}

#pragma mark -
#pragma mark Drawing

- (void)drawRect:(CGRect)rect
{
    if (self.hideOnGUI) return;
    
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGRect boundsRect = self.bounds;
	const CGFloat *colorComponents = CGColorGetComponents(self.color.CGColor);
	UIColor *backgroundColor = [UIColor colorWithRed:colorComponents[0]
											   green:colorComponents[1]
												blue:colorComponents[2]
											   alpha:self.backgroundColorAlpha];
	UIColor *lighterBackgroundColor = [UIColor colorWithRed:0.3 green:0.3 blue:0.3 alpha:1.];

	// draw background of slider
    self.backgroundColor = [UIColor blackColor];
	[lighterBackgroundColor set];
	[self context:context addRoundedRect:boundsRect cornerRadius:self.cornerRadius];
	CGContextFillPath(context);
    
    // Gradient
    context = UIGraphicsGetCurrentContext();
    
    UIColor *lightGradientColor = [UIColor colorWithRed:0.5 green:0.5 blue:0.5 alpha:1.];
    UIColor *darkGradientColor = [UIColor colorWithRed:0.2 green:0.2 blue:0.2 alpha:1.];
    
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
    
	// draw the 'filled' section to the left of the handle (or from the handle if in bidirectional mode)
	CGRect valueRect;
	[backgroundColor set];
	if (self.isHorizontalSlider)
	{
		CGFloat handlePos = CGRectGetMinX([self rectForHandle]);
		CGFloat handleMid = CGRectGetMidX([self rectForHandle]);
		CGFloat handleMax = CGRectGetMaxX([self rectForHandle]);
		if (self.biDirectional)
		{
			if (self.value > (self.max - self.min) / 2)
				valueRect = CGRectMake(self.bounds.size.width / 2.0, 0, handleMid - self.bounds.size.width / 2.0, self.bounds.size.height);
			else
				valueRect = CGRectMake(handleMid, 0, (self.bounds.size.width - handleMid - self.bounds.size.width / 2.0), self.bounds.size.height);
			[self context:context addRoundedRect:valueRect cornerRadius:0];
		}
		else
		{
			valueRect = CGRectMake(0, 0, self.bounds.size.width - (self.bounds.size.width - handleMax), self.bounds.size.height);
			[self context:context addRoundedRect:valueRect cornerRadius:self.cornerRadius];
		}
        
		CGContextFillPath(context);
        
		valueRect = CGRectMake(handlePos, 0, handleSize, self.bounds.size.height);
	}
	else
	{
		// draw the 'filled' section below the handle (or from the handle if in bidirectional mode) using a colour slightly lighter than the theme
		CGFloat handlePos = CGRectGetMinY([self rectForHandle]);
		CGFloat handleMid = CGRectGetMidY([self rectForHandle]);
		CGFloat handleMin = CGRectGetMinY([self rectForHandle]);
		if (self.biDirectional)
		{
			if (self.value > (self.max - self.min) / 2)
				valueRect = CGRectMake(0, handleMid, self.bounds.size.width, self.bounds.size.height / 2.0 - handleMid);
			else
				valueRect = CGRectMake(0, self.bounds.size.height / 2.0, self.bounds.size.width, handleMid - self.bounds.size.height / 2.0);
			[self context:context addRoundedRect:valueRect cornerRadius:0];
		}
		else
		{
			valueRect = CGRectMake(0, handleMin, self.bounds.size.width, self.bounds.size.height - handleMin);
			[self context:context addRoundedRect:valueRect cornerRadius:self.cornerRadius];
		}
        
		CGContextFillPath(context);
        
		valueRect = CGRectMake(0, handlePos, self.bounds.size.width, handleSize);
	}
    
	// draw the handle
	[self.color set];
	[self context:context addRoundedRect:valueRect cornerRadius:self.cornerRadius];
	CGContextFillPath(context);
    
	// draw value string as needed
	if (self.displaysValue)
	{
		[self.labelColor set];
		NSString *valueString = nil;
        float multiplier = 1.f;
        
        // In menu items, displays them instead of the value
        if (self.fMenuItemValues.size() > 0) {
        
            for (int i = 0; i < self.fMenuItemValues.size(); i++) {
                if (floor(self.value) == self.fMenuItemValues[i]) {
                    valueString = [NSString stringWithCString:self.fMenuItemNames[i].c_str() encoding:NSUTF8StringEncoding];
                }
            }
            
        } else {

            if ([self.suffixe compare:@""] == NSOrderedSame) {
                if (self.step < 0.01) valueString = [NSString stringWithFormat:@"%2.3f", self.value];
                else if (self.step < 0.1) valueString = [NSString stringWithFormat:@"%2.2f", self.value];
                else valueString = [NSString stringWithFormat:@"%2.1f", self.value];
            } else {
                if (self.step < 0.01) valueString = [NSString stringWithFormat:@"%2.3f\r%@", self.value, self.suffixe];
                else if (self.step < 0.1) valueString = [NSString stringWithFormat:@"%2.2f\r%@", self.value, self.suffixe];
                else valueString = [NSString stringWithFormat:@"%2.1f\r%@", self.value, self.suffixe];
                multiplier = 2.f;
            }
            
        }
		
		CGSize valueStringSize = [valueString sizeWithFont:self.labelFont];
		CGRect handleRect = [self rectForHandle];

        [valueString drawInRect:CGRectMake(handleRect.origin.x,
										   handleRect.origin.y + (handleRect.size.height - multiplier * valueStringSize.height) / 2.f,
										   handleRect.size.width,
										   multiplier * valueRect.size.height)
					   withFont:self.labelFont
				  lineBreakMode:UILineBreakModeMiddleTruncation
                      alignment:UITextAlignmentCenter];        
	}
    
    // Draw assignation
    if (self.assignated)
    {
        CGContextSetLineWidth(context, 3.);
        [self.color set];
        [self context:context addRoundedRect:boundsRect cornerRadius:self.cornerRadius];
        CGContextStrokePath(context);
    }
    
    // Draw selection
    if (self.responderSelected)
    {
        CGContextSetLineWidth(context, 15.);
        [self.color set];
        [self context:context addRoundedRect:boundsRect cornerRadius:self.cornerRadius];
        CGContextStrokePath(context);
    }
}

- (CGRect)rectForHandle
{
	CGRect valueRect;
    
	if (self.isHorizontalSlider)
	{
		float handlePos = (self.bounds.size.width - handleSize) * ((self.value - self.min) / (self.max - self.min));
		valueRect = CGRectMake(handlePos, 0, handleSize, self.bounds.size.height);
	}
	else
	{
		float handlePos = (self.bounds.size.height - handleSize) - ((self.bounds.size.height - handleSize) * ((self.value - self.min) / (self.max - self.min)));
		valueRect = CGRectMake(0, handlePos, self.bounds.size.width, handleSize);
	}
    
	return valueRect;
}

@end
