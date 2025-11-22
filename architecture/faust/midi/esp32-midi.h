/************************** BEGIN esp32-midi.h ****************************
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

#ifndef __esp32_midi__
#define __esp32_midi__

#include <cstdlib>

#include "driver/uart.h"
#include "esp_log.h"

#include "faust/midi/midi.h"

#ifndef RX1
#define RX1 GPIO_NUM_5
#endif

#ifndef TX1
#define TX1 GPIO_NUM_19
#endif

#define PORT_NUM UART_NUM_1

#define RX_BUF_SIZE 1024

#define TAG "MIDI_IO"


/**
 * MIDI handler for the ESP32 boards.
 */
class esp32_midi : public midi_handler {
    
    private:
    
        TaskHandle_t fProcessMidiHandle;
        
        /**
         * Simple MIDI parser implementation based on MIDI 1.0 specification.
         * Written from scratch for the FAUST project.
         */
        class MidiParser {
        private:
            uint8_t fRunningStatus;       // Current running status byte
            uint8_t fDataByte1;           // First data byte
            bool fWaitingForDataByte2;    // Waiting for second data byte
            
            // Determine if a byte is a status byte (bit 7 set)
            inline bool isStatusByte(uint8_t byte) const {
                return (byte & 0x80) != 0;
            }
            
            // Extract message type (upper nibble of status byte)
            inline uint8_t getMessageType(uint8_t status) const {
                return status & 0xF0;
            }
            
            // Extract channel (lower nibble of status byte)
            inline uint8_t getChannel(uint8_t status) const {
                return status & 0x0F;
            }
            
            // Determine number of data bytes needed for a message type
            int getExpectedDataBytes(uint8_t status) const {
                if (status >= 0xF8) {
                    // System Real-Time messages: no data bytes
                    return 0;
                } else if (status >= 0xF0) {
                    // System Common messages
                    switch (status) {
                        case 0xF0: // SysEx Start - variable length
                        case 0xF7: // SysEx End/Escape
                            return 0; // Handle separately
                        case 0xF1: // MIDI Time Code Quarter Frame
                        case 0xF3: // Song Select
                            return 1;
                        case 0xF2: // Song Position Pointer
                            return 2;
                        case 0xF4: // Undefined
                        case 0xF5: // Undefined
                        case 0xF6: // Tune Request
                            return 0;
                        default:
                            return 0;
                    }
                } else {
                    // Channel Voice/Mode messages
                    uint8_t type = getMessageType(status);
                    switch (type) {
                        case 0x80: // Note Off
                        case 0x90: // Note On
                        case 0xA0: // Polyphonic Key Pressure
                        case 0xB0: // Control Change
                        case 0xE0: // Pitch Bend
                            return 2;
                        case 0xC0: // Program Change
                        case 0xD0: // Channel Pressure
                            return 1;
                        default:
                            return 0;
                    }
                }
            }
            
        public:
            struct MidiMessage {
                uint8_t status;      // Complete status byte including channel
                uint8_t data1;       // First data byte
                uint8_t data2;       // Second data byte
                bool isComplete;     // Message is complete and valid
                
                // Helper to get channel from status
                uint8_t getChannel() const {
                    return status & 0x0F;
                }
                
                // Helper to get message type
                uint8_t getType() const {
                    return status & 0xF0;
                }
            };
            
            MidiParser() : fRunningStatus(0), fDataByte1(0), fWaitingForDataByte2(false) {}
            
            /**
             * Parse a single MIDI byte and return a message when complete.
             * Based on MIDI 1.0 specification for message parsing.
             */
            MidiMessage parse(uint8_t byte) {
                MidiMessage msg = {0, 0, 0, false};
                
                // System Real-Time messages can appear anywhere
                if (byte >= 0xF8) {
                    msg.status = byte;
                    msg.isComplete = true;
                    return msg;
                }
                
                // Check if this is a new status byte
                if (isStatusByte(byte)) {
                    // System Common messages cancel running status
                    if (byte >= 0xF0 && byte < 0xF8) {
                        fRunningStatus = 0;
                        msg.status = byte;
                        
                        // Some system common messages have no data bytes
                        if (getExpectedDataBytes(byte) == 0) {
                            msg.isComplete = true;
                        }
                        return msg;
                    }
                    
                    // Channel Voice/Mode message - update running status
                    fRunningStatus = byte;
                    fWaitingForDataByte2 = false;
                    return msg; // Not complete yet
                }
                
                // This is a data byte (bit 7 clear)
                if (fRunningStatus == 0) {
                    // No running status - ignore this data byte
                    return msg;
                }
                
                int expectedBytes = getExpectedDataBytes(fRunningStatus);
                
                if (expectedBytes == 0) {
                    // No data bytes expected
                    return msg;
                } else if (expectedBytes == 1) {
                    // Single data byte message
                    msg.status = fRunningStatus;
                    msg.data1 = byte;
                    msg.isComplete = true;
                    return msg;
                } else {
                    // Two data byte message
                    if (!fWaitingForDataByte2) {
                        // This is the first data byte
                        fDataByte1 = byte;
                        fWaitingForDataByte2 = true;
                        return msg; // Not complete yet
                    } else {
                        // This is the second data byte - message complete
                        msg.status = fRunningStatus;
                        msg.data1 = fDataByte1;
                        msg.data2 = byte;
                        msg.isComplete = true;
                        fWaitingForDataByte2 = false;
                        return msg;
                    }
                }
            }
            
