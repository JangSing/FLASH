#include "FLASH.h"
#include <stdint.h>

int main(void)
{
	int i=0,error=0;
	uint32_t checkCR;
	uint32_t *readAdd;
	uint32_t guard=0,firstTime=1;

	while(1){
		unlockFlashControl();
		error=checkError();
		readAdd=((uint32_t *)0x08100000);
		if(guard){
			sectorErase();
			guard=0;
		}
		readAdd=((uint32_t *)0x08100000);
		if(guard){
			flashProgram(x32);
			guard=0;
		}
		flashLock();
		readAdd=((uint32_t *)0x08100000);

	}



}
