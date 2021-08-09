--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
--Date        : Mon May  4 20:06:12 2020
--Host        : bata running 64-bit Ubuntu 18.04.3 LTS
--Command     : generate_target main_wrapper.bd
--Design      : main_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity main_wrapper is
  port (
    ack_error : out STD_LOGIC;
    bclk : out STD_LOGIC;
    bclkpmod : out STD_LOGIC;
    bypass_analog : in STD_LOGIC;
    bypass_dsp : in STD_LOGIC;
    bypass_faust : in STD_LOGIC;
    in_mute : in STD_LOGIC;
    mclk : out STD_LOGIC;
    mclkpmod : out STD_LOGIC;
    out_mute : out STD_LOGIC;
    reset_btn : in STD_LOGIC;
    sclk : inout STD_LOGIC;
    sclpmod : out STD_LOGIC;
    sd_rx : in STD_LOGIC;
    sd_rxpmod : out STD_LOGIC;
    sd_tx : out STD_LOGIC;
    sd_txpmod : out STD_LOGIC;
    sdapmod : out STD_LOGIC;
    sdin : inout STD_LOGIC;
    sys_clk : in STD_LOGIC;
    vol_down : in STD_LOGIC;
    vol_up : in STD_LOGIC;
    ws_rx : out STD_LOGIC;
    ws_tx : out STD_LOGIC;
    wspmod : out STD_LOGIC
  );
end main_wrapper;

architecture STRUCTURE of main_wrapper is
  component main is
  port (
    ack_error : out STD_LOGIC;
    bclk : out STD_LOGIC;
    bclkpmod : out STD_LOGIC;
    bypass_analog : in STD_LOGIC;
    bypass_dsp : in STD_LOGIC;
    bypass_faust : in STD_LOGIC;
    mclk : out STD_LOGIC;
    mclkpmod : out STD_LOGIC;
    reset_btn : in STD_LOGIC;
    sclk : inout STD_LOGIC;
    sclpmod : out STD_LOGIC;
    sd_rx : in STD_LOGIC;
    sd_rxpmod : out STD_LOGIC;
    sd_tx : out STD_LOGIC;
    sd_txpmod : out STD_LOGIC;
    sdapmod : out STD_LOGIC;
    sdin : inout STD_LOGIC;
    sys_clk : in STD_LOGIC;
    vol_down : in STD_LOGIC;
    vol_up : in STD_LOGIC;
    ws_rx : out STD_LOGIC;
    ws_tx : out STD_LOGIC;
    wspmod : out STD_LOGIC;
    in_mute : in STD_LOGIC;
    out_mute : out STD_LOGIC
  );
  end component main;
begin
main_i: component main
     port map (
      ack_error => ack_error,
      bclk => bclk,
      bclkpmod => bclkpmod,
      bypass_analog => bypass_analog,
      bypass_dsp => bypass_dsp,
      bypass_faust => bypass_faust,
      in_mute => in_mute,
      mclk => mclk,
      mclkpmod => mclkpmod,
      out_mute => out_mute,
      reset_btn => reset_btn,
      sclk => sclk,
      sclpmod => sclpmod,
      sd_rx => sd_rx,
      sd_rxpmod => sd_rxpmod,
      sd_tx => sd_tx,
      sd_txpmod => sd_txpmod,
      sdapmod => sdapmod,
      sdin => sdin,
      sys_clk => sys_clk,
      vol_down => vol_down,
      vol_up => vol_up,
      ws_rx => ws_rx,
      ws_tx => ws_tx,
      wspmod => wspmod
    );
end STRUCTURE;
