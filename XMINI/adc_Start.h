/*
 * adc.h
 *
 * Created: 08/03/2016 11:41:40
 *  Author: nokeeffe
 */ 


#ifndef ADC_H_
#define ADC_H_

#define ADC_ENABLE_MASK 0x80
#define ADC_START_CONVERSION_MASK 0x40
#define ADC_INTERRUPT_FLAG_MASK 0x10
#define PRESCALER_DIV2	0x0u
#define PRESCALER_DIV4	0x2u
#define PRESCALER_DIV8	0x3u
#define PRESCALER_DIV16	0x4u
#define PRESCALER_DIV32	0x5u
#define PRESCALER_DIV64	0x6u
#define PRESCALER_DIV128 0x7u

#define POT_CHANNEL 0
#define LM35_CHANNEL 4

//function prototypes
int read_ADC(char channel_no);



#endif /* ADC_H_ */