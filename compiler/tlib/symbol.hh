/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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
 
/** \file symbol.hh
 * A library to create and manipulate symbols with a unique name. 
 * A library of functions to create and manipulate symbols with a unique name.
 * 
 *  <b>API:</b>
 *
 *   - Sym q = symbol("abcd");     <i>returns the symbol of name "abcd"</i>
 *   - const char* s = name(q);    <i>returns the name of symbol q</i>
 *   - Sym q = unique("TOTO");	   <i>returns a new unique symbol of name "TOTOnnn"</i>  
 *
 *  <b>Properties:</b>
 *
 *     If p and q are two symbols then : 
 *  	   p != q  <=>  name(p) != name(q)
 *
 */ 
 
#ifndef     __SYMBOL__
#define     __SYMBOL__

#include <string>
#include <map>

#include "garbageable.hh"

using namespace std;

//--------------------------------SYMBOL-------------------------------------

/**
 * Symbols are unique objects with a name stored in a hash table.
 */
class Symbol : public virtual Garbageable {
	
 private:
		 
	static const int 	kHashTableSize = 511;					///< Size of the hash table (a prime number is recommended)
    static Symbol*		gSymbolTable[kHashTableSize];			///< Hash table used to store the symbols
    static map<const char*, unsigned int> gPrefixCounters;
	
 // Fields
    string			fName;										///< Name of the symbol
    unsigned int	fHash;										///< Hash key computed from the name and used to determine the hash table entry
    Symbol*			fNext;										///< Next symbol in the hash table entry
	void*			fData;										///< Field to user disposal to store additional data
	
 // Constructors & destructors
    Symbol (const string&, unsigned int hsh, Symbol* nxt);      ///< Constructs a new symbol ready to be placed in the hash table
   ~Symbol ();													///< The Destructor is never used
	
 // Others
	bool			equiv (unsigned int hash, const char* str) const ;	///< Check if the name of the symbol is equal to string \p str
	static unsigned int 	calcHashKey (const char* str);				///< Compute the 32-bits hash key of string \p str

 // Static methods
	static Symbol*		get (const string& str);				///< Get the symbol of name \p str
	static Symbol* 		get (const char* str);					///< Get the symbol of name \p str
	static Symbol* 		prefix (const char* str);				///< Creates a new symbol of name prefixed by \p str
	static bool 		isnew (const char* str);				///< Returns \b true if no symbol of name \p str exists
	
 public:
	ostream& 				print (ostream& fout) const; 								///< print a symbol on a stream

	friend Symbol*			symbol (const char* str);
	friend Symbol*			symbol (const string& str);
	friend Symbol*			unique (const char* str);
	friend const char* 	name (Symbol* sym);
	
	friend void* 			getUserData (Symbol* sym);
	friend void 			setUserData (Symbol* sym, void* d);
    
    static void init ();
		
};

inline Symbol*			symbol (const char* str) 	{ return Symbol::get(str); } 	///< Returns (and creates if new) the symbol of name \p str
inline Symbol*			symbol (const string& str) 	{ return Symbol::get(str); }	///< Returns (and creates if new) the symbol of name \p str
inline Symbol*			unique (const char* str) 	{ return Symbol::prefix(str);}	///< Returns a new unique symbol of name strxxx
inline const char* 	name (Symbol* sym) 			{ return sym->fName.c_str(); }		///< Returns the name of a symbol
	
inline void* 			getUserData (Symbol* sym) 			{ return sym->fData; }		///< Returns user data
inline void 			setUserData (Symbol* sym, void* d) 	{ sym->fData = d; }			///< Set user data

inline ostream& operator << (ostream& s, const Symbol& n) { return n.print(s); }

typedef Symbol* Sym;

#endif    
