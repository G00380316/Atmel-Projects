#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7

int main(void)
{
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	//Configure LED pin

	
	while(1){
		while(PORTB_get_pin_level(SW)==1){
			
		}
		printf("\n\nSwitch pressed");
		while(PORTB_get_pin_level(SW) == 0){
		}
		}
	
}
