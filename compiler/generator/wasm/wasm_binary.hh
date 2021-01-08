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

#ifndef _WASM_BINARY_H
#define _WASM_BINARY_H

#include <string.h>
#include <cmath>
#include <functional>
#include <vector>

#include "exception.hh"

using namespace std;

// Type punning needs to be done through this function to avoid undefined
// behavior: unions and reinterpret_cast aren't valid approaches.
template <class Destination, class Source>
inline Destination bit_cast(const Source& source)
{
    Destination destination;
    memcpy(&destination, &source, sizeof(destination));
    return destination;
}

template <typename T, typename MiniT>
struct LEB {
    T value;

    LEB() {}
    LEB(T val) : value(val) {}

    bool hasMore(T temp, MiniT byte)
    {
        // for signed, we must ensure the last bit has the right sign, as it will zero extend
        return std::is_signed<T>::value
                   ? (temp != 0 && temp != T(-1)) || (value >= 0 && (byte & 64)) || (value < 0 && !(byte & 64))
                   : (temp != 0);
    }

    void write(std::vector<uint8_t>* out)
    {
        T    temp = value;
        bool more;
        do {
            uint8_t byte = temp & 127;
            temp >>= 7;
            more = hasMore(temp, byte);
            if (more) {
                byte = byte | 128;
            }
            out->push_back(byte);
        } while (more);
    }

    void writeAt(std::vector<uint8_t>* out, size_t at, size_t minimum = 0)
    {
        T      temp   = value;
        size_t offset = 0;
        bool   more;

        do {
            uint8_t byte = temp & 127;
            temp >>= 7;
            more = hasMore(temp, byte) || offset + 1 < minimum;
            if (more) {
                byte = byte | 128;
            }
            (*out)[at + offset] = byte;
            offset++;
        } while (more);
    }

    void read(std::function<MiniT()> get)
    {
        value       = 0;
        T     shift = 0;
        MiniT byte;
        while (1) {
            byte         = get();
            bool last    = !(byte & 128);
            T    payload = byte & 127;

            typedef typename std::make_unsigned<T>::type mask_type;
            auto shift_mask          = 0 == shift ? ~mask_type(0) : ((mask_type(1) << (sizeof(T) * 8 - shift)) - 1u);
            T    significant_payload = payload & shift_mask;
            if (significant_payload != payload) {
                if (!(std::is_signed<T>::value && last)) {
                    throw faustexception("LEB dropped bits only valid for signed LEB");
                }
            }
            value |= significant_payload << shift;
            if (last) break;
            shift += 7;
            if (size_t(shift) >= sizeof(T) * 8) {
                throw faustexception("LEB overflow");
            }
        }
        // If signed LEB, then we might need to sign-extend. (compile should
        // optimize this out if not needed).
        if (std::is_signed<T>::value) {
            shift += 7;
            if ((byte & 64) && size_t(shift) < 8 * sizeof(T)) {
                size_t sext_bits = 8 * sizeof(T) - size_t(shift);
                value <<= sext_bits;
                value >>= sext_bits;
                if (value >= 0) {
                    throw faustexception(" LEBsign-extend should produce a negative value");
                }
            }
        }
    }
};

typedef LEB<uint32_t, uint8_t> U32LEB;
typedef LEB<uint64_t, uint8_t> U64LEB;
typedef LEB<int32_t, int8_t>   S32LEB;
typedef LEB<int64_t, int8_t>   S64LEB;

enum class ExternalKind { Function = 0, Table = 1, Memory = 2, Global = 3 };

