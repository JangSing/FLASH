#include "DMA.h"
#include "RCC.h"


void configDMA2s7CR(int direction,int PSIZE,int MSIZE,int PL,int CHSEL) {  // stream 7  channel 0

	DMA2->S7.CR &= ~DMA_SxCR_EN;			//Stream Disable
  
	DMA2->S7.CR &= ~DMA_SxCR_DMEIE;
	DMA2->S7.CR |= DMA_SxCR_DMEIE;
  
	DMA2->S7.CR &= ~DMA_SxCR_TEIE;
	DMA2->S7.CR |= DMA_SxCR_TEIE;
  
	DMA2->S7.CR &= ~DMA_SxCR_HTIE;
	DMA2->S7.CR |= DMA_SxCR_HTIE;
  
	DMA2->S7.CR &= ~DMA_SxCR_TCIE;
	DMA2->S7.CR |= DMA_SxCR_TCIE;
  
	DMA2->S7.CR &= ~DMA_SxCR_DIR;
	DMA2->S7.CR |= direction << DMA_SxCR_DIR_bit;

	DMA2->S7.CR &= ~DMA_SxCR_PINC;
	DMA2->S7.CR |= DMA_SxCR_PINC;

	DMA2->S7.CR &= ~DMA_SxCR_MINC;
	DMA2->S7.CR |= DMA_SxCR_MINC;
  
	DMA2->S7.CR &= ~DMA_SxCR_PSIZE;
	DMA2->S7.CR |= PSIZE << DMA_SxCR_PSIZE_bit;
  
	DMA2->S7.CR &= ~DMA_SxCR_MSIZE;
	DMA2->S7.CR |= MSIZE << DMA_SxCR_MSIZE_bit;
  
	DMA2->S7.CR &= ~DMA_SxCR_PL;
	DMA2->S7.CR |= PL << DMA_SxCR_PL_bit;
  
	DMA2->S7.CR &= ~DMA_SxCR_CHSEL;
	DMA2->S7.CR |= CHSEL << DMA_SxCR_CHSEL_bit;

}

void DMA_memcpy8( uint32_t *pDstAddr, uint32_t *pSrcAddr, unsigned int uSize ){
    														/* As per page 233 this is how to configure a stream */
	uint32_t checkS7CR;
	while( ( DMA2->S7.CR & 1 ) == 1 ){
         DMA2->S7.CR &= ~1;  					// 1. If stream is enabled, disable it
    }
	DMA2->S7.PAR =  (uint32_t)pSrcAddr;					/* source address */
	DMA2->S7.M0AR = (uint32_t)pDstAddr; 					/* destination address */
    DMA2->S7.NDTR = uSize;     							// Number of data items to transfer
    checkS7CR = DMA2->S7.CR;
}

void enableDMA(){
	uint32_t checkS7CR;
	DMA2->S7.CR &= ~1;
	DMA2->S7.CR |= 1;     						// Stream Enable
	checkS7CR = DMA2->S7.CR;
}
