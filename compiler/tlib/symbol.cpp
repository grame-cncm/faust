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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <iostream>
#include <limits>

#include "symbol.hh"
#include "tlib-error.hh"

using namespace std;

/**
 * Hash table used to store the symbols.
 */

Symbol** Symbol::gSymbolTable     = nullptr;
size_t   Symbol::gHashTableSize   = 0;
size_t   Symbol::gHashTableCount  = 0;
double   Symbol::gHashLoadFactor  = 0.7;

map<string, size_t> Symbol::gPrefixCounters;

namespace {

// A signature owns its base and the next dense local opcode. The registry is
// session-local, just like the symbol table whose Sym pointers are its keys.
struct SignatureState {
    SymbolOpcode base;
    std::uint16_t nextLocalOpcode;
};

map<Sym, SignatureState> gSignatureTable;
std::uint64_t            gNextSignatureBase = 0;

}  // namespace

// Smallest prime >= n (trial division; only called on the rare rehash path)
static size_t nextPrimeAtLeast(size_t n)
{
    if (n <= 2) return 2;
    size_t candidate = (n % 2 == 0) ? n + 1 : n;
    for (;;) {
        bool   isPrime = true;
        size_t d       = 3;
        while (d * d <= candidate) {
            if (candidate % d == 0) {
                isPrime = false;
                break;
            }
            d += 2;
        }
        if (isPrime) return candidate;
        candidate += 2;
    }
}

// Lazily allocates the table on first use : unlike the previous fixed-size C array (whose static
// storage duration guaranteed a valid zero-initialized table before any code ran), a
// dynamically-allocated table needs an explicit first allocation. This makes Symbol::get()/isnew()
// safe to call even if something creates a symbol before Symbol::init() has run (e.g. from another
// translation unit's static initializer, whose relative order versus init() is unspecified).
// Cheap after the first call (one non-null pointer check).
void Symbol::ensureHashTableAllocated()
{
    if (gSymbolTable != nullptr) return;
    gHashTableSize = kInitialHashTableSize;
    gSymbolTable   = new Symbol*[gHashTableSize];
    memset(gSymbolTable, 0, sizeof(Symbol*) * gHashTableSize);
}

// Rehash into a larger table once the load factor (average chain length) would exceed
// gHashLoadFactor (0.7 by default, see setHashLoadFactor) -- see the longer
// comment on CTree::growHashTableIfNeeded (tree.cpp) for why not 1.0.
// Existing Symbol instances keep their address : only their fNext chaining is rewired, so every
// Sym pointer already held elsewhere in the compiler remains valid across the resize.
//
// Only called right before an insert (see Symbol::get), not on every lookup.
void Symbol::growHashTableIfNeeded()
{
    if (double(gHashTableCount) < double(gHashTableSize) * gHashLoadFactor) return;

    size_t   newSize  = nextPrimeAtLeast(gHashTableSize * 2);
    Symbol** newTable = new Symbol*[newSize];
    memset(newTable, 0, sizeof(Symbol*) * newSize);

    for (size_t i = 0; i < gHashTableSize; i++) {
        Sym s = gSymbolTable[i];
        while (s) {
            Sym    next = s->fNext;
            size_t j    = s->fHash % newSize;
            s->fNext    = newTable[j];
            newTable[j] = s;
            s           = next;
        }
    }

    delete[] gSymbolTable;
    gSymbolTable   = newTable;
    gHashTableSize = newSize;
}

/**
 * Search the hash table for the symbol of name \p str or returns a new one.
 * \param str the name of the symbol
 * \return a symbol of name str
 */

Sym Symbol::get(const string& rawstr)
{
    ensureHashTableAllocated();

    // ---replaces control characters with white spaces---
    string str = rawstr;
    for (size_t i = 0; i < str.size(); i++) {
        char c = rawstr[i];
        str[i] = (c >= 0 && c < 32) ? 32 : c;
    }
    size_t hsh      = calcHashKey(str);
    size_t bckt     = hsh % gHashTableSize;
    Sym    item     = gSymbolTable[bckt];
    bool   collided = (item != nullptr);  // bucket already occupied, known for free from the lookup

    while (item && !item->equiv(hsh, str)) {
        item = item->fNext;
    }
    if (item) {
        return item;
    }

    // Only even consider growing when this insert lands on an already-occupied bucket.
    if (collided) {
        growHashTableIfNeeded();
        bckt = hsh % gHashTableSize;
    }
    Sym r              = new Symbol(str, hsh, gSymbolTable[bckt]);
    gSymbolTable[bckt] = r;
    gHashTableCount++;
    return r;
}

/**
 * Static method that searches the symbol table for a string.
 * \param str string to search
 * \return true if the string is NOT in the table (it is a new string)
 */

bool Symbol::isnew(const string& str)
{
    ensureHashTableAllocated();

    size_t hsh  = calcHashKey(str);
    size_t bckt = hsh % gHashTableSize;
    Sym    item = gSymbolTable[bckt];

    while (item && !item->equiv(hsh, str)) {
        item = item->fNext;
    }
    return item == nullptr;
}

/**
 * Creates a new symbol with a name obtained by concatenating the \p str prefix with a number in
 * order to make it unique. \param str the prefix of the name \return a symbol of name \p prefix++n
 */

