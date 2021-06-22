/*
 * myFLASH.h
 *
 *  Created on: Jun 6, 2021
 *      Author: NgTP
 */

#ifndef INC_MYFLASH_H_
#define INC_MYFLASH_H_

void myFlashErase(uint8_t StaSector,uint8_t numSector)__attribute__ ((section(".RamFunc")));

void myFlashWrite (uint32_t address, uint32_t data2Write)__attribute__ ((section(".RamFunc")));



#endif /* INC_MYFLASH_H_ */
