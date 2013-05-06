//
//  JackViewPortsView.m
//  iOS
//
//  Created by Olivier Guillerminet on 29/04/13.
//
//

#import "JackViewPortsView.h"
#import "JackView.h"


@implementation JackViewPortsViewItem

@synthesize longName;
@synthesize alias;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.backgroundColor = [UIColor darkGrayColor];
        self.longName = nil;
        self.alias = nil;
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{    
    if (self.longName)
    {
        [[UIColor whiteColor] set];
    
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGContextSetShadow(context, CGSizeMake(1.0f, 1.0f), 5.0f);
    
        [[[self.longName componentsSeparatedByString:@":"] objectAtIndex:1] drawAtPoint:CGPointMake(1.0f, 14.f)
                                                                               withFont:[UIFont boldSystemFontOfSize:16.0f]];
    }
    
    // Draw selection
    //if (self.selected)
    {
        UIBezierPath* path = [UIBezierPath bezierPath];
        
        [[UIColor blackColor] set];
        
        [path moveToPoint:CGPointMake(rect.origin.x, rect.origin.y + 2)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + 2)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height - 2)];
        [path addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height - 2)];
        [path closePath];
        path.lineWidth = 2;
        [path strokeWithBlendMode:kCGBlendModeNormal alpha:1.];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview);
    //JackView* jackView = portsView.clientButton.jackView;
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    
    if (self.frame.origin.x == portsView.currentAppX) return;
    
    portsView.linking = YES;
        
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        portsView.srcPt = CGPointMake([touch locationInView:portsView].x, [touch locationInView:portsView].y);
    }
    
    [portsView setNeedsDisplay];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview);
    
    if (self.frame.origin.x == portsView.currentAppX) return;
    
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    
    portsView.linking = YES;
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        portsView.dstPt = CGPointMake([touch locationInView:portsView].x, [touch locationInView:portsView].y);
    }

    [portsView setNeedsDisplay];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview);
    
    if (self.frame.origin.x == portsView.currentAppX) return;
    
    JackView* jackView = portsView.clientButton.jackView;

    jackView.linking = NO;
    [jackView setNeedsDisplay];
    
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    NSString* currentAppPortName = nil;
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        JackViewPortsViewItem* item = [portsView itemAtPoint:CGPointMake([touch locationInView:portsView].x,
                                                                         [touch locationInView:portsView].y)];

        if (item)
        {
            // Connect new link
            currentAppPortName = item.longName;
            
            if (currentAppPortName && portsView.clientButton.inputOutput == 1)
            {
                [jackView connectPort:self.longName withPort:currentAppPortName];
            }
            else if (currentAppPortName && portsView.clientButton.inputOutput == 2)
            {
                [jackView disconnectPort:currentAppPortName withPort:self.longName];
            }
            
            self.selected = YES;
            [self setNeedsDisplay];
            
            portsView.clientButton.selected = YES;
        }            
    }
    
    portsView.linking = NO;
    [portsView setNeedsDisplay];
    [jackView setNeedsDisplay];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview);
    
    if (self.frame.origin.x == portsView.currentAppX) return;
    
    portsView.linking = NO;
    [portsView setNeedsDisplay];
}

@end


@implementation JackViewPortsView

