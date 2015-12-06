#include "FLASH.h"
#include <stdint.h>



void sectorErase(){

	int busyCount=0;
	uint32_t checkSR,checkCR;
	uint32_t *readAdd;
	int busy=(FLASH->SR & SR_BSY)>>16;
	if(!busy){
		FLASH->CR |= CR_SER;
		FLASH->CR |= CR_SNB4;
		FLASH->CR |= CR_STRT;
		checkSR=FLASH->SR;
		checkCR=FLASH->CR;
		busy=(FLASH->SR & SR_BSY)>>16;
		while(busy){
			readAdd=((uint32_t *)(0x08100000));
			busy=(FLASH->SR & SR_BSY)>>16;
			busyCount++;
		}
	}
	FLASH->CR &= ~CR_SER;
	FLASH->CR &= ~CR_SNB4;
	checkSR=FLASH->SR;
	checkCR=FLASH->CR;
}

void flashProgram(){
	int busyCount=0,error=0;
	uint32_t checkSR,checkCR;
	uint32_t *write,*readAdd;

	write=((uint32_t *)(0x08100000));
	int busy=(FLASH->SR & SR_BSY)>>16;
	if(!busy){

		FLASH->CR |= CR_PSIZE0;
		FLASH->CR |= CR_PSIZE1;
		FLASH->CR |= CR_PG;
		error=checkError();
		checkSR=FLASH->SR;
		checkCR=FLASH->CR;
		*write=1;
		busy=(FLASH->SR & SR_BSY)>>16;
		error=checkError();
		/*

		while(busy){
			readAdd=((uint32_t *)(0x08100000));
			busy=(FLASH->SR & SR_BSY)>>16;
			busyCount++;
		}
		readAdd=((uint32_t *)(0x08100000));
		*/
	}


}

int main(void)
{
	int i,error;
	uint32_t checkCR;
	uint32_t *readSector;

	unlockFlashControl();
	error=checkError();
	sectorErase();
	readSector=((uint32_t *)0x08100000);
	flashProgram();




}
