/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

  /* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include "pbdata.h"
#include "gpio.h"
/* USER CODE BEGIN 0 */
#define I2C_SDA GPIO_PIN_6
#define I2C_SCL GPIO_PIN_7

#define I2C_SDA_H  HAL_GPIO_WritePin(GPIOB, I2C_SDA, GPIO_PIN_SET)
#define I2C_SDA_L  HAL_GPIO_WritePin(GPIOB, I2C_SDA, GPIO_PIN_RESET)

#define I2C_SCL_H  HAL_GPIO_WritePin(GPIOB, I2C_SCL, GPIO_PIN_SET)
#define I2C_SCL_L  HAL_GPIO_WritePin(GPIOB, I2C_SCL, GPIO_PIN_RESET)
/* USER CODE END 0 */
#if 0
I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  if (i2cHandle->Instance==I2C1)
  {
    /* USER CODE BEGIN I2C1_MspInit 0 */

    /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
    /* USER CODE BEGIN I2C1_MspInit 1 */

    /* USER CODE END I2C1_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if (i2cHandle->Instance==I2C1)
  {
    /* USER CODE BEGIN I2C1_MspDeInit 0 */

    /* USER CODE END I2C1_MspDeInit 0 */
      /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

    /* USER CODE BEGIN I2C1_MspDeInit 1 */

    /* USER CODE END I2C1_MspDeInit 1 */
  }
}
#endif

/* USER CODE BEGIN 1 */
void MX_I2C1_Init(void)
{
  GPIO_InitTypeDef I2C_GPIO_Structure = { 0 };
  I2C_GPIO_Structure.Pin = I2C_SDA|I2C_SCL;
  I2C_GPIO_Structure.Mode = GPIO_MODE_OUTPUT_PP;
  I2C_GPIO_Structure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &I2C_GPIO_Structure);

  HAL_GPIO_WritePin(GPIOB, I2C_SDA, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, I2C_SCL, GPIO_PIN_SET);
}
/**
 * @brief Configure SDA as input
 *
*/
static void I2C_SDA_IN(void)
{
  GPIO_InitTypeDef I2C_GPIO_Structure = { 0 };
  I2C_GPIO_Structure.Pin = I2C_SDA;
  I2C_GPIO_Structure.Mode = GPIO_MODE_INPUT;
  I2C_GPIO_Structure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &I2C_GPIO_Structure);
}
/**
 * @brief Configure SDA as output
 *
*/
static void I2C_SDA_OUT(void)
{
  GPIO_InitTypeDef I2C_GPIO_Structure = { 0 };
  I2C_GPIO_Structure.Pin = I2C_SDA;
  I2C_GPIO_Structure.Mode = GPIO_MODE_OUTPUT_PP;
  I2C_GPIO_Structure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &I2C_GPIO_Structure);
}
/**
 * @brief Generate start signal
 *
*/
void I2C_start(void)
{
  I2C_SDA_OUT();
  I2C_SDA_H;
  I2C_SCL_H;
  delay_us(1);
  I2C_SDA_L;
  delay_us(1);
  I2C_SCL_L;
}
/**
 * @brief Generate stop signal
 *
*/
void I2C_stop(void)
{
  I2C_SDA_OUT();
  I2C_SCL_L;
  I2C_SDA_L;
  I2C_SCL_H;
  delay_us(1);
  I2C_SDA_H;
  delay_us(1);
}
/**
 * @brief Construct a new i2c ack object
 *
 * @param ack 1:send ack,0:Nack
*/
void I2C_ack(uint8_t ack)
{
  I2C_SCL_L;
  I2C_SDA_OUT();
  ack?I2C_SDA_L:I2C_SDA_H;
  delay_us(1);
  I2C_SCL_H;
  delay_us(1);
  I2C_SCL_L;
}
/**
 * @brief
 *
 * @return uint8_t
*/
uint8_t I2C_wait_ack(void)
{
  uint8_t tempTime = 0;

  I2C_SDA_IN();
  I2C_SDA_H;
  delay_us(1);
  I2C_SCL_H;
  delay_us(1);
  while (HAL_GPIO_ReadPin(GPIOB, I2C_SDA))
  {
    tempTime++;
    if (tempTime>250)
    {
      I2C_stop();
      return 1;
    }
  }
  I2C_SCL_L;
  return 0;
}
/**
 * @brief send one byte
 *
 * @param data
*/
void I2C_send_byte(uint8_t data)
{
  uint8_t i = 0;

  I2C_SDA_OUT();
  I2C_SCL_L;

  for (i = 0;i<8;i++)
  {
    if ((data&0x80)>0) //0x80  1000 0000
      I2C_SDA_H;
    else
      I2C_SDA_L;
    data <<= 1;
    I2C_SCL_H;
    delay_us(1);
    I2C_SCL_L;
    delay_us(1);
  }
}
/**
 * @brief I2C read byte
 *
 * @param ack
 * @return uint8_t
*/
uint8_t I2C_read_byte(uint8_t ack)
{
  uint8_t i = 0, receive = 0;

  I2C_SDA_IN();
  for (i = 0;i<8;i++)
  {
    I2C_SCL_L;
    delay_us(2);
    I2C_SCL_H;
    receive <<= 1;
    if (HAL_GPIO_ReadPin(GPIOB, I2C_SDA))
      receive++;
    delay_us(1);
  }
  ack?I2C_ack(1):I2C_ack(0);

  return receive;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
