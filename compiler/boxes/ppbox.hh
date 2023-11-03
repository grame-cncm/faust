/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
    Copyright (C) 2023-2023 INRIA
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

#ifndef _PPBOX_H
#define _PPBOX_H

/**********************************************************************
        - ppbox.h : pretty print box expressions (projet FAUST) -

        Historique :
        -----------
        12-07-2002  first implementation  (yo)
***********************************************************************/

#include <iostream>
#include <map>
#include <sstream>
#include <utility>

#include "boxes.hh"
#include "garbageable.hh"

LIBFAUST_API const char* prim0name(CTree* (*ptr)());
LIBFAUST_API const char* prim1name(CTree* (*ptr)(CTree*));
LIBFAUST_API const char* prim2name(CTree* (*ptr)(CTree*, CTree*));
LIBFAUST_API const char* prim3name(CTree* (*ptr)(CTree*, CTree*, CTree*));
LIBFAUST_API const char* prim4name(CTree* (*ptr)(CTree*, CTree*, CTree*, CTree*));
LIBFAUST_API const char* prim5name(CTree* (*ptr)(CTree*, CTree*, CTree*, CTree*, CTree*));

// Box pretty printer.
// usage : out << boxpp(aBoxExp);

class boxpp : public virtual Garbageable {
   protected:
    Tree fBox;
    int  fPriority;

   public:
    boxpp(Tree b, int p = 0) : fBox(b), fPriority(p) {}
    virtual ~boxpp() {}
    virtual std::ostream& print(std::ostream& fout) const;
};

inline std::ostream& operator<<(std::ostream& file, const boxpp& bpp)
{
    return bpp.print(file);
}

// Use a map <ID, expression> to reuse already written expressions.
// printIDs allow to print the <ID, expression> list before 'process = exp;' final line.

class boxppShared : public boxpp {
   public:
    boxppShared(Tree b, int p = 0) : boxpp(b, p) {}
    boxppShared(Tree L, std::ostream& fout) : boxpp(L)
    {
        // Create a map of <ID, expression>
        std::stringstream s;
        s << boxppShared(L);
        // Print the <ID, expression> list
        printIDs(fout);
        fout << "process = " << s.str() << ";" << std::endl;
    }

    virtual ~boxppShared() {}
    virtual std::ostream& print(std::ostream& fout) const;

    static void printIDs(std::ostream& fout);
};

// environment pretty printer.
// usage : out << envpp(aEnvExp);

class envpp : public virtual Garbageable {
    Tree fEnv;

   public:
    envpp(Tree e) : fEnv(e) {}
    std::ostream& print(std::ostream& fout) const;
};

inline std::ostream& operator<<(std::ostream& file, const envpp& epp)
{
    return epp.print(file);
}

// Limit the box description string to max_size characters
std::string mBox(Tree b, int max_size);

#endif
