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
