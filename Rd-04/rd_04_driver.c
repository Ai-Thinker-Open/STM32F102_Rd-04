/**
 * @file rd_04_driver.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-31
 *
 * @copyright Copyright (c) 2023
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i2c.h"
#include "gpio.h"
#include "pbdata.h"
#include "rd_04_driver.h"

#define RD_04_I2C_ADDR 0X71

#define AXK_RD04_I2C_ENABLE HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)
#define AXK_RD04_I2C_DISABLE HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)

#define AXK_RD04_I2C_START I2C_start()
#define AXK_RD04_I2C_STOP I2C_stop()
#define AXK_RD04_I2C_WAITACK I2C_wait_ack()
#define AXK_RD04_I2C_SEND(byte) I2C_send_byte(byte)
#define AXK_RD04_I2C_READ(ack) I2C_read_byte(ack)
#define AXK_RD04_DELAY_us(us) delay_us(us)

#define AXK_RD04_WR 0X00
#define AXK_RD04_RD 0X01

/**
 * @brief RD04 I2C config REG funtion
 *
 * @param reg_addr Reg addr
 * @param buff Reg param
 * @param buf_size param size
 * @return uint8_t 1: success 0: fail
*/
static uint8_t axk_rd04_i2c_write(char reg_addr, char buff, char buf_size)
{

    for (size_t i = 0; i < buf_size; i++)
    {
        AXK_RD04_I2C_STOP;
        {
            AXK_RD04_I2C_START;
            AXK_RD04_I2C_SEND(RD_04_I2C_ADDR<<1|AXK_RD04_WR);
            if (AXK_RD04_I2C_WAITACK!=0) goto cmd_fail;
        }

        AXK_RD04_I2C_SEND(reg_addr|AXK_RD04_WR);
        if (AXK_RD04_I2C_WAITACK!=0) goto cmd_fail;
        AXK_RD04_I2C_SEND(buff);
        if (AXK_RD04_I2C_WAITACK!=0) goto cmd_fail;
    }
    AXK_RD04_I2C_STOP;
    return 1;

cmd_fail:
    AXK_RD04_I2C_STOP;
    printf("[%s:%d] Rd-04 write error,device does not exist\r\n", __func__, __LINE__);
    return 0;
}
/**
 * @brief
 *
 * @param reg_addr
 * @param size
 * @return char
*/
static char axk_rd04_i2c_read(char reg_addr, char size)
{
    char read_buf = 0;
    AXK_RD04_I2C_START;
    AXK_RD04_I2C_SEND(RD_04_I2C_ADDR<<1|AXK_RD04_WR);
    if (AXK_RD04_I2C_WAITACK!=0) goto cmd_fail;
    AXK_RD04_I2C_SEND(reg_addr);
    if (AXK_RD04_I2C_WAITACK!=0) goto cmd_fail;

    AXK_RD04_I2C_START;
    AXK_RD04_I2C_SEND(RD_04_I2C_ADDR<<1|AXK_RD04_RD);
    if (AXK_RD04_I2C_WAITACK!=0) goto cmd_fail;

    for (size_t i = 0; i < size; i++)
    {
        if (i!=size-1) {
            read_buf = AXK_RD04_I2C_READ(1);
        }
        else read_buf = AXK_RD04_I2C_READ(0);
        AXK_RD04_DELAY_us(2);
    }
    AXK_RD04_I2C_STOP;
    return read_buf;
cmd_fail:
    AXK_RD04_I2C_STOP;
    printf("[%s:%d] Rd-04 read error,device does not exist\r\n", __func__, __LINE__);
    return 0;
}
/**
 * @brief
 *
*/
uint8_t axk_rd04_i2c_init(void)
{
    MX_I2C1_Init();
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    AXK_RD04_I2C_START;
    AXK_RD04_I2C_SEND(RD_04_I2C_ADDR<<1|AXK_RD04_WR);

    if (AXK_RD04_I2C_WAITACK!=0) {
        AXK_RD04_I2C_DISABLE;
        return 0;
    }
    AXK_RD04_I2C_DISABLE;
    return 1;
}
/**
 * @brief Rd-04 factory default settings
 *
*/
void axk_rd04_default_config(void)
{
    char buff = 0;
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    for (size_t i = 0; i < 5; i++)
    {
        if (axk_rd04_i2c_write(0x13, 0x9b, 1))
            AXK_RD04_DELAY_us(10);
        else goto __exit;

        buff = axk_rd04_i2c_read(0x13, 1);
        AXK_RD04_DELAY_us(10);
    }
    axk_rd04_i2c_write(0x24, 0x03, 1);
    axk_rd04_i2c_write(0x04, 0x20, 1);
    axk_rd04_i2c_write(0x10, 0x20, 1);
    axk_rd04_i2c_write(0x03, 0x45, 1);
    axk_rd04_i2c_write(0x1C, 0x21, 1);

    axk_rd04_i2c_write(0x18, 0x5a, 1);
    axk_rd04_i2c_write(0x19, 0x01, 1);

    axk_rd04_i2c_write(0x1A, 0x55, 1);
    axk_rd04_i2c_write(0x1B, 0x01, 1);

    axk_rd04_i2c_write(0x1D, 0x80, 1);
    axk_rd04_i2c_write(0x1E, 0x0C, 1);
    axk_rd04_i2c_write(0x1F, 0x00, 1);

    axk_rd04_i2c_write(0x20, 0x00, 1);
    axk_rd04_i2c_write(0x21, 0x7D, 1);
    axk_rd04_i2c_write(0x22, 0x00, 1);

    axk_rd04_i2c_write(0x23, 0x0C, 1);

    AXK_RD04_DELAY_us(1000000);
    AXK_RD04_DELAY_us(1000000);
    AXK_RD04_DELAY_us(1000000);
__exit:
    AXK_RD04_I2C_DISABLE;
}
/**
 * @brief axk_rd04_output_config
 *
*/
void axk_rd04_display_config(void)
{
    AXK_RD04_I2C_ENABLE;
    printf("------------------------------------\r\n");
    printf("|    PSM config    |     0x%02X      |\r\n", axk_rd04_i2c_read(0x04, 1));
    printf("|----------------------------------|\r\n");
    printf("|  ADC frequency   |     0x%02X      |\r\n", axk_rd04_i2c_read(0x10, 1));
    printf("|----------------------------------|\r\n");
    printf("|   IO VAL pin     |     %s      |\r\n", (0x07==axk_rd04_i2c_read(0x24, 1))?"HIGH":"LOW ");
    printf("|----------------------------------|\r\n");
    printf("|TransmittingPower |     0x%02X      |\r\n", axk_rd04_i2c_read(0x03, 1));
    printf("|----------------------------------|\r\n");
    printf("|InductionThreshold|     0x%04X    |\r\n", (axk_rd04_i2c_read(0x19, 1)<<8|axk_rd04_i2c_read(0x18, 1)));
    printf("|----------------------------------|\r\n");
    printf("|   NoiseUpdate    |     0x%04X    |\r\n", (axk_rd04_i2c_read(0x1B, 1)<<8|axk_rd04_i2c_read(0x1A, 1)));
    printf("|----------------------------------|\r\n");
    printf("|    DelayTime     |     %04dms    |\r\n", (((axk_rd04_i2c_read(0x1F, 1)<<8|axk_rd04_i2c_read(0x1E, 1)))<<8|axk_rd04_i2c_read(0x1D, 1))/32);
    printf("|----------------------------------|\r\n");
    printf("|   BlockadeTime   |     %dms    |\r\n", (((axk_rd04_i2c_read(0x22, 1)<<8|axk_rd04_i2c_read(0x21, 1)))<<8|axk_rd04_i2c_read(0x20, 1))/32);
    printf("------------------------------------\r\n");
    AXK_RD04_I2C_DISABLE;
}
/**
 * @brief AxkRd04SetIoValOutput
 *  Set the output mode of the IO_VAL pin
 * @param OutputStatus  1:IO_VAL Output setting, 0：IO_VAL Output Clear
*/
void AxkRd04SetIoValOutput(uint8_t OutputStatus)
{
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    OutputStatus?axk_rd04_i2c_write(0X24, 0X07, 1):axk_rd04_i2c_write(0X24, 0X03, 1);
    AXK_RD04_I2C_DISABLE;
}
/**
 * @brief AxkRd04SetWayOfWorking
 * Set the working mode of Rd-04
 * @param PSM
*/
void AxkRd04SetWayOfWorking(rd04_psm_t PSM)
{
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    axk_rd04_i2c_write(0X04, PSM, 1);
    AXK_RD04_I2C_DISABLE;
}
/**
 * @brief AxkRd04SetADCSamplingFrequency
 *
 * @param ADC_SF
*/
void AxkRd04SetADCSamplingFrequency(rd04_adc_sf_t ADC_SF)
{
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    switch (ADC_SF)
    {
        case RD04_ADC_SF_1KHz:
            axk_rd04_i2c_write(0X10, 0X20, 1);
            break;
        case RD04_ADC_SF_2KHz:
            axk_rd04_i2c_write(0X10, 0X10, 1);
            break;
        case RD04_ADC_SF_4KHz:
            axk_rd04_i2c_write(0X10, 0X08, 1);
            break;
        case RD04_ADC_SF_16KHz:
            axk_rd04_i2c_write(0X10, 0X02, 1);
            break;
    }
    AXK_RD04_I2C_DISABLE;

}
/**
 * @brief AxkRD04SetTransmittingPower
 *     设置发射功率（Set the transmission power of Rd-04）
 * @param Tpower
*/
void AxkRD04SetTransmittingPower(rd04_tpower_t Tpower)
{
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    axk_rd04_i2c_write(0X03, 0X40+Tpower, 1);
    AXK_RD04_I2C_DISABLE;
}
/**
 * @brief AxkRD04SetInductionThreshold
 *  设置感应门限，当到达门限值之后，控制IO VAL 输出(Set induction threshold，After reaching the threshold value, control the IO VAL output)
 * @param IndTs
*/
void AxkRD04SetInductionThreshold(uint16_t IndTs)
{
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    axk_rd04_i2c_write(0X18, (IndTs&0XFF), 1);
    axk_rd04_i2c_write(0X19, (IndTs>>8)&0XFF, 1);
    AXK_RD04_I2C_DISABLE;
}
/**
 * @brief AxkRD04SetNoiseUpdate
 *
 * @param noiseupdate
*/
void AxkRD04SetNoiseUpdate(uint16_t noiseupdate)
{
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    axk_rd04_i2c_write(0X1A, (noiseupdate&0XFF), 1);
    axk_rd04_i2c_write(0X1B, (noiseupdate>>8)&0XFF, 1);
    AXK_RD04_I2C_DISABLE;
}
/**
 * @brief AxkRD04SetInductionDelay
 *  设置感应延时时间(Set induction delay time)
 * @param _delay_ms
*/
void AxkRD04SetInductionDelayTime(uint32_t _delay_ms)
{
    uint32_t timer_hex = 0;
    timer_hex = _delay_ms*32;
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    axk_rd04_i2c_write(0X1D, (timer_hex&0XFF), 1);
    axk_rd04_i2c_write(0X1E, (timer_hex>>8)&0XFF, 1);
    axk_rd04_i2c_write(0X1F, (timer_hex>>16)&0XFF, 1);
    AXK_RD04_I2C_DISABLE;
}
/**
 * @brief AxkRD04SetBlockadeTime
 *  设置封锁时间（Set blocking time）
 * @param _delay_ms
*/
void AxkRD04SetBlockadeTime(uint32_t _delay_ms)
{
    uint32_t timer_hex = 0;
    timer_hex = _delay_ms*32;
    AXK_RD04_I2C_ENABLE;
    AXK_RD04_DELAY_us(10);
    axk_rd04_i2c_write(0X20, (timer_hex&0XFF), 1);
    axk_rd04_i2c_write(0X21, (timer_hex>>8)&0XFF, 1);
    axk_rd04_i2c_write(0X22, (timer_hex>>16)&0XFF, 1);
    AXK_RD04_I2C_DISABLE;
}
