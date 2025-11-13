/*
 * SPDX-FileCopyrightText: 2015-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

#include "esp_websocket_client.h"
#include "esp_transport.h"
#include "esp_transport_tcp.h"
#include "esp_transport_ssl.h"
/* using uri parser */
#include "http_parser.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_tls_crypto.h"
#include "esp_system.h"
#include <errno.h>
#include <arpa/inet.h>

static const char *TAG = "websocket_client";

#define WEBSOCKET_TCP_DEFAULT_PORT      (80)
#define WEBSOCKET_SSL_DEFAULT_PORT      (443)
#define WEBSOCKET_BUFFER_SIZE_BYTE      (1024)
#define WEBSOCKET_RECONNECT_TIMEOUT_MS  (10*1000)
#define WEBSOCKET_TASK_PRIORITY         (5)
#define WEBSOCKET_TASK_STACK            (4*1024)
#define WEBSOCKET_NETWORK_TIMEOUT_MS    (10*1000)
#define WEBSOCKET_PING_INTERVAL_SEC     (10)
#define WEBSOCKET_EVENT_QUEUE_SIZE      (1)
#define WEBSOCKET_PINGPONG_TIMEOUT_SEC  (120)
#define WEBSOCKET_KEEP_ALIVE_IDLE       (5)
#define WEBSOCKET_KEEP_ALIVE_INTERVAL   (5)
#define WEBSOCKET_KEEP_ALIVE_COUNT      (3)

#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
#define WEBSOCKET_TX_LOCK_TIMEOUT_MS    (CONFIG_ESP_WS_CLIENT_TX_LOCK_TIMEOUT_MS)
#endif

#define ESP_WS_CLIENT_MEM_CHECK(TAG, a, action) if (!(a)) {                                         \
        ESP_LOGE(TAG,"%s(%d): %s", __FUNCTION__, __LINE__, "Memory exhausted");                     \
        action;                                                                                     \
        }

#define ESP_WS_CLIENT_ERR_OK_CHECK(TAG, err, action)  { \
        esp_err_t _esp_ws_err_to_check = err;           \
        if (_esp_ws_err_to_check != ESP_OK) {           \
            ESP_LOGE(TAG,"%s(%d): Expected ESP_OK; reported: %d", __FUNCTION__, __LINE__, _esp_ws_err_to_check); \
            action;                                     \
            }                                           \
        }

#define ESP_WS_CLIENT_STATE_CHECK(TAG, a, action) if ((a->state) < WEBSOCKET_STATE_INIT) {                                         \
        ESP_LOGE(TAG,"%s(%d): %s", __FUNCTION__, __LINE__, "Websocket already stop"); \
        action;                                                                                     \
        }

#define WS_OVER_TCP_SCHEME  "ws"
#define WS_OVER_TLS_SCHEME  "wss"
#define WS_HTTP_BASIC_AUTH  "Basic "

const static int STOPPED_BIT = BIT0;
const static int CLOSE_FRAME_SENT_BIT = BIT1;   // Indicates that a close frame was sent by the client
// and we are waiting for the server to continue with clean close

ESP_EVENT_DEFINE_BASE(WEBSOCKET_EVENTS);

typedef struct {
    const char                 *task_name;
    int                         task_stack;
    int                         task_prio;
    char                        *uri;
    char                        *host;
    char                        *path;
    char                        *scheme;
    char                        *username;
    char                        *password;
    char                        *auth;
    int                         port;
    bool                        auto_reconnect;
    bool                        close_reconnect;
    void                        *user_context;
    int                         network_timeout_ms;
    char                        *subprotocol;
    char                        *user_agent;
    char                        *headers;
    int                         pingpong_timeout_sec;
    size_t                      ping_interval_sec;
    const char                  *cert;
    size_t                      cert_len;
    const char                  *client_cert;
    size_t                      client_cert_len;
    const char                  *client_key;
    size_t                      client_key_len;
#if CONFIG_ESP_TLS_USE_DS_PERIPHERAL
    void                        *client_ds_data;
#endif
    bool                        use_global_ca_store;
    bool                        skip_cert_common_name_check;
    const char                  *cert_common_name;
    esp_err_t (*crt_bundle_attach)(void *conf);
    esp_transport_handle_t      ext_transport;
} websocket_config_storage_t;

typedef enum {
    WEBSOCKET_STATE_ERROR = -1,
    WEBSOCKET_STATE_UNKNOW = 0,
    WEBSOCKET_STATE_INIT,
    WEBSOCKET_STATE_CONNECTED,
    WEBSOCKET_STATE_WAIT_TIMEOUT,
    WEBSOCKET_STATE_CLOSING,
} websocket_client_state_t;

struct esp_websocket_client {
    esp_event_loop_handle_t     event_handle;
    TaskHandle_t                task_handle;
    esp_websocket_error_codes_t error_handle;
    esp_transport_list_handle_t transport_list;
    esp_transport_handle_t      transport;
    websocket_config_storage_t *config;
    websocket_client_state_t    state;
    uint64_t                    keepalive_tick_ms;
    uint64_t                    reconnect_tick_ms;
    uint64_t                    ping_tick_ms;
    uint64_t                    pingpong_tick_ms;
    int                         wait_timeout_ms;
    bool                        run;
    bool                        wait_for_pong_resp;
    bool                        selected_for_destroying;
    EventGroupHandle_t          status_bits;
    SemaphoreHandle_t           lock;
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
    SemaphoreHandle_t           tx_lock;
#endif
    size_t                      errormsg_size;
    char                        *errormsg_buffer;
    char                        *rx_buffer;
    char                        *tx_buffer;
    int                         buffer_size;
    bool                        last_fin;
    ws_transport_opcodes_t      last_opcode;
    int                         payload_len;
    int                         payload_offset;
    esp_transport_keep_alive_t  keep_alive_cfg;
    struct ifreq                *if_name;
};

static uint64_t _tick_get_ms(void)
{
    return esp_timer_get_time() / 1000;
}

static esp_err_t esp_websocket_new_buf(esp_websocket_client_handle_t client, bool is_tx)
{
#ifdef CONFIG_ESP_WS_CLIENT_ENABLE_DYNAMIC_BUFFER
    if (is_tx) {
        if (client->tx_buffer) {
            free(client->tx_buffer);
        }

        client->tx_buffer = calloc(1, client->buffer_size);
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->tx_buffer, return ESP_ERR_NO_MEM);
    } else {
        if (client->rx_buffer) {
            free(client->rx_buffer);
        }

        client->rx_buffer = calloc(1, client->buffer_size);
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->rx_buffer, return ESP_ERR_NO_MEM);
    }
#endif
    return ESP_OK;
}

static void esp_websocket_free_buf(esp_websocket_client_handle_t client, bool is_tx)
{
#ifdef CONFIG_ESP_WS_CLIENT_ENABLE_DYNAMIC_BUFFER
    if (is_tx) {
        if (client->tx_buffer) {
            free(client->tx_buffer);
            client->tx_buffer = NULL;
        }
    } else {
        if (client->rx_buffer) {
            free(client->rx_buffer);
            client->rx_buffer = NULL;
        }
    }
#endif
}

