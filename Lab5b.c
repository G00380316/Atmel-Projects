#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"

#define LED 5

int main(void)
{
	uint8_t x, password[3] = {0,1,0}, userInput[3], count = 0;
	//int8_t keypad[12] = "123456789*0#";
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	keypadConfigure();
	
	//Configure LED pin
	PORTB_set_pin_dir(LED,PORT_DIR_OUT);
	PORTB_set_pin_level(LED,0);
	
	while(1){
		PORTB_set_pin_level(LED,1);
		printf("Enter 3-digit PIN to open door\n");
		
		//read 3-digit pin
		count = 0;
		for (x=0;x<3; x++)
		{
			userInput[x]= keypadScan();
			printf("*");
			if (userInput[x] == password[x])
			{
				count++;
			}
		}
		printf("Count: %d\n", count);
		if (count == 3){
			printf("\nDoor Open\n");
			PORTB_set_pin_level(LED,0);
			_delay_ms(2000);
		}
		else{
			printf("\nIncorrect\n");
			for (x=0; x<6; x++)
			{
				PORTB_toggle_pin_level(LED);
				_delay_ms(300);
			}
			
		}
	}
}
