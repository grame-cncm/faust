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
    UIBezierPath* path = [UIBezierPath bezierPath];
    CGPoint pt;
    
    path.lineWidth = 1.5;
    path.lineCapStyle = kCGLineCapSquare;
    
    // Background
    self.backgroundColor = [UIColor clearColor];
    
    float cst = 0.4;
    
    // Links
    for (i = 0; i < [portsView.links count]; ++i)
    {
        link = [portsView.links objectAtIndex:i];
        
        if (portsView.linking) link.selected = NO;
                
        if (link.selected)
        {
            [[UIColor blueColor] set];
            portsView.deleteButton.hidden = NO;
        }
        else [[UIColor blackColor] set];
        
        [path removeAllPoints];
        [path moveToPoint:CGPointMake(link.srcPt.x - 5, link.srcPt.y)];
        [path addCurveToPoint:CGPointMake(link.dstPt.x - 5, link.dstPt.y)
                controlPoint1:CGPointMake((link.srcPt.x * cst + link.dstPt.x * (1. - cst)), link.srcPt.y)
                controlPoint2:CGPointMake((link.srcPt.x * (1. - cst) + link.dstPt.x * cst), link.dstPt.y)];
        [path stroke];
        
        // Arrow
        if (link.srcPt.x < link.dstPt.x) pt = CGPointMake(link.dstPt.x, link.dstPt.y);
        else pt = CGPointMake(link.srcPt.x, link.srcPt.y);
        [path removeAllPoints];
        [path moveToPoint:CGPointMake(pt.x - 10, pt.y - 2.5)];
        [path addLineToPoint:CGPointMake(pt.x, pt.y)];
        [path addLineToPoint:CGPointMake(pt.x - 10, pt.y + 2.5)];
        [path closePath];
        [path fill];
    }
    
    if (portsView.linking
        && !portsView.dontDrawLinking)
    {
        portsView.deleteButton.hidden = YES;
                
        [[UIColor blackColor] set];
        
        [path removeAllPoints];
        [path moveToPoint:CGPointMake(portsView.srcPt.x - 5, portsView.srcPt.y)];
        [path addCurveToPoint:CGPointMake(portsView.dstPt.x - 5, portsView.dstPt.y)
                controlPoint1:CGPointMake((portsView.srcPt.x * cst + portsView.dstPt.x * (1. - cst)), portsView.srcPt.y)
                controlPoint2:CGPointMake((portsView.srcPt.x * (1. - cst) + portsView.dstPt.x * cst), portsView.dstPt.y)];
        [path stroke];
        
        // Arrow
        if (portsView.srcPt.x < portsView.dstPt.x) pt = CGPointMake(portsView.dstPt.x, portsView.dstPt.y);
        else pt = CGPointMake(portsView.srcPt.x, portsView.srcPt.y);
        [path removeAllPoints];
        [path moveToPoint:CGPointMake(pt.x - 10, pt.y - 2.5)];
        [path addLineToPoint:CGPointMake(pt.x, pt.y)];
        [path addLineToPoint:CGPointMake(pt.x - 10, pt.y + 2.5)];
        [path closePath];
        [path fill];
    }
}


@end
