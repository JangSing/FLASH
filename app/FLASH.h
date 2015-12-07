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

#define FLASH_SR_EOP     (1<<0)
#define FLASH_SR_OPERR   (1<<1)
#define FLASH_SR_WRPERR  (1<<4)
#define FLASH_SR_PGAERR  (1<<5)
#define FLASH_SR_PGPERR  (1<<6)
#define FLASH_SR_PGSERR  (1<<7)
#define FLASH_SR_RDERR   (1<<8)
#define FLASH_SR_BSY     (1<<16)

#define FLASH_CR_PG      (1<<0)
#define FLASH_CR_SER     (1<<1)
#define FLASH_CR_MER     (1<<2)
#define FLASH_CR_SNB0    (1<<3)
#define FLASH_CR_SNB1    (1<<4)
#define FLASH_CR_SNB2    (1<<5)
#define FLASH_CR_SNB3    (1<<6)
#define FLASH_CR_SNB4    (1<<7)
#define FLASH_CR_PSIZE   (3<<8)
#define FLASH_CR_STRT    (1<<16)
#define FLASH_CR_EOPIE   (1<<24)
#define FLASH_CR_ERRIE   (1<<25)
#define FLASH_CR_LOCK    (1<<31)

#define x8      0
#define x16     1
#define x32     2
#define x64     3

void unlockFlashControl();
void flashLock();
void sectorErase();
void flashProgram(uint32_t PSIZEsel);
int checkBusy();
int checkError();
void checkSRnCR();





#endif
