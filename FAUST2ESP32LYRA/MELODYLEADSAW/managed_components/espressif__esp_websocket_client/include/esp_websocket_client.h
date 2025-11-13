/*
 * SPDX-FileCopyrightText: 2015-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ESP_WEBSOCKET_CLIENT_H_
#define _ESP_WEBSOCKET_CLIENT_H_


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "esp_event.h"
#include <sys/socket.h>
#include "esp_transport_ws.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_websocket_client *esp_websocket_client_handle_t;

ESP_EVENT_DECLARE_BASE(WEBSOCKET_EVENTS);         // declaration of the task events family

/**
 * @brief Websocket Client events id
 */
typedef enum {
    WEBSOCKET_EVENT_ANY = -1,
    WEBSOCKET_EVENT_ERROR = 0,      /*!< This event occurs when there are any errors during execution */
    WEBSOCKET_EVENT_CONNECTED,      /*!< Once the Websocket has been connected to the server, no data exchange has been performed */
    WEBSOCKET_EVENT_DISCONNECTED,   /*!< The connection has been disconnected */
    WEBSOCKET_EVENT_DATA,           /*!< When receiving data from the server, possibly multiple portions of the packet */
    WEBSOCKET_EVENT_CLOSED,         /*!< The connection has been closed cleanly */
    WEBSOCKET_EVENT_BEFORE_CONNECT, /*!< The event occurs before connecting */
    WEBSOCKET_EVENT_BEGIN,          /*!< The event occurs once after thread creation, before event loop */
    WEBSOCKET_EVENT_FINISH,         /*!< The event occurs once after event loop, before thread destruction */
    WEBSOCKET_EVENT_MAX
} esp_websocket_event_id_t;

/**
 * @brief Websocket connection error codes propagated via ERROR event
 */
typedef enum {
    WEBSOCKET_ERROR_TYPE_NONE = 0,
    WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT,
    WEBSOCKET_ERROR_TYPE_PONG_TIMEOUT,
    WEBSOCKET_ERROR_TYPE_HANDSHAKE,
    WEBSOCKET_ERROR_TYPE_SERVER_CLOSE
} esp_websocket_error_type_t;

/**
 * @brief Websocket error code structure to be passed as a contextual information into ERROR event
 */
typedef struct {
    /* compatible portion of the struct corresponding to struct esp_tls_last_error */
    esp_err_t esp_tls_last_esp_err;             /*!< last esp_err code reported from esp-tls component */
    int       esp_tls_stack_err;                /*!< tls specific error code reported from underlying tls stack */
    int       esp_tls_cert_verify_flags;        /*!< tls flags reported from underlying tls stack during certificate verification */
    /* esp-websocket specific structure extension */
    esp_websocket_error_type_t error_type;
    int esp_ws_handshake_status_code;           /*!< http status code of the websocket upgrade handshake */
    /* tcp_transport extension */
    int       esp_transport_sock_errno;         /*!< errno from the underlying socket */
} esp_websocket_error_codes_t;

/**
 * @brief Websocket event data
 */
typedef struct {
    const char *data_ptr;                   /*!< Data pointer */
    int data_len;                           /*!< Data length */
    bool fin;                               /*!< Fin flag */
    uint8_t op_code;                        /*!< Received opcode */
    esp_websocket_client_handle_t client;   /*!< esp_websocket_client_handle_t context */
    void *user_context;                     /*!< user_data context, from esp_websocket_client_config_t user_data */
    int payload_len;                        /*!< Total payload length, payloads exceeding buffer will be posted through multiple events */
    int payload_offset;                     /*!< Actual offset for the data associated with this event */
    esp_websocket_error_codes_t error_handle; /*!< esp-websocket error handle including esp-tls errors as well as internal websocket errors */
} esp_websocket_event_data_t;

/**
 * @brief Websocket Client transport
 */
typedef enum {
    WEBSOCKET_TRANSPORT_UNKNOWN = 0x0,  /*!< Transport unknown */
    WEBSOCKET_TRANSPORT_OVER_TCP,       /*!< Transport over tcp */
    WEBSOCKET_TRANSPORT_OVER_SSL,       /*!< Transport over ssl */
} esp_websocket_transport_t;

/**
 * @brief Websocket client setup configuration
 */
