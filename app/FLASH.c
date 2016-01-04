#include "FLASH.h"

int checkBusy(){
	return ((FLASH->SR>>16)&1);
}

int checkFlashError(){
  int seqErr,parallelErr,alignErr,writeProtErr,OperationErr;

  checkFlashReg();
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

void checkFlashReg(){
	uint32_t checkSR 	= FLASH->SR;
	uint32_t checkCR 	= FLASH->CR;
	uint32_t checkOPTCR	= FLASH->OPTCR;
}

uint32_t checkLatency(){
	return FLASH->ACR & 15;
}

void unlockFlashCR(){
	FLASH->KEYR =0x45670123;
	FLASH->KEYR =0xCDEF89AB;
}

void flashLock(){
	FLASH->CR |= FLASH_CR_LOCK;
}

void sectorErase(uint32_t sectorNum){
	while(checkBusy()){}
	checkFlashReg();
	FLASH->CR &= ~FLASH_CR_SER;
	FLASH->CR &= ~FLASH_CR_SNB;
	FLASH->CR &= ~FLASH_CR_STRT;
	FLASH->CR |= FLASH_CR_SER;
	FLASH->CR |= sectorNum << FLASH_CR_SNB_bit;
	FLASH->CR |= FLASH_CR_STRT;
	checkFlashReg();
	while(checkBusy()){}
	FLASH->CR &= ~FLASH_CR_SER;
	FLASH->CR &= ~FLASH_CR_SNB;
	checkFlashReg();
}

void bankErase(int bankNum){
	while(checkBusy()){}
	checkFlashReg();
	if(bankNum==1){
		FLASH->CR &= ~FLASH_CR_MER;
		FLASH->CR |= FLASH_CR_MER;
	}
	else{
		FLASH->CR &= ~FLASH_CR_MER1;
		FLASH->CR |= FLASH_CR_MER1;
	}
	checkFlashReg();
	FLASH->CR &= ~FLASH_CR_STRT;
	FLASH->CR |= FLASH_CR_STRT;
	checkFlashReg();
	while(checkBusy()){}
	FLASH->CR &= ~FLASH_CR_MER;
	FLASH->CR &= ~FLASH_CR_MER1;
	checkFlashReg();
}

void massErase(){

	while(checkBusy()){}
	checkFlashReg();
	FLASH->CR &= ~FLASH_CR_MER;
	FLASH->CR &= ~FLASH_CR_MER1;
	FLASH->CR |= FLASH_CR_MER;
	FLASH->CR |= FLASH_CR_MER1;
	checkFlashReg();
	FLASH->CR &= ~FLASH_CR_STRT;
	FLASH->CR |= FLASH_CR_STRT;
	checkFlashReg();
	while(checkBusy()){}
	FLASH->CR &= ~FLASH_CR_MER;
	FLASH->CR &= ~FLASH_CR_MER1;
	checkFlashReg();
}

void flashProgramEn(){
	FLASH->CR &= ~FLASH_CR_PG;
	FLASH->CR |= FLASH_CR_PG;
	checkFlashReg();
}

void flashProgramConfig(int PSIZEsel){
	FLASH->CR &= ~FLASH_CR_PG;
	FLASH->CR &= ~FLASH_CR_PSIZE;
	FLASH->CR |= PSIZEsel << FLASH_CR_PSIZE_bit;
	checkFlashReg();
}

void flashProgram(int PSIZEsel,uint64_t value,uint32_t *Address){
	int error=0;
	WRITE_SIZE *write;

	write=((uint32_t *)(Address));

	while(checkBusy()){}
	checkFlashReg();
	flashProgramConfig(PSIZEsel);
	flashProgramEn();
	error=checkFlashError();
	checkFlashReg();
	switch(PSIZEsel){
	  case x8 :value &= 0xFF;break;
	  case x16:value &= 0xFFFF;break;
	  case x32:value &= 0xFFFFFFFF;break;
	  case x64:value &= 0xFFFFFFFFFFFFFFFF;break;
	}
	*write=value;
	while(checkBusy()){}
	error=checkFlashError();
	flashProgramDisable();
}

void flashProgramDisable(){
	FLASH->CR &= ~FLASH_CR_PG;
}

void unlockFlashOptionByte(){
	FLASH->OPTKEYR =0x08192A3B;
	FLASH->OPTKEYR =0x4C5D6E7F;
}

void flashOptionByteLock(){
	FLASH->OPTCR|= FLASH_OPTCR_OPTLOCK;
}




