#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"

#define LED 5
#define size 4

int main(void)
{
	uint8_t x, password[size] = {0,1,0,5}, userInput[size], count = 0, y;
	int8_t keypad[12] = "123456789*0#";
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	keypadConfigure();
	
	//Configure LED pin
	PORTB_set_pin_dir(LED,PORT_DIR_OUT);
	PORTB_set_pin_level(LED,0);
	
	while(1){
		PORTB_set_pin_level(LED,1);
		printf("Enter 4-digit PIN to open door\n");
		
		//read 4-digit pin
		for (x=0;x<size; x++)
		{
			userInput[x]= keypadScan();
			printf("*");
			if (password[x] == userInput[x])
			{
				count++;
			}
		}
		if (count == size){
			printf("Door Opening");
			PORTB_set_pin_level(LED,0);
			_delay_ms(2000);
			PORTB_set_pin_level(LED,1);
		}
		else{
			printf("Incorrect");
			for (y=0; y<2; y++)
			{
				PORTB_toggle_pin_level(LED);
				_delay_ms(500);
			}
			
		}
	}
}
