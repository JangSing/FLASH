#include "DMA.h"
#include "RCC.h"

void checkDMAReg(){
	uint32_t checkHISR= DMA2->HISR;
	uint32_t chcekS7CR= DMA2->S7.CR;
}


void configDMA2s7CR(int direction,int PSIZE,int MSIZE,int PL,int CHSEL) {  // stream 7  channel 0
	checkDMAReg();

	DMA2->S7.CR &= ~DMA_SxCR_EN;			//Stream Disable

	DMA2->S7.CR |= 0x0000061e;

	DMA2->S7.CR &= ~DMA_SxCR_DIR;
	DMA2->S7.CR |= direction << DMA_SxCR_DIR_bit;

	DMA2->S7.CR &= ~DMA_SxCR_PSIZE;
	DMA2->S7.CR |= PSIZE << DMA_SxCR_PSIZE_bit;
  
	DMA2->S7.CR &= ~DMA_SxCR_MSIZE;
	DMA2->S7.CR |= MSIZE << DMA_SxCR_MSIZE_bit;
  
	DMA2->S7.CR &= ~DMA_SxCR_PL;
	DMA2->S7.CR |= PL << DMA_SxCR_PL_bit;
  
	DMA2->S7.CR &= ~DMA_SxCR_CHSEL;
	DMA2->S7.CR |= CHSEL << DMA_SxCR_CHSEL_bit;

	checkDMAReg();
}

void DMA_memcpy( uint32_t *pDstAddr, uint32_t *pSrcAddr, int uSize ){
	DMA2->S7.PAR =  (uint32_t)pSrcAddr;		// source address
	DMA2->S7.M0AR = (uint32_t)pDstAddr; 	// destination address
    DMA2->S7.NDTR = uSize;     				// Number of data items to transfer
}

void enableDMA(){
	DMA2->S7.CR &= ~1;
	DMA2->S7.CR |= 1;
	checkDMAReg();
}

void clearDMAHighIntrrFlag(){
	DMA2->HIFCR = (uint32_t)0x0f400000;
	checkDMAReg();
}
