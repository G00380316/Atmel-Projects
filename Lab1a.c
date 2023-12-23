#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define BUTTON 7
#define LED 5

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	PORTB_set_pin_level(LED, 0);
	
	printf("First ATmega Project\r\n");

	/* Replace with your application code */
	while (1) {
		//Test the switch
		if (PORTB_get_pin_level(BUTTON)==0){//Switch pressed
			PORTB_toggle_pin_level(LED);    //LED on and off 
			_delay_ms(100);
			//PORTB_set_pin_level(LED,1); //LED on
		}
		else
		{
			PORTB_toggle_pin_level(LED);
			_delay_ms(500);
			//PORTB_set_pin_level(LED,0); //LED off
		}
		
	}
}
