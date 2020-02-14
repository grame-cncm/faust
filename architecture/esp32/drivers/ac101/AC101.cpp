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

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "AC101.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

// Constructor.
AC101::AC101()
{}

// Initialize the I2C interface
esp_err_t AC101::InitI2C(void)
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
    return i2c_driver_install(i2c_master_port, conf.mode,
                              I2C_MASTER_RX_BUF_DISABLE,
                              I2C_MASTER_TX_BUF_DISABLE, 0);
}

// AC101 begin
// Initialize codec, using provided I2C pins and bus frequency.
// sets up 24 bit 48Khz sample-rate
// enables line input, line (headphone) output and turns on the speaker outputs
// @return false on success, true on failure.
esp_err_t AC101::begin()
{
    if(InitI2C()) return -1;
    esp_err_t res;
    res = WriteReg(CHIP_AUDIO_RS, 0x123);
    WriteReg(CHIP_AUDIO_RS, 0x123);
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    if (ESP_OK != res) {
        ESP_LOGE(AC101_TAG, "reset failed!");
        return res;
    } else {
        ESP_LOGI(AC101_TAG, "reset succeed");
    }
    
    res |= WriteReg(SPKOUT_CTRL, 0xe880);
    
    // Enable the PLL from 512*48KHz MCLK source 24.576Mhz
    res |= WriteReg(PLL_CTRL1, 0x014f);
    res |= WriteReg(PLL_CTRL2, 0x8030);                // N = 96 @ 0x8600 mclk 12.288Mhz // N = 3 @ 0x8030 mclk 24.576Mhz
    
    // Clocking system
    res |= WriteReg(SYSCLK_CTRL, 0x8b08);
    res |= WriteReg(MOD_CLK_ENA, 0x800c);
    res |= WriteReg(MOD_RST_CTRL, 0x800c);
    
    // Set default at I2S, 48KHz, 24bit
    res |= SetI2sSampleRate(SAMPLE_RATE_48000);
    res |= SetI2sClock(BCLK_DIV_8, false, LRCK_DIV_64, false);
    res |= SetI2sMode(MODE_SLAVE);
    res |= SetI2sWordSize(WORD_SIZE_24_BITS);
    res |= SetI2sFormat(DATA_FORMAT_I2S);
    
    // AIF config
    res |= WriteReg(I2S1_SDOUT_CTRL, 0xc000);
    res |= WriteReg(I2S1_SDIN_CTRL, 0xc000);
    res |= WriteReg(I2S1_MXR_SRC, 0x2200);
    
    res |= WriteReg(ADC_SRCBST_CTRL, 0xccc4);
    res |= WriteReg(ADC_SRC, 0x0408);                // 0x2020 for mic input // 0x0408 for line input
    res |= WriteReg(ADC_DIG_CTRL, 0x8000);
    res |= WriteReg(ADC_APC_CTRL, 0xbbc3);
    
    // Path Configuration
    res |= WriteReg(DAC_MXR_SRC, 0xcc00);
    res |= WriteReg(DAC_DIG_CTRL, 0x8000);
    res |= WriteReg(OMIXER_SR, 0x0081);
    res |= WriteReg(OMIXER_DACA_CTRL, 0xf080);
    
    res |= SetMode( MODE_DAC );
    
    ESP_LOGI(AC101_TAG, "init done");
    ac101_pa_power(true);
    return res;
}

// Get speaker volume.
// @return Speaker volume, [63..0] for [0..-43.5] [dB], in increments of 2.
uint8_t AC101::GetVolumeSpeaker()
{
    // Times 2, to scale to same range as headphone volume
    return (ReadReg(SPKOUT_CTRL) & 31) * 2;
}

// Set speaker volume.
// @param volume   Target volume, [63..0] for [0..-43.5] [dB], in increments of 2.
// @return false on success, true on failure.
esp_err_t AC101::SetVolumeSpeaker(uint8_t volume)
{
    // Divide by 2, as it is scaled to same range as headphone volume
    volume /= 2;
    if (volume > 31) volume = 31;
    
    uint16_t val = ReadReg(SPKOUT_CTRL);
    val &= ~31;
    val |= volume;
    return WriteReg(SPKOUT_CTRL, val);
}

