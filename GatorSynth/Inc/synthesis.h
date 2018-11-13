/*
 * synthesis.h
 *
 *  Created on: Nov 7, 2018
 *      Author: jamessafko
 */

#ifndef SYNTHESIS_H_
#define SYNTHESIS_H_

#include "main.h"
#include "stm32f4xx_hal.h"

// used to describe a sound file
struct SoundFile{
	uint32_t startSample;
	uint32_t endSample;
	float currentSample;
	uint32_t numSamples;
	uint16_t numChannels;
	uint16_t bitDepth;
	uint32_t sampleRate;
	char* name;
	int16_t* data;
};

void GS_SAI_Start();
void start_audio();
void process_block();
HAL_StatusTypeDef SAI_DoubleBuffer(SAI_HandleTypeDef *hsai, uint8_t *src1, uint8_t *src2, uint16_t Size);

#endif /* SYNTHESIS_H_ */
