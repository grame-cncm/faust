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

#import "FIBox.h"

@implementation FIBox

#pragma mark -
#pragma mark Init

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    return self;
}

- (void)updateFrame:(CGRect)frame
{
    self.frame = frame;
}

- (void)dealloc
{
    [super dealloc];
}

#pragma mark -
#pragma mark Drawing

- (void)drawRect:(CGRect)rect
{
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGRect boundsRect = self.bounds;
    
	CGContextSaveGState(context);
	CGContextSetLineWidth(context, 2.f);
    [self.color set];
    CGContextAddRect(context, boundsRect);
    CGContextStrokePath(context);
	CGContextRestoreGState(context);
}

@end