// Get headphone volume.
// @return Headphone volume, [63..0] for [0..-62] [dB]
uint8_t AC101::GetVolumeHeadphone()
{
    return (ReadReg(HPOUT_CTRL) >> 4) & 63;
}

// Set headphone volume
// @param volume   Target volume, [63..0] for [0..-62] [dB]
// @return false on success, true on failure.
esp_err_t AC101::SetVolumeHeadphone(uint8_t volume)
{
    if (volume > 63) volume = 63;
    uint16_t val = ReadReg(HPOUT_CTRL);
    val &= ~63 << 4;
    val |= volume << 4;
    return WriteReg(HPOUT_CTRL, val);
}

// Configure I2S samplerate.
// @param rate   Samplerate.
// @return false on success, true on failure.
esp_err_t AC101::SetI2sSampleRate(I2sSampleRate_t rate)
{
    return WriteReg(I2S_SR_CTRL, rate);
}

// Configure I2S mode (master/slave).
// @param mode   Mode.
// @return false on success, true on failure.
esp_err_t AC101::SetI2sMode(I2sMode_t mode)
{
    uint16_t val = ReadReg(I2S1LCK_CTRL);
    val &= ~0x8000;
    val |= uint16_t(mode) << 15;
    return WriteReg(I2S1LCK_CTRL, val);
}

// Configure I2S word size (8/16/20/24 bits).
// @param size   Word size.
// @return false on success, true on failure.
esp_err_t AC101::SetI2sWordSize(I2sWordSize_t size)
{
    uint16_t val = ReadReg(I2S1LCK_CTRL);
    val &= ~0x0030;
    val |= uint16_t(size) << 4;
    return WriteReg(I2S1LCK_CTRL, val);
}

// Configure I2S format (I2S/Left/Right/Dsp).
// @param format   I2S format.
// @return false on success, true on failure.
esp_err_t AC101::SetI2sFormat(I2sFormat_t format)
{
    uint16_t val = ReadReg(I2S1LCK_CTRL);
    val &= ~0x000C;
    val |= uint16_t(format) << 2;
    return WriteReg(I2S1LCK_CTRL, val);
}

// Configure I2S clock.
// @param bitClockDiv   I2S1CLK/BCLK1 ratio.
// @param bitClockInv   I2S1 BCLK Polarity.
// @param lrClockDiv    BCLK1/LRCK ratio.
// @param lrClockInv    I2S1 LRCK Polarity.
// @return false on success, true on failure.
esp_err_t AC101::SetI2sClock(I2sBitClockDiv_t bitClockDiv, bool bitClockInv, I2sLrClockDiv_t lrClockDiv, bool lrClockInv)
{
    uint16_t val = ReadReg(I2S1LCK_CTRL);
    val &= ~0x7FC0;
    val |= uint16_t(bitClockInv ? 1 : 0) << 14;
    val |= uint16_t(bitClockDiv) << 9;
    val |= uint16_t(lrClockInv ? 1 : 0) << 13;
    val |= uint16_t(lrClockDiv) << 6;
    return WriteReg(I2S1LCK_CTRL, val);
}

// Configure the mode (Adc/Dac/Adc+Dac/Line)
// @param mode    Operating mode.
// @return false on success, true on failure.
esp_err_t AC101::SetMode(Mode_t mode)
{
    esp_err_t ret = ESP_OK;
    if (MODE_LINE == mode)
    {
        ret |= WriteReg(ADC_SRC, 0x0408);
        ret |= WriteReg(ADC_DIG_CTRL, 0x8000);
        ret |= WriteReg(ADC_APC_CTRL, 0x3bc0);
    }
    
    if ((MODE_ADC == mode) or (MODE_ADC_DAC == mode) or (MODE_LINE == mode))
    {
        ret |= WriteReg(MOD_CLK_ENA,  0x800c);
        ret |= WriteReg(MOD_RST_CTRL, 0x800c);
    }
    
    if ((MODE_DAC == mode) or (MODE_ADC_DAC == mode) or (MODE_LINE == mode))
    {
        // Enable Headphone output
        ret |= WriteReg(OMIXER_DACA_CTRL, 0xff80);
        ret |= WriteReg(HPOUT_CTRL, 0xc3c1);
        ret |= WriteReg(HPOUT_CTRL, 0xcb00);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        ret |= WriteReg(HPOUT_CTRL, 0xfbc0);
        ret |= SetVolumeHeadphone(30);
        
        // Enable Speaker output
        ret |= WriteReg(SPKOUT_CTRL, 0xeabd);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        ret |= SetVolumeSpeaker(30);
    }
    return ret;
}

