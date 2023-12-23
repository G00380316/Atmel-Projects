/*****************************************************************************************************************
4x3 Keypad Interface

Niall O'Keeffe
V0.1
7/12/2016

 *********************************************************************************************************/

#include <atmel_start.h>
#include "keypad_Start.h"
#include <util/delay.h>

/**********************************************************************************
Function to configure the 4x3 keypad
The keypad row pins are connected to the lower 4 pins of Port C
The keypad column pins are defined in keypad.h and connect to the lower 3 pins of Port B
*/
void keypadConfigure(void)
{
	DDRC = 0x0F;	//PC0 to PC3 are outputs to row pins
	
	//Configure column pins
	PORTB_set_pin_dir(COL1, PORT_DIR_IN);
	PORTB_set_pin_pull_mode(COL1, PORT_PULL_UP);
	PORTB_set_pin_dir(COL2, PORT_DIR_IN);
	PORTB_set_pin_pull_mode(COL2, PORT_PULL_UP);
	PORTB_set_pin_dir(COL3, PORT_DIR_IN);
	PORTB_set_pin_pull_mode(COL3, PORT_PULL_UP);
	/*ioport_configure_pin(COL1, IOPORT_DIR_INPUT | IOPORT_PULL_UP);
	ioport_configure_pin(COL2, IOPORT_DIR_INPUT | IOPORT_PULL_UP);
	ioport_configure_pin(COL3, IOPORT_DIR_INPUT | IOPORT_PULL_UP);*/
}

/***************************************************************************
Function to determine if a key has been pressed on the keypad
Returns a 1 if a key has been pressed
Returns a 0 if no key has been pressed
*/
unsigned char keyPressed(void)
{
	PORTC &= 0xF0;	//pull row pins low
	if((PINB & 0x07) == 0x07)
		return 0;
	else
		return 1;
}

/***************************************************************************************
Function to scan the keypad to detect a key press
The position of the key pressed is returned
*/
unsigned char keypadScan(void)
{
	char rowScan[4] = {0xFE, 0xFD, 0xFB, 0xF7};
	unsigned char i, key=0;
	while(1)
	{
		for(i=0;i<=3;i++)
		{
			PORTC = rowScan[i];
			_delay_ms(1);
			if(PORTB_get_pin_level(COL1) == 0)
			//if(gpio_pin_is_low(COL1))		//is key on column 1?
			{
				switch(i)	//decode keypress
				{
					case 0:	key = 0; break;	//row1, col1
					case 1:	key = 3; break;	//row2, col1
					case 2:	key = 6; break;	//row3, col1
					case 3:	key = 9; break;	//row4, col1
					default:	break;
				}
				//debounce key
				_delay_ms(20);
				if(PORTB_get_pin_level(COL1) == 0)
				//if(gpio_pin_is_low(COL1))
				{
					//while(gpio_pin_is_low(COL1))	//wait for key release
					while(PORTB_get_pin_level(COL1) == 0)
					{}
					return key;		
				}
			}
			if(PORTB_get_pin_level(COL2) == 0)
			//if(gpio_pin_is_low(COL2))		//is key on column 1?
			{
				switch(i)	//decode keypress
				{
					case 0:	key = 1; break;	//row1, col1
					case 1:	key = 4; break;	//row2, col1
					case 2:	key = 7; break;	//row3, col1
					case 3:	key = 10; break;	//row4, col1
					default:	break;
				}
				//debounce key
				_delay_ms(20);
				if(PORTB_get_pin_level(COL2) == 0)
				//if(gpio_pin_is_low(COL2))
				{
					//while(gpio_pin_is_low(COL2))	//wait for key release
					while(PORTB_get_pin_level(COL2) == 0)
					{}
					return key;
				}			
			}
			if(PORTB_get_pin_level(COL3) == 0)
			//if (gpio_pin_is_low(COL3))		//is key on column 1?
			{
				switch(i)	//decode keypress
				{
					case 0:	key = 2; break;	//row1, col1
					case 1:	key = 5; break;	//row2, col1
					case 2:	key = 8; break;	//row3, col1
					case 3:	key = 11; break;	//row4, col1
					default:	break;
				}
				//debounce key
				_delay_ms(20);
				if(PORTB_get_pin_level(COL3) == 0)
				//if(gpio_pin_is_low(COL3))
				{
					//while(gpio_pin_is_low(COL3))	//wait for key release
					while(PORTB_get_pin_level(COL3) == 0)
					{}
					return key;		
				}
			}
		}
	}
}

