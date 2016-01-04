#include "FLASH.h"
#include "RCC.h"
#include "DMA.h"
#include <stdint.h>

#define TRANSFER_LEN	12

int main(void)
{
	int flashError=0;int guard=0;
	int latency=checkLatency();
	uint32_t HCLCK=getSystemClock();
	WRITE_SIZE *readAdd=TARGET_ADD;
	int i=0;
	WRITE_SIZE *readAdd1=TARGET_ADD;
	WRITE_SIZE SRC_Const_Buffer[]={12,23,15,10,12,34,56,87,98,36,90,100,123,156,189};

	char *str="JANG SING";

	DMA2UnresetEnableClock();

	while(1){
		checkFlashReg();
		unlockFlashCR();
		checkFlashReg();
		flashError=checkFlashError();
		for(i=0;i<(TRANSFER_LEN+1);i++)
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
			flashProgram(x32,0x23872,TARGET_ADD);
			flashError=checkFlashError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=TARGET_ADD;
		//Program Flash memory by DMA transfer
		if(guard){
			configDMA2s7CR(MemToMem,x32,x32,VeryHighPrio,CHANNEL0);
			DMA_memcpy(TARGET_ADD, ((uint32_t *)str), TRANSFER_LEN );
			flashProgramConfig(x32);
			flashProgramEn();
			enableDMA();
			while(checkBusy()){}
			flashError=checkFlashError();
			flashProgramDisable();
			clearDMAHighIntrrFlag();
			flashError=checkFlashError();
			guard=0;
		}
		checkDMAReg();
		checkFlashReg();
		readAdd=TARGET_ADD;

		flashLock();
		readAdd=TARGET_ADD;

		checkDMAReg();
		checkFlashReg();
	}



}
