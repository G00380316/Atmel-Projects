//Name: Enoch Abiodun
//Student ID: G00380316
//Date: 30/10/2020

#include <atmel_start.h>
#include <stdio.h>
#include "util/delay.h"
#include "lcd_Start.h"



int main(void)
{	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	lcd_init(LCD_DISP_ON_CURSOR);
	for (int i = 0; i < 3; i++)
	{
	lcd_puts("Enoch\nAbiodun");
	_delay_ms(2000);
	lcd_clrscr();
	lcd_puts("AGE:18");
	_delay_ms(2000);
	lcd_clrscr();
	}
	
	//Configure LED as an Output
	while(1){
		
	}
		

}