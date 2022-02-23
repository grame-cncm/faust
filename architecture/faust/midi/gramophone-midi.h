/************************** BEGIN gramophone-midi.h ***********************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __gramophone_midi__
#define __gramophone_midi__

#include "blemidi.h"
#include "esp_log.h"
#include "faust/gui/meta.h"

struct bt_meta : Meta
{
    // default values
    std::string localName = "Gramophone";
    std::string remoteName = "";
    void declare(const char* key, const char* value)
    {
        if (strstr(key,"btmidi_device_name") != NULL) {
            localName = value;
        }
        else if (strstr(key,"btmidi_remote_name") != NULL) {
            remoteName = value;
        }
    }
};

#define GMH_TAG "GramoMidiHandler"

class gramophone_midi : public midi_handler {
    
    private:
    
        bt_meta fBTMeta;
    
        static void callback_midi_message_received(uint8_t blemidi_port,
                                                   uint16_t timestamp,
                                                   uint8_t midi_status,
                                                   uint8_t* remaining_message,
                                                   size_t len,
                                                   size_t continued_sysex_pos,
                                                   void* arg)
        {
            gramophone_midi* midi = static_cast<gramophone_midi*>(arg);
            if (len == 1) {
                midi->handleData1(timestamp,(int)midi_status,0,
                                  (int)remaining_message[0]);
            } else if (len == 2) {
                midi->handleData2(timestamp,(int)midi_status,0,
                                  (int)remaining_message[0],
                                  (int)remaining_message[1]);
            }
        }
    
    public:
    
        gramophone_midi(bt_meta& btMeta) : midi_handler("gramophone")
        {
            fBTMeta = btMeta;
        }
    
        virtual ~gramophone_midi()
        {
            stopMidi();
        }
    
        bool startMidi()
        {
            int status = blemidi_init((void*)callback_midi_message_received, fBTMeta.localName.c_str(), fBTMeta.remoteName.c_str(), (void*)this);
            if (status < 0) {
                ESP_LOGE(GMH_TAG, "BLE MIDI Driver returned status=%d", status);
                return false;
            } else {
                ESP_LOGI(GMH_TAG, "BLE MIDI Driver initialized successfully");
                return true;
            }
        }
    
        void stopMidi()
        {
            // This should probably implemented eventually but it can remaind as is for now
        }
    
};

#endif
/**************************  END  gramophone-midi.h **************************/
