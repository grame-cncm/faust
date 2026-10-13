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

#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "garbageable.hh"
#include "signals.hh"

class ppsigNames;

// signal pretty printer.
// usage : out << ppsig(aSignalExp);

class ppsig : public virtual Garbageable {
   public:
    ppsig(Tree s, int max_size = INT_MAX);
    ppsig(Tree s, Tree env, int priority = 0, int max_size = INT_MAX,
          const ppsigNames* names = nullptr, bool expand = false)
        : fSig(s),
          fEnv(env),
          fPriority(priority),
          fHideRecursion(false),
          fMaxSize(max_size),
          fNames(names),
          fExpand(expand)
    {
    }
    virtual std::ostream& print(std::ostream& fout) const;

   protected:
    virtual std::ostream& printinfix(std::ostream& fout, const std::string& opname, int priority,
                                     Tree x, Tree y) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x,
                                   Tree y) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y,
                                   Tree z) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y,
                                   Tree z, Tree zz) const;
    virtual std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y,
                                   Tree z, Tree z2, Tree z3) const;
    virtual std::ostream& printout(std::ostream& fout, int i, Tree x) const;
    virtual std::ostream& printlist(std::ostream& fout, Tree largs) const;
    virtual std::ostream& printff(std::ostream& fout, Tree ff, Tree largs) const;
    virtual std::ostream& printrec(std::ostream& fout, Tree var, Tree lexp, bool hide) const;
    virtual std::ostream& printrec(std::ostream& fout, Tree lexp, bool hide) const;
    virtual std::ostream& printextended(std::ostream& fout, Tree sig1) const;
    virtual std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label) const;
    virtual std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label,
                                  Tree lo, Tree hi, Tree step) const;
    virtual std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label,
                                  Tree cur, Tree lo, Tree hi, Tree step) const;
    virtual std::ostream& printlabel(std::ostream& fout, Tree pathname) const;
    virtual std::ostream& printDelay(std::ostream& fout, Tree exp, Tree delay) const;

    Tree fSig;
    Tree fEnv;       ///< recursive environment stack
    int  fPriority;  ///< priority context
    bool fHideRecursion;
    int  fMaxSize;
    const ppsigNames* fNames;   ///< names printed in place of the nodes they name, if any
    bool              fExpand;  ///< print fSig itself even when it has a name
};

inline std::ostream& operator<<(std::ostream& file, const ppsig& pp)
{
    return pp.print(file);
}

// A version that cache already printed subsignals in variables
class ppsigShared final : public ppsig {
   private:
    std::ostream& printinfix(std::ostream& fout, const std::string& opname, int priority, Tree x,
                             Tree y) const;
    std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x) const;
    std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y) const;
    std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y,
                           Tree z) const;
    std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y, Tree z,
                           Tree zz) const;
    std::ostream& printfun(std::ostream& fout, const std::string& funame, Tree x, Tree y, Tree z,
                           Tree z2, Tree z3) const;
    std::ostream& printout(std::ostream& fout, int i, Tree x) const;
    std::ostream& printlist(std::ostream& fout, Tree largs) const;
    std::ostream& printff(std::ostream& fout, Tree ff, Tree largs) const;
    std::ostream& printrec(std::ostream& fout, Tree var, Tree lexp, bool hide) const;
    std::ostream& printrec(std::ostream& fout, Tree lexp, bool hide) const;
    std::ostream& printextended(std::ostream& fout, Tree sig1) const;
    std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label) const;
    std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label, Tree lo,
                          Tree hi, Tree step) const;
    std::ostream& printui(std::ostream& fout, const std::string& funame, Tree label, Tree cur,
                          Tree lo, Tree hi, Tree step) const;
    std::ostream& printDelay(std::ostream& fout, Tree exp, Tree delay) const;

   public:
    ppsigShared(Tree s) : ppsig(s) {}
    ppsigShared(Tree L, std::ostream& fout, bool sort = false) : ppsig(L)
    {
        // Create a map of <ID, expression>
        std::stringstream s;
        s << ppsigShared(L);
        // Print the <ID, expression> list
        printIDs(fout, sort);
        fout << "SIG = " << s.str() << ";" << std::endl;
    }
    // every compound node is printed as its ID, so the text of a node never depends on the
    // priority of the context where it is first met
    ppsigShared(Tree s, Tree env, int = 0) : ppsig(s, env, 0, INT_MAX) {}
    std::ostream& print(std::ostream& fout) const;

    static void printIDs(std::ostream& fout, bool sort);
};

// The names of an equation printing : one name per member of a recursive group (R0, or
// R4.0, R4.1 for the members of a mutually recursive group), and one per shared
// compound subexpression (E0, E1...).
class ppsigNames {
   public:
    std::map<Tree, std::pair<int, int>> fGroups;  ///< recursive group -> (number, members)
    std::map<Tree, std::string>         fShared;  ///< shared subexpression -> name

    // the name of t, if it has one
    bool lookup(Tree t, std::string& name) const;

    // the name of a recursive group, if it has one
    bool groupName(Tree group, std::string& name) const;
};

// A signal printed as equations : the recursions and the shared subexpressions are named
// and defined once, before their uses (except the uses through a delay), and the outputs
// are printed last. The members of a recursive group are defined on consecutive lines. Names
// are numbered in the order of a depth-first traversal from the outputs, left to right, so
// the text depends only on the signal. When all is set, every compound subexpression is
// named, not only the shared ones. An equation whose node carries a type is followed by
// it, as a comment : its nature, variability, interval, lsb, and validity. When the
// signal is typed, a node also has an equation of its own where its typing goes wrong :
// a delay whose amount has no valid bounds, which the compiler refuses, and a node whose
// interval becomes invalid or unbounded while its operands are not.
class ppsigEquations {
   public:
    // computes the names of L, then prints its equations
    ppsigEquations(Tree L, std::ostream& fout, bool all = false);

    // computes the names of L only
    explicit ppsigEquations(Tree L, bool all = false);

    const ppsigNames& names() const { return fNames; }
    void              print(std::ostream& fout) const;

   private:
    ppsigNames               fNames;
    std::map<Tree, int>      fCount;    ///< number of distinct parents of each node
    std::set<Tree>           fVisited;  ///< nodes already visited by define
    std::set<Tree>           fOnStack;  ///< nodes whose subsignals define is visiting
    // an equation : a shared subexpression (group nil), or member i of a recursive group
    struct Equation {
        Tree fNode;
        Tree fGroup;
        int  fMember;
    };
    std::vector<Equation>    fLines;    ///< the equations, in the order of definition
    std::map<std::pair<Tree, int>, Tree> fProjs;  ///< (group, member) -> its projection
    mutable std::map<Tree, std::string>  fProblems;  ///< node -> what its typing shows wrong
    mutable std::map<std::pair<Tree, Tree>, bool> fReaches;  ///< (node, group) -> reads it
    Tree                     fRoot;
    int                      fNextGroup  = 0;
    int                      fNextShared = 0;
    bool                     fAll;

    void        count(Tree t);
    bool        isNamed(Tree t) const;
    std::string nameOf(Tree t);
    void        define(Tree t);
    void        defineGroup(Tree group);
    void        instantDeps(Tree t, const std::map<Tree, int>& index,
                            const std::map<Tree, int>& firstMember, std::set<Tree>& seen,
                            std::set<int>& deps) const;
    void        order();
    std::string problemOf(Tree t) const;
    std::string groupProblem(Tree group, Tree member) const;
    bool        reaches(Tree t, Tree group) const;
    std::string expand(Tree t) const;
};

#endif