static esp_err_t esp_websocket_client_dispatch_event(esp_websocket_client_handle_t client,
                                                     esp_websocket_event_id_t event,
                                                     const char *data,
                                                     int data_len)
{
    esp_err_t err;
    esp_websocket_event_data_t event_data;

    event_data.client = client;
    event_data.user_context = client->config->user_context;
    event_data.data_ptr = data;
    event_data.data_len = data_len;
    event_data.fin = client->last_fin;
    event_data.op_code = client->last_opcode;
    event_data.payload_len = client->payload_len;
    event_data.payload_offset = client->payload_offset;

    if (client->error_handle.error_type == WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT) {
        event_data.error_handle.esp_tls_last_esp_err = esp_tls_get_and_clear_last_error(esp_transport_get_error_handle(client->transport),
                                                                                        &client->error_handle.esp_tls_stack_err,
                                                                                        &client->error_handle.esp_tls_cert_verify_flags);
        event_data.error_handle.esp_tls_stack_err = client->error_handle.esp_tls_stack_err;
        event_data.error_handle.esp_tls_cert_verify_flags = client->error_handle.esp_tls_cert_verify_flags;
        event_data.error_handle.esp_transport_sock_errno = esp_transport_get_errno(client->transport);
    }
    event_data.error_handle.error_type = client->error_handle.error_type;
    event_data.error_handle.esp_ws_handshake_status_code = client->error_handle.esp_ws_handshake_status_code;


    if ((err = esp_event_post_to(client->event_handle,
                                 WEBSOCKET_EVENTS, event,
                                 &event_data,
                                 sizeof(esp_websocket_event_data_t),
                                 portMAX_DELAY)) != ESP_OK) {
        return err;
    }
    return esp_event_loop_run(client->event_handle, 0);
}

static esp_err_t esp_websocket_client_abort_connection(esp_websocket_client_handle_t client, esp_websocket_error_type_t error_type)
{
    ESP_WS_CLIENT_STATE_CHECK(TAG, client, return ESP_FAIL);
    esp_transport_close(client->transport);

    if (!client->config->auto_reconnect) {
        client->run = false;
        client->state = WEBSOCKET_STATE_UNKNOW;
    } else {
        client->reconnect_tick_ms = _tick_get_ms();
        ESP_LOGI(TAG, "Reconnect after %d ms", client->wait_timeout_ms);
        client->state = WEBSOCKET_STATE_WAIT_TIMEOUT;
    }
    client->error_handle.error_type = error_type;
    esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_DISCONNECTED, NULL, 0);
    return ESP_OK;
}

static esp_err_t esp_websocket_client_error(esp_websocket_client_handle_t client, const char *format, ...) __attribute__((format(printf, 2, 3)));
static esp_err_t esp_websocket_client_error(esp_websocket_client_handle_t client, const char *format, ...)
{
    va_list myargs;
    va_start(myargs, format);

    size_t needed_size = vsnprintf(NULL, 0, format, myargs);
    needed_size++; // null terminator

    if (needed_size > client->errormsg_size) {
        if (client->errormsg_buffer) {
            free(client->errormsg_buffer);
        }
        client->errormsg_buffer = malloc(needed_size);
        if (client->errormsg_buffer == NULL) {
            client->errormsg_size = 0;
            ESP_LOGE(TAG, "Failed to allocate...");
            return ESP_ERR_NO_MEM;
        }
        client->errormsg_size = needed_size;
    }

    needed_size = vsnprintf(client->errormsg_buffer, client->errormsg_size, format, myargs);

    va_end(myargs);

    ESP_LOGE(TAG, "%s", client->errormsg_buffer);

    esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_ERROR, client->errormsg_buffer, needed_size);
    return ESP_OK;
}

static char *http_auth_basic(const char *username, const char *password)
{
    int out;
    char *user_info = NULL;
    char *digest = NULL;
    size_t n = 0;

    if (asprintf(&user_info, "%s:%s", username, password) < 0) {
        return NULL;
    }

    if (!user_info) {
        ESP_LOGE(TAG, "No enough memory for user information");
        return NULL;
    }

    esp_crypto_base64_encode(NULL, 0, &n, (const unsigned char *)user_info, strlen(user_info));
    digest = calloc(1, strlen(WS_HTTP_BASIC_AUTH) + n + 1);
    if (digest) {
        strcpy(digest, WS_HTTP_BASIC_AUTH);
        esp_crypto_base64_encode((unsigned char *)digest + 6, n, (size_t *)&out, (const unsigned char *)user_info, strlen(user_info));
    }
    free(user_info);
    return digest;
}

static esp_err_t esp_websocket_client_set_config(esp_websocket_client_handle_t client, const esp_websocket_client_config_t *config)
{
    websocket_config_storage_t *cfg = client->config;
    cfg->task_prio = config->task_prio;
    if (cfg->task_prio <= 0) {
        cfg->task_prio = WEBSOCKET_TASK_PRIORITY;
    }

    cfg->task_name = config->task_name;

    cfg->task_stack = config->task_stack;
    if (cfg->task_stack == 0) {
        cfg->task_stack = WEBSOCKET_TASK_STACK;
    }

    if (config->host) {
        cfg->host = strdup(config->host);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->host, return ESP_ERR_NO_MEM);
    }

    if (config->port) {
        cfg->port = config->port;
    }

    if (config->username) {
        free(cfg->username);
        cfg->username = strdup(config->username);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->username, return ESP_ERR_NO_MEM);
    }

    if (config->password) {
        free(cfg->password);
        cfg->password = strdup(config->password);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->password, return ESP_ERR_NO_MEM);
    }

    if (cfg->username && cfg->password) {
        free(cfg->auth);
        cfg->auth = http_auth_basic(cfg->username, cfg->password);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->auth, return ESP_ERR_NO_MEM);
    }

    if (config->uri) {
        free(cfg->uri);
        cfg->uri = strdup(config->uri);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->uri, return ESP_ERR_NO_MEM);
    }
    if (config->path) {
        free(cfg->path);
        cfg->path = strdup(config->path);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->path, return ESP_ERR_NO_MEM);
    }
    if (config->subprotocol) {
        free(cfg->subprotocol);
        cfg->subprotocol = strdup(config->subprotocol);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->subprotocol, return ESP_ERR_NO_MEM);
    }
    if (config->user_agent) {
        free(cfg->user_agent);
        cfg->user_agent = strdup(config->user_agent);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->user_agent, return ESP_ERR_NO_MEM);
    }
    if (config->headers) {
        free(cfg->headers);
        cfg->headers = strdup(config->headers);
        ESP_WS_CLIENT_MEM_CHECK(TAG, cfg->headers, return ESP_ERR_NO_MEM);
    }


    cfg->user_context = config->user_context;
    cfg->auto_reconnect = true;
    if (config->disable_auto_reconnect) {
        cfg->auto_reconnect = false;
    }
    cfg->close_reconnect = config->enable_close_reconnect;

    if (config->disable_pingpong_discon) {
        cfg->pingpong_timeout_sec = 0;
    } else if (config->pingpong_timeout_sec) {
        cfg->pingpong_timeout_sec = config->pingpong_timeout_sec;
    } else {
        cfg->pingpong_timeout_sec = WEBSOCKET_PINGPONG_TIMEOUT_SEC;
    }

    if (config->network_timeout_ms <= 0) {
        cfg->network_timeout_ms = WEBSOCKET_NETWORK_TIMEOUT_MS;
        ESP_LOGW(TAG, "`network_timeout_ms` is not set, or it is less than or equal to zero, using default time out %d (milliseconds)", WEBSOCKET_NETWORK_TIMEOUT_MS);
    } else {
        cfg->network_timeout_ms = config->network_timeout_ms;
    }

    if (config->ping_interval_sec == 0) {
        cfg->ping_interval_sec = WEBSOCKET_PING_INTERVAL_SEC;
    } else {
        cfg->ping_interval_sec = config->ping_interval_sec;
    }

    return ESP_OK;
}

