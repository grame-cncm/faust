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

#include "signal2vhdlVisitor.hh"
#include <cstdlib>
#include <map>
#include "Text.hh"
#include "global.hh"
#include "ppsig.hh"
#include "property.hh"
#include "signals.hh"
#include "sigtyperules.hh"
#include "tlib.hh"
#include "tree.hh"
#include <typeinfo>

//-------------------------Signal2VHDLVisitor-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
//--------------------------------------------------------------------------

static const char* binopname[] = {"+", "-", "*", "/", "%", "<<", ">>", ">", "<", ">=", "<=", "==", "!=", "&", "|", "^"};
bool delay = false;
bool proj = false;


void Signal2VHDLVisitor::sigToVHDL(Tree L, ofstream& fout)
{
  Tree Output = hd(L);
  while (!isNil(L)) {
      self(hd(L)); // comment
      L = tl(L);
  }
  faust_entity(bloc_1);
  faust_process(bloc_4);
  fout << bloc_0 << endl;
  fout << bloc_1 << endl;
  fout << bloc_2 << endl;
  fout << bloc_3 << endl;
  fout << bloc_4 << endl;
  fout << input << endl;
  fout << bloc_5 << endl;
  fout << "out_left_V_int <= to_slv(sig" << Output << ");\n" << endl;
  fout << "end logic;" << endl;
}

// comment
void Signal2VHDLVisitor::self(Tree t)
{
    // fonction affichage
    if (!fVisited.count(t)) {
        fVisited.insert(t);
        visit(t);
    }
}


void Signal2VHDLVisitor::visit(Tree sig)
{
    int    i;
    double r;
    vector<Tree> subsig;
    Tree   c, sel, x, y, z, u, v, var, le, label, id, ff, largs, type, name, file, sf;

    xtended* p = (xtended*)getUserData(sig);

    if (p) {
      if (strcmp(p->name(), "fmod") == 0) {
        if (fEntity.count("fmod") == 0) {
          arith_entity("FMOD", "mod", bloc_0);
          fEntity.insert({"fmod", true});
        }
        box_component("FMOD", 2, bloc_3);
        getSubSignals(sig, subsig);
        decl_sig_2(subsig[0], subsig[1], bloc_2);
        box_instantiate("FMOD", sig, subsig[0], subsig[1], bloc_5);
        self(subsig[0]);
        self(subsig[1]);
      } else {
          for (Tree b : sig->branches()) {
            self(b);
          }
      }

        return;
    } else if (isSigInt(sig, &i)) {
        return;
    } else if (isSigReal(sig, &r)) {
        return;
    } else if (isSigWaveform(sig)) {
        return;
    } else if (isSigInput(sig, &i)) {
        input_affectation(sig, input);
        return;
    } else if (isSigOutput(sig, &i, x)) {
        self(x);
        return;
    } else if (isSigDelay1(sig, x)) {
        self(x);
        return;
    } else if (isSigFixDelay(sig, x, y)) {
        if (fEntity.count("DELAY") == 0) {
          delay_entity(bloc_0);
          fEntity.insert({"DELAY", true});
        }
        decl_sig_1(x, bloc_2);
        delay_instantiate(sig, x, y, bloc_5);
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
    } else if (isSigBinOp(sig, &i, x, y)) {
        switch (i) {
          case 0:
            if (fEntity.count(binopname[i]) == 0) {
              arith_entity("ADD", binopname[i], bloc_0);
              fEntity.insert({binopname[i], true});
            }
            box_component("ADD", 2, bloc_3);
            decl_sig_2(x, y, bloc_2);
            box_instantiate("ADD", sig, x, y, bloc_5);
            break;
          case 1:
            if (fEntity.count(binopname[i]) == 0) {
              arith_entity("SUB", binopname[i], bloc_0);
              fEntity.insert({binopname[i], true});
            }
            box_component("SUB", 2, bloc_3);
            decl_sig_2(x, y, bloc_2);
            box_instantiate("SUB", sig, x, y, bloc_5);
            break;
          case 2:
            if (fEntity.count(binopname[i]) == 0) {
              arith_entity("MUL", binopname[i], bloc_0);
              fEntity.insert({binopname[i], true});
            }
            box_component("MUL", 2, bloc_3);
            decl_sig_2(x, y, bloc_2);
            box_instantiate("MUL", sig, x, y, bloc_5);
            break;
          case 3:
            if (fEntity.count(binopname[i]) == 0) {
              arith_entity("DIV", binopname[i], bloc_0);
              fEntity.insert({binopname[i], true});
            }
            box_component("DIV", 2, bloc_3);
            decl_sig_2(x, y, bloc_2);
            box_instantiate("DIV", sig, x, y, bloc_5);
            break;
          case 4:
            break;
          default:
            // operator is doesn't match any case constant (+, -, *, /)
            cout << "Error! The operator is not correct";
            break;
        }
        self(x);
        self(y);
        return;
    // Foreign functions
    } else if (isSigFFun(sig, ff, largs)) {
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

    // recursive signals
    else if (isProj(sig, &i, x)) {
        faustassert(isRec(x, var, le));
        if (fEntity.count("proj") == 0) {
          empty_entity("PROJ", bloc_0);
          fEntity.insert({"proj", true});
        }
        box_component("PROJ", 1, bloc_3);
        decl_sig_1(x, bloc_2);
        proj_instantiate(sig, nth(le, i), bloc_5);
        self(nth(le, i));
        return;
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
    }

    else if (isNil(sig)) {
        // now nil can appear in table write instructions
        return;
    } else {
        stringstream error;
        error << __FILE__ << ":" << __LINE__ << " ERROR : unrecognized signal : " << *sig << endl;
        throw faustexception(error.str());
    }
}
