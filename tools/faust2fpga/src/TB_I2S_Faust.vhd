--------------------------------------------------------------------------------
--
--   FileName:         test_bench_i2s.vhd
-------------------------------------------------------------------- 
-- Authors:, Tanguy Risset
-- Begin Date: 7/04/2019
-- Testbench for modified version of 
-- DigiKey logic eewiki
-- https://www.digikey.com/eewiki/pages/viewpage.action?pageId=10125324
-------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use STD.textio.all;
use ieee.std_logic_textio.all;

entity TB_I2S_Faust is
  generic(
    mclk_sclk_ratio : integer := 4;   --number of mclk periods per sclk period
                                      -- -> OK on digilent logic analyseur
    sclk_ws_ratio   : integer := 64;  --number of sclk periods per word select period
    d_width         : integer := 24);   --data width
  port(
    sys_clk       : in  std_logic;  -- sys_clk (FPGA) 120 MHz
    reset_n    : out  std_logic;          --asynchronous active low reset
    reset      : in  std_logic;          --asynchronous active low reset
    ap_start   : in  std_logic;          --asynchronous active low reset
    start   : out  std_logic;          --asynchronous active low reset
    sd_tx     : in std_logic;          --serial data transmit
    sd_rx     : out  std_logic          --serial data receive
    );
end TB_I2S_Faust ;


architecture logic of TB_I2S_Faust is
  
-----------------------------------------------------------------------------
  -- Testbench Internal Signals
  -----------------------------------------------------------------------------
  file file_VECTORS : text;


  signal    ap_idle :  STD_LOGIC;
  signal    l_i2s_to_faust : STD_LOGIC_VECTOR (23 downto 0);
  signal    r_i2s_to_faust :  STD_LOGIC_VECTOR (23 downto 0);
  signal    out_right_V_ap_vld :  STD_LOGIC;
  signal    out_left_V_ap_vld :  STD_LOGIC;

  signal sclk     : std_logic;          
  signal ws        : std_logic;          --word select (or left-right clock)
  signal mclk      :  std_logic := '0';
  signal l_faust_to_i2s : std_logic_vector(23 downto 0);
  signal r_faust_to_i2s : std_logic_vector(23 downto 0);

  
begin

  
  process(sys_clk,  reset)
    variable step : integer :=0;
    variable clock_cnt : integer :=0;

  begin

    if(reset = '1') then 
      ap_idle <='0';
    elsif(sys_clk'event and sys_clk = '1') then
      clock_cnt := clock_cnt + 1;
      --emulating faust result at 200 cycles 

      if (ap_start = '1') then
        clock_cnt := 0;
      else
        clock_cnt := clock_cnt + 1;
      end if;
      -- trick to send what we received
       sd_rx <= sd_tx;
      --sd_rx <= '0';
    end if;     
  end process;  

  ----------------------------------------------------------------
  -- process to emulate sd_rx comming from ssd
  -- -------------------------------------------------------------
  
  ---------------------------------------------------------------------------
  -- This procedure reads the file input_vectors.txt which is located in the
  -- simulation project area.
  -- It will read the data in and send it to the ripple-adder component
  -- to perform the operations.  The result is written to the
  -- output_results.txt file, located in the same directory.
  ---------------------------------------------------------------------------
  -- process
  --   variable v_ILINE     : line;
  --   variable sample_read : std_logic_vector(23 downto 0);
  --   --variable v_SPACE     : character;
     
  -- begin
  --   wait for 20 ns;
    
  --    file_open(file_VECTORS, "./input_samples.txt",  read_mode);
 
  --   while not endfile(file_VECTORS) loop
  --     readline(file_VECTORS,v_ILINE);
  --     -- read(v_ILINE, sample_read);
  --     -- in_left_V_int  <= sample_read;
  --     -- in_right_V_int <= sample_read;
  --     -- new_sample <= '1';
  --     -- wait for 8 ns;
  --     -- new_sample <= '0';
      
  --     wait for 20.8 us;
 
  --   end loop;
 
  --   file_close(file_VECTORS);
     
  --   wait;
  -- end process;

  ------------------------------------------------------------------------
  --------------   Data flow equation          ---------------------------
  ------------------------------------------------------------------------

  --sys_clk 120 Mhz 
  start <= '1' ;
  reset_n <= not reset ;

end architecture logic ;
