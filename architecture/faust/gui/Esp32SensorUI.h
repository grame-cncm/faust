/************************** BEGIN Esp32SensorUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_ESP32SENSOR_H
#define FAUST_ESP32SENSOR_H

#include <string>
#include <iostream>
#include <string.h>

#include "driver/uart.h"

#include "faust/gui/APIUI.h"

// To be used with Gramophone for accelerometers and gyroscope
class Esp32SensorUI : public APIUI
{
    private:
    
        TaskHandle_t fProcessHandle;
    
        void sensor()
        {
            while (true) {
                // TODO
            }
        }
    
        static void sensorHandler(void* arg)
        {
            static_cast<Esp32SensorUI*>(arg)->sensor();
        }
    
    public:
    
        bool start()
        {
            if ((getAccCount(0) > 0)
                || (getAccCount(1) > 0)
                || (getAccCount(2) > 0)
                || (getGyrCount(0) > 0)
                || (getGyrCount(1) > 0)
                || (getGyrCount(2) > 0)) {
                // Start Sensor receive task
                return (xTaskCreatePinnedToCore(sensorHandler, "Faust Sensor Task", 1024, (void*)this, 5, &fProcessHandle, 1) == pdPASS);
            } else {
                return true;
            }
        }
    
        void stop()
        {
            if (fProcessHandle != nullptr) {
                vTaskDelete(fProcessHandle);
                fProcessHandle = nullptr;
            }
        }
    
};

#endif // FAUST_ESP32CONTROL_H
/**************************  END  Esp32SensorUI.h **************************/
