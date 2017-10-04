/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 
 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.
 
 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#import "FIResponder.h"
#import "FIMainViewController.h"

#include <vector>
#include <string>

@interface FITextField : FIResponder <UITextViewDelegate,
                                      UIGestureRecognizerDelegate>
{
    UITextView*             _messageTextView;
    UIView*                 _inputAccView;
    UIButton*               _doneButton;
    UIButton*               _minusButton;
    UIButton*               _cancelButton;
    UILabel*                _rangeLabel;
    NSNumberFormatter*      _numberFormatter;
    UIColor*                _backgroundColor;
    UIColor*                _textColor;
    float                   _valueBeforeCancel;
}

@property CGFloat cornerRadius;				// default: 3.0
@property (assign, nonatomic) UIColor* backgroundColor;
@property (assign, nonatomic) UIColor* textColor;

@property std::vector<std::string>    fMenuItemNames;
@property std::vector<double>         fMenuItemValues;

- (id)initWithDelegate:(id)aDelegate;

- (void)minus;
- (void)doneTyping;
- (void)cancel;
- (void)createInputAccessoryView;

- (void)pan:(UIPanGestureRecognizer *)gesture;

@end
