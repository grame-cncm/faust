/*
	AC101 - a AC101 Codec driver library for ESP-IDF
	ported to esp-idf by Thomas Hopman from the Arduino driver made by Ivo Pullens

	AC101 - An AC101 Codec driver library for Arduino
	Copyright (C) 2019, Ivo Pullens, Emmission

	Inspired by:
	https://github.com/donny681/esp-adf/tree/master/components/audio_hal/driver/AC101

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AC101_H
#define AC101_H

#include <stdio.h>
#include <stdint.h>
#include "esp_types.h"
#include "esp_err.h"

#define AC101_TAG  "AC101"

// I2C 
#define I2C_MASTER_NUM              1 			/*!< I2C port number for master dev */
#define I2C_MASTER_SCL_IO           32
#define I2C_MASTER_SDA_IO           33
#define I2C_MASTER_FREQ_HZ          100000
#define I2C_MASTER_TX_BUF_DISABLE   0
#define I2C_MASTER_RX_BUF_DISABLE   0

#define WRITE_BIT               I2C_MASTER_WRITE                  /*!< I2C master write */
#define READ_BIT                I2C_MASTER_READ		              /*!< I2C master read */
#define ACK_CHECK_EN   		    0x1     	                      /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS  		    0x0     	                      /*!< I2C master will not check ack from slave */

#define ACK_VAL                 (i2c_ack_type_t) 0x0              /*!< I2C ack value */
#define NACK_VAL                (i2c_ack_type_t) 0x1              /*!< I2C nack value */

// PA GPIO
#define GPIO_PA_EN          GPIO_NUM_21
#define GPIO_SEL_PA_EN      GPIO_SEL_21

// Device address
#define AC101_ADDR			0x1A

// Register Adresses
#define CHIP_AUDIO_RS		0x00
#define PLL_CTRL1			0x01
#define PLL_CTRL2			0x02
#define SYSCLK_CTRL			0x03
#define MOD_CLK_ENA			0x04
#define MOD_RST_CTRL		0x05
#define I2S_SR_CTRL			0x06
#define I2S1LCK_CTRL		0x10
#define I2S1_SDOUT_CTRL		0x11
#define I2S1_SDIN_CTRL		0x12
#define I2S1_MXR_SRC		0x13
#define I2S1_VOL_CTRL1		0x14
#define I2S1_VOL_CTRL2		0x15
#define I2S1_VOL_CTRL3		0x16
#define I2S1_VOL_CTRL4		0x17
#define I2S1_MXR_GAIN		0x18
#define ADC_DIG_CTRL		0x40
#define ADC_VOL_CTRL		0x41
#define HMIC_CTRL1			0x44
#define HMIC_CTRL2			0x45
#define HMIC_STATUS			0x46
#define DAC_DIG_CTRL		0x48
#define DAC_VOL_CTRL		0x49
#define DAC_MXR_SRC			0x4C
#define DAC_MXR_GAIN		0x4D
#define ADC_APC_CTRL		0x50
#define ADC_SRC				0x51
#define ADC_SRCBST_CTRL		0x52
#define OMIXER_DACA_CTRL	0x53
#define OMIXER_SR			0x54
#define OMIXER_BST1_CTRL	0x55
#define HPOUT_CTRL			0x56
#define SPKOUT_CTRL			0x58
#define AC_DAC_DAPCTRL		0xA0
#define AC_DAC_DAPHHPFC 	0xA1
#define AC_DAC_DAPLHPFC 	0xA2
#define AC_DAC_DAPLHAVC 	0xA3
#define AC_DAC_DAPLLAVC 	0xA4
#define AC_DAC_DAPRHAVC 	0xA5
#define AC_DAC_DAPRLAVC 	0xA6
#define AC_DAC_DAPHGDEC 	0xA7
#define AC_DAC_DAPLGDEC 	0xA8
#define AC_DAC_DAPHGATC 	0xA9
#define AC_DAC_DAPLGATC 	0xAA
#define AC_DAC_DAPHETHD 	0xAB
#define AC_DAC_DAPLETHD 	0xAC
#define AC_DAC_DAPHGKPA 	0xAD
#define AC_DAC_DAPLGKPA 	0xAE
#define AC_DAC_DAPHGOPA 	0xAF
#define AC_DAC_DAPLGOPA 	0xB0
#define AC_DAC_DAPOPT   	0xB1
#define DAC_DAP_ENA     	0xB5

