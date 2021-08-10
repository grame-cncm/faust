library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_signed.all;
use work.fixed_pkg.all;

entity DELAYVAR is
generic(
    mxd       : integer;
    msb       : integer;
    lsb       : integer);
port(
    ws        : in std_logic;
    rst_n     : in  std_logic;
    delay_var : in  sfixed(23 downto 0);
    input0    : in  sfixed(msb downto lsb);
    output0   : out sfixed(msb downto lsb));
end DELAYVAR;
architecture behavioral of DELAYVAR is
type t_ram is array (mxd downto 0) of sfixed(msb downto lsb);
signal mem : t_ram;
begin
process(ws,delay_var)
begin
 if rising_edge(ws) then
   mem(0) <= input0;
   for i in 1 to mxd loop
     mem(i) <= mem(i-1);
   end loop;
 end if;
end process;
output0 <= mem(to_integer(delay_var)-1);
end behavioral;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_signed.all;
use work.fixed_pkg.all;

entity PROJ is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end PROJ;
architecture behavioral of PROJ is
begin
process (clk,rst)
begin
  if rst = '0' then
    output0 <= (others => '0');
  else
    output0 <= input0;
  end if;
end process;
end behavioral;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_signed.all;
use work.fixed_pkg.all;

entity ANDL is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   input1  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end ANDL;
architecture behavioral of ANDL is
begin
output0  <=  resize(input0 and input1,msb,lsb);
end behavioral;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_signed.all;
use work.fixed_pkg.all;

entity ADD is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   input1  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end ADD;
architecture behavioral of ADD is
begin
output0  <=  resize(input0 + input1,msb,lsb);
end behavioral;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_signed.all;
use work.fixed_pkg.all;

entity DELAY is
generic (
    delay   : integer;
    msb     : integer;
    lsb     : integer);
port (
    ws      : in std_logic;
    input0  : in  sfixed(msb downto lsb);
    output0 : out sfixed(msb downto lsb));
end DELAY;
architecture behavioral of DELAY is
type mem is array (delay-1 downto 0) of sfixed(msb downto lsb);
signal ligne : mem;
begin
process(ws)
    begin
    ligne(0) <= input0;
    if rising_edge(ws) then
        for i in 1 to delay-1 loop
            ligne(i) <= ligne(i-1);
        end loop;
    output0 <= ligne(delay-1);
    end if;
end process;
end behavioral;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_signed.all;
use work.fixed_pkg.all;

entity IntCast is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end IntCast;
architecture behavioral of IntCast is
begin
process (clk,rst)
begin
  if rst = '0' then
    output0 <= (others => '0');
  else
    output0 <= input0;
  end if;
end process;
end behavioral;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_signed.all;
use work.fixed_pkg.all;

entity DELAY0 is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end DELAY0;
architecture behavioral of DELAY0 is
begin
process (clk,rst)
begin
  if rst = '0' then
    output0 <= (others => '0');
  else
    output0 <= input0;
  end if;
end process;
end behavioral;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_signed.all;
use work.fixed_pkg.all;

entity FAUST is
port (
  ws : in std_logic;
  ap_clk : in std_logic;
  ap_rst_n : in std_logic;
  ap_start : in std_logic;
  ap_done : out std_logic;
  bypass_dsp : in std_logic;
  bypass_faust : in std_logic;
  in_left_V : in std_logic_vector (23 downto 0);
  in_right_V : in std_logic_vector (23 downto 0);
  out_left_V_ap_vld : out std_logic;
  out_right_V_ap_vld : out std_logic;
  out_left_V : out std_logic_vector (23 downto 0);
  out_right_V : out std_logic_vector (23 downto 0));
end FAUST;
architecture logic of FAUST is

signal    in_left_V_buf   : std_logic_vector (23 downto 0);
signal    in_left_fixed   : sfixed(23 downto 0);
signal    in_right_V_buf  :  std_logic_vector (23 downto 0);
signal    out_left_V_int  : std_logic_vector (23 downto 0);
signal    out_left_fixed  : sfixed(23 downto 0);
signal    out_right_V_int :  std_logic_vector (23 downto 0);
signal    step_cnt  : integer;
signal    sigoutput : sfixed(23 downto 0);

signal    sig0x55ae7c627ae0 : sfixed(1 downto -22);
signal    sig0x55ae7c621f20 : sfixed(1 downto -22);
signal    sig0x55ae7c626ed0 : sfixed(1 downto -22);
signal    sig0x55ae7c626c40 : sfixed(1 downto -22);
signal    sig0x55ae7c626ad0 : sfixed(1 downto -22);
signal    sig0x55ae7c612a20 : sfixed(1 downto -22) := to_sfixed(1,1,-22);
signal    sig0x55ae7c61d8d0 : sfixed(1 downto -22) := to_sfixed(15,1,-22);
signal    sig0x55ae7c623850 : sfixed(1 downto -22);
signal    sig0x55ae7c623760 : sfixed(1 downto -22);
signal    sig0x55ae7c622e50 : sfixed(1 downto -22);
signal    sig0x55ae7c627630 : sfixed(1 downto -22);
signal    sig0x55ae7c627480 : sfixed(1 downto -22);
signal    sig0x55ae7c627350 : sfixed(1 downto -22);
signal    sig0x55ae7c613190 : sfixed(1 downto -22) := to_sfixed(3,1,-22);
signal    sig0x55ae7c612390 : sfixed(1 downto -22) := to_sfixed(0,1,-22);

component DELAYVAR is
generic (
    mxd      : integer;
    msb      : integer;
    lsb      : integer);
