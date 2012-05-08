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
#import "FIButton.h"

@interface FITabView : FIResponder <FIResponderDelegate>
{
    NSMutableArray*             _buttons;
}

@property CGFloat cornerRadius;				// default: 3.0

- (id)initWithDelegate:(id)aDelegate;
- (void)addButtonWithLabel:(NSString *)label;

- (void)responderValueDidChange:(float)value sender:(id)sender;

@end
