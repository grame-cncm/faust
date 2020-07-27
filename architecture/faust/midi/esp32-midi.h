/************************** BEGIN esp32-midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __esp32_midi__
#define __esp32_midi__

#include <iostream>
#include <cstdlib>

#include "driver/uart.h"

#include "jdksmidi/world.h"
#include "jdksmidi/midi.h"
#include "jdksmidi/msg.h"
#include "jdksmidi/sysex.h"
#include "jdksmidi/parser.h"

#include "faust/midi/midi.h"

using namespace jdksmidi;

#ifndef RX1
#define RX1 GPIO_NUM_5
#endif

#ifndef TX1
#define TX1 GPIO_NUM_19
#endif

#define PORT_NUM UART_NUM_1
#define RX_BUF_SIZE 1024

class esp32_midi : public midi_handler {
    
    private:
    
        TaskHandle_t fProcessMidiHandle;
    
        void processMidi()
        {
            double time = 0;
            uint8_t data[RX_BUF_SIZE];
            MIDIParser parser;
            jdksMIDIMessage message;
            
            while (true) {
                int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE, 1);
                if (rxBytes > 0) {
                    for (int i = 0; i < rxBytes; i++) {
                        if (parser.Parse((uchar)data[i], &message)) {
                            unsigned char status = message.GetStatus();
                            if (status < 0xF0)
                            { // channel/system message discriminator.
                                unsigned char type = message.GetType();
                                switch (type)
                                {
                                case 0x80: // Note Off
                                    handleKeyOff(time, message.GetChannel(), message.GetNote(), message.GetVelocity());
                                    break;
                                case 0x90: // Note On
                                    handleKeyOn(time, message.GetChannel(), message.GetNote(), message.GetVelocity());
                                    break;
                                case 0xA0: // Poly Key Pressure
                                    handlePolyAfterTouch(time, message.GetChannel(), message.GetNote(), message.GetByte2());
                                    break;
                                case 0xB0: // Control Change
                                    handleCtrlChange(time, message.GetChannel(), message.GetController(), message.GetControllerValue());
                                    break;
                                case 0xC0: // Program Change // No Bank Select in faust?
                                    handleProgChange(time, message.GetChannel(), message.GetPGValue());
                                    break;
                                case 0xD0: // Channel Pressure
                                    handleAfterTouch(time, message.GetChannel(), message.GetChannelPressure());
                                    break;
                                case 0xE0: // Pitch Bend
                                    handlePitchWheel(time, message.GetChannel(), message.GetByte1(), message.GetByte2());
                                    break;
                                default:
                                    break;
                                }
                            }
                            else
                            {
                                switch (status)
                                {
                                case 0xF8: // Timing Clock
                                    handleClock(time);
                                    break;
                                // We can consider start and continue as identical messages.
                                case 0xFA: // Start
                                case 0xFB: // Continue
                                    handleStart(time);
                                    break;
                                case 0xFC: // Stop
                                    handleStop(time);
                                    break;
                                case 0xF0: // SysEx Start
                                    // TODO
                                    break;
                                case 0xF7: // SysEx Stop
                                    // TODO
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                        // Synchronize all GUI controllers
                        GUI::updateAllGuis();
                    }
                }
            }
        }
  
        static void processMidiHandler(void* arg)
        {
            static_cast<esp32_midi*>(arg)->processMidi();
        }
    
    public:
    
        esp32_midi():midi_handler("esp32"),fProcessMidiHandle(NULL)
        {
            // Setup UART for MIDI
            const uart_config_t uart_config = {
                .baud_rate = 31250,
                .data_bits = UART_DATA_8_BITS,
                .parity = UART_PARITY_DISABLE,
                .stop_bits = UART_STOP_BITS_1,
                .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
                .rx_flow_ctrl_thresh = 122,
                .use_ref_tick = false
            };
            uart_param_config(PORT_NUM, &uart_config);
            uart_set_pin(PORT_NUM, TX1, RX1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
            // We won't use a buffer for sending data.
            uart_driver_install(PORT_NUM, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
        }
    
        virtual ~esp32_midi()
        {
            stopMidi();
        }

        bool startMidi()
        {
            // Start MIDI receive task
            return (xTaskCreatePinnedToCore(processMidiHandler, "Faust MIDI Task", 4096, (void*)this, 5, &fProcessMidiHandle, 1) == pdPASS);
        }

        void stopMidi()
        {
            if (fProcessMidiHandle != nullptr) {
                vTaskDelete(fProcessMidiHandle);
                fProcessMidiHandle = nullptr;
            }
        }
   
};

#endif
/**************************  END  esp32-midi.h **************************/
