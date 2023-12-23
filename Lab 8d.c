//Name: Enoch Abiodun
//Student ID: G00380316
//Date: 30/10/2020

#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"
#include "adc_Start.h"

#define SW 7

int main(void)
{
	uint8_t stepNumber = 0,ch, run = 0 , stepDelay = 200, x;
	uint8_t forward[10] = {0x08, 0x04, 0x02, 0x01,0x08, 0x04, 0x02, 0x01, 0x08, 0x04};
	uint8_t reverse[10] = {0x08, 0x01, 0x02, 0x04,0x08, 0x01, 0x02, 0x04, 0x08, 0x01};
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	DDRB |= 0x0F;
	
	//User enters thresholds
	while(1){	
		if (USART_0_is_rx_ready())
		{
			ch = USART_0_read();
			switch(ch){
				case'o':run = 0; break;
				case'r':run = 1;break;
				case's':stepDelay = 200;break;
				case'f':stepDelay = 100;break;
				default: break;
			}
		}
	   if(run == 1){
	    for (stepNumber=0;stepNumber<10; stepNumber++)
	    {
			PORTB = forward[stepNumber];
			for(x=0; x < stepDelay; x++){
			_delay_ms(1);
			}
	    }
		
        for (stepNumber=0;stepNumber<10; stepNumber++)
        {
			PORTB = reverse[stepNumber];
			for(x=0; x < stepDelay; x++){
				_delay_ms(1);
			}
        }
	   }
	}
	
	return 0;
}