// AC101 DumpRegister
// prints out contents of the AC101 registers in hex
void AC101::DumpRegisters()
{
    for (size_t i = 0; i < ARRAY_SIZE(regs); ++i)
    {
        printf("%02x", regs[i]);
        printf(" = ");
        printf("%04x", ReadReg(regs[i]));
        printf("\n");
    }
}

// AC101 PA Power
// enables or disables the speaker outputs
void AC101::ac101_pa_power(bool enable)
{
    gpio_config_t  io_conf;
    memset(&io_conf, 0, sizeof(io_conf));
    io_conf.intr_type = (gpio_int_type_t) GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = BIT(GPIO_PA_EN);
    io_conf.pull_down_en = (gpio_pulldown_t) 0;
    io_conf.pull_up_en = (gpio_pullup_t) 0;
    gpio_config(&io_conf);
    if (enable) {
        gpio_set_level(GPIO_PA_EN, 1);
    } else {
        gpio_set_level(GPIO_PA_EN, 0);
    }
}

// printBits
// print out any value in binary format used for debugging
void AC101::printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
// printRead
// print out the contents of any ac101 register used for debugging
void AC101::printRead(uint8_t reg)
{
    uint8_t buf[2];
    ReadReg_Full(reg, buf, 2 );
    printBits(sizeof(buf), &buf);
}

// Write to a register of the AC101
// reg: Register Address
// val: Value to be written
// @return false on success, true on failure.
esp_err_t AC101::WriteReg(uint8_t reg, uint16_t val)
{
    esp_err_t ret = ESP_OK;
    uint8_t buf[2];
    buf[0] = uint8_t((val >> 8) & 0xff);
    buf[1] = uint8_t(val & 0xff);
    
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    ret |= i2c_master_start(cmd);
    ret |= i2c_master_write_byte(cmd, (AC101_ADDR << 1) | WRITE_BIT, ACK_CHECK_EN);
    ret |= i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    ret |= i2c_master_write(cmd, buf, 2, ACK_CHECK_EN);
    ret |= i2c_master_stop(cmd);
    ret |= i2c_master_cmd_begin((i2c_port_t) I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

// Read a register of the AC101
// reg: Register Address to be read
// @return false on success, true on failure.
uint16_t AC101::ReadReg(uint8_t reg)
{
    uint16_t val = 0;
    uint8_t data_rd[2];
    ReadReg_Full(reg, data_rd, 2);
    val=(data_rd[0]<<8)+data_rd[1];
    return val;
}

// AC101 read register
// Reads the value of the AC101 register Address
// reg: Register Address
// data_rd: Pointer to return value
// size: size of data to be read
// @return false on success, true on failure.
esp_err_t AC101::ReadReg_Full(uint8_t reg, uint8_t* data_rd, size_t size)
{
    esp_err_t ret = ESP_OK;
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    ret |= i2c_master_start(cmd);
    ret |= i2c_master_write_byte(cmd, (AC101_ADDR << 1), ACK_CHECK_EN);
    ret |= i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
    ret |= i2c_master_start(cmd);
    ret |= i2c_master_write_byte(cmd, (AC101_ADDR << 1) | READ_BIT, ACK_CHECK_EN);
    if (size > 1) {
        ret |= i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
    }
    ret |= i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
    ret |= i2c_master_stop(cmd);
    ret |= i2c_master_cmd_begin((i2c_port_t) I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
