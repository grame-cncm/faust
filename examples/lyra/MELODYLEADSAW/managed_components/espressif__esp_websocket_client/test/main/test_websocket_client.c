/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 *
 * This test code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <esp_websocket_client.h>
#include "esp_event.h"
#include "unity.h"
#include "test_utils.h"

#include "unity_fixture.h"
#include "memory_checks.h"

TEST_GROUP(websocket);

TEST_SETUP(websocket)
{
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 1, 0)
    /* IDF v5.0 runs some lazy inits within printf()
     * This test sets the leak threshold to 0, so we need to call printf()
     * before recording the heap size in test_utils_record_free_mem()
     */
    printf("TEST_SETUP: websocket\n");
#endif
    test_utils_record_free_mem();
    TEST_ESP_OK(test_utils_set_leak_level(0, ESP_LEAK_TYPE_CRITICAL, ESP_COMP_LEAK_GENERAL));
}

TEST_TEAR_DOWN(websocket)
{
    test_utils_finish_and_evaluate_leaks(0, 0);
}


TEST(websocket, websocket_init_deinit)
{
    const esp_websocket_client_config_t websocket_cfg = {
        // no connection takes place, but the uri has to be valid for init() to succeed
        .uri = "ws://echo.websocket.org",
    };
    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    TEST_ASSERT_NOT_EQUAL(NULL, client);
    esp_websocket_client_destroy(client);
}

TEST(websocket, websocket_init_invalid_url)
{
    const esp_websocket_client_config_t websocket_cfg = {
        .uri = "INVALID",
    };
    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    TEST_ASSERT_NULL(client);
}

TEST(websocket, websocket_set_invalid_url)
{
    const esp_websocket_client_config_t websocket_cfg = {};
    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    TEST_ASSERT_NOT_EQUAL(NULL, client);
    TEST_ASSERT_NOT_EQUAL(ESP_OK, esp_websocket_client_set_uri(client, "INVALID"));
    esp_websocket_client_destroy(client);
}

TEST_GROUP_RUNNER(websocket)
{
    RUN_TEST_CASE(websocket, websocket_init_deinit)
    RUN_TEST_CASE(websocket, websocket_init_invalid_url)
    RUN_TEST_CASE(websocket, websocket_set_invalid_url)
}

void app_main(void)
{
    UNITY_MAIN(websocket);
}
