#ifndef	__DMA_H__
#define	__DMA_H__
#include <stdint.h>

typedef struct DMA_Type DMA_reg;
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t NDTR;
	volatile uint32_t PAR;
	volatile uint32_t M0AR;
	volatile uint32_t M1AR;
	volatile uint32_t FCR;
}Stream_t;

struct DMA_Type{
	volatile uint32_t LISR;
	volatile uint32_t HISR;
	volatile uint32_t LIFCR;
	volatile uint32_t HIFCR;
	Stream_t	S0;
	Stream_t	S1;
	Stream_t	S2;
	Stream_t	S3;
	Stream_t	S4;
	Stream_t	S5;
	Stream_t	S6;
	Stream_t	S7;
};

#define DMA2   ((DMA_reg*)0x40026400)

#define DMA_SxCR_EN       (1<<0)
#define DMA_SxCR_DMEIE    (1<<1)
#define DMA_SxCR_TEIE     (1<<2)
#define DMA_SxCR_HTIE     (1<<3)
#define DMA_SxCR_TCIE     (1<<4)
#define DMA_SxCR_PFCTRL   (1<<5)
#define DMA_SxCR_DIR      (3<<6)
#define DMA_SxCR_CIRC     (1<<8)
#define DMA_SxCR_PINC     (1<<9)
#define DMA_SxCR_MINC     (1<<10)
#define DMA_SxCR_PSIZE    (3<<11)
#define DMA_SxCR_MSIZE    (3<<13)
#define DMA_SxCR_PINCOS   (1<<15)
#define DMA_SxCR_PL       (3<<16)
#define DMA_SxCR_DBM      (3<<18)
#define DMA_SxCR_CT       (3<<19)
#define DMA_SxCR_PBURST   (3<<21)
#define DMA_SxCR_MBURST   (3<<23)
#define DMA_SxCR_CHSEL    (7<<25)

#define DMA_SxCR_DIR_bit      6     
#define DMA_SxCR_PSIZE_bit    11
#define DMA_SxCR_MSIZE_bit    13
#define DMA_SxCR_PL_bit       16
#define DMA_SxCR_CHSEL_bit    25

#define PeriToMem         0
#define MemToPeri         1
#define MemToMem          2   

#define LowPrio           0
#define MediumPrio        1
#define HighPrio          2
#define VeryHighPrio      3

#define CHANNEL0          0
#define CHANNEL1          1
#define CHANNEL2          2
#define CHANNEL3          3
#define CHANNEL4          4
#define CHANNEL5          5
#define CHANNEL6          6
#define CHANNEL7          7

void checkDMAReg();
void configDMA2s7CR(int direction,int PSIZE,int MSIZE,int PL,int CHSEL);
void DMA_memcpy( uint32_t *pDstAddr, uint32_t *pSrcAddr, int uSize );
void enableDMA();
void clearDMAHighIntrrFlag();

#endif	//__DMA_H__
