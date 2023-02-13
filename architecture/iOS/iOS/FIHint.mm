/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
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
                 lineBreakMode:NSLineBreakByTruncatingTail
                     alignment:NSTextAlignmentCenter];
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
                 lineBreakMode:NSLineBreakByTruncatingTail
                     alignment:NSTextAlignmentCenter];
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
                 lineBreakMode:NSLineBreakByTruncatingTail
                     alignment:NSTextAlignmentLeft];
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
                 lineBreakMode:NSLineBreakByTruncatingTail
                     alignment:NSTextAlignmentRight];
    }
}

@end
