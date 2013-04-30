//
//  JackViewPortsView.h
//  iOS
//
//  Created by Olivier Guillerminet on 29/04/13.
//
//

#import <UIKit/UIKit.h>

#define kPortsViewWidth 100
#define kPortsViewItemHeight 30
#define kPortsArrowHeight 30
#define kPortsViewArrowWidth 50

@class JackViewButton;

@interface JackViewPortsViewItem : UIControl

@property (assign, nonatomic) NSString* longName;
@property (assign, nonatomic) NSString* shortName;
@property (assign, nonatomic) NSString* alias;

@end


@interface JackViewPortsView : UIView
{
    UIScrollView*           _scrollView;
}

@property (assign, nonatomic) NSMutableArray* ports;
@property (assign, nonatomic) JackViewButton* clientButton;

@end
