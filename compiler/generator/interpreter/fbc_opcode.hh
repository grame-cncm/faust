/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef _FBC_OPCODE_H
#define _FBC_OPCODE_H

#include <map>
#include <string>

// Interpreter

struct FBCInstruction {
    enum Opcode {

        // Numbers
        kRealValue,
        kInt32Value,

        // Memory
        kLoadReal,
        kLoadInt,
        kLoadSound,
        kLoadSoundField,
        kStoreReal,
        kStoreInt,
        kStoreSound,
        kStoreRealValue,
        kStoreIntValue,
        kLoadIndexedReal,
        kLoadIndexedInt,
        kStoreIndexedReal,
        kStoreIndexedInt,
        kBlockStoreReal,
        kBlockStoreInt,
        kMoveReal,
        kMoveInt,
        kPairMoveReal,
        kPairMoveInt,
        kBlockPairMoveReal,
        kBlockPairMoveInt,
        kBlockShiftReal,
        kBlockShiftInt,
        kLoadInput,
        kStoreOutput,

        // Cast/Bitcast
        kCastReal,
        kCastInt,
        kCastRealHeap,
        kCastIntHeap,
        kBitcastInt,
        kBitcastReal,

        // Standard math (stack OP stack)
        kAddReal,
        kAddInt,
        kSubReal,
        kSubInt,
        kMultReal,
        kMultInt,
        kDivReal,
        kDivInt,
        kRemReal,
        kRemInt,
        kLshInt,
        kARshInt,
        kLRshInt,
        kGTInt,
        kLTInt,
        kGEInt,
        kLEInt,
        kEQInt,
        kNEInt,
        kGTReal,
        kLTReal,
        kGEReal,
        kLEReal,
        kEQReal,
        kNEReal,
        kANDInt,
        kORInt,
        kXORInt,

        // Standard math (heap OP heap)
        kAddRealHeap,
        kAddIntHeap,
        kSubRealHeap,
        kSubIntHeap,
        kMultRealHeap,
        kMultIntHeap,
        kDivRealHeap,
        kDivIntHeap,
        kRemRealHeap,
        kRemIntHeap,
        kLshIntHeap,
        kARshIntHeap,
        kLRshIntHeap,
        kGTIntHeap,
        kLTIntHeap,
        kGEIntHeap,
        kLEIntHeap,
        kEQIntHeap,
        kNEIntHeap,
        kGTRealHeap,
        kLTRealHeap,
        kGERealHeap,
        kLERealHeap,
        kEQRealHeap,
        kNERealHeap,
        kANDIntHeap,
        kORIntHeap,
        kXORIntHeap,

        // Standard math (heap OP stack)
        kAddRealStack,
        kAddIntStack,
        kSubRealStack,
        kSubIntStack,
        kMultRealStack,
        kMultIntStack,
        kDivRealStack,
        kDivIntStack,
        kRemRealStack,
        kRemIntStack,
        kLshIntStack,
        kARshIntStack,
        kLRshIntStack,
        kGTIntStack,
        kLTIntStack,
        kGEIntStack,
        kLEIntStack,
        kEQIntStack,
        kNEIntStack,
        kGTRealStack,
        kLTRealStack,
        kGERealStack,
        kLERealStack,
        kEQRealStack,
        kNERealStack,
        kANDIntStack,
        kORIntStack,
        kXORIntStack,

        // Standard math (heap OP stack)
        kAddRealStackValue,
        kAddIntStackValue,
        kSubRealStackValue,
        kSubIntStackValue,
        kMultRealStackValue,
        kMultIntStackValue,
        kDivRealStackValue,
        kDivIntStackValue,
        kRemRealStackValue,
        kRemIntStackValue,
        kLshIntStackValue,
        kARshIntStackValue,
        kLRshIntStackValue,
        kGTIntStackValue,
        kLTIntStackValue,
        kGEIntStackValue,
        kLEIntStackValue,
        kEQIntStackValue,
        kNEIntStackValue,
        kGTRealStackValue,
        kLTRealStackValue,
        kGERealStackValue,
        kLERealStackValue,
        kEQRealStackValue,
        kNERealStackValue,
        kANDIntStackValue,
        kORIntStackValue,
        kXORIntStackValue,