static esp_err_t esp_websocket_client_destroy_config(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    websocket_config_storage_t *cfg = client->config;
    if (client->config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    free(cfg->host);
    free(cfg->uri);
    free(cfg->path);
    free(cfg->scheme);
    free(cfg->username);
    free(cfg->password);
    free(cfg->auth);
    free(cfg->subprotocol);
    free(cfg->user_agent);
    free(cfg->headers);
    memset(cfg, 0, sizeof(websocket_config_storage_t));
    free(client->config);
    client->config = NULL;
    return ESP_OK;
}

static void destroy_and_free_resources(esp_websocket_client_handle_t client)
{
    if (client->event_handle) {
        esp_event_loop_delete(client->event_handle);
    }
    if (client->if_name) {
        free(client->if_name);
    }
    esp_websocket_client_destroy_config(client);
    if (client->transport_list) {
        esp_transport_list_destroy(client->transport_list);
    }
    vSemaphoreDelete(client->lock);
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
    vSemaphoreDelete(client->tx_lock);
#endif
    free(client->tx_buffer);
    free(client->rx_buffer);
    free(client->errormsg_buffer);
    if (client->status_bits) {
        vEventGroupDelete(client->status_bits);
    }
    free(client);
    client = NULL;
}

static esp_err_t stop_wait_task(esp_websocket_client_handle_t client)
{
    /* A running client cannot be stopped from the websocket task/event handler */
    TaskHandle_t running_task = xTaskGetCurrentTaskHandle();
    if (running_task == client->task_handle) {
        ESP_LOGE(TAG, "Client cannot be stopped from websocket task");
        return ESP_FAIL;
    }

    client->run = false;
    xEventGroupWaitBits(client->status_bits, STOPPED_BIT, false, true, portMAX_DELAY);
    client->state = WEBSOCKET_STATE_UNKNOW;
    return ESP_OK;
}

static esp_err_t set_websocket_transport_optional_settings(esp_websocket_client_handle_t client, const char *scheme)
{
    esp_transport_handle_t trans = esp_transport_list_get_transport(client->transport_list, scheme);
    if (trans) {
        const esp_transport_ws_config_t config = {
            .ws_path = client->config->path,
            .sub_protocol = client->config->subprotocol,
            .user_agent = client->config->user_agent,
            .headers = client->config->headers,
            .auth = client->config->auth,
            .propagate_control_frames = true
        };
        return esp_transport_ws_set_config(trans, &config);
    }
    return ESP_ERR_INVALID_ARG;
}

static esp_err_t esp_websocket_client_create_transport(esp_websocket_client_handle_t client)
{
    if (!client->config->scheme) {
        ESP_LOGE(TAG, "No scheme found");
        return ESP_FAIL;
    }

    if (client->transport_list) {
        esp_transport_list_destroy(client->transport_list);
        client->transport_list = NULL;
    }

    client->transport_list = esp_transport_list_init();
    ESP_WS_CLIENT_MEM_CHECK(TAG, client->transport_list, return ESP_ERR_NO_MEM);
    if (strcasecmp(client->config->scheme, WS_OVER_TCP_SCHEME) == 0) {
        esp_transport_handle_t tcp = esp_transport_tcp_init();
        ESP_WS_CLIENT_MEM_CHECK(TAG, tcp, return ESP_ERR_NO_MEM);

        esp_transport_set_default_port(tcp, WEBSOCKET_TCP_DEFAULT_PORT);
        esp_transport_list_add(client->transport_list, tcp, "_tcp"); // need to save to transport list, for cleanup
        if (client->keep_alive_cfg.keep_alive_enable) {
            esp_transport_tcp_set_keep_alive(tcp, &client->keep_alive_cfg);
        }
        if (client->if_name) {
            esp_transport_tcp_set_interface_name(tcp, client->if_name);
        }

        esp_transport_handle_t ws = esp_transport_ws_init(tcp);
        ESP_WS_CLIENT_MEM_CHECK(TAG, ws, return ESP_ERR_NO_MEM);

        esp_transport_set_default_port(ws, WEBSOCKET_TCP_DEFAULT_PORT);
        esp_transport_list_add(client->transport_list, ws, WS_OVER_TCP_SCHEME);
        ESP_WS_CLIENT_ERR_OK_CHECK(TAG, set_websocket_transport_optional_settings(client, WS_OVER_TCP_SCHEME), return ESP_FAIL;)
    } else if (strcasecmp(client->config->scheme, WS_OVER_TLS_SCHEME) == 0) {
        esp_transport_handle_t ssl = esp_transport_ssl_init();
        ESP_WS_CLIENT_MEM_CHECK(TAG, ssl, return ESP_ERR_NO_MEM);

        esp_transport_set_default_port(ssl, WEBSOCKET_SSL_DEFAULT_PORT);
        esp_transport_list_add(client->transport_list, ssl, "_ssl"); // need to save to transport list, for cleanup
        if (client->keep_alive_cfg.keep_alive_enable) {
            esp_transport_ssl_set_keep_alive(ssl, &client->keep_alive_cfg);
        }
        if (client->if_name) {
            esp_transport_ssl_set_interface_name(ssl, client->if_name);
        }

        if (client->config->use_global_ca_store == true) {
            esp_transport_ssl_enable_global_ca_store(ssl);
        } else if (client->config->cert) {
            if (!client->config->cert_len) {
                esp_transport_ssl_set_cert_data(ssl, client->config->cert, strlen(client->config->cert));
            } else {
                esp_transport_ssl_set_cert_data_der(ssl, client->config->cert, client->config->cert_len);
            }
        }
        if (client->config->client_cert) {
            if (!client->config->client_cert_len) {
                esp_transport_ssl_set_client_cert_data(ssl, client->config->client_cert, strlen(client->config->client_cert));
            } else {
                esp_transport_ssl_set_client_cert_data_der(ssl, client->config->client_cert, client->config->client_cert_len);
            }
        }
        if (client->config->client_key) {
            if (!client->config->client_key_len) {
                esp_transport_ssl_set_client_key_data(ssl, client->config->client_key, strlen(client->config->client_key));
            } else {
                esp_transport_ssl_set_client_key_data_der(ssl, client->config->client_key, client->config->client_key_len);
            }
#if CONFIG_ESP_TLS_USE_DS_PERIPHERAL
        } else if (client->config->client_ds_data) {
            esp_transport_ssl_set_ds_data(ssl, client->config->client_ds_data);
#endif
        }
        if (client->config->crt_bundle_attach) {
#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
            esp_transport_ssl_crt_bundle_attach(ssl, client->config->crt_bundle_attach);
#else //CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
            ESP_LOGE(TAG, "crt_bundle_attach configured but not enabled in menuconfig: Please enable MBEDTLS_CERTIFICATE_BUNDLE option");
#endif
        }
        if (client->config->skip_cert_common_name_check) {
            esp_transport_ssl_skip_common_name_check(ssl);
        }
        if (client->config->cert_common_name) {
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 1, 0)
            esp_transport_ssl_set_common_name(ssl, client->config->cert_common_name);
#else
            ESP_LOGE(TAG, "cert_common_name requires ESP-IDF 5.1.0 or later");
#endif
        }

        esp_transport_handle_t wss = esp_transport_ws_init(ssl);
        ESP_WS_CLIENT_MEM_CHECK(TAG, wss, return ESP_ERR_NO_MEM);

        esp_transport_set_default_port(wss, WEBSOCKET_SSL_DEFAULT_PORT);

        esp_transport_list_add(client->transport_list, wss, WS_OVER_TLS_SCHEME);
        ESP_WS_CLIENT_ERR_OK_CHECK(TAG, set_websocket_transport_optional_settings(client, WS_OVER_TLS_SCHEME), return ESP_FAIL;)
    } else {
        ESP_LOGE(TAG, "Not support this websocket scheme %s, only support %s and %s", client->config->scheme, WS_OVER_TCP_SCHEME, WS_OVER_TLS_SCHEME);
        return ESP_FAIL;
    }
    return ESP_OK;
}

