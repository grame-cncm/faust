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

#include "interval.hh"
#include "sigOpcode.hh"
#include "sigtype.hh"

// The interval algebra used by the signal type system (declared in
// signals/interval.hh)
itv::interval_algebra gAlgebra;
#include "sigs-state.hh"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

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
 * Standalone initialization of the signal library state: signal symbols,
 * property keys, type singletons, session state and option defaults. NOT
 * called by the Faust compiler, which performs the same writes itself in
 * global.cpp (in its own, order-sensitive sequence); intended for standalone
 * hosts and tests. Requires tlib::init() first, and can be called again
 * between two sessions.
 */
void init()
{
    // Signal constructors (interned and registered in the Signal signature)
    initSignalSymbols();

    // Foreign function head and type constructors (ordinary symbols)
    g.FFUN       = symbol("ForeignFunction");
    g.SIMPLETYPE = symbol("SimpleType");
    g.TABLETYPE  = symbol("TableType");
    g.TUPLETTYPE = symbol("TupletType");

    // Property keys
    g.ORDERPROP    = tree(symbol("OrderProp"));
    g.RECURSIVNESS = tree(symbol("RecursivnessProp"));
    g.NULLTYPEENV  = tree(symbol("NullTypeEnv"));

    // Session state
    g.TABBER = Tabber(1);
    g.gSignalTable.clear();
    g.gSignalTrace.clear();
    g.gSignalCounter   = 0;
    g.gCountInferences = 0;
    g.gCountMaximal    = 0;
    g.gAllocationCount = 0;
    g.gSymListProp     = new property<Tree>();
    g.gMemoizedTypes   = new property<AudioType*>();

    // Option defaults (same values as global.cpp)
    g.gCausality      = false;
    g.gWideningLimit  = 0;
    g.gNarrowingLimit = 0;
    g.gFloatSize      = 1;

    // Extended primitive registry: empty in standalone mode (the concrete
    // primitives carry code generation and live in the compiler)
    g.gAbsPrim        = nullptr;
    g.gAcosPrim       = nullptr;
    g.gAsinPrim       = nullptr;
    g.gAtan2Prim      = nullptr;
    g.gAtanPrim       = nullptr;
    g.gCeilPrim       = nullptr;
    g.gCosPrim        = nullptr;
    g.gExp10Prim      = nullptr;
    g.gExpPrim        = nullptr;
    g.gFloorPrim      = nullptr;
    g.gFmodPrim       = nullptr;
    g.gLog10Prim      = nullptr;
    g.gLogPrim        = nullptr;
    g.gMaxPrim        = nullptr;
    g.gMinPrim        = nullptr;
    g.gPowPrim        = nullptr;
    g.gRemainderPrim  = nullptr;
    g.gRintPrim       = nullptr;
    g.gSinPrim        = nullptr;
    g.gSqrtPrim       = nullptr;
    g.gTanPrim        = nullptr;

    // Type singletons (require the interval algebra and gMemoizedTypes above)
    g.TINPUT  = makeSimpleType(kReal, kSamp, kExec, kVect, kNum, interval(-1, 1));
    g.TGUI    = makeSimpleType(kReal, kBlock, kExec, kVect, kNum, interval());
    g.TREC    = makeSimpleType(kInt, kSamp, kInit, kScal, kNum, interval(0, 0));
    g.TRECMAX = makeSimpleType(kInt, kSamp, kInit, kScal, kNum, interval(-HUGE_VAL, HUGE_VAL));
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
