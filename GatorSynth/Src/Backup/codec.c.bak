/*
 * codec.c
 *
 *  Created on: Oct 10, 2018
 *      Author: jamessafko
 */

#include "codec.h"
#include "stmpe811.h"
#include "gpio.h"
#include "stm32f429i_discovery_ts.h"
#include "stm32f429i_discovery.h"


extern I2C_HandleTypeDef I2cHandle;
uint8_t i2cBuff[2] = {0, 0}; //register address, value


HAL_StatusTypeDef test_i2c_connection()
{
	/*
	uint8_t buff[2] = {0x2, 5};
	  volatile HAL_StatusTypeDef test23=HAL_I2C_Master_Transmit(&I2cHandle, 24<<1, buff, 2, 10);

	  HAL_I2C_Master_Transmit(&I2cHandle, codec_address, 0x2, 1, 10);
	 */
	  return HAL_I2C_IsDeviceReady(&I2cHandle, codec_address, 1, 100);

	  /*
	  for(uint8_t i = 0; i < 255; i++)
	  {
		if(HAL_I2C_IsDeviceReady(&I2cHandle, i, 1, 100) == HAL_OK)
		{
			volatile int test = 0;
			//break;
		}
	  }
	  */
}

uint8_t write_to_codec(uint8_t pageNum, uint8_t regAddr, uint8_t regValue)
{
	volatile HAL_StatusTypeDef result;

	//can read and write zeros
	// clock stops on nonzero register and nonzero value??
	// --> busy flag up

	// ARBITRATION LOST when try to write a 1 (something holds line low)
		// Clock timing?
		// Dad pull high?

	// Set page number
	i2cBuff[0] = 0; // register
	i2cBuff[1] = 0; // register value
	IOE_Write(codec_address, i2cBuff[0], i2cBuff[1]);
	//I2C3_ClearBusyFlagErratum(&I2cHandle);

	I2Cx_Error();

	i2cBuff[0] = 0; // register
	i2cBuff[1] = 1; // register value
	if((result = HAL_I2C_Master_Transmit(&I2cHandle, codec_address, i2cBuff, 2, 1000)) != HAL_OK)
		i2cBuff[1] = 0;
	I2Cx_Error();

	volatile testResult = -1;
	//testResult = I2Cx_ReadData(codec_address|1, i2cBuff[0]);
	//I2Cx_Error();

	/*
	if((result = HAL_I2C_Master_Transmit(&I2cHandle, codec_address, i2cBuff, 2, 1000)) != HAL_OK)
		return -1;
	while(HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY);
	 */

	// Verify page number was written (read it)

	i2cBuff[0] = 0xFF; // register
	i2cBuff[1] = 0; // register value
	if((result = HAL_I2C_Master_Transmit(&I2cHandle, codec_address, &i2cBuff[0], 1, 1000)) != HAL_OK)
		I2Cx_Error();
	I2Cx_Error();
	if((result = HAL_I2C_Master_Receive(&I2cHandle, codec_address|1, &i2cBuff[1], 1, 1000)) != HAL_OK) // SW reset
		I2Cx_Error();
	I2Cx_Error();
	if(i2cBuff[1] != pageNum)
		return -1;





  if(HAL_I2C_Master_Transmit(&I2cHandle, codec_address, i2cBuff, 2, 10) != HAL_OK) // SW reset
	  I2Cx_Error();

  // Double check page


  //while(1)
  //{
	  //IOE_Write(codec_address, 2, 1);
	  //IOE_Delay(10);
	  //result = IOE_Read(codec_address, 0);
	  //IOE_Delay(10);
  //}

  //https://jure.tuta.si/?p=7

  volatile HAL_StatusTypeDef test;
  if((test = HAL_I2C_Master_Transmit(&I2cHandle, codec_address, i2cBuff, 1, 10)) != HAL_OK) // SW reset
	  return -1;


  if((test = HAL_I2C_Master_Receive(&I2cHandle, codec_address|1, &i2cBuff[1], 1, 10)) != HAL_OK) // SW reset
	  return -1;

  i2cBuff[0] = regAddr;
  i2cBuff[1] = regValue;
  test = HAL_I2C_Master_Transmit(&I2cHandle, codec_address, i2cBuff, 2, 10);
  if(test != HAL_OK) // SW reset
	  return -1;

  return 0;
}

#define I2C3_SDA_Pin GPIO_PIN_9
#define I2C3_SDA_GPIO_Port GPIOC
#define I2C3_SCL_Pin GPIO_PIN_8
#define I2C3_SCL_GPIO_Port GPIOA

