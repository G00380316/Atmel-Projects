#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7
#define LED 5

int main(void)
{
	uint8_t reactline=0;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	//Configure LED pin
    PORTB_set_pin_dir(LED,PORT_DIR_OUT);
	PORTB_set_pin_level(LED,0);
	
	while(1){
		PORTB_set_pin_level(LED,0);
		reactline = 0;
		printf("Press the switch to start the game");
		while(PORTB_get_pin_level(SW)==1){	
		}
		while(PORTB_get_pin_level(SW)==0){
		}
		printf("\nPress the switch once the LED lights(Don't cheat)");
		
		if(PORTB_get_pin_level(SW)==1)
		{
			_delay_ms(2000);
			PORTB_set_pin_level(LED,1);
			while (PORTB_get_pin_level(SW)==1)
			{
				_delay_ms(1);
				reactline++;
			}
			printf("\nYour reaction time: %d",reactline);
			printf("\n\n");
		}
		else{
			printf("\nYou are cheating\n\n");
		}
		while (PORTB_get_pin_level(SW)==0){
		}
		
		}
	
}
