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

#include "codegen_vhdl.hh"
#include <cstdlib>


string addr_to_str(Tree t)
{
    stringstream s;
    s << t;
    return s.str();
}

string val_to_str(Tree t)
{
    stringstream s;
    s << *t;
    return s.str();
}

void arith_entity(string name, const char* op, string & str) {
    str += "library ieee;\n"
    "use ieee.std_logic_1164.all;\n"
    "use ieee.std_logic_arith.all;\n"
    "use ieee.std_logic_signed.all;\n"
    "use work.fixed_pkg.all;\n\n"
    "entity " + name + " is\n"
    "generic (\n"
    "    msb     : integer;\n"
    "    lsb     : integer);\n"
    "port (\n"
    "    input_0 : in  sfixed(msb downto lsb);\n"
    "    input_1 : in  sfixed(msb downto lsb);\n"
    "    output  : out sfixed(msb downto lsb));\n"
    "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "output  <=  resize(input_0 " + op + " input_1,msb,lsb);\n"
    "end behavioral;\n\n";
}

void delay_entity(string & str) {
    str += "library ieee;\n"
    "use ieee.std_logic_1164.all;\n"
    "use ieee.std_logic_arith.all;\n"
    "use ieee.std_logic_signed.all;\n"
    "use work.fixed_pkg.all;\n\n"
    "entity delay is\n"
    "generic (\n"
    "    delay  : integer;\n"
    "    msb    : integer;\n"
    "    lsb    : integer);\n"
    "port (\n"
    "    ws       : in std_logic;\n"
    "    input_0  : in  sfixed(msb downto lsb);\n"
    "    output_0 : out sfixed(msb downto lsb));\n"
    "end delay;\n"
    "architecture behavioral of delay is\n"
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

void empty_entity(string name, string & str) {
    str += "library ieee;\n"
    "use ieee.std_logic_1164.all;\n"
    "use ieee.std_logic_arith.all;\n"
    "use ieee.std_logic_signed.all;\n"
    "use work.fixed_pkg.all;\n\n"
    "entity " + name + " is\n"
    "generic (\n"
    "    msb     : integer;\n"
    "    lsb     : integer);\n"
    "port (\n"
    "    input_0  : in  sfixed(msb downto lsb);\n"
    "    output_0 : out sfixed(msb downto lsb));\n"
    "end " + name + ";\n"
    "architecture behavioral of " + name + " is\n"
    "begin\n"
    "output_0  <=  input_0;\n"
    "end behavioral;\n\n";
}

void faust_entity(string & str) {
    str += "library ieee;\n"
    "use ieee.std_logic_1164.all;\n"
    "use ieee.numeric_std.all;\n"
    "use ieee.std_logic_signed.all;\n"
    "use ieee.std_logic_arith.all;\n"
    "use work.fixed_pkg.all;\n\n"
    "entity emul_faust is\n"
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
    "end emul_faust;\n"
    "architecture logic of emul_faust is\n\n"
    "signal    in_left_V_buf : std_logic_vector (23 downto 0);\n"
    "signal    in_left_fixed : sfixed(23 downto 0);\n"
    "signal    in_right_V_buf :  std_logic_vector (23 downto 0);\n"
    "signal    out_left_V_int : std_logic_vector (23 downto 0);\n"
    "signal    out_left_fixed : sfixed(23 downto 0);\n"
    "signal    out_right_V_int :  std_logic_vector (23 downto 0);\n"
    "signal    step_cnt : integer;\n"
    "signal    ap_start_reg : std_logic;";
}

void faust_process(string & str) {
    str += "begin\n\n"
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

void box_component(string name, int input, string & str) {
    str += "component " + name + " is\n"
    "generic (\n"
    "    msb  : integer;\n"
    "    lsb  : integer);\n"
    "port (\n";
    for (int i = 0; i < input; i++) {
      str += "   input_"+ to_string(i) + " : in  sfixed(msb downto lsb);\n";
    }
    str += "   output_0 : in  sfixed(msb downto lsb);\n"
    "end component;\n\n";
}


void delay_instantiate(Tree sig, Tree x, Tree y, string & str) {
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

void proj_instantiate(Tree sig, Tree x, string & str) {
    str += "PROJ_" + addr_to_str(sig) + " : PROJ\n"
    "generic map (\n"
    "    msb => 1,\n"
    "    lsb => -22)\n"
    "port map (\n"
    "    input_0  => sig"+ addr_to_str(x) +",\n"
    "    output_1 => sig"+ addr_to_str(sig) +");\n\n";
}


void box_instantiate(string name, Tree sig, Tree x, Tree y, string & str) {
  str += name + "_" + addr_to_str(sig) + " : " + name + "\n"
  "generic map (\n"
  "    msb => 1,\n"
  "    lsb => -22)\n"
  "port map (\n"
  "    input_0  => sig"+ addr_to_str(x) +",\n"
  "    input_1  => sig"+ addr_to_str(y) +",\n"
  "    output_1 => sig"+ addr_to_str(sig) +");\n\n";
}

void decl_sig_1(Tree x, string & str) {
  str += "signal    sig"+ addr_to_str(x) +" : sfixed(1 downto -22) :\n";
}


void decl_sig_2(Tree x, Tree y, string & str) {
  int i;
  double r;
  if (isSigInt(y, &i) || isSigReal(y, &r)) {
    str += "signal    sig"+addr_to_str(y)+" : sfixed(1 downto -22) := to_sfixed("+val_to_str(y)+",1,-22);\n";
  } else {
    str += "signal    sig"+ addr_to_str(y) +" : sfixed(1 downto -22) :\n";
  }
  str += "signal    sig"+ addr_to_str(x) +" : sfixed(1 downto -22) :\n";
}

void input_affectation(Tree sig, string & str) {
  str += "sig" + addr_to_str(sig) + " <= to_sfixed(in_left_V_buf,1,-22);\n";
}
