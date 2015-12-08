#include "FLASH.h"
#include <stdint.h>

int main(void)
{
	int error=0,guard=0;
	int latency=checkLatency();
	uint32_t HCLCK=getSystemClock();
	uint64_t *readAdd;


	while(1){
		unlockFlashControl();
		error=checkError();
		readAdd=((uint64_t *)TARGET_ADD);
		if(guard){
			sectorErase(SECTOR1);
			guard=0;
		}
		readAdd=((uint64_t *)TARGET_ADD);
		if(guard){
			bankErase(1);
			guard=0;
		}
		readAdd=((uint64_t *)TARGET_ADD);
		if(guard){
			flashProgram(x32,0x0101010101010101);
			guard=0;
		}

		flashLock();
		readAdd=((uint64_t *)0x08100000);

	}



}
