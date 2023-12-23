#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"

#define LED 5

int main(void)
{
	uint8_t x, password[3] = {1,2,3}, userInput[3], count = 0,lockcount = 0;//234
	//int8_t keypad[12] = "123456789*0#";
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	keypadConfigure();
	lcd_init(LCD_DISP_ON_CURSOR);
	
	//Configure LED pin
	PORTB_set_pin_dir(LED,PORT_DIR_OUT);
	PORTB_set_pin_level(LED,0);
	
	while(1){
		PORTB_set_pin_level(LED,1);
		lcd_clrscr();
		lcd_puts("Enter 3-digit\nPIN to open door");//printf("Enter 3-digit PIN to open door\n");
		
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
			lcd_clrscr();
			lcd_puts("Door Open");//printf("\nDoor Open\n");
			PORTB_set_pin_level(LED,0);
			lockcount = 0;
			_delay_ms(2000);
		}
		else{
			lcd_clrscr();
			lcd_puts("Incorrect");//printf("\nIncorrect\n");
			for (x=0; x<6; x++)
			{
				PORTB_toggle_pin_level(LED);
				_delay_ms(300);
			}
			//check for lockout
			lockcount++;
			if (lockcount >= 3)
			{
				lcd_clrscr();
				lcd_puts("lockout\n30 seconds");//printf("lockout for 30 seconds\n");
				_delay_ms(5000);
			}
		}
	}
}
