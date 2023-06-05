# 安信可Rd-04 驱动库

## [English document](README.md)

## 1.简介

安信可Rd-04驱动库是为了方便开发者更快地使用Rd-04,并对RD-04配置各个参数而开发的，你只需要写好几个相应的驱动函数并替换掉原有的驱动函数，即可实现对Rd-04的配置。
因为Rd-04 本身拥有MCU，所以你需要使用自己的MCU做配置的话，需要把板载的MCU拆掉，否者你将无法使用此驱动库。

## 2.移植

Rd-04 的配置依赖I2C 驱动，所以你需要准备开发好以下功能函数：

- Rd-04 I2C使能IO函数，Rd-04的I2C功能需要把IIC_EN引脚拉高之后才能使用，以STM32为例，使能HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)，使能：HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)
- I2C 发送起始信号函数
- I2C 发送停止信号函数
- I2C 主机等待ACK应答函数
- I2C 发送字节函数
- I2C 读取字节函数，这个函数需要自带是否给从机发送ACK 参数
- 微妙延时函数

开发好上述的函数之后，替换掉原有程序，例如：

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

## 3.默认配置

驱动库中，写好了Rd-04出厂时的配置，`axk_rd04_default_config()` ，建议不要直接改动里面的配置，应该通过其他函数修改。
