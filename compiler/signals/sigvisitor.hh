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

#pragma once

#include "signals.hh"

struct sigvisitor {
    // predefined visit scheme
    void visit(Tree sig);

    // Unrecognized signal (default handler)
    virtual void visitError(Tree sig);

    virtual ~sigvisitor() = default;

    //---------------abstract methods---------------
    // numbers
    virtual void visitInt(Tree sig, int i)     = 0;
    virtual void visitReal(Tree sig, double r) = 0;

    // audio inputs-outputs
    virtual void visitInput(Tree sig, int i)          = 0;
    virtual void visitOutput(Tree sig, int i, Tree s) = 0;

    // fixed size delays
    virtual void visitDelay1(Tree sig, Tree s)             = 0;
    virtual void visitPrefix(Tree sig, Tree s1, Tree s2)   = 0;
    virtual void visitFixDelay(Tree sig, Tree s1, Tree s2) = 0;

    // up and down sampling
    virtual void visitUpsampling(Tree sig, Tree s1, Tree s2)   = 0;
    virtual void visitDownsampling(Tree sig, Tree s1, Tree s2) = 0;

    // numerical operations
    virtual void visitBinOp(Tree sig, int opcode, Tree s1, Tree s2)     = 0;
    virtual void visitIntCast(Tree sig, Tree s)                         = 0;
    virtual void visitFloatCast(Tree sig, Tree s)                       = 0;
    virtual void visitFFun(Tree sig, Tree ff, Tree ls)                  = 0;
    virtual void visitFConst(Tree sig, Tree type, Tree name, Tree file) = 0;
    virtual void visitFVar(Tree sig, Tree type, Tree name, Tree file)   = 0;

    // user interface
    virtual void visitButton(Tree sig, Tree label)                                            = 0;
    virtual void visitCheckbox(Tree sig, Tree label)                                          = 0;
    virtual void visitVSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step)  = 0;
    virtual void visitHSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step)  = 0;
    virtual void visitNumEntry(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) = 0;
    virtual void visitVBargraph(Tree sig, Tree label, Tree min, Tree max, Tree s1)            = 0;
    virtual void visitHBargraph(Tree sig, Tree label, Tree min, Tree max, Tree s1)            = 0;
    virtual void visitAttach(Tree sig, Tree s1, Tree s2)                                      = 0;
    virtual void visitEnable(Tree sig, Tree s1, Tree s2)                                      = 0;
    virtual void visitControl(Tree sig, Tree s1, Tree s2)                                     = 0;

    // recursive
    virtual void visitRec(Tree sig, Tree var, Tree body) = 0;
    virtual void visitRef(Tree sig, Tree var)            = 0;
    virtual void visitProj(Tree sig, int i, Tree s1)     = 0;

    // Tables
    virtual void visitTable(Tree sig, Tree id, Tree s1, Tree s2)          = 0;
    virtual void visitWRTbl(Tree sig, Tree id, Tree s1, Tree s2, Tree s3) = 0;
    virtual void visitRDTbl(Tree sig, Tree s1, Tree s2)                   = 0;
    virtual void visitGen(Tree sig, Tree s1)                              = 0;

    virtual void visitDocConstantTbl(Tree sig, Tree s1, Tree s2)                = 0;
    virtual void visitDocWriteTbl(Tree sig, Tree s1, Tree s2, Tree s3, Tree s4) = 0;
    virtual void visitDocAccessTbl(Tree sig, Tree s1, Tree s2)                  = 0;

    // Selectors
    virtual void visitSelect2(Tree sig, Tree sel, Tree s1, Tree s2)          = 0;
    virtual void visitSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3) = 0;

    // Tuples
    virtual void visitTuple(Tree sig, int mod, Tree ls)        = 0;
    virtual void visitTupleAccess(Tree sig, Tree ts, Tree idx) = 0;

    // List of signals
    virtual void visitList(Tree lsig) = 0;
};

struct fullvisitor : sigvisitor {
    // numbers
    void visitInt(Tree sig, int i) override {}
    void visitReal(Tree sig, double r) override {}

    // audio inputs-outputs
    void visitInput(Tree sig, int i) override {}
    void visitOutput(Tree sig, int i, Tree s) override { visit(s); }

    // fixed size delays
    void visitDelay1(Tree sig, Tree s) override { visit(s); }
    void visitPrefix(Tree sig, Tree s1, Tree s2) override
    {
        visit(s1);
        visit(s2);
    }
    void visitFixDelay(Tree sig, Tree s1, Tree s2) override
    {
        visit(s1);
        visit(s2);
    }

    // numerical operations
    void visitIntCast(Tree sig, Tree s) override { visit(s); }
    void visitFloatCast(Tree sig, Tree s) override { visit(s); }
    void visitBinOp(Tree sig, int op, Tree s1, Tree s2) override
    {
        visit(s1);
        visit(s2);
    }
    void visitFFun(Tree sig, Tree ff, Tree ls) override { visit(ls); }
    void visitFConst(Tree sig, Tree type, Tree name, Tree file) override {}
    void visitFVar(Tree sig, Tree type, Tree name, Tree file) override {}

    // user interface
    void visitButton(Tree sig, Tree label) override {}
    void visitCheckbox(Tree sig, Tree label) override {}
    void visitVSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) override {}
    void visitHSlider(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) override {}
    void visitNumEntry(Tree sig, Tree label, Tree cur, Tree min, Tree max, Tree step) override {}
    void visitVBargraph(Tree sig, Tree label, Tree min, Tree max, Tree s) override { visit(s); }
    void visitHBargraph(Tree sig, Tree label, Tree min, Tree max, Tree s) override { visit(s); }
    void visitAttach(Tree sig, Tree s1, Tree s2) override
    {
        visit(s1);
        visit(s2);
    }

    // recursive
    void visitRec(Tree sig, Tree var, Tree body) override { visit(body); }
    void visitRef(Tree sig, Tree var) override {}
    void visitProj(Tree sig, int i, Tree s) override { visit(s); }

    // Tables
    void visitTable(Tree sig, Tree id, Tree s1, Tree s2) override
    {
        visit(s1);
        visit(s2);
    }
    void visitWRTbl(Tree sig, Tree id, Tree s1, Tree s2, Tree s3) override
    {
        visit(s1);
        visit(s2);
        visit(s3);
    }
    void visitRDTbl(Tree sig, Tree s1, Tree s2) override
    {
        visit(s1);
        visit(s2);
    }
    void visitGen(Tree sig, Tree s1) override { visit(s1); }

    // Selectors
    void visitSelect2(Tree sig, Tree sel, Tree s1, Tree s2) override
    {
        visit(sel);
        visit(s1);
        visit(s2);
    }
    void visitSelect3(Tree sig, Tree sel, Tree s1, Tree s2, Tree s3) override
    {
        visit(sel);
        visit(s1);
        visit(s2);
        visit(s3);
    }

    // Tuples
    void visitTuple(Tree sig, int mod, Tree ls) override { visit(ls); }
    void visitTupleAccess(Tree sig, Tree ts, Tree idx) override
    {
        visit(ts);
        visit(idx);
    }

    // List of signals
    void visitList(Tree lsig) override
    {
        while (!isNil(lsig)) {
            visit(hd(lsig));
            lsig = tl(lsig);
        }
    }
};