static int esp_websocket_client_send_with_exact_opcode(esp_websocket_client_handle_t client, ws_transport_opcodes_t opcode, const uint8_t *data, int len, TickType_t timeout)
{
    int ret = -1;
    int need_write = len;
    int wlen = 0, widx = 0;
    bool contained_fin = opcode & WS_TRANSPORT_OPCODES_FIN;

    if (client == NULL || len < 0 || (data == NULL && len > 0)) {
        ESP_LOGE(TAG, "Invalid arguments");
        return -1;
    }

    if (!esp_websocket_client_is_connected(client)) {
        ESP_LOGE(TAG, "Websocket client is not connected");
        return -1;
    }

    if (client->transport == NULL) {
        ESP_LOGE(TAG, "Invalid transport");
        return -1;
    }

#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
    if (xSemaphoreTakeRecursive(client->tx_lock, timeout) != pdPASS) {
        ESP_LOGE(TAG, "Could not lock ws-client within %" PRIu32 " timeout", timeout);
        return -1;
    }
#else
    if (xSemaphoreTakeRecursive(client->lock, timeout) != pdPASS) {
        ESP_LOGE(TAG, "Could not lock ws-client within %" PRIu32 " timeout", timeout);
        return -1;
    }
#endif

    if (esp_websocket_new_buf(client, true) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to setup tx buffer");
        goto unlock_and_return;
    }

    while (widx < len || opcode) {  // allow for sending "current_opcode" only message with len==0
        if (need_write > client->buffer_size) {
            need_write = client->buffer_size;
            opcode = opcode & ~WS_TRANSPORT_OPCODES_FIN;
        } else if (contained_fin) {
            opcode = opcode | WS_TRANSPORT_OPCODES_FIN;
        }
        memcpy(client->tx_buffer, data + widx, need_write);
        // send with ws specific way and specific opcode
        wlen = esp_transport_ws_send_raw(client->transport, opcode, (char *)client->tx_buffer, need_write,
                                         (timeout == portMAX_DELAY) ? -1 : timeout * portTICK_PERIOD_MS);
        if (wlen < 0 || (wlen == 0 && need_write != 0)) {
            ret = wlen;
            esp_websocket_free_buf(client, true);
            esp_tls_error_handle_t error_handle = esp_transport_get_error_handle(client->transport);
            if (error_handle) {
                esp_websocket_client_error(client, "esp_transport_write() returned %d, transport_error=%s, tls_error_code=%i, tls_flags=%i, errno=%d",
                                           ret, esp_err_to_name(error_handle->last_error), error_handle->esp_tls_error_code,
                                           error_handle->esp_tls_flags, errno);
            } else {
                esp_websocket_client_error(client, "esp_transport_write() returned %d, errno=%d", ret, errno);
            }
            esp_websocket_client_abort_connection(client, WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT);
            goto unlock_and_return;
        }
        opcode = 0;
        widx += wlen;
        need_write = len - widx;
    }
    esp_websocket_free_buf(client, true);
    ret = widx;

unlock_and_return:
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
    xSemaphoreGiveRecursive(client->tx_lock);
#else
    xSemaphoreGiveRecursive(client->lock);
#endif
    return ret;
}

esp_websocket_client_handle_t esp_websocket_client_init(const esp_websocket_client_config_t *config)
{
    esp_websocket_client_handle_t client = calloc(1, sizeof(struct esp_websocket_client));
    ESP_WS_CLIENT_MEM_CHECK(TAG, client, return NULL);

    esp_event_loop_args_t event_args = {
        .queue_size = WEBSOCKET_EVENT_QUEUE_SIZE,
        .task_name = NULL // no task will be created
    };

    if (esp_event_loop_create(&event_args, &client->event_handle) != ESP_OK) {
        ESP_LOGE(TAG, "Error create event handler for websocket client");
        free(client);
        return NULL;
    }

    if (config->keep_alive_enable == true) {
        client->keep_alive_cfg.keep_alive_enable = true;
        client->keep_alive_cfg.keep_alive_idle = (config->keep_alive_idle == 0) ? WEBSOCKET_KEEP_ALIVE_IDLE : config->keep_alive_idle;
        client->keep_alive_cfg.keep_alive_interval = (config->keep_alive_interval == 0) ? WEBSOCKET_KEEP_ALIVE_INTERVAL : config->keep_alive_interval;
        client->keep_alive_cfg.keep_alive_count = (config->keep_alive_count == 0) ? WEBSOCKET_KEEP_ALIVE_COUNT : config->keep_alive_count;
    }

    if (config->if_name) {
        client->if_name = calloc(1, sizeof(struct ifreq) + 1);
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->if_name, goto _websocket_init_fail);
        memcpy(client->if_name, config->if_name, sizeof(struct ifreq));
    }

    client->lock = xSemaphoreCreateRecursiveMutex();
    ESP_WS_CLIENT_MEM_CHECK(TAG, client->lock, goto _websocket_init_fail);

#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
    client->tx_lock = xSemaphoreCreateRecursiveMutex();
    ESP_WS_CLIENT_MEM_CHECK(TAG, client->tx_lock, goto _websocket_init_fail);
#endif

    client->config = calloc(1, sizeof(websocket_config_storage_t));
    ESP_WS_CLIENT_MEM_CHECK(TAG, client->config, goto _websocket_init_fail);

    if (config->transport == WEBSOCKET_TRANSPORT_OVER_TCP) {
        asprintf(&client->config->scheme, WS_OVER_TCP_SCHEME);
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->config->scheme, goto _websocket_init_fail);
    } else if (config->transport == WEBSOCKET_TRANSPORT_OVER_SSL) {
        asprintf(&client->config->scheme, WS_OVER_TLS_SCHEME);
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->config->scheme, goto _websocket_init_fail);
    }

    if (!config->disable_auto_reconnect && config->reconnect_timeout_ms <= 0) {
        client->wait_timeout_ms = WEBSOCKET_RECONNECT_TIMEOUT_MS;
        ESP_LOGW(TAG, "`reconnect_timeout_ms` is not set, or it is less than or equal to zero, using default time out %d (milliseconds)", WEBSOCKET_RECONNECT_TIMEOUT_MS);
    } else {
        client->wait_timeout_ms = config->reconnect_timeout_ms;
    }

    // configure ssl related parameters
    if (config->cert_common_name != NULL && config->skip_cert_common_name_check) {
        ESP_LOGE(TAG, "Both cert_common_name and skip_cert_common_name_check are set, only one of them can be set");
        goto _websocket_init_fail;
    }

    client->config->use_global_ca_store = config->use_global_ca_store;
    client->config->cert = config->cert_pem;
    client->config->cert_len = config->cert_len;
    client->config->client_cert = config->client_cert;
    client->config->client_cert_len = config->client_cert_len;
    client->config->client_key = config->client_key;
    client->config->client_key_len = config->client_key_len;
