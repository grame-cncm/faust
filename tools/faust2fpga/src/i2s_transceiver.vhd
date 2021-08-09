--------------------------------------------------------------------------------
--
--   FileName:         i2s_transceiver.vhd
--   Dependencies:     none
--   Design Software:  Quartus Prime Version 17.0.0 Build 595 SJ Lite Edition
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
--   Version 1.0 03/29/2019 Scott Larson
--     Initial Public Release
-- 
--------------------------------------------------------------------------------
-------------------------------------------------------------------- 
-- Authors: Adeyemi Gbadamosi, Tanguy Risset
-- Begin Date: 1/01/2019
-- version adapted to Syfala from
-- DigiKey logic eewiki
-- https://www.digikey.com/eewiki/pages/viewpage.action?pageId=10125324
-------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity i2s_transceiver is
  generic(
    mclk_sclk_ratio : integer := 4;   --number of mclk periods per sclk period
                                      -- -> OK on digilent logic analyseur
    sclk_ws_ratio   : integer := 64;  --number of sclk periods per word select period
    d_width         : integer := 24);   --data width
  port(
    sys_clk       : in  std_logic;  -- sys_clk (FPGA) 120 MHz
    mclk       : in  std_logic;     -- mclk 12.88 MHZ
    reset_n   : in  std_logic;          --asynchronous active low reset
    start     : in  std_logic;
    sclk      : out std_logic;          --serial clock (or bit clock)
    ws        : out std_logic;          --word select (or left-right clock)
    sd_tx     : out std_logic;          --serial data transmit
    sd_rx     : in  std_logic;          --serial data receive
    rdy       : out  std_logic;          
    ap_done             : in  std_logic;  -- faust computation finished    
    out_left_V_ap_vld   : in  std_logic;  -- left data from Faust ready  
    out_right_V_ap_vld  : in  std_logic;  -- right data from Faust ready       
    l_data_tx : in  std_logic_vector(d_width-1 downto 0);  --left channel data to transmit
    r_data_tx : in  std_logic_vector(d_width-1 downto 0);  --right channel data to transmit
    l_data_rx : out std_logic_vector(d_width-1 downto 0);  --left channel data received
    r_data_rx : out std_logic_vector(d_width-1 downto 0));  --right channel data received
end i2s_transceiver;

architecture logic of i2s_transceiver is


  signal sclk_int      : std_logic := '0';  --internal serial clock signal
  signal ws_int        : std_logic := '0';  --internal word select signal
  signal ap_done_reg        : std_logic := '0'; --internal word select signal
  signal  out_left_V_ap_vld_reg   : std_logic; --left data from Faust ready  
  signal  out_right_V_ap_vld_reg  : std_logic; --right data from Faust ready   
  signal faust_finished        : std_logic := '0';  --internal word select signa
  signal faust_finished_latched_mclk    : std_logic := '0';  
  signal l_data_rx_int : std_logic_vector(d_width-1 downto 0);  --internal left channel rx data buffer
  signal r_data_rx_int : std_logic_vector(d_width-1 downto 0);  --internal right channel rx data buffer
  signal l_data_tx_int : std_logic_vector(d_width-1 downto 0);  --internal left channel tx data buffer
  signal r_data_tx_int : std_logic_vector(d_width-1 downto 0);  --internal right channel tx data buffer
  signal l_data_tx_latched : std_logic_vector(d_width-1 downto 0);  --internal left channel tx data buffer
  signal r_data_tx_latched : std_logic_vector(d_width-1 downto 0);  --internal right channel tx data buffer
  signal rdy1 : std_logic:= '0';  -- shall trigger ap_start
  signal rdy1_reg : std_logic:= '0';  --internal right channel tx data buffer

