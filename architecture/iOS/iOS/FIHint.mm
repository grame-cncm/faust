/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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
#define kStdHintHeight          25

@implementation FIHint

@synthesize title;

- (id)init
{
    self = [super init];
    if (self)
    {
        self.title = [NSString stringWithString:@""];
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
    UIFont *labelFont = [UIFont boldSystemFontOfSize:19.0];

    CGContextSaveGState(context);
    CGContextClearRect(context, rect);
    
    [[UIColor colorWithRed:0.f green:0.f blue:0.f alpha:0.6] set];
    CGContextAddRect(context, rect);
    CGContextFillPath(context);
    
	CGContextRestoreGState(context);
    
    [[UIColor whiteColor] set];
    [self.title drawInRect:CGRectMake(rect.origin.x,
                                      rect.origin.y,
                                      rect.size.width,
                                      rect.size.height)
                  withFont:labelFont
             lineBreakMode:UILineBreakModeTailTruncation
                 alignment:UITextAlignmentCenter];
}

@end
