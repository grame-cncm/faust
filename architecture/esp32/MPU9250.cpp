#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "driver/i2c.h"
#include "MPU9250.h"

//magnetometer addresses
#define AK8963_ADDRESS  0x0C
#define AK8963_RA_HXL   0x03
#define AK8963_RA_CNTL1 0x0A
#define AK8963_RA_ASAX  0x10
//may need to change these
#define MPU9250_ADDR_ACCELCONFIG  0x1C
#define MPU9250_ADDR_INT_PIN_CFG  0x37
#define MPU9250_ADDR_ACCEL_XOUT_H 0x3B
#define MPU9250_ADDR_GYRO_XOUT_H  0x43
#define MPU9250_ADDR_PWR_MGMT_1   0x6B
#define MPU9250_ADDR_WHOAMI       0x75

//from the example. necessary info for I2C. common protocol defines
#define WRITE_BIT       I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT        I2C_MASTER_READ  /*!< I2C master read */
#define ACK_CHECK_EN    0x1              /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS   0x0              /*!< I2C master will not check ack from slave */
#define ACK_VAL         (i2c_ack_type_t)0x0              /*!< I2C ack value */
#define NACK_VAL        (i2c_ack_type_t)0x1              /*!< I2C nack value */

#define I2C_TX_BUF_DISABLE 0          /*!< I2C master do not need buffer */
#define I2C_RX_BUF_DISABLE 0          /*!< I2C master do not need buffer */

const float PI = 3.141592653;

//moved constructor from header to cpp file
MPU9250::MPU9250(uint8_t addresstmp = MPU9250_ADDRESS_AD0_LOW)
{
    address = addresstmp;
    //i2c_master_init();
    //address(address);
    accelRange = 0;
    gyroRange = 0;
    magXOffset = 0;
    magYOffset = 0;
    magZOffset = 0;
}

