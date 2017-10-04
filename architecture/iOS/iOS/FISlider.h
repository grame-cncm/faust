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

/************************************************************************
 ************************************************************************
 Based on DCControls - https://github.com/domesticcatsoftware/DCControls
 Copyright (C) 2011 by Patrick Richards - http://domesticcat.com.au/
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ************************************************************************
 ************************************************************************/

#import "FIResponder.h"
#import "FIHint.h"

#include <vector>
#include <string>

@interface FISlider : FIResponder
{
	CGFloat touchHandleOffset;
    FIHint* _hint;
}

@property std::vector<std::string>    fMenuItemNames;
@property std::vector<double>         fMenuItemValues;

@property CGFloat handleSize;				// default: longest side / 6 (minimum of 35.0)
@property CGFloat cornerRadius;				// default: 3.0
@property BOOL isHorizontalSlider;			// default: NO
@property BOOL biDirectional;				// default: NO

- (id)initWithDelegate:(id)aDelegate;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;

- (CGRect)rectForHandle;

- (void)updateHint;

@end
