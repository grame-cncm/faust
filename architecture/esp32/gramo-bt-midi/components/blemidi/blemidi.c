/*
BLE MIDI driver based on a heavy-lifted version of https://github.com/midibox/esp32-idf-blemidi by Thorsten Klose (tk@midibox.org). The driver can act both as a server and as a client.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "blemidi.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_gattc_api.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"

////////////////////////////////////////////////////////////////////////////////
// GLOBAL ELEMENTS SECTION
////////////////////////////////////////////////////////////////////////////////

#define BLEMIDI_NUM_PORTS 1
#define BLEMIDI_OUTBUFFER_FLUSH_MS 15

#define BLEMIDI_TAG "BLEMIDI"
#define PROFILE_NUM                 1
#define PROFILE_APP_IDX             0
#define PROFILE_A_APP_ID 0
#define INVALID_HANDLE   0
#define REMOTE_SERVICE_UUID 0x00, 0xC7, 0xC4, 0x4E, 0xE3, 0x6C, 0x51, 0xA7, 0x33, 0x4B, 0xE8, 0xED, 0x5A, 0x0E, 0xB8, 0x03
#define REMOTE_CHAR_UUID 0xF3, 0x6B, 0x10, 0x9D, 0x66, 0xF2, 0xA9, 0xA1, 0x12, 0x41, 0x68, 0x38, 0xDB, 0xE5, 0x72, 0x77
#define ESP_APP_ID                  0x55
#define SVC_INST_ID                 0

/* The max length of characteristic value. When the GATT client performs a write or prepare write operation,
*  the data length must be less than GATTS_MIDI_CHAR_VAL_LEN_MAX. 
*/
#define GATTS_MIDI_CHAR_VAL_LEN_MAX 100
#define PREPARE_BUF_MAX_SIZE        2048
#define CHAR_DECLARATION_SIZE       (sizeof(uint8_t))

#define ADV_CONFIG_FLAG             (1 << 0)
#define SCAN_RSP_CONFIG_FLAG        (1 << 1)

const char* current_device_name = "Gramophone";
const char* remote_device_name = "BBC micro:bit [zegut]";
static bool connect    = false;
static bool get_server = false;
static esp_gattc_char_elem_t *char_elem_result   = NULL;
static esp_gattc_descr_elem_t *descr_elem_result = NULL;

static uint8_t adv_config_done       = 0;

/* Attributes State Machine */
enum
{
    IDX_SVC,
    IDX_CHAR_A,
    IDX_CHAR_VAL_A,
    IDX_CHAR_CFG_A,
    HRS_IDX_NB,
};
uint16_t midi_handle_table[HRS_IDX_NB];

static uint8_t midi_service_uuid[16] = {
  REMOTE_SERVICE_UUID
};

static const uint8_t midi_characteristics_uuid[16] = {
  REMOTE_CHAR_UUID
};

/* The length of adv data must be less than 31 bytes */
static esp_ble_adv_data_t adv_data = {
  .set_scan_rsp        = false,
  .include_name        = false, // exclude name to ensure that we don't exceed 31 bytes...
  .include_txpower     = true,
  .min_interval        = 0x0006, //slave connection min interval, Time = min_interval * 1.25 msec
  .max_interval        = 0x0010, //slave connection max interval, Time = max_interval * 1.25 msec
  .appearance          = 0x00,
  .manufacturer_len    = 0,    //TEST_MANUFACTURER_DATA_LEN,
  .p_manufacturer_data = NULL, //test_manufacturer,
  .service_data_len    = 0,
  .p_service_data      = NULL,
  .service_uuid_len    = sizeof(midi_service_uuid),
  .p_service_uuid      = midi_service_uuid,
  .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static esp_ble_adv_params_t adv_params = {
  .adv_int_min         = 0x20,
  .adv_int_max         = 0x40,
  .adv_type            = ADV_TYPE_IND,
  .own_addr_type       = BLE_ADDR_TYPE_PUBLIC,
  .channel_map         = ADV_CHNL_ALL,
  .adv_filter_policy   = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

////////////////////////////////////////////////////////////////////////////////
// GATTC GLOBAL ELEMENTS SECTION
////////////////////////////////////////////////////////////////////////////////

struct gattc_profile_inst {
  esp_gattc_cb_t gattc_cb;
  uint16_t gattc_if;
  uint16_t app_id;
  uint16_t conn_id;
  uint16_t service_start_handle;
  uint16_t service_end_handle;
  uint16_t char_handle;
  esp_bd_addr_t remote_bda;
};

static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);
static void gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);

static struct gattc_profile_inst gl_profile_tab[PROFILE_NUM] = {
  [PROFILE_A_APP_ID] = {
    .gattc_cb = gattc_profile_event_handler,
    .gattc_if = ESP_GATT_IF_NONE,       /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
  },
};

////////////////////////////////////////////////////////////////////////////////
// GATTS GLOBAL ELEMENTS SECTION
////////////////////////////////////////////////////////////////////////////////

struct gatts_profile_inst {
  esp_gatts_cb_t gatts_cb;
  uint16_t gatts_if;
  uint16_t app_id;
  uint16_t conn_id;
  uint16_t service_handle;
  esp_gatt_srvc_id_t service_id;
  uint16_t char_handle;
  esp_bt_uuid_t char_uuid;
  esp_gatt_perm_t perm;
  esp_gatt_char_prop_t property;
  uint16_t descr_handle;
  esp_bt_uuid_t descr_uuid;
};