@synthesize clientButton;
@synthesize clientX;
@synthesize currentAppX;
@synthesize linking;
@synthesize srcPt;
@synthesize dstPt;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.backgroundColor = [UIColor clearColor];
        self.clientButton = nil;
        self.clientX = 0.;
        self.currentAppX = 0.;
        self.linking = NO;
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{
    int i = 0;
    
    // Background
    self.backgroundColor = [UIColor clearColor];
    [[UIColor darkGrayColor] set];
    UIRectFill(CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height - kPortsArrowHeight));
    
    // Ports
    for (i = 0; i < [[self subviews] count]; ++i)
    {
        [[[self subviews] objectAtIndex:i] setNeedsDisplay];
    }
    
    // Client arrow
    [[UIColor darkGrayColor] set];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context,
                         clientX,
                         [[self subviews] count] * kPortsViewItemHeight);
    CGContextAddLineToPoint(context,
                            clientX + kPortsViewArrowWidth,
                            [[self subviews] count] * kPortsViewItemHeight);
    CGContextAddLineToPoint(context,
                            clientX + kPortsViewArrowWidth / 2.,
                            rect.size.height);
    CGContextClosePath(context);
    
    CGContextFillPath(context);
    
    CGContextRestoreGState(context);
    
    
    // Current app arrow
    [[UIColor darkGrayColor] set];
    context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    CGContextMoveToPoint(context,
                         currentAppX,
                         [[self subviews] count] * kPortsViewItemHeight);
    CGContextAddLineToPoint(context,
                            currentAppX + kPortsViewArrowWidth,
                            [[self subviews] count] * kPortsViewItemHeight);
    CGContextAddLineToPoint(context,
                            currentAppX + kPortsViewArrowWidth / 2.,
                            rect.size.height);
    CGContextClosePath(context);
    
    CGContextFillPath(context);
    
    CGContextRestoreGState(context);
    
    // Links
    NSArray* buttons = [self subviews];
    JackViewPortsViewItem* srcItem = nil;
    JackViewPortsViewItem* dstItem = nil;
    JackView* jackView = self.clientButton.jackView;
    CGPoint tmpSrcPt;
    CGPoint tmpDstPt;
    int j = 0;
    NSString* srcName = nil;
    NSString* dstName = nil;
    NSArray* dstArray = nil;
    int k = 0;
        
    for (i = 0; i < [buttons count]; ++i)
    {
        srcItem = (JackViewPortsViewItem*)[buttons objectAtIndex:i];
        if (srcItem.frame.origin.x == clientX)
        {
            if ([jackView isPort:[jackView portWithName:srcItem.longName] connectedToCurrentClientInputOutput:self.clientButton.inputOutput audioMidi:self.clientButton.audioMidi])
            {
                srcName = srcItem.longName;
                tmpSrcPt = CGPointMake(srcItem.frame.origin.x + srcItem.frame.size.width / 2.,
                                    srcItem.frame.origin.y + srcItem.frame.size.height / 2.);
                
                dstArray = [jackView getCurrentClientPortConnectedTo:srcName];
               
                for (j = 0; j < [buttons count]; ++j)
                {
                    dstItem = (JackViewPortsViewItem*)[buttons objectAtIndex:j];
                    
                    if (dstItem.frame.origin.x == currentAppX)
                    {
                        for (k = 0; k < [dstArray count]; ++k)
                        {
                            dstName = (NSString*)[dstArray objectAtIndex:k];
                            
                            if ([dstItem.longName compare:dstName] == NSOrderedSame)
                            {
                                tmpDstPt = CGPointMake(dstItem.frame.origin.x + dstItem.frame.size.width / 2.,
                                                       dstItem.frame.origin.y + dstItem.frame.size.height / 2.);
                                
                                CGContextRef c = UIGraphicsGetCurrentContext();
                                
                                CGFloat color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
                                CGContextSetStrokeColor(c, color);
                                CGContextBeginPath(c);
                                CGContextMoveToPoint(c, tmpSrcPt.x, tmpSrcPt.y);
                                CGContextAddLineToPoint(c, tmpDstPt.x, tmpDstPt.y);
                                CGContextStrokePath(c);
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (self.linking)
    {        
        CGContextRef c = UIGraphicsGetCurrentContext();
        
        CGFloat color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        CGContextSetStrokeColor(c, color);
        CGContextBeginPath(c);
        CGContextMoveToPoint(c, self.srcPt.x, self.srcPt.y);
        CGContextAddLineToPoint(c, self.dstPt.x, self.dstPt.y);
        CGContextStrokePath(c);
    }
}

- (JackViewPortsViewItem*)itemAtPoint:(CGPoint)pt
{
    NSArray* items = [self subviews];
    JackViewPortsViewItem* item = nil;
    int i = 0;
    
    for (i = 0; i < [items count]; ++i)
    {
        item = (JackViewPortsViewItem*)[items objectAtIndex:i];
        if (pt.x >= item.frame.origin.x
            && pt.x <= item.frame.origin.x +item.frame.size.width
            && pt.y >= item.frame.origin.y
            && pt.y <= item.frame.origin.y +item.frame.size.height)
        {
            return item;
        }
    }
    
    return nil;
}

@end
