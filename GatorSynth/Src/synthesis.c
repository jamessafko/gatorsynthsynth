/*
 * synthesis.c
 *
 *  Created on: Nov 7, 2018
 *      Author: jamessafko
 */

#include "synthesis.h"
//#include "stm32f4xx_ll_dma_2.h"
#include <math.h>

#define BUFFER_SIZE 256

int16_t wav_buff[44100 * 5] __attribute__((__section__(".sdram")));
int16_t out_buff_1[BUFFER_SIZE] =
{ 0 };
int16_t out_buff_2[BUFFER_SIZE] =
{ 0 };
//int16_t sine_buff_1[BUFFER_SIZE] =
//{ 0 };

int16_t *curr_out_buff = out_buff_2;
extern SAI_HandleTypeDef hsai_BlockA1;
extern TIM_HandleTypeDef htim4;
uint8_t which_one = 0;
uint8_t processing_complete = 0;


struct SoundFile sample;

static uint32_t SAI_InterruptFlag_2(SAI_HandleTypeDef *hsai, uint32_t mode)
{
	uint32_t tmpIT = SAI_IT_OVRUDR;

	if (mode == 1)
	{
		tmpIT |= SAI_IT_FREQ;
	}

	if ((hsai->Init.Protocol == SAI_AC97_PROTOCOL)
			&& ((hsai->Init.AudioMode == SAI_MODESLAVE_RX)
					|| (hsai->Init.AudioMode == SAI_MODEMASTER_RX)))
	{
		tmpIT |= SAI_IT_CNRDY;
	}

	if ((hsai->Init.AudioMode == SAI_MODESLAVE_RX)
			|| (hsai->Init.AudioMode == SAI_MODESLAVE_TX))
	{
		tmpIT |= SAI_IT_AFSDET | SAI_IT_LFSDET;
	}
	else
	{
		/* hsai has been configured in master mode */
		tmpIT |= SAI_IT_WCKCFG;
	}
	return tmpIT;
}

void GS_SAI_Start()
{
	//Turn off all GPIOs to start
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	hsai_BlockA1.Instance->CR1 |= 1 << 16; // enable
	hsai_BlockA1.Instance->CR1 |= 1 << 13; // enable output drive
	hsai_BlockA1.Instance->CR1 |= 1 << 12; // enable mono mode

	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_Delay(20);

	// Turn on LRCLK
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_Delay(20);

	// Turn on SCLK
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_Delay(20);

	// Turn on Data
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_Delay(20);
}

void start_audio()
{

	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		//sine_buff_1[i] = (int16_t) (32767.0
			//	* sin(2.0 * M_PI * i / (2.0 * BUFFER_SIZE))); // sine
		//sine_buff_1[i] = (int16_t) ((((float) i - (double) (BUFFER_SIZE / 2))
			//	/ (double) (BUFFER_SIZE / 2)) * 32767.0); // saw
	}

	for (int i = BUFFER_SIZE; i < 2*BUFFER_SIZE; i++)
		{
			//sine_buff_2[i - BUFFER_SIZE] = (int16_t) (32767.0
					//* sin(2.0 * M_PI * i / (2.0 * BUFFER_SIZE))); // sine
			//saw_buff[i] = (int16_t) ((((float) i - (double) (BUFFER_SIZE / 2))
					// / (double) (BUFFER_SIZE / 2)) * 32767.0); // saw
		}


	if (SAI_DoubleBuffer(&hsai_BlockA1, out_buff_1, out_buff_2, BUFFER_SIZE))
		_Error_Handler(__FILE__, __LINE__);
}

volatile int sad;
void tx_complete_1(DMA_HandleTypeDef *hdma)
{
	//if(processing_complete != 1)
		//sad = 0;

	curr_out_buff = &(out_buff_1[0]);
	processing_complete = 0; // ready for new process
	//process_block();
}

void half_tx(DMA_HandleTypeDef *hdma)
{

}