#define ARRAY_SIZE(x)  (sizeof(x)/sizeof(x[0]))

const uint8_t regs[] = {
	 CHIP_AUDIO_RS		,
	 PLL_CTRL1			,
	 PLL_CTRL2			,
	 SYSCLK_CTRL		,
	 MOD_CLK_ENA		,
	 MOD_RST_CTRL		,
	 I2S_SR_CTRL		,
	 I2S1LCK_CTRL		,
	 I2S1_SDOUT_CTRL	,
	 I2S1_SDIN_CTRL		,
	 I2S1_MXR_SRC		,
	 I2S1_VOL_CTRL1		,
	 I2S1_VOL_CTRL2		,
	 I2S1_VOL_CTRL3		,
	 I2S1_VOL_CTRL4		,
	 I2S1_MXR_GAIN		,
	 ADC_DIG_CTRL		,
	 ADC_VOL_CTRL		,
	 HMIC_CTRL1			,
	 HMIC_CTRL2			,
	 HMIC_STATUS		,
	 DAC_DIG_CTRL		,
	 DAC_VOL_CTRL		,
	 DAC_MXR_SRC		,
	 DAC_MXR_GAIN		,
	 ADC_APC_CTRL		,
	 ADC_SRC			,
	 ADC_SRCBST_CTRL	,
	 OMIXER_DACA_CTRL	,
	 OMIXER_SR			,
	 OMIXER_BST1_CTRL	,
	 HPOUT_CTRL			,
	 SPKOUT_CTRL		,
	 AC_DAC_DAPCTRL		,
	 AC_DAC_DAPHHPFC 	,
	 AC_DAC_DAPLHPFC 	,
	 AC_DAC_DAPLHAVC 	,
	 AC_DAC_DAPLLAVC 	,
	 AC_DAC_DAPRHAVC 	,
	 AC_DAC_DAPRLAVC 	,
	 AC_DAC_DAPHGDEC 	,
	 AC_DAC_DAPLGDEC 	,
	 AC_DAC_DAPHGATC 	,
	 AC_DAC_DAPLGATC 	,
	 AC_DAC_DAPHETHD 	,
	 AC_DAC_DAPLETHD 	,
	 AC_DAC_DAPHGKPA 	,
	 AC_DAC_DAPLGKPA 	,
	 AC_DAC_DAPHGOPA 	,
	 AC_DAC_DAPLGOPA 	,
	 AC_DAC_DAPOPT   	,
	 DAC_DAP_ENA
};

class AC101
{
public:
	typedef enum {
		SAMPLE_RATE_8000	= 0x0000,
		SAMPLE_RATE_11052	= 0x1000,
		SAMPLE_RATE_12000	= 0x2000,
		SAMPLE_RATE_16000	= 0x3000,
		SAMPLE_RATE_22050	= 0x4000,
		SAMPLE_RATE_24000	= 0x5000,
		SAMPLE_RATE_32000	= 0x6000,
		SAMPLE_RATE_44100	= 0x7000,
		SAMPLE_RATE_48000	= 0x8000,
		SAMPLE_RATE_96000	= 0x9000,
		SAMPLE_RATE_192000	= 0xa000,
	} I2sSampleRate_t;

	typedef enum {
		MODE_MASTER			= 0x00,
		MODE_SLAVE			= 0x01,
	} I2sMode_t;

	typedef enum {
		WORD_SIZE_8_BITS	= 0x00,
		WORD_SIZE_16_BITS	= 0x01,
		WORD_SIZE_20_BITS	= 0x02,
		WORD_SIZE_24_BITS	= 0x03,
	} I2sWordSize_t;

	typedef enum {
		DATA_FORMAT_I2S		= 0x00,
		DATA_FORMAT_LEFT	= 0x01,
		DATA_FORMAT_RIGHT	= 0x02,
		DATA_FORMAT_DSP		= 0x03,
	} I2sFormat_t;

	typedef enum {
		BCLK_DIV_1			= 0x0,
		BCLK_DIV_2			= 0x1,
		BCLK_DIV_4			= 0x2,
		BCLK_DIV_6			= 0x3,
		BCLK_DIV_8			= 0x4,
		BCLK_DIV_12			= 0x5,
		BCLK_DIV_16			= 0x6,
		BCLK_DIV_24			= 0x7,
		BCLK_DIV_32			= 0x8,
		BCLK_DIV_48			= 0x9,
		BCLK_DIV_64			= 0xa,
		BCLK_DIV_96			= 0xb,
		BCLK_DIV_128		= 0xc,
		BCLK_DIV_192		= 0xd,
	} I2sBitClockDiv_t;

