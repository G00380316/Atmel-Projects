//Name: Enoch Abiodun
//Assignment: Mini-Project (Car Park system)
//Student ID: G00380316
//Date: 15/12/2020

#include <atmel_start.h>
#include <stdio.h>
#include <stdlib.h>
#include "util/delay.h"
#include "keypad_Start.h"
#include "lcd_Start.h"
#include <time.h>

#define GREEN_LED 4
#define Red_LED 6
#define Entry_BUTTON 7
#define ENTRY 5
#define size 4
#define EXIT 3
#define Exit_BUTTON 3
#define Ext_RED_LED 2
#define usercontrol_button 4

int main(void)
{
	uint8_t x, password[size] = {10,0,10,4}, userInput[size], count = 0, y , loop = 0,full = 0,select = 0,open=1;
	uint8_t takenspace = 0,ms=0;
	char buffer[5] = "";
	
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	lcd_init(LCD_DISP_ON_CURSOR);
	keypadConfigure();
	//setting pins to outputs
	PORTB_set_pin_dir(GREEN_LED,PORT_DIR_OUT);
	PORTB_set_pin_dir(Red_LED,PORT_DIR_OUT);
	PORTD_set_pin_dir(Ext_RED_LED,PORT_DIR_OUT);
	PORTB_set_pin_level(Red_LED,0);
	PORTB_set_pin_level(GREEN_LED,0);
	PORTD_set_pin_level(Ext_RED_LED,0);
    //informs user that car park system its getting prepared and sets the servo motors to its orginal position
	for (int i = 0; i < 3; i++)
	{
		lcd_puts("Car park\nSystem booting");
		_delay_ms(1000);
		lcd_clrscr();
		  for (x=0; x<15;x++)
		  {
			  PORTB_set_pin_level(ENTRY,1);
			  _delay_us(100);
		  }
		  for (x=0; x<185;x++)
		  {
			  PORTB_set_pin_level(ENTRY,0);
			  _delay_us(100);
		  }
		for (x=0; x<15;x++)
		{
			PORTB_set_pin_level(EXIT,1);
			_delay_us(100);
		}
		for (x=0; x<185;x++)
		{
			PORTB_set_pin_level(EXIT,0);
			_delay_us(100);
		}
	}
	printf("Enter 4-digit PIN to start and then press the control button when menu has loaded to begin operating Car Park gates\n");
    //read 4-digit pin
	while(loop == 0)
	{
		count=0;
		for (x=0;x<size; x++)
		{
			userInput[x]= keypadScan();
			printf("*");
			if (password[x] == userInput[x])
			{
				count++;
			}
		}
		if (count == size){
			printf("\n\nMenu loading...");
			lcd_puts("Car park\nSystem booted");
			_delay_ms(2000);
			PORTB_set_pin_level(GREEN_LED,1);
			printf("Menu loaded");
			loop = 2;
		}
		else{
			printf("\n\nIncorrect, try again after system light has flashed green\n");
			for (y=0; y<4; y++)
			{
				PORTB_toggle_pin_level(GREEN_LED);
				_delay_ms(500);
			}
			
		}
	}
	//while the control button isn't pressed ms is being incremented to create an affect such as a micro-controller with clock functionality to get a random number
	while(loop==2)
	{
		while(PORTC_get_pin_level(usercontrol_button)==1)
		{
			_delay_ms(1);
			ms++;
		}
		while(PORTC_get_pin_level(usercontrol_button)==0)
		{
			loop=3;
		}
	}
	lcd_clrscr();
	//prints out random number for the space taken
	srand(ms);
	for(y=0;y<100;y++)
	{
		takenspace = rand()%50;	
	}
	itoa(takenspace, buffer, 10);//converts int to string so it can be read by LCD
	lcd_puts("Spaces taken: ");
	lcd_puts(buffer);
	lcd_puts("\nMax Spaces: 50");
	
	while (1)
	{
		if (PORTC_get_pin_level(usercontrol_button) == 0)//reads control button checking if it has been pressed to do the functions within
		{
			loop=1;
			while( loop == 1)
			{
			printf("\n\nPress 1 on the keypad to open exit gate from office\nPress 2 on the keypad to close exit gate from office\n");
			printf("Press 3 on the keypad to Enter Space taken on the keyboard\n");
		    //Reads keypad input once 
		    for (x=0;x<1;x++)
		    {
					userInput[x]= keypadScan();
					select = userInput[x];
		    }
			switch(select)
			{
			case 0://if user entered a 0 it is actually option 1 due to keypad layout opens exit gate
			select=1;
			printf("\nNumber entered %d",select);
			for (x=0; x<10;x++)
			{
				PORTB_set_pin_level(EXIT,1);
				_delay_us(100);
			}
			for (x=0; x<190;x++)
			{
				PORTB_set_pin_level(EXIT,0);
				_delay_us(100);
			}
			_delay_ms(1000);
			open=0;
		    loop=0;
			break;
			case 1://if user entered a 1 it is actually option 2 due to keypad layout closes exit gate
			select=2;
			printf("\nNumber entered %d",select);
			for (x=0; x<15;x++)
			{
				PORTB_set_pin_level(EXIT,1);
				_delay_us(100);
			}
			for (x=0; x<185;x++)
			{
				PORTB_set_pin_level(EXIT,0);
				_delay_us(100);
			}
			loop=0;
			break;
			case 2://if user entered a 3 it is actually option 2 due to keypad layout allows user to enter desired space taken
			select=3;
			printf("\nNumber entered %d",select);
			printf("\nEnter Value(in Send Value)of space taken: ");
			takenspace=USART_0_read();
			printf("%d\n", takenspace);
			lcd_clrscr();
			itoa(takenspace, buffer,10);
			lcd_puts("Spaces taken: ");
			lcd_puts(buffer);
			lcd_puts("\nMax Spaces: 50");
			loop=0;
			break;
			default:
			printf("\nError,Please try again\n\n");
			_delay_ms(1000);
			break;
			}
		}
		}
		if (takenspace<50)//checks if space taken is over 50 if it is i will go to the else if() statement and inform user car park is full
		{
		if(PORTB_get_pin_level(Entry_BUTTON) == 0 && PORTB_get_pin_level(ENTRY)==0)//checks if button is closed and entry gate level is at 0
		{
			PORTB_set_pin_level(Red_LED,1);
			takenspace= takenspace+1;//increments the space taken as the entry gate has been opened indicating a person entering the car park	
			itoa(takenspace, buffer,10);//converts integer to string to write new space taken to LCD
			lcd_clrscr();
			lcd_puts("Spaces taken: ");
			lcd_puts(buffer);
			lcd_puts("\nMax Spaces: 50");
		    for (x=0; x<10;x++)//opens entry gate
		    {
				PORTB_set_pin_level(ENTRY,1);
				_delay_us(100);
		    }
			for (x=0; x<190;x++)
			{
				PORTB_set_pin_level(ENTRY,0);
				_delay_us(100);
			}
			PORTB_set_pin_level(Red_LED,0);
			_delay_ms(1000);
		}
		if (PORTB_get_pin_level(Entry_BUTTON)==1)//closes entry gate after a second to simulate a car entering 
		{
			for (x=0; x<15;x++)
			{
				PORTB_set_pin_level(ENTRY,1);
				_delay_us(100);
			}
			for (x=0; x<185;x++)
			{
				PORTB_set_pin_level(ENTRY,0);
				_delay_us(100);
			}
		}
		}
		else if (full==0)
		{
			lcd_clrscr();
			lcd_puts("Car park is full");
			full=1;
		}

		if (takenspace>0)
		{
		if(PORTD_get_pin_level(Exit_BUTTON) == 0 && PORTB_get_pin_level(EXIT)==0)//checks if button is closed and exit gate level is at 0
		{
			full=0;//unlocks gate as soon as a car passes through exit gate as there will be a space again
			PORTD_set_pin_level(Ext_RED_LED,1);
			takenspace= takenspace-1;// takes one away from space taken as a car has left the car park
			itoa(takenspace, buffer,10);// converts integer to string to be printed by LCD
			lcd_clrscr();
			for (x=0; x<10;x++)//opens exit gate 
			{
				PORTB_set_pin_level(EXIT,1);
				_delay_us(100);
			}
			for (x=0; x<190;x++)
			{
				PORTB_set_pin_level(EXIT,0);
				_delay_us(100);
			}
			lcd_puts("Spaces taken: ");
			lcd_puts(buffer);
			lcd_puts("\nMax Spaces: 50");
			_delay_ms(1000);
			PORTD_set_pin_level(Ext_RED_LED,0);
			open=1;//stops the gate being closed automatically after being opened by control button
		}
		if (PORTD_get_pin_level(Exit_BUTTON)==1 && open==1)// checks if exit button is not pressed and open is equal to 1 to close exit gate
		{
			for (x=0; x<15;x++)
			{
				PORTB_set_pin_level(EXIT,1);
				_delay_us(100);
			}
			for (x=0; x<185;x++)
			{
				PORTB_set_pin_level(EXIT,0);
				_delay_us(100);
			}
		}
		}
}
	
	return 0;
}

