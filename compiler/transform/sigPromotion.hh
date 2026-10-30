/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef __SIGPROMOTION__
#define __SIGPROMOTION__

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "description.hh"
#include "ppsig.hh"
#include "sigIdentity.hh"
#include "signalVisitor.hh"
#include "sigtyperules.hh"
#include "global.hh"

/*
 Print the type of a signal.
 To be used on a type annotated signal.
 */
class SignalTypePrinter final : public SignalVisitor {
   private:
    std::vector<std::string> fPrinted;
    void                     visit(Tree sig) override;

   public:
    SignalTypePrinter(Tree L);

    std::string print();
};

/*
 Check a signal:
 - for correct extended typing
 - for correct SigBinOp args typing
 - for proper SigIntCast and SigFloatCast use
 - for correct range in sliders (min < max and default in [min...max] range)
 - for correct SigWaveform values typing
 - for use on control/enable (not available in -vec mode)
 - for proper simplication of SigLowest/SigHighest

 To be used on a type annotated signal.
*/
class SignalChecker final : public SignalVisitor {
   private:
    void visit(Tree sig) override;

    void isRange(Tree sig, Tree init_aux, Tree min_aux, Tree max_aux);

   public:
    SignalChecker(Tree L)
    {
        // Check that the root tree is properly type annotated
        certifySignalsTyped(L);
        visitRoot(L);
    }
};


// An integer that may take the value v at some time : a value that may be invalid, or whose
// bound holds over the analysis horizon only, is any integer for all time
bool mayBeInteger(const itv::interval& i, double v);

// The divisor of an integer remainder in its defined form, select2(y == 0, y, 1) : y, the
// divisor whose 0 is replaced by 1
bool isGuardedDivisor(Tree d, Tree& y);

// The divisor the defined form takes in absolute value : never -1, whatever its interval
// (the absolute value of an integer is 0 or more, or -2147483648)
bool isAbsDivisor(Tree d);

// The conversion of the real x to an integer, defined for every value of its interval xi :
// NaN gives nan, 0 for a conversion of the program, a value beyond the integers saturates
// to their bounds
Tree definedIntCast(Tree x, const itv::interval& xi, int nan = 0);

// Public API
Tree signalPromote(Tree sig);
Tree signalBool2IntPromote(Tree sig);
Tree signalTablePromote(Tree sig);
Tree signalIntCastPromote(Tree sig);
Tree signalUIPromote(Tree sig);
Tree signalUIFreezePromote(Tree sig);
Tree signalFTZPromote(Tree sig);
// The nature of a power of integers, decided once : a pow(x, k) of integers whose exponent
// is not proven >= 0 by its sign becomes the real power of integers
Tree signalPowerNaturePromote(Tree sig);

#endif