        // Standard math (value OP heap)
        kAddRealValue,
        kAddIntValue,
        kSubRealValue,
        kSubIntValue,
        kMultRealValue,
        kMultIntValue,
        kDivRealValue,
        kDivIntValue,
        kRemRealValue,
        kRemIntValue,
        kLshIntValue,
        kARshIntValue,
        kLRshIntValue,
        kGTIntValue,
        kLTIntValue,
        kGEIntValue,
        kLEIntValue,
        kEQIntValue,
        kNEIntValue,
        kGTRealValue,
        kLTRealValue,
        kGERealValue,
        kLERealValue,
        kEQRealValue,
        kNERealValue,
        kANDIntValue,
        kORIntValue,
        kXORIntValue,

        // Standard math (value OP heap) : non commutative operations
        kSubRealValueInvert,
        kSubIntValueInvert,
        kDivRealValueInvert,
        kDivIntValueInvert,
        kRemRealValueInvert,
        kRemIntValueInvert,
        kLshIntValueInvert,
        kARshIntValueInvert,
        kLRshIntValueInvert,
        kGTIntValueInvert,
        kLTIntValueInvert,
        kGEIntValueInvert,
        kLEIntValueInvert,
        kGTRealValueInvert,
        kLTRealValueInvert,
        kGERealValueInvert,
        kLERealValueInvert,

        // Extended unary math
        kAbs,
        kAbsf,
        kAcosf,
        kAcoshf,
        kAsinf,
        kAsinhf,
        kAtanf,
        kAtanhf,
        kCeilf,
        kCosf,
        kCoshf,
        kExpf,
        kFloorf,
        kLogf,
        kLog10f,
        kRintf,
        kRoundf,
        kSinf,
        kSinhf,
        kSqrtf,
        kTanf,
        kTanhf,
        kIsnanf,
        kIsinff,

        // Extended unary math (heap OP)
        kAbsHeap,
        kAbsfHeap,
        kAcosfHeap,
        kAcoshfHeap,
        kAsinfHeap,
        kAsinhfHeap,
        kAtanfHeap,
        kAtanhfHeap,
        kCeilfHeap,
        kCosfHeap,
        kCoshfHeap,
        kExpfHeap,
        kFloorfHeap,
        kLogfHeap,
        kLog10fHeap,
        kRintfHeap,
        kRoundfHeap,
        kSinfHeap,
        kSinhfHeap,
        kSqrtfHeap,
        kTanfHeap,
        kTanhfHeap,

        // Extended binary math
        kAtan2f,
        kFmodf,
        kPowf,
        kMax,
        kMaxf,
        kMin,
        kMinf,

        // Extended binary math (heap OP heap)
        kAtan2fHeap,
        kFmodfHeap,
        kPowfHeap,
        kMaxHeap,
        kMaxfHeap,
        kMinHeap,
        kMinfHeap,

        // Extended binary math (heap OP stack)
        kAtan2fStack,
        kFmodfStack,
        kPowfStack,
        kMaxStack,
        kMaxfStack,
        kMinStack,
        kMinfStack,

        // Extended binary math (value OP stack)
        kAtan2fStackValue,
        kFmodfStackValue,
        kPowfStackValue,
        kMaxStackValue,
        kMaxfStackValue,
        kMinStackValue,
        kMinfStackValue,

        // Extended binary math (value OP heap)
        kAtan2fValue,
        kFmodfValue,
        kPowfValue,
        kMaxValue,
        kMaxfValue,
        kMinValue,
        kMinfValue,

        // Extended binary math (value OP heap) : non commutative operations
        kAtan2fValueInvert,
        kFmodfValueInvert,
        kPowfValueInvert,

        // Control
        kLoop,
        kReturn,

        // Select/if
        kIf,
        kSelectReal,
        kSelectInt,
        kCondBranch,

        // User Interface
        kOpenVerticalBox,
        kOpenHorizontalBox,
        kOpenTabBox,
        kCloseBox,
        kAddButton,
        kAddCheckButton,
        kAddHorizontalSlider,
        kAddVerticalSlider,
        kAddNumEntry,
        kAddSoundfile,
        kAddHorizontalBargraph,
        kAddVerticalBargraph,
        kDeclare,

        kNop,
    };

    virtual ~FBCInstruction() {}

    virtual int size() { return 1; }

