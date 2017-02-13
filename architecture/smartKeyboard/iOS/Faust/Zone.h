//
//  Zone.h
//  MultiXYTest
//
//  Created by Romain Michon on 4/15/16.
//  Copyright © 2016 CCRMA. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface Zone : UIView{
    @public
    int status; // the status of the zone (0:off, 1:on)
    bool staticMode;
}

- (void)setText:(NSString*)label;
- (void)setTextSize:(CGFloat)size;
- (void)setStatus:(int)s;
- (void)setNote:(int)note;
- (void)drawBackground;
- (int)getStatus;
- (void)showLabels:(bool)show;
- (void)setStaticMode:(bool)mode;

@end
