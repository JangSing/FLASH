#include "FLASH.h"

void unlockFlashControl(){
  FLASH->KEYR =0x45670123;
  FLASH->KEYR =0xCDEF89AB;
}

void flashLock(){
	FLASH->CR |= FLASH_CR_LOCK;
}

void sectorErase(uint32_t sectorNum){

	int busyCount=0;
	uint64_t *readAdd;
  
	if(!checkBusy()){

		checkSRnCR();
		FLASH->CR &= ~(FLASH_CR_SER);
		FLASH->CR &= ~(FLASH_CR_SNB);
		FLASH->CR &= ~(FLASH_CR_STRT);
		checkSRnCR();
		FLASH->CR |= FLASH_CR_SER;
		FLASH->CR |= sectorNum << FLASH_CR_SNB_bit;
		FLASH->CR |= FLASH_CR_STRT;
		checkSRnCR();

		while(checkBusy()){
			readAdd=((uint64_t *)(0x08100000));
			busyCount++;
		}
	}
	FLASH->CR &= ~FLASH_CR_SER;
	FLASH->CR &= ~FLASH_CR_SNB;
	checkSRnCR();
}

void bankErase(int bankNum){

	int busyCount=0;

	if(!checkBusy()){

		checkSRnCR();
		if(bankNum==1){
			FLASH->CR &= ~(FLASH_CR_MER);
			FLASH->CR |= FLASH_CR_MER;
		}
		else{
			FLASH->CR &= ~(FLASH_CR_MER1);
			FLASH->CR |= FLASH_CR_MER1;
		}
		checkSRnCR();
		FLASH->CR &= ~(FLASH_CR_STRT);
		FLASH->CR |= FLASH_CR_STRT;
		checkSRnCR();

		while(checkBusy()){
			busyCount++;
		}
	}
	FLASH->CR &= ~FLASH_CR_MER;
	FLASH->CR &= ~FLASH_CR_MER1;
	checkSRnCR();
}

void flashProgram(int PSIZEsel,uint64_t value){
	int busyCount=0,error=0;
	WRITE_SIZE *write;
	uint64_t *readAdd;

	write=((WRITE_SIZE *)(0x08100000));

	if(!checkBusy()){

		checkSRnCR();
		FLASH->CR &= ~(FLASH_CR_PSIZE);
		checkSRnCR();
		FLASH->CR |= PSIZEsel << FLASH_CR_PSIZE_bit;
		checkSRnCR();
		FLASH->CR &= ~(FLASH_CR_PG);
		FLASH->CR |= FLASH_CR_PG;
		checkSRnCR();

		error=checkError();

		checkSRnCR();

		switch(PSIZEsel){
		  case x8 :value &= 0xFF;break;
		  case x16:value &= 0xFFFF;break;
		  case x32:value &= 0xFFFFFFFF;break;
		  case x64:value &= 0xFFFFFFFFFFFFFFFF;break;
		}
		*write=value;
		error=checkError();

		while(checkBusy()){
			readAdd=((uint64_t *)(0x08100000));
			busyCount++;
		}
		readAdd=((uint64_t *)(0x08100000));
	}


}

int checkBusy(){
	return ((FLASH->SR>>16)&1);
}

int checkError(){
  int seqErr,parallelErr,alignErr,writeProtect,writeProtErr,OperationErr;
  
  checkSRnCR();
  seqErr       = (FLASH->SR>>7)&1;
  parallelErr  = (FLASH->SR>>6)&1;
  alignErr     = (FLASH->SR>>5)&1;
  writeProtErr = (FLASH->SR>>4)&1;
  OperationErr = (FLASH->SR>>1)&1;
  
  if(seqErr!=0 || parallelErr!=0 || alignErr!=0 || writeProtErr || OperationErr)
    return 1;
  else
    return 0;
}
  
void checkSRnCR(){
	uint32_t checkSR,checkCR;
	checkSR=FLASH->SR;
	checkCR=FLASH->CR;
}

uint32_t checkLatency(){
	return FLASH->ACR & 15;
}

uint32_t getSystemClock(){
	int divM, xN, divP, divAHB;
	int sysClock;
	int enbAHBPrescale = RCC_reg->RCC_CFGR & 256;

	if(enbAHBPrescale == 0)
		divAHB = 1;
	else
		divAHB = 1 << (((RCC_reg->RCC_CFGR >> 4) & 7) + 1);

	xN = (RCC_reg->RCC_PLLCFGR >> 6) & 511;
	divM = (RCC_reg->RCC_PLLCFGR & 63);
	divP = 1 << (((RCC_reg->RCC_PLLCFGR >> 16) & 3) + 1);

	if(((RCC_reg->RCC_CFGR & 0xC) >> 2) == 0)
		sysClock = INTERNAL_CLOCK / divAHB;
	else if(((RCC_reg->RCC_CFGR & 0xC) >> 2) == 1)
		sysClock = CRYSTAL_CLOCK / divAHB;
	else {
		if(((RCC_reg->RCC_PLLCFGR >> 22) & 1) == 0)
			sysClock = (INTERNAL_CLOCK * xN) / (divM * divP * divAHB);
		else
			sysClock = (CRYSTAL_CLOCK) / (divM * divP * divAHB) * xN;
	}

	return sysClock;
}