namespace BinaryConsts {

enum Meta {
    Magic   = 0x6d736100,
    Version = 0x01  // First official version
};

enum Section {
    User     = 0,
    Type     = 1,
    Import   = 2,
    Function = 3,
    Table    = 4,
    Memory   = 5,
    Global   = 6,
    Export   = 7,
    Start    = 8,
    Element  = 9,
    Code     = 10,
    Data     = 11
};

enum EncodedType {
    // value_type
    i32 = -0x1,  // 0x7f
    i64 = -0x2,  // 0x7e
    f32 = -0x3,  // 0x7d
    f64 = -0x4,  // 0x7c
    // elem_type
    AnyFunc = -0x10,  // 0x70
    // func_type form
    Func = -0x20,  // 0x60
    // block_type
    Empty = -0x40  // 0x40
};

namespace UserSections {
extern const char* Name;
}

enum ASTNodes {
    Unreachable = 0x00,
    Nop         = 0x01,
    Block       = 0x02,
    Loop        = 0x03,
    If          = 0x04,
    Else        = 0x05,

    End         = 0x0b,
    Br          = 0x0c,
    BrIf        = 0x0d,
    BrTable     = 0x0e,
    Return      = 0x0f,

    CallFunction = 0x10,
    CallIndirect = 0x11,
    RetCallFunction = 0x12,
    RetCallIndirect = 0x13,

    Drop   = 0x1a,
    Select = 0x1b,
    SelectWithType = 0x1c, // added in reference types proposal

    LocalGet = 0x20,
    LocalSet = 0x21,
    LocalTee = 0x22,
    GlobalGet = 0x23,
    GlobalSet = 0x24,

    I32LoadMem = 0x28,
    I64LoadMem = 0x29,
    F32LoadMem = 0x2a,
    F64LoadMem = 0x2b,

    I32LoadMem8S  = 0x2c,
    I32LoadMem8U  = 0x2d,
    I32LoadMem16S = 0x2e,
    I32LoadMem16U = 0x2f,
    I64LoadMem8S  = 0x30,
    I64LoadMem8U  = 0x31,
    I64LoadMem16S = 0x32,
    I64LoadMem16U = 0x33,
    I64LoadMem32S = 0x34,
    I64LoadMem32U = 0x35,

    I32StoreMem = 0x36,
    I64StoreMem = 0x37,
    F32StoreMem = 0x38,
    F64StoreMem = 0x39,

    I32StoreMem8  = 0x3a,
    I32StoreMem16 = 0x3b,
    I64StoreMem8  = 0x3c,
    I64StoreMem16 = 0x3d,
    I64StoreMem32 = 0x3e,

    MemorySize = 0x3f,
    MemoryGrow = 0x40,

    I32Const = 0x41,
    I64Const = 0x42,
    F32Const = 0x43,
    F64Const = 0x44,

    // Math operation moved in Binop.hh

    I32WrapI64     = 0xa7,
    I32STruncF32   = 0xa8,
    I32UTruncF32   = 0xa9,
    I32STruncF64   = 0xaa,
    I32UTruncF64   = 0xab,
    I64SExtendI32  = 0xac,
    I64UExtendI32  = 0xad,
    I64STruncF32   = 0xae,
    I64UTruncF32   = 0xaf,
    I64STruncF64   = 0xb0,
    I64UTruncF64   = 0xb1,
    F32SConvertI32 = 0xb2,
    F32UConvertI32 = 0xb3,
    F32SConvertI64 = 0xb4,
    F32UConvertI64 = 0xb5,
    F32DemoteI64   = 0xb6,
    F64SConvertI32 = 0xb7,
    F64UConvertI32 = 0xb8,
    F64SConvertI64 = 0xb9,
    F64UConvertI64 = 0xba,
    F64PromoteF32  = 0xbb,

    I32ReinterpretF32 = 0xbc,
    I64ReinterpretF64 = 0xbd,
    F32ReinterpretI32 = 0xbe,
    F64ReinterpretI64 = 0xbf
};

enum MemoryAccess {
    Offset           = 0x10,  // bit 4
    Alignment        = 0x80,  // bit 7
    NaturalAlignment = 0
};

}  // namespace BinaryConsts

#endif
