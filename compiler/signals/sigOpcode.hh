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
    Projection,
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
    Tuple,
    TupleAccess,
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

}  // namespace sigs
