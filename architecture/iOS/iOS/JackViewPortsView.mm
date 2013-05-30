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
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
        
    portsView.linking = NO;
        
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        portsView.srcPt = CGPointMake([touch locationInView:portsView].x, [touch locationInView:portsView].y);
    }
    
    [portsView setNeedsDisplay];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview);
        
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
        
    JackView* jackView = portsView.clientButton.jackView;

    jackView.linking = NO;
    [jackView setNeedsDisplay];
    
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    NSString* dstAppPortName = nil;
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        JackViewPortsViewItem* item = [portsView itemAtPoint:CGPointMake([touch locationInView:portsView].x,
                                                                         [touch locationInView:portsView].y)];

        if (item)
        {
            // Connect new link
            dstAppPortName = item.longName;
            
            [jackView connectPort:self.longName withPort:dstAppPortName];
            [jackView connectPort:dstAppPortName withPort:self.longName];
            
            self.selected = YES;
            [self setNeedsDisplay];
            
            portsView.clientButton.selected = YES;
        }            
    }
    
    portsView.linking = NO;
    [portsView refreshLinks];
    [portsView setNeedsDisplay];
    [jackView setNeedsDisplay];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview);
        
    portsView.linking = NO;
    [portsView refreshLinks];
    [portsView setNeedsDisplay];
}

@end


@implementation JackViewPortsLink

@synthesize srcPt;
@synthesize dstPt;
@synthesize srcName;
@synthesize dstName;
@synthesize selected;

- (id)init
{
    self = [super init];
    if (self)
    {
        self.srcPt = CGPointMake(0., 0.);
        self.dstPt = CGPointMake(0., 0.);
        self.srcName = nil;
        self.dstName = nil;
        self.selected = NO;
    }
    return self;
}

- (void)dealloc
{
    [self.srcName release];
    [self.dstName release];
    [super dealloc];
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
        _links = [[NSMutableArray alloc] initWithCapacity:0];
        _tapRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleTap:)];
        _tapRecognizer.numberOfTapsRequired = 1;
        [self addGestureRecognizer:_tapRecognizer];
        _deleteButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_deleteButton setTitle:@"X" forState:UIControlStateNormal];
        [_deleteButton setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
        [_deleteButton setFrame:CGRectMake(0, 0, 20, 20)];
        _deleteButton.showsTouchWhenHighlighted = YES;
        _deleteButton.hidden = YES;
        [_deleteButton addTarget:self action:@selector(deleteSelectedLink) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:_deleteButton];
    }
    return self;
}

- (void)dealloc
{
    [_links release];
    [super dealloc];
}

- (float)computeXOffsetWithXItems:(float)xItems xIcon:(float)xIcon
{
    float xOffset = 0.;
    
    if (xItems + kPortsViewItemWidth <= xIcon)                          xOffset = kPortsViewItemWidth - kPortsViewArrowWidth;
    else if (xItems <= xIcon && xItems + kPortsViewItemWidth >= xIcon)  xOffset = xIcon - xItems;
    else if (xItems == xIcon)                                       xOffset = 0;
    
    return xOffset;
}

- (void)drawRect:(CGRect)rect
{
    int i = 0;
    JackView* jackView = self.clientButton.jackView;
    float xItems = 0.;
    float xIcon = 0.;
    float xOffset = 0.;
    
    // Background
    self.backgroundColor = [UIColor clearColor];
    
    [[UIColor darkGrayColor] set];
    UIRectFill(CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height - kPortsViewArrowHeight));
    
    // Ports
    for (i = 0; i < [[self subviews] count]; ++i)
    {
        [[[self subviews] objectAtIndex:i] setNeedsDisplay];
    }
    
    // Client arrow
    xItems = clientX;
    xIcon = [clientButton convertPoint:CGPointMake(0, 0) toView:self].x;
    
    xOffset = [self computeXOffsetWithXItems:xItems xIcon:xIcon];
    
    [[UIColor darkGrayColor] set];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextBeginPath(context);
    CGContextMoveToPoint(context,
                         clientX + xOffset,
                         self.frame.size.height - kPortsViewArrowHeight);
    CGContextAddLineToPoint(context,
                            fmin(clientX + kPortsViewArrowWidth + xOffset, clientX + kPortsViewItemWidth),
                            self.frame.size.height - kPortsViewArrowHeight);
    CGContextAddLineToPoint(context,
                            [clientButton convertPoint:CGPointMake(0, 0) toView:self].x,
                            self.frame.size.height);
    CGContextClosePath(context);
    
    CGContextFillPath(context);
    
    // Current app arrow
    xItems = currentAppX;
    xIcon = jackView.currentClientButton.frame.origin.x;
    
    xOffset = [self computeXOffsetWithXItems:xItems xIcon:xIcon];
    
    [[UIColor darkGrayColor] set];
    CGContextBeginPath(context);
    CGContextMoveToPoint(context,
                         currentAppX + xOffset,
                         self.frame.size.height - kPortsViewArrowHeight);
    CGContextAddLineToPoint(context,
                            fmin(currentAppX + kPortsViewArrowWidth + xOffset, currentAppX + kPortsViewItemWidth),
                            self.frame.size.height - kPortsViewArrowHeight);
    CGContextAddLineToPoint(context,
                            jackView.currentClientButton.frame.origin.x,
                            self.frame.size.height);
    CGContextClosePath(context);
    
    CGContextFillPath(context);
        
    // Links
    JackViewPortsLink* link = nil;
    
    for (i = 0; i < [_links count]; ++i)
    {
        link = [_links objectAtIndex:i];
        
        if (linking) link.selected = NO;
        
        CGContextRef c = UIGraphicsGetCurrentContext();
        
        if (link.selected)
        {
            [[UIColor redColor] set];
            _deleteButton.hidden = NO;
        }
        else [[UIColor whiteColor] set];
        
        CGContextBeginPath(c);
        CGContextMoveToPoint(c, link.srcPt.x, link.srcPt.y);
        CGContextAddLineToPoint(c, link.dstPt.x, link.dstPt.y);
        CGContextStrokePath(c);
    }
    
    if (self.linking)
    {
        _deleteButton.hidden = YES;
        
        CGContextRef c = UIGraphicsGetCurrentContext();
        
        [[UIColor whiteColor] set];
        
        CGContextBeginPath(c);
        CGContextMoveToPoint(c, self.srcPt.x, self.srcPt.y);
        CGContextAddLineToPoint(c, self.dstPt.x, self.dstPt.y);
        CGContextStrokePath(c);
    }
}