static void gatts_profile_event_handler(esp_gatts_cb_event_t event,
                                        esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by ESP_GATTS_REG_EVT */
static struct gatts_profile_inst midi_profile_tab[PROFILE_NUM] = {
  [PROFILE_APP_IDX] = {
    .gatts_cb = gatts_profile_event_handler,
    .gatts_if = ESP_GATT_IF_NONE,       /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
  },
};

////////////////////////////////////////////////////////////////////////////////
// MIDI SECTION
////////////////////////////////////////////////////////////////////////////////

// the MTU can be changed by the client during runtime
static size_t blemidi_mtu = GATTS_MIDI_CHAR_VAL_LEN_MAX - 3;

// This timestamp should be increased each mS from the application via blemidi_tick_ms() call:
static uint16_t blemidi_timestamp = 0;

// we buffer outgoing MIDI messages for 10 mS - this should avoid that multiple BLE packets have to be queued for small messages
static uint8_t  blemidi_outbuffer[BLEMIDI_NUM_PORTS][GATTS_MIDI_CHAR_VAL_LEN_MAX];
static uint16_t blemidi_outbuffer_len[BLEMIDI_NUM_PORTS];
static uint16_t blemidi_outbuffer_timestamp_last_flush = 0;

// to handled continued SysEx
static size_t   blemidi_continued_sysex_pos[BLEMIDI_NUM_PORTS];

void (*blemidi_callback_midi_message_received)(uint8_t blemidi_port, uint16_t timestamp, uint8_t midi_status, uint8_t *remaining_message, size_t len, size_t continued_sysex_pos, void* arg);

void* callback_arg;

// ------ Time stamp handling --------
void blemidi_tick(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  blemidi_timestamp = (tv.tv_sec * 1000 + (tv.tv_usec / 1000)); // 1 mS per increment
  
  if( (blemidi_outbuffer_timestamp_last_flush > blemidi_timestamp) ||
  (blemidi_timestamp > (blemidi_outbuffer_timestamp_last_flush + BLEMIDI_OUTBUFFER_FLUSH_MS)) ) {
    uint8_t blemidi_port;
    for(blemidi_port=0; blemidi_port < BLEMIDI_NUM_PORTS; ++blemidi_port) {
      blemidi_outbuffer_flush(blemidi_port);
    }
    
    blemidi_outbuffer_timestamp_last_flush = blemidi_timestamp;
  }
}

uint8_t blemidi_timestamp_high(void)
{
  return (0x80 | ((blemidi_timestamp >> 7) & 0x3f));
}

uint8_t blemidi_timestamp_low(void)
{
  return (0x80 | (blemidi_timestamp & 0x7f));
}

// ----------------------------------

int32_t blemidi_outbuffer_flush(uint8_t blemidi_port)
{
  if( blemidi_port >= BLEMIDI_NUM_PORTS )
  return -1; // invalid port
  
  if( blemidi_outbuffer_len[blemidi_port] > 0 ) {
    esp_ble_gatts_send_indicate(midi_profile_tab[PROFILE_APP_IDX].gatts_if, midi_profile_tab[PROFILE_APP_IDX].conn_id, midi_handle_table[IDX_CHAR_VAL_A], blemidi_outbuffer_len[blemidi_port], blemidi_outbuffer[blemidi_port], false);
    blemidi_outbuffer_len[blemidi_port] = 0;
  }
  return 0; // no error
}

// Push a new MIDI message to the output buffer
static int32_t blemidi_outbuffer_push(uint8_t blemidi_port, uint8_t *stream, size_t len)
{
  const size_t max_header_size = 2;
  
  if( blemidi_port >= BLEMIDI_NUM_PORTS )
  return -1; // invalid port
  
  // if len >= MTU, it makes sense to send out immediately
  if( len >= (blemidi_mtu-max_header_size) ) {
    // this is very unlikely, since applemidi_send_message() maintains the size
    // but just in case of future extensions, we prepare dynamic memory allocation for "big packets"
    blemidi_outbuffer_flush(blemidi_port);
    {
      size_t packet_len = max_header_size + len;
      uint8_t *packet = malloc(packet_len);
      if( packet == NULL ) {
        return -1; // couldn't create temporary packet
      } else {
        // new packet: with timestampHigh and timestampLow, or in case of continued SysEx packet: only timestampHigh
        packet[0] = blemidi_timestamp_high();
        if( stream[0] >= 0x80 ) {
          packet[1] = blemidi_timestamp_low();
          memcpy((uint8_t *)packet + 2, stream, len);
        } else {
          packet_len -= 1;
          memcpy((uint8_t *)packet + 1, stream, len);
        }
        esp_ble_gatts_send_indicate(midi_profile_tab[PROFILE_APP_IDX].gatts_if, midi_profile_tab[PROFILE_APP_IDX].conn_id, midi_handle_table[IDX_CHAR_VAL_A], packet_len, packet, false);
        free(packet);
      }
    }
  } else {
    // flush buffer before adding new message
    if( (blemidi_outbuffer_len[blemidi_port] + len) >= blemidi_mtu )
    blemidi_outbuffer_flush(blemidi_port);
    
    // adding new message
    if( blemidi_outbuffer_len[blemidi_port] == 0 ) {
      // new packet: with timestampHigh and timestampLow, or in case of continued SysEx packet: only timestampHigh
      blemidi_outbuffer[blemidi_port][blemidi_outbuffer_len[blemidi_port]++] = blemidi_timestamp_high();
      if( stream[0] >= 0x80 ) {
        blemidi_outbuffer[blemidi_port][blemidi_outbuffer_len[blemidi_port]++] = blemidi_timestamp_low();
      }
    } else {
      blemidi_outbuffer[blemidi_port][blemidi_outbuffer_len[blemidi_port]++] = blemidi_timestamp_low();
    }
    
    memcpy(&blemidi_outbuffer[blemidi_port][blemidi_outbuffer_len[blemidi_port]], 
      stream, len);
    blemidi_outbuffer_len[blemidi_port] += len;
  }
  
  return 0; // no error
}

int32_t blemidi_send_message(uint8_t blemidi_port, uint8_t *stream, size_t len)
{
  const size_t max_header_size = 2;
  
  if( blemidi_port >= BLEMIDI_NUM_PORTS )
  return -1; // invalid port
  
  // we've to consider blemidi_mtu
  // if more bytes need to be sent, split over multiple packets
  // this will cost some extra stack space :-/ therefore handled separatly?
  
  if( len < (blemidi_mtu-max_header_size) ) {
    // just add to output buffer
    blemidi_outbuffer_push(blemidi_port, stream, len);
  } else {
    // sending packets
    size_t max_size = blemidi_mtu - max_header_size; // -3 since blemidi_outbuffer_push() will add the timestamps
    int pos;
    for(pos=0; pos<len; pos += max_size) {
      size_t packet_len = len-pos;
      if( packet_len >= max_size ) {
        packet_len = max_size;
      }
      blemidi_outbuffer_push(blemidi_port, &stream[pos], packet_len);
    }
  }
  
  return 0; // no error
}

static int32_t blemidi_receive_packet(uint8_t blemidi_port, uint8_t *stream, size_t len, void *_callback_midi_message_received)
{
  void (*callback_midi_message_received)(uint8_t blemidi_port, uint16_t timestamp, uint8_t midi_status, uint8_t *remaining_message, size_t len, size_t continued_sysex_pos, void* arg) = _callback_midi_message_received;
  
  if( blemidi_port >= BLEMIDI_NUM_PORTS )
  return -1; // invalid port
  
  ESP_LOGI(BLEMIDI_TAG, "receive_packet blemidi_port=%d, len=%d, stream:", blemidi_port, len);
  esp_log_buffer_hex(BLEMIDI_TAG, stream, len);
  
  // detect continued SysEx
  uint8_t continued_sysex = 0;
  if( len > 2 && (stream[0] & 0x80) && !(stream[1] & 0x80)) {
    continued_sysex = 1;
  } else {
    blemidi_continued_sysex_pos[blemidi_port] = 0;
  }
  
  
  if( len < 3 ) {
    ESP_LOGE(BLEMIDI_TAG, "stream length should be >=3");
    return -1;
  } else if( !(stream[0] & 0x80) ) {
    ESP_LOGE(BLEMIDI_TAG, "missing timestampHigh");
    return -2;
  } else {
    size_t pos = 0;
    
    // getting timestamp
    uint16_t timestamp = (stream[pos++] & 0x3f) << 7;
    
    // parsing stream
    {
      //! Number if expected bytes for a common MIDI event - 1
      const uint8_t midi_expected_bytes_common[8] = {
        2, // Note On
        2, // Note Off
        2, // Poly Preasure
        2, // Controller
        1, // Program Change
        1, // Channel Preasure
        2, // Pitch Bender
        0, // System Message - must be zero, so that mios32_midi_expected_bytes_system[] will be used
      };
      
      //! Number if expected bytes for a system MIDI event - 1
      const uint8_t midi_expected_bytes_system[16] = {
        1, // SysEx Begin (endless until SysEx End F7)
        1, // MTC Data frame
        2, // Song Position
        1, // Song Select
        0, // Reserved
        0, // Reserved
        0, // Request Tuning Calibration
        0, // SysEx End
        
        // Note: just only for documentation, Realtime Messages don't change the running status
        0, // MIDI Clock
        0, // MIDI Tick
        0, // MIDI Start
        0, // MIDI Continue
        0, // MIDI Stop
        0, // Reserved
        0, // Active Sense
        0, // Reset
      };
      
      uint8_t midi_status = continued_sysex ? 0xf0 : 0x00;
      
      while( pos < len ) {
        if( !(stream[pos] & 0x80) ) {
          if( !continued_sysex ) {
            ESP_LOGE(BLEMIDI_TAG, "missing timestampLow in parsed message");
            return -3;
          }
        } else {
          timestamp &= ~0x7f;
          timestamp |= stream[pos++] & 0x7f;
          continued_sysex = 0;
          blemidi_continued_sysex_pos[blemidi_port] = 0;
        }
        
        if( stream[pos] & 0x80 ) {
          midi_status = stream[pos++];
        }
        
        if( midi_status == 0xf0 ) {
          size_t num_bytes;
          for(num_bytes=0; stream[pos+num_bytes] < 0x80; ++num_bytes) {
            if( (pos+num_bytes) >= len ) {
              break;
            }
          }
          if( _callback_midi_message_received ) {
            callback_midi_message_received(blemidi_port, timestamp, midi_status, &stream[pos], num_bytes, blemidi_continued_sysex_pos[blemidi_port], callback_arg);
          }
          pos += num_bytes;
          blemidi_continued_sysex_pos[blemidi_port] += num_bytes; // we expect another packet with the remaining SysEx stream
        } else {
          uint8_t num_bytes = midi_expected_bytes_common[(midi_status >> 4) & 0x7];
          if( num_bytes == 0 ) { // System Message
            num_bytes = midi_expected_bytes_system[midi_status & 0xf];
          }
          
          if( (pos+num_bytes) > len ) {
            ESP_LOGE(BLEMIDI_TAG, "missing %d bytes in parsed message", num_bytes);
            return -5;
          } else {
            if( _callback_midi_message_received ) {
              callback_midi_message_received(blemidi_port, timestamp, midi_status, &stream[pos], num_bytes, 0, callback_arg);
            }
            pos += num_bytes;
          }
        }
      }
    }
  }  
  return 0; // no error
}

////////////////////////////////////////////////////////////////////////////////
// GAP SECTION
////////////////////////////////////////////////////////////////////////////////

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
  uint8_t *adv_name = NULL;
  uint8_t adv_name_len = 0;
  switch (event) {
    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
      //the unit of the duration is second
      uint32_t duration = 30;
      esp_ble_gap_start_scanning(duration);
      break;
    }
    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
    //scan start complete event to indicate scan start successfully or failed
    if (param->scan_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
      ESP_LOGE(BLEMIDI_TAG, "scan start failed, error status = %x", param->scan_start_cmpl.status);
      break;
    }
    ESP_LOGI(BLEMIDI_TAG, "scan start success");
    
    break;
    case ESP_GAP_BLE_SCAN_RESULT_EVT: {
      esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
      switch (scan_result->scan_rst.search_evt) {
        case ESP_GAP_SEARCH_INQ_RES_EVT:
        esp_log_buffer_hex(BLEMIDI_TAG, scan_result->scan_rst.bda, 6);
        ESP_LOGI(BLEMIDI_TAG, "searched Adv Data Len %d, Scan Response Len %d", scan_result->scan_rst.adv_data_len, scan_result->scan_rst.scan_rsp_len);
        adv_name = esp_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
          ESP_BLE_AD_TYPE_NAME_CMPL, &adv_name_len);
          ESP_LOGI(BLEMIDI_TAG, "searched Device Name Len %d", adv_name_len);
          esp_log_buffer_char(BLEMIDI_TAG, adv_name, adv_name_len);
          ESP_LOGI(BLEMIDI_TAG, "\n");
          
          if (adv_name != NULL) {
            if (strlen(remote_device_name) == adv_name_len && strncmp((char *)adv_name, remote_device_name, adv_name_len) == 0) {
              ESP_LOGI(BLEMIDI_TAG, "searched device %s\n", remote_device_name);
              if (connect == false) {
                connect = true;
                ESP_LOGI(BLEMIDI_TAG, "connect to the remote device.");
                esp_ble_gap_stop_scanning();
                esp_ble_gattc_open(gl_profile_tab[PROFILE_A_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
              }
            }
          }
          break;
          case ESP_GAP_SEARCH_INQ_CMPL_EVT:
          break;
          default:
          break;
        }
        break;
      }
      case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
      if (param->scan_stop_cmpl.status != ESP_BT_STATUS_SUCCESS){
        ESP_LOGE(BLEMIDI_TAG, "scan stop failed, error status = %x", param->scan_stop_cmpl.status);
        break;
      }
      ESP_LOGI(BLEMIDI_TAG, "stop scan successfully");
      break;  
      case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
      adv_config_done &= (~ADV_CONFIG_FLAG);
      if (adv_config_done == 0){
        esp_ble_gap_start_advertising(&adv_params);
      }
      break;
      case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
      adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
      if (adv_config_done == 0){
        esp_ble_gap_start_advertising(&adv_params);
      }
      break;
      case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
      /* advertising start complete event to indicate advertising start successfully or failed */
      if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
        ESP_LOGE(BLEMIDI_TAG, "advertising start failed");
      }else{
        ESP_LOGI(BLEMIDI_TAG, "advertising start successfully");
      }
      break;
      case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
      if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
        ESP_LOGE(BLEMIDI_TAG, "Advertising stop failed");
      }
      else {
        ESP_LOGI(BLEMIDI_TAG, "Stop adv successfully\n");
      }
      break;
      case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
      ESP_LOGI(BLEMIDI_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
      param->update_conn_params.status,
      param->update_conn_params.min_int,
      param->update_conn_params.max_int,
      param->update_conn_params.conn_int,
      param->update_conn_params.latency,
      param->update_conn_params.timeout);
      break;
      default:
      break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// GATT CLIENT SECTION
