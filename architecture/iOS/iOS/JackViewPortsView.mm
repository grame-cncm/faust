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
@synthesize touching;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.backgroundColor = [UIColor clearColor];
        self.longName = nil;
        self.touching = NO;
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{
    self.backgroundColor = [UIColor clearColor];

    // Draw selection
    //if (self.selected)
    {
        UIBezierPath* path = [UIBezierPath bezierPathWithRoundedRect:CGRectMake(rect.origin.x + 1.,
                                                                                rect.origin.y + 5.,
                                                                                rect.size.width - 2.,
                                                                                rect.size.height - 10.)
                                                        cornerRadius:10.];
        path.lineWidth = 1.5;
        
        /*[path moveToPoint:CGPointMake(rect.origin.x, rect.origin.y + 1)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + 1)];
        [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height - 1)];
        [path addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height - 1)];
        [path closePath];*/
        
        [[UIColor colorWithWhite:0.8 alpha:1.] set];
        [path fillWithBlendMode:kCGBlendModeNormal alpha:1.];
        
        [[UIColor blackColor] set];
        [path strokeWithBlendMode:kCGBlendModeNormal alpha:1.];
    }
    
    if (self.longName)
    {
        UIFont* font = [UIFont systemFontOfSize:16.0f];
        NSString* str = [[self.longName componentsSeparatedByString:@":"] objectAtIndex:1];
        CGSize stringBoundingBox = [str sizeWithFont:font];
        [[UIColor blackColor] set];
        
        [str drawAtPoint:CGPointMake((rect.size.width - stringBoundingBox.width) / 2., 14.f)
                withFont:font];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview.superview);
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    
    if ([touches count] == 1)
    {
        portsView.dontDrawLinking = NO;
    }
    
    portsView.linking = NO;
    self.touching = YES;
    
    [portsView connectIfTouchingTwoItems];
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        if (self.frame.origin.x == fminf(portsView.clientX, portsView.currentAppX))
        {
            portsView.srcPt = CGPointMake(self.frame.origin.x + self.frame.size.width, self.frame.origin.y + self.frame.size.height / 2.);
        }
        else
        {
            portsView.srcPt = CGPointMake(self.frame.origin.x, self.frame.origin.y + self.frame.size.height / 2.);
        }
    }
    
    [portsView setNeedsDisplay];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview.superview);
        
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    
    self.touching = YES;
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        if ([touch locationInView:self].x < self.frame.origin.x
            || [touch locationInView:self].x > self.frame.origin.x + self.frame.size.width
            || [touch locationInView:self].y < self.frame.origin.y
            || [touch locationInView:self].y > self.frame.origin.y + self.frame.size.height)
        {
            portsView.linking = YES;
            portsView.dstPt = CGPointMake([touch locationInView:portsView.backgroundView].x, [touch locationInView:portsView.backgroundView].y);
            [portsView refreshScrollViewOffset:[touch locationInView:portsView.backgroundView].y];
        }
    }

    [portsView setNeedsDisplay];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview.superview);
    JackView* jackView = portsView.clientButton.jackView;
    
    [jackView setNeedsDisplay];
    
    NSEnumerator* enumerator = [touches objectEnumerator];
    UITouch* touch;
    NSString* dstAppPortName = nil;
    if ([touches count] == 1)
    {
        self.touching = NO;
    }
    
    while ((touch = (UITouch*)[enumerator nextObject]))
    {
        JackViewPortsViewItem* item = [portsView itemAtPoint:CGPointMake([touch locationInView:portsView.backgroundView].x,
                                                                         [touch locationInView:portsView.backgroundView].y)];

        if (item && [item isKindOfClass:[JackViewPortsViewItem class]])
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
    JackViewPortsView* portsView = (JackViewPortsView*)(self.superview.superview);
    
    portsView.linking = NO;
    self.touching = NO;
    
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
@synthesize backgroundView;
@synthesize links;
@synthesize deleteButton;
@synthesize dontDrawLinking;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        // Add scroll view
        _scrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0,
                                                                     0,
                                                                     frame.size.width,
                                                                     frame.size.height - kPortsViewFSButtonHeight - kPortsViewArrowHeight)];
        [self addSubview:_scrollView];
        
        // Add background view in scroll view
        self.backgroundView = [[JackViewPortsViewBackgroundView alloc] initWithFrame:_scrollView.frame];
        [_scrollView addSubview:self.backgroundView];
        
        self.backgroundColor = [UIColor clearColor];
        self.clientButton = nil;
        self.clientX = 0.;
        self.currentAppX = 0.;
        self.linking = NO;
        self.dontDrawLinking = NO;
        self.links = [[NSMutableArray alloc] initWithCapacity:0];
        _tapRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleTap:)];
        _tapRecognizer.numberOfTapsRequired = 1;
        [self addGestureRecognizer:_tapRecognizer];
        self.deleteButton = [UIButton buttonWithType:UIButtonTypeCustom];
        //[self.deleteButton setTitle:@"X" forState:UIControlStateNormal];
        [self.deleteButton setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Icon-Delete" ofType:@"png"]] forState:UIControlStateNormal];
        [self.deleteButton setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
        [self.deleteButton setFrame:CGRectMake(0, 0, 20, 20)];
        self.deleteButton.showsTouchWhenHighlighted = YES;
        self.deleteButton.hidden = YES;
        [self.deleteButton addTarget:self action:@selector(deleteSelectedLink) forControlEvents:UIControlEventTouchUpInside];
        [_scrollView addSubview:self.deleteButton];
    }
    return self;
}

