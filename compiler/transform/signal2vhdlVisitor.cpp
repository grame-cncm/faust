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
    Tree output = hd(L);
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
    fout << "sigoutput <= resize(sig" << output << ",0,-23);" << endl;
    fout << "out_left_V_int <= to_slv(sigoutput);\n" << endl;
    fout << "out_right_V_int <= to_slv(sigoutput);\n" << endl;
    fout << "end logic;" << endl;
}

// comment
void Signal2VHDLVisitor::self(Tree t)
{
    // Display function
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
        } else if (strcmp(p->name(), "sin") == 0) {
            getSubSignals(sig, subsig);
            sincos_op("SIN", sig, subsig[0]);
        } else if (strcmp(p->name(), "cos") == 0) {
            getSubSignals(sig, subsig);
            sincos_op("COS", sig, subsig[0]);
        } else {
            for (Tree b : sig->branches()) {
                self(b);
            }
        }
        return;
    } else if (isSigInt(sig, &i)) {
        decl_sig(sig,1,-22);
        return;
    } else if (isSigReal(sig, &r)) {
        decl_sig(sig,1,-22);
        return;
    } else if (isSigWaveform(sig)) {
        return;
    } else if (isSigInput(sig, &i)) {
        input_affectation(sig);
        decl_sig(sig,1,-22);
        return;
    } else if (isSigOutput(sig, &i, x)) {
        self(x);
        return;
    } else if (isSigDelay1(sig, x)) {
        self(x);
        return;
    } else if (isSigDelay(sig, x, y)) {
        
        // Here is the maximum delay
        int mxd = fOccMarkup->retrieve(x)->getMaxDelay();
        if (!(isSigInt(y, &i)) && !(isSigReal(y, &r))) {
            if (fEntity.count("DELAYVAR") == 0) {
                if (mxd < 5000) { // to precise number
                    entity_delay_var_reg(fDeclEntity);
                } else {
                    entity_delay_var_ram(fDeclEntity);
                }
                component_delay_var(fDeclCompnt);
                fEntity.insert({"DELAYVAR", true});
            }
            decl_sig(sig,1,-22);
            inst_delay_var(sig, x, y, fMapCompnt, mxd);
        } else {
            if (((y->node()).getInt()) == 0) {
                bypass("DELAY0", sig, x);
            } else {
                if (fEntity.count("DELAY") == 0) {
                    entity_delay(fDeclEntity);
                    component_delay(fDeclCompnt);
                    fEntity.insert({"DELAY", true});
                }
                decl_sig(sig,1,-22);
                inst_delay(sig, x, y, fMapCompnt);
            }
        }
        self(x);
        self(y);
        return;
    } else if (isSigPrefix(sig, x, y)) {
        self(x);
        self(y);
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
                bin_op("MODULO", "mod", sig, x, y);
                break;
            case 8:
                cmp_op("GT", binopname[i], sig, x, y);
                break;
            case 9:
                cmp_op("LT", binopname[i], sig, x, y);
                break;
            case 10:
                cmp_op("GE", binopname[i], sig, x, y);
                break;
            case 11:
                cmp_op("LE", binopname[i], sig, x, y);
                break;
            case 12:
                cmp_op("EQUAL", "=", sig, x, y);
                break;
            case 13:
                cmp_op("DIFF", "/=", sig, x, y);
                break;
            case 14:
                bin_op("ANDL", "and", sig, x, y);
                break;
            case 15:
                bin_op("ORL", "or", sig, x, y);
                break;
            case 16:
                bin_op("XORL", "xor", sig, x, y);
                break;
            default:
                // operator is doesn't match any case constant (+, -, *, /, ...)
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
    
    // Select2
    else if (isSigSelect2(sig, sel, x, y)) {
        select_op("SELECT2", sig, sel, x, y);
        self(sel);
        self(x);
        self(y);
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
        bypass("PROJ", sig, nth(le, i));
        self(nth(le, i));
        return;
    }
    
    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        bypass("IntCast", sig, x);
        self(x);
        return;
    } else if (isSigFloatCast(sig, x)) {
        bypass("FloatCast", sig, x);
        self(x);
        return;
    }
    
    // UI
    else if (isSigButton(sig, label)) {
        return;
    } else if (isSigCheckbox(sig, label)) {
        return;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        bypass("HSLIDER", sig, c);
        self(c); // self(x), self(y), self(z);
        return;
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        bypass("HSLIDER", sig, c);
        self(c); // self(x), self(y), self(z);
        return;
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        bypass("ENTRY", sig, c);
        self(c); // self(x), self(y), self(z);
        return;
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        self(x), self(y), self(z);
        return;
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        self(x), self(y), self(z);
        return;
    }
    
    // Soundfile length, rate, buffer
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

