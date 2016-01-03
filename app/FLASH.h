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

#define FLASH_BASE_ADDRESS	0x40023C00
#define FLASH 				((FLASH_TypeDef*)FLASH_BASE_ADDRESS)

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

#define FLASH_OPTCR_SPRMOD    (1<<31)
#define FLASH_OPTCR_DB1M      (1<<30)
#define FLASH_OPTCR_nWRP      (0xFFF<<16)
#define FLASH_OPTCR_RDP       (0xFF<<8)
#define FLASH_OPTCR_USER      (7<<5)
#define FLASH_OPTCR_BFB2      (1<<4)
#define FLASH_OPTCR_BOR_LEV   (3<<2)
#define FLASH_OPTCR_OPTSTRT   (1<<1)
#define FLASH_OPTCR_OPTLOCK   (1<<0)

#define x8      0
#define x16     1
#define x32     2
#define x64     3

#define WRITE_SIZE	uint8_t
#define TARGET_ADD	((WRITE_SIZE *)0x08104000)

//Sector in bank 1
#define SECTOR0     0
#define SECTOR1     1
#define SECTOR2     2
#define SECTOR3     3
#define SECTOR4     4
#define SECTOR5     5
#define SECTOR6     6
#define SECTOR7     7
#define SECTOR8     8
#define SECTOR9     9
#define SECTOR10    10
#define SECTOR11    11

//Sector in bank 2
#define SECTOR12    16
#define SECTOR13    17
#define SECTOR14    18
#define SECTOR15    19
#define SECTOR16    20
#define SECTOR17    21
#define SECTOR18    22
#define SECTOR19    23
#define SECTOR20    24
#define SECTOR21    25
#define SECTOR22    26
#define SECTOR23    27

#define BANK1	1
#define BANK2	2

int checkBusy();
int checkFlashError();
void checkFlashReg();
uint32_t checkLatency();

void unlockFlashCR();
void flashLock();

void sectorErase(uint32_t sectorNum);
void bankErase(int bankNum);
void massErase();

void flashProgramEn();
void flashProgramConfig(int PSIZEsel);
void flashProgram(int PSIZEsel,uint64_t value,uint32_t *Address);
void flashProgramDisable();

void unlockFlashOptionByte();
void flashOptionByteLock();


#endif