void sai_dma_error()
{

}

void tx_complete_2()
{
	//if(processing_complete != 1)
		//sad = 0;

	curr_out_buff = &(out_buff_2[0]);
	processing_complete = 0; // ready for new process
	//process_block();
}

uint32_t out_index = 0;
uint16_t pitch_int = 256;
float sample_index = 0;
float pitch_factor = 1;
void process_block()
{
	pitch_factor = 0.5f + (pitch_int)/(4096.0f);

	if (processing_complete != 1)
	{
		// Turn off LCD while processing
		HAL_TIM_Base_Stop_IT(&htim4);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);

		for(out_index = 0; out_index < BUFFER_SIZE; out_index++)
		{
			curr_out_buff[out_index] = sample.data[(uint32_t)(sample.currentSample)];

			//sample_index = fmod((double)(sample_index + pitch_factor), (double) sample.numSamples);
			sample.currentSample += pitch_factor;

			// Past end point
			if((uint32_t)(sample.currentSample) > sample.endSample)
				sample.currentSample -= (float)(sample.endSample - sample.startSample + 1);
			if((uint32_t)(sample.currentSample) < sample.startSample)
				sample.currentSample = sample.startSample;
		}

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
		// Turn off LCD while processing
		HAL_TIM_Base_Start_IT(&htim4);
		processing_complete = 1;
	}

	//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_5);
}

/**
 * @brief  Transmit an amount of data in non-blocking mode with DMA.
 * @param  hsai pointer to a SAI_HandleTypeDef structure that contains
 *               the configuration information for SAI module.
 * @param  pData Pointer to data buffer
 * @param  Size Amount of data to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef SAI_DoubleBuffer(SAI_HandleTypeDef *hsai, uint8_t *src1,
		uint8_t *src2, uint16_t Size)
{
	if ((src1 == NULL) || (Size == 0))
	{
		return HAL_ERROR;
	}

	if (hsai->State == HAL_SAI_STATE_READY)
	{
		/* Process Locked */
		__HAL_LOCK(hsai);

		hsai->pBuffPtr = src1;
		hsai->XferSize = Size;
		hsai->XferCount = Size;
		hsai->ErrorCode = HAL_SAI_ERROR_NONE;
		hsai->State = HAL_SAI_STATE_BUSY_TX;

		/* Set the SAI Tx DMA Half transfer complete callback */
		hsai->hdmatx->XferHalfCpltCallback = half_tx;

		/* Set the SAI TxDMA transfer complete callback */
		hsai->hdmatx->XferCpltCallback = tx_complete_1;

		/* Set the DMA error callback */
		hsai->hdmatx->XferErrorCallback = sai_dma_error;

		hsai->hdmatx->XferM1CpltCallback = tx_complete_2;

		/* Set the DMA Tx abort callback */
		hsai->hdmatx->XferAbortCallback = NULL;

		/* Enable the Tx DMA Stream */
		if (HAL_DMAEx_MultiBufferStart_IT(hsai->hdmatx, (uint32_t) hsai->pBuffPtr,
				(uint32_t) &hsai->Instance->DR, (uint32_t) src2, hsai->XferSize)
				!= HAL_OK)
		{
			__HAL_UNLOCK(hsai);
			return HAL_ERROR;
		}

		/* Check if the SAI is already enabled */
		if ((hsai->Instance->CR1 & SAI_xCR1_SAIEN) == RESET)
		{
			/* Enable SAI peripheral */
			__HAL_SAI_ENABLE(hsai);
		}

		/* Enable the interrupts for error handling */
		__HAL_SAI_ENABLE_IT(hsai, SAI_InterruptFlag_2(hsai, 0));

		/* Enable SAI Tx DMA Request */
		hsai->Instance->CR1 |= SAI_xCR1_DMAEN;

		/* Process Unlocked */
		__HAL_UNLOCK(hsai);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}

