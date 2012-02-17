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

@implementation FITextField

@synthesize cornerRadius;

#pragma mark -
#pragma mark Init

- (id)initWithDelegate:(id)aDelegate
{
	if ((self = [super initWithDelegate:aDelegate]))
	{
        // UI parameters
		self.cornerRadius = 3.0;
        self.autoresizingMask = UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin;
        
        // Message text view creation
        _messageTextView = [[UITextView alloc] initWithFrame:self.bounds];
        [_messageTextView setAutocorrectionType:UITextAutocorrectionTypeNo];
        [_messageTextView setReturnKeyType:UIReturnKeyGo];
        [_messageTextView setTextColor:[UIColor lightGrayColor]];        
        _messageTextView.delegate = self;
        [self addSubview:_messageTextView];
        _messageTextView.keyboardType = UIKeyboardTypeDecimalPad;
        
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
}

#pragma mark -
#pragma mark Drawing

- (void)drawRect:(CGRect)rect
{
    _messageTextView.frame = rect;
    [_messageTextView setText:[NSString stringWithFormat:@"%2.2f", self.value]];
}


#pragma mark - UITextView Delegate Methods

-(void)textViewDidBeginEditing:(UITextView *)textView
{
    [_messageTextView setText:@""];
}

- (void)minus
{
    //if ([_messageTextView.text characterAtIndex:0] ==)
    //[_messageTextView setText:[NSString stringWithFormat:@"%2.2f", value]];
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
    
    [_messageTextView setText:[NSString stringWithFormat:@"%2.2f", value]];   
}

- (void)createInputAccessoryView
{
    float viewWidth = _messageTextView.inputView.frame.size.width;

    _inputAccView = [[UIView alloc] initWithFrame:CGRectMake(10.0, 0.0, viewWidth, 40.0)];
    _inputAccView.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    
    viewWidth = _inputAccView.frame.size.width;
    _inputAccView.backgroundColor = [UIColor blackColor];

    _rangeLabel = [[UILabel alloc] initWithFrame:CGRectMake(0.0, 0.0, 200.0, 40.0)];
    _rangeLabel.backgroundColor = [UIColor blackColor];
    _rangeLabel.textColor = [UIColor whiteColor];
    _rangeLabel.textAlignment = UITextAlignmentLeft;
    _rangeLabel.text = [NSString stringWithFormat:@"Range : %2.2f - %2.2f", self.min, self.max];
    [_inputAccView addSubview:_rangeLabel];
    
    _minusButton =[UIButton buttonWithType:UIButtonTypeCustom];
    [_minusButton setFrame:CGRectMake(viewWidth - 120.f, 0.0f, 60.0f, 40.0f)];
    _minusButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin;
    [_minusButton setTitle:@"-" forState:UIControlStateNormal];
    [_minusButton setBackgroundColor:[UIColor grayColor]];
    [_minusButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [_minusButton addTarget:self action:@selector(doneTyping) forControlEvents:UIControlEventTouchUpInside];
    [_inputAccView addSubview:_minusButton];
    
    _doneButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_doneButton setFrame:CGRectMake(viewWidth - 60.f, 0.0f, 60.0f, 40.0f)];
    _doneButton.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin;
    [_doneButton setTitle:@"Done" forState:UIControlStateNormal];
    [_doneButton setBackgroundColor:[UIColor grayColor]];
    [_doneButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [_doneButton addTarget:self action:@selector(doneTyping) forControlEvents:UIControlEventTouchUpInside];
    [_inputAccView addSubview:_doneButton];
}

@end
