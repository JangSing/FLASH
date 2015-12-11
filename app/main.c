#include "FLASH.h"
#include "RCC.h"
#include "DMA.h"
#include <stdint.h>

#define TRANSFER_LEN	9

int main(void)
{
	checkReg();
	int error=0,guard=0;
	int latency=checkLatency();
	uint32_t HCLCK=getSystemClock();
	uint64_t *readAdd;

	DMA2UnresetEnableClock();

	uint32_t checkHISR= DMA2->HISR;
	uint32_t chcekS7CR= DMA2->S7.CR;
	uint32_t SRC_Const_Buffer[9]= {1234,1211,256,12,23,34,45,56,67};
	uint32_t DST_Buffer[9]= {1,1,1,1,1,1,1,1,1};


	configDMA2s7CR();
	chcekS7CR= DMA2->S7.CR;
	DMA_memcpy8( DST_Buffer, SRC_Const_Buffer, TRANSFER_LEN );
	uint32_t *ptr2DST = DST_Buffer;
	uint32_t *ptr2SRC = SRC_Const_Buffer;
	enableDMA();
	checkHISR=  DMA2->HISR;

	while(1){
		unlockFlashCR();

		error=checkError();
		readAdd=((uint64_t *)TARGET_ADD);
		checkReg();

		if(guard){
			sectorErase(SECTOR1);
			guard=0;
		}
		checkReg();
		readAdd=((uint64_t *)TARGET_ADD);
		if(guard){
			bankErase(BANK1);
			guard=0;
		}
		checkReg();
		readAdd=((uint64_t *)TARGET_ADD);
		if(guard){
			flashProgram(x32,0x0101010101010101,0x08004000);
			guard=0;
		}
		checkReg();
		readAdd=((uint64_t *)TARGET_ADD);

		flashLock();
		readAdd=((uint64_t *)0x08100000);
		checkReg();
	}



}
