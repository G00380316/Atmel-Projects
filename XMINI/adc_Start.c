/*
 * adc.c
 *
 * Created: 08/03/2016 14:21:22
 *  Author: nokeeffe
 */ 
#include <atmel_start.h>
#include "adc_Start.h"



int read_ADC(char channel_no)
{
	PRR &= 0xFE;
	
	//ensure previous conversion is complete
	while(ADCSRA & ADC_START_CONVERSION_MASK)
	{}
	
	//Configure ADC control register
	ADMUX &= 0xF0;		//clear previous channel information
	ADMUX |= (0x1u << 6) | (channel_no);	//reference voltage set to AVCC, channel mux configured
	ADCSRA |= ADC_ENABLE_MASK | PRESCALER_DIV128;// |ADC_START_CONVERSION_MASK;	//ADC enabled, Prescaler of 128
	
	ADCSRA |= ADC_START_CONVERSION_MASK; //start conversion
	while((ADCSRA & ADC_START_CONVERSION_MASK) == 0)	//wait for conversion to complete
	{}
	return ADC;
}