- (void)dealloc
{
    [self.links release];
    [_scrollView release];
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
    CGContextRef context;
    UIBezierPath* path = [UIBezierPath bezierPath];

    // Background
    self.backgroundColor = [UIColor clearColor];
        
    [[UIColor colorWithWhite:0.8 alpha:0.95] set];
    
    [path moveToPoint:CGPointMake(rect.origin.x, rect.origin.y)];
    [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y)];
    [path addLineToPoint:CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height - kPortsViewArrowHeight)];
    [path addLineToPoint:CGPointMake(rect.origin.x, rect.origin.y + rect.size.height - kPortsViewArrowHeight)];
    [path closePath];
    [path fillWithBlendMode:kCGBlendModeNormal alpha:1.];
        
    // Ports
    for (i = 0; i < [[self subviews] count]; ++i)
    {
        [[[self subviews] objectAtIndex:i] setNeedsDisplay];
    }
        
    // Client arrow
    xItems = clientX;
    xIcon = [clientButton convertPoint:CGPointMake(0, 0) toView:self].x;
    
    xOffset = [self computeXOffsetWithXItems:xItems xIcon:xIcon];
    
    context = UIGraphicsGetCurrentContext();
    CGContextBeginPath(context);
    CGContextMoveToPoint(context,
                         clientX + xOffset,
                         self.frame.size.height - kPortsViewArrowHeight);
    CGContextAddLineToPoint(context,
                            fmin(clientX + kPortsViewArrowWidth + xOffset, clientX + kPortsViewItemWidth),
                            self.frame.size.height - kPortsViewArrowHeight);
    CGContextAddLineToPoint(context,
                            [clientButton convertPoint:CGPointMake(0, 0) toView:self].x + kPortsViewArrowWidth / 2.,
                            self.frame.size.height);
    CGContextClosePath(context);
    
    CGContextFillPath(context);
    
    // Current app arrow
    xItems = currentAppX;
    xIcon = jackView.currentClientButton.frame.origin.x;
    
    xOffset = [self computeXOffsetWithXItems:xItems xIcon:xIcon];
    
    CGContextBeginPath(context);
    CGContextMoveToPoint(context,
                         currentAppX + xOffset,
                         self.frame.size.height - kPortsViewArrowHeight);
    CGContextAddLineToPoint(context,
                            fmin(currentAppX + kPortsViewArrowWidth + xOffset, currentAppX + kPortsViewItemWidth),
                            self.frame.size.height - kPortsViewArrowHeight);
    CGContextAddLineToPoint(context,
                            jackView.currentClientButton.frame.origin.x + kPortsViewArrowWidth / 2.,
                            self.frame.size.height);
    CGContextClosePath(context);
    
    CGContextFillPath(context);
        
    // Links
    [self.backgroundView setNeedsDisplay];
}

