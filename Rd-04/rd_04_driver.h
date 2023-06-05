/**
 * @file rd_04_driver.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-31
 *
 * @copyright Copyright (c) 2023
 *
*/

#ifndef RD_04_DRIVER_H
#define RD_04_DRIVER_H

typedef enum {
    RD04_PSM_DEF = 0X20,//Pulse gap operation
    RD04_PSM_CONTINUOUS = 0XA0, //Continuous operation
}rd04_psm_t;

typedef enum {
    RD04_ADC_SF_1KHz = 0,
    RD04_ADC_SF_2KHz,
    RD04_ADC_SF_4KHz,
    RD04_ADC_SF_16KHz,
}rd04_adc_sf_t;

typedef enum {
    RD04_TPOWER_0 = 0,  //发射功率(0) -- 124.1uA@6V 靠近感应反应正常  --- 发射功率最大 (Transmission power (0)-- 124.1uA@6V Proximity induction response normal - maximum emission power)
    RD04_TPOWER_1,      //发射功率(1) -- 123.2uA@6V 靠近感应反应正常(Transmission power (1)-- 123.2uA@6V Proximity induction response is normal)
    RD04_TPOWER_2,      //发射功率(2) -- 121.1uA@6V 靠近感应反应正常(Transmission power (2)-- 121.1uA@6V Proximity induction response is normal)
    RD04_TPOWER_3,      //发射功率(3) -- 119.7uA@6V 靠近感应反应正常(Transmission power (3)-- 119.7uA@6V Proximity induction response is normal)
    RD04_TPOWER_4,      //发射功率(4) -- 117.9uA@6V 靠近感应反应正常(Transmission power (4)-- 117.9uA@6V Proximity induction response is normal)
    RD04_TPOWER_5,      //发射功率(5) -- 115.2uA@6V 靠近感应反应正常(Transmission power (5)-- 115.2uA@6V Proximity induction response is normal)
    RD04_TPOWER_6,      //发射功率(6) -- 114.5uA@6V 靠近感应反应正常（很近）(Transmission power (6)-- 114.5uA@6V Proximity induction response normal (very close))
    RD04_TPOWER_7       //发射功率(7) -- 108.5uA@6V 靠近感应无反应(Transmission power (7)-- 108.5uA@6V Proximity induction without response)
}rd04_tpower_t;

uint8_t axk_rd04_i2c_init(void);
void axk_rd04_default_config(void);
void axk_rd04_display_config(void);
void AxkRd04SetIoValOutput(uint8_t OutputStatus);
void AxkRd04SetADCSamplingFrequency(rd04_adc_sf_t ADC_SF);
void AxkRD04SetTransmittingPower(rd04_tpower_t Tpower);
void AxkRD04SetInductionThreshold(uint16_t IndTs);
void AxkRD04SetNoiseUpdate(uint16_t noiseupdate);
void AxkRD04SetInductionDelayTime(uint32_t _delay_ms);
void AxkRD04SetBlockadeTime(uint32_t _delay_ms);
#endif