////////////////////////////////////////////////////////////////////////////////

static esp_ble_scan_params_t ble_scan_params = {
  .scan_type              = BLE_SCAN_TYPE_ACTIVE,
  .own_addr_type          = BLE_ADDR_TYPE_PUBLIC,
  .scan_filter_policy     = BLE_SCAN_FILTER_ALLOW_ALL,
  .scan_interval          = 0x50,
  .scan_window            = 0x30,
  .scan_duplicate         = BLE_SCAN_DUPLICATE_DISABLE
};

static esp_bt_uuid_t remote_filter_service_uuid = {
    .len = ESP_UUID_LEN_128,
    .uuid = {.uuid128 = {REMOTE_SERVICE_UUID},},
};

static esp_bt_uuid_t remote_filter_char_uuid = {
    .len = ESP_UUID_LEN_128,
    .uuid = {.uuid128 = {REMOTE_CHAR_UUID},},
};

static esp_bt_uuid_t notify_descr_uuid = {
  .len = ESP_UUID_LEN_16,
  .uuid = {.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG,},
};

static void gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{
  esp_ble_gattc_cb_param_t *p_data = (esp_ble_gattc_cb_param_t *)param;
  switch (event) {
    case ESP_GATTC_REG_EVT:
    ESP_LOGI(BLEMIDI_TAG, "REG_EVT");
    esp_err_t scan_ret = esp_ble_gap_set_scan_params(&ble_scan_params);
    if (scan_ret){
      ESP_LOGE(BLEMIDI_TAG, "set scan params error, error code = %x", scan_ret);
    }
    // esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
    // ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
    break;
    case ESP_GATTC_CONNECT_EVT:{
      ESP_LOGI(BLEMIDI_TAG, "ESP_GATTC_CONNECT_EVT conn_id %d, if %d", p_data->connect.conn_id, gattc_if);
      gl_profile_tab[PROFILE_A_APP_ID].conn_id = p_data->connect.conn_id;
      memcpy(gl_profile_tab[PROFILE_A_APP_ID].remote_bda, p_data->connect.remote_bda, sizeof(esp_bd_addr_t));
      ESP_LOGI(BLEMIDI_TAG, "REMOTE BDA:");
      esp_log_buffer_hex(BLEMIDI_TAG, gl_profile_tab[PROFILE_A_APP_ID].remote_bda, sizeof(esp_bd_addr_t));
      esp_err_t mtu_ret = esp_ble_gattc_send_mtu_req (gattc_if, p_data->connect.conn_id);
      if (mtu_ret){
        ESP_LOGE(BLEMIDI_TAG, "config MTU error, error code = %x", mtu_ret);
      }
      break;
    }
    case ESP_GATTC_OPEN_EVT:
    if (param->open.status != ESP_GATT_OK){
      ESP_LOGE(BLEMIDI_TAG, "open failed, status %d", p_data->open.status);
      break;
    }
    ESP_LOGI(BLEMIDI_TAG, "open success");
    break;
    case ESP_GATTC_DIS_SRVC_CMPL_EVT:
    if (param->dis_srvc_cmpl.status != ESP_GATT_OK){
      ESP_LOGE(BLEMIDI_TAG, "discover service failed, status %d", param->dis_srvc_cmpl.status);
      break;
    }
    ESP_LOGI(BLEMIDI_TAG, "discover service complete conn_id %d", param->dis_srvc_cmpl.conn_id);
    esp_ble_gattc_search_service(gattc_if, param->cfg_mtu.conn_id, &remote_filter_service_uuid);
    break;
    case ESP_GATTC_CFG_MTU_EVT:
    if (param->cfg_mtu.status != ESP_GATT_OK){
      ESP_LOGE(BLEMIDI_TAG,"config mtu failed, error status = %x", param->cfg_mtu.status);
    }
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTC_CFG_MTU_EVT, Status %d, MTU %d, conn_id %d", param->cfg_mtu.status, param->cfg_mtu.mtu, param->cfg_mtu.conn_id);
    break;
    case ESP_GATTC_SEARCH_RES_EVT: {
      ESP_LOGI(BLEMIDI_TAG, "SEARCH RES: conn_id = %x is primary service %d", p_data->search_res.conn_id, p_data->search_res.is_primary);
      ESP_LOGI(BLEMIDI_TAG, "start handle %d end handle %d current handle value %d", p_data->search_res.start_handle, p_data->search_res.end_handle, p_data->search_res.srvc_id.inst_id);
      if (p_data->search_res.srvc_id.uuid.len == ESP_UUID_LEN_128) {
        ESP_LOGI(BLEMIDI_TAG, "service found with UUID128");
        get_server = true;
        gl_profile_tab[PROFILE_A_APP_ID].service_start_handle = p_data->search_res.start_handle;
        gl_profile_tab[PROFILE_A_APP_ID].service_end_handle = p_data->search_res.end_handle;
      }
      break;
    }
    case ESP_GATTC_SEARCH_CMPL_EVT:
    if (p_data->search_cmpl.status != ESP_GATT_OK){
      ESP_LOGE(BLEMIDI_TAG, "search service failed, error status = %x", p_data->search_cmpl.status);
      break;
    }
    if(p_data->search_cmpl.searched_service_source == ESP_GATT_SERVICE_FROM_REMOTE_DEVICE) {
      ESP_LOGI(BLEMIDI_TAG, "Get service information from remote device");
    } else if (p_data->search_cmpl.searched_service_source == ESP_GATT_SERVICE_FROM_NVS_FLASH) {
      ESP_LOGI(BLEMIDI_TAG, "Get service information from flash");
    } else {
      ESP_LOGI(BLEMIDI_TAG, "unknown service source");
    }
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTC_SEARCH_CMPL_EVT");
    if (get_server){
      uint16_t count = 0;
      esp_gatt_status_t status = esp_ble_gattc_get_attr_count( gattc_if,
        p_data->search_cmpl.conn_id,
        ESP_GATT_DB_CHARACTERISTIC,
        gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
        gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
        INVALID_HANDLE,
      &count);
      if (status != ESP_GATT_OK){
        ESP_LOGE(BLEMIDI_TAG, "esp_ble_gattc_get_attr_count error");
      }  
      if (count > 0){
        char_elem_result = (esp_gattc_char_elem_t *)malloc(sizeof(esp_gattc_char_elem_t) * count);
        if (!char_elem_result){
          ESP_LOGE(BLEMIDI_TAG, "gattc no mem");
        }else{
          status = esp_ble_gattc_get_char_by_uuid( gattc_if,
            p_data->search_cmpl.conn_id,
            gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
            gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
            remote_filter_char_uuid,
            char_elem_result,
          &count);
          if (status != ESP_GATT_OK){
            ESP_LOGE(BLEMIDI_TAG, "esp_ble_gattc_get_char_by_uuid error");
          }
          
          /*  Every service have only one char in our 'ESP_GATTS_DEMO' demo, so we used first 'char_elem_result' */
          if (count > 0 && (char_elem_result[0].properties & ESP_GATT_CHAR_PROP_BIT_NOTIFY)){
            gl_profile_tab[PROFILE_A_APP_ID].char_handle = char_elem_result[0].char_handle;
            esp_ble_gattc_register_for_notify (gattc_if, gl_profile_tab[PROFILE_A_APP_ID].remote_bda, char_elem_result[0].char_handle);
          }
        }
        /* free char_elem_result */
        free(char_elem_result);
      }else{
        ESP_LOGE(BLEMIDI_TAG, "no char found");
      }
    }
    break;
    case ESP_GATTC_REG_FOR_NOTIFY_EVT: {
      ESP_LOGI(BLEMIDI_TAG, "ESP_GATTC_REG_FOR_NOTIFY_EVT");
      if (p_data->reg_for_notify.status != ESP_GATT_OK){
        ESP_LOGE(BLEMIDI_TAG, "REG FOR NOTIFY failed: error status = %d", p_data->reg_for_notify.status);
      }else{
        uint16_t count = 0;
        uint16_t notify_en = 1;
        esp_gatt_status_t ret_status = esp_ble_gattc_get_attr_count( gattc_if,
          gl_profile_tab[PROFILE_A_APP_ID].conn_id,
          ESP_GATT_DB_DESCRIPTOR,
          gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
          gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
          gl_profile_tab[PROFILE_A_APP_ID].char_handle,
        &count);
        if (ret_status != ESP_GATT_OK){
          ESP_LOGE(BLEMIDI_TAG, "esp_ble_gattc_get_attr_count error");
        }
        if (count > 0){
          descr_elem_result = malloc(sizeof(esp_gattc_descr_elem_t) * count);
          if (!descr_elem_result){
            ESP_LOGE(BLEMIDI_TAG, "malloc error, gattc no mem");
          }else{
            ret_status = esp_ble_gattc_get_descr_by_char_handle( gattc_if,
              gl_profile_tab[PROFILE_A_APP_ID].conn_id,
              p_data->reg_for_notify.handle,
              notify_descr_uuid,
              descr_elem_result,
            &count);
            if (ret_status != ESP_GATT_OK){
              ESP_LOGE(BLEMIDI_TAG, "esp_ble_gattc_get_descr_by_char_handle error");
            }
            /* Every char has only one descriptor in our 'ESP_GATTS_DEMO' demo, so we used first 'descr_elem_result' */
            if (count > 0 && descr_elem_result[0].uuid.len == ESP_UUID_LEN_16 && descr_elem_result[0].uuid.uuid.uuid16 == ESP_GATT_UUID_CHAR_CLIENT_CONFIG){
              ret_status = esp_ble_gattc_write_char_descr( gattc_if,
                gl_profile_tab[PROFILE_A_APP_ID].conn_id,
                descr_elem_result[0].handle,
                sizeof(notify_en),
                (uint8_t *)&notify_en,
                ESP_GATT_WRITE_TYPE_RSP,
              ESP_GATT_AUTH_REQ_NONE);
            }
            
            if (ret_status != ESP_GATT_OK){
              ESP_LOGE(BLEMIDI_TAG, "esp_ble_gattc_write_char_descr error");
            }
            
            /* free descr_elem_result */
            free(descr_elem_result);
          }
        }
        else{
          ESP_LOGE(BLEMIDI_TAG, "decsr not found");
        }
        
      }
      break;
    }
    case ESP_GATTC_NOTIFY_EVT:
    if (p_data->notify.is_notify){
      ESP_LOGI(BLEMIDI_TAG, "ESP_GATTC_NOTIFY_EVT, receive notify value:");
    }else{
      ESP_LOGI(BLEMIDI_TAG, "ESP_GATTC_NOTIFY_EVT, receive indicate value:");
    }
    esp_log_buffer_hex(BLEMIDI_TAG, p_data->notify.value, p_data->notify.value_len);
    blemidi_receive_packet(0, p_data->notify.value, p_data->notify.value_len, blemidi_callback_midi_message_received);
    break;
    case ESP_GATTC_WRITE_DESCR_EVT:
    if (p_data->write.status != ESP_GATT_OK){
      ESP_LOGE(BLEMIDI_TAG, "write descr failed, error status = %x", p_data->write.status);
      break;
    }
    ESP_LOGI(BLEMIDI_TAG, "write descr success ");
    uint8_t write_char_data[35];
    for (int i = 0; i < sizeof(write_char_data); ++i)
    {
      write_char_data[i] = i % 256;
    }
    esp_ble_gattc_write_char( gattc_if,
      gl_profile_tab[PROFILE_A_APP_ID].conn_id,
      gl_profile_tab[PROFILE_A_APP_ID].char_handle,
      sizeof(write_char_data),
      write_char_data,
      ESP_GATT_WRITE_TYPE_RSP,
    ESP_GATT_AUTH_REQ_NONE);
    break;
    case ESP_GATTC_SRVC_CHG_EVT: {
      esp_bd_addr_t bda;
      memcpy(bda, p_data->srvc_chg.remote_bda, sizeof(esp_bd_addr_t));
      ESP_LOGI(BLEMIDI_TAG, "ESP_GATTC_SRVC_CHG_EVT, bd_addr:");
      esp_log_buffer_hex(BLEMIDI_TAG, bda, sizeof(esp_bd_addr_t));
      break;
    }
    case ESP_GATTC_WRITE_CHAR_EVT:
    if (p_data->write.status != ESP_GATT_OK){
      ESP_LOGE(BLEMIDI_TAG, "write char failed, error status = %x", p_data->write.status);
      break;
    }
    ESP_LOGI(BLEMIDI_TAG, "write char success ");
    break;
    case ESP_GATTC_DISCONNECT_EVT:
    connect = false;
    get_server = false;
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTC_DISCONNECT_EVT, reason = %d", p_data->disconnect.reason);
    break;
    default:
    break;
  }
}

