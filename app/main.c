#include "FLASH.h"
#include <stdint.h>

int main(void)
{
	int i,error;
	uint32_t checkCR;
	uint32_t *readAdd;
	uint32_t guard=0,firstTime=1;

	while(1){
		if(firstTime){
			unlockFlashControl();
			firstTime=0;
		}
		error=checkError();
		readAdd=((uint32_t *)0x08100000);
		if(guard){
			sectorErase();
			guard=0;
		}
		readAdd=((uint32_t *)0x08100000);
		if(guard){
			flashProgram();
			guard=0;
		}
		readAdd=((uint32_t *)0x08100000);
	}



}
