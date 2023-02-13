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
    NSUInteger  nbButtons = 0;
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
    button.labelFont = [UIFont boldSystemFontOfSize:18];
    button.labelColor = [UIColor colorWithWhite:1. alpha:1.];
    button.backgroundColorAlpha = 0.4;
    button.type = kTabItemButtonType;
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
        NSUInteger  nbButtons = [_buttons count];
        
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
    NSUInteger  nbButtons = [_buttons count];
    
    if (self.hideOnGUI) return;
    
    for (i = 0; i < nbButtons; ++i)
    {
        [((FIButton*)[_buttons objectAtIndex:i]) setNeedsDisplay];
    }
}

@end