typedef struct {
    const char                  *uri;                       /*!< Websocket URI, the information on the URI can be overrides the other fields below, if any */
    const char                  *host;                      /*!< Domain or IP as string */
    int                         port;                       /*!< Port to connect, default depend on esp_websocket_transport_t (80 or 443) */
    const char                  *username;                  /*!< Using for Http authentication, only support basic auth now */
    const char                  *password;                  /*!< Using for Http authentication */
    const char                  *path;                      /*!< HTTP Path, if not set, default is `/` */
    bool                        disable_auto_reconnect;     /*!< Disable the automatic reconnect function when disconnected */
    bool                        enable_close_reconnect;     /*!< Enable reconnect after server close */
    void                        *user_context;              /*!< HTTP user data context */
    int                         task_prio;                  /*!< Websocket task priority */
    const char                 *task_name;                  /*!< Websocket task name */
    int                         task_stack;                 /*!< Websocket task stack */
    int                         buffer_size;                /*!< Websocket buffer size */
    const char                  *cert_pem;                  /*!< Pointer to certificate data in PEM or DER format for server verify (with SSL), default is NULL, not required to verify the server. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in cert_len. */
    size_t                      cert_len;                   /*!< Length of the buffer pointed to by cert_pem. May be 0 for null-terminated pem */
    const char                  *client_cert;               /*!< Pointer to certificate data in PEM or DER format for SSL mutual authentication, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_key` or `client_ds_data` (if supported) has to be provided. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in client_cert_len. */
    size_t                      client_cert_len;            /*!< Length of the buffer pointed to by client_cert. May be 0 for null-terminated pem */
    const char                  *client_key;                /*!< Pointer to private key data in PEM or DER format for SSL mutual authentication, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_cert` has to be provided and `client_ds_data` (if supported) gets ignored. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in client_key_len */
    size_t                      client_key_len;             /*!< Length of the buffer pointed to by client_key_pem. May be 0 for null-terminated pem */
#if CONFIG_ESP_TLS_USE_DS_PERIPHERAL
    void                        *client_ds_data;            /*!< Pointer to the encrypted private key data for SSL mutual authentication using the DS peripheral, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_cert` has to be provided. It is ignored if `client_key` is provided */
#endif
    esp_websocket_transport_t   transport;                  /*!< Websocket transport type, see `esp_websocket_transport_t */
    const char                  *subprotocol;               /*!< Websocket subprotocol */
    const char                  *user_agent;                /*!< Websocket user-agent */
    const char                  *headers;                   /*!< Websocket additional headers */
    int                         pingpong_timeout_sec;       /*!< Period before connection is aborted due to no PONGs received */
    bool                        disable_pingpong_discon;    /*!< Disable auto-disconnect due to no PONG received within pingpong_timeout_sec */
    bool                        use_global_ca_store;        /*!< Use a global ca_store for all the connections in which this bool is set. */
    esp_err_t (*crt_bundle_attach)(void *conf);             /*!< Function pointer to esp_crt_bundle_attach. Enables the use of certification bundle for server verification, MBEDTLS_CERTIFICATE_BUNDLE must be enabled in menuconfig. Include esp_crt_bundle.h, and use `esp_crt_bundle_attach` here to include bundled CA certificates. */
    const char                  *cert_common_name;          /*!< Expected common name of the server certificate */
    bool                        skip_cert_common_name_check;/*!< Skip any validation of server certificate CN field */
    bool                        keep_alive_enable;          /*!< Enable keep-alive timeout */
    int                         keep_alive_idle;            /*!< Keep-alive idle time. Default is 5 (second) */
    int                         keep_alive_interval;        /*!< Keep-alive interval time. Default is 5 (second) */
    int                         keep_alive_count;           /*!< Keep-alive packet retry send count. Default is 3 counts */
    int                         reconnect_timeout_ms;       /*!< Reconnect after this value in miliseconds if disable_auto_reconnect is not enabled (defaults to 10s) */
    int                         network_timeout_ms;         /*!< Abort network operation if it is not completed after this value, in milliseconds (defaults to 10s) */
    size_t                      ping_interval_sec;          /*!< Websocket ping interval, defaults to 10 seconds if not set */
    struct ifreq                *if_name;                   /*!< The name of interface for data to go through. Use the default interface without setting */
    esp_transport_handle_t      ext_transport;              /*!< External WebSocket tcp_transport handle to the client; or if null, the client will create its own transport handle. */
} esp_websocket_client_config_t;

/**
 * @brief      Start a Websocket session
 *             This function must be the first function to call,
 *             and it returns a esp_websocket_client_handle_t that you must use as input to other functions in the interface.
 *             This call MUST have a corresponding call to esp_websocket_client_destroy when the operation is complete.
 *
 * @param[in]  config  The configuration
 *
 * @return
 *     - `esp_websocket_client_handle_t`
 *     - NULL if any errors
 */
esp_websocket_client_handle_t esp_websocket_client_init(const esp_websocket_client_config_t *config);

