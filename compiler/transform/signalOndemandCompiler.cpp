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

#include "signalOndemandCompiler.hh"

#include <cstdlib>
#include <map>
#include "Text.hh"
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signalDependencies.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"
#include "treeTransform.hh"

//-------------------------SignalOndemandCompiler-------------------------------
// Implementation of Faust with Ondemand compilation. Signals are now in a time
// context (a list of clocks). What is visited is not just a signal S, but a
// list : (S . clocklist)
//----------------------------------------------------------------------

void SignalOndemandCompiler::traceEnter(Tree t)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << ppsig(hd(t)) << " in context " << tl(t) << endl;
}

void SignalOndemandCompiler::traceExit(Tree t, Tree r)
{
    tab(fIndent, cerr);
    cerr << fMessage << ": " << ppsig(hd(t)) << " in context " << tl(t) << "  ===>  " << ppsig(r) << endl;
}

static Tree scalID(int nature, Tree sigwclklist)
{
    Tree ident = (nature == kInt) ? uniqueID("iScal", sigwclklist) : uniqueID("fScal", sigwclklist);
    return ident;
}

static Tree timeID(Tree clklist)
{
    Tree ident = uniqueID("iTime", clklist);
    return ident;
}

static Tree vecID(int nature, Tree sigwclklist)
{
    Tree ident = (nature == kInt) ? uniqueID("iVec", sigwclklist) : uniqueID("fVec", sigwclklist);
    return ident;
}

static Tree outID(Tree sigwclklist)
{
    Tree ident = uniqueID("fOut", sigwclklist);
    return ident;
}

void SignalOndemandCompiler::mark(Tree t)
{
    fVisitedRecursions.insert(t);
}

bool SignalOndemandCompiler::isMarked(Tree t)
{
    return fVisitedRecursions.cend() != fVisitedRecursions.find(t);
}

std::set<Tree> ondemandCompileToInstr(Tree lsig)
{
    SignalOndemandCompiler C;
    C.trace(true);
    // compile each output signal with an empty clock list
    while (!isNil(lsig)) {
        Tree sig         = hd(lsig);
        lsig             = tl(lsig);
        Tree sigwclklist = cons(sig, gGlobal->nil);
        /*Tree expr        =*/C.self(sigwclklist);
        // std::cerr << " expr : " << ppsig(expr) << std::endl;
        //  Tree ident       = outID(sigwclklist);
        //  Tree instr       = sigInstruction2MemWrite(gGlobal->nil, ident, kReal, expr);
        //  C.insert(instr);
    }
    return C.instructions();
}

