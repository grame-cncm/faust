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

void Signal2VHDLVisitor::sigToVHDL(Tree L, ofstream& fout)
{
    Tree Output = hd(L);
    while (!isNil(L)) {
        self(hd(L)); // comment
        L = tl(L);
    }
    entity_faust();
    faust_process();
    fout << fDeclEntity << endl;
    fout << fFaustEntity << endl;
    fout << fDeclSig << endl;
    fout << fDeclCompnt << endl;
    fout << fFaustProcess << endl;
    fout << fInput << endl;
    fout << fMapCompnt << endl;
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
            getSubSignals(sig, subsig);
            bin_op("FMOD", "mod", sig, subsig[0], subsig[1]);
            self(subsig[0]);
            self(subsig[1]);
        } else {
            for (Tree b : sig->branches()) {
                self(b);
            }
        }
        
        return;
    } else if (isSigInt(sig, &i)) {
        decl_sig(sig);
        return;
    } else if (isSigReal(sig, &r)) {
        decl_sig(sig);
        return;
    } else if (isSigWaveform(sig)) {
        return;
    } else if (isSigInput(sig, &i)) {
        input_affectation(sig);
        return;
    } else if (isSigOutput(sig, &i, x)) {
        self(x);
        return;
    } else if (isSigDelay1(sig, x)) {
        self(x);
        return;
    } else if (isSigFixDelay(sig, x, y)) {
        if (fEntity.count("DELAY") == 0) {
            entity_delay(fDeclEntity);
            component_delay(fDeclCompnt);
            fEntity.insert({"DELAY", true});
        }
        decl_sig(sig);
        inst_delay(sig, x, y, fMapCompnt);
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
                bin_op("ADD", binopname[i], sig, x, y);
                break;
            case 1:
                bin_op("SUB", binopname[i], sig, x, y);
                break;
            case 2:
                bin_op("MUL", binopname[i], sig, x, y);
                break;
            case 3:
                bin_op("DIV", binopname[i], sig, x, y);
                break;
            case 4:
                break;
            case 13:
                bin_op("AND", "and", sig, x, y);
                break;
            case 14:
                bin_op("OR", "or", sig, x, y);
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
            entity_bypass("PROJ", fDeclEntity);
            component_standard("PROJ", 1, fDeclCompnt);
            fEntity.insert({"proj", true});
        }
        decl_sig(sig);
        inst_proj(sig, nth(le, i), fMapCompnt);
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

void Signal2VHDLVisitor::bin_op(const string& name, const char* op, Tree sig, Tree x, Tree y)
{
    if (fEntity.count(op) == 0) {
        entity_bin_op(name, op, fDeclEntity);
        component_standard(name, 2, fDeclCompnt);
        fEntity.insert({op, true});
    }
    decl_sig(sig);
    inst_bin_op(name, sig, x, y, fMapCompnt);
}

string Signal2VHDLVisitor::addr_to_str(Tree t)
{
    stringstream s;
    s << t;
    return s.str();
}

string Signal2VHDLVisitor::val_to_str(Tree t)
{
    stringstream s;
    s << *t;
    return s.str();
}

void Signal2VHDLVisitor::entity_header(string & str)
{
    str += "library ieee;\n"
    "use ieee.std_logic_1164.all;\n"
    "use ieee.numeric_std.all;\n"
    "use ieee.std_logic_arith.all;\n"
    "use ieee.std_logic_signed.all;\n"
    "use work.fixed_pkg.all;\n\n";
}

void Signal2VHDLVisitor::generic_decl(string & str)
{
    str += "generic (\n"
    "    msb     : integer;\n"
    "    lsb     : integer);\n";
}

void Signal2VHDLVisitor::port_decl(int input, string & str)
{
    str += "port (\n";
    for (int i = 0; i < input; i++) {
        str += "   input_"+ to_string(i) + "  : in  sfixed(msb downto lsb);\n";
    }
    str += "   output_0 : in  sfixed(msb downto lsb));\n";
}