//rewrite this for the esp32
//doesn't include port declaration as in
uint8_t MPU9250::i2cRead(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
    if (Nbytes == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    //send the device address with a write indicating register to be read
    i2c_master_write_byte(cmd, (Address << 1), ACK_CHECK_EN);
    //send register we want
    i2c_master_write_byte(cmd, Register, ACK_CHECK_EN);
    //send repeated start. maybe not nessecary
    i2c_master_start(cmd);
    // send device address indicating read & read Data
    i2c_master_write_byte(cmd, (Address << 1) | READ_BIT, ACK_CHECK_EN);
    if (Nbytes > 1) {
        i2c_master_read(cmd, Data, Nbytes - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, Data + Nbytes - 1, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

uint8_t MPU9250::i2cWriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    // first, send device address (indicating write) & register to be written
    i2c_master_write_byte(cmd, (Address << 1 ) | WRITE_BIT, ACK_CHECK_EN);
    // send register we want
    i2c_master_write_byte(cmd, Register, ACK_CHECK_EN);
    // write the data. doesn't include a size declaration, hopefully its not needed
    i2c_master_write(cmd, &Data, ACK_CHECK_EN, sizeof(Data));
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

/**
 * @brief i2c master initialization
 */
void MPU9250::i2c_master_init()
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config((i2c_port_t) i2c_master_port, &conf);
    
    i2c_driver_install((i2c_port_t) i2c_master_port, conf.mode,
                       I2C_RX_BUF_DISABLE, I2C_TX_BUF_DISABLE, 0);
}

uint8_t MPU9250::readId(uint8_t *id)
{
    return i2cRead(address, MPU9250_ADDR_WHOAMI, 1, id);
}

void MPU9250::beginAccel(uint8_t mode)
{
    switch(mode) {
        case ACC_FULL_SCALE_2_G:
            accelRange = 2.0;
            break;
        case ACC_FULL_SCALE_4_G:
            accelRange = 4.0;
            break;
        case ACC_FULL_SCALE_8_G:
            accelRange = 8.0;
            break;
        case ACC_FULL_SCALE_16_G:
            accelRange = 16.0;
            break;
        default:
            return; // Return without writing invalid mode
    }
    i2cWriteByte(address, MPU9250_ADDR_ACCELCONFIG, mode);
}

void MPU9250::magReadAdjustValues()
{
    magSetMode(MAG_MODE_POWERDOWN);
    magSetMode(MAG_MODE_FUSEROM);
    uint8_t buff[3];
    i2cRead(AK8963_ADDRESS, AK8963_RA_ASAX, 3, buff);
    magXAdjust = buff[0];
    magYAdjust = buff[1];
    magZAdjust = buff[2];
}

void MPU9250::beginMag(uint8_t mode)
{
    magWakeup();
    magEnableSlaveMode();
    
    magReadAdjustValues();
    magSetMode(MAG_MODE_POWERDOWN);
    magSetMode(mode);
}

void MPU9250::magSetMode(uint8_t mode)
{
    i2cWriteByte(AK8963_ADDRESS, AK8963_RA_CNTL1, mode);
}

void MPU9250::magWakeup()
{
    unsigned char bits;
    i2cRead(address, MPU9250_ADDR_PWR_MGMT_1, 1, &bits);
    bits &= ~0x70; // Turn off SLEEP, STANDBY, CYCLE
    i2cWriteByte(address, MPU9250_ADDR_PWR_MGMT_1, bits);
}

void MPU9250::magEnableSlaveMode()
{
    unsigned char bits;
    i2cRead(address, MPU9250_ADDR_INT_PIN_CFG, 1, &bits);
    bits |= 0x02; // Activate BYPASS_EN
    i2cWriteByte(address, MPU9250_ADDR_INT_PIN_CFG, bits);
}

float MPU9250::magHorizDirection()
{
    return atan2(magX(), magY()) * 180 / PI;
}

uint8_t MPU9250::magUpdate()
{
    return i2cRead(AK8963_ADDRESS, AK8963_RA_HXL, 7, magBuf);
}

int16_t MPU9250::magGet(uint8_t highIndex, uint8_t lowIndex)
{
    return (((int16_t) magBuf[highIndex]) << 8) | magBuf[lowIndex];
}

float adjustMagValue(int16_t value, uint8_t adjust)
{
    return ((float) value * (((((float)adjust - 128) * 0.5) / 128) + 1));
}

float MPU9250::magX()
{
    return adjustMagValue(magGet(1, 0), magXAdjust) + magXOffset;
}

float MPU9250::magY()
{
    return adjustMagValue(magGet(3, 2), magYAdjust) + magYOffset;
}

float MPU9250::magZ()
{
    return adjustMagValue(magGet(5, 4), magZAdjust) + magZOffset;
}

uint8_t MPU9250::accelUpdate()
{
    return i2cRead(address, MPU9250_ADDR_ACCEL_XOUT_H, 6, accelBuf);
}

float MPU9250::accelGet(uint8_t highIndex, uint8_t lowIndex)
{
    int16_t v = ((int16_t) accelBuf[highIndex]) << 8 | accelBuf[lowIndex];
    return ((float)-v) * accelRange / (float)0x8000; // (float)0x8000 == 32768.0
}

float MPU9250::accelX()
{
    return accelGet(0, 1);
}

float MPU9250::accelY()
{
    return accelGet(2, 3);
}

float MPU9250::accelZ()
{
    return accelGet(4, 5);
}

float MPU9250::accelSqrt()
{
    return sqrt(pow(accelGet(0, 1), 2) +
                pow(accelGet(2, 3), 2) +
                pow(accelGet(4, 5), 2));
}

void MPU9250::beginGyro(uint8_t mode)
{
    switch (mode) {
        case GYRO_FULL_SCALE_250_DPS:
            gyroRange = 250.0;
            break;
        case GYRO_FULL_SCALE_500_DPS:
            gyroRange = 500.0;
            break;
        case GYRO_FULL_SCALE_1000_DPS:
            gyroRange = 1000.0;
            break;
        case GYRO_FULL_SCALE_2000_DPS:
            gyroRange = 2000.0;
            break;
        default:
            return; // Return without writing invalid mode
    }
    i2cWriteByte(address, 27, mode);
}

uint8_t MPU9250::gyroUpdate()
{
    return i2cRead(address, MPU9250_ADDR_GYRO_XOUT_H, 6, gyroBuf);
}

float MPU9250::gyroGet(uint8_t highIndex, uint8_t lowIndex)
{
    int16_t v = ((int16_t) gyroBuf[highIndex]) << 8 | gyroBuf[lowIndex];
    return ((float)-v) * gyroRange / (float)0x8000;
}

float MPU9250::gyroX()
{
    return gyroGet(0, 1);
}

float MPU9250::gyroY()
{
    return gyroGet(2, 3);
}

float MPU9250::gyroZ()
{
    return gyroGet(4, 5);
}
