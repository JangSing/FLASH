#include "FLASH.h"

void unlockFlashControl(){
  FLASH->KEYR =0x45670123;
  FLASH->KEYR =0xCDEF89AB;
}

int checkBusy(){
	return ((FLASH->SR<<16)&1);
}

int checkError(){
  int seqErr,parallelErr,alignErr;
  uint32_t checkSR,checkCR;
  checkSR=FLASH->SR;
  checkCR=FLASH->CR;
  seqErr      = (FLASH->SR>>7)&1;
  parallelErr = (FLASH->SR>>6)&1;
  alignErr    = (FLASH->SR>>5)&1;
  
  if(seqErr!=0 || parallelErr!=0 || alignErr!=0)
    return 1;
  else
    return 0;
}
  