void I2C3_ClearBusyFlagErratum(I2C_HandleTypeDef *instance)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    int timeout =100;
    int timeout_cnt=0;

    // 1. Clear PE bit.
    instance->Instance->CR1 &= ~(0x0001);

    //  2. Configure the SCL and SDA I/Os as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
    GPIO_InitStruct.Mode         = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Alternate    = GPIO_AF4_I2C3;
    GPIO_InitStruct.Pull         = GPIO_PULLUP;
    GPIO_InitStruct.Speed        = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Pin          = I2C3_SCL_Pin;
    HAL_GPIO_Init(I2C3_SCL_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_WritePin(I2C3_SCL_GPIO_Port, I2C3_SCL_Pin, GPIO_PIN_SET);

    GPIO_InitStruct.Pin          = I2C3_SDA_Pin;
    HAL_GPIO_Init(I2C3_SDA_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_WritePin(I2C3_SDA_GPIO_Port, I2C3_SDA_Pin, GPIO_PIN_SET);


    // 3. Check SCL and SDA High level in GPIOx_IDR.
    while (GPIO_PIN_SET != HAL_GPIO_ReadPin(I2C3_SDA_GPIO_Port, I2C3_SDA_Pin))
    {
        //Move clock to release I2C
        HAL_GPIO_WritePin(I2C3_SCL_GPIO_Port, I2C3_SCL_Pin, GPIO_PIN_RESET);
        asm("nop");
        HAL_GPIO_WritePin(I2C3_SCL_GPIO_Port, I2C3_SCL_Pin, GPIO_PIN_SET);

        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    reInit_driver();

    /*
    // 4. Configure the SDA I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
    HAL_GPIO_WritePin(I2C3_SDA_GPIO_Port, I2C3_SDA_Pin, GPIO_PIN_RESET);

    //  5. Check SDA Low level in GPIOx_IDR.
    while (GPIO_PIN_RESET != HAL_GPIO_ReadPin(I2C3_SDA_GPIO_Port, I2C3_SDA_Pin))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 6. Configure the SCL I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
    HAL_GPIO_WritePin(I2C3_SCL_GPIO_Port, I2C3_SCL_Pin, GPIO_PIN_RESET);

    //  7. Check SCL Low level in GPIOx_IDR.
    while (GPIO_PIN_RESET != HAL_GPIO_ReadPin(I2C3_SCL_GPIO_Port, I2C3_SCL_Pin))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 8. Configure the SCL I/O as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
    HAL_GPIO_WritePin(I2C3_SCL_GPIO_Port, I2C3_SCL_Pin, GPIO_PIN_SET);

    // 9. Check SCL High level in GPIOx_IDR.
    while (GPIO_PIN_SET != HAL_GPIO_ReadPin(I2C3_SCL_GPIO_Port, I2C3_SCL_Pin))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 10. Configure the SDA I/O as General Purpose Output Open-Drain , High level (Write 1 to GPIOx_ODR).
    HAL_GPIO_WritePin(I2C3_SDA_GPIO_Port, I2C3_SDA_Pin, GPIO_PIN_SET);

    // 11. Check SDA High level in GPIOx_IDR.
    while (GPIO_PIN_SET != HAL_GPIO_ReadPin(I2C3_SDA_GPIO_Port, I2C3_SDA_Pin))
    {
        timeout_cnt++;
        if(timeout_cnt>timeout)
            return;
    }

    // 12. Configure the SCL and SDA I/Os as Alternate function Open-Drain.
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;

    GPIO_InitStruct.Pin = I2C3_SCL_Pin;
    HAL_GPIO_Init(I2C3_SCL_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = I2C3_SDA_Pin;
    HAL_GPIO_Init(I2C3_SDA_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(I2C3_SCL_GPIO_Port, I2C3_SCL_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(I2C3_SDA_GPIO_Port, I2C3_SDA_Pin, GPIO_PIN_SET);

    // 13. Set SWRST bit in I2Cx_CR1 register.
    instance->Instance->CR1 |= 0x8000;

    asm("nop");

    // 14. Clear SWRST bit in I2Cx_CR1 register.
    instance->Instance->CR1 &= ~0x8000;

    asm("nop");

    // 15. Enable the I2C peripheral by setting the PE bit in I2Cx_CR1 register
    instance->Instance->CR1 |= 0x0001;

    // Call initialization function.
    HAL_I2C_Init(instance);
    */
}

