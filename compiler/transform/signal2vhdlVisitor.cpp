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

#include <cstdlib>
#include <string>
#include <typeinfo>

#include "signal2vhdlVisitor.hh"
#include "sigtyperules.hh"

//-------------------------Signal2VHDLVisitor-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
// 2022 TANG: I introduced HIGH and LOW (default HIGH = 8 and LOW = -23) to have
// systematic 32 bit size for sfixed
//--------------------------------------------------------------------------

static const char* binopname[] = {
    "+", "-", "*", "/", "%",
    "<<", ">>", ">", "<",
    ">=", "<=", "=", "!=",
    "&", "|", "^"
};

void Signal2VHDLVisitor::sigToVHDL(Tree L, ostream& fout)
{
    Tree output[2];
    int i = 0;

    while (!isNil(L)) {
        output[i] = hd(L);
        i++;
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

    if (globalCodingSfixed()) {
        // coding is sfixed
        fout << "left_sigoutput <= sig" << addr_to_str(output[0]) << ";" << endl;
    } else {
        // coding is float
        fout << "left_sigoutput <= to_sfixed(sig" << addr_to_str(output[0]) << ",8,-23);"
        << endl;
    }
    //fout << "sigoutput <= resize(sig" << output << ",0,-23);" << endl;
    fout << "left_out_fixed_32bits <= left_sigoutput;"  << endl;
    fout << "left_out_slv_32bits <= to_slv(left_out_fixed_32bits);" << endl;
    fout << "out_left_V_int(22 downto 0) <=  left_out_slv_32bits(22 downto 0);" << endl;
    fout << "out_left_V_int(23) <=  left_out_slv_32bits(31);" << endl;

    if (globalCodingSfixed()) {
        fout << "right_sigoutput <= sig" << addr_to_str(output[1]) << ";" << endl;
    } else {
        fout << "right_sigoutput <= to_sfixed(sig" << addr_to_str(output[1]) << ",8,-23);"
        << endl;
    }

    fout << "right_out_fixed_32bits <= right_sigoutput;"  << endl;
    fout << "right_out_slv_32bits <= to_slv(right_out_fixed_32bits);" << endl;
    fout <<  "out_right_V_int(22 downto 0) <= right_out_slv_32bits(22 downto 0);" << endl;
    fout <<  "out_right_V_int(23) <= right_out_slv_32bits(31);" << endl;
    fout << "end logic;" << endl;
}

void Signal2VHDLVisitor::visit(Tree sig)
{
    int    i;
    double r;
    vector<Tree> subsig;
    Tree   c, sel, x, y, z, u, v, var, le, label, id, ff, largs, type, name, file, sf;

    xtended* p = (xtended*) getUserData(sig);
    int nature = getCertifiedSigType(sig)->nature();
    string suffixe = getObjectSuffix(nature);

    if (p) {
        if (strcmp(p->name(), "fmod") == 0) {
            getSubSignals(sig, subsig);
            bin_op("FMOD" + suffixe, "mod", sig, subsig[0], subsig[1]);
            self(subsig[0]);
            self(subsig[1]);
        } else if (strcmp(p->name(), "sin") == 0) {
            getSubSignals(sig, subsig);
            sincos_op("SIN", sig, subsig[0], nature);
        } else if (strcmp(p->name(), "cos") == 0) {
            getSubSignals(sig, subsig);
            sincos_op("COS", sig, subsig[0],nature);
        } else {
            for (Tree b : sig->branches()) {
                self(b);
            }
        }
        return;
    } else if (isSigInt(sig, &i)) {
        decl_sig(sig, HIGH, LOW, nature);
        return;
    } else if (isSigReal(sig, &r)) {
        decl_sig(sig, HIGH, LOW, nature);
        return;
    } else if (isSigWaveform(sig)) {
        return;
    } else if (isSigInput(sig, &i)) {
        input_affectation(sig,i);
        decl_sig(sig, HIGH, LOW, nature);
        return;
    } else if (isSigOutput(sig, &i, x)) {
        /* Never reached */
        self(x);
        return;
    } else if (isSigDelay1(sig, x)) {
        self(x);
        return;
    } else if (isSigDelay(sig, x, y)) {

        // Here is the maximum delay
        int mxd = fOccMarkup->retrieve(x)->getMaxDelay();
        if (!(isSigInt(y, &i)) && !(isSigReal(y, &r))) {
            if (fEntity.count("DELAYVAR" + suffixe) == 0) {
                if (mxd < 5000) { // to precise number
                    entity_delay_var_reg(nature, fDeclEntity);
                } else {
                    entity_delay_var_ram(nature, fDeclEntity);
                }
                component_delay_var(nature, fDeclCompnt);
                fEntity.insert({"DELAYVAR" + suffixe, true});
            }
            decl_sig(sig, HIGH, LOW, nature);
            inst_delay_var(sig, x, y, fMapCompnt, mxd);
        } else {
            if (((y->node()).getInt()) == 0) {
                bypass("DELAY0" + suffixe, sig, x);
            } else {
                if (fEntity.count("DELAY" + suffixe) == 0) {
                    entity_delay(nature, fDeclEntity);
                    component_delay(nature, fDeclCompnt);
                    fEntity.insert({"DELAY" + suffixe, true});
                }
                decl_sig(sig, HIGH, LOW, nature);
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
                bin_op("ADD" + suffixe, binopname[i], sig, x, y);
                break;
            case 1:
                bin_op("SUB" + suffixe, binopname[i], sig, x, y);
                break;
            case 2:
                bin_op("MUL" + suffixe, binopname[i], sig, x, y);
                break;
            case 3:
                bin_op("DIV" + suffixe, binopname[i], sig, x, y);
                break;
            case 4:
                bin_op("MODULO" + suffixe, "mod", sig, x, y);
                break;
            case 8:
                cmp_op("GT" + suffixe, ">", sig, x, y);
                break;
            case 9:
                cmp_op("LT" + suffixe, "<", sig, x, y);
                break;
            case 10:
                cmp_op("GE" + suffixe, ">=", sig, x, y);
                break;
            case 11:
                cmp_op("LE" + suffixe, "<=", sig, x, y);
                break;
            case 12:
                cmp_op("EQUAL" + suffixe, "=", sig, x, y);
                break;
            case 13:
                cmp_op("DIFF" + suffixe, "/=", sig, x, y);
                break;
            case 14:
                bin_op("ANDL" + suffixe, "and", sig, x, y);
                break;
            case 15:
                bin_op("ORL" + suffixe, "or", sig, x, y);
                break;
            case 16:
                bin_op("XORL" + suffixe, "xor", sig, x, y);
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
        select_op("SELECT2" + suffixe, sig, sel, x, y);
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
        bypass("PROJ" + suffixe, sig, nth(le, i));
        self(nth(le, i));
        return;
    }

    // Int and Float Cast
    else if (isSigIntCast(sig, x)) {
        //bypass("IntCast", sig, x);
        cast("IntCast", sig, x);
        self(x);
        return;
    } else if (isSigFloatCast(sig, x)) {
        //bypass("FloatCast", sig, x);
        cast("FloatCast", sig, x);
        self(x);
        return;
    }

    // UI
    else if (isSigButton(sig, label)) {
        return;
    } else if (isSigCheckbox(sig, label)) {
        return;
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        bypass("HSLIDER" + suffixe, sig, c);
        self(c); // self(x), self(y), self(z);
        return;
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        bypass("HSLIDER" + suffixe, sig, c);
        self(c); // self(x), self(y), self(z);
        return;
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        bypass("ENTRY" + suffixe, sig, c);
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
        cerr << __FILE__ << ":" << __LINE__ << " ERROR : unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
}

string Signal2VHDLVisitor::addr_to_str(Tree t)
{
    stringstream s;
    s << t->serial();
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
    "use work.fixed_float_types.all;\n"
    "use work.fixed_pkg.all;\n"
    "use work.float_pkg.all;\n\n";
}

void Signal2VHDLVisitor::generic_decl(string& str)
{
    str += "generic (\n"
    "    msb     : integer;\n"
    "    lsb     : integer);\n";
}

void Signal2VHDLVisitor::port_decl(int input, int nature, string& str)
{
    string range = getRange(nature);
    string stype = getSignalType(nature);

    str += "port (\n"
    "   clk     : in std_logic;\n"
    "   rst     : in std_logic;\n";
    for (int i = 0; i < input; i++) {
        str += "   input" + to_string(i) + "  : in  " + stype + range + ";\n";
    }
    str += "   output0 : out " + stype + range + ");\n";
}

void Signal2VHDLVisitor::entity_bin_op(const string& name, const char* op, int nature, string& str)
{
    string range = getMSB(nature) + ", " + getLSB(nature);
    string stype = getSignalType(nature);

    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(2,nature,str);
    str += "end " + name + ";\n\n"
    "architecture behavioral of " + name + " is\n"
    "  signal temp : " + stype + "(msb downto lsb);\n"
    "begin\n";
    if (globalCodingSfixed()) {
        str += "  temp  <= resize(input0 " + (string)op + " input1,"
        + range + ");\n";
    } else {
        str +="  temp  <=  resize(input0 " + (string)op + " input1,temp);\n";
    }
    str += "  output0 <= temp;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_bin_op_concat(const string& name, const char* op, int nature, string& str)
{
    int high = getHigh(nature), low = getLow(nature);
    string stype = getSignalType(nature);

    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(2, nature, str);
    str += "end " + name + ";\n\n"
    "architecture behavioral of " + name + " is\n"
    "signal inter : " + stype + "(63 downto 0);\n"
    "begin\n"
    "inter  <=  resize(input0 " + op + " input1,63,0);\n"
    "output0 <= inter("+ to_string(high) +" downto " + to_string(low) + " );\n"  //?????
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_cmp_op(const string& name, const char* op, int nature, string& str)
{
    string range = getMSB(nature) + ", " + getLSB(nature);
    string stype = getSignalType(nature);

    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(2, nature, str);
    str += "end " + name + ";\n\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "process(input0, input1)\n"
    "begin\n"
    " if (input0 " + op + " input1) then\n"
    "   output0 <= to_" + stype + "(1," + range + ");\n"
    " else\n"
    "   output0 <= to_" + stype + "(0," + range + ");\n"
    " end if; \n"
    "end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_delay(int nature, string& str)
{
    string nature_string = getObjectSuffix(nature);
    string stype = getSignalType(nature);
    string range = getRange(nature);
    string range_init = getFloatMSB(nature);
    if (globalCodingFloat() && nature == kReal)
         range_init.append("input0 ");
    else range_init.append(",");
    range_init.append(getFloatLSB(nature));
    entity_header(str);

    str += "entity DELAY" + nature_string + " is\n"
    "generic (\n"
    "    delay_value   : integer;\n"
    "    msb     : integer;\n"
    "    lsb     : integer);\n"
    "port (\n"
    "    ws      : in std_logic;\n"
    "    rst     : in std_logic;\n"
    "    input0  : in  " + stype + "" + range + ";\n"
    "    output0 : out " + stype + "" + range + ");\n"
    "end DELAY" + nature_string + ";\n\n"
    "architecture behavioral of DELAY" + nature_string + " is\n"
    "type mem is array (delay_value-1 downto 0) of " + stype + "" + range + ";\n"
    "signal ligne : mem;\n"
    "begin\n"
    "output0 <= ligne(delay_value-1);\n"
    "process(ws,rst)\n"
    "    begin\n"
    "        if rst = '0' then\n"
    "           for i in 0 to delay_value-1 loop\n"
    "               ligne(i) <= to_" + stype + "(0," + range_init + ");\n"
    "           end loop;\n"
    "        else\n"
    "           if rising_edge(ws) then\n"
    "               ligne(0) <= input0;\n"
    "               for i in 1 to delay_value-1 loop\n"
    "                   ligne(i) <= ligne(i-1);\n"
    "               end loop;\n"
    "           end if;\n"
    "        end if;\n"
    "    end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_delay_var_reg(int nature, string& str)
{
    string stype  = getSignalType(nature);
    string range  = getRange(nature);
    entity_header(str);

    str += "entity DELAYVAR is\n"
    "generic(\n"
    "    mxd       : integer;\n"
    "    msb       : integer;\n"
    "    lsb       : integer);\n"
    "port(\n"
    "    ws        : in std_logic;\n"
    "    rst_n     : in  std_logic;\n"
    "    delay_var : in  " + stype + "(31 downto 0);\n"
    "    input0    : in  " + stype + "" + range + ";\n"
    "    output0   : out " + stype + "" + range + ");\n"
    "end DELAYVAR;\n\n"
    "architecture behavioral of DELAYVAR is\n"
    "type t_ram is array (mxd downto 0) of " + stype + "" + range + ";\n"
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

void Signal2VHDLVisitor::entity_delay_var_ram(int nature, string& str)
{
    string stype = getSignalType(nature);
    string range = getRange(nature);
    string range_init = getFloatMSB(nature);
    if (globalCodingFloat() && nature == kReal)
         range_init.append("input0 ");
    else range_init.append(",");
    range_init.append(getFloatLSB(nature));
    entity_header(str);

    str += "entity DELAYVAR is\n"
    "TODO"
    "generic(\n"
    "    mxd       : integer;\n"
    "    msb       : integer;\n"
    "    lsb       : integer);\n"
    "port(\n"
    "    ws        : in  std_logic;\n"
    "    rst_n     : in  std_logic;\n"
    "    delay_var : in  " + stype + "(31 downto 0);\n"
    "    input0    : in  " + stype + "" + range + ";\n"
    "    output0   : out " + stype + "" + range + ");\n"
    "end DELAYVAR;\n\n"
    "architecture behavioral of DELAYVAR is\n"
    "type t_ram is array (mxd downto 0) of " + stype + "" + range + ";\n"
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

void Signal2VHDLVisitor::entity_bypass(const string& name, int nature, string& str)
{
    // signal initialization is a bit tricky
    string range = getRange(nature);
    string stype = getSignalType(nature);
    string range_init = getFloatMSB(nature);
    if (globalCodingFloat() && nature == kReal)
         range_init.append("input0 ");
    else range_init.append(",");
    range_init.append(getFloatLSB(nature));

    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(1,nature,str);
    str += "end " + name + ";\n\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "process (clk,rst)\n"
    "begin\n"
    "  if rst = '0' then\n"
    "    output0 <= to_" + stype + "(0," + range_init + ");\n"
    "  else\n"
    "    output0 <= input0;\n"
    "  end if;\n"
    "end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_cast(const string& name, int nature_in, int nature_out, string& str)
{
    string coding     = getRealCoding();
    string stype_in   = getSignalType(nature_in);
    string stype_out  = getSignalType(nature_out);
    string range_in   = getRange(nature_in);
    string range_out  = getRange(nature_out);
    string range_init = getFloatMSB(nature_out);
//        ((gGlobal->gVHDLFloatType == 1) ? ((nature_out == kReal) ? " temp ": ",") : ",") + getFloatLSB(nature_out);
//    string range_init_ = getFloatMSB(nature_out);
    if (globalCodingFloat() && nature_out == kReal)
         range_init.append(" temp ");
    else range_init.append(",");
    range_init += getFloatLSB(nature_out);

    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    str += "port (\n"
    "   clk     : in std_logic;\n"
    "   rst     : in std_logic;\n";
    str += "   input0  : in  " + stype_in  + range_in + ";\n";
    str += "   output0 : out " + stype_out + range_out + ");\n";
    str += "end " + name + ";\n\n"
    "architecture behavioral of " + name + " is\n"
    "  signal temp : " + coding + "(msb downto lsb);\n"
    "begin\n"
    "output0 <= temp;\n"
    "process (clk,rst)\n"
    "begin\n"
    "  if rst = '0' then\n"
    "    temp <= to_" + coding + "(0," + range_init + ");\n"
    "  else\n";
    if (globalCodingSfixed()) {
        str += "  temp <= resize(input0,msb,lsb);\n";
    } else {
        str += "  temp  <= to_float(input0,temp);\n";
    }
    str += "  end if;\n"
    "end process;\n"
    "end behavioral;\n\n";
}

void Signal2VHDLVisitor::entity_select2(const string& name, int nature, string& str)
{
    entity_header(str);
    str += "entity " + name + " is\n";
    generic_decl(str);
    port_decl(3, nature, str);
    str += "end " + name + ";\n\n"
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
    string separator = gGlobal->gVHDLFloatType ? " downto " : ",";
    string sig_float_coding = "float_coding";

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
    "end FAUST;\n\n"
    "architecture logic of FAUST is\n\n"
    "signal    in_left_V_buf  : std_logic_vector (23 downto 0);\n"
    "signal    in_left_fixed  : sfixed(23 downto 0);\n"
    "signal    in_left_fixed_24bits : sfixed(0 downto -23);\n"
    "signal    in_right_V_buf : std_logic_vector (23 downto 0);\n"
    "signal    in_right_fixed : sfixed(23 downto 0);\n"
    "signal    in_right_fixed_24bits : sfixed(0 downto -23);\n"
    "signal    out_left_V_int : std_logic_vector (23 downto 0);\n"
    "signal    out_right_V_int : std_logic_vector (23 downto 0);\n"
    "signal    step_cnt  : integer;\n"
    "signal    left_sigoutput : sfixed(8 downto -23);\n"
    "signal    left_out_fixed_32bits : sfixed(31 downto 0);\n"
    "signal    left_out_slv_32bits : std_logic_vector (31 downto 0);\n"
    "signal    left_out_slv_24bits : std_logic_vector (24 downto 0);\n"
    "signal    right_sigoutput : sfixed(8 downto -23);\n"
    "signal    right_out_fixed_32bits : sfixed(31 downto 0);\n"
    "signal    right_out_slv_32bits : std_logic_vector (31 downto 0);\n"
    "signal    right_out_slv_24bits : std_logic_vector (24 downto 0);\n";

    if (globalCodingFloat()) { //float vhdl option
        fDeclEntity += "\n"
        "signal    sig_float_coding : float(8 downto -23);\n";
    }
}

void Signal2VHDLVisitor::component_standard(const string& name, int input, int nature, string& str)
{
    string nature_coding = getObjectSuffix(nature);
    str += "component " + name + " is\n";
    generic_decl(str);
    port_decl(input, nature, str);
    str += "end component;\n\n";
}

void Signal2VHDLVisitor::component_cast(const string& name, int input, int nature_in, int nature_out, string& str)
{
    string stype_in  = getSignalType(nature_in);
    string stype_out = getSignalType(nature_out);
    int high_in  = getHigh(nature_in),  low_in  = getLow(nature_in);
    int high_out = getHigh(nature_out), low_out = getLow(nature_out);

    str += "component " + name + " is\n";
    generic_decl(str);
    str += "port (\n"
    "   clk     : in std_logic;\n"
    "   rst     : in std_logic;\n";
    str += "   input0  : in  sfixed(" + to_string(high_in) + " downto " + to_string(low_in) + ");\n";
    str += "   output0 : out " + stype_out + "("  + to_string(high_out) + " downto " + to_string(low_out) + "));\n";
    str += "end component;\n\n";
}

void Signal2VHDLVisitor::component_delay(int nature, string& str)
{
    int high = getHigh(nature), low = getLow(nature);
    string suffix = getObjectSuffix(nature);
    string stype  = getSignalType(nature);

    str += "component DELAY" + suffix + " is\n"
    "generic (\n"
    "    delay_value    : integer;\n"
    "    msb      : integer;\n"
    "    lsb      : integer);\n"
    "port (\n"
    "    ws      : in std_logic;\n"
    "    rst     : in std_logic;\n"
    "    input0  : in  " + stype + "(" + to_string(high) + " downto " + to_string(low) + ");\n"
    "    output0 : out " + stype + "(" + to_string(high) + " downto " + to_string(low) + "));\n"
    "end component;\n\n";
}

void Signal2VHDLVisitor::component_delay_var(int nature, string& str)
{
    string stype = getSignalType(nature);
    int high = getHigh(nature), low = getLow(nature);

    str += "component DELAYVAR is\n"
    "generic (\n"
    "    mxd      : integer;\n"
    "    msb      : integer;\n"
    "    lsb      : integer);\n"
    "port (\n"
    "   ws        : in  std_logic;\n"
    "   rst_n     : in  std_logic;\n"
    "   delay_var : in  " + stype + "(31 downto 0)\n"
    "   input0    : in  " + stype + "(" + to_string(high) + " downto " + to_string(low) + ");\n"
    "   output0   : out " + stype + "(" + to_string(high) + " downto " + to_string(low) + "));\n"
    "end component;\n\n";
}

void Signal2VHDLVisitor::component_sincos(int nature, string& str)
{
    string stype = getSignalType(nature);
    printf("WARNING, SinCos not impl yet\n");
    str += "component SinCos8_23 is\n"
    "port (\n"
    "    input8_23 : in   " + stype + "(8 downto -23);\n"
    "    SIN8_23   : out  " + stype + "(8 downto -23);\n"
    "    COS8_23   : out  " + stype + "(8 downto -23));\n"
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
    // test type of first argument
    int nature = getCertifiedSigType(x)->nature();
    int high = getHigh(nature), low = getLow(nature);

    str += name + "_" + addr_to_str(sig) + " : " + name + "\n"
    "generic map (\n"
    "    msb => " + to_string(high) + ",\n"
    "    lsb => " + to_string(low) +" )\n"
    "port map (\n"
    "    clk => ap_clk,\n"
    "    rst => ap_rst_n,\n"
    "    input0  => sig"+ addr_to_str(x) +",\n"
    "    input1  => sig"+ addr_to_str(y) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_delay(Tree sig, Tree x, Tree y, string& str)
{
    // test type of output
    int nature = getCertifiedSigType(sig)->nature();
    int high = getHigh(nature), low = getLow(nature);

    string suffix = getObjectSuffix(nature);

    str += "DELAY" + suffix + "_" + addr_to_str(sig) + " : DELAY" + suffix + "\n"
    "generic map (\n"
    "    delay_value => "+ val_to_str(y) +",\n"
    "    msb => " + to_string(high) + ",\n"
    "    lsb => " + to_string(low) +" )\n"
    "port map (\n"
    "    ws => ws,\n"
    "    rst => ap_rst_n,\n"
    "    input0  => sig"+ addr_to_str(x) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_delay_var(Tree sig, Tree x, Tree y, string& str, int mxd)
{
    // test type of second input
    int nature = getCertifiedSigType(sig)->nature();
    int high = getHigh(nature), low = getLow(nature);

    str += "DELAYVAR_" + addr_to_str(sig) + " : DELAYVAR\n"
    "generic map (\n"
    "    mxd => " + to_string(mxd) + ",\n"
    "    msb => " + to_string(high) + ",\n"
    "    lsb => " + to_string(low) + " )\n"
    "port map (\n"
    "    ws => ws,\n"
    "    rst_n => ap_rst_n,\n"
    "    delay_var => sig" + addr_to_str(y) + ",\n"
    "    input0  => sig" + addr_to_str(x) + ",\n"
    "    output0 => sig" + addr_to_str(sig) + ");\n\n";
}

void Signal2VHDLVisitor::inst_sincos(const string& name, Tree sig, Tree x, int nature, string& str)
{
    str += name + "_" + addr_to_str(sig) + " : SinCos8_23\n"
    "port map (\n"
    "    input8_23  => sig" + addr_to_str(x) + ",\n"
    "    " + name + "8_23   => sig" + addr_to_str(sig) + ");\n\n";
}

void Signal2VHDLVisitor::inst_bypass(const string& name, Tree sig, Tree x, string& str)
{
    // test type of  input
    int nature = getCertifiedSigType(sig)->nature();
    int high = getHigh(nature), low = getLow(nature);

    str += name + "_" + addr_to_str(sig) + " : " + name +  "\n"
    "generic map (\n"
    "    msb => " + to_string(high) + ",\n"
    "    lsb => " + to_string(low) +" )\n"
    "port map (\n"
    "    clk => ap_clk,\n"
    "    rst => ap_rst_n,\n"
    "    input0  => sig"+ addr_to_str(x) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::inst_select2(const string& name, Tree sig, Tree sel, Tree x, Tree y, string& str)
{
    // test type of  input
    int nature = getCertifiedSigType(x)->nature();
    int high = getHigh(nature), low = getLow(nature);

    str += name + "_" + addr_to_str(sig) + " : " + name + "\n"
    "generic map (\n"
    "    msb => " + to_string(high) + ",\n"
    "    lsb => " + to_string(low) +" )\n"
    "port map (\n"
    "    clk => ap_clk,\n"
    "    rst => ap_rst_n,\n"
    "    input0  => sig"+ addr_to_str(sel) +",\n"
    "    input1  => sig"+ addr_to_str(x) +",\n"
    "    input2  => sig"+ addr_to_str(y) +",\n"
    "    output0 => sig"+ addr_to_str(sig) +");\n\n";
}

void Signal2VHDLVisitor::decl_sig(Tree sig, int msb, int lsb, int nature)
{
    int i;
    double r;
    string stype = getSignalType(nature);
    string separator = gGlobal->gVHDLFloatType ? " downto " : ",";
    string val_init_sfixed, val_init_float;
    val_init_sfixed = "(" + val_to_str(sig) + "," + to_string(msb) + separator + to_string(lsb) + ")";
    val_init_float = "(" + val_to_str(sig) + ", sig_float_coding )";

    if (nature == kReal) {
        // float type: " + float_coding + "(msb,lsb)
        if (isSigInt(sig, &i) || isSigReal(sig, &r)) {// with initialization
            fDeclSig += "signal    sig" + addr_to_str(sig) + " : " + stype + "(" + to_string(msb) + " downto " + to_string(lsb) + ") := to_" + stype + (gGlobal->gVHDLFloatType ? val_init_float : val_init_sfixed) + ";\n";
        } else {
            // without initialization
            fDeclSig += "signal    sig" + addr_to_str(sig) + " : " + stype + "(" + to_string(msb) + " downto " + to_string(lsb) + ");\n";
        }
    } else {
        // int type: " sfixed(31,0)
        if (isSigInt(sig, &i) || isSigReal(sig, &r)) {// with initialization
            fDeclSig += "signal    sig" + addr_to_str(sig) + " : sfixed(" + to_string(31) + " downto " + to_string(0) + ") := to_sfixed(" + val_to_str(sig) + "," + to_string(31) + "," + to_string(0) + ");\n";
        } else {
            // without initialization
            fDeclSig += "signal    sig" + addr_to_str(sig) + " : sfixed(" + to_string(31)+" downto " + to_string(0) + ");\n";
        }
    }
}

void Signal2VHDLVisitor::input_affectation(Tree sig, int i)
{
    if (i == 0) {
        // left channel
        fInput +="in_left_fixed_24bits <= to_sfixed(in_left_V_buf,0,-23);\n";
        if (gGlobal->gVHDLFloatType == 0) {
            // sfixed
            fInput += "sig" + addr_to_str(sig) +
            " <= resize(in_left_fixed_24bits," + to_string(HIGH) + "," + to_string(LOW) + ");\n";
        } else {
            // float
            fInput += "sig" + addr_to_str(sig) +
            " <= to_float(in_left_fixed_24bits, sig" + addr_to_str(sig) + ");\n";
        }
    } else {
        // right channel
        fInput +="in_right_fixed_24bits <= to_sfixed(in_right_V_buf,0,-23);\n";
        if (gGlobal->gVHDLFloatType == 0) {
            // sfixed
            fInput += "sig" + addr_to_str(sig) +
            " <= resize(in_right_fixed_24bits," + to_string(HIGH) + "," + to_string(LOW) + ");\n";
        } else {
            // float
            fInput += "sig" + addr_to_str(sig) +
            " <= to_float(in_right_fixed_24bits, sig" + addr_to_str(sig) + ");\n";
        }
    }
}

void Signal2VHDLVisitor::bin_op(const string& name, const char* op, Tree sig, Tree x, Tree y)
{
    int nature = getCertifiedSigType(sig)->nature();
    if (fEntity.count(name) == 0) {
        entity_bin_op(name, op, nature, fDeclEntity);
        component_standard(name, 2, nature, fDeclCompnt);
        fEntity.insert({name, true});
    }
    decl_sig(sig, HIGH, LOW, nature);
    inst_bin_op(name, sig, x, y, fMapCompnt);
}

void Signal2VHDLVisitor::select_op(const string& name, Tree sig, Tree sel, Tree x, Tree y)
{
    int nature = getCertifiedSigType(sig)->nature();
    if (fEntity.count(name) == 0) {
        entity_select2(name, nature, fDeclEntity);
        component_standard(name, 3, nature, fDeclCompnt);
        fEntity.insert({name, true});
    }
    decl_sig(sig, HIGH, LOW, nature);
    inst_select2(name, sig, sel, x, y, fMapCompnt);
}

void Signal2VHDLVisitor::cmp_op(const string& name, const char* op, Tree sig, Tree x, Tree y)
{
    int nature = getCertifiedSigType(x)->nature();

    if (fEntity.count(name) == 0) {
        entity_cmp_op(name, op, nature, fDeclEntity);
        component_standard(name, 2, nature, fDeclCompnt);
        fEntity.insert({name, true});
    }
    decl_sig(sig, HIGH, LOW, nature);
    inst_bin_op(name, sig, x, y, fMapCompnt);
}

void Signal2VHDLVisitor::sincos_op(const string& name, Tree sig, Tree x, int nature)
{
    if (fEntity.count("SinCos8_23") == 0) {
        component_sincos(nature,fDeclCompnt);
        fEntity.insert({"SinCos8_23", true});
    }
    decl_sig(sig, 8, -23, nature);
    inst_sincos(name, sig, x, nature, fMapCompnt);
    self(x);
}

void Signal2VHDLVisitor::bypass(const string& name, Tree sig, Tree x)
{
    int nature = getCertifiedSigType(sig)->nature();
    string real_name = name + getObjectSuffix(nature);

    if (fEntity.count(real_name) == 0) {
        entity_bypass(name, nature, fDeclEntity);
        component_standard(name, 1, nature, fDeclCompnt);
        fEntity.insert({real_name, true});
    }
    decl_sig(sig, HIGH, LOW, nature);
    inst_bypass(name, sig, x, fMapCompnt);
}

void Signal2VHDLVisitor::cast(const string& name, Tree sig, Tree x)
{
    int nature_in  = getCertifiedSigType(x)->nature();
    int nature_out = getCertifiedSigType(sig)->nature();
    string real_name = name + getObjectSuffix(nature_out);
    int high_out = getHigh(nature_out);
    int low_out  = getLow(nature_out);

    if (fEntity.count(real_name) == 0) {
        entity_cast(real_name, nature_in, nature_out, fDeclEntity);
        component_cast(real_name, 1, nature_in, nature_out, fDeclCompnt);
        fEntity.insert({real_name, true});
    }
    decl_sig(sig, high_out, low_out, nature_out);
    inst_bypass(real_name, sig, x, fMapCompnt);
}

// Public API
void sigVHDLFile(old_OccMarkup* markup, Tree L, bool trace)
{
    Signal2VHDLVisitor V(markup);
    ofstream file("faust.vhd");
    V.sigToVHDL(L, file);
    V.trace(trace, "VHDL");  // activate with --trace option
    V.mapself(L);
}
