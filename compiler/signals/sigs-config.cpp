/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#include "sigs-config.hh"

#include "sigOpcode.hh"
#include "sigs-state.hh"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace sigs {

void initSignalSymbols()
{
    const Signature signal_signature = signalSignature();

    // Every SIG* symbol is a constructor of the Signal language. Keeping
    // these add() calls in SignalOpcode declaration order makes their dense
    // local opcodes usable directly by folds without a translation table.
    g.SIGINPUT           = signal_signature.add("SigInput");
    g.SIGOUTPUT          = signal_signature.add("SigOutput");
    g.SIGDELAY1          = signal_signature.add("SigDelay1");
    g.SIGDELAY           = signal_signature.add("SigDelay");
    g.SIGPREFIX          = signal_signature.add("SigPrefix");
    g.SIGRDTBL           = signal_signature.add("SigRDTbl");
    g.SIGWRTBL           = signal_signature.add("SigWRTbl");
    g.SIGGEN             = signal_signature.add("SigGen");
    g.SIGDOCONSTANTTBL   = signal_signature.add("SigDocConstantTbl");
    g.SIGDOCWRITETBL     = signal_signature.add("SigDocWriteTbl");
    g.SIGDOCACCESSTBL    = signal_signature.add("SigDocAccessTbl");
    g.SIGSELECT2         = signal_signature.add("SigSelect2");
    g.SIGASSERTBOUNDS    = signal_signature.add("sigAssertBounds");
    g.SIGHIGHEST         = signal_signature.add("sigHighest");
    g.SIGLOWEST          = signal_signature.add("sigLowest");
    g.SIGBINOP           = signal_signature.add("SigBinOp");
    g.SIGFFUN            = signal_signature.add("SigFFun");
    g.SIGFCONST          = signal_signature.add("SigFConst");
    g.SIGFVAR            = signal_signature.add("SigFVar");
    g.SIGPROJ            = signal_signature.add("SigProj");
    g.SIGINTCAST         = signal_signature.add("SigIntCast");
    g.SIGBITCAST         = signal_signature.add("SigBitCast");
    g.SIGFLOATCAST       = signal_signature.add("SigFloatCast");
    g.SIGBUTTON          = signal_signature.add("SigButton");
    g.SIGCHECKBOX        = signal_signature.add("SigCheckbox");
    g.SIGWAVEFORM        = signal_signature.add("SigWaveform");
    g.SIGHSLIDER         = signal_signature.add("SigHSlider");
    g.SIGVSLIDER         = signal_signature.add("SigVSlider");
    g.SIGNUMENTRY        = signal_signature.add("SigNumEntry");
    g.SIGHBARGRAPH       = signal_signature.add("SigHBargraph");
    g.SIGVBARGRAPH       = signal_signature.add("SigVBargraph");
    g.SIGATTACH          = signal_signature.add("SigAttach");
    g.SIGENABLE          = signal_signature.add("SigEnable");
    g.SIGCONTROL         = signal_signature.add("SigControl");
    g.SIGSOUNDFILE       = signal_signature.add("SigSoundfile");
    g.SIGSOUNDFILELENGTH = signal_signature.add("SigSoundfileLength");
    g.SIGSOUNDFILERATE   = signal_signature.add("SigSoundfileRate");
    g.SIGSOUNDFILEBUFFER = signal_signature.add("SigSoundfileBuffer");
    g.SIGREGISTER        = signal_signature.add("SigRegister");
    g.SIGTUPLE           = signal_signature.add("SigTuple");
    g.SIGTUPLEACCESS     = signal_signature.add("SigTupleAccess");
}

/**
 * Default real printer: shortest "%g" form that round-trips to the same
 * double, with a trailing ".0" added when the result would read as an int.
 */
static std::string defaultRealPrinter(double n)
{
    char c[64];
    for (int p = 1; p <= 32; p++) {
        snprintf(c, sizeof(c), "%.*g", p, n);
        if (strtod(c, nullptr) == n) {
            break;
        }
    }
    if (strcspn(c, ".e") == strlen(c)) {
        strncat(c, ".0", sizeof(c) - strlen(c) - 1);
    }
    return std::string(c);
}

static RealPrinter gRealPrinter = defaultRealPrinter;

RealPrinter setRealPrinter(RealPrinter p)
{
    RealPrinter old = gRealPrinter;
    gRealPrinter    = (p != nullptr) ? p : defaultRealPrinter;
    return old;
}

std::string printReal(double n)
{
    return gRealPrinter(n);
}

}  // namespace sigs
