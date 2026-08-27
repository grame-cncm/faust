/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    SPDX-License-Identifier: LGPL-2.1-or-later
 ************************************************************************
 ************************************************************************/


/** \file sigOpcode.hh
 * Dense constructor identities of the signal language, used to dispatch on
 * signal constructors by opcode instead of a linear chain of isSigXXX
 * predicates.
 */

#pragma once

#include <cstdint>

#include "sigs-export.hh"
#include "symbol.hh"
#include "tree.hh"

namespace sigs {

/**
 * Opcodes of the signal constructors.
 *
 * Declaration order must match the order of Signature::add() calls in
 * sigs::initSignalSymbols(), because TLIB assigns dense local opcodes
 * automatically. Values identify symbol-headed constructor families, not
 * atomic numeric leaves or the secondary operator stored inside SIGBINOP.
 */
enum class SignalOpcode : std::uint8_t {
    Input,
    Output,
    Delay1,
    Delay,
    Prefix,
    ReadTable,
    WriteTable,
    Generator,
    DocConstantTable,
    DocWriteTable,
    DocAccessTable,
    Select2,
    AssertBounds,
    Highest,
    Lowest,
    BinOp,
    ForeignFunction,
    ForeignConstant,
    ForeignVariable,
    // Projection moved to tlib (proj/isProj), out of the signal signature.
    IntCast,
    BitCast,
    FloatCast,
    Button,
    Checkbox,
    Waveform,
    HSlider,
    VSlider,
    NumEntry,
    HBargraph,
    VBargraph,
    Attach,
    Enable,
    Control,
    Soundfile,
    SoundfileLength,
    SoundfileRate,
    SoundfileBuffer,
    Register,
    // port FIR/IIR : registered last in sigs-config (the registration
    // order assigns the dense local opcodes -- see the header comment)
    Fir,
    Iir,
    Sum,
    Temp,
    Count
};

static_assert(static_cast<std::uint16_t>(SignalOpcode::Count) <= kOpcodesPerSignature,
              "the Signal signature exceeds TLIB's constructor capacity");

/**
 * Return the interned signature shared by every registered signal constructor.
 *
 * The handle is looked up on every call rather than cached because a TLIB
 * cleanup/init cycle invalidates its identity and allocation state.
 */
SIGS_API Signature signalSignature();

/**
 * Return true and set \p op when the head of \p t is a constructor of the Signal
 * signature.
 *
 * Returns false for everything else a generic walk of a signal term also meets:
 * numeric leaves, labels, identifiers, lists, and nodes owned by another signature
 * (tlib's rec and proj, boxes). A caller dispatching on the result must therefore keep
 * a path for those.
 *
 * \p sigSignature is the handle returned by signalSignature(). It is a parameter rather
 * than an internal call because signalSignature() performs a registry lookup: a caller
 * dispatching on every node of a term should hoist it out of the walk.
 */
inline bool signalOpcode(Tree t, Signature sigSignature, SignalOpcode& op)
{
    Sym s;
    if (!isSym(t->node(), &s)) return false;
    SymbolTag tag;
    if (!getSymbolTag(s, tag)) return false;
    if (tag.signature != sigSignature.identity()) return false;
    op = static_cast<SignalOpcode>(tag.localOpcode());
    return true;
}

}  // namespace sigs