Tree SignalOndemandCompiler::transformation(Tree sigwclklist)
{
    Tree sig     = hd(sigwclklist);
    Tree clklist = tl(sigwclklist);
    Type t       = getSimpleType(sig);
    int  nature  = t->nature();

    int    dmin, dmax, i, tblsize;
    double r;
    Tree   c, sel, x, y, z, u, v, var, le, label, id, tid, ff, largs, type, name, file, sf, origin, init, idx, exp;

    if (getUserData(sig)) {
        vector<Tree> newBranches;
        for (Tree b : sig->branches()) {
            newBranches.push_back(self(cons(b, clklist)));
        }
        Tree ident = scalID(nature, sigwclklist);
        Tree expr  = tree(sig->node(), newBranches);
        std::cerr << "expr = " << *expr << std::endl;
        fInstructions.insert(sigInstruction2MemWrite(clklist, ident, nature, expr));
        return sigInstruction2MemRead(ident, nature);
    } else if (isSigInt(sig, &i)) {
        return sig;
    } else if (isSigReal(sig, &r)) {
        return sig;
    } else if (isSigInput(sig, &i)) {
        return sig;
    } else if (isSigBinOp(sig, &i, x, y)) {
        Tree m1    = self(cons(x, clklist));
        Tree m2    = self(cons(y, clklist));
        Tree ident = scalID(nature, sigwclklist);
        fInstructions.insert(sigInstruction2MemWrite(clklist, ident, nature, sigBinOp(i, m1, m2)));
        return sigInstruction2MemRead(ident, nature);
    } else if (isSigOutput(sig, &i, x)) {
        Tree m1    = self(cons(x, clklist));
        Tree instr = sigOutput(i, m1);
        fInstructions.insert(instr);
        return instr;
    } else if (isSigUpsampling(sig, x, y)) {
        Tree m2       = self(cons(y, clklist));  // we compile the clock signal
        Tree clklist2 = cons(m2, clklist);
        Tree m1       = self(cons(x, clklist2));  // we compile x in the new time reference
#if 1
        Tree ident = scalID(nature, cons(m1, clklist2));
        Tree instr = sigInstruction2MemWrite(clklist2, ident, nature, m1);
        // std::cerr << "Upsampling instr " << ppsig(instr) << std::endl;
        fInstructions.insert(instr);
        return sigInstruction2MemRead(ident, nature);
#else
        return m1;
#endif
    } else if (isSigDownsampling(sig, x, y)) {
        // assert(isCons(clklist));
        Tree clklist0 = tl(clklist);
        Tree m1       = self(cons(x, clklist0));
        Tree ident    = scalID(nature, cons(m1, clklist0));
        Tree instr    = sigInstruction2MemWrite(clklist0, ident, nature, m1);
        // std::cerr << "Downsampling instr " << ppsig(instr) << std::endl;
        fInstructions.insert(instr);
        return sigInstruction2MemRead(ident, nature);

    } else if (isSigFixDelay(sig, x, y)) {
        Tree it     = timeID(clklist);                   // allocate time ID
        Tree mt     = sigInstruction2MemRead(it, kInt);  // instruction to read the currenttime
        Tree instr2 = sigInstruction2IncWrite(clklist, it, kInt);
        fInstructions.insert(instr2);

        if (isProj(x, &i, var)) {
            // delay of a recursive signal
            Tree iv = vecID(nature, cons(x, clklist));  // allocate delayline ID

            if (isMarked(cons(x, clklist))) {
                // we are or have already visited this projection in this context
                /*
                    MARK(Xi.T) = true       // déjà ou encours de visite
                    IV(Xi.T) = v            // nom de ligne a retard pour Xi dans le référentiel T
                    CS[D.T]  = Md x {I}d    // on compile le retard
                    IT(T) = t               // nom de la variable temps du référentiel T
                    ----------------------------------------------
                    CS[(Xi@D).T] = v[t,Md] x {I}d
                */
                Tree m2 = self(cons(y, clklist));  // compile delay signal
                return sigInstruction2DelayRead(iv, nature, mt, m2);

            } else {
                // it is our first visit
                /*
                    MARK(Xi.T) = 0          // non encore marqué
                    IV(Xi.T) = v            // nom de ligne a retard pour Xi dans le référentiel T
                    MARK(Xi.T) := v         // on marque avant la compilation de la définition

                    D(X)= (...,Si,...)      // on récupère la définition
                    CS[Si.T] = Mi x {I}i    // on compile la définition du signal récursif
                    CS[D.T]  = Md x {I}d    // on compile le signal qui indique le retard
                    IT(T) = t               // nom de la variable temps du référentiel T
                    ----------------------------------------------
                    CS[(Xi@D).T] = v[t,Md] x ({T:v[t]=Mi; T:t=t+1;} u {I}i u {I}d)
                */
                mark(cons(x, clklist));
                // get the definition of the projection
                Tree body;
                isRec(var, body);
                Tree def = nth(body, i);

                Tree m1    = self(cons(def, clklist));  // compile delayed signal
                Tree m2    = self(cons(y, clklist));    // compile delay signal
                Tree instr = sigInstruction2DelayWrite(clklist, iv, nature, mt, m1);
                fInstructions.insert(instr);
                return sigInstruction2DelayRead(iv, nature, mt, m2);
            }
        } else {
            // normal delay
            /*
                ### Retard

                CS[S1.T] = M1 x {I}1
                CS[S2.T] = M2 x {I}2
                IV(M1.T) = v            // nom de ligne a retard pour M1 dans le référentiel T
                IT(T) = t               // nom de la variable temps du référentiel T
                ----------------------------------------------
                CS[(S1@S2).T] = v[t,M2] x ({T:v[t]=M1; T:t=t+1;} u {I}1 u {I}2)
            */
            Tree m1    = self(cons(x, clklist));            // compile delayed signal
            Tree m2    = self(cons(y, clklist));            // compile delay signal
            Tree iv    = vecID(nature, cons(m1, clklist));  // allocate delayline ID
            Tree instr = sigInstruction2DelayWrite(clklist, iv, nature, mt, m1);
            fInstructions.insert(instr);
            return sigInstruction2DelayRead(iv, nature, mt, m2);
        }

    } else if (isSigIntCast(sig, x)) {
        // assert(isCons(clklist));
        Tree m1 = self(cons(x, clklist));
        return sigIntCast(m1);
    }

    /*
     else if (isProj(sig, &i, x)) {
            return sigProj(i, self(x));
        } else if (isRec(sig, var, le)) {

    */
    // UI

    else if (isSigButton(sig, label)) {
        return sig;
    } else if (isSigCheckbox(sig, label)) {
        return sig;
    }
#if 0
    // NOT YET
     else if (isSigVSlider(sig, label, c, x, y, z)) {
        return sigVSlider(label, self(c), self(x), self(y), self(z));
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        return sigHSlider(label, self(c), self(x), self(y), self(z));
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        return sigNumEntry(label, self(c), self(x), self(y), self(z));
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        return sigVBargraph(label, self(x), self(y), self(z));
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        return sigHBargraph(label, self(x), self(y), self(z));
    } else if (isSigWaveform(sig)) {
        return sig;
    }
    // Foreign functions
    else if (isSigFFun(sig, ff, largs)) {
        return sigFFun(ff, mapself(largs));
    } else if (isSigFConst(sig, type, name, file)) {
        return sig;
    } else if (isSigFVar(sig, type, name, file)) {
        return sig;
    }

    // Tables
    else if (isSigTable(sig, id, x, y)) {
        return sigTable(id, self(x), self(y));
    } else if (isSigWRTbl(sig, id, x, y, z)) {
        return sigWRTbl(id, self(x), self(y), self(z));
    } else if (isSigRDTbl(sig, x, y)) {
        // cerr << "IDENTITY TRANSFORM " << ppsig(sig) << " INTO ";
        Tree rr = sigRDTbl(self(x), self(y));
        // cerr << rr << endl;
        return rr;
    }

    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
        return sigDocConstantTbl(self(x), self(y));
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        return sigDocWriteTbl(self(x), self(y), self(u), self(v));
    } else if (isSigDocAccessTbl(sig, x, y)) {
        return sigDocAccessTbl(self(x), self(y));
    }

    // Select2 and Select3
    else if (isSigSelect2(sig, sel, x, y)) {
        return sigSelect2(self(sel), self(x), self(y));
    } else if (isSigSelect3(sig, sel, x, y, z)) {
        return sigSelect3(self(sel), self(x), self(y), self(z));
    }

    // Table sigGen
    else if (isSigGen(sig, x)) {
        if (fVisitGen) {
            return sigGen(self(x));
        } else {
            return sig;
        }
    }

    // recursive signals
    else if (isProj(sig, &i, x)) {
        return sigProj(i, self(x));
    } else if (isRec(sig, var, le)) {
        Tree var2 = tree(Node(unique("trec")));
        fResult.set(sig, rec(var2, gGlobal->nil));
        return rec(var2, mapself(le));
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        return sigIntCast(self(x));
    } else if (isSigFloatCast(sig, x)) {
        return sigFloatCast(self(x));
    }

    // Soundfile length, rate, channels, buffer
    else if (isSigSoundfile(sig, label)) {
        return sig;
    } else if (isSigSoundfileLength(sig, sf, x)) {
        return sigSoundfileLength(self(sf), self(x));
    } else if (isSigSoundfileRate(sig, sf, x)) {
        return sigSoundfileRate(self(sf), self(x));
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        return sigSoundfileBuffer(self(sf), self(x), self(y), self(z));
    }

    // Attach, Enable, Control
    else if (isSigAttach(sig, x, y)) {
        return sigAttach(self(x), self(y));
    } else if (isSigEnable(sig, x, y)) {
        return sigEnable(self(x), self(y));
    } else if (isSigControl(sig, x, y)) {
        return sigControl(self(x), self(y));
    }

    // DelayLine Read and Write
    else if (isSigInstructionDelayLineRead(sig, x, u, &nature, &dmax, &dmin,
                                           y)) {  // x is used as an id, we don't go into it
        return sigInstructionDelayLineRead(x, u, nature, dmax, dmin, self(y));
    } else if (isSigInstructionDelayLineWrite(sig, x, u, &nature, &dmax,
                                              y)) {  // x is used as an id, we don't go into it
        return sigInstructionDelayLineWrite(x, u, nature, dmax, self(y));
    }

    // Shared Read and Write
    else if (isSigInstructionSharedRead(sig, x, u, &nature)) {  // x is used as an id, we don't go into it
        return sig;
    } else if (isSigInstructionSharedWrite(sig, x, u, &nature, y)) {  // x is used as an id, we don't go into it
        return sigInstructionSharedWrite(x, u, nature, self(y));
    }

    // Vector Read and Write
    else if (isSigInstructionVectorRead(sig, x, u, &nature)) {  // x is used as an id, we don't go into it
        return sig;
    } else if (isSigInstructionVectorWrite(sig, x, u, &nature, y)) {  // x is used as an id, we don't go into it
        return sigInstructionVectorWrite(x, u, nature, self(y));
    }

    // Short DelayLine Read and Write
    else if (isSigInstructionShortDLineRead(sig, x, u, &nature, &dmin)) {  // x is used as an id, we don't go into it
        return sig;
    } else if (isSigInstructionShortDLineWrite(sig, x, u, &nature, y)) {  // x is used as an id, we don't go into it
        return sigInstructionShortDLineWrite(x, u, nature, self(y));
    }

    // Time Read and Write
    else if (isSigInstructionTimeRead(sig)) {  // x is used as an id, we don't go into it
        return sig;
    } else if (isSigInstructionTimeWrite(sig)) {  // x is used as an id, we don't go into it
        return sig;
    }

    // Control Read and Write
    else if (isSigInstructionControlRead(sig, x, u, &nature)) {  // x is used as an id, we don't go into it
        return sig;
    } else if (isSigInstructionControlWrite(sig, x, u, &nature, y)) {  // x is used as an id, we don't go into it
        return sigInstructionControlWrite(x, u, nature, self(y));
    }

    // Bargraph Read and Write
    else if (isSigInstructionBargraphRead(sig, x, u, &nature)) {  // x is used as an id, we don't go into it
        return sig;
    } else if (isSigInstructionBargraphWrite(sig, x, u, &nature, y)) {  // x is used as an id, we don't go into it
        return sigInstructionBargraphWrite(x, u, nature, self(y));
    }

    // Table Read and Write
    else if (isSigInstructionTableWrite(sig, id, origin, &nature, &dmax, init, idx, exp)) {
        return sigInstructionTableWrite(id, origin, nature, dmax, self(init), self(idx), self(exp));
    } else if (isSigInstructionTableRead(sig, id, origin, &nature, &tblsize, idx)) {
        return sigInstructionTableRead(id, origin, nature, tblsize, self(idx));
    } else if (isSigInstructionTableAccessWrite(sig, id, origin, &nature, &dmin, tid, idx)) {
        return sigInstructionTableAccessWrite(id, origin, nature, dmin, tid, self(idx));
    }
#endif
    else if (isNil(sig)) {
        // now nil can appear in table write instructions
        return sig;
    } else {
        stringstream error;
        error << __FILE__ << ":" << __LINE__ << " ERROR : unrecognized signal : " << *sig << endl;
        throw faustexception(error.str());
    }
}