            // Reset parser state
            void reset() {
                fRunningStatus = 0;
                fDataByte1 = 0;
                fWaitingForDataByte2 = false;
            }
        };
            
        void processMidi()
        {
            double time = 0;
            MidiParser parser;
            uint8_t data[RX_BUF_SIZE];

            while (true) {
                int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE, 1);
                if (rxBytes > 0) {
                    for (int i = 0; i < rxBytes; i++) {
                        MidiParser::MidiMessage msg = parser.parse(data[i]);
                        
                        if (msg.isComplete) {
                            if (msg.status < 0xF0) { // Channel Voice/Mode messages
                                uint8_t type = msg.getType();
                                uint8_t channel = msg.getChannel();
                                
                                switch (type) {
                                case 0x80: // Note Off
                                    handleKeyOff(time, channel, msg.data1, msg.data2);
                                    ESP_LOGI(TAG, "Note Off - Channel: %d, Note: %d, Velocity: %d", channel, msg.data1, msg.data2);
                                    break;
                                case 0x90: // Note On
                                    handleKeyOn(time, channel, msg.data1, msg.data2);
                                    ESP_LOGI(TAG, "Note On - Channel: %d, Note: %d, Velocity: %d", channel, msg.data1, msg.data2);
                                    break;
                                case 0xA0: // Poly Key Pressure (Aftertouch)
                                    handlePolyAfterTouch(time, channel, msg.data1, msg.data2);
                                    ESP_LOGI(TAG, "Polyphonic Key Pressure (Aftertouch) - Channel: %d, Note: %d, Pressure: %d", channel, msg.data1, msg.data2);
                                    break;
                                case 0xB0: // Control Change
                                    handleCtrlChange(time, channel, msg.data1, msg.data2);
                                    ESP_LOGI(TAG, "Control Change - Channel: %d, Controller: %d, Value: %d", channel, msg.data1, msg.data2);
                                    break;
                                case 0xC0: // Program Change
                                    handleProgChange(time, channel, msg.data1);
                                    ESP_LOGI(TAG, "Program Change - Channel: %d, Program Number: %d", channel, msg.data1);
                                    break;
                                case 0xD0: // Channel Pressure
                                    handleAfterTouch(time, channel, msg.data1);
                                    ESP_LOGI(TAG, "Channel Pressure (Aftertouch) - Channel: %d, Pressure: %d", channel, msg.data1);
                                    break;
                                case 0xE0: // Pitch Bend
                                    handlePitchWheel(time, channel, msg.data1, msg.data2);
                                    ESP_LOGI(TAG, "Pitch Bend Change - Channel: %d, LSB: %d, MSB: %d", channel, msg.data1, msg.data2);
                                    break;
                                default:
                                    ESP_LOGI(TAG, "Unsupported MIDI message type: 0x%02X", type);
                                    break;
                                }
                            }
                            else if (msg.status >= 0xF0) { // System messages
                                switch (msg.status) {
                                case 0xF8: // Timing Clock
                                    handleClock(time);
                                    ESP_LOGI(TAG, "Timing Clock");
                                    break;
                                case 0xFA: // Start
                                    handleStart(time);
                                    ESP_LOGI(TAG, "Start");
                                    break;
                                case 0xFB: // Continue
                                    handleStart(time);
                                    ESP_LOGI(TAG, "Continue");
                                    break;
                                case 0xFC: // Stop
                                    handleStop(time);
                                    ESP_LOGI(TAG, "Stop");
                                    break;
                                case 0xF0: // SysEx Start
                                    // TODO: Implement SysEx handling
                                    ESP_LOGI(TAG, "SysEx Start");
                                    break;
                                case 0xF7: // SysEx End
                                    // TODO: Implement SysEx handling
                                    ESP_LOGI(TAG, "SysEx End");
                                    break;
                                default:
                                    ESP_LOGI(TAG, "Unsupported system message: 0x%02X", msg.status);
                                    break;
                                }
                            }
                            // Synchronize all GUI controllers
                            GUI::updateAllGuis();
                        }
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
                .source_clk = UART_SCLK_DEFAULT
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
