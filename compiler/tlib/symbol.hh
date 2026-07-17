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

/** \file symbol.hh
 * A library of functions to create and manipulate symbols with a unique name.
 *
 *  <b>API:</b>
 *
 *   - Sym q = symbol("abcd");     <i>returns the symbol of name "abcd"</i>
 *   - const char* s = name(q);    <i>returns the name of symbol q</i>
 *   - Sym q = unique("TOTO");	 <i>returns a new unique symbol of name "TOTOnnn"</i>
 *
 *  <b>Properties:</b>
 *
 *     If p and q are two symbols then :
 *  	   p != q  <=>  name(p) != name(q)
 *
 */

#ifndef __SYMBOL__
#define __SYMBOL__

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>

#include "export.hh"
#include "garbageable.hh"
#include "tlib-error.hh"

//--------------------------------SYMBOL-------------------------------------

class Symbol;
typedef Symbol* Sym;
class Signature;

using SymbolOpcode = std::uint32_t;

/** Number of consecutive global opcodes reserved by every signature. */
inline constexpr SymbolOpcode kOpcodesPerSignature = 256;

/**
 * Optional signature membership attached to an interned symbol.
 *
 * The signature identifies a constructor language and the global opcode
 * identifies one constructor in its disjoint 256-opcode range. A null
 * signature represents an ordinary, unregistered symbol.
 */
struct SymbolTag {
    Sym          signature = nullptr;
    SymbolOpcode opcode    = 0;

    /**
     * Return the dense opcode within this tag's signature.
     *
     * Valid tags need no registry lookup: aligned 256-opcode ranges make the
     * low byte of the global opcode its local position. The caller must first
     * establish that signature is non-null, normally through getSymbolTag().
     */
    constexpr std::uint8_t localOpcode() const noexcept
    {
        return static_cast<std::uint8_t>(opcode % kOpcodesPerSignature);
    }
};

/**
 * Symbols are unique objects with a name stored in a hash table.
 */
class Symbol : public Garbageable {
   private:
    static const std::size_t kInitialHashTableSize = 511;  ///< initial size of the hash table (prime)
    static std::size_t        gHashTableSize;   ///< current size of the hash table (grows as needed)
    static std::size_t        gHashTableCount;  ///< number of symbols currently stored in the table
    static Symbol**       gSymbolTable;     ///< hash table used to store the symbols (grows by rehashing)
    static std::map<std::string, std::size_t> gPrefixCounters;

    static double gHashLoadFactor;  ///< load factor triggering table growth (see setHashLoadFactor)

    ///< cheap check, called on every get()/isnew() : lazily allocates the table on first use
    static void ensureHashTableAllocated();
    ///< called only right before inserting a new symbol ; rehash into a larger table once the
    ///< load factor is too high. Not called on a lookup that finds an existing symbol.
    static void growHashTableIfNeeded();

    // Fields
    std::string fName;  ///< Name of the symbol
    std::size_t fHash;  ///< Hash key computed from the name and used to determine the hash table entry
    Sym         fNext;  ///< Next symbol in the hash table entry
    void*       fData;  ///< Field to user disposal to store additional data
    Sym          fSignature;  ///< Owning signature, null while the symbol is ordinary
    SymbolOpcode fOpcode;     ///< Global constructor identity; meaningful only when signed

    // Constructors & destructors
    Symbol(const std::string&, std::size_t hsh,
           Sym nxt);  ///< Constructs a new symbol ready to be placed in the hash table
    ~Symbol();        ///< The destructor is never used

    // Others
    bool equiv(std::size_t hash, const std::string& str)
        const;  ///< Check if the name of the symbol is equal to string \p str
    static std::size_t calcHashKey(
        const std::string& str);  ///< Compute the 32-bits hash key of string \p str

    // Static methods
    static Sym get(const std::string& str);     ///< Get the symbol of name \p str
    static Sym prefix(const std::string& str);  ///< Creates a new symbol of name prefixed by \p str
    static bool isnew(
        const std::string& str);  ///< Returns \b true if no symbol of name \p str exists

   public:
    std::ostream& print(std::ostream& fout) const;  ///< print a symbol on a stream

    friend Sym         symbol(const char* str);
    friend Sym         symbol(const std::string& str);
    friend Sym         unique(const char* str);
    friend const char* name(Sym sym);

    friend void* getUserData(Sym sym);
    friend void  setUserData(Sym sym, void* d);
    friend bool  getSymbolTag(Sym sym, SymbolTag& tag);
    friend Signature signature(const std::string& name);
    friend class Signature;

    static void init();

    ///< Set the load factor that triggers hash table growth (default 0.7).
    ///< A pure performance knob : it never changes the symbols created.
    static void setHashLoadFactor(double f) { gHashLoadFactor = f; }
};

/**
 * Copyable handle to an interned constructor signature.
 *
 * Each signature owns one disjoint range of 256 global opcodes. Handles and
 * their identity Sym belong to the current TLIB session and become invalid at
 * cleanup(), like every other symbol pointer.
 */
class Signature {
   private:
    Sym fIdentity;

    explicit Signature(Sym identity) : fIdentity(identity) {}
    friend Signature signature(const std::string& name);

   public:
    /**
     * Add the interned symbol named \p name to this signature.
     *
     * First additions receive dense local opcodes from 0 to 255. Repeating an
     * addition returns the same symbol without consuming an opcode. Adding a
     * 257th distinct constructor or a symbol owned by another signature is
     * reported through the TLIB error handler without changing existing tags.
     */
    TLIB_API Sym add(const std::string& name) const;

    /** Return the interned symbol that identifies this signature. */
    Sym identity() const { return fIdentity; }
};

inline Sym symbol(const char* str)
{
    return Symbol::get(str);
}  ///< Returns (and creates if new) the symbol of name \p str
inline Sym symbol(const std::string& str)
{
    return Symbol::get(str);
}  ///< Returns (and creates if new) the symbol of name \p str
inline Sym unique(const char* str)
{
    return Symbol::prefix(str);
}  ///< Returns a new unique symbol of name strxxx
inline const char* name(Sym sym)
{
    return sym->fName.c_str();
}  ///< Returns the name of a symbol

inline void* getUserData(Sym sym)
{
    return sym->fData;
}  ///< Returns user data
inline void setUserData(Sym sym, void* d)
{
    sym->fData = d;
}  ///< Set user data

//--------------------------------------------------------------------------
// Public API: symbol signatures
//--------------------------------------------------------------------------

/**
 * Return the interned signature named \p name.
 *
 * The first call reserves a fresh, aligned range of 256 global opcodes.
 * Repeating the call returns a handle to the same range and allocation state.
 */
TLIB_API Signature signature(const std::string& name);

/**
 * Read the immutable signature tag of \p sym.
 *
 * Return true and copy the complete tag to \p tag when one is present.
 * Return false without modifying \p tag when the symbol is ordinary. A null
 * symbol is invalid and is reported through the TLIB error handler. This hot
 * fold accessor is inline so successful lookups compile to two field reads.
 */
inline bool getSymbolTag(Sym sym, SymbolTag& tag)
{
    if (!sym) {
        tlib::error("getSymbolTag: null symbol");
    }
    if (!sym->fSignature) {
        return false;
    }
    tag = {sym->fSignature, sym->fOpcode};
    return true;
}

inline std::ostream& operator<<(std::ostream& s, const Symbol& n)
{
    return n.print(s);
}

#endif
