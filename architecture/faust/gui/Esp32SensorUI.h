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

#define ONE_G 9.81

// To be used with Gramophone for accelerometer, gyroscope and magnetometer
class Esp32SensorUI : public APIUI
{
    private:
    
        TaskHandle_t fProcessHandle;
        MPU9250 fMPU9250;
        bool fHasAcc, fHasGyr, fHasMag;
    
        void sensor()
        {
            while (true) {
                
                if (fHasAcc) {
                    fMPU9250.accelUpdate();
                    propagateAcc(0, fMPU9250.accelX() * ONE_G);
                    propagateAcc(1, fMPU9250.accelY() * ONE_G);
                    propagateAcc(2, fMPU9250.accelZ() * ONE_G);
                    /*
                    std::cout << "======================" << std::endl;
                    std::cout << "accelX " << fMPU9250.accelX() << std::endl;
                    std::cout << "accelY " << fMPU9250.accelX() << std::endl;
                    std::cout << "accelZ " << fMPU9250.accelZ() << std::endl;
                    */
                }
                
                if (fHasGyr) {
                    fMPU9250.gyroUpdate();
                    propagateGyr(0, fMPU9250.gyroX());
                    propagateGyr(1, fMPU9250.gyroY());
                    propagateGyr(2, fMPU9250.gyroZ());
                    /*
                    std::cout << "======================" << std::endl;
                    std::cout << "gyroX " << fMPU9250.gyroX() << std::endl;
                    std::cout << "gyroY " << fMPU9250.gyroY() << std::endl;
                    std::cout << "gyroZ " << fMPU9250.gyroZ() << std::endl;
                    */
                }
                
                /*
                if (fHasMag) {
                    fMPU9250.magUpdate();
                    propagateMag(0, fMPU9250.magX());
                    propagateMag(1, fMPU9250.magY());
                    propagateMag(2, fMPU9250.magZ());
                    propagateMag(2, fMPU9250.magHorizDirection());
                }
                */
                
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
        }
    
        static void sensorHandler(void* arg)
        {
            static_cast<Esp32SensorUI*>(arg)->sensor();
        }
    
    public:
    
        Esp32SensorUI():fProcessHandle(nullptr),
        fMPU9250(MPU9250_ADDRESS_AD0_HIGH),
        fHasAcc(false),
        fHasGyr(false),
        fHasMag(false)
        {}
    
        bool start()
        {
            fHasAcc = (getAccCount(0) > 0) || (getAccCount(1) > 0) || (getAccCount(2) > 0);
            fHasGyr = (getGyrCount(0) > 0) || (getGyrCount(1) > 0) || (getGyrCount(2) > 0);
            
            std::cout << "fHasAcc " << fHasAcc << std::endl;
            std::cout << "fHasGyr " << fHasGyr << std::endl;
            
            if (fHasAcc) fMPU9250.beginAccel();
            if (fHasGyr) fMPU9250.beginGyro();
            if (fHasMag) fMPU9250.beginMag();
            if (fHasAcc || fHasGyr || fHasMag) {
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
