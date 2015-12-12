#include "FLASH.h"
#include "RCC.h"
#include "DMA.h"
#include <stdint.h>

#define TRANSFER_LEN	1

int main(void)
{
	checkReg();
	int error=0,guard=0;
	int latency=checkLatency();
	uint32_t HCLCK=getSystemClock();
	uint64_t *readAdd;
	uint32_t checkHISR= DMA2->HISR;
	uint32_t chcekS7CR= DMA2->S7.CR;
	uint32_t SRC_Const_Buffer,DST_Buffer;
	uint32_t ptr2DST = DST_Buffer;
	uint32_t ptr2SRC = SRC_Const_Buffer;

	DMA2UnresetEnableClock();


	while(1){
		unlockFlashCR();

		error=checkError();
		readAdd=((uint64_t *)TARGET_ADD);
		checkReg();
		//Sector Erase
		if(guard){
			sectorErase(SECTOR1);
			guard=0;
		}
		checkReg();
		readAdd=((uint64_t *)TARGET_ADD);
		//Bank Erase
		if(guard){
			bankErase(BANK1);
			guard=0;
		}
		checkReg();
		readAdd=((uint64_t *)TARGET_ADD);
		//Flash Program
		if(guard){
			flashProgram(x32,0x0101010101010101,0x08004000);
			guard=0;
		}
		checkReg();
		readAdd=((uint64_t *)TARGET_ADD);
		//DMA transfer
		if(guard){
			configDMA2s7CR(MemToMem,x32,x32,VeryHighPrio,CHANNEL0);
			chcekS7CR= DMA2->S7.CR;
			SRC_Const_Buffer= 0x10111101;
			DMA_memcpy8( ((uint32_t *)TARGET_ADD), &SRC_Const_Buffer, TRANSFER_LEN );
			flashProgramConfig(x32);
			flashProgramEn();
			enableDMA();
			readAdd=((uint64_t *)TARGET_ADD);
		}
		checkReg();
		readAdd=((uint64_t *)TARGET_ADD);

		flashLock();
		readAdd=((uint64_t *)0x08100000);
		checkReg();
	}



}