static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{
  /* If event is register event, store the gattc_if for each profile */
  if (event == ESP_GATTC_REG_EVT) {
    if (param->reg.status == ESP_GATT_OK) {
      gl_profile_tab[param->reg.app_id].gattc_if = gattc_if;
    } else {
      ESP_LOGI(BLEMIDI_TAG, "reg app failed, app_id %04x, status %d",
      param->reg.app_id,
      param->reg.status);
      return;
    }
  }
  
  /* If the gattc_if equal to profile A, call profile A cb handler,
  * so here call each profile's callback */
  do {
    int idx;
    for (idx = 0; idx < PROFILE_NUM; idx++) {
      if (gattc_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
        gattc_if == gl_profile_tab[idx].gattc_if) {
          if (gl_profile_tab[idx].gattc_cb) {
            gl_profile_tab[idx].gattc_cb(event, gattc_if, param);
          }
        }
      }
    } while (0);
  }

////////////////////////////////////////////////////////////////////////////////
// GATT SERVER SECTION
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    uint8_t                 *prepare_buf;
    int                     prepare_len;
} prepare_type_env_t;

static prepare_type_env_t prepare_write_env;

// scan response data
static esp_ble_adv_data_t scan_rsp_data = {
  .set_scan_rsp        = true,
  .include_name        = true,
  .include_txpower     = true,
  .min_interval        = 0x0006,
  .max_interval        = 0x0010,
  .appearance          = 0x00,
  .manufacturer_len    = 0, //TEST_MANUFACTURER_DATA_LEN,
  .p_manufacturer_data = NULL, //&test_manufacturer[0],
  .service_data_len    = 0,
  .p_service_data      = NULL,
  .service_uuid_len    = sizeof(midi_service_uuid),
  .p_service_uuid      = midi_service_uuid,
  .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

/* Service */
static const uint16_t primary_service_uuid         = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid   = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
// RM: commented below 
//static const uint8_t char_prop_read                = ESP_GATT_CHAR_PROP_BIT_READ;
//static const uint8_t char_prop_write               = ESP_GATT_CHAR_PROP_BIT_WRITE;
//static const uint8_t char_prop_read_write_notify   = ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t char_prop_read_write_writenr_notify = ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY | ESP_GATT_CHAR_PROP_BIT_WRITE_NR;

static const uint8_t char_value[3]                 = {0x80, 0x80, 0xfe};
static const uint8_t blemidi_ccc[2]                = {0x00, 0x00};

// Full Database Description - Used to add attributes into the database
static const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB] =
{
  // Service Declaration
  [IDX_SVC]        =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
    16, sizeof(midi_service_uuid), (uint8_t *)&midi_service_uuid}},
    
  // Characteristic Declaration
  [IDX_CHAR_A]     =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&char_prop_read_write_writenr_notify}},
      
  // Characteristic Value
  [IDX_CHAR_VAL_A] =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_128, (uint8_t *)&midi_characteristics_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
    GATTS_MIDI_CHAR_VAL_LEN_MAX, sizeof(char_value), (uint8_t *)char_value}},
        
  // Client Characteristic Configuration Descriptor (this is a BLE2902 descriptor)
  [IDX_CHAR_CFG_A]  =
  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
  sizeof(uint16_t), sizeof(blemidi_ccc), (uint8_t *)blemidi_ccc}},
};

