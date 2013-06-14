//
//  JackViewPortsViewBackgroundView.m
//  iOS
//
//  Created by Olivier Guillerminet on 13/06/13.
//
//

#import "JackViewPortsViewBackgroundView.h"
#import "JackViewPortsView.h"

@implementation JackViewPortsViewBackgroundView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.backgroundColor = [UIColor clearColor];
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{
    int i = 0;
    JackViewPortsView* portsView = (JackViewPortsView*)self.superview.superview;
    JackViewPortsLink* link = nil;
        
    // Background
    self.backgroundColor = [UIColor clearColor];
        
    // Links
    for (i = 0; i < [portsView.links count]; ++i)
    {
        link = [portsView.links objectAtIndex:i];
        
        if (portsView.linking) link.selected = NO;
        
        CGContextRef c = UIGraphicsGetCurrentContext();
        
        if (link.selected)
        {
            [[UIColor redColor] set];
            portsView.deleteButton.hidden = NO;
        }
        else [[UIColor whiteColor] set];
        
        CGContextBeginPath(c);
        CGContextMoveToPoint(c, link.srcPt.x, link.srcPt.y);
        CGContextAddLineToPoint(c, link.dstPt.x, link.dstPt.y);
        CGContextStrokePath(c);
    }
    
    if (portsView.linking)
    {
        portsView.deleteButton.hidden = YES;
        
        CGContextRef c = UIGraphicsGetCurrentContext();
        
        [[UIColor whiteColor] set];
        
        CGContextBeginPath(c);
        CGContextMoveToPoint(c, portsView.srcPt.x, portsView.srcPt.y);
        CGContextAddLineToPoint(c, portsView.dstPt.x, portsView.dstPt.y);
        CGContextStrokePath(c);
    }
}


@end
