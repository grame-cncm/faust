/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
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
              lineBreakMode:NSLineBreakByTruncatingTail];
    
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
