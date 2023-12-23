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
	int sample;uint8_t voltage;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	
	while(1){
		sample = read_ADC(0);
		voltage = (uint8_t)sample*5000/1023;
		printf("ADC sample: 0x%03x\tVoltage:%1dmV\n",sample,voltage);
		_delay_ms(1000);
	}
	
	return 0;
}
