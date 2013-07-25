//
//  JackViewPortsView.h
//  iOS
//
//  Created by Olivier Guillerminet on 29/04/13.
//
//

#import <UIKit/UIKit.h>

#define kPortsViewItemWidth 100
#define kPortsViewItemHeight 50
#define kPortsViewArrowHeight 30
#define kPortsViewArrowWidth 30
#define kPortsViewMinXBetweenItems 120
#define kPortsViewFSButtonWidth 30
#define kPortsViewFSButtonHeight 30
#define kPortsViewMaxHeight 150

#import "JackViewPortsViewBackgroundView.h"

@class JackViewButton;

@interface JackViewPortsViewItem : UIControl

@property (assign, nonatomic) NSString* longName;
@property (assign, nonatomic) NSString* alias;
@property (assign, nonatomic) BOOL touching;

@end


@interface JackViewPortsLink : NSObject

@property (assign, nonatomic) CGPoint srcPt;
@property (assign, nonatomic) CGPoint dstPt;
@property (assign, nonatomic) NSString* srcName;
@property (assign, nonatomic) NSString* dstName;
@property (assign, nonatomic) BOOL selected;

@end


@interface JackViewPortsView : UIView
{
    UIScrollView*           _scrollView;
    UITapGestureRecognizer* _tapRecognizer;
}

@property (assign, nonatomic) JackViewButton* clientButton;
@property (assign, nonatomic) UIButton* fsButton;
@property (assign, nonatomic) float clientX;
@property (assign, nonatomic) float currentAppX;
@property (assign, nonatomic) BOOL linking;
@property (assign, nonatomic) BOOL dontDrawLinking;
@property (assign, readwrite) CGPoint srcPt;
@property (assign, readwrite) CGPoint dstPt;
@property (assign, readwrite) JackViewPortsViewBackgroundView* backgroundView;
@property (assign, readwrite) NSMutableArray* links;
@property (assign, readwrite) UIButton* deleteButton;

- (void)refreshLinks;
- (void)deleteSelectedLink;
- (JackViewPortsViewItem*)itemAtPoint:(CGPoint)pt;
- (void)singleTap:(UIGestureRecognizer *)gestureRecognizer;
- (float)computeXOffsetWithXItems:(float)xItems xIcon:(float)xIcon;
- (void)setUtilHeight:(float)h;
- (void)addItem:(JackViewPortsViewItem*)item;
- (void)refreshScrollViewOffset:(float)y;
- (NSArray*)portsItems;
- (void)connectIfTouchingTwoItems;

@end
