/* Automatically generated file; DO NOT EDIT */
/* Espressif IoT Development Framework Linker Script */
/* Generated from: /Users/anantrohmetra/esp/v5.1.6/esp-idf/components/esp_system/ld/esp32/sections.ld.in */

/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/*  Default entry point:  */
ENTRY(call_start_cpu0);

SECTIONS
{
  /* RTC fast memory holds RTC wake stub code,
     including from any source file named rtc_wake_stub*.c
  */
  .rtc.text :
  {
    . = ALIGN(4);

    *(.rtc.literal .rtc.text .rtc.text.*)

    *rtc_wake_stub*.*(.literal .text .literal.* .text.*)
    _rtc_text_end = ABSOLUTE(.);
  } > rtc_iram_seg

  /*
    This section is required to skip rtc.text area because rtc_iram_seg and
    rtc_data_seg are reflect the same address space on different buses.
  */
  .rtc.dummy :
  {
    _rtc_dummy_start = ABSOLUTE(.);
    _rtc_fast_start = ABSOLUTE(.);
    . = SIZEOF(.rtc.text);
    _rtc_dummy_end = ABSOLUTE(.);
  } > rtc_data_seg

  /* This section located in RTC FAST Memory area.
     It holds data marked with RTC_FAST_ATTR attribute.
     See the file "esp_attr.h" for more information.
  */
  .rtc.force_fast :
  {
    . = ALIGN(4);
    _rtc_force_fast_start = ABSOLUTE(.);

    _coredump_rtc_fast_start = ABSOLUTE(.);
    *(.rtc.fast.coredump .rtc.fast.coredump.*)
    _coredump_rtc_fast_end = ABSOLUTE(.);

    *(.rtc.force_fast .rtc.force_fast.*)
    . = ALIGN(4) ;

    _rtc_force_fast_end = ABSOLUTE(.);
  } > rtc_data_seg

  /* RTC data section holds RTC wake stub
     data/rodata, including from any source file
     named rtc_wake_stub*.c and the data marked with
     RTC_DATA_ATTR, RTC_RODATA_ATTR attributes.
     The memory location of the data is dependent on
     CONFIG_ESP32_RTCDATA_IN_FAST_MEM option.
  */
  .rtc.data :
  {
    _rtc_data_start = ABSOLUTE(.);

    _coredump_rtc_start = ABSOLUTE(.);
    *(.rtc.coredump .rtc.coredump.*)
    _coredump_rtc_end = ABSOLUTE(.);
    *(.rtc.data .rtc.data.*)
    *(.rtc.rodata .rtc.rodata.*)

    *rtc_wake_stub*.*(.data .rodata .data.* .rodata.*)
    _rtc_data_end = ABSOLUTE(.);

  } > rtc_data_location

  /* RTC bss, from any source file named rtc_wake_stub*.c */
  .rtc.bss (NOLOAD) :
  {
    _rtc_bss_start = ABSOLUTE(.);
    *rtc_wake_stub*.*(.bss .bss.*)
    *rtc_wake_stub*.*(COMMON)

    *(.rtc.bss)

    _rtc_bss_end = ABSOLUTE(.);
  } > rtc_data_location

  /* This section holds data that should not be initialized at power up
     and will be retained during deep sleep.
     User data marked with RTC_NOINIT_ATTR will be placed
     into this section. See the file "esp_attr.h" for more information.
	 The memory location of the data is dependent on
     CONFIG_ESP32_RTCDATA_IN_FAST_MEM option.
  */
  .rtc_noinit (NOLOAD):
  {
    . = ALIGN(4);
    _rtc_noinit_start = ABSOLUTE(.);
    *(.rtc_noinit .rtc_noinit.*)
    . = ALIGN(4) ;
    _rtc_noinit_end = ABSOLUTE(.);
  } > rtc_data_location

  /* This section located in RTC SLOW Memory area.
     It holds data marked with RTC_SLOW_ATTR attribute.
     See the file "esp_attr.h" for more information.
  */
  .rtc.force_slow :
  {
    . = ALIGN(4);
    _rtc_force_slow_start = ABSOLUTE(.);
    *(.rtc.force_slow .rtc.force_slow.*)
    . = ALIGN(4) ;
    _rtc_force_slow_end = ABSOLUTE(.);
  } > rtc_slow_seg

  /**
   * This section holds RTC FAST data that should have fixed addresses.
   * The data are not initialized at power-up and are retained during deep sleep.
   */
  .rtc_fast_reserved (NOLOAD):
  {
    . = ALIGN(4);
    _rtc_fast_reserved_start = ABSOLUTE(.);
    /* New data can only be added here to ensure existing data are not moved.
       Because data have adhered to the end of the segment and code is relied on it.
       >> put new data here << */
    KEEP(*(.bootloader_data_rtc_mem .bootloader_data_rtc_mem.*))
    _rtc_fast_reserved_end = ABSOLUTE(.);
  } > rtc_fast_reserved_seg

  _rtc_fast_reserved_length = _rtc_fast_reserved_end - _rtc_fast_reserved_start;
  ASSERT((_rtc_fast_reserved_length <= LENGTH(rtc_fast_reserved_seg)),
          "RTC FAST reserved segment data does not fit.")

  /**
   * This section holds RTC SLOW data that should have fixed addresses.
   * The data are not initialized at power-up and are retained during deep sleep.
   */
  .rtc_slow_reserved (NOLOAD):
  {
    . = ALIGN(4);
    _rtc_slow_reserved_start = ABSOLUTE(.);
    /* New data can only be added here to ensure existing data are not moved.
       Because data have adhered to the end of the segment and code is relied on it.
       >> put new data here << */

    *(.rtc_timer_data_in_rtc_mem .rtc_timer_data_in_rtc_mem.*)
    _rtc_slow_reserved_end = ABSOLUTE(.);
  } > rtc_slow_reserved_seg

  _rtc_slow_reserved_length = _rtc_slow_reserved_end - _rtc_slow_reserved_start;
  _rtc_reserved_length = _rtc_slow_reserved_length;
  ASSERT((_rtc_slow_reserved_length <= LENGTH(rtc_slow_reserved_seg)),
          "RTC SLOW reserved segment data does not fit.")

  /* Get size of rtc slow data based on rtc_data_location alias */
  _rtc_slow_length = (ORIGIN(rtc_slow_seg) == ORIGIN(rtc_data_location))
                        ? (_rtc_force_slow_end - _rtc_data_start)
                        : (_rtc_force_slow_end - _rtc_force_slow_start);

  _rtc_fast_length = (ORIGIN(rtc_slow_seg) == ORIGIN(rtc_data_location))
                        ? (_rtc_force_fast_end - _rtc_fast_start)
                        : (_rtc_noinit_end - _rtc_fast_start);

  ASSERT((_rtc_slow_length <= LENGTH(rtc_slow_seg)),
          "RTC_SLOW segment data does not fit.")

  ASSERT((_rtc_fast_length <= LENGTH(rtc_data_seg)),
          "RTC_FAST segment data does not fit.")

  /* Send .iram0 code to iram */
  .iram0.vectors :
  {
    _iram_start = ABSOLUTE(.);
    /* Vectors go to IRAM */
    _vector_table = ABSOLUTE(.);
    /* Vectors according to builds/RF-2015.2-win32/esp108_v1_2_s5_512int_2/config.html */
    . = 0x0;
    KEEP(*(.WindowVectors.text));
    . = 0x180;
    KEEP(*(.Level2InterruptVector.text));
    . = 0x1c0;
    KEEP(*(.Level3InterruptVector.text));
    . = 0x200;
    KEEP(*(.Level4InterruptVector.text));
    . = 0x240;
    KEEP(*(.Level5InterruptVector.text));
    . = 0x280;
    KEEP(*(.DebugExceptionVector.text));
    . = 0x2c0;
    KEEP(*(.NMIExceptionVector.text));
    . = 0x300;
    KEEP(*(.KernelExceptionVector.text));
    . = 0x340;
    KEEP(*(.UserExceptionVector.text));
    . = 0x3C0;
    KEEP(*(.DoubleExceptionVector.text));
    . = 0x400;
    _invalid_pc_placeholder = ABSOLUTE(.);
    *(.*Vector.literal)

    *(.UserEnter.literal);
    *(.UserEnter.text);
    . = ALIGN (16);
    *(.entry.text)
    *(.init.literal)
    *(.init)

    _init_end = ABSOLUTE(.);
  } > iram0_0_seg

  .iram0.text :
  {
    /* Code marked as runnning out of IRAM */
    _iram_text_start = ABSOLUTE(.);

    *(.iram1 .iram1.*)
    *libapp_trace.a:app_trace.*(.literal .literal.* .text .text.*)
    *libapp_trace.a:app_trace_util.*(.literal .literal.* .text .text.*)
    *libapp_trace.a:port_uart.*(.literal .literal.* .text .text.*)
    *libc.a:creat.*(.literal .literal.* .text .text.*)
    *libc.a:isatty.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-abs.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-asctime.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-asctime_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-atoi.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-atol.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-bzero.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-close.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-creat.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-ctime.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-ctime_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-ctype_.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-div.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-environ.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-envlock.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-fclose.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-fflush.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-findfp.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-fputwc.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-fvwrite.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-fwalk.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-getenv_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-gettzinfo.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-gmtime.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-gmtime_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-impure.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isalnum.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isalpha.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isascii.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isblank.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-iscntrl.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isdigit.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isgraph.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-islower.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isprint.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-ispunct.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isspace.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-isupper.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-itoa.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-labs.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-lcltime.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-lcltime_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-ldiv.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-longjmp.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-makebuf.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-memccpy.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-memchr.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-memcmp.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-memcpy.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-memmove.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-memrchr.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-memset.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-mktime.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-month_lengths.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-open.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-quorem.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-raise.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-rand.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-rand_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-read.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-refill.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-rshift.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-s_fpclassify.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-sbrk.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-sccl.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-setjmp.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-sf_nan.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-srand.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-stdio.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strcasecmp.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strcasestr.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strcat.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strchr.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strcmp.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strcoll.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strcpy.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strcspn.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strdup.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strdup_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strftime.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strlcat.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strlcpy.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strlen.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strlwr.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strncasecmp.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strncat.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strncmp.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strncpy.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strndup.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strndup_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strnlen.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strptime.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strrchr.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strsep.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strspn.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strstr.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strtok_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strtol.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strtoul.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-strupr.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-sysclose.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-sysopen.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-sysread.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-syssbrk.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-system.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-systimes.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-syswrite.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-time.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-timelocal.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-toascii.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-tolower.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-toupper.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-tzcalc_limits.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-tzlock.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-tzset.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-tzset_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-tzvars.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-ungetc.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-utoa.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-wbuf.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-wcrtomb.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-wctomb_r.*(.literal .literal.* .text .text.*)
    *libc.a:lib_a-wsetup.*(.literal .literal.* .text .text.*)
    *libc.a:lock.*(.literal .literal.* .text .text.*)
    *libdriver.a:gptimer.*(.literal.gptimer_default_isr .text.gptimer_default_isr)
    *libesp_event.a:default_event_loop.*(.literal.esp_event_isr_post .text.esp_event_isr_post)
    *libesp_event.a:esp_event.*(.literal.esp_event_isr_post_to .text.esp_event_isr_post_to)
    *libesp_hw_support.a:cpu.*(.literal.esp_cpu_compare_and_set .text.esp_cpu_compare_and_set)
    *libesp_hw_support.a:cpu.*(.literal.esp_cpu_reset .text.esp_cpu_reset)
    *libesp_hw_support.a:cpu.*(.literal.esp_cpu_stall .text.esp_cpu_stall)
    *libesp_hw_support.a:cpu.*(.literal.esp_cpu_unstall .text.esp_cpu_unstall)
    *libesp_hw_support.a:cpu.*(.literal.esp_cpu_wait_for_intr .text.esp_cpu_wait_for_intr)
    *libesp_hw_support.a:esp_gpio_reserve.*(.literal.esp_gpio_is_pin_reserved .text.esp_gpio_is_pin_reserved)
    *libesp_hw_support.a:esp_gpio_reserve.*(.literal.esp_gpio_reserve_pins .text.esp_gpio_reserve_pins)
    *libesp_hw_support.a:esp_memory_utils.*(.literal .literal.* .text .text.*)
    *libesp_hw_support.a:periph_ctrl.*(.literal.periph_module_reset .text.periph_module_reset)
    *libesp_hw_support.a:periph_ctrl.*(.literal.wifi_module_disable .text.wifi_module_disable)
    *libesp_hw_support.a:periph_ctrl.*(.literal.wifi_module_enable .text.wifi_module_enable)
    *libesp_hw_support.a:rtc_clk.*(.literal .literal.* .text .text.*)
    *libesp_hw_support.a:rtc_sleep.*(.literal .literal.* .text .text.*)
    *libesp_hw_support.a:rtc_time.*(.literal .literal.* .text .text.*)
    *libesp_hw_support.a:rtc_wdt.*(.literal .literal.* .text .text.*)
    *libesp_hw_support.a:sar_periph_ctrl.*(.literal.sar_periph_ctrl_power_enable .text.sar_periph_ctrl_power_enable)
    *libesp_mm.a:cache_esp32.*(.literal .literal.* .text .text.*)
    *libesp_mm.a:esp_cache.*(.literal .literal.* .text .text.*)
    *libesp_ringbuf.a:(.literal .literal.* .text .text.*)
    *libesp_rom.a:esp_rom_spiflash.*(.literal .literal.* .text .text.*)
    *libesp_system.a:esp_err.*(.literal .literal.* .text .text.*)
    *libesp_system.a:esp_system_chip.*(.literal.esp_system_abort .text.esp_system_abort)
    *libesp_system.a:ubsan.*(.literal .literal.* .text .text.*)
    *libesp_wifi.a:esp_adapter.*(.literal.coex_pti_get_wrapper .text.coex_pti_get_wrapper)
    *libesp_wifi.a:wifi_netif.*(.literal.wifi_sta_receive .text.wifi_sta_receive)
    *libesp_wifi.a:wifi_netif.*(.literal.wifi_transmit_wrap .text.wifi_transmit_wrap)
    *libfreertos.a:(EXCLUDE_FILE(*libfreertos.a:app_startup.* *libfreertos.a:idf_additions.*) .literal EXCLUDE_FILE(*libfreertos.a:app_startup.* *libfreertos.a:idf_additions.*) .literal.* EXCLUDE_FILE(*libfreertos.a:app_startup.* *libfreertos.a:idf_additions.*) .text EXCLUDE_FILE(*libfreertos.a:app_startup.* *libfreertos.a:idf_additions.*) .text.*)
    *libgcc.a:lib2funcs.*(.literal .literal.* .text .text.*)
    *libgcov.a:(.literal .literal.* .text .text.*)
    *libhal.a:cache_hal_esp32.*(.literal .literal.* .text .text.*)
    *libhal.a:i2c_hal_iram.*(.literal .literal.* .text .text.*)
    *libhal.a:ledc_hal_iram.*(.literal .literal.* .text .text.*)
    *libhal.a:mmu_hal.*(.literal .literal.* .text .text.*)
    *libhal.a:spi_flash_encrypt_hal_iram.*(.literal .literal.* .text .text.*)
    *libhal.a:spi_flash_hal_iram.*(.literal .literal.* .text .text.*)
    *libhal.a:spi_hal_iram.*(.literal .literal.* .text .text.*)
    *libhal.a:spi_slave_hal_iram.*(.literal .literal.* .text .text.*)
    *libhal.a:timer_hal.*(.literal.timer_hal_capture_and_get_counter_value .text.timer_hal_capture_and_get_counter_value)
    *libhal.a:wdt_hal_iram.*(.literal .literal.* .text .text.*)
    *libheap.a:multi_heap.*(.literal.assert_valid_block .text.assert_valid_block)
    *libheap.a:multi_heap.*(.literal.multi_heap_aligned_alloc_impl .text.multi_heap_aligned_alloc_impl)
    *libheap.a:multi_heap.*(.literal.multi_heap_aligned_alloc_impl_offs .text.multi_heap_aligned_alloc_impl_offs)
    *libheap.a:multi_heap.*(.literal.multi_heap_free_impl .text.multi_heap_free_impl)
    *libheap.a:multi_heap.*(.literal.multi_heap_get_allocated_size_impl .text.multi_heap_get_allocated_size_impl)
    *libheap.a:multi_heap.*(.literal.multi_heap_get_block_address_impl .text.multi_heap_get_block_address_impl)
    *libheap.a:multi_heap.*(.literal.multi_heap_get_first_block .text.multi_heap_get_first_block)
    *libheap.a:multi_heap.*(.literal.multi_heap_get_next_block .text.multi_heap_get_next_block)
    *libheap.a:multi_heap.*(.literal.multi_heap_internal_lock .text.multi_heap_internal_lock)
    *libheap.a:multi_heap.*(.literal.multi_heap_internal_unlock .text.multi_heap_internal_unlock)
    *libheap.a:multi_heap.*(.literal.multi_heap_is_free .text.multi_heap_is_free)
    *libheap.a:multi_heap.*(.literal.multi_heap_malloc_impl .text.multi_heap_malloc_impl)
    *libheap.a:multi_heap.*(.literal.multi_heap_realloc_impl .text.multi_heap_realloc_impl)
    *libheap.a:multi_heap.*(.literal.multi_heap_set_lock .text.multi_heap_set_lock)
    *libheap.a:tlsf.*(.literal.tlsf_align_size .text.tlsf_align_size)
    *libheap.a:tlsf.*(.literal.tlsf_alloc_overhead .text.tlsf_alloc_overhead)
    *libheap.a:tlsf.*(.literal.tlsf_block_size .text.tlsf_block_size)
    *libheap.a:tlsf.*(.literal.tlsf_block_size_max .text.tlsf_block_size_max)
    *libheap.a:tlsf.*(.literal.tlsf_block_size_min .text.tlsf_block_size_min)
    *libheap.a:tlsf.*(.literal.tlsf_free .text.tlsf_free)
    *libheap.a:tlsf.*(.literal.tlsf_get_pool .text.tlsf_get_pool)
    *libheap.a:tlsf.*(.literal.tlsf_malloc .text.tlsf_malloc)
    *libheap.a:tlsf.*(.literal.tlsf_memalign .text.tlsf_memalign)
    *libheap.a:tlsf.*(.literal.tlsf_memalign_offs .text.tlsf_memalign_offs)
    *libheap.a:tlsf.*(.literal.tlsf_realloc .text.tlsf_realloc)
    *libheap.a:tlsf.*(.literal.tlsf_size .text.tlsf_size)
    *liblog.a:log.*(.literal.esp_log_write .text.esp_log_write)
    *liblog.a:log_freertos.*(.literal.esp_log_early_timestamp .text.esp_log_early_timestamp)
    *liblog.a:log_freertos.*(.literal.esp_log_impl_lock .text.esp_log_impl_lock)
    *liblog.a:log_freertos.*(.literal.esp_log_impl_lock_timeout .text.esp_log_impl_lock_timeout)
    *liblog.a:log_freertos.*(.literal.esp_log_impl_unlock .text.esp_log_impl_unlock)
    *liblog.a:log_freertos.*(.literal.esp_log_timestamp .text.esp_log_timestamp)
    *libnet80211.a:(.wifi0iram .wifi0iram.*)
    *libnet80211.a:(.wifirxiram .wifirxiram.*)
    *libnet80211.a:(.wifislprxiram .wifislprxiram.*)
    *libnewlib.a:abort.*(.literal .literal.* .text .text.*)
    *libnewlib.a:assert.*(.literal .literal.* .text .text.*)
    *libnewlib.a:heap.*(.literal .literal.* .text .text.*)
    *libnewlib.a:stdatomic.*(.literal .literal.* .text .text.*)
    *libpp.a:(.wifi0iram .wifi0iram.*)
    *libpp.a:(.wifiorslpiram .wifiorslpiram.*)
    *libpp.a:(.wifirxiram .wifirxiram.*)
    *libpp.a:(.wifislprxiram .wifislprxiram.*)
    *librtc.a:(.literal .literal.* .text .text.*)
    *libsoc.a:lldesc.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:flash_brownout_hook.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:memspi_host_driver.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:spi_flash_chip_boya.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:spi_flash_chip_gd.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:spi_flash_chip_generic.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:spi_flash_chip_issi.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:spi_flash_chip_mxic.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:spi_flash_chip_th.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:spi_flash_chip_winbond.*(.literal .literal.* .text .text.*)
    *libspi_flash.a:spi_flash_wrap.*(.literal .literal.* .text .text.*)
    *libxt_hal.a:(.literal .literal.* .text .text.*)
    *libxtensa.a:eri.*(.literal .literal.* .text .text.*)
    *libxtensa.a:xtensa_intr_asm.*(.literal .literal.* .text .text.*)

  } > iram0_0_seg

  .dram0.data :
  {
    _data_start = ABSOLUTE(.);
    *(.gnu.linkonce.d.*)
    *(.data1)
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    *(.gnu.linkonce.s2.*)
    *(.jcr)

    *(.data .data.*)
    *(.dram1 .dram1.*)
    _coredump_dram_start = ABSOLUTE(.);
    *(.dram2.coredump .dram2.coredump.*)
    _coredump_dram_end = ABSOLUTE(.);
    *libapp_trace.a:app_trace.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libapp_trace.a:app_trace_util.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libapp_trace.a:port_uart.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:creat.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:isatty.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-abs.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-asctime.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-asctime_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-atoi.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-atol.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-bzero.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-close.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-creat.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-ctime.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-ctime_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-ctype_.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-div.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-environ.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-envlock.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-fclose.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-fflush.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-findfp.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-fputwc.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-fvwrite.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-fwalk.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-getenv_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-gettzinfo.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-gmtime.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-gmtime_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-impure.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isalnum.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isalpha.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isascii.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isblank.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-iscntrl.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isdigit.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isgraph.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-islower.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isprint.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-ispunct.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isspace.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-isupper.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-itoa.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-labs.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-lcltime.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-lcltime_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-ldiv.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-longjmp.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-makebuf.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-memccpy.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-memchr.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-memcmp.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-memcpy.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-memmove.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-memrchr.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-memset.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-mktime.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-month_lengths.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-open.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-quorem.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-raise.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-rand.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-rand_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-read.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-refill.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-rshift.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-s_fpclassify.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-sbrk.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-sccl.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-setjmp.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-sf_nan.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-srand.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-stdio.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strcasecmp.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strcasestr.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strcat.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strchr.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strcmp.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strcoll.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strcpy.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strcspn.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strdup.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strdup_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strftime.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strlcat.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strlcpy.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strlen.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strlwr.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strncasecmp.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strncat.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strncmp.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strncpy.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strndup.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strndup_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strnlen.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strptime.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strrchr.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strsep.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strspn.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strstr.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strtok_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strtol.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strtoul.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-strupr.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-sysclose.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-sysopen.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-sysread.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-syssbrk.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-system.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-systimes.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-syswrite.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-time.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-timelocal.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-toascii.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-tolower.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-toupper.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-tzcalc_limits.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-tzlock.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-tzset.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-tzset_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-tzvars.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-ungetc.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-utoa.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-wbuf.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-wcrtomb.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-wctomb_r.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lib_a-wsetup.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libc.a:lock.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libesp_hw_support.a:esp_memory_utils.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libesp_hw_support.a:rtc_clk.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libesp_mm.a:cache_esp32.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libesp_mm.a:esp_cache.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libesp_rom.a:esp_rom_spiflash.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libesp_system.a:esp_err.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libesp_system.a:ubsan.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libfreertos.a:FreeRTOS-openocd.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libgcov.a:(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:cache_hal_esp32.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:i2c_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:ledc_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:mmu_hal.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:spi_flash_encrypt_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:spi_flash_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:spi_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:spi_slave_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libhal.a:wdt_hal_iram.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libnewlib.a:abort.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libnewlib.a:assert.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libnewlib.a:heap.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libnewlib.a:stdatomic.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libphy.a:(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libsoc.a:lldesc.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:flash_brownout_hook.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:memspi_host_driver.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:spi_flash_chip_boya.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:spi_flash_chip_gd.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:spi_flash_chip_generic.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:spi_flash_chip_issi.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:spi_flash_chip_mxic.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:spi_flash_chip_th.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:spi_flash_chip_winbond.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)
    *libspi_flash.a:spi_flash_wrap.*(.rodata .rodata.* .sdata2 .sdata2.* .srodata .srodata.*)

    _data_end = ABSOLUTE(.);
    . = ALIGN(4);
  } > dram0_0_seg

  /**
   * This section holds data that won't be initialised when startup.
   * This section locates in External RAM region.
   */
  .ext_ram_noinit (NOLOAD) :
  {
    _ext_ram_noinit_start = ABSOLUTE(.);
    *(.ext_ram_noinit*)
    . = ALIGN(4);
    _ext_ram_noinit_end = ABSOLUTE(.);
  } > extern_ram_seg

  /*This section holds data that should not be initialized at power up.
    The section located in Internal SRAM memory region. The macro _NOINIT
    can be used as attribute to place data into this section.
    See the esp_attr.h file for more information.
  */
  .noinit (NOLOAD):
  {
    . = ALIGN(4);
    _noinit_start = ABSOLUTE(.);
    *(.noinit .noinit.*)
    . = ALIGN(4) ;
    _noinit_end = ABSOLUTE(.);
  } > dram0_0_seg

   /* external memory bss, from any global variable with EXT_RAM_BSS_ATTR attribute*/
  .ext_ram.bss (NOLOAD) :
  {
    _ext_ram_bss_start = ABSOLUTE(.);


    . = ALIGN(4);
    _ext_ram_bss_end = ABSOLUTE(.);
  } > extern_ram_seg

  /* Shared RAM */
  .dram0.bss (NOLOAD) :
  {
    . = ALIGN (8);
    _bss_start = ABSOLUTE(.);

    *(.bss .bss.*)
    *(.dynbss .dynsbss .gnu.linkonce.b .gnu.linkonce.b.* .gnu.linkonce.sb .gnu.linkonce.sb.* .gnu.linkonce.sb2 .gnu.linkonce.sb2.* .sbss .sbss.* .sbss2 .sbss2.* .scommon .share.mem)
    *(.ext_ram.bss .ext_ram.bss.*)
    *(COMMON)

    . = ALIGN (8);
    _bss_end = ABSOLUTE(.);
  } > dram0_0_seg

  ASSERT(((_bss_end - ORIGIN(dram0_0_seg)) <= LENGTH(dram0_0_seg)),
          "DRAM segment data does not fit.")

  .flash.appdesc : ALIGN(0x10)
  {
    _rodata_reserved_start = ABSOLUTE(.);  /* This is a symbol marking the flash.rodata start, this can be used for mmu driver to maintain virtual address */
    _rodata_start = ABSOLUTE(.);

    *(.rodata_desc .rodata_desc.*)               /* Should be the first.  App version info.        DO NOT PUT ANYTHING BEFORE IT! */
    *(.rodata_custom_desc .rodata_custom_desc.*) /* Should be the second. Custom app version info. DO NOT PUT ANYTHING BEFORE IT! */

    /* Create an empty gap within this section. Thanks to this, the end of this
     * section will match .flah.rodata's begin address. Thus, both sections
     * will be merged when creating the final bin image. */
    . = ALIGN(ALIGNOF(.flash.rodata));
  } >default_rodata_seg

  .flash.rodata : ALIGN(0x10)
  {
    _flash_rodata_start = ABSOLUTE(.);

    *(EXCLUDE_FILE(*libgcov.a *libphy.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:rtc_clk.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:ubsan.* *libfreertos.a:FreeRTOS-openocd.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:wdt_hal_iram.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.*) .rodata EXCLUDE_FILE(*libgcov.a *libphy.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:rtc_clk.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:ubsan.* *libfreertos.a:FreeRTOS-openocd.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:wdt_hal_iram.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.*) .rodata.* EXCLUDE_FILE(*libgcov.a *libphy.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:rtc_clk.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:ubsan.* *libfreertos.a:FreeRTOS-openocd.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:wdt_hal_iram.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.*) .sdata2 EXCLUDE_FILE(*libgcov.a *libphy.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:rtc_clk.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:ubsan.* *libfreertos.a:FreeRTOS-openocd.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:wdt_hal_iram.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.*) .sdata2.* EXCLUDE_FILE(*libgcov.a *libphy.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:rtc_clk.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:ubsan.* *libfreertos.a:FreeRTOS-openocd.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:wdt_hal_iram.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.*) .srodata EXCLUDE_FILE(*libgcov.a *libphy.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:rtc_clk.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:ubsan.* *libfreertos.a:FreeRTOS-openocd.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:wdt_hal_iram.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.*) .srodata.*)
    *(.rodata_wlog_error .rodata_wlog_error.*)
    *(.rodata_wlog_info .rodata_wlog_info.*)
    *(.rodata_wlog_warning .rodata_wlog_warning.*)


    *(.irom1.text) /* catch stray ICACHE_RODATA_ATTR */
    *(.gnu.linkonce.r.*)
    *(.rodata1)
    __XT_EXCEPTION_TABLE_ = ABSOLUTE(.);
    *(.xt_except_table)
    *(.gcc_except_table .gcc_except_table.*)
    *(.gnu.linkonce.e.*)
    *(.gnu.version_r)
    . = (. + 3) & ~ 3;
    __eh_frame = ABSOLUTE(.);
    KEEP(*(.eh_frame))
    . = (. + 7) & ~ 3;
    /*  C++ constructor and destructor tables

        Make a point of not including anything from crtbegin.o or crtend.o, as IDF doesn't use toolchain crt
      */
    __init_array_start = ABSOLUTE(.);
    KEEP (*(EXCLUDE_FILE (*crtend.* *crtbegin.*) .ctors SORT(.ctors.*)))
    __init_array_end = ABSOLUTE(.);

    KEEP (*crtbegin.*(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.*) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    /*  C++ exception handlers table:  */
    __XT_EXCEPTION_DESCS_ = ABSOLUTE(.);
    *(.xt_except_desc)
    *(.gnu.linkonce.h.*)
    __XT_EXCEPTION_DESCS_END__ = ABSOLUTE(.);
    *(.xt_except_desc_end)
    *(.dynamic)
    *(.gnu.version_d)
    /* Addresses of memory regions reserved via
       SOC_RESERVE_MEMORY_REGION() */
    soc_reserved_memory_region_start = ABSOLUTE(.);
    KEEP (*(.reserved_memory_address))
    soc_reserved_memory_region_end = ABSOLUTE(.);
    /* System init functions registered via ESP_SYSTEM_INIT_FN */
    _esp_system_init_fn_array_start = ABSOLUTE(.);
    KEEP (*(SORT_BY_INIT_PRIORITY(.esp_system_init_fn.*)))
    _esp_system_init_fn_array_end = ABSOLUTE(.);
    _rodata_end = ABSOLUTE(.);
    /* Literals are also RO data. */
    _lit4_start = ABSOLUTE(.);
    *(*.lit4)
    *(.lit4.*)
    *(.gnu.linkonce.lit4.*)
    _lit4_end = ABSOLUTE(.);
    . = ALIGN(4);
    _thread_local_start = ABSOLUTE(.);
    *(.tdata)
    *(.tdata.*)
    *(.tbss)
    *(.tbss.*)
    _thread_local_end = ABSOLUTE(.);
    . = ALIGN(4);
  } >default_rodata_seg

  _flash_rodata_align = ALIGNOF(.flash.rodata);

  /*
    This section is a place where we dump all the rodata which aren't used at runtime,
    so as to avoid binary size increase
  */
  .flash.rodata_noload (NOLOAD) :
  {
    /*
      This is a symbol marking the flash.rodata end, this can be used for mmu driver to maintain virtual address
      We don't need to include the noload rodata in this section
    */
    _rodata_reserved_end = ABSOLUTE(.);
    . = ALIGN (4);
    *(.rodata_wlog_debug .rodata_wlog_debug.*)
    *(.rodata_wlog_verbose .rodata_wlog_verbose.*)
  } > default_rodata_seg

  .flash.text :
  {
    _stext = .;
    _instruction_reserved_start = ABSOLUTE(.);  /* This is a symbol marking the flash.text start, this can be used for mmu driver to maintain virtual address */
    _text_start = ABSOLUTE(.);

    *(EXCLUDE_FILE(*libesp_ringbuf.a *libfreertos.a *libgcov.a *librtc.a *libxt_hal.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libdriver.a:gptimer.* *libesp_event.a:default_event_loop.* *libesp_event.a:esp_event.* *libesp_hw_support.a:cpu.* *libesp_hw_support.a:esp_gpio_reserve.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:periph_ctrl.* *libesp_hw_support.a:rtc_clk.* *libesp_hw_support.a:rtc_sleep.* *libesp_hw_support.a:rtc_time.* *libesp_hw_support.a:rtc_wdt.* *libesp_hw_support.a:sar_periph_ctrl.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:esp_system_chip.* *libesp_system.a:ubsan.* *libesp_wifi.a:esp_adapter.* *libesp_wifi.a:wifi_netif.* *libgcc.a:lib2funcs.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:timer_hal.* *libhal.a:wdt_hal_iram.* *libheap.a:multi_heap.* *libheap.a:tlsf.* *liblog.a:log.* *liblog.a:log_freertos.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.* *libxtensa.a:eri.* *libxtensa.a:xtensa_intr_asm.*) .literal EXCLUDE_FILE(*libesp_ringbuf.a *libfreertos.a *libgcov.a *librtc.a *libxt_hal.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libdriver.a:gptimer.* *libesp_event.a:default_event_loop.* *libesp_event.a:esp_event.* *libesp_hw_support.a:cpu.* *libesp_hw_support.a:esp_gpio_reserve.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:periph_ctrl.* *libesp_hw_support.a:rtc_clk.* *libesp_hw_support.a:rtc_sleep.* *libesp_hw_support.a:rtc_time.* *libesp_hw_support.a:rtc_wdt.* *libesp_hw_support.a:sar_periph_ctrl.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:esp_system_chip.* *libesp_system.a:ubsan.* *libesp_wifi.a:esp_adapter.* *libesp_wifi.a:wifi_netif.* *libgcc.a:lib2funcs.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:timer_hal.* *libhal.a:wdt_hal_iram.* *libheap.a:multi_heap.* *libheap.a:tlsf.* *liblog.a:log.* *liblog.a:log_freertos.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.* *libxtensa.a:eri.* *libxtensa.a:xtensa_intr_asm.*) .literal.* EXCLUDE_FILE(*libesp_ringbuf.a *libfreertos.a *libgcov.a *librtc.a *libxt_hal.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libdriver.a:gptimer.* *libesp_event.a:default_event_loop.* *libesp_event.a:esp_event.* *libesp_hw_support.a:cpu.* *libesp_hw_support.a:esp_gpio_reserve.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:periph_ctrl.* *libesp_hw_support.a:rtc_clk.* *libesp_hw_support.a:rtc_sleep.* *libesp_hw_support.a:rtc_time.* *libesp_hw_support.a:rtc_wdt.* *libesp_hw_support.a:sar_periph_ctrl.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:esp_system_chip.* *libesp_system.a:ubsan.* *libesp_wifi.a:esp_adapter.* *libesp_wifi.a:wifi_netif.* *libgcc.a:lib2funcs.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:timer_hal.* *libhal.a:wdt_hal_iram.* *libheap.a:multi_heap.* *libheap.a:tlsf.* *liblog.a:log.* *liblog.a:log_freertos.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.* *libxtensa.a:eri.* *libxtensa.a:xtensa_intr_asm.*) .text EXCLUDE_FILE(*libesp_ringbuf.a *libfreertos.a *libgcov.a *librtc.a *libxt_hal.a *libapp_trace.a:app_trace.* *libapp_trace.a:app_trace_util.* *libapp_trace.a:port_uart.* *libc.a:creat.* *libc.a:isatty.* *libc.a:lib_a-abs.* *libc.a:lib_a-asctime.* *libc.a:lib_a-asctime_r.* *libc.a:lib_a-atoi.* *libc.a:lib_a-atol.* *libc.a:lib_a-bzero.* *libc.a:lib_a-close.* *libc.a:lib_a-creat.* *libc.a:lib_a-ctime.* *libc.a:lib_a-ctime_r.* *libc.a:lib_a-ctype_.* *libc.a:lib_a-div.* *libc.a:lib_a-environ.* *libc.a:lib_a-envlock.* *libc.a:lib_a-fclose.* *libc.a:lib_a-fflush.* *libc.a:lib_a-findfp.* *libc.a:lib_a-fputwc.* *libc.a:lib_a-fvwrite.* *libc.a:lib_a-fwalk.* *libc.a:lib_a-getenv_r.* *libc.a:lib_a-gettzinfo.* *libc.a:lib_a-gmtime.* *libc.a:lib_a-gmtime_r.* *libc.a:lib_a-impure.* *libc.a:lib_a-isalnum.* *libc.a:lib_a-isalpha.* *libc.a:lib_a-isascii.* *libc.a:lib_a-isblank.* *libc.a:lib_a-iscntrl.* *libc.a:lib_a-isdigit.* *libc.a:lib_a-isgraph.* *libc.a:lib_a-islower.* *libc.a:lib_a-isprint.* *libc.a:lib_a-ispunct.* *libc.a:lib_a-isspace.* *libc.a:lib_a-isupper.* *libc.a:lib_a-itoa.* *libc.a:lib_a-labs.* *libc.a:lib_a-lcltime.* *libc.a:lib_a-lcltime_r.* *libc.a:lib_a-ldiv.* *libc.a:lib_a-longjmp.* *libc.a:lib_a-makebuf.* *libc.a:lib_a-memccpy.* *libc.a:lib_a-memchr.* *libc.a:lib_a-memcmp.* *libc.a:lib_a-memcpy.* *libc.a:lib_a-memmove.* *libc.a:lib_a-memrchr.* *libc.a:lib_a-memset.* *libc.a:lib_a-mktime.* *libc.a:lib_a-month_lengths.* *libc.a:lib_a-open.* *libc.a:lib_a-quorem.* *libc.a:lib_a-raise.* *libc.a:lib_a-rand.* *libc.a:lib_a-rand_r.* *libc.a:lib_a-read.* *libc.a:lib_a-refill.* *libc.a:lib_a-rshift.* *libc.a:lib_a-s_fpclassify.* *libc.a:lib_a-sbrk.* *libc.a:lib_a-sccl.* *libc.a:lib_a-setjmp.* *libc.a:lib_a-sf_nan.* *libc.a:lib_a-srand.* *libc.a:lib_a-stdio.* *libc.a:lib_a-strcasecmp.* *libc.a:lib_a-strcasestr.* *libc.a:lib_a-strcat.* *libc.a:lib_a-strchr.* *libc.a:lib_a-strcmp.* *libc.a:lib_a-strcoll.* *libc.a:lib_a-strcpy.* *libc.a:lib_a-strcspn.* *libc.a:lib_a-strdup.* *libc.a:lib_a-strdup_r.* *libc.a:lib_a-strftime.* *libc.a:lib_a-strlcat.* *libc.a:lib_a-strlcpy.* *libc.a:lib_a-strlen.* *libc.a:lib_a-strlwr.* *libc.a:lib_a-strncasecmp.* *libc.a:lib_a-strncat.* *libc.a:lib_a-strncmp.* *libc.a:lib_a-strncpy.* *libc.a:lib_a-strndup.* *libc.a:lib_a-strndup_r.* *libc.a:lib_a-strnlen.* *libc.a:lib_a-strptime.* *libc.a:lib_a-strrchr.* *libc.a:lib_a-strsep.* *libc.a:lib_a-strspn.* *libc.a:lib_a-strstr.* *libc.a:lib_a-strtok_r.* *libc.a:lib_a-strtol.* *libc.a:lib_a-strtoul.* *libc.a:lib_a-strupr.* *libc.a:lib_a-sysclose.* *libc.a:lib_a-sysopen.* *libc.a:lib_a-sysread.* *libc.a:lib_a-syssbrk.* *libc.a:lib_a-system.* *libc.a:lib_a-systimes.* *libc.a:lib_a-syswrite.* *libc.a:lib_a-time.* *libc.a:lib_a-timelocal.* *libc.a:lib_a-toascii.* *libc.a:lib_a-tolower.* *libc.a:lib_a-toupper.* *libc.a:lib_a-tzcalc_limits.* *libc.a:lib_a-tzlock.* *libc.a:lib_a-tzset.* *libc.a:lib_a-tzset_r.* *libc.a:lib_a-tzvars.* *libc.a:lib_a-ungetc.* *libc.a:lib_a-utoa.* *libc.a:lib_a-wbuf.* *libc.a:lib_a-wcrtomb.* *libc.a:lib_a-wctomb_r.* *libc.a:lib_a-wsetup.* *libc.a:lock.* *libdriver.a:gptimer.* *libesp_event.a:default_event_loop.* *libesp_event.a:esp_event.* *libesp_hw_support.a:cpu.* *libesp_hw_support.a:esp_gpio_reserve.* *libesp_hw_support.a:esp_memory_utils.* *libesp_hw_support.a:periph_ctrl.* *libesp_hw_support.a:rtc_clk.* *libesp_hw_support.a:rtc_sleep.* *libesp_hw_support.a:rtc_time.* *libesp_hw_support.a:rtc_wdt.* *libesp_hw_support.a:sar_periph_ctrl.* *libesp_mm.a:cache_esp32.* *libesp_mm.a:esp_cache.* *libesp_rom.a:esp_rom_spiflash.* *libesp_system.a:esp_err.* *libesp_system.a:esp_system_chip.* *libesp_system.a:ubsan.* *libesp_wifi.a:esp_adapter.* *libesp_wifi.a:wifi_netif.* *libgcc.a:lib2funcs.* *libhal.a:cache_hal_esp32.* *libhal.a:i2c_hal_iram.* *libhal.a:ledc_hal_iram.* *libhal.a:mmu_hal.* *libhal.a:spi_flash_encrypt_hal_iram.* *libhal.a:spi_flash_hal_iram.* *libhal.a:spi_hal_iram.* *libhal.a:spi_slave_hal_iram.* *libhal.a:timer_hal.* *libhal.a:wdt_hal_iram.* *libheap.a:multi_heap.* *libheap.a:tlsf.* *liblog.a:log.* *liblog.a:log_freertos.* *libnewlib.a:abort.* *libnewlib.a:assert.* *libnewlib.a:heap.* *libnewlib.a:stdatomic.* *libsoc.a:lldesc.* *libspi_flash.a:flash_brownout_hook.* *libspi_flash.a:memspi_host_driver.* *libspi_flash.a:spi_flash_chip_boya.* *libspi_flash.a:spi_flash_chip_gd.* *libspi_flash.a:spi_flash_chip_generic.* *libspi_flash.a:spi_flash_chip_issi.* *libspi_flash.a:spi_flash_chip_mxic.* *libspi_flash.a:spi_flash_chip_th.* *libspi_flash.a:spi_flash_chip_winbond.* *libspi_flash.a:spi_flash_wrap.* *libxtensa.a:eri.* *libxtensa.a:xtensa_intr_asm.*) .text.*)
    *(EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifi0iram EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifi0iram.*)
    *(.wifiextrairam .wifiextrairam.*)
    *(EXCLUDE_FILE(*libpp.a) .wifiorslpiram EXCLUDE_FILE(*libpp.a) .wifiorslpiram.*)
    *(EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifirxiram EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifirxiram.*)
    *(.wifislpiram .wifislpiram.*)
    *(EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifislprxiram EXCLUDE_FILE(*libnet80211.a *libpp.a) .wifislprxiram.*)
    *libdriver.a:gptimer.*(.literal.gptimer_acquire_group_handle .literal.gptimer_del_timer .literal.gptimer_destroy .literal.gptimer_disable .literal.gptimer_enable .literal.gptimer_get_captured_count .literal.gptimer_get_raw_count .literal.gptimer_get_resolution .literal.gptimer_new_timer .literal.gptimer_register_event_callbacks .literal.gptimer_register_to_group .literal.gptimer_release_group_handle .literal.gptimer_select_periph_clock .literal.gptimer_set_alarm_action .literal.gptimer_set_raw_count .literal.gptimer_start .literal.gptimer_stop .literal.gptimer_unregister_from_group .literal.timer_ll_set_clock_prescale .text .text.gptimer_acquire_group_handle .text.gptimer_del_timer .text.gptimer_destroy .text.gptimer_disable .text.gptimer_enable .text.gptimer_get_captured_count .text.gptimer_get_raw_count .text.gptimer_get_resolution .text.gptimer_new_timer .text.gptimer_register_event_callbacks .text.gptimer_register_to_group .text.gptimer_release_group_handle .text.gptimer_select_periph_clock .text.gptimer_set_alarm_action .text.gptimer_set_raw_count .text.gptimer_start .text.gptimer_stop .text.gptimer_unregister_from_group .text.timer_ll_set_clock_prescale)
    *libesp_event.a:default_event_loop.*(.literal.esp_event_handler_instance_register .literal.esp_event_handler_instance_unregister .literal.esp_event_handler_register .literal.esp_event_handler_unregister .literal.esp_event_loop_create_default .literal.esp_event_loop_delete_default .literal.esp_event_post .text .text.esp_event_handler_instance_register .text.esp_event_handler_instance_unregister .text.esp_event_handler_register .text.esp_event_handler_unregister .text.esp_event_loop_create_default .text.esp_event_loop_delete_default .text.esp_event_post)
    *libesp_event.a:esp_event.*(.literal.base_node_add_handler .literal.base_node_remove_all_handler .literal.base_node_remove_handler .literal.esp_event_handler_instance_register_with .literal.esp_event_handler_instance_unregister_with .literal.esp_event_handler_register_with .literal.esp_event_handler_register_with_internal .literal.esp_event_handler_unregister_with .literal.esp_event_handler_unregister_with_internal .literal.esp_event_loop_create .literal.esp_event_loop_delete .literal.esp_event_loop_run .literal.esp_event_loop_run_task .literal.esp_event_post_to .literal.handler_instances_add .literal.handler_instances_remove .literal.handler_instances_remove_all .literal.loop_node_add_handler .literal.loop_node_remove_all_handler .literal.loop_node_remove_handler .text .text.base_node_add_handler .text.base_node_remove_all_handler .text.base_node_remove_handler .text.esp_event_dump .text.esp_event_handler_instance_register_with .text.esp_event_handler_instance_unregister_with .text.esp_event_handler_register_with .text.esp_event_handler_register_with_internal .text.esp_event_handler_unregister_with .text.esp_event_handler_unregister_with_internal .text.esp_event_loop_create .text.esp_event_loop_delete .text.esp_event_loop_run .text.esp_event_loop_run_task .text.esp_event_post_to .text.handler_execute .text.handler_instances_add .text.handler_instances_remove .text.handler_instances_remove_all .text.loop_node_add_handler .text.loop_node_remove_all_handler .text.loop_node_remove_handler)
    *libesp_hw_support.a:cpu.*(.literal.esp_cpu_set_watchpoint .text .text.esp_cpu_clear_breakpoint .text.esp_cpu_clear_watchpoint .text.esp_cpu_set_breakpoint .text.esp_cpu_set_watchpoint)
    *libesp_hw_support.a:esp_gpio_reserve.*(.text)
    *libesp_hw_support.a:periph_ctrl.*(.literal.periph_ll_disable_clk_set_rst .literal.periph_ll_enable_clk_clear_rst .literal.periph_ll_get_clk_en_mask .literal.periph_ll_get_rst_en_mask .literal.periph_ll_reset .literal.periph_ll_wifi_module_disable_clk_set_rst .literal.periph_ll_wifi_module_enable_clk_clear_rst .literal.periph_module_disable .literal.periph_module_enable .text .text.periph_ll_disable_clk_set_rst .text.periph_ll_enable_clk_clear_rst .text.periph_ll_get_clk_en_mask .text.periph_ll_get_rst_en_mask .text.periph_ll_reset .text.periph_ll_wifi_module_disable_clk_set_rst .text.periph_ll_wifi_module_enable_clk_clear_rst .text.periph_module_disable .text.periph_module_enable)
    *libesp_hw_support.a:sar_periph_ctrl.*(.literal.s_sar_power_acquire .literal.s_sar_power_release .literal.sar_periph_ctrl_adc_continuous_power_acquire .literal.sar_periph_ctrl_adc_continuous_power_release .literal.sar_periph_ctrl_adc_oneshot_power_acquire .literal.sar_periph_ctrl_adc_oneshot_power_release .literal.sar_periph_ctrl_init .literal.sar_periph_ctrl_power_disable .literal.sar_periph_ctrl_pwdet_power_acquire .literal.sar_periph_ctrl_pwdet_power_release .text .text.s_sar_power_acquire .text.s_sar_power_release .text.sar_periph_ctrl_adc_continuous_power_acquire .text.sar_periph_ctrl_adc_continuous_power_release .text.sar_periph_ctrl_adc_oneshot_power_acquire .text.sar_periph_ctrl_adc_oneshot_power_release .text.sar_periph_ctrl_init .text.sar_periph_ctrl_power_disable .text.sar_periph_ctrl_pwdet_power_acquire .text.sar_periph_ctrl_pwdet_power_release)
    *libesp_system.a:esp_system_chip.*(.literal.esp_get_free_heap_size .literal.esp_get_free_internal_heap_size .literal.esp_get_idf_version .literal.esp_get_minimum_free_heap_size .text .text.esp_get_free_heap_size .text.esp_get_free_internal_heap_size .text.esp_get_idf_version .text.esp_get_minimum_free_heap_size)
    *libesp_wifi.a:esp_adapter.*(.literal.esp_cpu_intr_disable .literal.esp_cpu_intr_enable .literal.esp_event_post_wrapper .literal.esp_phy_disable_wrapper .literal.esp_phy_enable_wrapper .literal.event_group_wait_bits_wrapper .literal.get_time_wrapper .literal.mutex_create_wrapper .literal.mutex_delete_wrapper .literal.queue_create_wrapper .literal.queue_delete_wrapper .literal.queue_recv_wrapper .literal.queue_send_to_back_wrapper .literal.queue_send_to_front_wrapper .literal.queue_send_wrapper .literal.recursive_mutex_create_wrapper .literal.set_intr_wrapper .literal.set_isr_wrapper .literal.task_create_pinned_to_core_wrapper .literal.task_create_wrapper .literal.wifi_clock_disable_wrapper .literal.wifi_clock_enable_wrapper .literal.wifi_create_queue .literal.wifi_create_queue_wrapper .literal.wifi_delete_queue .literal.wifi_delete_queue_wrapper .literal.wifi_reset_mac_wrapper .literal.wifi_thread_semphr_free .literal.wifi_thread_semphr_get_wrapper .text .text.clear_intr_wrapper .text.coex_deinit_wrapper .text.coex_disable_wrapper .text.coex_enable_wrapper .text.coex_init_wrapper .text.coex_register_start_cb_wrapper .text.coex_schm_curr_period_get_wrapper .text.coex_schm_curr_phase_get_wrapper .text.coex_schm_flexible_period_get_wrapper .text.coex_schm_flexible_period_set_wrapper .text.coex_schm_interval_get_wrapper .text.coex_schm_process_restart_wrapper .text.coex_schm_register_cb_wrapper .text.coex_schm_status_bit_clear_wrapper .text.coex_schm_status_bit_set_wrapper .text.coex_wifi_channel_set_wrapper .text.coex_wifi_request_wrapper .text.esp_cpu_intr_disable .text.esp_cpu_intr_enable .text.esp_event_post_wrapper .text.esp_phy_disable_wrapper .text.esp_phy_enable_wrapper .text.event_group_wait_bits_wrapper .text.get_time_wrapper .text.mutex_create_wrapper .text.mutex_delete_wrapper .text.queue_create_wrapper .text.queue_delete_wrapper .text.queue_recv_wrapper .text.queue_send_to_back_wrapper .text.queue_send_to_front_wrapper .text.queue_send_wrapper .text.recursive_mutex_create_wrapper .text.set_intr_wrapper .text.set_isr_wrapper .text.task_create_pinned_to_core_wrapper .text.task_create_wrapper .text.task_get_max_priority_wrapper .text.wifi_clock_disable_wrapper .text.wifi_clock_enable_wrapper .text.wifi_create_queue .text.wifi_create_queue_wrapper .text.wifi_delete_queue .text.wifi_delete_queue_wrapper .text.wifi_reset_mac_wrapper .text.wifi_thread_semphr_free .text.wifi_thread_semphr_get_wrapper)
    *libesp_wifi.a:wifi_netif.*(.literal.esp_wifi_create_if_driver .literal.esp_wifi_destroy_if_driver .literal.esp_wifi_get_if_mac .literal.esp_wifi_register_if_rxcb .literal.wifi_ap_receive .literal.wifi_driver_start .literal.wifi_free .literal.wifi_transmit .text .text.esp_wifi_create_if_driver .text.esp_wifi_destroy_if_driver .text.esp_wifi_get_if_mac .text.esp_wifi_is_if_ready_when_started .text.esp_wifi_register_if_rxcb .text.wifi_ap_receive .text.wifi_driver_start .text.wifi_free .text.wifi_transmit)
    *libfreertos.a:app_startup.*(.literal .literal.* .text .text.*)
    *libfreertos.a:idf_additions.*(.literal .literal.* .text .text.*)
    *libhal.a:timer_hal.*(.literal.timer_hal_deinit .literal.timer_hal_init .text .text.timer_hal_deinit .text.timer_hal_init .text.timer_hal_set_counter_value)
    *libheap.a:multi_heap.*(.literal.multi_heap_check .literal.multi_heap_dump .literal.multi_heap_dump_tlsf .literal.multi_heap_get_info_impl .literal.multi_heap_register_impl .text .text.multi_heap_check .text.multi_heap_dump .text.multi_heap_dump_tlsf .text.multi_heap_free_size_impl .text.multi_heap_get_block_owner .text.multi_heap_get_info_impl .text.multi_heap_get_info_tlsf .text.multi_heap_minimum_free_size_impl .text.multi_heap_register_impl)
    *libheap.a:tlsf.*(.literal.control_construct .literal.default_walker .literal.integrity_walker .literal.tlsf_add_pool .literal.tlsf_check .literal.tlsf_check_pool .literal.tlsf_create .literal.tlsf_create_with_pool .literal.tlsf_fit_size .literal.tlsf_remove_pool .literal.tlsf_walk_pool .text .text.control_construct .text.default_walker .text.integrity_walker .text.tlsf_add_pool .text.tlsf_check .text.tlsf_check_pool .text.tlsf_create .text.tlsf_create_with_pool .text.tlsf_destroy .text.tlsf_fit_size .text.tlsf_pool_overhead .text.tlsf_remove_pool .text.tlsf_walk_pool)
    *liblog.a:log.*(.literal.add_to_cache .literal.clear_log_level_list .literal.esp_log_level_get .literal.esp_log_level_set .literal.esp_log_set_vprintf .literal.esp_log_writev .literal.fix_cache_generation_overflow .literal.get_cached_log_level .literal.get_uncached_log_level .literal.heap_bubble_down .literal.heap_swap .literal.s_log_level_get_and_unlock .text .text.add_to_cache .text.clear_log_level_list .text.esp_log_level_get .text.esp_log_level_set .text.esp_log_set_vprintf .text.esp_log_writev .text.fix_cache_generation_overflow .text.get_cached_log_level .text.get_uncached_log_level .text.heap_bubble_down .text.heap_swap .text.s_log_level_get_and_unlock)
    *liblog.a:log_freertos.*(.literal.esp_log_system_timestamp .text .text.esp_log_system_timestamp)

    *(.stub .gnu.warning .gnu.linkonce.literal.* .gnu.linkonce.t.*.literal .gnu.linkonce.t.*)
    *(.irom0.text) /* catch stray ICACHE_RODATA_ATTR */
    *(.fini.literal)
    *(.fini)
    *(.gnu.version)

    /** CPU will try to prefetch up to 16 bytes of
      * of instructions. This means that any configuration (e.g. MMU, PMS) must allow
      * safe access to up to 16 bytes after the last real instruction, add
      * dummy bytes to ensure this
      */
    . += _esp_flash_mmap_prefetch_pad_size;

    _text_end = ABSOLUTE(.);
    _instruction_reserved_end = ABSOLUTE(.);  /* This is a symbol marking the flash.text end, this can be used for mmu driver to maintain virtual address */
    _etext = .;

    /* Similar to _iram_start, this symbol goes here so it is
       resolved by addr2line in preference to the first symbol in
       the flash.text segment.
    */
    _flash_cache_start = ABSOLUTE(0);
  } >default_code_seg

  /* Marks the end of IRAM code segment */
  .iram0.text_end (NOLOAD) :
  {
    . = ALIGN (4);
    _iram_text_end = ABSOLUTE(.);
  } > iram0_0_seg

  .iram0.data :
  {
    . = ALIGN(4);
    _iram_data_start = ABSOLUTE(.);

    *(.iram.data .iram.data.*)
    _coredump_iram_start = ABSOLUTE(.);
    *(.iram2.coredump .iram2.coredump.*)
    _coredump_iram_end = ABSOLUTE(.);

    _iram_data_end = ABSOLUTE(.);
  } > iram0_0_seg

  .iram0.bss (NOLOAD) :
  {
    . = ALIGN(4);
    _iram_bss_start = ABSOLUTE(.);

    *(.iram.bss .iram.bss.*)

    _iram_bss_end = ABSOLUTE(.);
    . = ALIGN(4);
    _iram_end = ABSOLUTE(.);
   } > iram0_0_seg

  /* Marks the end of data, bss and possibly rodata  */
  .dram0.heap_start (NOLOAD) :
  {
    . = ALIGN (8);
    /* Lowest possible start address for the heap */
    _heap_low_start = ABSOLUTE(.);
  } > dram0_0_seg

  /** This section will be used by the debugger and disassembler to get more information
    * about raw data present in the code.
    * Indeed, it may be required to add some padding at some points in the code
    * in order to align a branch/jump destination on a particular bound.
    * Padding these instructions will generate null bytes that shall be
    * interpreted as data, and not code by the debugger or disassembler.
    * This section will only be present in the ELF file, not in the final binary
    * For more details, check GCC-212
    */
  .xt.prop 0 :
  {
    KEEP (*(.xt.prop .gnu.linkonce.prop.*))
  }

  .xt.lit 0 :
  {
    KEEP (*(.xt.lit .gnu.linkonce.p.*))
  }
}

ASSERT(((_iram_end - ORIGIN(iram0_0_seg)) <= LENGTH(iram0_0_seg)),
          "IRAM0 segment data does not fit.")

ASSERT(((_heap_low_start - ORIGIN(dram0_0_seg)) <= LENGTH(dram0_0_seg)),
          "DRAM segment data does not fit.")
