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
 Based on F3BarGauge - https://github.com/ChiefPilot/F3BarGauge
 Copyright (c) 2011 by Brad Benson - https://github.com/ChiefPilot
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
 THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 OF SUCH DAMAGE.
 ************************************************************************
 ************************************************************************/

//---> Pick up required headers <-----------------------------------------

#import <UIKit/UIKit.h>
#import "FIResponder.h"

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------|  F3BarGauge class definition  |---------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
@interface FIBargraph : FIResponder
{
@private
    BOOL        m_fHoldPeak,            // YES = hold peak value enabled
                m_fLitEffect,           // YES = draw segments with gradient "lit-up" effect
                m_fReverseDirection;    // YES = top-to-bottom or right-to-left 
    float       m_flValue,              // Current value being displayed
                m_flPeakValue,          // Peak value seen since reset
                m_flMaxLimit,           // Maximum displayable value
                m_flMinLimit,           // Minimum displayable value    
                m_flWarnThreshold,      // Warning threshold (segment color specified by m_clrWarning)
                m_flDangerThreshold;    // Danger threshold (segment color specified by m_clrDanger)
    int         m_iNumBars;             // Number of segments
    UIColor     *m_clrOuterBorder,      // Color of outer border
                *m_clrInnerBorder,      // Color of inner border
                *m_clrBackground,       // Background color of gauge
                *m_clrNormal,           // Normal segment color
                *m_clrWarning,          // Warning segment color
                *m_clrDanger;           // Danger segment color
}

@property (readwrite, nonatomic)  CGFloat   value;
@property (readwrite, nonatomic)  float     warnThreshold;
@property (readwrite, nonatomic)  float     dangerThreshold;
@property (readwrite, nonatomic)  float     maxLimit;
@property (readwrite, nonatomic)  float     minLimit;
@property (readwrite, nonatomic)  int       numBars;
@property (readonly, nonatomic)   float     peakValue;
@property (readwrite, nonatomic)  BOOL      holdPeak;
@property (readwrite, nonatomic)  BOOL      litEffect;
@property (readwrite, nonatomic)  BOOL      reverse;
@property (readwrite, nonatomic)  BOOL      led;
@property (readwrite, retain)     UIColor   *outerBorderColor;
@property (readwrite, retain)     UIColor   *innerBorderColor;
@property (readwrite, retain)     UIColor   *backgroundColor;
@property (readwrite, retain)     UIColor   *normalBarColor;
@property (readwrite, retain)     UIColor   *warningBarColor;
@property (readwrite, retain)     UIColor   *dangerBarColor;
@property (readwrite, retain)     UIColor   *ledMinColor;
@property (readwrite, retain)     UIColor   *ledMaxColor;

-(void) resetPeak;

@end
