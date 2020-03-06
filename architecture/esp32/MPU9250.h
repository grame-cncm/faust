#ifndef __MPU9250_H
#define __MPU9250_H

#include <stdio.h>
#include <stdint.h>

//START from WM8978
#define I2C_MASTER_NUM I2C_NUM_1 /*!< I2C port number for master dev */
#define I2C_MASTER_SCL_IO (gpio_num_t) 18//these may be wrong
#define I2C_MASTER_SDA_IO (gpio_num_t) 19
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0

#define WM8978_ADDR 0X1A    //WM8978

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define ACK_CHECK_EN 0x1
//END from WM8978

//START from Asukiaaa
#define MPU9250_ADDRESS_AD0_LOW  0x68
#define MPU9250_ADDRESS_AD0_HIGH 0x69

#define ACC_FULL_SCALE_2_G       0x00
#define ACC_FULL_SCALE_4_G       0x08
#define ACC_FULL_SCALE_8_G       0x10
#define ACC_FULL_SCALE_16_G      0x18

#define GYRO_FULL_SCALE_250_DPS  0x00
#define GYRO_FULL_SCALE_500_DPS  0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define MAG_MODE_POWERDOWN        0x0
#define MAG_MODE_SINGLE           0x1
#define MAG_MODE_CONTINUOUS_8HZ   0x2
#define MAG_MODE_EXTERNAL         0x4
#define MAG_MODE_CONTINUOUS_100HZ 0x6
#define MAG_MODE_SELFTEST         0x8
#define MAG_MODE_FUSEROM          0xF
//END from Asukiaaa

class MPU9250 { //Removed all mentions of wire and asukiaaa
    
    public:
    
        MPU9250(uint8_t address);
    
        uint8_t readId(uint8_t* id);
        void i2c_master_init();
    
        void beginAccel(uint8_t mode = ACC_FULL_SCALE_16_G);
        uint8_t accelUpdate();
        float accelX();
        float accelY();
        float accelZ();
        float accelSqrt();
    
        void beginGyro(uint8_t mode = GYRO_FULL_SCALE_2000_DPS);
        uint8_t gyroUpdate();
        float gyroX();
        float gyroY();
        float gyroZ();
    
        void beginMag(uint8_t mode = MAG_MODE_CONTINUOUS_8HZ);
        void magSetMode(uint8_t mode);
        uint8_t magUpdate();
        float magX();
        float magY();
        float magZ();
        float magHorizDirection();
    
    private:
    
        uint8_t address;
        uint8_t accelBuf[6];
        float accelRange;
        uint8_t gyroBuf[6];
        float gyroRange;
        uint8_t magBuf[7];
        uint8_t magXAdjust, magYAdjust, magZAdjust;
        int16_t magXOffset, magYOffset, magZOffset;
    
        float accelGet(uint8_t highIndex, uint8_t lowIndex);
        float gyroGet(uint8_t highIndex, uint8_t lowIndex);
        int16_t magGet(uint8_t highIndex, uint8_t lowIndex);
        void magEnableSlaveMode();
        void magReadAdjustValues();
        void magWakeup();
        uint8_t i2cRead(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
        uint8_t i2cWriteByte(uint8_t Address, uint8_t Register, uint8_t Data);
};

#endif
