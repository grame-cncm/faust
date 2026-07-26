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

//-------------SignalAutoDifferentiate---------------
// Auto Differentiate a signal for a given variable
//--------------------------------------------------
class SignalAutoDifferentiate final : public SignalIdentity {
   private:
    Tree fVar;

    Tree sigZero(int type) { return (type == kInt) ? sigInt(0) : sigReal(0.0); }
    Tree sigOne(int type) { return (type == kInt) ? sigInt(1) : sigReal(1.0); }
    Tree diff(Tree x, int ty) { return (x == fVar) ? sigOne(ty) : sigZero(ty); }
    Tree transformation(Tree sig);

   public:
    // The variable with respect to which the differentiation is performed.
    SignalAutoDifferentiate(Tree var) : fVar(var)
    {
        if (gGlobal->gDetailsSwitch) {
            std::cout << ">>> Differentiate wrt. " << ppsig(var) << "\n";
        }
        // Go inside tables
        fVisitGen = true;
    }
};

struct DiffVarCollector : public SignalVisitor {
    siglist inputs;

    DiffVarCollector(Tree L)
    {
        while (!isNil(L)) {
            self(hd(L));
            L = tl(L);
        }
    }

    void visit(Tree sig)
    {
        Tree label, init, min, max, step;

        if (isSigButton(sig, label) || isSigCheckbox(sig, label) ||
            isSigVSlider(sig, label, init, min, max, step) ||
            isSigHSlider(sig, label, init, min, max, step) ||
            isSigNumEntry(sig, label, init, min, max, step)) {
            std::string                                   simplifiedLabel;
            std::map<std::string, std::set<std::string> > metadata;
            extractMetadata(tree2str(hd(label)), simplifiedLabel, metadata);

            // Look for [diff:1] or [diff:on]
            for (const auto& i : metadata) {
                if (i.first == "diff") {
                    const std::set<std::string>& values = i.second;
                    for (const auto& j : values) {
                        if (j == "1" || j == "on") {
                            inputs.push_back(sig);
                            break;
                        }
                    }
                }
            }
        } else {
            SignalVisitor::visit(sig);
        }
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
Tree signalAutoDifferentiate(Tree sig);
#endif