void Signal2VHDLVisitor::entity_bin_op(const string& name, const char* op, string & str)
{
    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(2,str);
    str += "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "output  <=  resize(input_0 " + op + " input_1,msb,lsb);\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_delay(string & str)
{
    entity_header(str);
    str += "entity DELAY is\n"
    "generic (\n"
    "    delay    : integer;\n"
    "    msb      : integer;\n"
    "    lsb      : integer);\n"
    "port (\n"
    "    ws       : in std_logic;\n"
    "    input_0  : in  sfixed(msb downto lsb);\n"
    "    output_0 : out sfixed(msb downto lsb));\n"
    "end DELAY;\n"
    "architecture behavioral of DELAY is\n"
    "type mem is array (delay downto 0) of sfixed(msb downto lsb);\n"
    "signal ligne : mem;\n"
    "begin\n"
    "process(ws)\n"
    "    begin\n"
    "    ligne(0) <= input_0;\n"
    "    if rising_edge(ws) then\n"
    "        for i in 1 to delay loop\n"
    "            ligne(i) <= ligne(i-1);\n"
    "        end loop;\n"
    "    end if;\n"
    "end process;\n"
    "output_0 <= ligne(delay);\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_bypass(const string& name, string & str)
{
    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(1,str);
    str += "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "output_0  <=  input_0;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_faust()
{
    entity_header(fDeclEntity);
    fDeclEntity += "entity FAUST_IP is\n"
    "port (\n"
    "  ap_clk : in std_logic;\n"
    "  ap_rst_n : in std_logic;\n"
    "  ap_ws : in std_logic;\n"
    "  ap_start : in std_logic;\n"
    "  ap_done : out std_logic;\n"
    "  bypass_dsp : in std_logic;\n"
    "  bypass_faust : in std_logic;\n"
    "  in_left_V : in std_logic_vector (23 downto 0);\n"
    "  in_right_V : in std_logic_vector (23 downto 0);\n"
    "  out_left_V_ap_vld : out std_logic;\n"
    "  out_right_V_ap_vld : out std_logic;\n"
    "  out_left_V : out std_logic_vector (23 downto 0);\n"
    "  out_right_V : out std_logic_vector (23 downto 0));\n"
    "end FAUST_IP;\n"
    "architecture logic of FAUST_IP is\n\n"
    "signal    in_left_V_buf : std_logic_vector (23 downto 0);\n"
    "signal    in_left_fixed : sfixed(23 downto 0);\n"
    "signal    in_right_V_buf :  std_logic_vector (23 downto 0);\n"
    "signal    out_left_V_int : std_logic_vector (23 downto 0);\n"
    "signal    out_left_fixed : sfixed(23 downto 0);\n"
    "signal    out_right_V_int :  std_logic_vector (23 downto 0);\n"
    "signal    step_cnt : integer;\n"
    "signal    ap_start_reg : std_logic;";
}

void Signal2VHDLVisitor::component_standard(const string& name, int input, string & str)
{
    str += "component " + name + " is\n";
    generic_decl(str);
    port_decl(input,str);
    str += "end component;\n\n";
}

void Signal2VHDLVisitor::component_delay(string & str)
{
    str += "component DELAY is\n"
    "generic (\n"
    "    delay    : integer;\n"
    "    msb      : integer;\n"
    "    lsb      : integer);\n"
    "port (\n"
    "    ws       : in std_logic;\n"
    "    input_0  : in  sfixed(msb downto lsb);\n"
    "    output_0 : out sfixed(msb downto lsb));\n"
    "end component;\n\n";
}

void Signal2VHDLVisitor::faust_process()
{
    fFaustProcess += "begin\n\n"
    " process(ap_clk, ap_rst_n)\n"
    "   variable clock_cnt : integer := 0;\n"
    " begin\n\n"
    "   if(ap_rst_n = '0') then\n"
    "     step_cnt <= 0;\n"
    "     clock_cnt := 0;\n"
    "     ap_done <= '0';\n"
    "     out_left_V   <= (others => '0');\n"
    "     out_left_V_ap_vld   <= '0';\n"
    "     out_right_V  <= (others => '0');\n"
    "     out_right_V_ap_vld <=   '0' ;\n"
    "   elsif(ap_clk'event and ap_clk = '1') then\n"
    "     -- trick used to detect rising edge of ap_start ('event does not work)\n"
    "     ap_start_reg <= ap_start;\n"
    "     if (ap_start = '1') and (ap_start_reg /= ap_start) then\n"
    "       clock_cnt := 0;\n"
    "     end if;\n"
    "     -- loading (buffering) input data\n"
    "     if (clock_cnt = 1) then\n"
    "       step_cnt <= step_cnt + 1;\n"
    "       in_left_V_buf <= in_left_V;\n"
    "       in_right_V_buf <= in_right_V;\n"
    "     end if;\n"
    "     clock_cnt := clock_cnt+1;\n\n"
    "     -- Say faust has read all input at cycle 20 and keeps ready until cycle 400\n"
    "     if (clock_cnt > 100) and (clock_cnt <102)  then\n"
    "     end if;\n\n"
    "     -- Say faust output are ready is active between cycle 50 and 400\n"
    "     if (clock_cnt >= 300) and (clock_cnt <302) then\n"
    "       ap_done <= '1';\n"
    "       out_right_V <=  out_right_V_int;\n"
    "       out_left_V <= out_left_V_int;\n"
    "     else\n"
    "       ap_done <= '0';\n"
    "     end if ;\n"
    "   end if;\n"
    " end process;\n\n"
    " ------------------------------------------------------------------------\n"
    " --------------   Data flow equation          ---------------------------\n"
    " ------------------------------------------------------------------------\n\n";
}

void Signal2VHDLVisitor::inst_delay(Tree sig, Tree x, Tree y, string & str)
{
    str += "DELAY_" + addr_to_str(sig) + " : delay\n"
    "generic map (\n"
    "    delay => "+ val_to_str(y) +",\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    ws => ap_ws,\n"
    "    input_0  => sig"+ addr_to_str(x) +",\n"
    "    output_1 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_proj(Tree sig, Tree x, string & str)
{
    str += "PROJ_" + addr_to_str(sig) + " : PROJ\n"
    "generic map (\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    input_0  => sig"+ addr_to_str(x) +",\n"
    "    output_1 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_bin_op(const string& name, Tree sig, Tree x, Tree y, string & str)
{
    str += name + "_" + addr_to_str(sig) + " : " + name + "\n"
    "generic map (\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    input_0  => sig"+ addr_to_str(x) +",\n"
    "    input_1  => sig"+ addr_to_str(y) +",\n"
    "    output_1 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::decl_sig(Tree sig)
{
    int i;
    double r;
    if (isSigInt(sig, &i) || isSigReal(sig, &r)) {
        fDeclSig += "signal    sig"+addr_to_str(sig)+" : sfixed(1 downto -22) := to_sfixed(" + val_to_str(sig) + ",1,-22);\n";
    } else {
        fDeclSig += "signal    sig"+ addr_to_str(sig) +" : sfixed(1 downto -22) :\n";
    }
}

void Signal2VHDLVisitor::input_affectation(Tree sig)
{
    fInput += "sig" + addr_to_str(sig) + " <= to_sfixed(in_left_V_buf,1,-22);\n";
}
