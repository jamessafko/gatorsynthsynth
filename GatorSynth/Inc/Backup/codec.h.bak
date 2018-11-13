/*
 * codec.h
 *
 *  Created on: Oct 10, 2018
 *      Author: jamessafko
 */

#ifndef CODEC_H_
#define CODEC_H_

#include "main.h"

#define codec_address (24<<1)

HAL_StatusTypeDef test_i2c_connection();

uint8_t write_to_codec(uint8_t pageNum, uint8_t regAddr, uint8_t regValue);

void I2C3_ClearBusyFlagErratum(I2C_HandleTypeDef *instance);

#endif /* CODEC_H_ */