static void blemidi_prepare_write_event_env(esp_gatt_if_t gatts_if, prepare_type_env_t *prepare_write_env, esp_ble_gatts_cb_param_t *param)
{
  ESP_LOGI(BLEMIDI_TAG, "prepare write, handle = %d, value len = %d", param->write.handle, param->write.len);
  esp_gatt_status_t status = ESP_GATT_OK;
  if (prepare_write_env->prepare_buf == NULL) {
    prepare_write_env->prepare_buf = (uint8_t *)malloc(PREPARE_BUF_MAX_SIZE * sizeof(uint8_t));
    prepare_write_env->prepare_len = 0;
    if (prepare_write_env->prepare_buf == NULL) {
      ESP_LOGE(BLEMIDI_TAG, "%s, Gatt_server prep no mem", __func__);
      status = ESP_GATT_NO_RESOURCES;
    }
  } else {
    if(param->write.offset > PREPARE_BUF_MAX_SIZE) {
      status = ESP_GATT_INVALID_OFFSET;
    } else if ((param->write.offset + param->write.len) > PREPARE_BUF_MAX_SIZE) {
      status = ESP_GATT_INVALID_ATTR_LEN;
    }
  }
  /*send response when param->write.need_rsp is true */
  if (param->write.need_rsp){
    esp_gatt_rsp_t *gatt_rsp = (esp_gatt_rsp_t *)malloc(sizeof(esp_gatt_rsp_t));
    if (gatt_rsp != NULL){
      gatt_rsp->attr_value.len = param->write.len;
      gatt_rsp->attr_value.handle = param->write.handle;
      gatt_rsp->attr_value.offset = param->write.offset;
      gatt_rsp->attr_value.auth_req = ESP_GATT_AUTH_REQ_NONE;
      memcpy(gatt_rsp->attr_value.value, param->write.value, param->write.len);
      esp_err_t response_err = esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, status, gatt_rsp);
      if (response_err != ESP_OK){
        ESP_LOGE(BLEMIDI_TAG, "Send response error");
      }
      free(gatt_rsp);
    }else{
      ESP_LOGE(BLEMIDI_TAG, "%s, malloc failed", __func__);
    }
  }
  if (status != ESP_GATT_OK){
    return;
  }
  memcpy(prepare_write_env->prepare_buf + param->write.offset,
    param->write.value,
    param->write.len);
    prepare_write_env->prepare_len += param->write.len;
  }

