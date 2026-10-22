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

#include <cstdint>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

#include "property.hh"
#include "sigs-export.hh"
#include "smartpointer.hh"
#include "tree.hh"

class AudioType;
typedef P<AudioType> Type;

/**
 * The key of a simple type in the table of the memoized types : all its attributes,
 * the bounds of its interval compared bit for bit, its grid and its possible
 * invalidity. A plain value : coding a type creates no tree, so the typing leaves the
 * trees of the program, and their creation order, untouched.
 */
struct SimpleTypeKey {
    int           nature, variability, computability, vectorability, boolean;
    std::uint64_t lo, hi;  ///< the bit patterns of the bounds
    int           lsb;
    bool          mayBeInvalid;
    bool          mayOverflow;  ///< the int32 operation may wrap
    bool          loMoves, hiMoves;  ///< the bounds that hold over the horizon only
    bool          resValid;
    int           resIndex;

    bool operator==(const SimpleTypeKey& k) const
    {
        return nature == k.nature && variability == k.variability &&
               computability == k.computability && vectorability == k.vectorability &&
               boolean == k.boolean && lo == k.lo && hi == k.hi && lsb == k.lsb &&
               mayBeInvalid == k.mayBeInvalid && mayOverflow == k.mayOverflow &&
               loMoves == k.loMoves && hiMoves == k.hiMoves &&
               resValid == k.resValid &&
               resIndex == k.resIndex;
    }
};

struct SimpleTypeKeyHash {
    std::size_t operator()(const SimpleTypeKey& k) const
    {
        std::uint64_t h = 1469598103934665603ULL;  // FNV-1a over the fields
        auto mix = [&h](std::uint64_t x) {
            h ^= x;
            h *= 1099511628211ULL;
        };
        mix(std::uint64_t(k.nature));
        mix(std::uint64_t(k.variability));
        mix(std::uint64_t(k.computability));
        mix(std::uint64_t(k.vectorability));
        mix(std::uint64_t(k.boolean));
        mix(k.lo);
        mix(k.hi);
        mix(std::uint64_t(std::uint32_t(k.lsb)));
        mix(std::uint64_t(k.mayBeInvalid));
        mix(std::uint64_t(k.mayOverflow));
        mix(std::uint64_t(k.loMoves) | (std::uint64_t(k.hiMoves) << 1));
        mix(std::uint64_t(k.resValid));
        mix(std::uint64_t(std::uint32_t(k.resIndex)));
        return std::size_t(h);
    }
};
class xtended;
class TreeAlgebra;