port (
   ws        : in  std_logic;
   rst_n     : in  std_logic;
   delay_var : in  sfixed(msb downto lsb);
   input0    : in  sfixed(msb downto lsb);
   output0   : out sfixed(msb downto lsb));
end component;

component PROJ is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end component;

component ANDL is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   input1  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end component;

component ADD is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   input1  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end component;

component DELAY is
generic (
    delay    : integer;
    msb      : integer;
    lsb      : integer);
port (
    ws      : in std_logic;
    input0  : in  sfixed(msb downto lsb);
    output0 : out sfixed(msb downto lsb));
end component;

component IntCast is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end component;

component DELAY0 is
generic (
    msb     : integer;
    lsb     : integer);
port (
   clk     : in std_logic;
   rst     : in std_logic;
   input0  : in  sfixed(msb downto lsb);
   output0 : out sfixed(msb downto lsb));
end component;


begin

 process(ap_clk, ap_rst_n, ap_start)
   variable clock_cnt : integer := 0;
   variable date_ap_vld1 : integer := 3;
 begin

   if(ap_rst_n = '0') then
     step_cnt <= 0;
     clock_cnt := 0;
     ap_done <= '0';
     out_left_V   <= (others => '0');
     out_left_V_ap_vld   <= '0';
     out_right_V  <= (others => '0');
     out_right_V_ap_vld <=   '0' ;
   elsif(ap_clk'event and ap_clk = '1') then
     if (ap_start = '1') then
       clock_cnt := 0;
     end if;
     -- loading (buffering) input data
     if (clock_cnt = 1) then
       --step_cnt <= step_cnt + 1;
       in_left_V_buf <= in_left_V;
       in_right_V_buf <= in_right_V;
     end if;
     clock_cnt := clock_cnt+1;
     -- Say faust left output is ready
     if (clock_cnt >= 2) and (clock_cnt < 3)  then
       out_left_V_ap_vld <= '1';
       out_left_V <= out_left_V_int;
       out_right_V_ap_vld <= '1';
       out_right_V <=  out_right_V_int;
       ap_done <= '1';
     else
       ap_done <= '0';
       out_right_V_ap_vld <= '0';
       out_left_V_ap_vld <= '0';
     end if;
   end if;
 end process;
 ------------------------------------------------------------------------
 --------------   Data flow equation          ---------------------------
 ------------------------------------------------------------------------



DELAYVAR_0x55ae7c627ae0 : DELAYVAR
generic map (
    mxd => 3,
    msb => 1,
    lsb => -22)
port map (
    ws => ws,
    rst_n => ap_rst_n,
    delay_var => sig0x55ae7c623850,
    input0  => sig0x55ae7c621f20,
    output0 => sig0x55ae7c627ae0);

PROJ_0x55ae7c621f20 : PROJ
generic map (
    msb => 1,
    lsb => -22)
port map (
    clk => ap_clk,
    rst => ap_rst_n,
    input0  => sig0x55ae7c626ed0,
    output0 => sig0x55ae7c621f20);

ANDL_0x55ae7c626ed0 : ANDL
generic map (
    msb => 1,
    lsb => -22)
port map (
    clk => ap_clk,
    rst => ap_rst_n,
    input0  => sig0x55ae7c626c40,
    input1  => sig0x55ae7c61d8d0,
    output0 => sig0x55ae7c626ed0);

ADD_0x55ae7c626c40 : ADD
generic map (
    msb => 1,
    lsb => -22)
port map (
    clk => ap_clk,
    rst => ap_rst_n,
    input0  => sig0x55ae7c626ad0,
    input1  => sig0x55ae7c612a20,
    output0 => sig0x55ae7c626c40);

DELAY_0x55ae7c626ad0 : DELAY
generic map (
    delay => 1,
    msb => 1,
    lsb => -22)
port map (
    ws => ws,
    input0  => sig0x55ae7c621f20,
    output0 => sig0x55ae7c626ad0);

IntCast_0x55ae7c623850 : IntCast
generic map (
    msb => 1,
    lsb => -22)
port map (
    clk => ap_clk,
    rst => ap_rst_n,
    input0  => sig0x55ae7c623760,
    output0 => sig0x55ae7c623850);

DELAY0_0x55ae7c623760 : DELAY0
generic map (
    msb => 1,
    lsb => -22)
port map (
    clk => ap_clk,
    rst => ap_rst_n,
    input0  => sig0x55ae7c622e50,
    output0 => sig0x55ae7c623760);

PROJ_0x55ae7c622e50 : PROJ
generic map (
    msb => 1,
    lsb => -22)
port map (
    clk => ap_clk,
    rst => ap_rst_n,
    input0  => sig0x55ae7c627630,
    output0 => sig0x55ae7c622e50);

ANDL_0x55ae7c627630 : ANDL
generic map (
    msb => 1,
    lsb => -22)
port map (
    clk => ap_clk,
    rst => ap_rst_n,
    input0  => sig0x55ae7c627480,
    input1  => sig0x55ae7c613190,
    output0 => sig0x55ae7c627630);

ADD_0x55ae7c627480 : ADD
generic map (
    msb => 1,
    lsb => -22)
port map (
    clk => ap_clk,
    rst => ap_rst_n,
    input0  => sig0x55ae7c627350,
    input1  => sig0x55ae7c612a20,
    output0 => sig0x55ae7c627480);

DELAY_0x55ae7c627350 : DELAY
generic map (
    delay => 1,
    msb => 1,
    lsb => -22)
port map (
    ws => ws,
    input0  => sig0x55ae7c622e50,
    output0 => sig0x55ae7c627350);


sigoutput <= resize(sig0x55ae7c627ae0,0,-23);
out_left_V_int <= to_slv(sigoutput);

out_right_V_int <= to_slv(sigoutput);

end logic;
