#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

int main(void)
{
	uint8_t display[10] = {0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};//0,1,2,3,4,5,6,7,8,9 in binary(hexa-deximal)
	uint8_t count = 0;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	//Configure PB0 to PB6 as outputs
	DDRB = 0x7F;


	/* Printf menu*/
	
	while (1) {
		PORTB= display[count];
		_delay_ms(1000);
		count++;
		if(count==10){
			count=0;
		      }
	}
		
	
}