static void blemidi_exec_write_event_env(prepare_type_env_t *prepare_write_env, esp_ble_gatts_cb_param_t *param){
  if (param->exec_write.exec_write_flag == ESP_GATT_PREP_WRITE_EXEC && prepare_write_env->prepare_buf){
    esp_log_buffer_hex(BLEMIDI_TAG, prepare_write_env->prepare_buf, prepare_write_env->prepare_len);
  }else{
    ESP_LOGI(BLEMIDI_TAG,"ESP_GATT_PREP_WRITE_CANCEL");
  }
  if (prepare_write_env->prepare_buf) {
    free(prepare_write_env->prepare_buf);
    prepare_write_env->prepare_buf = NULL;
  }
  prepare_write_env->prepare_len = 0;
}

static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
  switch (event) {
    case ESP_GATTS_REG_EVT:{
      esp_err_t set_dev_name_ret = esp_ble_gap_set_device_name(current_device_name);
      if (set_dev_name_ret){
        ESP_LOGE(BLEMIDI_TAG, "set device name failed, error code = %x", set_dev_name_ret);
      }
      
      //config adv data
      esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
      if (ret){
        ESP_LOGE(BLEMIDI_TAG, "config adv data failed, error code = %x", ret);
      }
      adv_config_done |= ADV_CONFIG_FLAG;
      //config scan response data
      ret = esp_ble_gap_config_adv_data(&scan_rsp_data);
      if (ret){
        ESP_LOGE(BLEMIDI_TAG, "config scan response data failed, error code = %x", ret);
      }
      adv_config_done |= SCAN_RSP_CONFIG_FLAG;
      
      esp_err_t create_attr_ret = esp_ble_gatts_create_attr_tab(gatt_db, gatts_if, HRS_IDX_NB, SVC_INST_ID);
      if (create_attr_ret){
        ESP_LOGE(BLEMIDI_TAG, "create attr table failed, error code = %x", create_attr_ret);
      }
    }
    break;
    case ESP_GATTS_READ_EVT:
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTS_READ_EVT");
    break;
    case ESP_GATTS_WRITE_EVT:
    if (!param->write.is_prep){
      if (midi_handle_table[IDX_CHAR_VAL_A] == param->write.handle ) {
        // the data length of gattc write  must be less than blemidi_mtu.
        #if 0             
        ESP_LOGI(BLEMIDI_TAG, "GATT_WRITE_EVT, handle = %d, value len = %d, value :", param->write.handle, param->write.len);
        esp_log_buffer_hex(BLEMIDI_TAG, param->write.value, param->write.len);
        #endif
        blemidi_receive_packet(0, param->write.value, param->write.len, blemidi_callback_midi_message_received);
      }
    } else {
      /* handle prepare write */
      blemidi_prepare_write_event_env(gatts_if, &prepare_write_env, param);
    }
    break;
    case ESP_GATTS_EXEC_WRITE_EVT: 
    // the length of gattc prepare write data must be less than blemidi_mtu. 
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTS_EXEC_WRITE_EVT");
    blemidi_exec_write_event_env(&prepare_write_env, param);
    break;
    case ESP_GATTS_MTU_EVT:
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTS_MTU_EVT, MTU %d", param->mtu.mtu);
    
    // change MTU for BLE MIDI transactions
    if( param->mtu.mtu <= 3 ) {
      blemidi_mtu = 3; // very unlikely...
    } else {
      // we decrease -10 to prevent following driver warning:
      //  (30774) BT_GATT: attribute value too long, to be truncated to 97
      blemidi_mtu = param->mtu.mtu - 3;
      // failsave
      if( blemidi_mtu > (GATTS_MIDI_CHAR_VAL_LEN_MAX-3) )
      blemidi_mtu = (GATTS_MIDI_CHAR_VAL_LEN_MAX-3);
    }
    break;
    case ESP_GATTS_CONF_EVT:
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTS_CONF_EVT, status = %d, attr_handle %d", param->conf.status, param->conf.handle);
    break;
    case ESP_GATTS_START_EVT:
    ESP_LOGI(BLEMIDI_TAG, "SERVICE_START_EVT, status %d, service_handle %d", param->start.status, param->start.service_handle);
    break;
    case ESP_GATTS_CONNECT_EVT:
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTS_CONNECT_EVT, conn_id = %d", param->connect.conn_id);
    esp_log_buffer_hex(BLEMIDI_TAG, param->connect.remote_bda, 6);
    esp_ble_conn_update_params_t conn_params = {0};
    memcpy(conn_params.bda, param->connect.remote_bda, sizeof(esp_bd_addr_t));
    /* For the iOS system, please refer to Apple official documents about the BLE connection parameters restrictions. */
    conn_params.latency = 0;
    conn_params.max_int = 0x10;    // max_int = 0x10*1.25ms = 20ms
    conn_params.min_int = 0x0b;    // min_int = 0x0b*1.25ms = 15ms
    conn_params.timeout = 400;    // timeout = 400*10ms = 4000ms
    //start sent the update connection parameters to the peer device.
    esp_ble_gap_update_conn_params(&conn_params);
    break;
    case ESP_GATTS_DISCONNECT_EVT:
    ESP_LOGI(BLEMIDI_TAG, "ESP_GATTS_DISCONNECT_EVT, reason = 0x%x", param->disconnect.reason);
    esp_ble_gap_start_advertising(&adv_params);
    break;
    case ESP_GATTS_CREAT_ATTR_TAB_EVT:{
      if (param->add_attr_tab.status != ESP_GATT_OK){
        ESP_LOGE(BLEMIDI_TAG, "create attribute table failed, error code=0x%x", param->add_attr_tab.status);
      }
      else if (param->add_attr_tab.num_handle != HRS_IDX_NB){
        ESP_LOGE(BLEMIDI_TAG, "create attribute table abnormally, num_handle (%d) \
        doesn't equal to HRS_IDX_NB(%d)", param->add_attr_tab.num_handle, HRS_IDX_NB);
      }
      else {
        ESP_LOGI(BLEMIDI_TAG, "create attribute table successfully, the number handle = %d\n",param->add_attr_tab.num_handle);
        memcpy(midi_handle_table, param->add_attr_tab.handles, sizeof(midi_handle_table));
        esp_ble_gatts_start_service(midi_handle_table[IDX_SVC]);
      }
      break;
    }
    case ESP_GATTS_STOP_EVT:
    case ESP_GATTS_OPEN_EVT:
    case ESP_GATTS_CANCEL_OPEN_EVT:
    case ESP_GATTS_CLOSE_EVT:
    case ESP_GATTS_LISTEN_EVT:
    case ESP_GATTS_CONGEST_EVT:
    case ESP_GATTS_UNREG_EVT:
    case ESP_GATTS_DELETE_EVT:
    default:
    break;
  }
}

