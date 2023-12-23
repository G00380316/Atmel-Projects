#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7
#define LED 5

int main(void)
{
	uint8_t count=0;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	//Configure LED pin
    PORTB_set_pin_dir(LED,PORT_DIR_OUT);
	PORTB_set_pin_level(LED,0);
	
	while(1){
		
		while(PORTB_get_pin_level(SW)==1){
			switch(count)
			{
				case 0: PORTB_set_pin_level(LED,0);
				break;
				case 1: PORTB_set_pin_level(LED,1);
				break;
				case 2: PORTB_toggle_pin_level(LED);_delay_ms(500);
				break;
				case 3: PORTB_toggle_pin_level(LED);_delay_ms(100);
				break;
				default: count = 0;
				break;
			}
		}
		printf("Switch pressed\n");
		count++;
		if (count == 4)
		{
			count = 0;
		}
		while(PORTB_get_pin_level(SW) == 0){
			
		}
		}
	
}
