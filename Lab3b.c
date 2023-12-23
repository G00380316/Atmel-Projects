#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7
#define LED 5

int main(void)
{
	uint8_t ch = 'O';
	uint8_t temp;
	uint8_t old = 1, new1 = 1;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/*Configure LED pin as output*/
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	PORTB_set_pin_level(LED, 0);


	/* Printf menu*/
	printf("O\tTurn Led Off\nL\tTurn LED On\nF\tFlash LED at 5 Hz\nAll other characters should be ignored\n\n");
	
	while (1){ 
		if (USART_0_is_rx_ready()){//has a character received
	     temp = USART_0_read();
		 printf("\nCharacter Received: %c", temp);
		
		//checking if the value inputed is correct if not error message will be printed
		if (temp == 'O' ||temp == 'L' ||temp == 'F'){
			ch = temp;
		}
		else{
			printf("\nInvalid option, Try again\n");}
		
		
		
		
		//control LED
		switch (ch)
		{
			case 'O':
			case 'o': PORTB_set_pin_level(LED,0);
			break;
			case 'L':
			case 'l':PORTB_set_pin_level(LED,1);
			break;
			case 'F':
			case 'f':PORTB_toggle_pin_level(LED);_delay_ms(100);
			break;
			default: ch = 'O';
			break;
		}
	
	//check if the switch has change state
	new1 = PORTB_get_pin_level(SW);
	if (new1 != old){// switch pin state
	if (new1 == 0)
	{
		printf("\nSwitch Pressed\n");
	}
	else{
		printf("\nSwitch Released\n");
	old = new1;}
	}
	 }
	}
}

	
		
	
