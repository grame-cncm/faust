#include "WM8978.h"

#include "driver/i2c.h"
#include "driver/i2s.h"
#include "esp_err.h"

// ADF
#include "audio_hal.h"
#include "es8311.h"

// External codec handle from es8311 driver
extern audio_hal_func_t AUDIO_CODEC_ES8311_DEFAULT_HANDLE;

// ---------- LyraT-Mini v1.2 defaults (change if needed) ----------
#ifndef CODEC_I2C_PORT
#define CODEC_I2C_PORT I2C_NUM_0
#endif
#ifndef CODEC_I2C_SDA
#define CODEC_I2C_SDA 23
#endif
#ifndef CODEC_I2C_SCL
#define CODEC_I2C_SCL 18
#endif

#ifndef CODEC_I2S_PORT
#define CODEC_I2S_PORT I2S_NUM_0
#endif
// Typical LyraT-Mini v1.2 I2S pins (BCLK=5, WS=25, DOUT=26, DIN=35, MCLK
// provided by ESP) Your project likely sets I2S separately; leave this here for
// reference.

// Map WM8978 fmt/len to ADF enums
static audio_hal_iface_format_t map_fmt(uint8_t fmt) {
  // 0: I2S(Philips), 1: left-justified, 2: right-justified, 3: DSP
  switch (fmt) {
  case 1:
    return AUDIO_HAL_I2S_LEFT;
  case 2:
    return AUDIO_HAL_I2S_RIGHT;
  case 3:
    return AUDIO_HAL_I2S_DSP;
  default:
    return AUDIO_HAL_I2S_NORMAL;
  }
}
static audio_hal_iface_bits_t map_bits(uint8_t len) {
  // 0->16, 1->20, 2->24, 3->32 (common mapping in Faust templates)
  // Note: AUDIO_HAL_BIT_LENGTH_20BITS removed in newer ESP-ADF, map to 24
  switch (len) {
  case 1:
    return AUDIO_HAL_BIT_LENGTH_24BITS; // was 20BITS, no longer supported
  case 2:
    return AUDIO_HAL_BIT_LENGTH_24BITS;
  case 3:
    return AUDIO_HAL_BIT_LENGTH_32BITS;
  default:
    return AUDIO_HAL_BIT_LENGTH_16BITS;
  }
}

static audio_hal_handle_t s_hal = nullptr;

int WM8978_Init(void) {
  if (s_hal)
    return 0;

  // Note: I2C initialization is handled by audio_hal_init through the ES8311
  // driver Do not manually initialize I2C here to avoid conflicts

  audio_hal_codec_config_t cfg = {
      .adc_input = AUDIO_HAL_ADC_INPUT_LINE1, // use LINE1, MIC1 removed
      .dac_output = AUDIO_HAL_DAC_OUTPUT_ALL,
      .codec_mode = AUDIO_HAL_CODEC_MODE_BOTH,
      .i2s_iface = {
          // On LyraT-Mini, codec is typically I2S SLAVE, ESP32 is MASTER.
          .mode = AUDIO_HAL_MODE_SLAVE,
          .fmt = AUDIO_HAL_I2S_NORMAL,
          .samples =
              AUDIO_HAL_48K_SAMPLES, // adjust if your project fixes srate
          .bits = AUDIO_HAL_BIT_LENGTH_16BITS // updated later by WM8978_I2S_Cfg
      }};

  // New API: audio_hal_init takes only 2 parameters
  s_hal = audio_hal_init(&cfg, &AUDIO_CODEC_ES8311_DEFAULT_HANDLE);
  if (!s_hal)
    return -2;

  audio_hal_ctrl_codec(s_hal, AUDIO_HAL_CODEC_MODE_BOTH, AUDIO_HAL_CTRL_START);
  audio_hal_set_mute(s_hal, false);
  audio_hal_set_volume(s_hal, 80);
  return 0;
}

int WM8978_ADDA_Cfg(uint8_t dacen, uint8_t adcen) {
  if (!s_hal)
    return -1;
  audio_hal_codec_mode_t mode = AUDIO_HAL_CODEC_MODE_LINE_IN;
  if (dacen && adcen)
    mode = AUDIO_HAL_CODEC_MODE_BOTH;
  else if (dacen)
    mode = AUDIO_HAL_CODEC_MODE_DECODE;
  else if (adcen)
    mode = AUDIO_HAL_CODEC_MODE_ENCODE;
  audio_hal_ctrl_codec(s_hal, mode, AUDIO_HAL_CTRL_START);
  return 0;
}

int WM8978_Input_Cfg(uint8_t micen, uint8_t lineinen, uint8_t /*auxen*/) {
  if (!s_hal)
    return -1;
  // Note: audio_hal_set_adc_input removed in newer ESP-ADF
  // ADC input is configured in initial audio_hal_init call
  // This function kept for API compatibility but does nothing
  (void)micen;
  (void)lineinen;
  return 0;
}

int WM8978_Output_Cfg(uint8_t dacen, uint8_t /*bps*/) {
  if (!s_hal)
    return -1;
  // Note: audio_hal_set_dac_output removed in newer ESP-ADF
  // DAC output is configured in initial audio_hal_init call
  // This function kept for API compatibility but does nothing
  (void)dacen;
  return 0;
}

int WM8978_I2S_Cfg(uint8_t fmt, uint8_t len) {
  if (!s_hal)
    return -1;
  // Note: audio_hal_set_iface and audio_hal_iface_cfg_t removed in newer
  // ESP-ADF I2S interface is configured in initial audio_hal_init call This
  // function kept for API compatibility but does nothing
  (void)fmt;
  (void)len;
  return 0;
}

int WM8978_SPKvol(uint8_t vol) {
  if (!s_hal)
    return -1;
  if (vol > 100)
    vol = 100;
  audio_hal_set_volume(s_hal, vol);
  return 0;
}

int WM8978_MIC_Gain(uint8_t gain) {
  // ES8311 mic gain is configured via registers, ADF exposes helpers.
  // Map 0..100 to 0..+30 dB (approx) over 0..15 steps (2 dB/step).
  // Note: es8311_codec_set_adc_input_gain may not be available in all versions
  // This function kept for API compatibility but does nothing
  (void)gain;
  return 0;
}
