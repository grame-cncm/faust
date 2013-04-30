//
//  JackViewPortsView.m
//  iOS
//
//  Created by Olivier Guillerminet on 29/04/13.
//
//

#import "JackViewPortsView.h"


@implementation JackViewPortsViewItem

@synthesize longName;
@synthesize shortName;
@synthesize alias;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.backgroundColor = [UIColor darkGrayColor];
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{    
    NSString *string = self.shortName;
    
    [[UIColor whiteColor] set];
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetShadow(context, CGSizeMake(1.0f, 1.0f), 5.0f);
    
    [string drawAtPoint:CGPointMake(0.0f, 0.0f) withFont:[UIFont boldSystemFontOfSize:16.0f]];
    
    // Draw selection
    if (self.selected)
    {
        UIBezierPath* path = [UIBezierPath bezierPath];
        
        [[UIColor whiteColor] set];
        
        [path moveToPoint:CGPointMake(rect.origin.x, rect.origin.y)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height)];
        [path addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height)];
        [path closePath];
        path.lineWidth = 2;
        [path strokeWithBlendMode:kCGBlendModeNormal alpha:1.];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesBegan");
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesMoved");
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesEnded");
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesCancelled");
}

@end


@implementation JackViewPortsView

@synthesize ports;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.backgroundColor = [UIColor clearColor];
        self.clientButton = nil;
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{
    int i = 0;
    
    // Ports
    for (i = 0; i < [[self subviews] count]; ++i)
    {
        [[[self subviews] objectAtIndex:i] setNeedsDisplay];
    }
    
    // Arrow
    [[UIColor darkGrayColor] set];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context,
                         0.,
                         [[self subviews] count] * kPortsViewItemHeight);
    CGContextAddLineToPoint(context,
                            kPortsViewArrowWidth,
                            [[self subviews] count] * kPortsViewItemHeight);
    CGContextAddLineToPoint(context,
                            kPortsViewArrowWidth / 2.,
                            rect.size.height);
    CGContextClosePath(context);
    
    CGContextFillPath(context);
    
    CGContextRestoreGState(context);
    
}

@end
