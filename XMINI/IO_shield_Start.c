/*
 * IO_shield.c
 *
 * Created: 25/05/2016 11:46:20
 *  Author: nokeeffe
 */ 

#include <util/delay.h>
#include <atmel_start.h>
#include "IO_shield_Start.h"

/***********************************************************************
Function to configure the 4 LEDS on the IO shield
All LEDs are initialised as off - logic 1 output
************************************************************************/
void IO_shield_LEDs_configure(void)
{
	PORTB_set_pin_dir(LED1, PORT_DIR_OUT);
	PORTB_set_pin_level(LED1, 1);		//LED Off
	PORTB_set_pin_dir(LED2, PORT_DIR_OUT);
	PORTB_set_pin_level(LED2, 1);		//LED Off
	PORTB_set_pin_dir(LED3, PORT_DIR_OUT);
	PORTB_set_pin_level(LED3, 1);		//LED Off
	PORTB_set_pin_dir(LED4, PORT_DIR_OUT);
	PORTB_set_pin_level(LED4, 1);		//LED Off
	/*ioport_configure_pin(LED1, IOPORT_DIR_OUTPUT |  IOPORT_INIT_HIGH);
	ioport_configure_pin(LED2, IOPORT_DIR_OUTPUT |  IOPORT_INIT_HIGH);
	ioport_configure_pin(LED3, IOPORT_DIR_OUTPUT |  IOPORT_INIT_HIGH);
	ioport_configure_pin(LED4, IOPORT_DIR_OUTPUT |  IOPORT_INIT_HIGH);*/
}

/***********************************************************************
Function to turn off a LED on the IO shield
A logic 1 output turns off the led

Passed Parameter: Led number 1,2,3 or 4
************************************************************************/
void IO_LED_off(char led_no)
{
	switch(led_no)
	{
		case 1: PORTB_set_pin_level(LED1, 1); break;
		case 2:PORTB_set_pin_level(LED2, 1); break;
		case 3: PORTB_set_pin_level(LED3, 1); break;
		case 4: PORTB_set_pin_level(LED4, 1); break;
		default: break;
	}
}

/***********************************************************************
Function to turn on a LED on the IO shield
A logic 0 output turns on the led

Passed Parameter: Led number 1,2,3 or 4
************************************************************************/
void IO_LED_on(char led_no)
{
	switch(led_no)
	{
		case 1: PORTB_set_pin_level(LED1, 0); break;
		case 2: PORTB_set_pin_level(LED2, 0); break;
		case 3: PORTB_set_pin_level(LED3, 0); break;
		case 4: PORTB_set_pin_level(LED4, 0); break;
		default: break;
	}
}

/***********************************************************************
Function to toggle a LED on the IO shield

Passed Parameter: Led number 1,2,3 or 4
************************************************************************/
void IO_LED_toggle(char led_no)
{
	switch(led_no)
	{
		case 1: PORTB_toggle_pin_level(LED1); break;
		case 2: PORTB_toggle_pin_level(LED2); break;
		case 3: PORTB_toggle_pin_level(LED3); break;
		case 4: PORTB_toggle_pin_level(LED4); break;
		default: break;
	}
}

void all_LEDs_on(void)
{
	PORTB &= 0xC3;	//PB2 to PB5 low
}

void all_LEDs_off(void)
{
	PORTB |= 0x3C;	//PB2 to PB5 high
}

/**************************************************************************
Function to configure Buzzer GPIO pin
Buzzer is connected to PORTD2
A logic 0 turns on the buzzer
***************************************************************************/
void buzzer_configure(void)
{
	PORTD_set_pin_dir(BUZZER, PORT_DIR_OUT);
	PORTD_set_pin_level(BUZZER, 1);		//Buzzer Off
	//ioport_configure_pin(BUZZER, IOPORT_DIR_OUTPUT |  IOPORT_INIT_HIGH);
}

/**************************************************************************
Function to sound buzzer
A logic 0 turns on buzzer
**************************************************************************/
void buzzer_on(void)
{
	PORTD_set_pin_level(BUZZER, 0);
}

