#include "RCC.h"

void DMA2UnresetEnableClock(){
	RCC->RCC_AHB1RSTR &= ~ RCC_AHB1RSTR_DMA2RST; 	//Reseting
	RCC->RCC_AHB1ENR  &= ~RCC_AHB1ENR_DMA2EN;
	RCC->RCC_AHB1ENR  |= RCC_AHB1ENR_DMA2EN;		//Enable Clock

	uint32_t checkAHB1ENR = RCC->RCC_AHB1ENR ;
	uint32_t checkRCC_AHB1RSTR = RCC->RCC_AHB1RSTR;
}

uint32_t getSystemClock(){
	int divM, xN, divP, divAHB;
	int sysClock;
	int enbAHBPrescale = RCC->RCC_CFGR & 256;

	if(enbAHBPrescale == 0)
		divAHB = 1;
	else
		divAHB = 1 << (((RCC->RCC_CFGR >> 4) & 7) + 1);

	xN = (RCC->RCC_PLLCFGR >> 6) & 511;
	divM = (RCC->RCC_PLLCFGR & 63);
	divP = 1 << (((RCC->RCC_PLLCFGR >> 16) & 3) + 1);

	if(((RCC->RCC_CFGR & 0xC) >> 2) == 0)
		sysClock = INTERNAL_CLOCK / divAHB;
	else if(((RCC->RCC_CFGR & 0xC) >> 2) == 1)
		sysClock = CRYSTAL_CLOCK / divAHB;
	else {
		if(((RCC->RCC_PLLCFGR >> 22) & 1) == 0)
			sysClock = (INTERNAL_CLOCK * xN) / (divM * divP * divAHB);
		else
			sysClock = (CRYSTAL_CLOCK) / (divM * divP * divAHB) * xN;
	}
	return sysClock;
}