#if CONFIG_ESP_TLS_USE_DS_PERIPHERAL
    client->config->client_ds_data = config->client_ds_data;
#endif
    client->config->skip_cert_common_name_check = config->skip_cert_common_name_check;
    client->config->cert_common_name = config->cert_common_name;
    client->config->crt_bundle_attach = config->crt_bundle_attach;
    client->config->ext_transport = config->ext_transport;

    if (config->uri) {
        if (esp_websocket_client_set_uri(client, config->uri) != ESP_OK) {
            ESP_LOGE(TAG, "Invalid uri");
            goto _websocket_init_fail;
        }
    }

    if (esp_websocket_client_set_config(client, config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set the configuration");
        goto _websocket_init_fail;
    }

    if (client->config->scheme == NULL) {
        asprintf(&client->config->scheme, WS_OVER_TCP_SCHEME);
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->config->scheme, goto _websocket_init_fail);
    }

    client->keepalive_tick_ms = _tick_get_ms();
    client->reconnect_tick_ms = _tick_get_ms();
    client->ping_tick_ms = _tick_get_ms();
    client->wait_for_pong_resp = false;
    client->selected_for_destroying = false;

    int buffer_size = config->buffer_size;
    if (buffer_size <= 0) {
        buffer_size = WEBSOCKET_BUFFER_SIZE_BYTE;
    }
    client->errormsg_buffer = NULL;
    client->errormsg_size = 0;
#ifndef CONFIG_ESP_WS_CLIENT_ENABLE_DYNAMIC_BUFFER
    client->rx_buffer = malloc(buffer_size);
    ESP_WS_CLIENT_MEM_CHECK(TAG, client->rx_buffer, {
        goto _websocket_init_fail;
    });
    client->tx_buffer = malloc(buffer_size);
    ESP_WS_CLIENT_MEM_CHECK(TAG, client->tx_buffer, {
        goto _websocket_init_fail;
    });
#endif
    client->status_bits = xEventGroupCreate();
    ESP_WS_CLIENT_MEM_CHECK(TAG, client->status_bits, {
        goto _websocket_init_fail;
    });
    xEventGroupSetBits(client->status_bits, STOPPED_BIT);

    client->buffer_size = buffer_size;
    return client;

_websocket_init_fail:
    esp_websocket_client_destroy(client);
    return NULL;
}

esp_err_t esp_websocket_client_destroy(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (client->status_bits && (STOPPED_BIT & xEventGroupGetBits(client->status_bits)) == 0) {
        stop_wait_task(client);
    }

    destroy_and_free_resources(client);
    return ESP_OK;
}

esp_err_t esp_websocket_client_destroy_on_exit(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    client->selected_for_destroying = true;
    return ESP_OK;
}

esp_err_t esp_websocket_client_set_uri(esp_websocket_client_handle_t client, const char *uri)
{
    if (client == NULL || uri == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    struct http_parser_url puri;
    http_parser_url_init(&puri);
    int parser_status = http_parser_parse_url(uri, strlen(uri), 0, &puri);
    if (parser_status != 0) {
        ESP_LOGE(TAG, "Error parse uri = %s", uri);
        return ESP_FAIL;
    }
    if (puri.field_data[UF_SCHEMA].len) {
        free(client->config->scheme);
        asprintf(&client->config->scheme, "%.*s", puri.field_data[UF_SCHEMA].len, uri + puri.field_data[UF_SCHEMA].off);
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->config->scheme, return ESP_ERR_NO_MEM);
    }

    if (puri.field_data[UF_HOST].len) {
        free(client->config->host);
        asprintf(&client->config->host, "%.*s", puri.field_data[UF_HOST].len, uri + puri.field_data[UF_HOST].off);
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->config->host, return ESP_ERR_NO_MEM);
    }


    if (puri.field_data[UF_PATH].len || puri.field_data[UF_QUERY].len) {
        free(client->config->path);
        if (puri.field_data[UF_QUERY].len == 0) {
            asprintf(&client->config->path, "%.*s", puri.field_data[UF_PATH].len, uri + puri.field_data[UF_PATH].off);
        } else if (puri.field_data[UF_PATH].len == 0)  {
            asprintf(&client->config->path, "/?%.*s", puri.field_data[UF_QUERY].len, uri + puri.field_data[UF_QUERY].off);
        } else {
            asprintf(&client->config->path, "%.*s?%.*s", puri.field_data[UF_PATH].len, uri + puri.field_data[UF_PATH].off,
                     puri.field_data[UF_QUERY].len, uri + puri.field_data[UF_QUERY].off);
        }
        ESP_WS_CLIENT_MEM_CHECK(TAG, client->config->path, return ESP_ERR_NO_MEM);
    }
    if (puri.field_data[UF_PORT].off) {
        client->config->port = strtol((const char *)(uri + puri.field_data[UF_PORT].off), NULL, 10);
    }

    if (puri.field_data[UF_USERINFO].len) {
        char *user_info = NULL;
        asprintf(&user_info, "%.*s", puri.field_data[UF_USERINFO].len, uri + puri.field_data[UF_USERINFO].off);
        if (user_info) {
            char *pass = strchr(user_info, ':');
            if (pass) {
                pass[0] = 0; //terminal username
                pass ++;
                free(client->config->password);
                client->config->password = strdup(pass);
                ESP_WS_CLIENT_MEM_CHECK(TAG, client->config->password, return ESP_ERR_NO_MEM);
            }
            free(client->config->username);
            client->config->username = strdup(user_info);
            ESP_WS_CLIENT_MEM_CHECK(TAG, client->config->username, return ESP_ERR_NO_MEM);
            free(user_info);
        } else {
            return ESP_ERR_NO_MEM;
        }
    }
    return ESP_OK;
}

