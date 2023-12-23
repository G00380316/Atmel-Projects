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
	int sample;uint32_t voltage;uint16_t lowT =0, highT = 5000;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	//User enters thresholds
	while(1){
	printf("Enter Low threshold in the range 0 to 4999mV\n");
	scanf("%d",&lowT);
	printf("Enter High threshold in the range 0 to 5000mV\n");
	scanf("\%d",&highT);
	printf("Low Threshold: %dmV\tHigh Threshold: %dmV\n\n",lowT,highT);
	//check entered levels
	if (lowT<5000 && highT <= 5000 && lowT<highT)
	{
		printf("Valid threshold values entered\n\n");
		break;
	}
	else 
	{
		printf("******Invalid entry,please try again*****\n");
	}
	}
	
	while(1){
		sample = read_ADC(0);//Read ADC channel 0
		voltage = (uint32_t)sample*5000/1023;
		printf("ADC sample: 0x%03x\tVoltage:%1dmV\n",sample,voltage);
		if (voltage < lowT)
		{
			printf("*****WARNING: VOLTAGE TOO LOW*****\n");
		}
		if(voltage>highT){
			printf("*****WARNING: VOLTAGE TOO HIGH*****\n");
		}
		//Read LM35 VOltage
		sample = read_ADC(4);//Read ADC channel 4
		voltage = (uint32_t)sample*5000/1023;
		printf("ADC sample: 0x%03x\tTempature:%1dC\n",sample,voltage/10);
		_delay_ms(1000);
	}
	
	return 0;
}