Sym Symbol::prefix(const string& str)
{
    string name;

    for (int n = 0; n < 10000; n++) {
        name = str + std::to_string(gPrefixCounters[str]++);
        if (isnew(name)) {
            return get(name);
        }
    }
    TLIB_ASSERT(false);
    return get("UNIQUEOVERFLOW");
}

/**
 * Check if the name of the symbol is equal to string \p str
 * This method is used by isnew() and make() when searching the hashtable
 * for an existing symbol.
 *
 * \param hash the hash key of the string (used to speedup the comparison)
 * \param str the string to compare
 * \return \p true if the name of the symbol and \p str are the same
 */

bool Symbol::equiv(size_t hash, const string& str) const
{
    return (fHash == hash) && (fName == str);
}

/**
 * Compute the 32-bits hash key of string \p str.
 * \param str the string
 * \return a 32-bits hash key
 */

std::size_t Symbol::calcHashKey(const std::string& str)
{
    std::size_t hk = 0;
    for (char c : str) {
        // Taken from by boost::hash_combine
        hk = hk ^ (static_cast<std::size_t>(c) + 0x9e3779b9 + (hk << 6) + (hk >> 2));
    }
    return hk;
}

/**
 * Constructs a symbol ready to be placed in the hash table.
 * Gets a string to be kept.
 * \param str the name of the symbol
 * \param hsh the hash key of the symbol
 * \param nxt a pointer to the next symbol in the hash table entry
 */

Symbol::Symbol(const string& str, size_t hsh, Sym nxt)
{
    fName      = str;
    fHash      = hsh;
    fNext      = nxt;
    fData      = nullptr;
    fSignature = nullptr;
    fOpcode    = 0;
}

Symbol::~Symbol()
{
}

ostream& Symbol::print(ostream& fout) const  ///< print a symbol on a stream
{
    return fout << fName;
}

void Symbol::init()
{
    gPrefixCounters.clear();
    gSignatureTable.clear();
    gNextSignatureBase = 0;
    gHashTableCount = 0;
    delete[] gSymbolTable;
    gHashTableSize = kInitialHashTableSize;
    gSymbolTable   = new Symbol*[gHashTableSize];
    memset(gSymbolTable, 0, sizeof(Sym) * gHashTableSize);
}

//--------------------------------------------------------------------------
// Public API: symbol signatures
//--------------------------------------------------------------------------

/**
 * Return the interned signature named \p name.
 *
 * The first call reserves a fresh, aligned range of 256 global opcodes.
 * Repeating the call returns a handle to the same range and allocation state.
 */
Signature signature(const std::string& signatureName)
{
    const std::uint64_t lastBase = std::numeric_limits<SymbolOpcode>::max() -
                                   (kOpcodesPerSignature - 1);

    // Avoid creating even the identity symbol when no new range can be
    // reserved; an existing signature remains retrievable at exhaustion.
    if (Symbol::isnew(signatureName) && gNextSignatureBase > lastBase) {
        tlib::error("signature: global opcode space exhausted");
    }

    Sym identity = Symbol::get(signatureName);
    if (gSignatureTable.find(identity) == gSignatureTable.end()) {
        if (gNextSignatureBase > lastBase) {
            tlib::error("signature: global opcode space exhausted");
        }
        gSignatureTable.emplace(
            identity, SignatureState {static_cast<SymbolOpcode>(gNextSignatureBase), 0});
        gNextSignatureBase += kOpcodesPerSignature;
    }
    return Signature(identity);
}

/**
 * Add the interned symbol named \p name to this signature.
 *
 * First additions receive dense local opcodes from 0 to 255. Repeating an
 * addition returns the same symbol without consuming an opcode. Adding a
 * 257th distinct constructor or a symbol owned by another signature is
 * reported through the TLIB error handler without changing existing tags.
 */
Sym Signature::add(const std::string& symbolName) const
{
    auto stateIt = gSignatureTable.find(fIdentity);
    if (stateIt == gSignatureTable.end()) {
        tlib::error("Signature::add: invalid signature handle");
    }

    SignatureState& state = stateIt->second;

    // Check capacity before interning a new name so a rejected 257th
    // constructor leaves neither the signature nor the symbol table changed.
    if (state.nextLocalOpcode == kOpcodesPerSignature && Symbol::isnew(symbolName)) {
        tlib::error("Signature::add: signature " + string(name(fIdentity)) +
                    " already contains 256 constructors");
    }

    Sym constructor = Symbol::get(symbolName);

    if (constructor->fSignature) {
        if (constructor->fSignature == fIdentity) {
            return constructor;
        }
        tlib::error("Signature::add: symbol " + string(name(constructor)) +
                    " already belongs to signature " + string(name(constructor->fSignature)));
    }

    if (state.nextLocalOpcode == kOpcodesPerSignature) {
        tlib::error("Signature::add: signature " + string(name(fIdentity)) +
                    " already contains 256 constructors");
    }

    // Commit both immutable fields only after every validation succeeds.
    constructor->fSignature = fIdentity;
    constructor->fOpcode    = state.base + state.nextLocalOpcode;
    ++state.nextLocalOpcode;
    return constructor;
}
