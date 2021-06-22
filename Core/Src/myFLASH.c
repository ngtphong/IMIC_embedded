/*
 * myFLASH.c
 *
 *  Created on: Jun 6, 2021
 *      Author: NgTP
 */
#include "main.h"
#include "myFLASH.h"

void myFlashErase(uint8_t StaSector,uint8_t numSector)
{
/*
 * STEP FOLLOWED
 * 1. Check no Flash memory operation is ongoing by checking BSY bit in FLASH_SR register
 * 2. Set the SER bit and select the sector out of the 7 sectors (STM32F411) in the main memory
 * block you wish to erase (SNB) in the FLASH_CR register
 * 3. Set the STRT bit in the FLASH_CR register
 * 4. Wait for BSY bit to be cleared
 */
	uint32_t *FLASH_SR = (uint32_t*) 0x40023c0c;
	uint32_t *FLASH_CR = (uint32_t*) 0x40023c10;

	*FLASH_CR |= (1<<1);						// (SER bit) Sector Erase activate
	*FLASH_CR &= ~(1<<0);						// (PG bit) Flash programming deactivate
	*FLASH_CR |= (0b10<<8);						// PSIZE bits - program x32 parallelism.

	for (uint8_t i = 0; i < numSector; i++)
	{
		uint8_t Sector = StaSector + i;
		if ((Sector >=0) && (Sector <= 7))
		{
			while ((*FLASH_SR & (1<<16))) {};			// Wait for BSY bit deactivate
			*FLASH_CR &= ~(0b1111 << 3);				// Clear SNB
			*FLASH_CR |= (Sector << 3);					// Select the sector to erase
			*FLASH_CR |= (1<<16);						// Start erasing
			while ((*FLASH_SR & (1<<16))) {};			// Wait for BSY bit deactivate
			while ((*FLASH_SR & (1<<0))) {};			// Wait for EOP bit activate
			*FLASH_SR |=  (1<<0);						// Clear EOP by writing a 1.
		}
	}

	*FLASH_CR &= ~(1<<1);						// (SER bit) Sector Erase deactivate
}

void myFlashWrite (uint32_t address, uint32_t data2Write)
{
/*
 * STEP FOLLOWED
 * 1. Check no Flash memory operation is ongoing by checking BSY bit in FLASH_SR register
 * 2. Set the PG bit in the FLASH_CR register
 * 3. Perform the data write operation to the desired memory address
 * 4. Wait for BSY bit to be cleared
 */

	uint32_t *FLASH_SR = (uint32_t*) 0x40023c0c;
	uint32_t *FLASH_CR = (uint32_t*) 0x40023c10;

	volatile uint32_t *pData;

	*FLASH_CR |= (1<<0);						// (PG bit) Flash programming activate
	*FLASH_CR &= ~(1<<1);						// (SER bit) Sector Erase deactivate
	*FLASH_CR |= (0b10<<8);						// PSIZE bits - program x32 parallelism.

	pData = address;
	while ((*FLASH_SR & (1<<16))) {};			// Wait for BSY bit deactivate
	*pData = data2Write;
	while ((*FLASH_SR & (1<<16))) {};			// Wait for BSY bit deactivate
	while ((*FLASH_SR & (1<<0))) {};			// Wait for EOP bit activate
	*FLASH_SR |=  (1<<0);						// Clear EOP by writing a 1.
	*FLASH_CR &= ~(1<<0);						// (PG bit) Flash programming deactivate

}

