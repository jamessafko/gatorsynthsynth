/**
  ******************************************************************************
  * File Name          : SDIO.c
  * Description        : This file provides code for the configuration
  *                      of the SDIO instances.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sdio.h"

#include "gpio.h"
#include "dma.h"

/* USER CODE BEGIN 0 */
#include "stm32f4xx_it.h"
#include "fatfs.h"
#include "ff.h"
#include <string.h>
extern int16_t wav_buff[48000 * 15];
extern Disk_drvTypeDef disk;
extern int enc_cnt_end;
extern int enc_cnt_start;
/* USER CODE END 0 */

SD_HandleTypeDef hsd;
DMA_HandleTypeDef hdma_sdio_rx;
DMA_HandleTypeDef hdma_sdio_tx;

/* SDIO init function */

void MX_SDIO_SD_Init(void)
{

  hsd.Instance = SDIO;
  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
  hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_ENABLE;
  hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd.Init.ClockDiv = 15;

}

void HAL_SD_MspInit(SD_HandleTypeDef* sdHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(sdHandle->Instance==SDIO)
  {
  /* USER CODE BEGIN SDIO_MspInit 0 */

  /* USER CODE END SDIO_MspInit 0 */
    /* SDIO clock enable */
    __HAL_RCC_SDIO_CLK_ENABLE();
  
    /**SDIO GPIO Configuration    
    PC8     ------> SDIO_D0
    PC12     ------> SDIO_CK
    PD2     ------> SDIO_CMD 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* SDIO DMA Init */
    /* SDIO_RX Init */
    hdma_sdio_rx.Instance = DMA2_Stream3;
    hdma_sdio_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_sdio_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sdio_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio_rx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio_rx.Init.Mode = DMA_PFCTRL;
    hdma_sdio_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_sdio_rx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_sdio_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_sdio_rx.Init.MemBurst = DMA_MBURST_INC4;
    hdma_sdio_rx.Init.PeriphBurst = DMA_PBURST_INC4;
    if (HAL_DMA_Init(&hdma_sdio_rx) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(sdHandle,hdmarx,hdma_sdio_rx);

    /* SDIO_TX Init */
    hdma_sdio_tx.Instance = DMA2_Stream6;
    hdma_sdio_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_sdio_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_sdio_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio_tx.Init.Mode = DMA_PFCTRL;
    hdma_sdio_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_sdio_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_sdio_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_sdio_tx.Init.MemBurst = DMA_MBURST_INC4;
    hdma_sdio_tx.Init.PeriphBurst = DMA_PBURST_INC4;
    if (HAL_DMA_Init(&hdma_sdio_tx) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(sdHandle,hdmatx,hdma_sdio_tx);

    /* SDIO interrupt Init */
    HAL_NVIC_SetPriority(SDIO_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(SDIO_IRQn);
  /* USER CODE BEGIN SDIO_MspInit 1 */

  /* USER CODE END SDIO_MspInit 1 */
  }
}

void HAL_SD_MspDeInit(SD_HandleTypeDef* sdHandle)
{

  if(sdHandle->Instance==SDIO)
  {
  /* USER CODE BEGIN SDIO_MspDeInit 0 */

  /* USER CODE END SDIO_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDIO_CLK_DISABLE();
  
    /**SDIO GPIO Configuration    
    PC8     ------> SDIO_D0
    PC12     ------> SDIO_CK
    PD2     ------> SDIO_CMD 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8|GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

    /* SDIO DMA DeInit */
    HAL_DMA_DeInit(sdHandle->hdmarx);
    HAL_DMA_DeInit(sdHandle->hdmatx);

    /* SDIO interrupt Deinit */
    HAL_NVIC_DisableIRQ(SDIO_IRQn);
  /* USER CODE BEGIN SDIO_MspDeInit 1 */

  /* USER CODE END SDIO_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

UINT bytesRead;
UINT bytesWritten;
FATFS myFATFS;
FIL myFile; // file pointer

int gs_sd_read_write_test()
{
	uint8_t failed = 0;
	volatile FRESULT check = FR_OK;
	//mount SD card

	//disk.is_initialized[0] = 0;
	check = f_mount(&myFATFS, (TCHAR const*) SDPath, 1);
	if (check == FR_OK) // 1 = connect
	{
		// LIMITED TO 8 CHARACTER FILE NAMES???
		char myPath[] = "JAMES4.TXT\0"; // user upper case and terminate with this char
		char myData[] = "Hello, world!!!";

		//Create and open this file
		check = f_open(&myFile, myPath, FA_WRITE | FA_CREATE_ALWAYS);
		if (check != FR_OK)
			_Error_Handler(__FILE__, __LINE__);

		check = f_write(&myFile, myData, sizeof(myData), &bytesWritten);
		if (check != FR_OK)
			_Error_Handler(__FILE__, __LINE__);

		check = f_close(&myFile);
		if (check != FR_OK)
			_Error_Handler(__FILE__, __LINE__);

		//Create and open this file
		check = f_open(&myFile, myPath, FA_READ | FA_OPEN_ALWAYS);
		if (check != FR_OK)
			_Error_Handler(__FILE__, __LINE__);
		char testData[sizeof(myData)];
		check = f_read(&myFile, testData, sizeof(testData), &bytesRead);
		if (check != FR_OK)
			_Error_Handler(__FILE__, __LINE__);
		check = f_close(&myFile);
		if (check != FR_OK)
			_Error_Handler(__FILE__, __LINE__);

		for (int i = 0; i < sizeof(testData); i++)
		{
			if (myData[i] != testData[i])
			{
				failed++;
			}
		}
	}
	else
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//f_mount(0, (TCHAR const*) SDPath, 1);
	return failed;
}

// This function adapted from ChaN, the creator of the FatFs library
int sd_read_wav(struct SoundFile *sound, char name[])
{

	//disk.is_initialized[0] = 0;
	FRESULT check = FR_OK;
	check = f_mount(&myFATFS, (TCHAR const*) SDPath, 1);
	if (check == FR_OK) // 1 = connect
	{
		//Create and open this file
		check = f_open(&myFile, name, FA_READ | FA_OPEN_ALWAYS);
		if (check != FR_OK)
			return 1;

		/**********	READ RIFF HEADER *********/
		char chunk[16];
		check = f_read(&myFile, &chunk, 12, &bytesRead);
		if (check != FR_OK)
			return 2;
		// Check chunk
		if (!(chunk[0] == 'R' && chunk[1] == 'I' && chunk[2] == 'F'
				&& chunk[3] == 'F' && chunk[8] == 'W' && chunk[9] == 'A'
				&& chunk[10] == 'V' && chunk[11] == 'E'))
			return 3;

		/**********	READ FMT HEADER *********/
		check = f_read(&myFile, &chunk, 4, &bytesRead);
		if (check != FR_OK)
			return 2;
		if (!(chunk[0] == 'f' && //fmt??
				chunk[1] == 'm' && chunk[2] == 't'))
			return 4;
		check = f_read(&myFile, &chunk, 4, &bytesRead);
		if (check != FR_OK)
			return 5;
		if (!(chunk[0] == 0x10 && //Subchunk1Size == 16 == PCM???
				chunk[1] == 0x00 && chunk[2] == 0x00 && chunk[3] == 0x00))
			return 6;

		// Parse file information
		check = f_read(&myFile, &chunk, 16, &bytesRead);
		if (check != FR_OK)
			return 7;
		if (!(chunk[0] == 0x01 && //AudioFormat == 1 == PCM???
				chunk[1] == 0x00))
			return 8;
		if (!(chunk[2] == 0x01 && //NumChannels == 1 == mono???
				chunk[3] == 0x00))
			return 8;
		sound->numChannels = (chunk[3] << 8) | chunk[2];
		// Skip sample rate verification
		//if (!(chunk[4] == 0x80 && //SampleRate == 44.1kHz???***************
				//chunk[5] == 0xBB && chunk[6] == 0x00 && chunk[7] == 0x00))
			//return 9;
		sound->sampleRate = (chunk[7] << 24) | (chunk[6] << 16) | (chunk[5] << 8)
				| chunk[4];
		if (!(chunk[14] == 16 && //bit depth == 16 bits???***************
				chunk[15] == 00))
			return 10;
		sound->bitDepth = (chunk[15] << 8) | chunk[14];

		// DATA CHUNK
		check = f_read(&myFile, &chunk[0], 4, &bytesRead);
		if (!(chunk[0] == 'd' && // Subchunk2ID == 'data'??????
				chunk[1] == 'a' && chunk[2] == 't' && chunk[3] == 'a'))
			return 11;
		check = f_read(&myFile, &chunk[0], 4, &bytesRead); // numsamples * num channels * bitdepth / 8
		sound->numSamples = 8
				* ((chunk[3] << 24) | (chunk[2] << 16) | (chunk[1] << 8) | chunk[0])
				/ (sound->numChannels * sound->bitDepth);

		// Read in data
		check = f_read(&myFile, &wav_buff, sound->numSamples * 2, &bytesRead);
		if (bytesRead != sound->numSamples * 2)
			return 12;

		sound->data = wav_buff;
		sound->currentSample = 0;
		sound->startSample = 0;
		sound->loopLength = sound->numSamples - 1;

		enc_cnt_end = sound->loopLength;
		enc_cnt_start = 0;

		if (f_close(&myFile) != FR_OK)
			return 13;
	}
	else
		return 14;

	//f_mount(0, (TCHAR const*) SDPath, 1);
	return 0;
}

// This function adapted from ChaN, the creator of the FatFs library
FRESULT scan_files(char* path) /* Start node to be scanned (***also used as work area***) */
{
	FRESULT res;
	DIR dir;
	static FILINFO fno;

	res = f_mount(&myFATFS, (TCHAR const*) SDPath, 1);
	if (res == FR_OK) // 1 = connect
	{
		res = f_opendir(&dir, path); /* Open the directory */
		if (res == FR_OK)
		{
			for (;;)
			{
				res = f_readdir(&dir, &fno); /* Read a directory item */
				if (res != FR_OK || fno.fname[0] == 0)
					break; /* Break on error or end of dir */
				if (fno.fattrib & AM_DIR)
				{ /* It is a directory */
					/*
					 i = strlen(path);
					 sprintf(&path[i], "/%s", fno.fname);
					 res = scan_files(path); // Enter the directory
					 if (res != FR_OK)
					 break;
					 path[i] = 0;
					 */
				}
				else
				{ /* It is a file. */
					printf("%s/%s\n", path, fno.fname);
				}
			}
			f_closedir(&dir);
		}
	}

	return res;
}

DIR dir;
static FILINFO fno;

// This function adapted from ChaN, the creator of the FatFs library
FRESULT open_dir(char* path) /* Start node to be scanned (***also used as work area***) */
{
	FRESULT res;

	res = f_mount(&myFATFS, (TCHAR const*) SDPath, 1);
	if (res == FR_OK) // 1 = connect
	{
		res = f_opendir(&dir, path); /* Open the directory */
	}

	return res;
}

// This function adapted from ChaN, the creator of the FatFs library
char* read_one_name() /* Start node to be scanned (***also used as work area***) */
{
	FRESULT res;

	res = f_readdir(&dir, &fno); /* Read a directory item */
	if (res != FR_OK || fno.fname[0] == 0)
	{
		f_closedir(&dir);
		return "done\0"; /* Break on error or end of dir */
	}
	if (fno.fattrib & AM_DIR)
	{ /* It is a directory */
		return read_one_name();
	}
	else
	{ /* It is a file. */
		return fno.fname;
	}
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
