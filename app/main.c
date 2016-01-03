#include "FLASH.h"
#include "RCC.h"
#include "DMA.h"
#include <stdint.h>

#define TRANSFER_LEN	14

int main(void)
{
	int flashError=0;int guard=0;int i=0;
	int latency=checkLatency();
	uint32_t HCLCK=getSystemClock();
	WRITE_SIZE *readAdd=TARGET_ADD;
	uint32_t *readAdd1=((uint32_t *)0x08104000);
	uint32_t SRC_Const_Buffer[]={12,23,15,10,12,22,22,12,32,12,14,53,90,99};
	uint32_t test_Buffer[10];

	DMA2UnresetEnableClock();

	while(1){
		checkFlashReg();
		unlockFlashCR();
		checkFlashReg();
		unlockFlashOptionByte();
		flashError=checkFlashError();
		for(i=0;i<TRANSFER_LEN;i++)
			readAdd1++;
		checkDMAReg();
		checkFlashReg();
		//Sector Erase
		if(guard){
			sectorErase(SECTOR13);
			flashError=checkFlashError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=TARGET_ADD;
		//Bank Erase
		if(guard){
			bankErase(BANK2);
			flashError=checkFlashError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=TARGET_ADD;
		//Flash Program
		if(guard){
			flashProgram(x32,0x11101,TARGET_ADD);
			flashError=checkFlashError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=TARGET_ADD;
		//Program by DMA transfer
		if(guard){
			configDMA2s7CR(MemToMem,x32,x32,VeryHighPrio,CHANNEL0);
			DMA_memcpy8( ((uint32_t *)0x08104000), SRC_Const_Buffer, TRANSFER_LEN );
			//DMA_memcpy8( test_Buffer, SRC_Const_Buffer, TRANSFER_LEN );

			flashProgramConfig(x32);
			flashProgramEn();
			enableDMA();
			while(checkBusy()){}
			flashError=checkFlashError();

			flashProgramDisable();
			clearDMAHighIntrrFlag();


			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=TARGET_ADD;

		flashLock();
		flashOptionByteLock();
		readAdd=TARGET_ADD;

		checkDMAReg();
		checkFlashReg();
	}



}
