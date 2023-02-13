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
