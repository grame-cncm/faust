//
//  JackViewPortsView.h
//  iOS
//
//  Created by Olivier Guillerminet on 29/04/13.
//
//

#import <UIKit/UIKit.h>

#define kPortsViewWidth 100
#define kPortsViewItemHeight 50
#define kPortsArrowHeight 30
#define kPortsViewArrowWidth 50


@class JackViewButton;

@interface JackViewPortsViewItem : UIControl

@property (assign, nonatomic) NSString* longName;
@property (assign, nonatomic) NSString* alias;

@end


@interface JackViewPortsView : UIView
{
    UIScrollView*           _scrollView;
}

@property (assign, nonatomic) JackViewButton* clientButton;
@property (assign, nonatomic) float clientX;
@property (assign, nonatomic) float currentAppX;
@property (assign, nonatomic) BOOL linking;
@property (assign, readwrite) CGPoint srcPt;
@property (assign, readwrite) CGPoint dstPt;

- (JackViewPortsViewItem*)itemAtPoint:(CGPoint)pt;

@end
