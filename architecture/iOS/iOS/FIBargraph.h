//
//  F3BarGauge.h
//
//  Copyright (c) 2011 by Brad Benson
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following 
//  conditions are met:
//    1.  Redistributions of source code must retain the above copyright
//        notice this list of conditions and the following disclaimer.
//    2.  Redistributions in binary form must reproduce the above copyright 
//        notice, this list of conditions and the following disclaimer in 
//        the documentation and/or other materials provided with the 
//        distribution.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
//  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
//  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
//  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
//  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
//  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
//  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
//  OF SUCH DAMAGE.
//  

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

@property (readwrite, nonatomic)  float     value;
@property (readwrite, nonatomic)  float     warnThreshold;
@property (readwrite, nonatomic)  float     dangerThreshold;
@property (readwrite, nonatomic)  float     maxLimit;
@property (readwrite, nonatomic)  float     minLimit;
@property (readwrite, nonatomic)  int       numBars;
@property (readonly, nonatomic)   float     peakValue;
@property (readwrite, nonatomic)  BOOL      holdPeak;
@property (readwrite, nonatomic)  BOOL      litEffect;
@property (readwrite, nonatomic)  BOOL      reverse;
@property (readwrite, retain)     UIColor   *outerBorderColor;
@property (readwrite, retain)     UIColor   *innerBorderColor;
@property (readwrite, retain)     UIColor   *backgroundColor;
@property (readwrite, retain)     UIColor   *normalBarColor;
@property (readwrite, retain)     UIColor   *warningBarColor;
@property (readwrite, retain)     UIColor   *dangerBarColor;

-(void) resetPeak;



@end
