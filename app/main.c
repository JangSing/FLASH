#include "FLASH.h"
#include "RCC.h"
#include "DMA.h"
#include <stdint.h>

#define TRANSFER_LEN	3

int main(void)
{
	int error=0,guard=0,i=0;
	int latency=checkLatency();
	uint32_t HCLCK=getSystemClock();
	uint64_t *readAdd;
	uint32_t *readAdd1=((uint32_t *)0x08104000);
	uint32_t SRC_Const_Buffer[3]={0x10100010,0x10111010,0x11110000};

	checkDMAReg();
	checkFlashReg();

	DMA2UnresetEnableClock();

	while(1){
		unlockFlashCR();
		error=checkError();
		for(i=0;i<10;i++)
			readAdd1++;
		checkDMAReg();
		checkFlashReg();
		//Sector Erase
		if(guard){
			sectorErase(SECTOR13);
			error=checkError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=((uint64_t *)TARGET_ADD);
		//Bank Erase
		if(guard){
			bankErase(BANK2);
			error=checkError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=((uint64_t *)TARGET_ADD);
		//Flash Program
		if(guard){
			flashProgram(x32,0x0101010101010101,0x08004000);
			error=checkError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=((uint64_t *)TARGET_ADD);
		//Program by DMA transfer
		if(guard){
			configDMA2s7CR(MemToMem,x32,x32,VeryHighPrio,CHANNEL0);
			DMA_memcpy8( ((uint32_t *)0x08104000), &SRC_Const_Buffer, TRANSFER_LEN );
			flashProgramConfig(x32);
			flashProgramEn();
			enableDMA();
			flashProgramDisable();
			clearDMAHighIntrrFlag();
			error=checkError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=((uint64_t *)TARGET_ADD);

		flashLock();
		readAdd=((uint64_t *)0x08100000);

		checkDMAReg();
		checkFlashReg();
	}



}