- (void)refreshLinks
{
    // Links
    int i = 0;
    int j = 0;
    int k = 0;
    NSArray* buttons = [self subviews];
    JackViewPortsViewItem* srcItem = nil;
    JackViewPortsViewItem* dstItem = nil;
    JackView* jackView = self.clientButton.jackView;
    CGPoint tmpSrcPt;
    CGPoint tmpDstPt;
    NSString* srcName = nil;
    NSString* dstName = nil;
    NSArray* dstArray = nil;

    [_links removeAllObjects];
    _deleteButton.hidden = YES;
    
    for (i = 0; i < [buttons count]; ++i)
    {
        srcItem = ((JackViewPortsViewItem*)([buttons objectAtIndex:i]));
        if ([srcItem isKindOfClass:[JackViewPortsViewItem class]] && srcItem.frame.origin.x == clientX)
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
                            dstName = [[NSString alloc] initWithFormat:@"%@", (NSString*)[dstArray objectAtIndex:k]];
                            
                            if ([dstItem.longName compare:dstName] == NSOrderedSame)
                            {
                                tmpDstPt = CGPointMake(dstItem.frame.origin.x + dstItem.frame.size.width / 2.,
                                                       dstItem.frame.origin.y + dstItem.frame.size.height / 2.);
                                
                                JackViewPortsLink* link = [[JackViewPortsLink alloc] init];
                                link.srcPt = CGPointMake(tmpSrcPt.x, tmpSrcPt.y);
                                link.dstPt = CGPointMake(tmpDstPt.x, tmpDstPt.y);
                                link.srcName = srcName;
                                link.dstName = dstName;
                                [_links addObject:link];
                            }
                        }
                    }
                }
            }
        }
    }
}

- (void)deleteSelectedLink
{
    int i = 0;
    JackViewPortsLink* link = nil;
    JackView* jackView = self.clientButton.jackView;
    
    for (i = 0; i < [_links count]; ++i)
    {
        link = [_links objectAtIndex:i];

        if (link.selected)
        {
            [clientButton.jackView disconnectPort:link.srcName withPort:link.dstName];
            [clientButton.jackView disconnectPort:link.dstName withPort:link.srcName];
            
            clientButton.selected = [jackView isClient:clientButton.jackViewClient connectedToCurrentClientInputOutput:clientButton.inputOutput audioMidi:clientButton.audioMidi];
        }
    }
    
    _deleteButton.hidden = YES;
    [self refreshLinks];
    [self setNeedsDisplay];
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

- (void)singleTap:(UIGestureRecognizer *)gestureRecognizer
{
    CGPoint pt = [gestureRecognizer locationInView:self];
    float a = 0.f;
    float b = 0.f;
    float c = 0.f;
    float m = 0.f;
    float p = 0.f;
    JackViewPortsLink* link = nil;
    int i = 0;
    int minLinkIndex = -1;
    float dist = 0.;
    float minDist = 100000.;
    
    _deleteButton.hidden = YES;
    
    // Look for nearest link
    for (i = 0; i < [_links count]; ++i)
    {
        link = [_links objectAtIndex:i];
        link.selected = NO;
        
        if (pt.x > fminf(link.srcPt.x, link.dstPt.x)
            && pt.x < fmaxf(link.srcPt.x, link.dstPt.x))
        {
            // Compute link equation : y = mx + p
            m = (link.dstPt.y - link.srcPt.y) / (link.dstPt.x - link.srcPt.x);
            p = link.srcPt.y - m * link.srcPt.x;
            
            // Convert link equation to ax + by + c = 0
            b = 1.;
            a = -m;
            c = -p;
            
            // Compute distance from pt to line
            dist = fabsf(a * pt.x + b * pt.y + c) / sqrt(a * a + b * b);
            
            if (dist <= 10)
            {
                // Compare distance with min distance
                minDist = fminf(minDist, dist);
                
                // If this current link is the nearest, keep its index
                if (minDist == dist)
                {
                    minLinkIndex = i;
                }
            }
        }
    }
    
    if (minLinkIndex != -1)
    {
        float x = 0.f;
        float y = 0.f;
        
        link = [_links objectAtIndex:minLinkIndex];
        link.selected = YES;
        
        x = fmaxf(link.dstPt.x, link.srcPt.x);
        if (x == link.dstPt.x) y = link.dstPt.y;
        else y = link.srcPt.y;
        
        [_deleteButton setFrame:CGRectMake(x - 70, (y - 20) * 0.8 + (y - 20) * 0.2, 20, 20)];
        //_deleteButton.hidden = NO;
    }
    
    [self setNeedsDisplay];
}

@end
