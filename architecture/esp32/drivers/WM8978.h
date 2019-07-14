#ifndef __WM8978_H
#define __WM8978_H

#include <stdio.h>
#include "sys/types.h"

typedef uint16_t u16;
typedef uint8_t u8;
typedef unsigned char byte;

#define I2C_MASTER_NUM 1 /*!< I2C port number for master dev */
#define I2C_MASTER_SCL_IO 18
#define I2C_MASTER_SDA_IO 19
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0
 
#define WM8978_ADDR 0X1A	//WM8978

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define ACK_CHECK_EN 0x1
 
#define EQ1_80Hz 0X00
#define EQ1_105Hz 0X01
#define EQ1_135Hz 0X02
#define EQ1_175Hz	0X03

#define EQ2_230Hz	0X00
#define EQ2_300Hz	0X01
#define EQ2_385Hz	0X02
#define EQ2_500Hz	0X03

#define EQ3_650Hz	0X00
#define EQ3_850Hz	0X01
#define EQ3_1100Hz 0X02
#define EQ3_14000Hz 0X03

#define EQ4_1800Hz 0X00
#define EQ4_2400Hz 0X01
#define EQ4_3200Hz 0X02
#define EQ4_4100Hz 0X03

#define EQ5_5300Hz 0X00
#define EQ5_6900Hz 0X01
#define EQ5_9000Hz 0X02
#define EQ5_11700Hz 0X03

class WM8978
{
  public:
    u8 init(void);
    void initI2C(void);
    void addaCfg(u8 dacen,u8 adcen);
    void inputCfg(u8 micen,u8 lineinen,u8 auxen);
    void outputCfg(u8 dacen,u8 bpsen);
    void micGain(u8 gain);
    void lineinGain(u8 gain);
    void auxGain(u8 gain);
    u8 writeReg(u8 reg,u16 val); 
    u16 readReg(u8 reg);
    void hpVolSet(u8 voll,u8 volr);
    void spkVolSet(u8 volx);
    void i2sCfg(u8 fmt,u8 len);
    void threeDSet(u8 depth);
    void eq3DDir(u8 dir); 
    void eq1Set(u8 cfreq,u8 gain); 
    void eq2Set(u8 cfreq,u8 gain);
    void eq3Set(u8 cfreq,u8 gain);
    void eq4Set(u8 cfreq,u8 gain);
    void eq5Set(u8 cfreq,u8 gain);
    void noiseSet(u8 enable,u8 gain);
    void alcSet(u8 enable, u8 maxgain, u8 mingain);
};

#endif

