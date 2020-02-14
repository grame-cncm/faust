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
#include "MPU9250.h"

#include "faust/gui/APIUI.h"

// To be used with Gramophone for accelerometer and gyroscope
class Esp32SensorUI : public APIUI
{
    private:
    
        TaskHandle_t fProcessHandle;
        MPU9250 fMpu9250;
    
        void sensor()
        {
            while (true) {
                fMpu9250.accelUpdate();
                propagateAcc(0, fMpu9250.accelX());
                propagateAcc(1, fMpu9250.accelY());
                propagateAcc(2, fMpu9250.accelZ());
                
                fMpu9250.gyroUpdate();
                propagateGyr(0, fMpu9250.gyroX());
                propagateGyr(1, fMpu9250.gyroY());
                propagateGyr(2, fMpu9250.gyroZ());
                
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
        }
    
        static void sensorHandler(void* arg)
        {
            static_cast<Esp32SensorUI*>(arg)->sensor();
        }
    
    public:
    
        Esp32SensorUI():fMpu9250(MPU9250_ADDRESS_AD0_HIGH)
        {
            fMpu9250.beginAccel();
            fMpu9250.beginGyro();
            //fMpu9250.beginMag();
        }
    
        bool start()
        {
            if ((getAccCount(0) > 0)
                || (getAccCount(1) > 0)
                || (getAccCount(2) > 0)
                || (getGyrCount(0) > 0)
                || (getGyrCount(1) > 0)
                || (getGyrCount(2) > 0)) {
                // Start Sensor receive task
                return (xTaskCreatePinnedToCore(sensorHandler, "Faust Sensor Task", 10240, (void*)this, 5, &fProcessHandle, 1) == pdPASS);
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
