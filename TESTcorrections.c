//Name: Enoch Abiodun
//Student ID: G00380316
//Date: 30/10/2020

#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"

#define SW 7
#define LED 5 

int main(void)
{
	uint8_t count = 0;
	uint8_t temp;
	uint8_t sign = '+';
	uint8_t x;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	//Configure LED as an Output
	PORTB_set_pin_dir(LED, PORT_DIR_OUT);
	PORTB_set_pin_level(LED,0);
	
	printf("LED Frequency control\n0: LED OFF\n1: 1Hz\n2: 2Hz\n3: 4Hz\nPress + or - key to change LED Frequency");
	
	while (1) {
		if (USART_0_is_rx_ready()){
			temp = USART_0_read();
			if (temp == '+')
			{
				if (count<3)
				{
					count++;
				}
				else{
					printf("Already at max frequency setting\n");
				}
			}
	}
	else if (temp=='-')
	{
		if (count > 0)
		{
			
		}
	}
		
	
	
	switch(count)
	{
		case 0: PORTB_set_pin_level(LED,0);
		        printf("LED off\n");
		break;
		case 1: printf("Frequency set at 1Hz\n");
		        PORTB_toggle_pin_level(LED);
		        _delay_ms(1000);
		break;
		case 2: printf("Frequency set at 2Hz\n");
		        PORTB_toggle_pin_level(LED);
		        _delay_ms(500);
		break;
		case 3: printf("Frequency set at 4Hz\n");
		        PORTB_toggle_pin_level(LED);
		        _delay_ms(250);
		break;
		default:count=0;
		break;
	}
}
}