esp_err_t esp_websocket_client_set_headers(esp_websocket_client_handle_t client, const char *headers)
{
    if (client == NULL || client->state != WEBSOCKET_STATE_CONNECTED || headers == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    xSemaphoreTakeRecursive(client->lock, portMAX_DELAY);
    esp_err_t ret = esp_transport_ws_set_headers(client->transport, headers);
    xSemaphoreGiveRecursive(client->lock);

    return ret;
}

esp_err_t esp_websocket_client_append_header(esp_websocket_client_handle_t client, const char *key, const char *value)
{
    // Validate the input parameters
    if (client == NULL || key == NULL || value == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    websocket_config_storage_t *cfg = client->config;

    // Calculate the length for "key: value\r\n"
    size_t len = strlen(key) + strlen(value) + 5; // 5 accounts for ": \r\n" and null-terminator

    // If no previous headers exist
    if (cfg->headers == NULL) {
        cfg->headers = (char *)malloc(len);
        if (cfg->headers == NULL) {
            ESP_LOGE(TAG, "Failed to allocate...");
            return ESP_ERR_NO_MEM;
        }
        snprintf(cfg->headers, len, "%s: %s\r\n", key, value);
        return ESP_OK;
    }

    // Extend the current headers to accommodate the new key-value pair
    size_t current_len = strlen(cfg->headers);
    size_t new_len = current_len + len;

    // Allocate memory for new headers
    char *new_headers = (char *)malloc(new_len);
    if (new_headers == NULL) {
        ESP_LOGE(TAG, "Failed to allocate...");
        return ESP_ERR_NO_MEM;
    }

    // Copy old headers and append the new header
    strcpy(new_headers, cfg->headers);
    snprintf(new_headers + current_len, len, "%s: %s\r\n", key, value);

    // Free old headers and assign the new header pointer to cfg->headers
    free(cfg->headers);
    cfg->headers = new_headers;

    return ESP_OK;
}

static esp_err_t esp_websocket_client_recv(esp_websocket_client_handle_t client)
{
    int rlen;
    client->payload_offset = 0;
    if (esp_websocket_new_buf(client, false) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to setup rx buffer");
        return ESP_FAIL;
    }
    do {
        rlen = esp_transport_read(client->transport, client->rx_buffer, client->buffer_size, client->config->network_timeout_ms);
        if (rlen < 0) {
            esp_websocket_free_buf(client, false);
            esp_tls_error_handle_t error_handle = esp_transport_get_error_handle(client->transport);
            if (error_handle) {
                esp_websocket_client_error(client, "esp_transport_read() failed with %d, transport_error=%s, tls_error_code=%i, tls_flags=%i, errno=%d",
                                           rlen, esp_err_to_name(error_handle->last_error), error_handle->esp_tls_error_code,
                                           error_handle->esp_tls_flags, errno);
            } else {
                esp_websocket_client_error(client, "esp_transport_read() failed with %d, errno=%d", rlen, errno);
            }
            return ESP_FAIL;
        }
        client->payload_len = esp_transport_ws_get_read_payload_len(client->transport);
        client->last_fin = esp_transport_ws_get_fin_flag(client->transport);
        client->last_opcode = esp_transport_ws_get_read_opcode(client->transport);

        if (rlen == 0 && client->last_opcode == WS_TRANSPORT_OPCODES_NONE) {
            ESP_LOGV(TAG, "esp_transport_read timeouts");
            esp_websocket_free_buf(client, false);
            return ESP_OK;
        }

        esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_DATA, client->rx_buffer, rlen);

        client->payload_offset += rlen;
    } while (client->payload_offset < client->payload_len);

    // if a PING message received -> send out the PONG, this will not work for PING messages with payload longer than buffer len
    if (client->last_opcode == WS_TRANSPORT_OPCODES_PING) {
        const char *data = (client->payload_len == 0) ? NULL : client->rx_buffer;
        ESP_LOGD(TAG, "Sending PONG with payload len=%d", client->payload_len);
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
        if (xSemaphoreTakeRecursive(client->tx_lock, WEBSOCKET_TX_LOCK_TIMEOUT_MS) != pdPASS) {
            ESP_LOGE(TAG, "Could not lock ws-client within %d timeout", WEBSOCKET_TX_LOCK_TIMEOUT_MS);
            return ESP_FAIL;
        }
#endif
        esp_transport_ws_send_raw(client->transport, WS_TRANSPORT_OPCODES_PONG | WS_TRANSPORT_OPCODES_FIN, data, client->payload_len,
                                  client->config->network_timeout_ms);
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
        xSemaphoreGiveRecursive(client->tx_lock);
#endif
    } else if (client->last_opcode == WS_TRANSPORT_OPCODES_PONG) {
        client->wait_for_pong_resp = false;
    } else if (client->last_opcode == WS_TRANSPORT_OPCODES_CLOSE) {
        ESP_LOGD(TAG, "Received close frame");
        client->state = WEBSOCKET_STATE_CLOSING;
    }
    esp_websocket_free_buf(client, false);
    return ESP_OK;
}

static int esp_websocket_client_send_close(esp_websocket_client_handle_t client, int code, const char *additional_data, int total_len, TickType_t timeout);

static void esp_websocket_client_task(void *pv)
{
    const int lock_timeout = portMAX_DELAY;
    esp_websocket_client_handle_t client = (esp_websocket_client_handle_t) pv;
    client->run = true;

    //get transport by scheme
    if (client->transport == NULL && client->config->ext_transport == NULL) {
        client->transport = esp_transport_list_get_transport(client->transport_list, client->config->scheme);
    }

    if (client->transport == NULL) {
        ESP_LOGE(TAG, "There are no transports valid, stop websocket client");
        client->run = false;
    }
    //default port
    if (client->config->port == 0) {
        client->config->port = esp_transport_get_default_port(client->transport);
    }

    client->state = WEBSOCKET_STATE_INIT;
    xEventGroupClearBits(client->status_bits, STOPPED_BIT | CLOSE_FRAME_SENT_BIT);
    esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_BEGIN, NULL, 0);
    int read_select = 0;
    while (client->run) {
        if (xSemaphoreTakeRecursive(client->lock, lock_timeout) != pdPASS) {
            ESP_LOGE(TAG, "Failed to lock ws-client tasks, exiting the task...");
            break;
        }
        switch ((int)client->state) {
        case WEBSOCKET_STATE_INIT:
            if (client->transport == NULL) {
                ESP_LOGE(TAG, "There are no transport");
                client->run = false;
                break;
            }
            esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_BEFORE_CONNECT, NULL, 0);
            int result = esp_transport_connect(client->transport,
                                               client->config->host,
                                               client->config->port,
                                               client->config->network_timeout_ms);
            if (result < 0) {
                esp_tls_error_handle_t error_handle = esp_transport_get_error_handle(client->transport);
                client->error_handle.esp_ws_handshake_status_code  = esp_transport_ws_get_upgrade_request_status(client->transport);
                if (error_handle) {
                    esp_websocket_client_error(client, "esp_transport_connect() failed with %d, "
                                               "transport_error=%s, tls_error_code=%i, tls_flags=%i, esp_ws_handshake_status_code=%d, errno=%d",
                                               result, esp_err_to_name(error_handle->last_error), error_handle->esp_tls_error_code,
                                               error_handle->esp_tls_flags, client->error_handle.esp_ws_handshake_status_code, errno);
                } else {
                    esp_websocket_client_error(client, "esp_transport_connect() failed with %d, esp_ws_handshake_status_code=%d, errno=%d",
                                               result, client->error_handle.esp_ws_handshake_status_code, errno);
                }
                esp_websocket_client_abort_connection(client, WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT);
                break;
            }
            ESP_LOGD(TAG, "Transport connected to %s://%s:%d", client->config->scheme, client->config->host, client->config->port);

            client->state = WEBSOCKET_STATE_CONNECTED;
            client->wait_for_pong_resp = false;
            client->error_handle.error_type = WEBSOCKET_ERROR_TYPE_NONE;
            esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_CONNECTED, NULL, 0);
            break;
        case WEBSOCKET_STATE_CONNECTED:
            if ((CLOSE_FRAME_SENT_BIT & xEventGroupGetBits(client->status_bits)) == 0) { // only send and check for PING
                // if closing hasn't been initiated
                if (_tick_get_ms() - client->ping_tick_ms > client->config->ping_interval_sec * 1000) {
                    client->ping_tick_ms = _tick_get_ms();
                    ESP_LOGD(TAG, "Sending PING...");
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
                    if (xSemaphoreTakeRecursive(client->tx_lock, WEBSOCKET_TX_LOCK_TIMEOUT_MS) != pdPASS) {
                        ESP_LOGE(TAG, "Could not lock ws-client within %d timeout", WEBSOCKET_TX_LOCK_TIMEOUT_MS);
                        break;
                    }
#endif
                    esp_transport_ws_send_raw(client->transport, WS_TRANSPORT_OPCODES_PING | WS_TRANSPORT_OPCODES_FIN, NULL, 0, client->config->network_timeout_ms);
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
                    xSemaphoreGiveRecursive(client->tx_lock);
#endif
                    if (!client->wait_for_pong_resp && client->config->pingpong_timeout_sec) {
                        client->pingpong_tick_ms = _tick_get_ms();
                        client->wait_for_pong_resp = true;
                    }
                }

                if (_tick_get_ms() - client->pingpong_tick_ms > client->config->pingpong_timeout_sec * 1000) {
                    if (client->wait_for_pong_resp) {
                        esp_websocket_client_error(client, "Error, no PONG received for more than %d seconds after PING", client->config->pingpong_timeout_sec);
                        esp_websocket_client_abort_connection(client, WEBSOCKET_ERROR_TYPE_PONG_TIMEOUT);
                        break;
                    }
                }
            }


            if (read_select == 0) {
                ESP_LOGV(TAG, "Read poll timeout: skipping esp_transport_read()...");
                break;
            }
            client->ping_tick_ms = _tick_get_ms();
            break;
        case WEBSOCKET_STATE_WAIT_TIMEOUT:

            if (_tick_get_ms() - client->reconnect_tick_ms > client->wait_timeout_ms) {
                client->state = WEBSOCKET_STATE_INIT;
                client->reconnect_tick_ms = _tick_get_ms();
                ESP_LOGD(TAG, "Reconnecting...");
            }
            break;
        case WEBSOCKET_STATE_CLOSING:
            // if closing not initiated by the client echo the close message back
            if ((CLOSE_FRAME_SENT_BIT & xEventGroupGetBits(client->status_bits)) == 0) {
                ESP_LOGD(TAG, "Closing initiated by the server, sending close frame");
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
                if (xSemaphoreTakeRecursive(client->tx_lock, WEBSOCKET_TX_LOCK_TIMEOUT_MS) != pdPASS) {
                    ESP_LOGE(TAG, "Could not lock ws-client within %d timeout", WEBSOCKET_TX_LOCK_TIMEOUT_MS);
                    break;
                }
#endif
                esp_transport_ws_send_raw(client->transport, WS_TRANSPORT_OPCODES_CLOSE | WS_TRANSPORT_OPCODES_FIN, NULL, 0, client->config->network_timeout_ms);
#ifdef CONFIG_ESP_WS_CLIENT_SEPARATE_TX_LOCK
                xSemaphoreGiveRecursive(client->tx_lock);
#endif
                xEventGroupSetBits(client->status_bits, CLOSE_FRAME_SENT_BIT);
            }
            break;
        default:
            ESP_LOGD(TAG, "Client run iteration in a default state: %d", client->state);
            break;
        }
        xSemaphoreGiveRecursive(client->lock);
        if (WEBSOCKET_STATE_CONNECTED == client->state) {
            read_select = esp_transport_poll_read(client->transport, 1000); //Poll every 1000ms
            if (read_select < 0) {
                esp_tls_error_handle_t error_handle = esp_transport_get_error_handle(client->transport);
                if (error_handle) {
                    esp_websocket_client_error(client, "esp_transport_poll_read() returned %d, transport_error=%s, tls_error_code=%i, tls_flags=%i, errno=%d",
                                               read_select, esp_err_to_name(error_handle->last_error), error_handle->esp_tls_error_code,
                                               error_handle->esp_tls_flags, errno);
                } else {
                    esp_websocket_client_error(client, "esp_transport_poll_read() returned %d, errno=%d", read_select, errno);
                }
                xSemaphoreTakeRecursive(client->lock, lock_timeout);
                esp_websocket_client_abort_connection(client, WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT);
                xSemaphoreGiveRecursive(client->lock);
            } else if (read_select > 0) {
                if (esp_websocket_client_recv(client) == ESP_FAIL) {
                    ESP_LOGE(TAG, "Error receive data");
                    xSemaphoreTakeRecursive(client->lock, lock_timeout);
                    esp_websocket_client_abort_connection(client, WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT);
                    xSemaphoreGiveRecursive(client->lock);
                }
            }
        } else if (WEBSOCKET_STATE_WAIT_TIMEOUT == client->state) {
            // waiting for reconnecting...
            vTaskDelay(client->wait_timeout_ms / 2 / portTICK_PERIOD_MS);
        } else if (WEBSOCKET_STATE_CLOSING == client->state &&
                   (CLOSE_FRAME_SENT_BIT & xEventGroupGetBits(client->status_bits))) {
            ESP_LOGD(TAG, " Waiting for TCP connection to be closed by the server");
            int ret = esp_transport_ws_poll_connection_closed(client->transport, 1000);
            if (ret == 0) {
                ESP_LOGW(TAG, "Did not get TCP close within expected delay");

            } else if (ret < 0) {
                ESP_LOGW(TAG, "Connection terminated while waiting for clean TCP close");
            }
            if (client->config->close_reconnect && xSemaphoreTakeRecursive(client->lock, lock_timeout) == pdPASS) {
                client->state = WEBSOCKET_STATE_WAIT_TIMEOUT;
                client->error_handle.error_type = WEBSOCKET_ERROR_TYPE_SERVER_CLOSE;
                esp_transport_close(client->transport);
                esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_CLOSED, NULL, 0);
                client->reconnect_tick_ms = _tick_get_ms();
                ESP_LOGI(TAG, "Reconnect after %d ms", client->wait_timeout_ms);
                xEventGroupClearBits(client->status_bits, STOPPED_BIT | CLOSE_FRAME_SENT_BIT);
                xSemaphoreGiveRecursive(client->lock);
            } else {
                client->run = false;
                client->state = WEBSOCKET_STATE_UNKNOW;
                esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_CLOSED, NULL, 0);
                break;
            }
        }
    }

    esp_websocket_client_dispatch_event(client, WEBSOCKET_EVENT_FINISH, NULL, 0);
    esp_transport_close(client->transport);
    xEventGroupSetBits(client->status_bits, STOPPED_BIT);
    client->state = WEBSOCKET_STATE_UNKNOW;
    if (client->selected_for_destroying == true) {
        destroy_and_free_resources(client);
    }
    vTaskDelete(NULL);
}

