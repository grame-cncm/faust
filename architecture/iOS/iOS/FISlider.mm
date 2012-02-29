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

#import "FISlider.h"

@implementation FISlider
@synthesize handleSize, cornerRadius, isHorizontalSlider, biDirectional;

#pragma mark -
#pragma mark Init

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super initWithDelegate:aDelegate]))
	{
		// add the double tap gesture for jumping the value straight to that point
		UITapGestureRecognizer *doubleTapGesture = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleTap:)] autorelease];
		doubleTapGesture.numberOfTapsRequired = 2;
		[self addGestureRecognizer:doubleTapGesture];
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleRightMargin;
        
		self.cornerRadius = 3.0;
	}
	
	return self;
}

- (void)dealloc
{
    [super dealloc];
}

// to setup handle size
- (void)setFrame:(CGRect)frame
{
	[super setFrame:frame];
	//self.handleSize = floorf((self.isHorizontalSlider) ? self.bounds.size.width / 6 : self.bounds.size.height / 6);
	if (self.handleSize < 35.0)
		self.handleSize = 35.0;
}

#pragma mark -
#pragma mark Touch Handling

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch *touch = [touches anyObject];
	CGPoint touchPosition = [touch locationInView:self];
	CGFloat handleOrigin;
	CGFloat valueInternal = (self.value - self.min) / (self.max - self.min);
    
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
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	if (touchHandleOffset == -1)
		return;
    
	UITouch *touch = [touches anyObject];
	CGPoint touchPosition = [touch locationInView:self];
    
	CGFloat newValue;
    
	if (self.isHorizontalSlider)
		newValue = (touchPosition.x - touchHandleOffset) / (self.bounds.size.width - self.handleSize);
	else
		newValue = 1 - (touchPosition.y - touchHandleOffset) / (self.bounds.size.height - self.handleSize);
    
	[self setValue:self.min + newValue * (self.max - self.min)];
}

- (void)doubleTap:(UIGestureRecognizer *)gesture
{
	if (!self.allowsGestures)
		return;
	
	CGPoint tapPoint = [gesture locationInView:self];
	
	// work out the touch position and therefore value
	CGFloat newValue;
	if (self.isHorizontalSlider)
		newValue = (tapPoint.x - self.handleSize / 2) / (self.bounds.size.width - self.handleSize);
	else
		newValue = 1 - (tapPoint.y - self.handleSize / 2) / (self.bounds.size.height - self.handleSize);
	
	[self setValue:self.min + newValue * (self.max - self.min)];
}

#pragma mark -
#pragma mark Drawing

- (void)drawRect:(CGRect)rect
{
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGRect boundsRect = self.bounds;
	const CGFloat *colorComponents = CGColorGetComponents(self.color.CGColor);
	UIColor *backgroundColor = [UIColor colorWithRed:colorComponents[0]
											   green:colorComponents[1]
												blue:colorComponents[2]
											   alpha:self.backgroundColorAlpha];
	UIColor *lighterBackgroundColor = [UIColor colorWithRed:colorComponents[0]
                                                      green:colorComponents[1]
                                                       blue:colorComponents[2]
                                                      alpha:self.backgroundColorAlpha / 2.0];

	// draw background of slider
	[lighterBackgroundColor set];
	[self context:context addRoundedRect:boundsRect cornerRadius:self.cornerRadius];
	CGContextFillPath(context);
    
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

        valueString = [NSString stringWithFormat:@"%2.1f", self.value];
		
		CGSize valueStringSize = [valueString sizeWithFont:self.labelFont];
		CGRect handleRect = [self rectForHandle];
		[valueString drawInRect:CGRectMake(handleRect.origin.x + (handleRect.size.width - valueStringSize.width) / 2,
										   handleRect.origin.y + (handleRect.size.height - valueStringSize.height) / 2,
										   valueRect.size.width,
										   valueRect.size.height)
					   withFont:self.labelFont
				  lineBreakMode:UILineBreakModeTailTruncation];
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
