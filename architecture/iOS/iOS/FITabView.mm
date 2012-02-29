//
//  FITabView.m
//  iOS
//
//  Created by Olivier Guillerminet on 28/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "FITabView.h"

@implementation FITabView

@synthesize cornerRadius;

#pragma mark -
#pragma mark Init

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super initWithDelegate:aDelegate]))
	{
		self.cornerRadius = 3.0;
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth |
                                UIViewAutoresizingFlexibleRightMargin |
                                UIViewAutoresizingFlexibleLeftMargin;
        _buttons = [[NSMutableArray alloc] initWithCapacity:0];
        self.min = 0.f;
        self.max = 0.f;
	}
	
	return self;
}

- (void)dealloc
{
    [_buttons release];
    [super dealloc];
}

// to setup handle size
- (void)setFrame:(CGRect)frame
{
	[super setFrame:frame];
}

- (void)addButtonWithLabel:(NSString *)label
{
    FIButton*   button = [[[FIButton alloc] initWithDelegate:self] autorelease];
    int         nbButtons = 0;
    float       viewWidth = self.frame.size.width;
    float       viewHeight = self.frame.size.height;
    int         i = 0;
    
    [_buttons addObject:button];
    nbButtons = [_buttons count];
    if (nbButtons == 1) ((FIButton*)[_buttons objectAtIndex:i]).value = 1.f;
    
    for (i = 0; i < nbButtons; ++i)
    {
        ((FIButton*)[_buttons objectAtIndex:i]).frame = CGRectMake(i * viewWidth / nbButtons,
                                                                   0.f,
                                                                   viewWidth / nbButtons,
                                                                   viewHeight);
    }
    
    button.autoresizingMask =   UIViewAutoresizingFlexibleWidth |
                                UIViewAutoresizingFlexibleRightMargin |
                                UIViewAutoresizingFlexibleLeftMargin;
    
    button.title = [[NSString alloc] initWithString:label];
    button.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.0];
    button.labelColor = [UIColor whiteColor];
    button.backgroundColorAlpha = 0.4;
    button.type = TYPE_TABITEM;
    self.max = nbButtons - 1;
    [self addSubview:button];
}


#pragma mark -
#pragma mark Touch Handling

- (void)responderValueDidChange:(float)value sender:(id)sender
{
    if (value == 1)
    {
        int         i = 0;
        int         nbButtons = [_buttons count];
        
        for (i = 0; i < nbButtons; ++i)
        {
            if (sender != ((FIButton*)[_buttons objectAtIndex:i]))
            {
                ((FIButton*)[_buttons objectAtIndex:i]).value = 0;
            }
            else
            {
                self.value = i;
            }
        }
    }
}


#pragma mark -
#pragma mark Drawing

- (void)drawRect:(CGRect)rect
{
    int         i = 0;
    int         nbButtons = [_buttons count];
        
    for (i = 0; i < nbButtons; ++i)
    {
        [((FIButton*)[_buttons objectAtIndex:i]) setNeedsDisplay];
    }
}

@end
