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
	uint8_t stepNumber = 0;
	uint8_t forward[10] = {0x08, 0x04, 0x02, 0x01,0x08, 0x04, 0x02, 0x01, 0x08, 0x04};
	uint8_t reverse[10] = {0x08, 0x01, 0x02, 0x04,0x08, 0x01, 0x02, 0x04, 0x08, 0x01};
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	DDRB |= 0x0F;
	
	//User enters thresholds
	while(1){	
	    for (stepNumber=0;stepNumber<10; stepNumber++)
	    {
			PORTB = forward[stepNumber];
			_delay_ms(200);
	    }
		
        for (stepNumber=0;stepNumber<10; stepNumber++)
        {
			PORTB = reverse[stepNumber];
			_delay_ms(200);
        }
	}
	
	return 0;
}
