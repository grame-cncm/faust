#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Minimal API used by faust2esp templates.
// These will be implemented using ESP-ADF's ES8311 driver.

int WM8978_Init(void);
int WM8978_ADDA_Cfg(uint8_t dacen, uint8_t adcen);
int WM8978_Input_Cfg(uint8_t micen, uint8_t lineinen, uint8_t auxen);
int WM8978_Output_Cfg(uint8_t dacen, uint8_t bps);
int WM8978_I2S_Cfg(uint8_t fmt, uint8_t len);
int WM8978_SPKvol(uint8_t vol);
int WM8978_MIC_Gain(uint8_t gain);

#ifdef __cplusplus
}
#endif
