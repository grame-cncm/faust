/*******************************************************************************
I2C Configuration for a Wolfson WM8978 Audio Codec.
This file was written based on the information provided in the Codec Specs
and on the NuovotonDuino project: https://github.com/DFRobot/NuvotonDuino.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "WM8978.h"
#include "sys/types.h"
#include "driver/i2c.h"

static u16 WM8978_REGVAL_TBL[58]=
{
	0X0000,0X0000,0X0000,0X0000,0X0050,0X0000,0X0140,0X0000,
	0X0000,0X0000,0X0000,0X00FF,0X00FF,0X0000,0X0100,0X00FF,
	0X00FF,0X0000,0X012C,0X002C,0X002C,0X002C,0X002C,0X0000,
	0X0032,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,
	0X0038,0X000B,0X0032,0X0000,0X0008,0X000C,0X0093,0X00E9,
	0X0000,0X0000,0X0000,0X0000,0X0003,0X0010,0X0010,0X0100,
	0X0100,0X0002,0X0001,0X0001,0X0039,0X0039,0X0039,0X0039,
	0X0001,0X0001
}; 

// WM8978 init
u8 WM8978::init(void)
{
	initI2C();
	u8 res;
	res = writeReg(0,0);	// WM8978
	if(res) return 1;
	writeReg(1,0X1B);	// R1, MICEN (MIC), BIASEN, VMIDSEL[1:0]
	writeReg(2,0X1B0); // R2, ROUT1, LOUT1, BOOSTENR, BOOSTENL
	writeReg(3,0X6C);	// R3, LOUT2, ROUT2, RMIX, LMIX	
	writeReg(6,0); // R6, MCLK
	writeReg(43,1<<4); // R43, INVROUT2
	writeReg(47,1<<8); // R47, PGABOOSTL, MIC
	writeReg(48,1<<8); // R48, PGABOOSTR, MIC
	writeReg(49,1<<1); // R49, TSDEN
	writeReg(10,1<<3); // R10, SOFTMUTE
	writeReg(14,1<<3); // R14, ADC
	return 0;
}

// Initialize i2c for the ESP32
void WM8978::initI2C(void)
{
  i2c_port_t i2c_master_port = (i2c_port_t) I2C_MASTER_NUM;
  i2c_config_t conf;
  conf.mode = I2C_MODE_MASTER;
  conf.sda_io_num = (gpio_num_t) I2C_MASTER_SDA_IO;
  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf.scl_io_num = (gpio_num_t) I2C_MASTER_SCL_IO;
  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
  i2c_param_config(i2c_master_port, &conf);
	i2c_driver_install(i2c_master_port, conf.mode,
                              I2C_MASTER_RX_BUF_DISABLE,
                              I2C_MASTER_TX_BUF_DISABLE, 0);
}

// WM8978 register write
// reg: Register Address
// val: Register value
u8 WM8978::writeReg(u8 reg,u16 val)
{ 
	byte buf[2];
	buf[0] = (reg<<1)|((val>>8)&0X01);
	buf[1] = val&0XFF;
	
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (WM8978_ADDR << 1) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write(cmd, buf, 2, ACK_CHECK_EN);
  i2c_master_stop(cmd);
	i2c_master_cmd_begin((i2c_port_t) 1, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
	
	WM8978_REGVAL_TBL[reg] = val;
	return 0;	
}  

// WM8978 read register
// Reads the value of the local register buffer zone
// reg: Register Address
// Return Value: Register value
u16 WM8978::readReg(u8 reg)
{
  return WM8978_REGVAL_TBL[reg];	
} 

// WM8978 DAC/ADC
// adcen: adc 1/0
// dacen: dac 1/0
void WM8978::addaCfg(u8 dacen,u8 adcen)
{
	u16 regval;
	regval = readReg(3); // R3
	if(dacen)regval |= 3<<0; // R3 DACR & DACL
	else regval &= ~(3<<0); // R3 DACR & DACL
	writeReg(3,regval); // R3
	regval=readReg(2); // R2
	if(adcen)regval|=3<<0; // R2 ADCR & ADCL
	else regval&=~(3<<0); //R2 ADCR & ADCL
	writeReg(2,regval); // R2	
}

// WM8978 Input Config
// micen: MIC 1/0
// lineinen: Line In 1/0
// auxen: aux 1/0
void WM8978::inputCfg(u8 micen,u8 lineinen,u8 auxen)
{
	u16 regval;  
	regval = readReg(2); // R2
	if(micen) regval|=3<<2; // INPPGAENR, INPPGAENL (MIC/PGA)
	else regval&=~(3<<2);
 	writeReg(2,regval); // R2 
	
	regval=readReg(44); // R44
	if(micen) regval|=3<<4|3<<0; // LIN2INPPGA, LIP2INPGA, RIN2INPPGA, RIP2INPGA
	else regval&=~(3<<4|3<<0);
	writeReg(44,regval); // R44
	
	if(lineinen) lineinGain(5); // LINE IN 0dB
	else lineinGain(0);	
	if(auxen) auxGain(7); // AUX 6dB
	else auxGain(0);
}

// WM8978
// dacen: DAC 1/0 
// bpsen: Bypass (MIC, LINE IN,AUX) 1/0
void WM8978::outputCfg(u8 dacen,u8 bpsen)
{
	u16 regval = 0;
	if(dacen) regval|=1<<0; // DAC
	if(bpsen)
	{
		regval|=1<<1; // BYPASS
		regval|=5<<2; // 0dB
	} 
	writeReg(50,regval); // R50
	writeReg(51,regval); // R51 
}

// WM8978 MIC (BOOST 20dB,MIC-->ADC)
// gain: 0~63, -12dB~35.25dB, 0.75dB/Step
void WM8978::micGain(u8 gain)
{
	gain &= 0X3F;
	writeReg(45,gain); // R45,PGA
	writeReg(46,gain|1<<8);	// R46, PGA
}

// WM8978 L2/R2 (Line In) (L2/R2-->ADC)
// gain: 0~7, 0ֹ, 1~7, -12dB~6dB, 3dB/Step
void WM8978::lineinGain(u8 gain)
{
	u16 regval;
	gain &= 0X07;
	regval = readReg(47);	// R47
	regval&=~(7<<4); 
 	writeReg(47,regval|gain<<4); // R47
	regval = readReg(48);	// R48
	regval&=~(7<<4); 
 	writeReg(48,regval|gain<<4); // R48
} 

// WM8978 AUXR, AUXL(PWM) (AUXR/L-->ADC)
// gain:0~7, 0ֹ, 1~7, -12dB~6dB, 3dB/Step
void WM8978::auxGain(u8 gain)
{
	u16 regval;
	gain &= 0X07;
	regval = readReg(47);	// R47
	regval&=~(7<<0); 
 	writeReg(47,regval|gain<<0); // R47
	regval = readReg(48);	// R48
	regval&=~(7<<0); 
 	writeReg(48,regval|gain<<0); // R48
}  

// I2S
// fmt: 0, LSB; 1,MSB; 2, I2S; 3, PCM/DSP;
// len:0,16λ;1,20λ;2,24λ;3,32λ;  
void WM8978::i2sCfg(u8 fmt,u8 len)
{
	fmt &= 0X03;
	len &= 0X03;
	writeReg(4,(fmt<<3)|(len<<5));	// R4, WM8978
}	

// Headphone Output Volume
// voll: (0~63)
// volr: (0~63)
void WM8978::hpVolSet(u8 voll,u8 volr)
{
	voll &= 0X3F;
	volr &= 0X3F;
	if(voll==0) voll|=1<<6;
	if(volr==0) volr|=1<<6; 
	writeReg(52,voll); // R52 
	writeReg(53,volr|(1<<8)); //R53 (HPVU=1)
}

// Speaker Volume
// voll: (0~63) 
void WM8978::spkVolSet(u8 volx)
{ 
	volx &= 0X3F;
	if(volx==0) volx|=1<<6;
 	writeReg(54,volx); // R54
	writeReg(55,volx|(1<<8)); //R55 (SPKVU=1)	
}

// 3D Setup
// depth: 0~15
void WM8978::threeDSet(u8 depth)
{ 
	depth &= 0XF;
 	writeReg(41,depth);	// R41
}

// EQ/3D
// dir:0, ADC
// 1,DAC
void WM8978::eq3DDir(u8 dir)
{
	u16 regval; 
	regval = readReg(0X12);
	if(dir) regval|=1<<8;
	else regval&=~(1<<8); 
 	writeReg(18,regval); // R18
}

// EQ1
// cfreq: 0~3, 80/105/135/175Hz
// gain: 0~24, -12~+12dB
void WM8978::eq1Set(u8 cfreq,u8 gain)
{ 
	u16 regval;
	cfreq &= 0X3; 
	if(gain>24) gain = 24;
	gain = 24-gain;
	regval = readReg(18);
	regval &= 0X100;
	regval |= cfreq<<5;
	regval |= gain;
 	writeReg(18,regval);// R18, EQ1
}

// EQ2
// cfreq: 0~3, 230/300/385/500Hz
// gain: 0~24, -12~+12dB
void WM8978::eq2Set(u8 cfreq,u8 gain)
{ 
	u16 regval = 0;
	cfreq &= 0X3; 
	if(gain>24) gain = 24;
	gain = 24-gain; 
	regval |= cfreq<<5;
	regval |= gain;
 	writeReg(19,regval);
}

// EQ3
// cfreq: 0~3, 650/850/1100/1400Hz
// gain: 0~24, -12~+12dB
void WM8978::eq3Set(u8 cfreq,u8 gain)
{ 
	u16 regval = 0;
	cfreq &= 0X3; 
	if(gain>24) gain = 24;
	gain = 24-gain; 
	regval |= cfreq << 5;
	regval |= gain;
 	writeReg(20,regval); // R20, EQ3
}

// EQ4
// cfreq: 0~3, 1800/2400/3200/4100Hz
// gain: 0~24, -12~+12dB
void WM8978::eq4Set(u8 cfreq,u8 gain)
{ 
	u16 regval = 0;
	cfreq &= 0X3;
	if(gain>24) gain = 24;
	gain = 24-gain; 
	regval |= cfreq << 5;
	regval |= gain;
 	writeReg(21,regval); // R21, EQ4	
}

// EQ5
// cfreq: 0~3, 5300/6900/9000/11700Hz
// gain: 0~24, -12~+12dB
void WM8978::eq5Set(u8 cfreq,u8 gain)
{ 
	u16 regval = 0;
	cfreq &= 0X3;
	if(gain>24) gain = 24;
	gain = 24-gain; 
	regval |= cfreq << 5;
	regval |= gain;
 	writeReg(22,regval); // R22, EQ5 	
}

void WM8978::alcSet(u8 enable, u8 maxgain, u8 mingain)
{ 
	u16 regval;

	if(maxgain>7) maxgain=7;
	if(mingain>7) mingain=7;

	regval=readReg(32);
	if(enable)
		regval |= (3<<7);
	regval |= (maxgain<<3)|(mingain<<0);
 	writeReg(32,regval);
}


void WM8978::noiseSet(u8 enable,u8 gain)
{ 
	u16 regval;

	if(gain>7) gain=7;

	regval = readReg(35);
	regval = (enable<<3);
	regval |= gain;
 	writeReg(35,regval); // R18, EQ1 	
}

