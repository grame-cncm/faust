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

#ifndef _PPSIG_H
#define _PPSIG_H

/**********************************************************************
        - ppsig.h : pretty print signals expressions (projet FAUST) -

        Historique :
        -----------
        05-07-2006  first implementation  (yo)

***********************************************************************/

#include <iostream>
#include <sstream>
#include <climits>

#include "garbageable.hh"
#include "signals.hh"

// signal pretty printer.
// usage : out << ppsig(aSignalExp);

class ppsig : public virtual Garbageable {
   public:
    ppsig(Tree s, int max_size = INT_MAX);
    ppsig(Tree s, Tree env, int priority = 0, int max_size = INT_MAX)
        : fSig(s), fEnv(env), fPriority(priority), fHideRecursion(false), fMaxSize(max_size)
    {}
    virtual std::ostream& print(std::ostream& fout) const;

   protected:
    virtual std::ostream& printinfix(std::ostream& fout, const std::string& opname, int priority, Tree x, Tree y) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y, Tree z) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y, Tree z, Tree zz) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y, Tree z, Tree z2, Tree z3) const;
    virtual std::ostream& printout(std::ostream& fout, int i, Tree x) const;
    virtual std::ostream& printlist(std::ostream& fout, Tree largs) const;
    virtual std::ostream& printff(std::ostream& fout, Tree ff, Tree largs) const;
    virtual std::ostream& printrec(std::ostream& fout, Tree var, Tree lexp, bool hide) const;
    virtual std::ostream& printrec(std::ostream& fout, Tree lexp, bool hide) const;
    virtual std::ostream& printextended(std::ostream& fout, Tree sig1) const;
    virtual std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label) const;
    virtual std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label, Tree lo, Tree hi, Tree step) const;
    virtual std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label, Tree cur, Tree lo, Tree hi, Tree step) const;
    virtual std::ostream& printlabel(std::ostream& fout, Tree pathname) const;
    virtual std::ostream& printDelay(std::ostream& fout, Tree exp, Tree delay) const;
    
    Tree fSig;
    Tree fEnv;            ///< recursive environment stack
    int  fPriority;       ///< priority context
    bool fHideRecursion;
    int fMaxSize;
    
};

inline std::ostream& operator<<(std::ostream& file, const ppsig& pp)
{
    return pp.print(file);
}

// A version that cache already printed subsignals in variables
class ppsigShared final : public ppsig {
    
    private:
     
        std::ostream& printinfix(std::ostream& fout, const std::string& opname, int priority, Tree x, Tree y) const;
        std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x) const;
        std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y) const;
        std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y, Tree z) const;
        std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y, Tree z, Tree zz) const;
        std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y, Tree z, Tree z2, Tree z3) const;
        std::ostream& printout(std::ostream& fout, int i, Tree x) const;
        std::ostream& printlist(std::ostream& fout, Tree largs) const;
        std::ostream& printff(std::ostream& fout, Tree ff, Tree largs) const;
        std::ostream& printrec(std::ostream& fout, Tree var, Tree lexp, bool hide) const;
        std::ostream& printrec(std::ostream& fout, Tree lexp, bool hide) const;
        std::ostream& printextended(std::ostream& fout, Tree sig1) const;
        std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label) const;
        std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label, Tree lo, Tree hi, Tree step) const;
        std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label, Tree cur, Tree lo, Tree hi, Tree step) const;
        std::ostream& printDelay(std::ostream& fout, Tree exp, Tree delay) const;
    
    public:
        ppsigShared(Tree s):ppsig(s) {}
        ppsigShared(Tree L, std::ostream& fout, bool sort = false):ppsig(L)
        {
            // Create a map of <ID, expression>
            std::stringstream s; s << ppsigShared(L);
            // Print the <ID, expression> list
            printIDs(fout, sort);
            fout << "SIG = " << s.str() << ";" << std::endl;
        }
        ppsigShared(Tree s, Tree env, int priority = 0) : ppsig(s, env, priority, INT_MAX) {}
        std::ostream& print(std::ostream& fout) const;
    
        static void printIDs(std::ostream& fout, bool sort);
};

#endif
