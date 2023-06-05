# Anxinke Rd-04 Driver Library

## [中文文档](README_CN.md)

## 1. Introduction

The Ai-Thinker Rd-04 driver library is developed to facilitate developers to use Rd-04 faster and configure various parameters for RD-04. You only need to write several corresponding driver functions and replace the original driver functions to achieve the configuration of Rd-04.
Because Rd-04 itself has an MCU, if you need to use your own MCU for configuration, you need to remove the onboard MCU. Otherwise, you will not be able to use this driver library.

## 2. Transplantation

The configuration of Rd-04 relies on the I2C driver, so you need to prepare to develop the following functional functions:
-Rd-04 I2C enables IO function, and the I2C function of Rd-04 requires IIC_The EN pin can only be used after being pulled up, using STM32 as an example to enable HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET), enable: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
-I2C send start signal function
-I2C send stop signal function
-I2C host waiting for ACK response function
-I2C Send Byte Function
-I2C reads byte function, which needs to come with whether to send ACK parameters to the slave
-Subtle delay function

After developing the above functions, replace the original program, such as:

```
#define AXK_RD04_I2C_ENABLE HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)
#define AXK_RD04_I2C_DISABLE HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)

#define AXK_RD04_I2C_START I2C_start()
#define AXK_RD04_I2C_STOP I2C_stop()
#define AXK_RD04_I2C_WAITACK I2C_wait_ack()
#define AXK_RD04_I2C_SEND(byte) I2C_send_byte(byte)
#define AXK_RD04_I2C_READ(ack) I2C_read_byte(ack)
#define AXK_RD04_DELAY_us(us) delay_us(us)
```

## 3. Default Configuration

In the driver library, the configuration of Rd-04 from the factory has been written, 'axk_Rd04_Default_Config()', it is recommended not to directly modify the configuration inside. It should be modified through other functions.
