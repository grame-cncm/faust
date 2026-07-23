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

/** \file sigs-state.hh
 * State of the signal library.
 *
 * Storage for the symbols, property keys, type singletons, session state,
 * options and extended-primitive registry of the signal library. The Faust
 * compiler binds the corresponding members of 'global' as references to this
 * state, so every existing gGlobal-> read and write keeps working unchanged.
 */

#ifndef __SIGS_STATE__
#define __SIGS_STATE__

#include <map>
#include <string>
#include <vector>

#include "property.hh"
#include "sigs-export.hh"
#include "smartpointer.hh"
#include "tree.hh"

class AudioType;
typedef P<AudioType> Type;
class xtended;

namespace sigs {

struct State {
    int                                         gFloatSize{};  // -single/double/quad/fx option (1 for 'float', 2 for 'double', 3 for 'quad',
    int                                         gWideningLimit{};   // Max number of iterations before interval widening
    int                                         gNarrowingLimit{};  // Max number of iterations to compute interval widener
    Tabber                                      TABBER{};
    std::map<Tree, std::pair<int, std::string>> gSignalTable{};
    int                                         gSignalCounter{};
    std::vector<std::string>                    gSignalTrace{};
    int                                         gCountInferences{};
    // Instrumentation for the planned kContainsRec optimization : count the inferences run
    // on a rec-free node that ALREADY carried a type. Those are exactly the ones the
    // optimization would skip, since nothing below such a node can move during a fixpoint
    // iteration. gCountRecFreeChanged counts how many of them nevertheless produced a
    // DIFFERENT type -- it must stay at 0, otherwise the hypothesis is wrong.
    int                                         gCountRecFreeRedundant{};
    int                                         gCountRecFreeChanged{};
    bool                                        gTypeStatistics{};  // print them after typeAnnotation
    int                                         gCountMaximal{};
    int                                         gAllocationCount{};  // Internal signal types counter
    bool                                        gCausality{};  // FIXME: global used as a parameter of typeAnnotation when true trigs
    Tree                                        ORDERPROP{};
    Tree                                        RECURSIVNESS{};
    Tree                                        NULLTYPEENV{};
    xtended*                                    gAbsPrim{};
    xtended*                                    gAcosPrim{};
    xtended*                                    gTanPrim{};
    xtended*                                    gSqrtPrim{};
    xtended*                                    gSinPrim{};
    xtended*                                    gRintPrim{};
    xtended*                                    gRemainderPrim{};
    xtended*                                    gPowPrim{};
    xtended*                                    gMinPrim{};
    xtended*                                    gMaxPrim{};
    xtended*                                    gLogPrim{};
    xtended*                                    gLog10Prim{};
    xtended*                                    gFmodPrim{};
    xtended*                                    gFloorPrim{};
    xtended*                                    gExpPrim{};
    xtended*                                    gExp10Prim{};
    xtended*                                    gCosPrim{};
    xtended*                                    gCeilPrim{};
    xtended*                                    gAtanPrim{};
    xtended*                                    gAtan2Prim{};
    xtended*                                    gAsinPrim{};
    property<Tree>*                             gSymListProp{};
    property<AudioType*>*                       gMemoizedTypes{};
    Sym                                         FFUN{};
    Sym                                         SIGINPUT{};
    Sym                                         SIGOUTPUT{};
    Sym                                         SIGDELAY1{};
    Sym                                         SIGDELAY{};
    Sym                                         SIGPREFIX{};
    Sym                                         SIGRDTBL{};
    Sym                                         SIGWRTBL{};
    Sym                                         SIGGEN{};
    Sym                                         SIGDOCONSTANTTBL{};
    Sym                                         SIGDOCWRITETBL{};
    Sym                                         SIGDOCACCESSTBL{};
    Sym                                         SIGSELECT2{};
    Sym                                         SIGASSERTBOUNDS{};
    Sym                                         SIGHIGHEST{};
    Sym                                         SIGLOWEST{};
    Sym                                         SIGBINOP{};
    Sym                                         SIGFFUN{};
    Sym                                         SIGFCONST{};
    Sym                                         SIGFVAR{};
    Sym                                         SIGINTCAST{};
    Sym                                         SIGBITCAST{};
    Sym                                         SIGFLOATCAST{};
    Sym                                         SIGBUTTON{};
    Sym                                         SIGCHECKBOX{};
    Sym                                         SIGWAVEFORM{};
    Sym                                         SIGHSLIDER{};
    Sym                                         SIGVSLIDER{};
    Sym                                         SIGNUMENTRY{};
    Sym                                         SIGHBARGRAPH{};
    Sym                                         SIGVBARGRAPH{};
    Sym                                         SIGATTACH{};
    Sym                                         SIGENABLE{};
    Sym                                         SIGCONTROL{};
    Sym                                         SIGSOUNDFILE{};
    Sym                                         SIGSOUNDFILELENGTH{};
    Sym                                         SIGSOUNDFILERATE{};
    Sym                                         SIGSOUNDFILEBUFFER{};
    Sym                                         SIGREGISTER{};  // for FPGA Retiming
    Sym                                         SIGTUPLE{};
    Sym                                         SIGTUPLEACCESS{};
    Sym                                         SIMPLETYPE{};
    Sym                                         TABLETYPE{};
    Sym                                         TUPLETTYPE{};
    Type                                        TINPUT{};
    Type                                        TGUI{};
    Type                                        TREC{};  // kVect ou kScal ?
    Type                                        TRECMAX{};
};

/// The state of the signal library (one per process, like tlib).
SIGS_API extern State g;

}  // namespace sigs

// Limits of the signal library, shared with the host compiler (global.hh
// carries the same definitions; identical redefinition is legal)
#define MAX_SOUNDFILE_PARTS 256
#define MAX_ERROR_SIZE 192

#endif
