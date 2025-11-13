#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rtc_wdt.h"
#include <cstdio>
#include <new>

#include "esp_heap_caps.h"
#ifdef CONFIG_SPIRAM
#if defined(__has_include)
#if __has_include("esp_spiram.h")
#include "esp_spiram.h"
#else
#warning "esp_spiram.h not found in include path; continuing without it"
#endif
#else
#include "esp_spiram.h"
#endif
#endif
/* We avoid including esp_spiram.h here to keep this translation unit
  independent of the presence of that header in build include paths.
  Instead, allocation into SPIRAM is attempted when CONFIG_SPIRAM is set
  and we fall back to internal heap if the allocation fails. */

extern "C" {
#include "WM8978.h" // ES8311-backed shim
}

#include "FaustSawtooth.h" // your faust2esp32 output

#define SAMPLE_RATE 48000
#define I2S_PORT I2S_NUM_0
#define BLOCK_SIZE 128

static void i2s_init() {
  i2s_config_t cfg = {.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
                      .sample_rate = SAMPLE_RATE,
                      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
                      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
                      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
                      .intr_alloc_flags = 0,
                      .dma_buf_count = 8,
                      .dma_buf_len = BLOCK_SIZE,
                      .use_apll = false,
                      .tx_desc_auto_clear = true,
                      .fixed_mclk = 0};
  i2s_pin_config_t pins = {.bck_io_num = 5, // LyraT-Mini v1.2 defaults
                           .ws_io_num = 25,
                           .data_out_num = 26,
                           .data_in_num = 35};
  i2s_driver_install(I2S_PORT, &cfg, 0, nullptr);
  i2s_set_pin(I2S_PORT, &pins);
  i2s_zero_dma_buffer(I2S_PORT);
}

extern "C" void app_main() {
  // Print available heap before initialization
  printf("Free heap before init: %lu bytes\n", esp_get_free_heap_size());

  // Init codec (ES8311 under the hood)
  WM8978_Init();
  WM8978_ADDA_Cfg(/*DAC*/ 1, /*ADC*/ 0);
  WM8978_I2S_Cfg(/*I2S*/ 0, /*16-bit*/ 0);
  WM8978_SPKvol(90);

  printf("Free heap after codec init: %lu bytes\n", esp_get_free_heap_size());

  // Create Faust DSP with sample rate and buffer size on heap
  // Prefer allocating the large data for the object in SPIRAM (PSRAM) when
  // available.
  void *dsp_buf = nullptr;

  /* Prefer allocating the large data for the object in SPIRAM (PSRAM) when
     available. Guarded so the code compiles even when PSRAM support is not
     enabled in sdkconfig (no esp_spiram.h available). */
#ifdef CONFIG_SPIRAM
  /* Try to allocate directly in SPIRAM. If that fails, fall back to internal
   * RAM. */
  printf("Attempting allocation in SPIRAM (if available)\n");
  dsp_buf = heap_caps_malloc(sizeof(FaustSawtooth),
                             MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
  if (dsp_buf) {
    printf("Allocated DSP buffer in SPIRAM\n");
  } else {
    printf("SPIRAM allocation failed or not present - allocating in internal "
           "heap\n");
    dsp_buf = heap_caps_malloc(sizeof(FaustSawtooth), MALLOC_CAP_8BIT);
  }
#else
  printf("SPIRAM support not compiled in - allocating DSP in internal heap\n");
  dsp_buf = heap_caps_malloc(sizeof(FaustSawtooth), MALLOC_CAP_8BIT);
#endif

  if (!dsp_buf) {
    printf(
        "Failed to allocate buffer for FaustSawtooth (requested %zu bytes)\n",
        sizeof(FaustSawtooth));
    return;
  }

  // Placement-new the object into the allocated buffer
  FaustSawtooth *dsp = new (dsp_buf) FaustSawtooth(SAMPLE_RATE, BLOCK_SIZE);

  if (!dsp) {
    printf("Failed to construct FaustSawtooth object\n");
    heap_caps_free(dsp_buf);
    return;
  }

  printf("Free heap after DSP creation: %lu bytes\n", esp_get_free_heap_size());

  // Start the audio processing
  if (dsp->start()) {
    printf("Faust DSP started successfully\n");
  } else {
    printf("Failed to start Faust DSP\n");
  }
  rtc_wdt_protect_off(); // Turns off the automatic wdt service
  rtc_wdt_enable();      // Turn it on manually
  rtc_wdt_set_time(RTC_WDT_STAGE0, 20000);
  // Main loop - the DSP runs in its own task
  // ... inside the while(true) loop
  while (true) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
