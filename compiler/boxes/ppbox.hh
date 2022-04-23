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

#ifndef _PPBOX_H
#define _PPBOX_H

/**********************************************************************
        - ppbox.h : pretty print box expressions (projet FAUST) -

        Historique :
        -----------
        12-07-2002  first implementation  (yo)
***********************************************************************/

#include <iostream>
#include <sstream>
#include <utility>
#include <map>

#include "boxes.hh"
#include "garbageable.hh"

using namespace std;

const char *prim0name(CTree *(*ptr)());
const char *prim1name(CTree *(*ptr)(CTree *));
const char *prim2name(CTree *(*ptr)(CTree *, CTree *));
const char *prim3name(CTree *(*ptr)(CTree *, CTree *, CTree *));
const char *prim4name(CTree *(*ptr)(CTree *, CTree *, CTree *, CTree *));
const char *prim5name(CTree *(*ptr)(CTree *, CTree *, CTree *, CTree *, CTree *));

// box pretty printer.
// usage : out << boxpp(aBoxExp);

class boxpp : public virtual Garbageable {
    protected:
        Tree fBox;
        int  fPriority;
        
    public:
        boxpp(Tree b, int p = 0) : fBox(b), fPriority(p) {}
        virtual ~boxpp() {}
        virtual ostream &print(ostream &fout) const;
};

// Use a map <ID, expression> to reuse already written expressions.
// printIDs allow to print the <ID, expression> list before 'process = exp;' final line.

class boxppShared : public boxpp {
    protected:
        
    public:
        boxppShared(Tree b, int p = 0) : boxpp(b, p) {}
        virtual ~boxppShared() {}
        virtual ostream &print(ostream &fout) const;
    
        static void printIDs(ostream& fout);
};

inline ostream &operator<<(ostream &file, const boxpp &bpp)
{
    return bpp.print(file);
}

// environment pretty printer.
// usage : out << envpp(aEnvExp);

class envpp : public virtual Garbageable {
    Tree fEnv;

    public:
        envpp(Tree e) : fEnv(e) {}
        ostream &print(ostream &fout) const;
};

inline ostream &operator<<(ostream &file, const envpp &epp)
{
    return epp.print(file);
}

#endif
