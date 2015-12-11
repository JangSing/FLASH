#include "FLASH.h"

void unlockFlashCR(){
	FLASH->KEYR =0x45670123;
	FLASH->KEYR =0xCDEF89AB;
}

void flashLock(){
	FLASH->CR |= FLASH_CR_LOCK;
}

void sectorErase(uint32_t sectorNum){

	int busyCount=0;
  
	if(!checkBusy()){
		checkReg();
		FLASH->CR &= ~(FLASH_CR_SER);
		FLASH->CR &= ~(FLASH_CR_SNB);
		FLASH->CR &= ~(FLASH_CR_STRT);
		checkReg();
		FLASH->CR |= FLASH_CR_SER;
		FLASH->CR |= sectorNum << FLASH_CR_SNB_bit;
		FLASH->CR |= FLASH_CR_STRT;
		checkReg();
		while(checkBusy()){
			busyCount++;
		}
	}
	FLASH->CR &= ~FLASH_CR_SER;
	FLASH->CR &= ~FLASH_CR_SNB;
	checkReg();
}

void bankErase(int bankNum){

	int busyCount=0;

	if(!checkBusy()){

		checkReg();
		if(bankNum==1){
			FLASH->CR &= ~(FLASH_CR_MER);
			FLASH->CR |= FLASH_CR_MER;
		}
		else{
			FLASH->CR &= ~(FLASH_CR_MER1);
			FLASH->CR |= FLASH_CR_MER1;
		}
		checkReg();
		FLASH->CR &= ~(FLASH_CR_STRT);
		FLASH->CR |= FLASH_CR_STRT;
		checkReg();

		while(checkBusy()){
			busyCount++;
		}
	}
	FLASH->CR &= ~FLASH_CR_MER;
	FLASH->CR &= ~FLASH_CR_MER1;
	checkReg();
}

void massErase(){

	int busyCount=0;

	if(!checkBusy()){

		checkReg();
		FLASH->CR &= ~(FLASH_CR_MER);
		FLASH->CR |= FLASH_CR_MER;
		FLASH->CR &= ~(FLASH_CR_MER1);
		FLASH->CR |= FLASH_CR_MER1;
		checkReg();
		FLASH->CR &= ~(FLASH_CR_STRT);
		FLASH->CR |= FLASH_CR_STRT;
		checkReg();

		while(checkBusy()){
			busyCount++;
		}
	}
	FLASH->CR &= ~FLASH_CR_MER;
	FLASH->CR &= ~FLASH_CR_MER1;
	checkReg();
}

void flashProgram(int PSIZEsel,uint64_t value,uint32_t Address){
	int busyCount=0,error=0;
	WRITE_SIZE *write;

	write=((uint32_t *)(Address));

	if(!checkBusy()){
		checkReg();
		FLASH->CR &= ~(FLASH_CR_PSIZE);
		checkReg();
		FLASH->CR |= PSIZEsel << FLASH_CR_PSIZE_bit;
		checkReg();
		FLASH->CR &= ~(FLASH_CR_PG);
		FLASH->CR |= FLASH_CR_PG;
		checkReg();

		error=checkError();

		checkReg();
		switch(PSIZEsel){
		  case x8 :value &= 0xFF;break;
		  case x16:value &= 0xFFFF;break;
		  case x32:value &= 0xFFFFFFFF;break;
		  case x64:value &= 0xFFFFFFFFFFFFFFFF;break;
		}
		*write=value;
		error=checkError();

		while(checkBusy()){
			busyCount++;
		}
	}
}

int checkBusy(){
	return ((FLASH->SR>>16)&1);
}

int checkError(){
  int seqErr,parallelErr,alignErr,writeProtect,writeProtErr,OperationErr;
  
  checkReg();
  seqErr       = (FLASH->SR>>7)&1;
  parallelErr  = (FLASH->SR>>6)&1;
  alignErr     = (FLASH->SR>>5)&1;
  writeProtErr = (FLASH->SR>>4)&1;
  OperationErr = (FLASH->SR>>1)&1;
  
  if(seqErr!=0 || parallelErr!=0 || alignErr!=0 || writeProtErr!=0 || OperationErr!=0)
    return 1;
  else
    return 0;
}
  
void checkReg(){
	uint32_t checkSR,checkCR,checkOPTCR;
	checkSR		=FLASH->SR;
	checkCR		=FLASH->CR;
	checkOPTCR	=FLASH->OPTCR;
}

uint32_t checkLatency(){
	return FLASH->ACR & 15;
}



