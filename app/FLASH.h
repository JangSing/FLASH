#ifndef FLASH_H
#define FLASH_H
#include <stdint.h>

typedef struct FLASH_TypeDef_t FLASH_TypeDef;
struct FLASH_TypeDef_t
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t OPTCR;
  volatile uint32_t OPTCR1;
};

#define FLASH ((FLASH_TypeDef*)(0x40023C00))

typedef struct RCC_Type RCC_t;
struct RCC_Type{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	volatile uint32_t RCC_AHB3RSTR;
	volatile uint32_t RESERVE_0;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RESERVE_1;
	volatile uint32_t RESERVE_2;
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	volatile uint32_t RCC_AHB3ENR;
	volatile uint32_t RESERVE_3;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RESERVE_4;
	volatile uint32_t RESERVE_5;
	volatile uint32_t RCC_AHB1LPENR;
	volatile uint32_t RCC_AHB2LPENR;
	volatile uint32_t RCC_AHB3LPENR;
	volatile uint32_t RESERVE_6;
	volatile uint32_t RCC_APB1LPENR;
	volatile uint32_t RCC_APB2LPENR;
	volatile uint32_t RESERVE_7;
	volatile uint32_t RESERVE_8;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	volatile uint32_t RESERVE_9;
	volatile uint32_t RESERVE_10;
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	volatile uint32_t RCC_PLLSAICFGR;
	volatile uint32_t RCC_DCKCFGR;
};

#define RCC_reg	((RCC_t*)0x40023800)

#define FLASH_ACR_LATENCY   (15<<0)
#define FLASH_ACR_PRFTEN    (1<<8)
#define FLASH_ACR_ICEN      (1<<9)
#define FLASH_ACR_DCEN      (1<<10)
#define FLASH_ACR_ICRST     (1<<11)
#define FLASH_ACR_DCRST     (1<<12)

#define FLASH_SR_EOP     (1<<0)
#define FLASH_SR_OPERR   (1<<1)
#define FLASH_SR_WRPERR  (1<<4)
#define FLASH_SR_PGAERR  (1<<5)
#define FLASH_SR_PGPERR  (1<<6)
#define FLASH_SR_PGSERR  (1<<7)
#define FLASH_SR_RDERR   (1<<8)
#define FLASH_SR_BSY     (1<<16)

#define FLASH_CR_SNB_bit	3
#define FLASH_CR_PSIZE_bit	8

#define FLASH_CR_PG      (1<<0)
#define FLASH_CR_SER     (1<<1)
#define FLASH_CR_MER     (1<<2)
#define FLASH_CR_SNB     (31<<3)
#define FLASH_CR_PSIZE   (3<<8)
#define FLASH_CR_MER1    (1<<15)
#define FLASH_CR_STRT    (1<<16)
#define FLASH_CR_EOPIE   (1<<24)
#define FLASH_CR_ERRIE   (1<<25)
#define FLASH_CR_LOCK    (1<<31)

#define x8      0
#define x16     1
#define x32     2
#define x64     3

#define WRITE_SIZE	uint32_t

#define SECTOR0   0
#define SECTOR1   1
#define SECTOR2   2
#define SECTOR3   3
#define SECTOR4   4
#define SECTOR5   5
#define SECTOR6   6
#define SECTOR7   7
#define SECTOR8   8
#define SECTOR9   9
#define SECTOR10 10
#define SECTOR11 11
#define SECTOR12 16
#define SECTOR13 17
#define SECTOR14 18
#define SECTOR15 19
#define SECTOR16 20
#define SECTOR17 21
#define SECTOR18 22
#define SECTOR19 23
#define SECTOR20 24
#define SECTOR21 25
#define SECTOR22 26
#define SECTOR23 27

void unlockFlashControl();
void flashLock();
void sectorErase(uint32_t sectorNum);
void bankErase(int bankNum);
void flashProgram(int PSIZEsel,uint64_t value);
int checkBusy();
int checkError();
void checkSRnCR();
uint32_t checkLatency();
uint32_t getSystemClock();

#define INTERNAL_CLOCK	  16000000
#define CRYSTAL_CLOCK	   8000000

#endif