begin
  process(sys_clk, reset_n)
  begin
    if(reset_n = '0') then              --asynchronous reset
      ap_done_reg <= '0';               
      out_left_V_ap_vld_reg <= '0';
      out_right_V_ap_vld_reg <= '0';
      rdy           <= '0';
    elsif(sys_clk'event and sys_clk = '1')  then  --system clock rising
      -- detect ap_done rising edge. At the moment we do not use it
      ap_done_reg <= ap_done;
      if (ap_done = '1') and (ap_done_reg /= ap_done) then
        -- do nothing right now
        -- r_data_tx_latched <= r_data_tx; 
        -- l_data_tx_latched <= l_data_tx;
      end if;
      -- latch left input from faust (at any sys_clk cycle) 
      out_left_V_ap_vld_reg <= out_left_V_ap_vld;
      if (out_left_V_ap_vld = '1') and
        (out_left_V_ap_vld_reg /= out_left_V_ap_vld) then
        l_data_tx_latched <= l_data_tx;
      end if;
      -- latch left input from faust (at any sys_clk cycle) 
      out_right_V_ap_vld_reg <= out_right_V_ap_vld;
      if (out_right_V_ap_vld = '1') and
        (out_right_V_ap_vld_reg /= out_right_V_ap_vld) then
        r_data_tx_latched <= r_data_tx;
      end if;

      -- rdy detect rising edge of rdy1 (clocked on sys_clk)
      rdy1_reg <= rdy1;
      if (rdy1 = '1') and (rdy1_reg /= rdy1) then
        rdy <= '1';
        assert false
          report "setting ap_start to 1"
          severity NOTE;
      else
        rdy <= '0';
      end if;
    end if;   
  end process;
  
  process(mclk, reset_n)
    variable sclk_cnt : integer := 0;  --counter of master clocks during half period of serial clock
    variable ws_cnt   : integer := 0;  --counter of serial clock toggles during half period of word select
  begin

    if(reset_n = '0') then              --asynchronous reset
      sclk_cnt      := 0;               --clear mclk/sclk counter
      ws_cnt        := 0;               --clear sclk/ws counter
      sclk_int      <= '0';             --clear serial clock signal
      ws_int        <= '0';             --clear word select signal
      l_data_rx_int <= (others => '0');  --clear internal left channel rx data buffer
      r_data_rx_int <= (others => '0');  --clear internal right channel rx data buffer
      l_data_tx_int <= (others => '0');  --clear internal left channel tx data buffer
      r_data_tx_int <= (others => '0');  --clear internal right channel tx data buffer
      sd_tx         <= '0';             --clear serial data transmit output
      l_data_rx     <= (others => '0');  --clear left channel received data output
      r_data_rx     <= (others => '0');  --clear right channel received data output
    elsif(mclk'event and mclk = '1') and start = '1' then  --master clock rising edge
      -- build sclk (= 4x mclk)
      if(sclk_cnt < mclk_sclk_ratio/2-1) then  --less than half period of sclk
                                               --didn't understand but works fine
        sclk_cnt := sclk_cnt + 1;       --increment mclk/sclk counter
      else                              --half period of sclk
        sclk_cnt := 0;                  --reset mclk/sclk counter
        sclk_int <= not sclk_int;       --toggle serial clock
        if(ws_cnt < sclk_ws_ratio-1) then  --less than half period of ws
          ws_cnt := ws_cnt + 1;         --increment sclk/ws counter
          -- "beguinning" of faust computation x ws is '1' 
          if (ws_cnt = 1) and (ws_int = '1') then
            rdy1 <= '1';
          else
            rdy1 <= '0';
          end if;
          -- regular i2q process
          if(sclk_int = '0' and ws_cnt > 1 and ws_cnt < d_width*2+2) then  --rising edge of sclk during data word
            if(ws_int = '1') then       --right channel
              r_data_rx_int <= r_data_rx_int(d_width-2 downto 0) & sd_rx;  --shift data bit into right channel rx data buffer
            else                        --left channel
              l_data_rx_int <= l_data_rx_int(d_width-2 downto 0) & sd_rx;  --shift data bit into left channel rx data buffer
            end if;
          end if;
          if(sclk_int = '1' and ws_cnt > 1 and ws_cnt < d_width*2+3) then  --falling edge of sclk during data word
            if(ws_int = '1') then       --right channel
              sd_tx         <= r_data_tx_int(d_width-1);  --transmit serial data bit
              r_data_tx_int <= r_data_tx_int(d_width-2 downto 0) & '0';  --shift data of right channel tx data buffer
            else                        --left channel
              sd_tx         <= l_data_tx_int(d_width-1);  --transmit serial data bit
              l_data_tx_int <= l_data_tx_int(d_width-2 downto 0) & '0';  --shift data of left channel tx data buffer
            end if;
          end if; 
        else                            --half period of ws: ws_cnt = sclk_ws_ratio-1
          ws_cnt        := 0;           --reset sclk/ws counter
          ws_int        <= not ws_int;  --toggle word select
          if (ws_int = '1') then
            r_data_rx     <= r_data_rx_int;  --output right channel received data
            l_data_rx     <= l_data_rx_int;  --output left channel received data
          end if;
          if (ws_int = '0') then
            r_data_tx_int <= r_data_tx_latched;    --latch in right channel data to transmit
          else
            l_data_tx_int <= l_data_tx_latched;    --latch left channel data to transmit
          end if;     
        end if; 
      end if;
    end if;
  end process;

  sclk <= sclk_int;                     --output serial clock
  ws   <= ws_int;                       --output word select

end logic;
