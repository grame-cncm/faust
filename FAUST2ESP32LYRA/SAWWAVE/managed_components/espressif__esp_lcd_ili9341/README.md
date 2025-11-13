# ESP LCD ILI9341

[![Component Registry](https://components.espressif.com/components/espressif/esp_lcd_ili9341/badge.svg)](https://components.espressif.com/components/espressif/esp_lcd_ili9341)

Implementation of the ILI9341 LCD controller with esp_lcd component.

| LCD controller | Communication interface | Component name | Link to datasheet |
| :------------: | :---------------------: | :------------: | :---------------: |
| ILI9341        | SPI                     | esp_lcd_ili9341     | [Specification](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf) |

## Add to project

Packages from this repository are uploaded to [Espressif's component service](https://components.espressif.com/).
You can add them to your project via `idf.py add-dependancy`, e.g.
```
    idf.py add-dependency esp_lcd_ili9341==1.0.0
```

Alternatively, you can create `idf_component.yml`. More is in [Espressif's documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/tools/idf-component-manager.html).

## Example use

```c
    ESP_LOGI(TAG, "Initialize SPI bus");
    const spi_bus_config_t bus_config = ILI9341_PANEL_BUS_SPI_CONFIG(EXAMPLE_PIN_NUM_LCD_PCLK, EXAMPLE_PIN_NUM_LCD_MOSI,
                                                                     EXAMPLE_LCD_H_RES * 80 * sizeof(uint16_t));
    ESP_ERROR_CHECK(spi_bus_initialize(EXAMPLE_LCD_HOST, &bus_config, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_handle_t io_handle = NULL;
    const esp_lcd_panel_io_spi_config_t io_config = ILI9341_PANEL_IO_SPI_CONFIG(EXAMPLE_PIN_NUM_LCD_CS, EXAMPLE_PIN_NUM_LCD_DC,
                                                                                example_callback, &example_callback_ctx);
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)EXAMPLE_LCD_HOST, &io_config, &io_handle));

/**
 * Uncomment these lines if use custom initialization commands.
 * The array should be declared as static const and positioned outside the function.
 */
// static const ili9341_lcd_init_cmd_t lcd_init_cmds[] = {
// // {cmd, { data }, data_size, delay_ms}
//    {0xCF, (uint8_t []){0x00, 0xAA, 0XE0}, 3, 0},
//    {0xED, (uint8_t []){0x67, 0x03, 0X12, 0X81}, 4, 0},
//    {0xE8, (uint8_t []){0x8A, 0x01, 0x78}, 3, 0},
//     ...
// };

    ESP_LOGI(TAG, "Install ILI9341 panel driver");
    esp_lcd_panel_handle_t panel_handle = NULL;
    // const ili9341_vendor_config_t vendor_config = {  // Uncomment these lines if use custom initialization commands
    //     .init_cmds = lcd_init_cmds,
    //     .init_cmds_size = sizeof(lcd_init_cmds) / sizeof(ili9341_lcd_init_cmd_t),
    // };
    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = EXAMPLE_PIN_NUM_LCD_RST,      // Set to -1 if not use
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)      // Implemented by LCD command `36h`
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
#else
        .rgb_endian = LCD_RGB_ENDIAN_RGB,
#endif
        .bits_per_pixel = 16,                           // Implemented by LCD command `3Ah` (16/18)
        // .vendor_config = &vendor_config,            // Uncomment this line if use custom initialization commands
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    ESP_ERROR_CHECK(esp_lcd_panel_disp_off(panel_handle, false));
#else
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
#endif
```

There is an example in ESP-IDF with this LCD controller. Please follow this [link](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/lcd/spi_lcd_touch).
