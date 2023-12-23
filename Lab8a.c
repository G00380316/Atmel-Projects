//Name: Enoch Abiodun
//Student ID: G00380316
//Date: 30/10/2020

#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"
#include "adc_Start.h"

int main(void)
{
	uint8_t stepNumber = 0,stepper[4] = {0x08,0x04,0x02,0x01};
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	DDRB |= 0x0F;
	
	//User enters thresholds
	while(1){
	    PORTB = stepper[stepNumber];
		_delay_ms(500);
		
		stepNumber++;
		if (stepNumber > 3)
		{
			stepNumber = 0;
		}
	}
	
	return 0;
}
