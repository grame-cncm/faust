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

#import "FITextField.h"

#define kAccViewHeight          40.0

@implementation FITextField

@synthesize cornerRadius;
@synthesize backgroundColor = _backgroundColor;
@synthesize textColor = _textColor;
@synthesize fMenuItemNames;
@synthesize fMenuItemValues;

#pragma mark -
#pragma mark Init

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super initWithDelegate:aDelegate]))
	{
        _valueBeforeCancel = 0.f;
        
        // UI parameters
		self.cornerRadius = 3.0;
        
        // Message text view creation
        _messageTextView = [[UITextView alloc] initWithFrame:self.bounds];
        [_messageTextView setAutocorrectionType:UITextAutocorrectionTypeNo];
        [_messageTextView setReturnKeyType:UIReturnKeyGo];
        _backgroundColor = [UIColor whiteColor];
        _textColor = [UIColor blackColor];
        _messageTextView.textColor = [UIColor whiteColor];
        _messageTextView.backgroundColor = [UIColor darkGrayColor];
        _messageTextView.delegate = self;
        _messageTextView.font = [UIFont boldSystemFontOfSize:14];
        _messageTextView.textAlignment = UITextAlignmentCenter;
        [self addSubview:_messageTextView];
        
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
        {
            _messageTextView.keyboardType = UIKeyboardTypeDecimalPad;
        }
        else
        {
            _messageTextView.keyboardType = UIKeyboardTypeNumberPad;
        }
                
        // Input accessory view
        [self createInputAccessoryView];
        _messageTextView.inputAccessoryView = _inputAccView;
        
        // Number formatter
        _numberFormatter = [[NSNumberFormatter alloc] init];
        [_numberFormatter setNumberStyle:NSNumberFormatterDecimalStyle];
        [_numberFormatter setRoundingMode:NSNumberFormatterRoundDown];
        
        UIPanGestureRecognizer *panGesture = [[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(pan:)] autorelease];
        panGesture.delegate = self;
		[self addGestureRecognizer:panGesture];
	}
	
	return self;
}

// to setup handle size
- (void)setFrame:(CGRect)frame
{
    /*
    2017/10/27 : finally values need to be edited, so deactivate this case
     
    // Edition is deactivated if medata 'menu' is used
    if (self.fMenuItemValues.size() > 0) {
        _messageTextView.editable = NO;
    }
    */

    [super setFrame:frame];
}

- (void)dealloc
{
    [_messageTextView release];
    [_inputAccView release];
    [_doneButton release];
    [_rangeLabel release];
    
    [super dealloc];
}

#pragma mark -
#pragma mark Drawing

- (void)drawRect:(CGRect)rect
{
    if (self.hideOnGUI) return;
    
    _messageTextView.frame = CGRectMake(rect.origin.x,
                                        rect.origin.y,
                                        rect.size.width,
                                        rect.size.height);
    
    // In menu items, displays them instead of the value
    if (self.fMenuItemValues.size() > 0) {
        
        for (int i = 0; i < self.fMenuItemValues.size(); i++) {
            if (floor(self.value) == self.fMenuItemValues[i]) {
                _messageTextView.text = [NSString stringWithCString:self.fMenuItemNames[i].c_str() encoding:NSUTF8StringEncoding];
            }
        }
        
    } else {
    
        if (self.step < 0.01) _messageTextView.text = [NSString stringWithFormat:@"%2.3f%@", self.value, self.suffixe];
        else if (self.step < 0.1) _messageTextView.text = [NSString stringWithFormat:@"%2.2f%@", self.value, self.suffixe];
        else _messageTextView.text = [NSString stringWithFormat:@"%2.1f%@", self.value, self.suffixe];
            
    }
}

#pragma mark - UITextView Delegate Methods

-(void)textViewDidBeginEditing:(UITextView *)textView
{
    _valueBeforeCancel = self.value;
    [((FIMainViewController*)self.delegate) zoomToWidget:self];
    if (self.step < 0.01) _rangeLabel.text = [NSString stringWithFormat:@"Range : %2.3f - %2.3f", self.min, self.max];
    else if (self.step < 0.1) _rangeLabel.text = [NSString stringWithFormat:@"Range : %2.2f - %2.2f", self.min, self.max];
    else _rangeLabel.text = [NSString stringWithFormat:@"Range : %2.1f - %2.1f", self.min, self.max];
    [_messageTextView setText:@""];
}