    static bool isRealType(Opcode opt)
    {
        return ((opt == kRealValue)

                || (opt == kLoadReal) || (opt == kLoadIndexedReal) || (opt == kLoadInput)

                || (opt == kCastReal) || (opt == kBitcastReal)

                || (opt == kSelectReal)

                || (opt == kAddReal) || (opt == kSubReal) || (opt == kMultReal) || (opt == kDivReal) ||
                (opt == kRemReal)

                || (opt == kAbsf)
                || (opt == kAcosf) || (opt == kAcoshf)
                || (opt == kAsinf) || (opt == kAsinhf)
                || (opt == kAtanf) || (opt == kAtanhf)
                || (opt == kCeilf) ||
                (opt == kCosf) || (opt == kCoshf) || (opt == kExpf) || (opt == kFloorf) || (opt == kLogf) ||
                (opt == kLog10f) || (opt == kRintf) || (opt == kRoundf) || (opt == kSinf) || (opt == kSinhf) || (opt == kSqrtf) ||
                (opt == kTanf) || (opt == kTanhf)

                || (opt == kAtan2f) || (opt == kFmodf) || (opt == kPowf) || (opt == kMaxf) || (opt == kMinf));
    }

    static bool isMath(Opcode opt) { return (opt >= kAddReal) && (opt <= kXORInt); }
    static bool isExtendedUnaryMath(Opcode opt) { return (opt >= kAbs) && (opt <= kTanhf); }
    static bool isExtendedBinaryMath(Opcode opt) { return (opt >= kAtan2f) && (opt <= kMinf); }
    static bool isChoice(Opcode opt) { return (opt == kIf) || (opt == kSelectReal) || (opt == kSelectInt); }
};

