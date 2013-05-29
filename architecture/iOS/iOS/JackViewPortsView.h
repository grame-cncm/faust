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


@class JackViewButton;

@interface JackViewPortsViewItem : UIControl

@property (assign, nonatomic) NSString* longName;
@property (assign, nonatomic) NSString* alias;

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
    NSMutableArray*         _links;
    UITapGestureRecognizer* _tapRecognizer;
    UIButton*               _deleteButton;
}

@property (assign, nonatomic) JackViewButton* clientButton;
@property (assign, nonatomic) float clientX;
@property (assign, nonatomic) float currentAppX;
@property (assign, nonatomic) BOOL linking;
@property (assign, readwrite) CGPoint srcPt;
@property (assign, readwrite) CGPoint dstPt;

- (void)createLinks;
- (void)deleteSelectedLink;
- (JackViewPortsViewItem*)itemAtPoint:(CGPoint)pt;
- (void)singleTap:(UIGestureRecognizer *)gestureRecognizer;
- (float)computeXOffsetWithXItems:(float)xItems xIcon:(float)xIcon;

@end
