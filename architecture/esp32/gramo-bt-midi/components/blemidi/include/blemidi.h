/*
BLE MIDI driver based on a heavy-lifted version of https://github.com/midibox/esp32-idf-blemidi by Thorsten Klose (tk@midibox.org). The driver can act both as a server and as a client.  
*/

#ifndef _BLEMIDI_H
#define _BLEMIDI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

  
extern int32_t blemidi_init(void *callback_midi_message_received, const char* device_name, const char* remote_name, void *arg);

extern int32_t blemidi_send_message(uint8_t blemidi_port, uint8_t *stream, size_t len);

extern int32_t blemidi_outbuffer_flush(uint8_t blemidi_port);

extern void blemidi_tick(void);
  
extern uint8_t blemidi_timestamp_high(void);
    
extern uint8_t blemidi_timestamp_low(void);

#ifdef __cplusplus
}
#endif

#endif /* _BLEMIDI_H */