static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
  /* If event is register event, store the gatts_if for each profile */
  if (event == ESP_GATTS_REG_EVT) {
    if (param->reg.status == ESP_GATT_OK) {
      midi_profile_tab[PROFILE_APP_IDX].gatts_if = gatts_if;
    } else {
      ESP_LOGE(BLEMIDI_TAG, "reg app failed, app_id %04x, status %d",
      param->reg.app_id,
      param->reg.status);
      return;
    }
  }
  do {
    int idx;
    for (idx = 0; idx < PROFILE_NUM; idx++) {
      /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
      if (gatts_if == ESP_GATT_IF_NONE || gatts_if == midi_profile_tab[idx].gatts_if) {
        if (midi_profile_tab[idx].gatts_cb) {
          midi_profile_tab[idx].gatts_cb(event, gatts_if, param);
        }
      }
    }
  } while (0);
}

///////////////////////////////////////////////////////////////////////////////
// INITIALIZING THE BLE MIDI SERVER
//
// This function should be called from the Faust MIDI handler
// It initializes both a GATT client and a GATT server. This might somewhat
// risky so if there are bugs, that should be the first place to look.
///////////////////////////////////////////////////////////////////////////////

int32_t blemidi_init(void *_callback_midi_message_received, const char* device_name, const char* remote_name, void *arg)
{
  esp_err_t ret;
  
  current_device_name = device_name;
  remote_device_name = remote_name;
  callback_arg = arg;
  
  // callback will be installed if driver was booted successfully
  blemidi_callback_midi_message_received = NULL;
  
  /* Initialize NVS. */
  ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK( ret );
  
  ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));
  
  /* Initialize Bluedroid. */
  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  ret = esp_bt_controller_init(&bt_cfg);
  if (ret) {
    ESP_LOGE(BLEMIDI_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
    return -1;
  }
  
  ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
  if (ret) {
    ESP_LOGE(BLEMIDI_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
    return -2;
  }
  
  ret = esp_bluedroid_init();
  if (ret) {
    ESP_LOGE(BLEMIDI_TAG, "%s init bluetooth failed: %s", __func__, esp_err_to_name(ret));
    return -3;
  }
  
  ret = esp_bluedroid_enable();
  if (ret) {
    ESP_LOGE(BLEMIDI_TAG, "%s enable bluetooth failed: %s", __func__, esp_err_to_name(ret));
    return -4;
  }
  
  ret = esp_ble_gatts_register_callback(gatts_event_handler);
  if (ret){
    ESP_LOGE(BLEMIDI_TAG, "gatts register error, error code = %x", ret);
    return -5;
  }
  
  ret = esp_ble_gap_register_callback(gap_event_handler);
  if (ret){
    ESP_LOGE(BLEMIDI_TAG, "gap register error, error code = %x", ret);
    return -6;
  }
  
  ret = esp_ble_gatts_app_register(ESP_APP_ID);
  if (ret){
    ESP_LOGE(BLEMIDI_TAG, "gatts app register error, error code = %x", ret);
    return -7;
  }
  
  if(strcmp(remote_name,"") != 0){
    ret = esp_ble_gattc_register_callback(esp_gattc_cb);
    if (ret){
      ESP_LOGE(BLEMIDI_TAG, "gattc register failed, error code = %x", ret);
      return -8;
    }
  
    ret = esp_ble_gattc_app_register(PROFILE_A_APP_ID);
    if (ret){
      ESP_LOGE(BLEMIDI_TAG, "gattc app register error, error code = %x", ret);
      return -9;
    }
  }
  
  esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(GATTS_MIDI_CHAR_VAL_LEN_MAX);
  if (local_mtu_ret){
    ESP_LOGE(BLEMIDI_TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    return -10;
  }
  
  // Output Buffer
  {
    uint32_t blemidi_port;
    for(blemidi_port=0; blemidi_port<BLEMIDI_NUM_PORTS; ++blemidi_port) {
      blemidi_outbuffer_len[blemidi_port] = 0;
      blemidi_continued_sysex_pos[blemidi_port] = 0;
    }
  }
  
  // Finally install callback
  blemidi_callback_midi_message_received = _callback_midi_message_received;
  
  esp_log_level_set(BLEMIDI_TAG, ESP_LOG_WARN); // can be changed with the "blemidi_debug on" console command
  
  return 0; // no error
}