static std::string gFBCInstructionTable[] = {

    // Numbers
    "kRealValue", "kInt32Value",

    // Memory
    "kLoadReal", "kLoadInt", "kLoadSound", "kLoadSoundField", "kStoreReal", "kStoreInt", "kStoreSound",
    "kStoreRealValue", "kStoreIntValue", "kLoadIndexedReal", "kLoadIndexedInt", "kStoreIndexedReal", "kStoreIndexedInt",
    "kBlockStoreReal", "kBlockStoreInt", "kMoveReal", "kMoveInt", "kPairMoveReal", "kPairMoveInt", "kBlockPairMoveReal",
    "kBlockPairMoveInt", "kBlockShiftReal", "kBlockShiftInt", "kLoadInput", "kStoreOutput",

    // Cast/Bitcast
    "kCastReal", "kCastInt", "kCastRealHeap", "kCastIntHeap", "kBitcastInt", "kBitcastReal",

    // Standard math (stack OP stack)
    "kAddReal", "kAddInt", "kSubReal", "kSubInt", "kMultReal", "kMultInt", "kDivReal", "kDivInt", "kRemReal", "kRemInt",
    "kLshInt", "kARshInt", "kLRshInt", "kGTInt", "kLTInt", "kGEInt", "kLEInt", "kEQInt", "kNEInt", "kGTReal", "kLTReal", "kGEReal",
    "kLEReal", "kEQReal", "kNEReal", "kANDInt", "kORInt", "kXORInt",

    // Standard math (heap OP heap)
    "kAddRealHeap", "kAddIntHeap", "kSubRealHeap", "kSubIntHeap", "kMultRealHeap", "kMultIntHeap", "kDivRealHeap",
    "kDivIntHeap", "kRemRealHeap", "kRemIntHeap", "kLshIntHeap", "kARshIntHeap", "kLRshIntHeap", "kGTIntHeap", "kLTIntHeap",
    "kGEIntHeap", "kLEIntHeap", "kEQIntHeap", "kNEIntHeap", "kGTRealHeap", "kLTRealHeap", "kGERealHeap", "kLERealHeap",
    "kEQRealHeap", "kNERealHeap", "kANDIntHeap", "kORIntHeap", "kXORIntHeap",

    // Standard math (heap OP stack)
    "kAddRealStack", "kAddIntStack", "kSubRealStack", "kSubIntStack", "kMultRealStack", "kMultIntStack",
    "kDivRealStack", "kDivIntStack", "kRemRealStack", "kRemIntStack", "kLshIntStack", "kARshIntStack", "kLRshIntStack", "kGTIntStack",
    "kLTIntStack", "kGEIntStack", "kLEIntStack", "kEQIntStack", "kNEIntStack", "kGTRealStack", "kLTRealStack",
    "kGERealStack", "kLERealStack", "kEQRealStack", "kNERealStack", "kANDIntStack", "kORIntStack", "kXORIntStack",

    // Standard math (value OP stack)
    "kAddRealStackValue", "kAddIntStackValue", "kSubRealStackValue", "kSubIntStackValue", "kMultRealStackValue",
    "kMultIntStackValue", "kDivRealStackValue", "kDivIntStackValue", "kRemRealStackValue", "kRemIntStackValue",
    "kLshIntStackValue", "kARshIntStackValue", "kLRshIntStackValue", "kGTIntStackValue", "kLTIntStackValue", "kGEIntStackValue",
    "kLEIntStackValue", "kEQIntStackValue", "kNEIntStackValue", "kGTRealStackValue", "kLTRealStackValue",
    "kGERealStackValue", "kLERealStackValue", "kEQRealStackValue", "kNERealStackValue", "kANDIntStackValue",
    "kORIntStackValue", "kXORIntStackValue",

    // Standard math (value OP heap)
    "kAddRealValue", "kAddIntValue", "kSubRealValue", "kSubIntValue", "kMultRealValue", "kMultIntValue",
    "kDivRealValue", "kDivIntValue", "kRemRealValue", "kRemIntValue", "kLshIntValue", "kARshIntValue", "kLRshIntValue", "kGTIntValue",
    "kLTIntValue", "kGEIntValue", "kLEIntValue", "kEQIntValue", "kNEIntValue", "kGTRealValue", "kLTRealValue",
    "kGERealValue", "kLERealValue", "kEQRealValue", "kNERealValue", "kANDIntValue", "kORIntValue", "kXORIntValue",

    // Standard math (value OP heap) : non commutative operations
    "kSubRealValueInvert", "kSubIntValueInvert", "kDivRealValueInvert", "kDivIntValueInvert", "kRemRealValueInvert",
    "kRemIntValueInvert", "kLshIntValueInvert", "kARshIntValueInvert", "kLRshIntValueInvert", "kGTIntValueInvert", "kLTIntValueInvert",
    "kLTIntValueInvert", "kLEIntValueInvert", "kGTRealValueInvert", "kLTRealValueInvert", "kGERealValueInvert",
    "kLERealValueInvert",

    // Extended unary math
    "kAbs", "kAbsf", "kAcosf", "kAcoshf", "kAsinf", "kAsinhf", "kAtanf", "kAtanhf", "kCeilf", "kCosf", "kCoshf", "kExpf", "kFloorf", "kLogf", "kLog10f",
    "kRintf", "kRoundf", "kSinf", "kSinhf", "kSqrtf", "kTanf", "kTanhf", "kIsnanf", "kIsinff",

    // Extended unary math (heap OP heap)
    "kAbsHeap", "kAbsfHeap", "kAcosfHeap", "kAcoshfHeap", "kAsinfHeap", "kAsinhfHeap", "kAtanfHeap", "kAtanhfHeap", "kCeilfHeap", "kCosfHeap", "kCoshfHeap",
    "kExpfHeap", "kFloorfHeap", "kLogfHeap", "kLog10fHeap", "kRintfHeap", "kRoundfHeap", "kSinfHeap", "kSinhfHeap", "kSqrtfHeap",
    "kTanfHeap", "kTanhfHeap",

    // Extended binary math
    "kAtan2f", "kFmodf", "kPowf", "kMax", "kMaxf", "kMin", "kMinf",

    // Extended binary math (heap version)
    "kAtan2fHeap", "kFmodfHeap", "kPowfHeap", "kMaxHeap", "kMaxfHeap", "kMinHeap", "kMinfHeap",

    // Extended binary math (stack version)
    "kAtan2fStack", "kFmodfStack", "kPowfStack", "kMaxStack", "kMaxfStack", "kMinStack", "kMinfStack",

    // Extended binary math (Stack/Value version)
    "kAtan2fStackValue", "kFmodfStackValue", "kPowfStackValue", "kMaxStackValue", "kMaxStackfValue", "kMinStackValue",
    "kMinfStackValue",

    // Extended binary math (Value version)
    "kAtan2fValue", "kFmodfValue", "kPowfValue", "kMaxValue", "kMaxfValue", "kMinValue", "kMinfValue",

    // Extended binary math (Value version) : non commutative operations
    "kAtan2fValueInvert", "kFmodfValueInvert", "kPowfValueInvert",

    // Control
    "kLoop", "kReturn",

    // Select/if
    "kIf", "kSelectReal", "kSelectInt", "kCondBranch",

    // User Interface
    "kOpenVerticalBox", "kOpenHorizontalBox", "kOpenTabBox", "kCloseBox", "kAddButton", "kAddChecButton",
    "kAddHorizontalSlider", "kAddVerticalSlider", "kAddNumEntry", "kAddSoundfile", "kAddHorizontalBargraph",
    "kAddVerticalBargraph", "kDeclare",

    "kNop"};

#define INTERP_FILE_VERSION 8

#endif
