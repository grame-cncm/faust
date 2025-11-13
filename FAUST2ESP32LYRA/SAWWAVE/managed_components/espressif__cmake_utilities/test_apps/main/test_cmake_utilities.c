/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_log.h"
#include "unity.h"
#include "test_component1.h"
#include "test_component2.h"


/* USB PIN fixed in esp32-s2, can not use io matrix */
#define TEST_MEMORY_LEAK_THRESHOLD (-400)

TEST_CASE("Test package manager version", "[cmake_utilities][package_manager]")
{
    esp_log_level_set("*", ESP_LOG_INFO);
    TEST_ASSERT_EQUAL_INT(test_component1_version_major(), 1);
    TEST_ASSERT_EQUAL_INT(test_component1_version_minor(), 2);
    TEST_ASSERT_EQUAL_INT(test_component1_version_patch(), 3);
    TEST_ASSERT_EQUAL_INT(test_component2_version_major(), 3);
    TEST_ASSERT_EQUAL_INT(test_component2_version_minor(), 2);
    TEST_ASSERT_EQUAL_INT(test_component2_version_patch(), 1);
}

static size_t before_free_8bit;
static size_t before_free_32bit;

static void check_leak(size_t before_free, size_t after_free, const char *type)
{
    ssize_t delta = after_free - before_free;
    printf("MALLOC_CAP_%s: Before %u bytes free, After %u bytes free (delta %d)\n", type, before_free, after_free, delta);
    TEST_ASSERT_MESSAGE(delta >= TEST_MEMORY_LEAK_THRESHOLD, "memory leak");
}

void setUp(void)
{
    before_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    before_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
}

void tearDown(void)
{
    size_t after_free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t after_free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
    check_leak(before_free_8bit, after_free_8bit, "8BIT");
    check_leak(before_free_32bit, after_free_32bit, "32BIT");
}

void app_main(void)
{
    printf("Cmake Utilities TEST \n");
    unity_run_menu();
}