void Signal2VHDLVisitor::entity_header(string& str)
{
    str += "library ieee;\n"
    "use ieee.std_logic_1164.all;\n"
    "use ieee.numeric_std.all;\n"
    "use ieee.std_logic_arith.all;\n"
    "use ieee.std_logic_signed.all;\n"
    "use work.fixed_pkg.all;\n\n";
}

void Signal2VHDLVisitor::generic_decl(string& str)
{
    str += "generic (\n"
    "    msb     : integer;\n"
    "    lsb     : integer);\n";
}

void Signal2VHDLVisitor::port_decl(int input, string& str)
{
    str += "port (\n"
    "   clk     : in std_logic;\n"
    "   rst     : in std_logic;\n";
    for (int i = 0; i < input; i++) {
        str += "   input"+ to_string(i) + "  : in  sfixed(msb downto lsb);\n";
    }
    str += "   output0 : out sfixed(msb downto lsb));\n";
}

void Signal2VHDLVisitor::entity_bin_op(const string& name, const char* op, string& str)
{
    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(2,str);
    str += "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "output0  <=  resize(input0 " + op + " input1,msb,lsb);\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_bin_op_concat(const string& name, const char* op, string& str)
{
    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(2,str);
    str += "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "signal inter : sfixed(63 downto 0);\n"
    "begin\n"
    "inter  <=  resize(input0 " + op + " input1,63,0);\n"
    "output0 <= inter(msb downto lsb);\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_cmp_op(const string& name, const char* op, string& str)
{
    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(2,str);
    str += "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "process(input0, input1)\n"
    "begin\n"
    " if (input0 " + op + " input1) then\n"
    "   output0 <= to_sfixed(1,msb,lsb);\n"
    " else\n"
    "   output0 <= to_sfixed(0,msb,lsb);\n"
    " end if; \n"
    "end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_delay(string& str)
{
    entity_header(str);
    str += "entity DELAY is\n"
    "generic (\n"
    "    delay   : integer;\n"
    "    msb     : integer;\n"
    "    lsb     : integer);\n"
    "port (\n"
    "    ws      : in std_logic;\n"
    "    input0  : in  sfixed(msb downto lsb);\n"
    "    output0 : out sfixed(msb downto lsb));\n"
    "end DELAY;\n"
    "architecture behavioral of DELAY is\n"
    "type mem is array (delay-1 downto 0) of sfixed(msb downto lsb);\n"
    "signal ligne : mem;\n"
    "begin\n"
    "process(ws)\n"
    "    begin\n"
    "    ligne(0) <= input0;\n"
    "    if rising_edge(ws) then\n"
    "        for i in 1 to delay-1 loop\n"
    "            ligne(i) <= ligne(i-1);\n"
    "        end loop;\n"
    "    output0 <= ligne(delay-1);\n"
    "    end if;\n"
    "end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_delay_var_reg(string& str)
{
    entity_header(str);
    str += "entity DELAYVAR is\n"
    "generic(\n"
    "    mxd       : integer;\n"
    "    msb       : integer;\n"
    "    lsb       : integer);\n"
    "port(\n"
    "    ws        : in std_logic;\n"
    "    rst_n     : in  std_logic;\n"
    "    delay_var : in  sfixed(23 downto 0);\n"
    "    input0    : in  sfixed(msb downto lsb);\n"
    "    output0   : out sfixed(msb downto lsb));\n"
    "end DELAYVAR;\n"
    "architecture behavioral of DELAYVAR is\n"
    "type t_ram is array (mxd downto 0) of sfixed(msb downto lsb);\n"
    "signal mem : t_ram;\n"
    "begin\n"
    "process(ws,delay_var)\n"
    "begin\n"
    " if rising_edge(ws) then\n"
    "   mem(0) <= input0;\n"
    "   for i in 1 to mxd loop\n"
    "     mem(i) <= mem(i-1);\n"
    "   end loop;\n"
    " end if;\n\n"
    " if (to_integer(delay_var) = 0) then\n"
    "   output0 <= input0;\n"
    " else\n"
    "   output0 <= mem(to_integer(delay_var)-1);\n"
    " end if;\n"
    "end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_delay_var_ram(string& str)
{
    entity_header(str);
    str += "entity DELAYVAR is\n"
    "generic(\n"
    "    mxd       : integer;\n"
    "    msb       : integer;\n"
    "    lsb       : integer);\n"
    "port(\n"
    "    ws        : in  std_logic;\n"
    "    rst_n     : in  std_logic;\n"
    "    delay_var : in  sfixed(23 downto 0);\n"
    "    input0    : in  sfixed(msb downto lsb);\n"
    "    output0   : out sfixed(msb downto lsb));\n"
    "end DELAYVAR;\n"
    "architecture behavioral of DELAYVAR is\n"
    "type t_ram is array (mxd downto 0) of sfixed(msb downto lsb);\n"
    "signal mem : t_ram;\n"
    "signal r_addr_wr   : integer range 0 to mxd := 0;\n"
    "signal r_addr_rd   : integer range 0 to mxd := 0;\n"
    "begin\n\n"
    "p_write : process(ws)\n"
    "begin\n"
    " if rising_edge(ws) then\n"
    "   mem(r_addr_wr) <= input0;\n"
    "   if(r_addr_wr < mxd) then\n"
    "     r_addr_wr <= r_addr_wr + 1;\n"
    "   else\n"
    "     r_addr_wr <= 0;\n"
    "   end if;\n"
    " end if;\n"
    "end process p_write;\n\n"
    "p_read : process(ws)\n"
    "begin\n"
    " if rising_edge(ws) then\n"
    "   r_addr_rd <= r_addr_wr - to_integer(delay_var);\n"
    "   if(r_addr_rd < 0) then\n"
    "     output0 <= mem(r_addr_rd+mxd+1);\n"
    "   else\n"
    "     output0 <= mem(r_addr_rd);\n"
    "   end if;\n"
    " end if;\n"
    "end process p_read;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_bypass(const string& name, string& str)
{
    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(1,str);
    str += "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "process (clk,rst)\n"
    "begin\n"
    "  if rst = '0' then\n"
    "    output0 <= (others => '0');\n"
    "  else\n"
    "    output0 <= input0;\n"
    "  end if;\n"
    "end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_select2(const string& name, string& str)
{
    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(3,str);
    str += "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "process(input0)\n"
    "begin\n"
    "if (input0 = 0) then\n"
    "    output0 <= input2;\n"
    "else\n"
    "    output0 <= input1;\n"
    "end if;\n"
    "end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_faust()
{
    entity_header(fDeclEntity);
    fDeclEntity += "entity FAUST is\n"
    "port (\n"
    "  ws : in std_logic;\n"
    "  ap_clk : in std_logic;\n"
    "  ap_rst_n : in std_logic;\n"
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
    "end FAUST;\n"
    "architecture logic of FAUST is\n\n"
    "signal    in_left_V_buf   : std_logic_vector (23 downto 0);\n"
    "signal    in_left_fixed   : sfixed(23 downto 0);\n"
    "signal    in_right_V_buf  :  std_logic_vector (23 downto 0);\n"
    "signal    out_left_V_int  : std_logic_vector (23 downto 0);\n"
    "signal    out_left_fixed  : sfixed(23 downto 0);\n"
    "signal    out_right_V_int :  std_logic_vector (23 downto 0);\n"
    "signal    step_cnt  : integer;\n"
    "signal    sigoutput : sfixed(23 downto 0);";
}

void Signal2VHDLVisitor::component_standard(const string& name, int input, string& str)
{
    str += "component " + name + " is\n";
    generic_decl(str);
    port_decl(input,str);
    str += "end component;\n\n";
}

void Signal2VHDLVisitor::component_delay(string& str)
{
    str += "component DELAY is\n"
    "generic (\n"
    "    delay    : integer;\n"
    "    msb      : integer;\n"
    "    lsb      : integer);\n"
    "port (\n"
    "    ws      : in std_logic;\n"
    "    input0  : in  sfixed(msb downto lsb);\n"
    "    output0 : out sfixed(msb downto lsb));\n"
    "end component;\n\n";
}

void Signal2VHDLVisitor::component_delay_var(string& str)
{
    str += "component DELAYVAR is\n"
    "generic (\n"
    "    mxd      : integer;\n"
    "    msb      : integer;\n"
    "    lsb      : integer);\n"
    "port (\n"
    "   ws        : in  std_logic;\n"
    "   rst_n     : in  std_logic;\n"
    "   delay_var : in  sfixed(msb downto lsb);\n"
    "   input0    : in  sfixed(msb downto lsb);\n"
    "   output0   : out sfixed(msb downto lsb));\n"
    "end component;\n\n";
}

void Signal2VHDLVisitor::component_sincos(string& str)
{
    str += "component SinCos24 is\n"
    "port (\n"
    "    input : in   sfixed(1 downto -22);\n"
    "    SIN   : out  sfixed(0 downto -23);\n"
    "    COS   : out  sfixed(0 downto -23));\n"
    "end component;\n\n";
}

void Signal2VHDLVisitor::faust_process()
{
    fFaustProcess += "begin\n\n"
    " process(ap_clk, ap_rst_n, ap_start)\n"
    "   variable clock_cnt : integer := 0;\n"
    "   variable date_ap_vld1 : integer := 3;\n"
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
    "     if (ap_start = '1') then\n"
    "       clock_cnt := 0;\n"
    "     end if;\n"
    "     -- loading (buffering) input data\n"
    "     if (clock_cnt = 1) then\n"
    "       --step_cnt <= step_cnt + 1;\n"
    "       in_left_V_buf <= in_left_V;\n"
    "       in_right_V_buf <= in_right_V;\n"
    "     end if;\n"
    "     clock_cnt := clock_cnt+1;\n"
    "     -- Say faust left output is ready\n"
    "     if (clock_cnt >= 2) and (clock_cnt < 3)  then\n"
    "       out_left_V_ap_vld <= '1';\n"
    "       out_left_V <= out_left_V_int;\n"
    "       out_right_V_ap_vld <= '1';\n"
    "       out_right_V <=  out_right_V_int;\n"
    "       ap_done <= '1';\n"
    "     else\n"
    "       ap_done <= '0';\n"
    "       out_right_V_ap_vld <= '0';\n"
    "       out_left_V_ap_vld <= '0';\n"
    "     end if;\n"
    "   end if;\n"
    " end process;\n"
    " ------------------------------------------------------------------------\n"
    " --------------   Data flow equation          ---------------------------\n"
    " ------------------------------------------------------------------------\n\n";
}

void Signal2VHDLVisitor::inst_bin_op(const string& name, Tree sig, Tree x, Tree y, string& str)
{
    str += name + "_" + addr_to_str(sig) + " : " + name + "\n"
    "generic map (\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    clk => ap_clk,\n"
    "    rst => ap_rst_n,\n"
    "    input0  => sig"+ addr_to_str(x) +",\n"
    "    input1  => sig"+ addr_to_str(y) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_delay(Tree sig, Tree x, Tree y, string& str)
{
    str += "DELAY_" + addr_to_str(sig) + " : DELAY\n"
    "generic map (\n"
    "    delay => "+ val_to_str(y) +",\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    ws => ws,\n"
    "    input0  => sig"+ addr_to_str(x) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_delay_var(Tree sig, Tree x, Tree y, string& str, int mxd)
{
    str += "DELAYVAR_" + addr_to_str(sig) + " : DELAYVAR\n"
    "generic map (\n"
    "    mxd => "+ to_string(mxd) +",\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    ws => ws,\n"
    "    rst_n => ap_rst_n,\n"
    "    delay_var => sig"+ addr_to_str(y) +",\n"
    "    input0  => sig"+ addr_to_str(x) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_sincos(const string& name, Tree sig, Tree x, string& str)
{
    str += name + "_" + addr_to_str(sig) + " : SinCos24\n"
    "port map (\n"
    "    input  => sig"+ addr_to_str(x) +",\n"
    "    " + name + " => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_bypass(const string& name, Tree sig, Tree x, string& str)
{
    str += name + "_" + addr_to_str(sig) + " : " + name + "\n"
    "generic map (\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    clk => ap_clk,\n"
    "    rst => ap_rst_n,\n"
    "    input0  => sig"+ addr_to_str(x) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_select2(const string& name, Tree sig, Tree sel, Tree x, Tree y, string& str)
{
    str += name + "_" + addr_to_str(sig) + " : " + name + "\n"
    "generic map (\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    clk => ap_clk,\n"
    "    rst => ap_rst_n,\n"
    "    input0  => sig"+ addr_to_str(sel) +",\n"
    "    input1  => sig"+ addr_to_str(x) +",\n"
    "    input2  => sig"+ addr_to_str(y) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::decl_sig(Tree sig, int msb, int lsb)
{
    int i;
    double r;
    if (isSigInt(sig, &i) || isSigReal(sig, &r)) {
        fDeclSig += "signal    sig"+addr_to_str(sig)+" : sfixed(" +to_string(msb)+ " downto " +to_string(lsb)+") := to_sfixed("+val_to_str(sig)+","+to_string(msb)+","+to_string(lsb)+");\n";
    } else {
        fDeclSig += "signal    sig"+ addr_to_str(sig) +" : sfixed("+to_string(msb)+" downto "+to_string(lsb)+");\n";
    }
}

void Signal2VHDLVisitor::input_affectation(Tree sig)
{
    fInput += "sig" + addr_to_str(sig) + " <= to_sfixed(in_left_V_buf,1,-22);\n";
}

void Signal2VHDLVisitor::bin_op(const string& name, const char* op, Tree sig, Tree x, Tree y)
{
    if (fEntity.count(op) == 0) {
        entity_bin_op(name, op, fDeclEntity);
        component_standard(name, 2, fDeclCompnt);
        fEntity.insert({op, true});
    }
    decl_sig(sig,1,-22);
    inst_bin_op(name, sig, x, y, fMapCompnt);
}

void Signal2VHDLVisitor::select_op(const string& name, Tree sig, Tree sel, Tree x, Tree y)
{
    if (fEntity.count(name) == 0) {
        entity_select2(name, fDeclEntity);
        component_standard(name, 3, fDeclCompnt);
        fEntity.insert({name, true});
    }
    decl_sig(sig,1,-22);
    inst_select2(name, sig, sel, x, y, fMapCompnt);
}

void Signal2VHDLVisitor::cmp_op(const string& name, const char* op, Tree sig, Tree x, Tree y)
{
    if (fEntity.count(op) == 0) {
        entity_cmp_op(name, op, fDeclEntity);
        component_standard(name, 2, fDeclCompnt);
        fEntity.insert({op, true});
    }
    decl_sig(sig,1,-22);
    inst_bin_op(name, sig, x, y, fMapCompnt);
}

void Signal2VHDLVisitor::sincos_op(const string& name, Tree sig, Tree x)
{
    if (fEntity.count("SinCos24") == 0) {
        component_sincos(fDeclCompnt);
        fEntity.insert({"SinCos24", true});
    }
    decl_sig(sig,0,-23);
    inst_sincos(name, sig, x, fMapCompnt);
    self(x);
}

void Signal2VHDLVisitor::bypass(const string& name, Tree sig, Tree x)
{
    if (fEntity.count(name) == 0) {
        entity_bypass(name, fDeclEntity);
        component_standard(name, 1, fDeclCompnt);
        fEntity.insert({name, true});
    }
    decl_sig(sig,1,-22);
    inst_bypass(name, sig, x, fMapCompnt);
}
