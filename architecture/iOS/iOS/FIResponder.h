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

#import <UIKit/UIKit.h>

#define FIDegreesToRadians(x) (M_PI * (x) / 180.0)
#define FIRadiansToDegrees(x) ((x) * 180.0 / M_PI)

@protocol FIResponderDelegate <NSObject>

@required

- (void)responderValueDidChange:(float)value sender:(id)sender;

@end

@interface FIResponder : UIControl

@property (nonatomic, assign) id delegate;
@property (nonatomic, retain) UIColor *color;			// default: black
@property CGFloat backgroundColorAlpha;					// default: 0.3

@property (nonatomic, retain) UIFont *labelFont;		// default: bold, system, 12.5
@property (nonatomic, retain) UIColor *labelColor;		// default: use self.color
@property CGPoint labelOffset;							// default: CGPointZero

@property CGFloat min;									// default: 0.0
@property CGFloat max;									// default: 1.0
@property (nonatomic) CGFloat value;					// default: 0.0
@property (nonatomic) CGFloat step;                     // default: 0.1
@property (assign, nonatomic) NSString* suffixe;        // default: @""

@property BOOL displaysValue;							// default: YES
@property BOOL allowsGestures;							// default: YES
@property BOOL responderSelected;                       // default: NO
@property BOOL motionBlocked;                           // default: NO
@property BOOL assignated;                              // default: NO
@property BOOL hideOnGUI;                               // default: NO

- (id)initWithDelegate:(id)aDelegate;

- (void)context:(CGContextRef)context addRoundedRect:(CGRect)rect cornerRadius:(float)cornerRadius;

@end
