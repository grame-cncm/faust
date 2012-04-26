//
//  FIScrollView.m
//  iOS
//
//  Created by Olivier Guillerminet on 26/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "FIScrollView.h"
#import "FIBox.h"

@implementation FIScrollView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
    }
    return self;
}

- (void)awakeFromNib
{
    self.canCancelContentTouches = NO;
    self.delaysContentTouches = NO;
}

-(BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

- (BOOL)touchesShouldBegin:(NSSet *)touches withEvent:(UIEvent *)event inContentView:(UIView *)view
{
    if ([view isKindOfClass:[FIBox class]])
    {
        return NO;
    }
    else
    {
        return YES;
    }
    
    return YES;
}

@end
