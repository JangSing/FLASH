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

#define SR_EOP     (1<<0)
#define SR_OPERR   (1<<1)
#define SR_WRPERR  (1<<4)
#define SR_PGAERR  (1<<5)
#define SR_PGPERR  (1<<6)
#define SR_PGSERR  (1<<7)
#define SR_RDERR   (1<<8)
#define SR_BSY     (1<<16)

#define CR_PG      (1<<0)
#define CR_SER     (1<<1)
#define CR_MER     (1<<2)
#define CR_SNB0    (1<<3)
#define CR_SNB1    (1<<4)
#define CR_SNB2    (1<<5)
#define CR_SNB3    (1<<6)
#define CR_SNB4    (1<<7)
#define CR_PSIZE0  (1<<8)
#define CR_PSIZE1  (1<<9)
#define CR_STRT    (1<<16)
#define CR_EOPIE   (1<<24)
#define CR_ERRIE   (1<<25)



void unlockFlashControl();

int checkBusy();







#endif
