-------------------------------------------------------------------------------
--
--   FileName:         i2c_master.vhd
--   Dependencies:     none
--   Design Software:  Quartus II 64-bit Version 13.1 Build 162 SJ Full Version
--
--   HDL CODE IS PROVIDED "AS IS."  DIGI-KEY EXPRESSLY DISCLAIMS ANY
--   WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
--   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
--   PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL DIGI-KEY
--   BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
--   DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
--   PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
--   BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
--   ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
--
--   Version History
--   Version 1.0 11/01/2012 Scott Larson
--     Initial Public Release
--   Version 2.0 06/20/2014 Scott Larson
--     Added ability to interface with different slaves in the same transaction
--     Corrected ack_error bug where ack_error went 'Z' instead of '1' on error
--     Corrected timing of when ack_error signal clears
--   Version 2.1 10/21/2014 Scott Larson
--     Replaced gated clock with clock enable
--     Adjusted timing of SCL during start and stop conditions
--   Version 2.2 02/05/2015 Scott Larson
--     Corrected small SDA glitch introduced in version 2.1
-------------------------------------------------------------------- 
-------------------------------------------------------------------- 
-- Authors: Adeyemi Gbadamosi, Tanguy Risset
-- Begin Date: 1/01/2019
-- version adapted to Syfala from
-- DigiKey logic eewiki
-- https://www.digikey.com/eewiki/pages/viewpage.action?pageId=10125324
-------------------------------------------------------------------------
-- Purpose:
-- This entity/architecture pair is an I2C controler configuration block for
-- use with the SSM2603 audio chip present on the ZyboZ-7 Xilinx board.
-- The SSM2603 chip i2c control need a specific sequence of adressing
-- See SSM2603 datasheet p 17:
--
-- i2c sequences: (S=Start, A=Acknowledge (from slave), P=Stop
--  bits:     S 7 6 .... 1 0 A 15 14 ... 10 9 8 A 7 ... 1 0 A P
--  write seq:  |dev addr| 0   | reg addr   | |Reg data |
--
---------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity i2cemu is
  generic(
    input_clk : integer := 125_000_000;  --input clock speed from user logic in Hz
    bus_clk   : integer := 400_000);  --speed the i2c bus (scl) will run at in Hz
  port(
    clk           : in  std_logic;     --system clock
    reset_n       : in  std_logic;     --active low reset
    vol_up        : in  std_logic;  --pushbutton input for changing the DAC volume
    vol_down      : in  std_logic;  --pushbutton input for changing the DAC volume
    analog_bypass : in  std_logic;  --signals when the i2c PROCESS is finished
    ack_error     : out std_logic;  --flag IF improper acknowledge from slave
    done          : out std_logic;  --signals when the i2c PROCESS is finished
    sdin          : inout std_logic;     --serial data output of i2c bus
    sclk          : inout std_logic;    --serial clock output of i2c bus
    sdinpmod      : out std_logic;    --serial data output of i2c bus to be
                                      --sent to pmod
    sclkpmod      : out std_logic);   --serial clock output of i2c bus to be
                                      --sent to pmod
end i2cemu;

architecture logic of i2cemu is
  --divider will allow to build 400kHz clocks for scl and data_clock
  constant divider     : integer                       := (input_clk/bus_clk)/4;  --number of clocks in 1/4 cycle of scl

  -- I2C R/W state machine
  type machine is(ready, start, command, slv_ack1, wr, wr2, slv_ack2, slv_ack3, delay, stop);  --needed states
  signal state         : machine;       --state machine
  signal data_clk      : std_logic;     --data clock forsdina
  signal data_clk_prev : std_logic;  --data clock during previous system clock
  signal scl_clk       : std_logic;     --constantly running internal scl
  signal scl_ena       : std_logic                     := '0';  --enables internal scl to output
  signal sda_int       : std_logic                     := '1';  --internal sda
  signal sda_ena_n     : std_logic;     --enables internal sda to output
  signal stopi2c       : std_logic                     := '0';  --unlatch the i2c PROCESS AND makes it idle
  -----SIGNALS FOR CHANGING THE DAC VOLUME
  signal inc_vol       : std_logic;  -------------------volume increase signal from the debounce
  signal dec_vol       : std_logic;  -------------------volume decrease signal from the debounce
  signal dirty         : std_logic                     := '0';  --unlatch the i2c PROCESS AND makes it idle
  signal analog_dirty         : std_logic                     := '0';  --unlatch the i2c PROCESS AND makes it idle
  signal volume_dirty         : std_logic                     := '0';  --unlatch the i2c PROCESS AND makes it idle
  signal volume        : std_logic_vector(7 downto 0)  := "00010111";
  signal analog_path   : std_logic_vector(7 downto 0)  := "00001010";
  signal addr          : std_logic_vector(6 downto 0)  := "0011010";  --SSM2603 chip address
  signal delaycount    : std_logic_vector(14 downto 0) := "000000000000000";  ----- 75ms delay before activating the audio chip
  signal regaddress    : std_logic_vector(7 downto 0);  --address of the register to be configured
  signal regdata       : std_logic_vector(7 downto 0);  --data to be sent to the register
  signal addr_rw       : std_logic_vector(7 downto 0);  --latched in address AND read/write
  signal bit_cnt       : integer range 0 to 7          := 7;  --tracks bit number in transaction
  signal wait_ack      : std_logic                     := '0';  --identIFies IF slave is stretching scl
  signal count1        : integer                       := 0;  --used to keep track of the register being configured
  signal counter       : integer                       := 0;
  signal sdin_s        : std_logic := '0';
  signal sclk_s        : std_logic := '0';
  signal last_analog_bypass : std_logic := '0';

  component debounce is
    port (pb  : in  std_logic;
          clk : in  std_logic;
          q   : out std_logic
          );
  end component;


begin
  increment_volume : debounce
    port map(
      pb  => vol_up,
      clk => clk,
      q   => inc_vol
      );
  decrement_volume : debounce
    port map(
      pb  => vol_down,
      clk => clk,
      q   => dec_vol
      );

  -- copy for pmod debugging
  process(clk)
  begin
    if rising_edge(clk) then
        sclkpmod<=sclk_s;
        sdinpmod<=sdin_s;
    end if;
  end process;

  --generate the timing for the bus clock (scl_clk) AND the data clock (data_clk)
  ----------------------------------------------------------------------------
  -- i2c_clocks_gen process: generate the clocks used for i2c bus (scl_clk) and
  -- i2c data clock (data_clk). scl_clk and data_clk are shifted from 1/4 of T,
  -- T being the number of input clock between two i2c buc_clk:
  -- (T=input_clk/bus_clk)
  -- data_clk is used to set up the data so that it is stable when it is
  -- sampled along with scl_clk
  -- time         0 ................................ |4*divider
  -- data_clk     | ________----------------________ |
  -- scl_clk      | ________________---------------- |
  ----------------------------------------------------------------------------
  process(clk, reset_n)
    variable count : integer range 0 to divider*4;  --timing for clock generation
  begin
    if(reset_n = '0') then              --reset asserted
      wait_ack <= '0';
      count    := 0;
    elsif(clk'event and clk = '1') then
      data_clk_prev <= data_clk;  --store data clock  at previous clk cycle
      if (count = divider*4-1) then
        -- End of cycle: reset timer
        count := 0;
      elsif (wait_ack = '0') then
        -- if Ack is OK, count
        count := count + 1;
      end if;
      -- build data_clk and scl_clk
      case count is
        when 0 to divider-1 =>
          --first 1/4 cycle of clocking
          scl_clk  <= '0';
          data_clk <= '0';
        when divider to divider*2-1 =>
          --second 1/4 cycle of clocking
          scl_clk  <= '0';
          data_clk <= '1';
        when divider*2 to divider*3-1 =>
          --third 1/4 cycle of clocking
          scl_clk <= '1';
          if(sclk_s = '0') then
            --  if slave does not Acknowledge, it forces scl to 0
            -- then we enter in a "wait_ack" phase
            wait_ack <= '1';
          else
            wait_ack <= '0';
          end if;
          data_clk <= '1';
        when others =>
          --last 1/4 cycle of clocking
          scl_clk  <= '1';
          data_clk <= '0';
      end case;
    end if;
  end process;

  ----------------------------------------------------------------------------
  -- state_machine process:
  -- i2c state machine
  -- Writing bit to sda when scl is low (data_clk rising edge)
  ----------------------------------------------------------------------------
  process(clk, reset_n)
    -----------------procedure for sending the bits over the sda line-------------------
    procedure decrementbit(  -- SIGNAL   bitcnt        : inout  INTEGER;      --tracks bit number in transaction
      signal datatosEND  : in  std_logic_vector(7 downto 0);
      nextstate          :     machine;
      variable byte_sent : out boolean) is
    begin
      if(bit_cnt = 0) then              --write byte transmit finished
        byte_sent := true;
        sda_int   <= '1';
        state     <= nextstate;
        bit_cnt   <= 7;
      else                              --next clock cycle of write state
        bit_cnt   <= bit_cnt - 1;       --keep track of transaction bits
        sda_int   <= datatosEND(bit_cnt-1);
        byte_sent := false;
      end if;
    end procedure;
    variable bytesent : boolean;  ---------------------------true after the data has been sent
  begin
    if(reset_n = '0') then              --reset asserted
      state     <= ready;               --return to initial state
      scl_ena   <= '0';                 --sets scl high impedance
      sda_int   <= '1';                 --sets sda high impedance
      ack_error <= '0';                 --clear acknowledge error flag
      count1    <= 0;  -------------------resets the register address and  data
      bit_cnt   <= 7;                   --restarts data bit counter
      stopi2c   <= '0';      ----------------------enables the i2c states
    elsif(clk'event and clk = '1') then
      if dirty = '1' then  --------------------detects a change in volume
        count1  <= 9;  ----------------sets the register to the volume registers
        stopi2c <= '0';      ------------------starts the i2c protocol
      end if;
      ----------------------------I2C STATE MACHINE--------------------------------
      if(data_clk = '1' and data_clk_prev = '0') then  --data clock rising edge
        case state is
          when ready =>                 --idle state
            if stopi2c = '0' then       --transaction requested
              addr_rw <= addr & '0';  --collect requested slave address AND command
              state   <= start;         --go to start bit
              done    <= '0';
            else                        --remain idle
              done  <= '1';
              state <= ready;           --remain idle
            end if;

          when start =>                 --start bit of transaction
            sda_int <= addr_rw(7);      --set first address bit to bus
            state   <= command;

          when command =>  --address AND command byte of transaction
            decrementbit(addr_rw, slv_ack1, bytesent);  ------------------sending the dsata over the sda line

          when slv_ack1 =>              --slave acknowledge bit (command)
            sda_int <= regaddress(7);   --write first bit of data
            state   <= wr;              --go to write byte

          when wr =>                    --write byte of transaction
            decrementbit(regaddress, slv_ack2, bytesent);  ------------------sending the dsata over the sda line

          when slv_ack2 =>              --slave acknowledge bit (write)
            sda_int <= regdata(7);
            state   <= wr2;

          when wr2 =>                   --write byte of transaction
            decrementbit(regdata, slv_ack3, bytesent);  ------------------sending the dsata over the sda line
            if bytesent = true then     --write byte transmit finished
              ----------------------------------------
              if count1 = 11 then
                count1 <= count1;
              else
                count1 <= count1 +1;
              end if;
            ----------------------------------------
            end if;

          when slv_ack3 =>              --slave acknowledge bit (command)
            sda_int <= '1';             --release sda from incoming data
            if count1 = 7 then
              state <= delay;
            elsif count1 = 11 then
              state <= stop;
            else
              state <= ready;
            end if;

          when delay =>
            if delaycount = "111010100001100" then
              delaycount <= "000000000000000";
              state      <= start;
            else
              delaycount <= delaycount + 1;
            end if;

          when stop =>                  --stop bit of transaction
            stopi2c <= '1';             --unflag busy
            state   <= ready;           --go to idle state
        end case;

      elsif(data_clk = '0' and data_clk_prev = '1') then  --data clock falling edge
        case state is
          when start =>
            if(scl_ena = '0') then      --starting new transaction
              scl_ena   <= '1';         --enable scl output
              ack_error <= '0';         --reset acknowledge error output
            end if;
          when slv_ack1 =>              --receiving slave acknowledge (command)
            if(sdin_s /= '0' ) then  --no-acknowledge or previous no-acknowledge
              ack_error <= '1';         --set error output IF no-acknowledge
            end if;
          when slv_ack2 =>              --receiving slave acknowledge (write)
            if(sdin_s /= '0' ) then  --no-acknowledge or previous no-acknowledge
              ack_error <= '1';         --set error output IF no-acknowledge
            end if;
          when delay =>
            scl_ena <= '0';
          when stop =>
            scl_ena <= '0';             --disable scl
          when others =>
            null;
        end case;
      end if;
    end if;
  end process;

  ------------------------------------------------------------------------
  --------------   Data flow equation          ---------------------------
  ------------------------------------------------------------------------

  ------------------------------------------------------------------------
  ----------- Select statement to implement start and stop condition -----
  ------------------------------------------------------------------------
  with state select
    sda_ena_n <=
    -- generate start condition: set sda to 0 while scl is 'Z'
    data_clk_prev     when start,
    -- generate stop condition: set sda to 1 while scl is 'Z'
    not data_clk_prev when stop,
    sda_int           when others;      --set sda to internal sda signal

  --set scl AND sda outputs these output need to be in High impedance state
  -- when they are not forced by the i2c controler on order to receive slave
  -- acknowledge
  sclk_s <= '0' when (scl_ena = '1' and scl_clk = '0') else '1';
  sdin_s <= '0' when sda_ena_n = '0'                   else '1';
  --sclk <= '0' when (scl_ena = '1' and scl_clk = '0') else '1';
  --sdin <= '0' when sda_ena_n = '0'                   else '1';
  sdin <= sdin_s;
  sclk <= sclk_s;

  with count1 select
    regaddress <= "00001100" when 0,  ----------------------------REGISTER R6 0X06 &'0'(eighth bit of the register data)
    "00000000"               when 1,  ----------------------------REGISTER R0 0X00 &'0'(eighth bit of the register data)
    "00000010"               when 2,  ----------------------------REGISTER R1 0X01 &'0'(eighth bit of the register data)
    "00001000"               when 3,  ----------------------------REGISTER R4 0X04 &'0'(eighth bit of the register data)
    "00001010"               when 4,  ----------------------------REGISTER R5 0X05 &'0'(eighth bit of the register data)
    "00001110"               when 5,  ----------------------------REGISTER R7 0X07 &'0'(eighth bit of the register data)
    "00010000"               when 6,  ----------------------------REGISTER R8 0X08 &'0'(eighth bit of the register data)
    ----------------------------------------------------75ms delay
    "00010010"               when 7,  ----------------------------REGISTER R9 0X09 &'0'(eighth bit of the register data)
    "00001100"               when 8,  ---------------------------REGISTER R6 0X06 &'0'(eighth bit of the register data)
    "00000100"               when 9,  ----------------------------REGISTER R2 0X02 &'0'(eighth bit of the register data)
    "00000110"               when 10,  ----------------------------REGISTER R3 0X03 &'0'(eighth bit of the register data)
    "00000000"               when others;
  with count1 select
    regdata <= "00110000" when 0,  ------------------------- REGISTER R6 (bit 7 downto 0)
    "00010111"            when 1,       ------------------------- REGISTER R0
    "00010111"            when 2,  ------------------------- REGISTER R1
    analog_path            when 3,       ------------------------- REGISTER R4
    "00000000"            when 4,       ------------------------- REGISTER R5
    "00001010"            when 5,  ------------------------- REGISTER R7
    "00000000"            when 6,       ------------------------- REGISTER R8
    ---------------------------------------------75ms delay
    "00000001"            when 7,       ------------------------- REGISTER R9
    "00100000"            when 8,       ------------------------ REGISTER R6
    volume                when 9,       ------------------------- REGISTER R2
    volume                when 10,      ------------------------- REGISTER R3
    "00000000"            when others;

  analog_path <= "00001010" when analog_bypass = '1' else "00010010";
  dirty <= analog_dirty or volume_dirty;

  process(analog_bypass, reset_n)
  begin
    if reset_n = '0' then
      analog_dirty <= '0';
      last_analog_bypass <= '0';
    elsif (analog_bypass /= last_analog_bypass) then
      analog_dirty <= '1';
      last_analog_bypass <= analog_bypass;
    else
      analog_dirty <= '0';
    end if;
  end process;

  process(clk, reset_n, vol_up, vol_down)
  begin
    if reset_n = '0' then
      volume       <= "01100000";
      volume_dirty <= '0';
    elsif rising_edge(clk) then
      ------increments the DAC volume
      if inc_vol = '1' then
        volume       <= volume+2;
        volume_dirty <= '1';
        counter      <= 0;
      ------------decrements the DAC volume
      elsif dec_vol = '1' then
        volume       <= volume-2;
        volume_dirty <= '1';
        counter      <= 0;
      else
        volume <= volume;
        if counter = 200 then
          counter      <= 0;
          volume_dirty <= '0';
        else
          counter <= counter + 1;
        end if;
      end if;
    end if;
  end process;


end logic;
