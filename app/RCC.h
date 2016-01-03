#ifndef	__RCC_H__
#define	__RCC_H__

#include <stdint.h>

typedef struct RCC_t RCC_TypeDef;
struct RCC_t{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	volatile uint32_t RCC_AHB3RSTR;
	volatile uint32_t RESERVE0[1];
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RESERVE1[2];
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	volatile uint32_t RCC_AHB3ENR;
	volatile uint32_t RESERVE2[1];
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RESERVE3[2];
	volatile uint32_t RCC_AHB1LPENR;
	volatile uint32_t RCC_AHB2LPENR;
	volatile uint32_t RCC_AHB3LPENR;
	volatile uint32_t RESERVE4[1];
	volatile uint32_t RCC_APB1LPENR;
	volatile uint32_t RCC_APB2LPENR;
	volatile uint32_t RESERVE5[2];
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	volatile uint32_t RESERVE6[2];
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	volatile uint32_t RCC_PLLSAICFGR;
	volatile uint32_t RCC_DCKCFGR;
};

#define RCC	((RCC_TypeDef*)0x40023800)

#define RCC_AHB1RSTR_DMA2RST	(1 << 22)
#define RCC_AHB1ENR_DMA2EN		(1 << 22)

#define INTERNAL_CLOCK	  16000000
#define CRYSTAL_CLOCK	  8000000

void DMA2UnresetEnableClock();
uint32_t getSystemClock();

#endif	//__RCC_H__
