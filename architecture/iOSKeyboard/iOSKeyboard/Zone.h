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
    bool keyboardMode;
}

- (void)setColorOff:(UIColor*)color; // sets the color when off
- (void)setColorOn:(UIColor*)color; // sets the color when on
- (void)setImageOff:(UIImage*)image; // sets the background image when off
- (void)setImageOn:(UIImage*)image; // sets the background image when on
- (void)setText:(NSString*)label;
- (void)setTextSize:(CGFloat)size;
- (void)setStatus:(int)s;
- (void)setNote:(int)note;
- (int)getStatus;
- (void)setKeyboardMode:(bool)mode;

@end
