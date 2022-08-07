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
#include "garbageable.hh"
#include "signals.hh"

using namespace std;

// signal pretty printer.
// usage : out << ppsig(aSignalExp);

class ppsig : public virtual Garbageable {
   public:
    ppsig(Tree s);
    ppsig(Tree s, Tree env, int priority = 0) : fSig(s), fEnv(env), fPriority(priority), fHideRecursion(false) {}
    virtual ostream& print(ostream& fout) const;

   protected:
    virtual ostream& printinfix(ostream& fout, const string& opname, int priority, Tree x, Tree y) const;
    virtual ostream& printfun(ostream& fout, const string& funame, Tree x) const;
    virtual ostream& printfun(ostream& fout, const string& funame, Tree x, Tree y) const;
    virtual ostream& printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z) const;
    virtual ostream& printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree zz) const;
    virtual ostream& printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2, Tree z3) const;
    virtual ostream& printout(ostream& fout, int i, Tree x) const;
    virtual ostream& printlist(ostream& fout, Tree largs) const;
    virtual ostream& printff(ostream& fout, Tree ff, Tree largs) const;
    virtual ostream& printrec(ostream& fout, Tree var, Tree lexp, bool hide) const;
    virtual ostream& printrec(ostream& fout, Tree lexp, bool hide) const;
    virtual ostream& printextended(ostream& fout, Tree sig1) const;
    virtual ostream& printui(ostream& fout, const string& funame, Tree label) const;
    virtual ostream& printui(ostream& fout, const string& funame, Tree label, Tree lo, Tree hi, Tree step) const;
    virtual ostream& printui(ostream& fout, const string& funame, Tree label, Tree cur, Tree lo, Tree hi, Tree step) const;
    virtual ostream& printlabel(ostream& fout, Tree pathname) const;
    virtual ostream& printDelay(ostream& fout, Tree exp, Tree delay) const;
    
    Tree fSig;
    Tree fEnv;            ///< recursive environment stack
    int  fPriority;       ///< priority context
    bool fHideRecursion;  ///<
    
};

inline ostream& operator<<(ostream& file, const ppsig& pp)
{
    return pp.print(file);
}

// A version that cache already printed subsignals in variables
class ppsigShared final : public ppsig {
    
    private:
     
        ostream& printinfix(ostream& fout, const string& opname, int priority, Tree x, Tree y) const;
        ostream& printfun(ostream& fout, const string& funame, Tree x) const;
        ostream& printfun(ostream& fout, const string& funame, Tree x, Tree y) const;
        ostream& printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z) const;
        ostream& printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree zz) const;
        ostream& printfun(ostream& fout, const string& funame, Tree x, Tree y, Tree z, Tree z2, Tree z3) const;
        ostream& printout(ostream& fout, int i, Tree x) const;
        ostream& printlist(ostream& fout, Tree largs) const;
        ostream& printff(ostream& fout, Tree ff, Tree largs) const;
        ostream& printrec(ostream& fout, Tree var, Tree lexp, bool hide) const;
        ostream& printrec(ostream& fout, Tree lexp, bool hide) const;
        ostream& printextended(ostream& fout, Tree sig1) const;
        ostream& printui(ostream& fout, const string& funame, Tree label) const;
        ostream& printui(ostream& fout, const string& funame, Tree label, Tree lo, Tree hi, Tree step) const;
        ostream& printui(ostream& fout, const string& funame, Tree label, Tree cur, Tree lo, Tree hi, Tree step) const;
        ostream& printDelay(ostream& fout, Tree exp, Tree delay) const;
    
    public:
        ppsigShared(Tree s):ppsig(s) {}
        ppsigShared(Tree L, ostream& fout):ppsig(L)
        {
            // Create a map of <ID, expression>
            stringstream s; s << ppsigShared(L);
            // Print the <ID, expression> list
            printIDs(fout);
            fout << "SIG = " << s.str() << ";" << endl;
        }
        ppsigShared(Tree s, Tree env, int priority = 0) : ppsig(s, env, priority) {}
        ostream& print(ostream& fout) const;
    
        static void printIDs(ostream& fout);
};

#endif
