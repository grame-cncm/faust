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

#include <map>
#include <string>

#include "garbageable.hh"

//--------------------------------SYMBOL-------------------------------------

class Symbol;
typedef Symbol* Sym;

/**
 * Symbols are unique objects with a name stored in a hash table.
 */
class Symbol : public virtual Garbageable {
   private:
    static const int kHashTableSize =
        511;  ///< Size of the hash table (a prime number is recommended)
    static Symbol* gSymbolTable[kHashTableSize];  ///< Hash table used to store the symbols
    static std::map<std::string, size_t> gPrefixCounters;

    // Fields
    std::string fName;  ///< Name of the symbol
    size_t fHash;  ///< Hash key computed from the name and used to determine the hash table entry
    Sym    fNext;  ///< Next symbol in the hash table entry
    void*  fData;  ///< Field to user disposal to store additional data

    // Constructors & destructors
    Symbol(const std::string&, size_t hsh,
           Sym nxt);  ///< Constructs a new symbol ready to be placed in the hash table
    ~Symbol();        ///< The destructor is never used

    // Others
    bool equiv(size_t hash, const std::string& str)
        const;  ///< Check if the name of the symbol is equal to string \p str
    static size_t calcHashKey(
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

    static void init();
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

inline std::ostream& operator<<(std::ostream& s, const Symbol& n)
{
    return n.print(s);
}

#endif