/**************************************************************************
Function to turn off buzzer
A logic 1 turns off buzzer
**************************************************************************/
void buzzer_off(void)
{
	PORTD_set_pin_level(BUZZER, 1);
}

/*************************************************************************
Function to configure IO shield switches
*************************************************************************/
void IO_shield_switch_configure(void)
{
	PORTC_set_pin_dir(SW1, PORT_DIR_IN);
	PORTC_set_pin_pull_mode(SW1, PORT_PULL_UP);
	PORTC_set_pin_dir(SW2, PORT_DIR_IN);
	PORTC_set_pin_pull_mode(SW2, PORT_PULL_UP);
	PORTC_set_pin_dir(SW2, PORT_DIR_IN);
	PORTC_set_pin_pull_mode(SW2, PORT_PULL_UP);
	/*ioport_configure_pin(SW1, IOPORT_DIR_INPUT | IOPORT_PULL_UP);
	ioport_configure_pin(SW2, IOPORT_DIR_INPUT | IOPORT_PULL_UP);
	ioport_configure_pin(SW3, IOPORT_DIR_INPUT | IOPORT_PULL_UP);*/
}

/*************************************************************************
Function to configure IO shield quad 7-segment display
*************************************************************************/
void IO_shield_display_configure(void)
{
	PORTB_set_pin_dir(SDI, PORT_DIR_OUT);
	PORTB_set_pin_level(SDI, 0);	
	PORTD_set_pin_dir(SFTCLK, PORT_DIR_OUT);
	PORTD_set_pin_level(SFTCLK, 0);		
	PORTD_set_pin_dir(LCHCLK, PORT_DIR_OUT);
	PORTD_set_pin_level(LCHCLK, 0);			
	/*ioport_configure_pin(SDI, IOPORT_DIR_OUTPUT |  IOPORT_INIT_LOW);
	ioport_configure_pin(SFTCLK, IOPORT_DIR_OUTPUT |  IOPORT_INIT_LOW);
	ioport_configure_pin(LCHCLK, IOPORT_DIR_OUTPUT |  IOPORT_INIT_LOW);*/
}

void display_write(char display_code, char display_select)
{
	char i, select=0x01;
	
	switch(display_select)
	{
		case 1: select = 0x01; break;	//left display
		case 2: select = 0x02; break;
		case 3: select = 0x04; break;
		case 4: select = 0x08; break;	//right display
		default: break;
	}
	PORTD_set_pin_level(LCHCLK, 0);
	//gpio_set_pin_low(LCHCLK);
	//shift first byte (display data)
	for(i=0;i<8;i++)
	{
		PORTD_set_pin_level(SFTCLK, 0);
		//gpio_set_pin_low(SFTCLK);
		_delay_us(1);
		if(display_code & 0x80)	//high
		PORTB_set_pin_level(SDI, 1);
		//gpio_set_pin_high(SDI);
		else
		PORTB_set_pin_level(SDI, 0);
		//gpio_set_pin_low(SDI);
		display_code = display_code << 1;
		PORTD_set_pin_level(SFTCLK, 1);
		//gpio_set_pin_high(SFTCLK);
		_delay_us(1);
		
	}
	//shift 2nd byte to select display
	for(i=0;i<8;i++)
	{
		PORTD_set_pin_level(SFTCLK, 0);
		//gpio_set_pin_low(SFTCLK);
		_delay_us(1);
		if(select & 0x80)	//high
		PORTB_set_pin_level(SDI, 1);
		//gpio_set_pin_high(SDI);
		else
		PORTB_set_pin_level(SDI, 0);
		//gpio_set_pin_low(SDI);
		select = select << 1;
		PORTD_set_pin_level(SFTCLK, 1);
		//gpio_set_pin_high(SFTCLK);
		_delay_us(1);
		
	}
	//output data to display
	PORTD_set_pin_level(LCHCLK, 1);
	//gpio_set_pin_high(LCHCLK);
	_delay_us(1);
}