	typedef enum {
		LRCK_DIV_16			= 0x0,
		LRCK_DIV_32			= 0x1,
		LRCK_DIV_64			= 0x2,
		LRCK_DIV_128		= 0x3,
		LRCK_DIV_256		= 0x4,
	} I2sLrClockDiv_t;


	typedef enum {
		MODE_ADC,
		MODE_DAC,
		MODE_ADC_DAC,
		MODE_LINE
	} Mode_t;

	// Constructor.
  	AC101();

	// Initialize the I2C interface
    esp_err_t InitI2C(void);

	// AC101 begin
	// Initialize codec, using provided I2C pins and bus frequency.
	// sets up 24 bit 48Khz sample-rate
	// enables line input, line (headphone) output and turns on the speaker outputs
	// @return false on success, true on failure.
	esp_err_t begin();

	// Get speaker volume.
	// @return Speaker volume, [63..0] for [0..-43.5] [dB], in increments of 2.
	uint8_t GetVolumeSpeaker();

	// Set speaker volume.
	// @param volume   Target volume, [63..0] for [0..-43.5] [dB], in increments of 2.
	// @return false on success, true on failure.
	esp_err_t SetVolumeSpeaker(uint8_t volume);

	// Get headphone volume.
	// @return Headphone volume, [63..0] for [0..-62] [dB]
	uint8_t GetVolumeHeadphone();

	// Set headphone volume
	// @param volume   Target volume, [63..0] for [0..-62] [dB]
	// @return false on success, true on failure.
	esp_err_t SetVolumeHeadphone(uint8_t volume);

	// Configure I2S samplerate.
	// @param rate   Samplerate.
	// @return false on success, true on failure.
	esp_err_t SetI2sSampleRate(I2sSampleRate_t rate);

	// Configure I2S mode (master/slave).
	// @param mode   Mode.
	// @return false on success, true on failure.
	esp_err_t SetI2sMode(I2sMode_t mode);

	// Configure I2S word size (8/16/20/24 bits).
	// @param size   Word size.
	// @return false on success, true on failure.
	esp_err_t SetI2sWordSize(I2sWordSize_t size);

	// Configure I2S format (I2S/Left/Right/Dsp).
	// @param format   I2S format.
	// @return false on success, true on failure.
	esp_err_t SetI2sFormat(I2sFormat_t format);

	// Configure I2S clock.
	// @param bitClockDiv   I2S1CLK/BCLK1 ratio.
	// @param bitClockInv   I2S1 BCLK Polarity.
	// @param lrClockDiv    BCLK1/LRCK ratio.
	// @param lrClockInv    I2S1 LRCK Polarity.
	// @return false on success, true on failure.
	esp_err_t SetI2sClock(I2sBitClockDiv_t bitClockDiv, bool bitClockInv, I2sLrClockDiv_t lrClockDiv, bool lrClockInv);

	// Configure the mode (Adc/Dac/Adc+Dac/Line)
	// @param mode    Operating mode.
	// @return false on success, true on failure.
	esp_err_t SetMode(Mode_t mode);

	// AC101 DumpRegister
	// prints out contents of the AC101 registers in hex
	void DumpRegisters();
	
	// AC101 PA Power
	// enables or disables the speaker outputs
	void ac101_pa_power(bool enable);

	// printBits
	// print out any value in binary format. Used for debugging
	void printBits(size_t const size, void const * const ptr);

	// printRead
	// print out the contents of any ac101 register. Used for debugging
    void printRead(uint8_t reg);

protected:

	// Write to a register of the AC101
	// reg: Register Address
	// val: Value to be written
	// @return false on success, true on failure.
	esp_err_t WriteReg(uint8_t reg, uint16_t val);

	// Read a register of the AC101
	// reg: Register Address to be read
	// @return: uint16_t value of register.
	uint16_t ReadReg(uint8_t reg);

	// AC101 read register full
	// Reads the value of the AC101 register Address
	// reg: Register Address
	// data_rd: Pointer to return value
	// size: size of data to be read
	// @return false on success, true on failure.
	esp_err_t ReadReg_Full(uint8_t reg, uint8_t* data_rd, size_t size);
	
};

#endif
