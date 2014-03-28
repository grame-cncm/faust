//  Based on Paolo Boschini's FlatKnob.

#import "FaustAU_Knob.h"

#import <QuartzCore/QuartzCore.h>

@implementation FaustAU_FlatKnob

- (id)initWithFrame:(NSRect)frame
{
    return [self initWithFrame:(NSRect)frame
                withInsets:INSETS
                withControlPointDiameter:CONTROL_POINT_DIAMETER
                withControlPointColor:[NSColor redColor]
                withKnobColor:[NSColor colorWithSRGBRed:0 green:0.4 blue:1 alpha:1]
                withBackgroundColor:[NSColor blackColor]
                withCurrentAngle:225];
}

- (id)initWithFrame:(NSRect)frame withInsets:(int)_insets
        withControlPointDiameter:(int)_controlPointDiameter
        withControlPointColor:(NSColor*)_controlPointColor
        withKnobColor:(NSColor*)_knobColor
        withBackgroundColor:(NSColor*)_backgroundColor
        withCurrentAngle:(int)_currentAngle;

{
    self = [super initWithFrame:frame];
    if (self)
    {
        backgroundColor = _backgroundColor;
        knobColor = _knobColor;
        insets = _insets;
        
        [self setWantsLayer:YES];
        self.layer.backgroundColor = backgroundColor.CGColor;
        self.layer.cornerRadius = 15;
        
        NSRect rect = NSMakeRect(0, 0, self.frame.size.width, self.frame.size.height);
        self->controlPoint = [[FaustAU_ControlPoint alloc] initWithFrame:rect
                                                    withInsets:insets
                                                    withControlPointDiameter:_controlPointDiameter
                                                    withControlPointColor:_controlPointColor
                                                    withCurrentAngle:_currentAngle];
        [self addSubview:self->controlPoint];
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    NSBezierPath *fillCircle;
    NSRect rect;
    
    int i;
    for (i = 0; i < 5; ++i)
    {
        rect = NSMakeRect(insets+i,
                          insets+i,
                          self.bounds.size.width - (insets*2 + i*2),
                          self.bounds.size.height - (insets*2 + i*2));
        fillCircle = [NSBezierPath bezierPathWithOvalInRect:rect];
        [[knobColor colorWithAlphaComponent:i * 0.1 + 0.3] setFill];
        [fillCircle fill];
    }
    
    rect = NSMakeRect(insets+i,
                      insets+i,
                      self.bounds.size.width - (insets*2 + i*2),
                      self.bounds.size.height - (insets*2 + i*2));
    fillCircle = [NSBezierPath bezierPathWithOvalInRect:rect];
    [[knobColor colorWithAlphaComponent:1] setFill];
    [fillCircle fill];
}

@end

/**********************************************************************************/

@implementation FaustAU_ControlPoint

- (id)initWithFrame:(NSRect)frame withInsets:(int)_insets
    withControlPointDiameter:(int)_controlPointDiameter
    withControlPointColor:(NSColor*)_controlPointColor
    withCurrentAngle:(int)_currentAngle;

{
    self = [super initWithFrame:frame];
    if (self)
    {
        insets = _insets;
        controlPointDiameter = _controlPointDiameter;
        controlPointColor = _controlPointColor;
        currentDraggedAngle = currentAngle = _currentAngle;
        previousValue = 0;
    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    NSBezierPath *indicator;
    [[controlPointColor colorWithAlphaComponent:1] set];
    indicator = [NSBezierPath bezierPathWithOvalInRect:[self makeRectWithWidth:controlPointDiameter]];
    [indicator fill];
    
    [[controlPointColor colorWithAlphaComponent:0.5] set];
    indicator = [NSBezierPath bezierPathWithOvalInRect:[self makeRectWithWidth:controlPointDiameter+2]];
    [indicator fill];
    
    [[controlPointColor colorWithAlphaComponent:0.3] set];
    indicator = [NSBezierPath bezierPathWithOvalInRect:[self makeRectWithWidth:controlPointDiameter+4]];
    [indicator fill];
}

- (NSRect)makeRectWithWidth:(int)width
{
    double radians = currentDraggedAngle * M_PI / 180.0;
    int radius = (self.bounds.size.width/2 - insets);
    return NSMakeRect(cos(radians)*radius + self.bounds.size.width/2 - width/2,
                      sin(radians)*radius + self.bounds.size.height/2 - width/2,
                      width,
                      width);
}

#pragma mark Control
- (void)mouseDown:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    mouseDownPosition = (int)local_point.y;
}

- (void)mouseUp:(NSEvent *)theEvent
{
    currentAngle = currentDraggedAngle;
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    [self updateWithYcoord:theEvent];
}

- (void)updateWithYcoord:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    currentDraggedAngle = mouseDownPosition - (int)local_point.y + currentAngle;
    
    if (currentDraggedAngle > 225) currentDraggedAngle = 225;
    if (currentDraggedAngle < -45) currentDraggedAngle = -45;
    
    float currentValuePosition = (225.0 - currentDraggedAngle);
    value = (currentValuePosition / 270.0) * (self->data.count-1);
    
    if (value != previousValue)
    {
        previousValue = value;
        
        double val = [[self->data objectAtIndex:value] doubleValue]; //TODO
        [self->delegate knobUpdatedWithIndex:value
                                   withValue:val
                                  withObject:[self superview]];
        
        currentDraggedAngle = 225.0 - ((270.0 / (self->data.count-1)) * value);
        [self setNeedsDisplay:YES];
    }
}

- (BOOL)mouseDownCanMoveWindow
{
    return NO;
}

@end

/**********************************************************************************/


@implementation FaustAU_Knob

@synthesize labelTextField =_labelTextField;
@synthesize valueTextField =_valueTextField;

- (void)setDoubleValue:(double)aDouble //TODO
{
    //TODO controlPoint->value = aDouble;
    NSString *stringValue = [NSString stringWithFormat:@"%9.2f", aDouble]; //TODO
    [_valueTextField setStringValue:stringValue]; //TODO
}

- (double)doubleValue
{
    return [[self->controlPoint->data objectAtIndex:self->controlPoint->value] doubleValue]; //TODO
}


@end