#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7

int main(void)
{
	uint8_t display[10] = {0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
	int8_t count = 1;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	//Configure PB0 to PB6 as outputs
	DDRB = 0x7F;
    PORTB= display[count];
	
	while (1) {
		while(PORTB_get_pin_level(SW)==0){
			//count up
			count++;
			if (count == 7)
			{
				count = 1;
			}
		}
		PORTB = display[count];
	}	
}
