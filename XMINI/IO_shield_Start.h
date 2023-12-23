/*
 * IO_shield.h
 *
 * Created: 25/05/2016 11:43:00
 *  Author: nokeeffe
 */ 


#ifndef IO_SHIELD_H_
#define IO_SHIELD_H_

/******************************************************************/
//LED definitions
#define LED1	5u//IOPORT_CREATE_PIN(PORTB, 5)
#define LED2	4u//IOPORT_CREATE_PIN(PORTB, 4)
#define LED3	3u//IOPORT_CREATE_PIN(PORTB, 3)
#define LED4	2u//IOPORT_CREATE_PIN(PORTB, 2)

//function prototypes
void IO_shield_LEDs_configure(void);
void IO_LED_on(char led_no);
void IO_LED_off(char led_no);
void IO_LED_toggle(char led_no);
void all_LEDs_on(void);
void all_LEDs_off(void);
/******************************************************************/

//Buzzer
#define BUZZER	3u//IOPORT_CREATE_PIN(PORTD, 3)

//function prototypes
void buzzer_configure(void);
void buzzer_on(void);
void buzzer_off(void);
/******************************************************************/

//Switches
#define SW1	1u//IOPORT_CREATE_PIN(PORTC, 1)
#define SW2	2u//IOPORT_CREATE_PIN(PORTC, 2)
#define SW3	3u//IOPORT_CREATE_PIN(PORTC, 3)

//function prototypes
void IO_shield_switch_configure(void);

/******************************************************************/
//7-Segment Display interface pins
#define SDI			0u//IOPORT_CREATE_PIN(PORTB, 0)
#define SFTCLK		7u//IOPORT_CREATE_PIN(PORTD, 7)
#define LCHCLK		4u//IOPORT_CREATE_PIN(PORTD, 4)

//function prototypes
void IO_shield_display_configure(void);
void display_write(char display_code, char display_select);


#endif /* IO_SHIELD_H_ */