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


// Public API
Tree signalPromote(Tree sig);
Tree signalBool2IntPromote(Tree sig);
Tree signalTablePromote(Tree sig);
Tree signalIntCastPromote(Tree sig);
Tree signalUIPromote(Tree sig);
Tree signalUIFreezePromote(Tree sig);
Tree signalFTZPromote(Tree sig);
#endif