esp_err_t esp_websocket_client_start(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (client->state >= WEBSOCKET_STATE_INIT) {
        ESP_LOGE(TAG, "The client has started");
        return ESP_FAIL;
    }

    client->transport = client->config->ext_transport;
    if (!client->transport) {
        if (esp_websocket_client_create_transport(client) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to create websocket transport");
            return ESP_FAIL;
        }
    }

    if (xTaskCreate(esp_websocket_client_task, client->config->task_name ? client->config->task_name : "websocket_task",
                    client->config->task_stack, client, client->config->task_prio, &client->task_handle) != pdTRUE) {
        ESP_LOGE(TAG, "Error create websocket task");
        return ESP_FAIL;
    }
    xEventGroupClearBits(client->status_bits, STOPPED_BIT | CLOSE_FRAME_SENT_BIT);
    ESP_LOGI(TAG, "Started");
    return ESP_OK;
}

esp_err_t esp_websocket_client_stop(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (xEventGroupGetBits(client->status_bits) & STOPPED_BIT) {
        ESP_LOGW(TAG, "Client was not started");
        return ESP_FAIL;
    }

    return stop_wait_task(client);
}

static int esp_websocket_client_send_close(esp_websocket_client_handle_t client, int code, const char *additional_data, int total_len, TickType_t timeout)
{
    uint8_t *close_status_data = NULL;
    // RFC6455#section-5.5.1: The Close frame MAY contain a body (indicated by total_len >= 2)
    if (total_len >= 2) {
        close_status_data = calloc(1, total_len);
        ESP_WS_CLIENT_MEM_CHECK(TAG, close_status_data, return -1);
        // RFC6455#section-5.5.1: The first two bytes of the body MUST be a 2-byte representing a status
        uint16_t *code_network_order = (uint16_t *) close_status_data;
        *code_network_order = htons(code);
        memcpy(close_status_data + 2, additional_data, total_len - 2);
    }
    int ret = esp_websocket_client_send_with_opcode(client, WS_TRANSPORT_OPCODES_CLOSE, close_status_data, total_len, timeout);
    free(close_status_data);
    return ret;
}