- (void)refreshLinks
{
    // Links
    int i = 0;
    int j = 0;
    int k = 0;
    NSArray* buttons = [_scrollView subviews];
    JackViewPortsViewItem* srcItem = nil;
    JackViewPortsViewItem* dstItem = nil;
    JackView* jackView = self.clientButton.jackView;
    CGPoint tmpSrcPt;
    CGPoint tmpDstPt;
    NSString* srcName = nil;
    NSString* dstName = nil;
    NSArray* dstArray = nil;
    
    [self.links removeAllObjects];
    self.deleteButton.hidden = YES;
    
    for (i = 0; i < [buttons count]; ++i)
    {
        srcItem = ((JackViewPortsViewItem*)([buttons objectAtIndex:i]));
        if ([srcItem isKindOfClass:[JackViewPortsViewItem class]] && srcItem.frame.origin.x == clientX)
        {
            if ([jackView isPort:[jackView portWithName:srcItem.longName] connectedToCurrentClientInputOutput:self.clientButton.inputOutput audioMidi:self.clientButton.audioMidi])
            {
                srcName = srcItem.longName;
                
                if (srcItem.frame.origin.x == fminf(self.clientX, self.currentAppX))
                {
                    tmpSrcPt = CGPointMake(srcItem.frame.origin.x + srcItem.frame.size.width,
                                           srcItem.frame.origin.y + srcItem.frame.size.height / 2.);
                }
                else
                {
                    tmpSrcPt = CGPointMake(srcItem.frame.origin.x,
                                           srcItem.frame.origin.y + srcItem.frame.size.height / 2.);
                }
                
                dstArray = [jackView getCurrentClientPortConnectedTo:srcName];
                
                for (j = 0; j < [buttons count]; ++j)
                {
                    dstItem = (JackViewPortsViewItem*)[buttons objectAtIndex:j];
                    
                    if ([dstItem isKindOfClass:[JackViewPortsViewItem class]] && dstItem.frame.origin.x == currentAppX)
                    {
                        for (k = 0; k < [dstArray count]; ++k)
                        {
                            dstName = [[NSString alloc] initWithFormat:@"%@", (NSString*)[dstArray objectAtIndex:k]];
                            
                            if ([dstItem.longName compare:dstName] == NSOrderedSame)
                            {
                                if (dstItem.frame.origin.x == fminf(self.clientX, self.currentAppX))
                                {
                                    tmpDstPt = CGPointMake(dstItem.frame.origin.x + dstItem.frame.size.width,
                                                           dstItem.frame.origin.y + dstItem.frame.size.height / 2.);
                                }
                                else
                                {
                                    tmpDstPt = CGPointMake(dstItem.frame.origin.x,
                                                           dstItem.frame.origin.y + dstItem.frame.size.height / 2.);
                                }
                                
                                JackViewPortsLink* link = [[JackViewPortsLink alloc] init];
                                link.srcPt = CGPointMake(tmpSrcPt.x, tmpSrcPt.y);
                                link.dstPt = CGPointMake(tmpDstPt.x, tmpDstPt.y);
                                link.srcName = srcName;
                                link.dstName = dstName;
                                [self.links addObject:link];
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
    
    for (i = 0; i < [self.links count]; ++i)
    {
        link = [self.links objectAtIndex:i];

        if (link.selected)
        {
            [clientButton.jackView disconnectPort:link.srcName withPort:link.dstName];
            [clientButton.jackView disconnectPort:link.dstName withPort:link.srcName];
            
            clientButton.selected = [jackView isClient:clientButton.jackViewClient connectedToCurrentClientInputOutput:clientButton.inputOutput audioMidi:clientButton.audioMidi];
        }
    }
    
    self.deleteButton.hidden = YES;
    [self refreshLinks];
    [self setNeedsDisplay];
}

- (JackViewPortsViewItem*)itemAtPoint:(CGPoint)pt
{
    NSArray* items = [_scrollView subviews];
    JackViewPortsViewItem* item = nil;
    int i = 0;
    
    pt.y = pt.y;
    
    for (i = 0; i < [items count]; ++i)
    {
        item = (JackViewPortsViewItem*)[items objectAtIndex:i];
        if ([item isKindOfClass:[JackViewPortsViewItem class]]
            && pt.x >= item.frame.origin.x
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
    CGPoint pt = [gestureRecognizer locationInView:self.backgroundView];
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
    
    self.deleteButton.hidden = YES;
    
    // Look for nearest link
    for (i = 0; i < [self.links count]; ++i)
    {
        link = [self.links objectAtIndex:i];
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
        
        link = [self.links objectAtIndex:minLinkIndex];
        link.selected = YES;
        
        x = fmaxf(link.dstPt.x, link.srcPt.x);
        if (x == link.dstPt.x) y = link.dstPt.y;
        else y = link.srcPt.y;
        
        [self.deleteButton setFrame:CGRectMake(x - 30,
                                               (y - 20) * 0.8 + (y - 20) * 0.2,
                                               20,
                                               20)];
    }
    
    [self setNeedsDisplay];
}

- (void)setUtilHeight:(float)h
{
    [backgroundView setFrame:CGRectMake(0, 0, self.frame.size.width, h)];
    [_scrollView setContentSize:CGSizeMake(self.frame.size.width, h)];
}

- (void)addItem:(JackViewPortsViewItem*)item
{
    [_scrollView addSubview:item];
}

- (void)refreshScrollViewOffset:(float)y
{
    [_scrollView scrollRectToVisible:CGRectMake(0, y, 1, 1) animated:NO];
}

- (NSArray*)portsItems
{
    return [_scrollView subviews];
}

- (void)connectIfTouchingTwoItems
{
    JackViewPortsViewItem* item = nil;
    JackViewPortsViewItem* item1 = nil;
    JackViewPortsViewItem* item2 = nil;
    int i = 0;
    NSArray* items = [_scrollView subviews];
    JackView* jackView = self.clientButton.jackView;
    
    for (i = 0; i < [items count]; ++i)
    {
        item = ((JackViewPortsViewItem*)[items objectAtIndex:i]);
        if (item && [item isKindOfClass:[JackViewPortsViewItem class]] && item.touching)
        {
            if (!item1) item1 = item;
            else if (!item2) item2 = item;
        }
    }
    
    if (item1 && item2)
    {
        if ([jackView isPort:item1.longName
            connectedWithPort:item2.longName])
        {
            [jackView disconnectPort:item1.longName withPort:item2.longName];
            [jackView disconnectPort:item2.longName withPort:item1.longName];
        }
        else
        {
            [jackView connectPort:item1.longName withPort:item2.longName];
            [jackView connectPort:item2.longName withPort:item1.longName];
        }
        
        self.linking = NO;
        self.dontDrawLinking = YES;
        
        [self setNeedsDisplay];
    }
}

@end