- (void)minus
{
    if ([_messageTextView.text length] == 0)
    {
        _messageTextView.text = @"-";
    }
    else if ([_messageTextView.text characterAtIndex:0] != 45) //45 for minus
    {
        _messageTextView.text = [NSString stringWithFormat:@"-%@", _messageTextView.text];
    }
    else
    {
        _messageTextView.text = [_messageTextView.text substringFromIndex:1];
    }    
}

- (void)doneTyping
{
    float value;
    
    // Hide the keyboard
    [_messageTextView resignFirstResponder];
    value = [[_numberFormatter numberFromString:_messageTextView.text] floatValue];
    if (value < self.min) value = self.min;
    else if (value > self.max) value = self.max;
    
    [self setValue:value];
    
    [self setNeedsDisplay];
}

- (void)cancel
{    
    // Hide the keyboard
    [_messageTextView resignFirstResponder];
    
    [self setValue:_valueBeforeCancel];
    
    [self setNeedsDisplay];
}

- (void)createInputAccessoryView
{
    float viewWidth = _messageTextView.inputView.frame.size.width;

    _inputAccView = [[UIView alloc] initWithFrame:CGRectMake(10.0, 0.0, viewWidth, kAccViewHeight)];
    _inputAccView.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    
    viewWidth = _inputAccView.frame.size.width;
    _inputAccView.backgroundColor = [UIColor blackColor];

    _rangeLabel = [[UILabel alloc] initWithFrame:CGRectMake(0.0, 0.0, 200.0, kAccViewHeight)];
    _rangeLabel.backgroundColor = [UIColor blackColor];
    _rangeLabel.textColor = [UIColor whiteColor];
    _rangeLabel.textAlignment = UITextAlignmentLeft;
    [_inputAccView addSubview:_rangeLabel];
    
    _minusButton =[UIButton buttonWithType:UIButtonTypeCustom];
    [_minusButton setFrame:CGRectMake(viewWidth - 120.f, 0.0f, 40.0f, kAccViewHeight)];
    _minusButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin;
    [_minusButton setTitle:@"-" forState:UIControlStateNormal];
    [_minusButton setBackgroundColor:[UIColor blueColor]];
    [_minusButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [_minusButton addTarget:self action:@selector(minus) forControlEvents:UIControlEventTouchUpInside];
    [_inputAccView addSubview:_minusButton];
    
    _cancelButton =[UIButton buttonWithType:UIButtonTypeCustom];
    [_cancelButton setFrame:CGRectMake(viewWidth - 80.f, 0.0f, 40.0f, kAccViewHeight)];
    _cancelButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin;
    [_cancelButton setTitle:@"X" forState:UIControlStateNormal];
    [_cancelButton setBackgroundColor:[UIColor blueColor]];
    [_cancelButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [_cancelButton addTarget:self action:@selector(cancel) forControlEvents:UIControlEventTouchUpInside];
    [_inputAccView addSubview:_cancelButton];
    
    _doneButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_doneButton setFrame:CGRectMake(viewWidth - 40.f, 0.0f, 40.0f, kAccViewHeight)];
    _doneButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin;
    [_doneButton setTitle:@"OK" forState:UIControlStateNormal];
    [_doneButton setBackgroundColor:[UIColor blueColor]];
    [_doneButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [_doneButton addTarget:self action:@selector(doneTyping) forControlEvents:UIControlEventTouchUpInside];
    [_inputAccView addSubview:_doneButton];
}

#pragma mark -
#pragma mark Touch Handling

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    UIScrollView* scrollView = (UIScrollView*)self.superview.superview;
    
    scrollView.scrollEnabled = NO;
    
    return YES;
}

- (void)pan:(UIPanGestureRecognizer *)gesture
{
    UIScrollView* scrollView = (UIScrollView*)self.superview.superview;
    float value = 0.f - [gesture velocityInView:scrollView].y;
    value = value / 200.;
        
    if ([gesture velocityInView:scrollView].y < 0)
    {
        [self setValue:self.value + (floor(value) + 1.) * self.step];
    }
    else
    {
        [self setValue:self.value + floor(value) * self.step];
    }
    
    scrollView.scrollEnabled = YES;
}

@end