/**
 * @brief      Set URL for client, when performing this behavior, the options in the URL will replace the old ones
 *             Must stop the WebSocket client before set URI if the client has been connected
 *
 * @param[in]  client  The client
 * @param[in]  uri     The uri
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_set_uri(esp_websocket_client_handle_t client, const char *uri);

/**
 * @brief      Set additional websocket headers for the client, when performing this behavior, the headers will replace the old ones
 * @pre        Must stop the WebSocket client before set headers if the client has been connected
 *
 *    - This API should be used after the WebSocket client connection has succeeded (i.e., once the transport layer is initialized).
 *    - If you wish to set or append headers before the WebSocket client connection is established(before handshake), consider the following options:
 *       1. Input headers directly into the config options, terminating each item with [CR][LF]. This approach will replace any previous headers.
 *          Example: websocket_cfg.headers = "Sec-WebSocket-Key: my_key\r\nPassword: my_pass\r\n";
 *       2. Use the `esp_websocket_client_append_header` API to append a single header to the current set.
 *
 * @param[in]  client  The WebSocket client handle
 * @param[in]  headers Additional header strings each terminated with [CR][LF]
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_set_headers(esp_websocket_client_handle_t client, const char *headers);

/**
 * @brief      Appends a new key-value pair to the headers of a WebSocket client.
 * @pre        Ensure that this function is called before starting the WebSocket client.
 *
 * @param[in]  client  The WebSocket client handle
 * @param[in]  key     The header key to append
 * @param[in]  value   The associated value for the given key
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_append_header(esp_websocket_client_handle_t client, const char *key, const char *value);

/**
 * @brief      Open the WebSocket connection
 *
 * @param[in]  client  The client
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_start(esp_websocket_client_handle_t client);

/**
 * @brief      Stops the WebSocket connection without websocket closing handshake
 *
 * This API stops ws client and closes TCP connection directly without sending
 * close frames. It is a good practice to close the connection in a clean way
 * using esp_websocket_client_close().
 *
 *  Notes:
 *  - Cannot be called from the websocket event handler
 *
 * @param[in]  client  The client
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_stop(esp_websocket_client_handle_t client);

/**
 * @brief      Destroy the WebSocket connection and free all resources.
 *             This function must be the last function to call for an session.
 *             It is the opposite of the esp_websocket_client_init function and must be called with the same handle as input that a esp_websocket_client_init call returned.
 *             This might close all connections this handle has used.
 *
 *  Notes:
 *  - Cannot be called from the websocket event handler
 *
 * @param[in]  client  The client
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_destroy(esp_websocket_client_handle_t client);

/**
 * @brief      If this API called, WebSocket client will destroy and free all resources at the end of event loop.
 *
 *  Notes:
 *  - After event loop finished, client handle would be dangling and should never be used
 *
 * @param[in]  client      The client
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_destroy_on_exit(esp_websocket_client_handle_t client);

/**
 * @brief      Write binary data to the WebSocket connection (data send with WS OPCODE=02, i.e. binary)
 *
 * @param[in]  client  The client
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout in RTOS ticks
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int esp_websocket_client_send_bin(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      Write binary data to the WebSocket connection and sends it without setting the FIN flag(data send with WS OPCODE=02, i.e. binary)
 *
 *  Notes:
 *   - To send continuation frame, you should use 'esp_websocket_client_send_cont_msg(...)' API.
 *   - To mark the end of fragmented data, you should use the 'esp_websocket_client_send_fin(...)' API. This sends a FIN frame.
 *
 * @param[in]  client  The client
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout in RTOS ticks
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int esp_websocket_client_send_bin_partial(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      Write textual data to the WebSocket connection (data send with WS OPCODE=01, i.e. text)
 *
 * @param[in]  client  The client
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout in RTOS ticks
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int esp_websocket_client_send_text(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      Write textual data to the WebSocket connection and sends it without setting the FIN flag(data send with WS OPCODE=01, i.e. text)
 *
 *  Notes:
 *   - To send continuation frame, you should use 'esp_websocket_client_send_cont_mgs(...)' API.
 *   - To mark the end of fragmented data, you should use the 'esp_websocket_client_send_fin(...)' API. This sends a FIN frame.
 *
 * @param[in]  client  The client
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout in RTOS ticks
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int esp_websocket_client_send_text_partial(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      Write textual data to the WebSocket connection and sends it as continuation frame (OPCODE=0x0)
 *
 *  Notes:
 *   - Continuation frames have an opcode of 0x0 and do not explicitly signify whether they are continuing a text or a binary message.
 *   - You determine the type of message (text or binary) being continued by looking at the opcode of the initial frame in the sequence of fragmented frames.
 *   - To mark the end of fragmented data, you should use the 'esp_websocket_client_send_fin(...)' API. This sends a FIN frame.
 *
 * @param[in]  client  The client
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout in RTOS ticks
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int esp_websocket_client_send_cont_msg(esp_websocket_client_handle_t client, const char *data, int len, TickType_t timeout);

/**
 * @brief      Sends FIN frame
 *
 * @param[in]  client  The client
 * @param[in]  timeout Write data timeout in RTOS ticks
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int esp_websocket_client_send_fin(esp_websocket_client_handle_t client, TickType_t timeout);

/**
 * @brief      Write opcode data to the WebSocket connection
 *
 * @param[in]  client  The client
 * @param[in]  opcode  The opcode
 * @param[in]  data    The data
 * @param[in]  len     The length
 * @param[in]  timeout Write data timeout in RTOS ticks
 *
 *  Notes:
 *  - In order to send a zero payload, data and len should be set to NULL/0
 *  - This API sets the FIN bit on the last fragment of message
 *
 *
 * @return
 *     - Number of data was sent
 *     - (-1) if any errors
 */
