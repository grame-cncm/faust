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
  string bloc_0;
  string bloc_1;
  string bloc_2;
  string bloc_3;
  string bloc_4;
  string bloc_5;
  while (!isNil(L)) {
      trans(hd(L), &bloc_0, &bloc_2, &bloc_3, &bloc_5);
      L = tl(L);
  }
  faust_entity(&bloc_1);
  faust_process(&bloc_4);
  fout << bloc_0 << endl;
  fout << bloc_1 << endl;
  fout << bloc_2 << endl;
  fout << bloc_3 << endl;
  fout << bloc_4 << endl;
  fout << bloc_5 << endl;
}


void Signal2VHDLVisitor::trans(Tree t, string * str0, string * str1, string * str2, string * str3)
{
    // fonction affichage
    if (!fVisited.count(t)) {
        fVisited.insert(t);
        parcours(t,str0, str1, str2, str3);
        //cout << "hahoua1" << *str << endl;
    }
}

void Signal2VHDLVisitor::parcours(Tree sig, string * str0, string * str1, string * str2, string * str3)
{
    int    i;
    double r;
    Tree   c, sel, x, y, z, u, v, var, le, label, id, ff, largs, type, name, file, sf;

    if (getUserData(sig)) {
        for (Tree b : sig->branches()) {
            trans(b,str0, str1, str2, str3);
        }
        return;
    } else if (isSigInt(sig, &i)) {
        return;
    } else if (isSigReal(sig, &r)) {
        return;
    } else if (isSigWaveform(sig)) {
        return;
    } else if (isSigInput(sig, &i)) {
        return;
    } else if (isSigOutput(sig, &i, x)) {
        trans(x,str0, str1, str2, str3);
        return;
    } else if (isSigDelay1(sig, x)) {
        if (delay == false) {
          delay = true;
        }
        trans(x,str0, str1, str2, str3);
        return;
    } else if (isSigFixDelay(sig, x, y)) {
        if (delay == false) {
          delay_entity(str0);
          delay = true;
        }
        delay_component(sig, x, y, str3);
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        return;
    } else if (isSigPrefix(sig, x, y)) {
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        return;
    } else if (isSigIota(sig, x)) {
        trans(x,str0, str1, str2, str3);
        return;
    } else if (isSigBinOp(sig, &i, x, y)) {
        switch (i) {
        case 0:
            arith_entity("add", binopname[i],str0);
            arith_component("add",str2);
            trans(x,str0, str1, str2, str3);
            trans(y,str0, str1, str2, str3);
            break;
        case 1:
            arith_entity("sub", binopname[i],str0);
            arith_component("sub",str2);
            trans(x,str0, str1, str2, str3);
            trans(y,str0, str1, str2, str3);
            break;
        case 2:
            arith_entity("mul", binopname[i],str0);
            arith_component("mul",str2);
            trans(x,str0, str1, str2, str3);
            trans(y,str0, str1, str2, str3);
            break;
        case 3:
            arith_entity("div", binopname[i],str0);
            arith_component("div",str2);
            trans(x,str0, str1, str2, str3);
            trans(y,str0, str1, str2, str3);
            break;
        case 4:
            trans(x,str0, str1, str2, str3);
            trans(y,str0, str1, str2, str3);
            break;
        default:
            // operator is doesn't match any case constant (+, -, *, /)
            cout << "Error! The operator is not correct";
            break;
        //self(x);
        //self(y);
        return;
        }

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
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        return;
    } else if (isSigWRTbl(sig, id, x, y, z)) {
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        trans(z,str0, str1, str2, str3);
        return;
    } else if (isSigRDTbl(sig, x, y)) {
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        return;
    }

    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        return;
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        trans(u,str0, str1, str2, str3);
        trans(v,str0, str1, str2, str3);
        return;
    } else if (isSigDocAccessTbl(sig, x, y)) {
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        return;
    }

    // Select2 and Select3
    else if (isSigSelect2(sig, sel, x, y)) {
        trans(sel,str0, str1, str2, str3);
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        return;
    } else if (isSigSelect3(sig, sel, x, y, z)) {
        trans(sel,str0, str1, str2, str3);
        trans(x,str0, str1, str2, str3);
        trans(y,str0, str1, str2, str3);
        trans(z,str0, str1, str2, str3);
        return;
    }

    // Table sigGen
    else if (isSigGen(sig, x)) {
        if (fVisitGen) {
            trans(x,str0, str1, str2, str3);
            return;
        } else {
            return;
        }
    }

    // recursive signals
    else if (isProj(sig, &i, x)) {
        faustassert(isRec(x, var, le));
        empty_entity("proj", str0);
        trans(nth(le, i),str0, str1, str2, str3);
        return;
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        trans(x,str0, str1, str2, str3);
        return;
    } else if (isSigFloatCast(sig, x)) {
        trans(x,str0, str1, str2, str3);
        return;
    }

    // UI
    else if (isSigButton(sig, label)) {
        return;
    } else if (isSigCheckbox(sig, label)) {
        return;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        trans(c,str0, str1, str2, str3), trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3), trans(z,str0, str1, str2, str3);
        return;
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        trans(c,str0, str1, str2, str3), trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3), trans(z,str0, str1, str2, str3);
        return;
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        trans(c,str0, str1, str2, str3), trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3), trans(z,str0, str1, str2, str3);
        return;
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3), trans(z,str0, str1, str2, str3);
        return;
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3), trans(z,str0, str1, str2, str3);
        return;
    }

    // Soundfile length, rate, channels, buffer
    else if (isSigSoundfile(sig, label)) {
        return;
    } else if (isSigSoundfileLength(sig, sf, x)) {
        trans(sf,str0, str1, str2, str3), trans(x,str0, str1, str2, str3);
        return;
    } else if (isSigSoundfileRate(sig, sf, x)) {
        trans(sf,str0, str1, str2, str3), trans(x,str0, str1, str2, str3);
        return;
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        trans(sf,str0, str1, str2, str3), trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3), trans(z,str0, str1, str2, str3);
        return;
    }

    // Attach, Enable, Control
    else if (isSigAttach(sig, x, y)) {
        trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3);
        return;
    } else if (isSigEnable(sig, x, y)) {
        trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3);
        return;
    } else if (isSigControl(sig, x, y)) {
        trans(x,str0, str1, str2, str3), trans(y,str0, str1, str2, str3);
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


void Signal2VHDLVisitor::visit(Tree sig)
{
    int    i;
    double r;
    Tree   c, sel, x, y, z, u, v, var, le, label, id, ff, largs, type, name, file, sf;

    if (getUserData(sig)) {
        for (Tree b : sig->branches()) {
            self(b);
        }
        return;
    } else if (isSigInt(sig, &i)) {
        return;
    } else if (isSigReal(sig, &r)) {
        return;
    } else if (isSigWaveform(sig)) {
        return;
    } else if (isSigInput(sig, &i)) {
        return;
    } else if (isSigOutput(sig, &i, x)) {
        self(x);
        return;
    } else if (isSigDelay1(sig, x)) {
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
    } else if (isSigBinOp(sig, &i, x, y)) {
        self(x);
        self(y);
        return;
    }
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

    // recursive signals
    else if (isProj(sig, &i, x)) {
        faustassert(isRec(x, var, le));
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
