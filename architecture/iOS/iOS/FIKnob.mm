/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#import "FIKnob.h"

@implementation FIKnob
@synthesize biDirectional, arcStartAngle, cutoutSize, valueArcWidth;
@synthesize doubleTapValue, tripleTapValue;

#pragma mark -
#pragma mark Init

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super initWithDelegate:aDelegate]))
	{
		self.arcStartAngle = 90.0;
		self.cutoutSize = 60.0;
		self.valueArcWidth = 15.0;
        
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
		[self performSelector:@selector(setValueFromGesture:) withObject:[NSNumber numberWithFloat:self.doubleTapValue] afterDelay:0.17];
	}
}

- (void)tripleTap:(UIGestureRecognizer *)gestureRecognizer
{
	if (self.allowsGestures)
	{
		// cancel the double tap
		[NSThread cancelPreviousPerformRequestsWithTarget:self selector:@selector(setValueFromGesture:) object:[NSNumber numberWithFloat:self.doubleTapValue]];
        
		[self performSelector:@selector(setValueFromGesture:) withObject:[NSNumber numberWithFloat:self.tripleTapValue]];
	}
}

- (void)setValueFromGesture:(NSNumber *)newValue
{
	self.value = [newValue floatValue];
}

#pragma mark -
#pragma mark Touch Handling

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint thisPoint = [[touches anyObject] locationInView:self];
	CGPoint centerPoint = CGPointMake(self.frame.size.width / 2.0, self.frame.size.width / 2.0);
	initialAngle = angleBetweenPoints(thisPoint, centerPoint);
    
	// create the initial angle and initial transform
	initialTransform = [self initialTransform];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
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
}

#pragma mark -
#pragma mark Helper Methods

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
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGRect boundsRect = self.bounds;
	CGFloat maxHalf = self.min + (self.max - self.min) / 2;
	float x = boundsRect.size.width / 2;
	float y = boundsRect.size.height / 2;
    
	CGContextSaveGState(context);
	CGContextSetLineWidth(context, self.valueArcWidth);
    
	if (self.backgroundColorAlpha > 0.02)
	{
		// outline semi circle
		const CGFloat *colorComponents = CGColorGetComponents(self.color.CGColor);
		UIColor *backgroundColor = [UIColor colorWithRed:colorComponents[0]
												   green:colorComponents[1]
													blue:colorComponents[2]
												   alpha:self.backgroundColorAlpha];
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
		if (self.biDirectional)
			valueString = [NSString stringWithFormat:@"%02.0f%%", ((self.value - self.min - (self.max - self.min) / 2) / (self.max - self.min)) * 100];
		else
			valueString = [NSString stringWithFormat:@"%03.0f%%", ((self.value - self.min) / (self.max - self.min)) * 100];
		CGSize valueStringSize = [valueString sizeWithFont:self.labelFont
												  forWidth:boundsRect.size.width
											 lineBreakMode:UILineBreakModeTailTruncation];
		[valueString drawInRect:CGRectMake(floorf((boundsRect.size.width - valueStringSize.width) / 2.0 + self.labelOffset.x),
										   floorf((boundsRect.size.height - valueStringSize.height) / 2.0 + self.labelOffset.y),
										   valueStringSize.width,
										   valueStringSize.height)
					   withFont:self.labelFont
				  lineBreakMode:UILineBreakModeTailTruncation];		
	}
    
	CGContextRestoreGState(context);
}

@end