int esp_websocket_client_send_with_opcode(esp_websocket_client_handle_t client, ws_transport_opcodes_t opcode, const uint8_t *data, int len, TickType_t timeout);

/**
 * @brief      Close the WebSocket connection in a clean way
 *
 * Sequence of clean close initiated by client:
 * * Client sends CLOSE frame
 * * Client waits until server echos the CLOSE frame
 * * Client waits until server closes the connection
 * * Client is stopped the same way as by the `esp_websocket_client_stop()`
 *
 *  Notes:
 *  - Cannot be called from the websocket event handler
 *
 * @param[in]  client  The client
 * @param[in]  timeout Timeout in RTOS ticks for waiting
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_close(esp_websocket_client_handle_t client, TickType_t timeout);

/**
 * @brief      Close the WebSocket connection in a clean way with custom code/data
 *             Closing sequence is the same as for esp_websocket_client_close()
 *
 *  Notes:
 *  - Cannot be called from the websocket event handler
 *
 * @param[in]  client  The client
 * @param[in]  code    Close status code as defined in RFC6455 section-7.4
 * @param[in]  data    Additional data to closing message
 * @param[in]  len     The length of the additional data
 * @param[in]  timeout Timeout in RTOS ticks for waiting
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_close_with_code(esp_websocket_client_handle_t client, int code, const char *data, int len, TickType_t timeout);

/**
 * @brief      Check the WebSocket client connection state
 *
 * @param[in]  client  The client handle
 *
 * @return
 *     - true
 *     - false
 */
bool esp_websocket_client_is_connected(esp_websocket_client_handle_t client);

/**
 * @brief      Get the ping interval sec for client.
 *
 * @param[in]  client             The client
 *
 * @return     The ping interval in sec
 */
size_t esp_websocket_client_get_ping_interval_sec(esp_websocket_client_handle_t client);

/**
 * @brief      Set new ping interval sec for client.
 *
 * @param[in]  client             The client
 * @param[in]  ping_interval_sec  The new interval
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_set_ping_interval_sec(esp_websocket_client_handle_t client, size_t ping_interval_sec);

/**
 * @brief      Get the next reconnect timeout for client. Returns -1 when client is not initialized or automatic reconnect is disabled.
 *
 * @param[in]  client             The client
 *
 * @return     Reconnect timeout in msec
 */
int esp_websocket_client_get_reconnect_timeout(esp_websocket_client_handle_t client);

/**
 * @brief      Set next reconnect timeout for client.
 *
 *  Notes:
 *  - Changing this value when reconnection delay is already active does not immediately affect the active delay and may have unexpected result.
 *  - Good place to change this value is when handling WEBSOCKET_EVENT_DISCONNECTED or WEBSOCKET_EVENT_ERROR events.
 *
 * @param[in]  client             The client
 * @param[in]  reconnect_timeout_ms  The new timeout
 *
 * @return     esp_err_t
 */
esp_err_t esp_websocket_client_set_reconnect_timeout(esp_websocket_client_handle_t client, int reconnect_timeout_ms);

/**
 * @brief Register the Websocket Events
 *
 * @param client            The client handle
 * @param event             The event id
 * @param event_handler     The callback function
 * @param event_handler_arg User context
 * @return esp_err_t
 */
esp_err_t esp_websocket_register_events(esp_websocket_client_handle_t client,
                                        esp_websocket_event_id_t event,
                                        esp_event_handler_t event_handler,
                                        void *event_handler_arg);

/**
 * @brief Unegister the Websocket Events
 *
 * @param client            The client handle
 * @param event             The event id
 * @param event_handler     The callback function
 * @return esp_err_t
 */
esp_err_t esp_websocket_unregister_events(esp_websocket_client_handle_t client,
                                          esp_websocket_event_id_t event,
                                          esp_event_handler_t event_handler);

#ifdef __cplusplus
}
#endif

#endif
