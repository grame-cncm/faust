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

#import "FIButton.h"

@implementation FIButton

@synthesize cornerRadius;
@synthesize title;
@synthesize type = _type;

#pragma mark -
#pragma mark Init

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super initWithDelegate:aDelegate]))
	{
        self.type = kPushButtonType;
		self.cornerRadius = 3.0;
        UITapGestureRecognizer *doubleTapGesture = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(doubleTap:)] autorelease];
		doubleTapGesture.numberOfTapsRequired = 2;
		[self addGestureRecognizer:doubleTapGesture];
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
}

#pragma mark -
#pragma mark Touch Handling

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.type == kPushButtonType
        || self.type == kTabItemButtonType
        || self.type == kCheckButtonType) {
        self.value = 1.f;
    }
    [self setNeedsDisplay];
}

- (void)setOn
{
    if (self.type == kPushButtonType
        || self.type == kTabItemButtonType
        || self.type == kCheckButtonType) {
        self.value = 1.f;
    }
    [self setNeedsDisplay];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.type == kToggleButtonType) self.value = 1.f - self.value;
    else if (self.type == kPushButtonType) self.value = 0.f;
    [self setNeedsDisplay];
}

// Function only here to refresh and intercept dble click to prevent zoom of the scroll view
- (void)doubleTap:(UIGestureRecognizer *)gesture
{
    [self setNeedsDisplay];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.type == kToggleButtonType) self.value = 1.f - self.value;
    else if (self.type == kPushButtonType) self.value = 0.f;
    [self setNeedsDisplay];
}

#pragma mark -
#pragma mark Drawing

- (void)drawRect:(CGRect)rect
{
    if (self.hideOnGUI) return;
    
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGRect boundsRect = self.bounds;
	const CGFloat* colorComponents = CGColorGetComponents(self.color.CGColor);
	UIColor* backgroundColor;
    
    // Tab buttons in gray
    if (self.type == kTabItemButtonType)
    {
        if (self.value == 0.f)
        {
            backgroundColor = [UIColor colorWithRed:0.1f
                                              green:0.1f
                                               blue:0.1f
                                              alpha:1.f];
        }
        else
        {
            backgroundColor = [UIColor darkGrayColor];
        }
    }
    
    // Other buttons in color
    else
    {
        if (self.value == 0.f)
        {
            backgroundColor = [UIColor colorWithRed:colorComponents[0]
                                              green:colorComponents[1]
                                               blue:colorComponents[2]
                                              alpha:self.backgroundColorAlpha];
        }
        else
        {
            backgroundColor = [UIColor colorWithRed:colorComponents[0]
                                              green:colorComponents[1]
                                               blue:colorComponents[2]
                                              alpha:1.f];
        }
    }
    
	[backgroundColor set];
	[self context:context addRoundedRect:boundsRect cornerRadius:self.cornerRadius];
	CGContextFillPath(context);
    
    CGSize valueStringSize = [title sizeWithFont:self.labelFont];
    [self.labelColor set];
    [title drawInRect:CGRectMake(0 + (self.frame.size.width - valueStringSize.width) / 2,
                                 0 + (self.frame.size.height - valueStringSize.height) / 2,
                                 self.frame.size.width,
                                 self.frame.size.height)
                   withFont:self.labelFont
              lineBreakMode:UILineBreakModeTailTruncation];
    
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

@end