static esp_err_t esp_websocket_client_close_with_optional_body(esp_websocket_client_handle_t client, bool send_body, int code, const char *data, int len, TickType_t timeout)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (!client->run) {
        ESP_LOGW(TAG, "Client was not started");
        return ESP_FAIL;
    }

    /* A running client cannot be stopped from the websocket task/event handler */
    TaskHandle_t running_task = xTaskGetCurrentTaskHandle();
    if (running_task == client->task_handle) {
        ESP_LOGE(TAG, "Client cannot be stopped from websocket task");
        return ESP_FAIL;
    }

    if (send_body) {
        esp_websocket_client_send_close(client, code, data, len + 2, portMAX_DELAY); // len + 2 -> always sending the code
    } else {
        esp_websocket_client_send_close(client, 0, NULL, 0, portMAX_DELAY); // only opcode frame
    }

    // Set closing bit to prevent from sending PING frames while connected
    xEventGroupSetBits(client->status_bits, CLOSE_FRAME_SENT_BIT);

    if (STOPPED_BIT & xEventGroupWaitBits(client->status_bits, STOPPED_BIT, false, true, timeout)) {
        return ESP_OK;
    }

    // If could not close gracefully within timeout, stop the client and disconnect
    client->run = false;
    xEventGroupWaitBits(client->status_bits, STOPPED_BIT, false, true, portMAX_DELAY);
    client->state = WEBSOCKET_STATE_UNKNOW;
    return ESP_OK;
}

esp_err_t esp_websocket_client_close_with_code(esp_websocket_client_handle_t client, int code, const char *data, int len, TickType_t timeout)
{
    return esp_websocket_client_close_with_optional_body(client, true, code, data, len, timeout);
}

esp_err_t esp_websocket_client_close(esp_websocket_client_handle_t client, TickType_t timeout)
{
    return esp_websocket_client_close_with_optional_body(client, false, 0, NULL, 0, timeout);
}

int esp_websocket_client_send_text(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout)
{
    return esp_websocket_client_send_with_opcode(client, WS_TRANSPORT_OPCODES_TEXT, (const uint8_t *)data, len, timeout);
}

int esp_websocket_client_send_text_partial(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout)
{
    return esp_websocket_client_send_with_exact_opcode(client, WS_TRANSPORT_OPCODES_TEXT, (const uint8_t *)data, len, timeout);
}

int esp_websocket_client_send_cont_msg(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout)
{
    return esp_websocket_client_send_with_exact_opcode(client, WS_TRANSPORT_OPCODES_CONT, (const uint8_t *)data, len, timeout);
}

int esp_websocket_client_send_bin(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout)
{
    return esp_websocket_client_send_with_opcode(client, WS_TRANSPORT_OPCODES_BINARY, (const uint8_t *)data, len, timeout);
}

int esp_websocket_client_send_bin_partial(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout)
{
    return esp_websocket_client_send_with_exact_opcode(client, WS_TRANSPORT_OPCODES_BINARY, (const uint8_t *)data, len, timeout);
}

int esp_websocket_client_send_fin(esp_websocket_client_handle_t client, TickType_t timeout)
{
    return esp_websocket_client_send_with_exact_opcode(client, WS_TRANSPORT_OPCODES_FIN, NULL, 0, timeout);
}

int esp_websocket_client_send_with_opcode(esp_websocket_client_handle_t client, ws_transport_opcodes_t opcode, const uint8_t *data, int len, TickType_t timeout)
{
    return esp_websocket_client_send_with_exact_opcode(client, opcode | WS_TRANSPORT_OPCODES_FIN, data, len, timeout);
}

bool esp_websocket_client_is_connected(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return false;
    }
    return client->state == WEBSOCKET_STATE_CONNECTED;
}

size_t esp_websocket_client_get_ping_interval_sec(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        ESP_LOGW(TAG, "Client was not initialized");
        return 0;
    }

    if (client->config == NULL) {
        ESP_LOGW(TAG, "No config available to change the ping interval");
        return 0;
    }

    return client->config->ping_interval_sec;
}

esp_err_t esp_websocket_client_set_ping_interval_sec(esp_websocket_client_handle_t client, size_t ping_interval_sec)
{
    if (client == NULL) {
        ESP_LOGW(TAG, "Client was not initialized");
        return ESP_ERR_INVALID_ARG;
    }

    if (client->config == NULL) {
        ESP_LOGW(TAG, "No config available to change the ping interval");
        return ESP_ERR_INVALID_STATE;
    }

    client->config->ping_interval_sec = ping_interval_sec == 0 ? WEBSOCKET_PING_INTERVAL_SEC : ping_interval_sec;

    return ESP_OK;
}

int esp_websocket_client_get_reconnect_timeout(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        ESP_LOGW(TAG, "Client was not initialized");
        return -1;
    }

    if (!client->config->auto_reconnect) {
        ESP_LOGW(TAG, "Automatic reconnect is disabled");
        return -1;
    }

    return client->wait_timeout_ms;
}

esp_err_t esp_websocket_client_set_reconnect_timeout(esp_websocket_client_handle_t client, int reconnect_timeout_ms)
{
    if (client == NULL) {
        ESP_LOGW(TAG, "Client was not initialized");
        return ESP_ERR_INVALID_ARG;
    }

    if (reconnect_timeout_ms <= 0) {
        ESP_LOGW(TAG, "Invalid reconnect timeout");
        return ESP_ERR_INVALID_ARG;
    }

    if (!client->config->auto_reconnect) {
        ESP_LOGW(TAG, "Automatic reconnect is disabled");
        return ESP_ERR_INVALID_STATE;
    }

    client->wait_timeout_ms = reconnect_timeout_ms;

    return ESP_OK;
}

esp_err_t esp_websocket_register_events(esp_websocket_client_handle_t client,
                                        esp_websocket_event_id_t event,
                                        esp_event_handler_t event_handler,
                                        void *event_handler_arg)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return esp_event_handler_register_with(client->event_handle, WEBSOCKET_EVENTS, event, event_handler, event_handler_arg);
}

esp_err_t esp_websocket_unregister_events(esp_websocket_client_handle_t client,
                                          esp_websocket_event_id_t event,
                                          esp_event_handler_t event_handler)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return esp_event_handler_unregister_with(client->event_handle, WEBSOCKET_EVENTS, event, event_handler);
}
