------------------------------------------------------------------------------
-- Authors: Adeyemi Gbadamosi, Tanguy Risset                                  
-- Copyright Insa-Lyon/Inria, 2019--
-- Begin Date: 1/01/2019
-- Revision History  Date            Author        Comments
--                  
--
-------------------------------------------------------------------------
-- Purpose:
-- This architecture serves two purposes, it helps in debouncing a pushbutton 
-- ensures that only 1 pulse is read from the press of a button. 
---------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.all;
use IEEE.STD_LOGIC_UNSIGNED.all;

entity debounce is

  port (pb  : in  std_logic;
        clk : in  std_logic;
        q   : out std_logic := '0'
        );
end entity;

architecture rtl of debounce is

  signal ff0, ff1, ff2 : std_logic;
  signal count         : std_logic := '0';
  signal counter       : integer   := 0;
  signal enable        : std_logic;

begin

  count <= ff0 xor ff1;  ----detect a change in the values of the flipflops
  process(clk)
  begin
-------shifting the values from the input through the flipflops 
    if rising_edge(clk) then
      ff2 <= ff1;
      ff1 <= ff0;
      ff0 <= pb;
    end if;
  end process;

  process(pb, clk, counter, ff2)
  begin
    if rising_edge(clk) then
      if counter = 6000 then
        counter <= 0;
        q       <=ff2;  -----release the value of flipflop2 to the output in one pulse
      elsif enable = '1' then           --------activate counter
        counter <= counter+1;
      else
        counter <= counter;
        q       <='0';
      end if;
    end if;
  end process;

  process(counter, count, clk)
  begin
    if rising_edge(clk) then
      if count = '1' then               ------change detected in the flipflops
        enable <= '1';
      elsif counter = 6000 then         ---resets the value of the enable
        enable <= '0';
      else
        enable <= enable;
      end if;
    end if;
  end process;

end architecture;
