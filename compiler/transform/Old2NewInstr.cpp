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

#include "Old2NewInstr.hh"
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "Text.hh"
#include "arrow.hh"
#include "digraph.hh"
#include "digraphop.hh"
#include "global.hh"
#include "node.hh"
#include "ppsig.hh"
#include "property.hh"
#include "schedule.hh"
#include "signalDependencies.hh"
#include "signalVisitor.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "stdprinting.hh"
#include "symbol.hh"
#include "tlib.hh"
#include "tree.hh"
#include "xtended.hh"

static string nature2ctype(int n)
{
    string ctype{(n == kInt) ? "int" : "float"};
    return ctype;
}

namespace nlpl {
void graphOf(const std::set<Instr>& I)
{
#if 1
    std::map<Memory, Instr>  providedBy;  // Collect everything provided by I
    digraph<Instr, multidep> G;           // The dependency graph
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    for (Instr i : I) {
        G.add(i);
        std::set<Memory> M;
        i->getProvided(M);
        std::cout << "Instruction " << i << " provides memories: ";
        for (Memory m : M) std::cout << m << "; ";
        std::cout << std::endl;
        for (Memory m : M) {
            std::cout << "Memory " << m << " is provided by " << i << std::endl;
            providedBy[m] = i;
        }
    }
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    for (Instr i : I) {
        std::set<Dependency> D;
        i->getDependencies(D);
        std::cout << "Instruction " << i << " depends on: ";
        for (const Dependency& d : D) {
            std::cout << d.first << '@' << d.second << "; ";
            auto p = providedBy.find(d.first);
            if (p != providedBy.end()) {
                std::cout << "provided by: " << p->second << std::endl;
            } else {
                std::cout << "provided by: "
                          << "NOT FOUND" << std::endl;
            }
        }
        std::cout << "\n--------------------------------------- " << std::endl;

        for (const Dependency& d : D) {
            auto p = providedBy.find(d.first);

            if (/*(d.second == 0) &&*/ (p != providedBy.end())) {
                // Only consider immediate local dependencies
                Instr src = p->second;
                G.add(i, src, mdep(d.first->name(), d.second));
                std::cout << "\nG.add(" << i << " --" << d.first->name() << "@" << d.second << "--> " << src << ")" << std::endl;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------- " << std::endl;
    std::cout << "--------------------------------------- " << std::endl;
    std::cout << "graph " << G << std::endl;
    std::cout << "--------------------------------------- " << std::endl;
    std::cout << "--------------------------------------- " << std::endl;
    schedule<Instr> S = dfschedule(G);
    std::cout << "schedule " << S << std::endl;
#endif
}
}  // namespace nlpl

//-------------------------Old2NewInstr-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
//----------------------------------------------------------------------

nlpl::Expr old2NewExpr(Tree sig)
{
    int         i, nature, dmax, dmin;
    double      r;
    Tree        c, sel, x, y, z, u, v, var, le, label, id, tid, ff, largs, type, file, sf, origin, init, idx, exp;
    std::string filename, varname;

    if (getUserData(sig)) {
        xtended*                xtd = (xtended*)getUserData(sig);
        std::vector<nlpl::Expr> VE;
        for (Tree b : sig->branches()) {
            VE.push_back(old2NewExpr(b));
        }
        return nlpl::Fun(xtd->name(), VE);

    } else if (isSigInt(sig, &i)) {
        return nlpl::Integer(i);
    } else if (isSigReal(sig, &r)) {
        return nlpl::Float(r);
    } else if (isSigBinOp(sig, &i, x, y)) {
        return nlpl::BinaryOp(binopname[i], newbinopprec[i], old2NewExpr(x), old2NewExpr(y));
    } else if (isSigInput(sig, &i)) {
        return nlpl::ReadMem(nlpl::sFloat(subst("input$0[i]", T(i))));

    } else if (isSigButton(sig, label)) {
        string varname = uniqueStringID("fButton", sig);
        return nlpl::ReadMem(nlpl::sFloat(varname));

    } else if (isSigCheckbox(sig, label)) {
        string varname = uniqueStringID("fCheckbox", sig);
        return nlpl::ReadMem(nlpl::sFloat(varname));

    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        string varname = uniqueStringID("fSlider", sig);
        return nlpl::ReadMem(nlpl::sFloat(varname));

    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        string varname = uniqueStringID("fSlider", sig);
        return nlpl::ReadMem(nlpl::sFloat(varname));

    } else if (isSigInstructionControlRead(sig, id, origin, &nature)) {  // x is used as an id, we don't go into it
        return nlpl::ReadMem(nlpl::sFloat(tree2str(id)));
    } else if (isSigIntCast(sig, x)) {
        return nlpl::Fun("int", {old2NewExpr(x)});
    } else if (isSigFloatCast(sig, x)) {
        return nlpl::Fun("float", {old2NewExpr(x)});
    } else if (isSigSelect2(sig, sel, x, y)) {
        return nlpl::Fun("if2", {old2NewExpr(sel), old2NewExpr(x), old2NewExpr(y)});
    } else if (isSigSelect3(sig, sel, x, y, z)) {
        return nlpl::Fun("if3", {old2NewExpr(sel), old2NewExpr(x), old2NewExpr(y), old2NewExpr(z)});
    } else if (isSigInstructionTimeRead(sig)) {
        nlpl::Memory M = nlpl::Scalar(nlpl::kPermanent, "int", "time", nlpl::kFinal);
        return nlpl::ReadMem(M);
    } else if (isSigInstructionTableRead(sig, id, origin, &nature, &dmin, idx)) {
        string       vname{tree2str(id)};
        nlpl::Memory V = nlpl::Vector(nlpl::kPermanent, nature2ctype(nature), vname, 123456, nlpl::kReplaceWrite);
        return nlpl::ReadVec(V, old2NewExpr(idx), dmin);
    } else if (isSigInstructionSharedRead(sig, id, origin, &nature)) {  // x is used as an id, we don't go into it
        string       vname{tree2str(id)};
        nlpl::Memory M = nlpl::Scalar(nlpl::kSample, nature2ctype(nature), vname, nlpl::kFinal);
        return nlpl::ReadMem(M);

    } else if (isSigFConst(sig, type, id, file)) {
        string varname = tree2str(id);
        if (varname == "fSamplingFreq") varname = "fSampleRate";
        int          nature = tree2int(type);
        nlpl::Memory M      = nlpl::Scalar(nlpl::kPermanent, nature2ctype(nature), varname, nlpl::kFinal);
        return nlpl::ReadMem(M);
    }
    /*
} else if (isSigWaveform(sig)) {
    return;
}  else if (isSigDelay1(sig, x)) {
    self(x);
    return;
} else if (isSigFixDelay(sig, x, y)) {
    self(x);
    self(y);
    return;
} else if (isSigPrefix(sig, x, y)) {
    self(x);
    self(y);
    return;
} else if (isSigIota(sig, x)) {
    self(x);
    return;
} else if (isSigTime(sig)) {
    return;

// Foreign functions
else if (isSigFFun(sig, ff, largs)) {
    mapself(largs);
    return;
} else if (isSigFConst(sig, type, name, file)) {
    return;
} else if (isSigFVar(sig, type, name, file)) {
    return;
}

// Tables
else if (isSigTable(sig, id, x, y)) {
    self(x);
    self(y);
    return;
} else if (isSigWRTbl(sig, id, x, y, z)) {
    self(x);
    self(y);
    self(z);
    return;
} else if (isSigRDTbl(sig, x, y)) {
    self(x);
    self(y);
    return;
}

// Doc
else if (isSigDocConstantTbl(sig, x, y)) {
    self(x);
    self(y);
    return;
} else if (isSigDocWriteTbl(sig, x, y, u, v)) {
    self(x);
    self(y);
    self(u);
    self(v);
    return;
} else if (isSigDocAccessTbl(sig, x, y)) {
    self(x);
    self(y);
    return;
}

// Select2 and Select3
else if (isSigSelect2(sig, sel, x, y)) {
    self(sel);
    self(x);
    self(y);
    return;
} else if (isSigSelect3(sig, sel, x, y, z)) {
    self(sel);
    self(x);
    self(y);
    self(z);
    return;
}

// Table sigGen
else if (isSigGen(sig, x)) {
    if (fVisitGen) {
        self(x);
        return;
    } else {
        return;
    }
}

// Int and Float Cast
else if (isSigIntCast(sig, x)) {
    self(x);
    return;
} else if (isSigFloatCast(sig, x)) {
    self(x);
    return;
}

// UI
else if (isSigButton(sig, label)) {
    return;
} else if (isSigCheckbox(sig, label)) {
    return;
} else if (isSigVSlider(sig, label, c, x, y, z)) {
    self(c), self(x), self(y), self(z);
    return;
} else if (isSigHSlider(sig, label, c, x, y, z)) {
    self(c), self(x), self(y), self(z);
    return;
} else if (isSigNumEntry(sig, label, c, x, y, z)) {
    self(c), self(x), self(y), self(z);
    return;
} else if (isSigVBargraph(sig, label, x, y, z)) {
    self(x), self(y), self(z);
    return;
} else if (isSigHBargraph(sig, label, x, y, z)) {
    self(x), self(y), self(z);
    return;
}

// Soundfile length, rate, channels, buffer
else if (isSigSoundfile(sig, label)) {
    return;
} else if (isSigSoundfileLength(sig, sf, x)) {
    self(sf), self(x);
    return;
} else if (isSigSoundfileRate(sig, sf, x)) {
    self(sf), self(x);
    return;
} else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
    self(sf), self(x), self(y), self(z);
    return;
}

// Attach, Enable, Control
else if (isSigAttach(sig, x, y)) {
    self(x), self(y);
    return;
} else if (isSigEnable(sig, x, y)) {
    self(x), self(y);
    return;
} else if (isSigControl(sig, x, y)) {
    self(x), self(y);
    return;
    */

    else {
        stringstream error;
        error << __FILE__ << ":" << __LINE__ << " ERROR : unrecognized signal : " << *sig << endl;
        throw faustexception(error.str());
    }
}

nlpl::Instr old2NewInstr(Tree sig)
{
    int    i, nature, dmax, dmin;
    double r;
    Tree   c, sel, x, y, z, u, v, var, le, label, id, tid, ff, largs, type, name, file, sf, origin, init, idx, exp;

    // Read and Write
    if (isSigOutput(sig, &i, x)) {
        // self(x);
        return nlpl::Write(nlpl::sFloat(subst("output$0[i]", T(i))), old2NewExpr(x));
    } else if (isSigInstructionControlWrite(sig, id, origin, &nature, y)) {  // x is used as an id, we don't go into it
        // string ctype = nature2ctype(nature);
        string vname{tree2str(id)};
        // Type   t = getCertifiedSigType(origin);
        // nlpl::Expr ye = old2NewExpr(y);
        return nlpl::Write(nlpl::sFloat(vname), old2NewExpr(y));
        // if (t->variability() == kKonst) {
        //     // init level
        //     K->addDeclCode(subst("$0 \t$1;", ctype, vname));
        //     K->addInitCode(subst("$0 = $1;", vname, CS(y)));
        // } else {
        //     // block level
        //     K->addFirstPrivateDecl(vname);
        //     K->addZone2(subst("$0 \t$1 = $2;", nature2ctype(nature), vname, CS(y)));
        // }

    } else if (isSigInstructionTableWrite(sig, id, origin, &nature, &dmax, init, idx, exp)) {
        string       vname{tree2str(id)};
        nlpl::Memory V = nlpl::Vector(nlpl::kPermanent, nature2ctype(nature), vname, dmax, nlpl::kFinal);
        return nlpl::WriteVec(V, nlpl::kReplaceWrite, old2NewExpr(idx), old2NewExpr(exp));
    } else if (isSigInstructionTimeWrite(sig)) {
        nlpl::Memory M = nlpl::Scalar(nlpl::kPermanent, "int", "time", nlpl::kFinal);
        return nlpl::WriteMem(M, nlpl::kReplaceWrite, nlpl::Add(nlpl::Integer(1), nlpl::ReadMem(M, 1)));
    } else if (isSigInstructionSharedWrite(sig, id, origin, &nature, y)) {
        string       vname{tree2str(id)};
        nlpl::Memory M = nlpl::Scalar(nlpl::kSample, nature2ctype(nature), vname, nlpl::kFinal);
        return nlpl::WriteMem(M, nlpl::kReplaceWrite, old2NewExpr(y));
    }

    /*else if (isSigInstructionDelayLineRead(sig, id, origin, &nature, &dmax, &dmin,
                                            y)) {  // x is used as an id, we don't go into it
       // self(y);
       return;
   } else if (isSigInstructionDelayLineWrite(sig, id, origin, &nature, &i,
                                             y)) {  // x is used as an id, we don't go into it
       // self(y);
       return;
   }

   // Shared Read and Write
   else if (isSigInstructionSharedRead(sig, id, origin, &nature)) {  // x is used as an id, we don't go into it
       return;
   }
   else if (isSigInstructionSharedWrite(sig, id, origin, &nature, y)) {  // x is used as an id, we don't go into it
       // self(y);
       return;
   }

   // Vector Read and Write
   else if (isSigInstructionVectorRead(sig, id, origin, &nature)) {  // x is used as an id, we don't go into it
       return;
   } else if (isSigInstructionVectorWrite(sig, id, origin, &nature, y)) {  // x is used as an id, we don't go into it
       // self(y);
       return;
   }

   // Read and Write
   else if (isSigInstructionShortDLineRead(sig, id, origin, &nature,
                                           &dmin)) {  // x is used as an id, we don't go into it
       return;
   } else if (isSigInstructionShortDLineWrite(sig, id, origin, &nature,
                                              y)) {  // x is used as an id, we don't go into it
       // self(y);
       return;
   }

   else if (isSigInstructionTableWrite(sig, id, origin, &nature, &dmax, init, idx, exp)) {
       // self(init);
       // self(idx);
       // self(exp);
       return;
   } else if (isSigInstructionTableAccessWrite(sig, id, origin, &nature, &dmin, tid, x)) {
       // self(x);
       return;
   } else if (isSigInstructionTableRead(sig, id, origin, &nature, &dmin, x)) {
       // self(x);
       return;
   }

   // Read and Write
   else if (isSigInstructionControlRead(sig, id, origin, &nature)) {  // x is used as an id, we don't go into it
       return;
   } else if (isSigInstructionControlWrite(sig, id, origin, &nature, y)) {  // x is used as an id, we don't go into it
       // self(y);
       return;
   }

   // Time Read and Write
   else if (isSigInstructionTimeRead(sig)) {  // x is used as an id, we don't go into it
       return;
   } else if (isSigInstructionTimeWrite(sig)) {  // x is used as an id, we don't go into it
       return;
   }

   // Read and Write
   else if (isSigInstructionBargraphRead(sig, id, origin, &nature)) {  // x is used as an id, we don't go into it
       return;
   } else if (isSigInstructionBargraphWrite(sig, id, origin, &nature, y)) {
       // self(y);
       return;
   }

   else if (isNil(sig)) {
       // now nil can appear in table write instructions
       return;
   } */
    else {
        stringstream error;
        error << __FILE__ << ":" << __LINE__ << " ERROR : unrecognized signal : " << *sig << endl;
        throw faustexception(error.str());
    }
}
