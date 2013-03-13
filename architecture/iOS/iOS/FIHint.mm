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

#import "FIHint.h"

#define kStdHintWidth           120
#define kStdHintHeight          50

@implementation FIHint

@synthesize title;
@synthesize position;

- (id)init
{
    self = [super init];
    if (self)
    {
        self.position = 0;
        self.backgroundColor = [UIColor clearColor];
        self.title = @"";
        [self setFrame:CGRectMake(0.f, 0.f, kStdHintWidth, kStdHintHeight)];
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
	CGContextRef context = UIGraphicsGetCurrentContext();
    UIFont* labelFont = [UIFont boldSystemFontOfSize:19.0];
    UIColor* bgColor = [UIColor colorWithWhite:0.1 alpha:0.9];
    UIColor* textColor = [UIColor whiteColor];
    
    self.backgroundColor = [UIColor clearColor];
    
    // Top
    if (self.position == 0)
    {
        CGContextSaveGState(context);
        
        // Main rect
        [bgColor set];
        CGContextAddRect(context, CGRectMake(rect.origin.x,
                                             rect.origin.y, 
                                             rect.size.width,
                                             rect.size.height / 2.f));
        CGContextFillPath(context);
        
        // Triangle
        CGContextBeginPath(context);
        CGContextMoveToPoint(context,
                             rect.origin.x + rect.size.width / 3.f,
                             rect.origin.y + rect.size.height / 2.f);
        CGContextAddLineToPoint(context,
                                rect.origin.x + rect.size.width / 2.f,
                                rect.origin.y + rect.size.height);
        CGContextAddLineToPoint(context,
                                rect.origin.x + 2 * rect.size.width / 3.f,
                                rect.origin.y + rect.size.height / 2.f);
        CGContextClosePath(context);
        
        CGContextFillPath(context);
        
        CGContextRestoreGState(context);
        
        // Text
        [textColor set];
        [self.title drawInRect:CGRectMake(rect.origin.x,
                                          rect.origin.y,
                                          rect.size.width,
                                          rect.size.height / 2.f)
                      withFont:labelFont
                 lineBreakMode:UILineBreakModeTailTruncation
                     alignment:UITextAlignmentCenter];
    }
    
    // Bottom
    else if (self.position == 1)
    {
        CGContextSaveGState(context);
        
        // Main rect
        [bgColor set];
        CGContextAddRect(context, CGRectMake(rect.origin.x,
                                             rect.origin.y + rect.size.height / 2.f, 
                                             rect.size.width,
                                             rect.size.height / 2.f));
        CGContextFillPath(context);
        
        // Triangle
        CGContextBeginPath(context);
        CGContextMoveToPoint(context,
                             rect.origin.x + rect.size.width / 3.f,
                             rect.origin.y + rect.size.height / 2.f);
        CGContextAddLineToPoint(context,
                                rect.origin.x + rect.size.width / 2.f,
                                rect.origin.y - rect.size.height);
        CGContextAddLineToPoint(context,
                                rect.origin.x + 2 * rect.size.width / 3.f,
                                rect.origin.y + rect.size.height / 2.f);
        CGContextClosePath(context);
        
        CGContextFillPath(context);
        
        CGContextRestoreGState(context);
        
        // Text
        [textColor set];
        [self.title drawInRect:CGRectMake(rect.origin.x,
                                          rect.origin.y + rect.size.height / 2.f,
                                          rect.size.width,
                                          rect.size.height / 2.f)
                      withFont:labelFont
                 lineBreakMode:UILineBreakModeTailTruncation
                     alignment:UITextAlignmentCenter];
    }
    
    // Left
    else if (self.position == 2)
    {
        CGContextSaveGState(context);
        
        // Main rect
        [bgColor set];
        CGContextAddRect(context, CGRectMake(rect.origin.x,
                                             rect.origin.y + rect.size.height / 4.f, 
                                             3.f * rect.size.width / 4.f,
                                             rect.size.height / 2.f));
        CGContextFillPath(context);
        
        // Triangle
        CGContextBeginPath(context);
        CGContextMoveToPoint(context,
                             rect.origin.x + 3.f * rect.size.width / 4.f,
                             rect.origin.y + rect.size.height / 4.f);
        CGContextAddLineToPoint(context,
                                rect.origin.x + rect.size.width,
                                rect.origin.y + rect.size.height / 2.f);
        CGContextAddLineToPoint(context,
                                rect.origin.x + 3.f * rect.size.width / 4.f,
                                rect.origin.y + 3.f * rect.size.height / 4.f);
        CGContextClosePath(context);
        
        CGContextFillPath(context);
        
        CGContextRestoreGState(context);
        
        // Text
        [textColor set];
        [self.title drawInRect:CGRectMake(rect.origin.x,
                                          rect.origin.y + rect.size.height / 4.f,
                                          3.f * rect.size.width / 4.f,
                                          rect.size.height / 2.f)
                      withFont:labelFont
                 lineBreakMode:UILineBreakModeTailTruncation
                     alignment:UITextAlignmentLeft];
    }
    // Right
    else if (self.position == 3)
    {
        CGContextSaveGState(context);
        
        // Main rect
        [bgColor set];
        CGContextAddRect(context, CGRectMake(rect.origin.x + rect.size.width / 4.f,
                                             rect.origin.y + rect.size.height / 4.f, 
                                             3.f * rect.size.width / 4.f,
                                             rect.size.height / 2.f));
        CGContextFillPath(context);
        
        // Triangle
        CGContextBeginPath(context);
        CGContextMoveToPoint(context,
                             rect.origin.x + rect.size.width / 4.f,
                             rect.origin.y + rect.size.height / 4.f);
        CGContextAddLineToPoint(context,
                                rect.origin.x,
                                rect.origin.y + rect.size.height / 2.f);
        CGContextAddLineToPoint(context,
                                rect.origin.x + rect.size.width / 4.f,
                                rect.origin.y + 3.f * rect.size.height / 4.f);
        CGContextClosePath(context);
        
        CGContextFillPath(context);
        
        CGContextRestoreGState(context);
        
        // Text
        [textColor set];
        [self.title drawInRect:CGRectMake(rect.origin.x + rect.size.width / 4.f,
                                          rect.origin.y + rect.size.height / 4.f,
                                          3.f * rect.size.width / 4.f,
                                          rect.size.height / 2.f)
                      withFont:labelFont
                 lineBreakMode:UILineBreakModeTailTruncation
                     alignment:UITextAlignmentRight];
    }
}

@end
