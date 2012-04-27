/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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
#import "FIMainViewController.h"

#define kAccViewHeight          40.0
#define kIncDecButtonWidth      100.0
#define kIncDecButtonHeight     35.0

@implementation FITextField

@synthesize cornerRadius;
@synthesize backgroundColor = _backgroundColor;
@synthesize textColor = _textColor;

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
        _messageTextView.backgroundColor = [UIColor colorWithRed:0.f green:0.f blue:1.f alpha:0.2];
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
        
        // Inc dec buttons
        _incButton = [[[FIButton alloc] initWithDelegate:self] autorelease];
        _incButton.title = @"+";
        _incButton.labelFont = [UIFont boldSystemFontOfSize:18];
        _incButton.labelColor = [UIColor colorWithWhite:1. alpha:1.];
        _incButton.backgroundColorAlpha = 0.4;
        _incButton.type = kPushButtonType;
        [self addSubview:_incButton];
        
        _decButton = [[[FIButton alloc] initWithDelegate:self] autorelease];
        _decButton.title = @"-";
        _decButton.labelFont = [UIFont boldSystemFontOfSize:18];
        _decButton.labelColor = [UIColor colorWithWhite:1. alpha:1.];
        _decButton.backgroundColorAlpha = 0.4;
        _decButton.type = kPushButtonType;
        [self addSubview:_decButton];
        
        // Input accessory view
        [self createInputAccessoryView];
        _messageTextView.inputAccessoryView = _inputAccView;
        
        // Number formatter
        _numberFormatter = [[NSNumberFormatter alloc] init];
        [_numberFormatter setNumberStyle:NSNumberFormatterDecimalStyle];
        [_numberFormatter setRoundingMode:NSNumberFormatterRoundDown];
	}
	
	return self;
}

// to setup handle size
- (void)setFrame:(CGRect)frame
{
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
    _messageTextView.frame = CGRectMake(rect.origin.x,
                                        rect.origin.y + kIncDecButtonHeight,
                                        rect.size.width,
                                        rect.size.height - 2 * kIncDecButtonHeight);
    _messageTextView.text = [NSString stringWithFormat:@"%2.2f%@", self.value, self.suffixe];
    _incButton.frame = CGRectMake(rect.origin.x + rect.size.width / 2.f - kIncDecButtonWidth / 2.f,
                                  rect.origin.y,
                                  kIncDecButtonWidth,
                                  kIncDecButtonHeight);
    _decButton.frame = CGRectMake(rect.origin.x + rect.size.width / 2.f - kIncDecButtonWidth / 2.f,
                                  rect.origin.y + rect.size.height - kIncDecButtonHeight,
                                  kIncDecButtonWidth,
                                  kIncDecButtonHeight);
}


#pragma mark - UITextView Delegate Methods

-(void)textViewDidBeginEditing:(UITextView *)textView
{
    _valueBeforeCancel = self.value;
    [((FIMainViewController*)self.delegate) zoomToWidget:self];
    _rangeLabel.text = [NSString stringWithFormat:@"Range : %2.2f - %2.2f", self.min, self.max];
    [_messageTextView setText:@""];
}

- (void)minus
{
    if ([_messageTextView.text length] == 0)
    {
        _messageTextView.text = [NSString stringWithString:@"-"];
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
    
    [_messageTextView setText:[NSString stringWithFormat:@"%2.2f%@", value, self.suffixe]];
}

- (void)cancel
{
    float value;
    
    // Hide the keyboard
    [_messageTextView resignFirstResponder];
    
    [self setValue:_valueBeforeCancel];
    
    [_messageTextView setText:[NSString stringWithFormat:@"%2.2f%@", value, self.suffixe]];
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

- (void)responderValueDidChange:(float)value sender:(id)sender
{
    if (value == 1)
    {
        if (sender == _incButton)
        {
            [self setValue:self.value + self.step];
        }
        else if (sender == _decButton)
        {
            [self setValue:self.value - self.step];
        }
    }
}

@end
