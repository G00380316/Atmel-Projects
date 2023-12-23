//Name: Enoch Abiodun
//Student ID: G00380316
//Date: 30/10/2020

#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"
#include "adc_Start.h"

#define LED 1
#define SW 5
#define SWRst 0 

int main(void)
{
	char ledstring[24];
	int8_t count = 20;
	uint8_t userinput;
	uint8_t check = 1;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	lcd_init(LCD_DISP_ON_CURSOR);
	

	PORTB_set_pin_dir(LED,PORT_DIR_OUT);
	PORTB_set_pin_level(LED,0);
	
	while(1){		
			while (check == 1)
			{
				printf("Enter the number of seconds for the countdown(Must between 1 and 60 seconds): ");
				scanf("%d",&userinput);
	
				printf("\n\n");
				
				if (userinput > 1 && userinput < 60)
				{
					count = userinput;
					check = 0;
				}
				else
				{
				    printf("Error, Invalid Entry please try again\n\n");
				}
				
			}
				
				sprintf(ledstring,"Timer =\n%d Seconds",userinput);
				lcd_puts(ledstring);
				
				while (PORTB_get_pin_level(SW) == 0)
				{
					if (PORTB_get_pin_level(SWRst) == 0)
					{
						count = userinput;
					}
					while(PORTB_get_pin_level(SW) == 0 && count >= 0)
					{
						lcd_clrscr();
						sprintf(ledstring,"Timer =\n%d Seconds",count);
						printf("Timer: %d Seconds\n\n",count);
						lcd_puts(ledstring);
						_delay_ms(1000);
						count --;
						if (PORTB_get_pin_level(SWRst) == 0)
						{
							count = userinput;
						}
						if (count < 10 )
						{
							PORTB_toggle_pin_level(LED);
						}
						check = 1;
					}
				}
	}
	return 0;
}

