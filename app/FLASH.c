#include "FLASH.h"

void unlockFlashControl(){
  FLASH->KEYR =0x45670123;
  FLASH->KEYR =0xCDEF89AB;
}

void sectorErase(){

	int busyCount=0;
	uint32_t *readAdd;
  
	if(!checkBusy()){

		checkSRnCR();
		FLASH->CR &= ~(FLASH_CR_SER);
		FLASH->CR &= ~(FLASH_CR_SNB4);
		FLASH->CR &= ~(FLASH_CR_STRT);
		checkSRnCR();
		FLASH->CR |= FLASH_CR_SER;
		FLASH->CR |= FLASH_CR_SNB4;
		FLASH->CR |= FLASH_CR_STRT;
		checkSRnCR();

		while(checkBusy()){
			readAdd=((uint32_t *)(0x08100000));
			busyCount++;
		}
	}
	FLASH->CR &= ~FLASH_CR_SER;
	FLASH->CR &= ~FLASH_CR_SNB4;
	checkSRnCR();
}

void flashProgram(){
	int busyCount=0,error=0;
	uint32_t *write,*readAdd;

	write=((uint32_t *)(0x08100000));

	if(!checkBusy()){

		checkSRnCR();
		FLASH->CR &= ~(FLASH_CR_PSIZE0);
		FLASH->CR &= ~(FLASH_CR_PSIZE1);
		checkSRnCR();
		//FLASH->CR |= FLASH_CR_PSIZE0;
		FLASH->CR |= FLASH_CR_PSIZE1;
		checkSRnCR();
		FLASH->CR &= ~(FLASH_CR_PG);
		FLASH->CR |= FLASH_CR_PG;
		checkSRnCR();

		error=checkError();

		checkSRnCR();

		*write=0x01010101;
		error=checkError();

		while(checkBusy()){
			readAdd=((uint32_t *)(0x08100000));
			busyCount++;
		}
		readAdd=((uint32_t *)(0x08100000));
	}


}

int checkBusy(){
	return ((FLASH->SR>>16)&1);
}

int checkError(){
  int seqErr,parallelErr,alignErr;
  
  checkSRnCR();
  seqErr      = (FLASH->SR>>7)&1;
  parallelErr = (FLASH->SR>>6)&1;
  alignErr    = (FLASH->SR>>5)&1;
  
  if(seqErr!=0 || parallelErr!=0 || alignErr!=0)
    return 1;
  else
    return 0;
}
  
void checkSRnCR(){
	uint32_t checkSR,checkCR;
	checkSR=FLASH->SR;
	checkCR=FLASH->CR;
}


