#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7
#define LED 5

int main(void)
{
	uint8_t ch = '0';
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/*Configure LED pin as output*/
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	PORTB_set_pin_level(LED, 0);


	/* Printf menu*/
	printf("O\tTurn Led Off\nL\tTurn LED On\nF\tFlash LED at 5 Hz\nAll other characters should be ignored");
	
	while (1) {
		if (USART_0_is_rx_ready())
		{//has a character recieved
	     ch = USART_0_read();
		 printf("\n\nCharacter Recieved: %d\n", ch);
		}
		
	}
	
}