namespace sigs {

// Consumer kind bit, carried as DATA on the interned symbols (see tree.hh
// and symbol.hh : Signature::add(name, kinds) at registration) and folded by
// the tree layer into every tree headed by them : "audio-rate temporality
// occurs in this subtree". Carriers are the constructors whose result is
// audio rate even when every argument is slow (inputs, projections, delays,
// tables, waveforms, IIR -- what the retired sigorderrules called the
// unconditional order-3 cases) ; every other constructor inherits by the union
// convention. 1@1 is the witness that delays must declare : delaying a
// constant still yields a sample-rate signal.
enum : unsigned int { kAudioRate = 1u << 4 };

// Order bits : the 4-level classification of the historical sigorderrules
// (0 numbers, 1 constants, 2 user interface, 3 audio) encoded as
// existential bits -- "a carrier of this level reaches me". The max of
// the order lattice and the union of the bits coincide because every
// inference rule is either a carrier declaration or a max of the
// children (checked exhaustively, xtended included). The audio level
// reads kAudioRate itself : select2's historical pessimism (order 3
// unconditionally) was judged and dropped (exp-select2fin-20260809 :
// control-rate selections hoist, sawtoothLab x1.55), which made the
// separate order-audio bit the exact duplicate of kAudioRate. Known
// over-approximations inherited from the union rule : ffun with slow
// arguments (precedent : FFUN declares kAudioRate unconditionally) and
// attach, whose historical order ignores its second branch.
enum : unsigned int {
    kOrderCtrl  = 1u << 6,  ///< an order-2 carrier occurs (UI, fvariable...)
    kOrderConst = 1u << 7,  ///< an order-1 carrier occurs (fconstant...)
};

///< true iff audio-rate temporality occurs in this signal, by construction
inline bool isAudioRate(Tree t)
{
    return (t->contains() & kAudioRate) != 0;
}

///< order 0-4 of a signal (numbers / constants / UI / audio /
///< audio-recursive), read from the kind bits : highest level present,
///< O(1), total domain. Level 4 is tlib's own kContainsRec bit : "a
///< recursive node reaches me" == "I depend on some state" (inside a
///< definition too : a self-reference is proj(i, SYMREC), the rec node
///< closes its knot through the RECDEF property, not a branch, so the
///< bit stays honest). Known pessimisms : SOME state (not necessarily
///< my own), and table generators whose init-time recursions count.
inline int sigOrder(Tree t)
{
    unsigned int k = t->contains();
    if (t->containsRec()) {
        return 4;
    }
    if (k & kAudioRate) {
        return 3;
    }
    if (k & kOrderCtrl) {
        return 2;
    }
    if (k & kOrderConst) {
        return 1;
    }
    return 0;
}

struct State {
    int                                         gFloatSize{};  // -single/double/quad/fx option (1 for 'float', 2 for 'double', 3 for 'quad',
    Tabber                                      TABBER{};
    std::map<Tree, std::pair<int, std::string>, treeorder> gSignalTable{};
    int                                         gSignalCounter{};
    std::vector<std::string>                    gSignalTrace{};
    // Validity certificates of the interval analysis : a rule that bounds a signal only
    // for a limited number of samples records it here, keyed by its reason (the
    // smallest count wins). The compiler reports them, by default.
    std::map<std::string, double>               gCertifiedSamples{};
    // -nocert : a delay of proven upper bound whose lower bound may be negative, and a
    // soundfile part beyond its range, are accepted and held within their range at run time
    // instead of refused ; each waiver is recorded here, for the compiler to report
    bool                                        gNoCertification{};
    std::vector<std::string>                    gCertificationWaivers{};
    int                                         gAllocationCount{};  // Internal signal types counter
    bool                                        gCausality{};  // FIXME: global used as a parameter of typeAnnotation when true trigs
    Tree                                        RECURSIVNESS{};
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
    std::unordered_map<SimpleTypeKey, AudioType*, SimpleTypeKeyHash> gMemoizedTypes;
    Sym                                         FFUN{};
    Sym                                         SIGINPUT{};
    Sym                                         SIGOUTPUT{};
    Sym                                         SIGDELAY1{};
    Sym                                         SIGDELAY{};
    Sym                                         SIGFIR{};
    Sym                                         SIGIIR{};
    Sym                                         SIGSUM{};
    Sym                                         SIGTEMP{};
    Sym                                         SIGFRAC{};
    Sym                                         SIGCFRAC{};
    Sym                                         SIGMIX{};
    Sym                                         SIGTPT{};
    Sym                                         SIGNEG{};
    Sym                                         SIGPROD{};
    Sym                                         SIGPHASE{};
    Sym                                         SIGIRM{};
    Sym                                         SIGBPF{};
    int                                         gMaxFIRSize{1024};  // -mfs threshold (port)
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

    /// The initial algebra of the session, rebuilt by initSignalSymbols(): its
    /// dispatch signature dies with the tlib session, so its lifetime is one
    /// compilation. The sigXXX constructors are a facade over it.
    TreeAlgebra* gTreeAlgebra{};
};

/// The state of the signal library (one per process, like tlib).
SIGS_API extern State g;

/// The initial algebra of the current session (built by initSignalSymbols()).
SIGS_API const TreeAlgebra& algebra();

}  // namespace sigs

// Limits of the signal library, shared with the host compiler (global.hh
// carries the same definitions; identical redefinition is legal)
#define MAX_SOUNDFILE_PARTS 256
#define MAX_ERROR_SIZE 192

#endif
