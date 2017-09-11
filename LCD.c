/*
 * LCD.c
 *
 * Created: 09/09/2017 04:17:46 م
 *  Author: user
 */ 
#include "LCD.h"

void lcd_init_4bits()
{
	data_pinsmode=0xf0;			// Configure both databus and controlbus as output
	control_pinsmode=0x07;
	_delay_ms(20);
	send_cmd_4bits(0x30);
	_delay_ms(5);
	send_cmd_4bits(0x30);
	_delay_ms(1);
	send_cmd_4bits(0x30);
	_delay_ms(1);
	send_cmd_4bits(0x02);	       //Initilize the LCD in 4bit Mode
	_delay_ms(1);
	send_cmd_4bits(0x28);
	_delay_ms(1);
	send_cmd_4bits(0x06);  //entry mode set: increment cursor & without shifting entire display
	_delay_ms(1);
	send_cmd_4bits(0x14);		//cursor or display shift: only cursor shifted right
	_delay_ms(1);
	send_cmd_4bits(0x0E);	      // Display ON cursor ON
	_delay_ms(1);
	send_cmd_4bits(0x40);		//enable CGRAM
	_delay_ms(1);
	send_cmd_4bits(0x80);	      // Move the Cursor to First line First Position
	//send_cmd_4bits(0x01);
}

void send_cmd_4bits( char cmd)
{
	check_busy();
	databus=(cmd & 0xf0);        // Send the Higher Nibble of the command to LCD
	control_bus &=~(1<<rs);  // Select the Command Register by pulling RS LOW
	control_bus &=~(1<<rw);  // Select the Write Operation  by pulling RW LOW
	control_bus |=1<<en;     // Send a High-to-Low Pusle at Enable Pin
	_delay_us(1);
	control_bus &=~(1<<en);
	
	_delay_us(10);				// wait for some time
	
	databus=((cmd<<4) & 0xf0);   // Send the Lower Nibble of the command to LCD
	control_bus &=~(1<<rs);  // Select the Command Register by pulling RS LOW
	control_bus &=~(1<<rw);  // Select the Write Operation  by pulling RW LOW
	control_bus |=1<<en;     // Send a High-to-Low Pusle at Enable Pin
	_delay_us(1);
	control_bus &=~(1<<en);
	
	_delay_ms(1);
	databus=0;
}
void send_char_4bits( char dat)
{
	check_busy();
	databus=(dat & 0xf0);	  // Send the Higher Nibble of the Data to LCD
	control_bus |=1<<rs;	  // Select the Data Register by pulling RS HIGH
	control_bus &=~(1<<rw);	  // Select the Write Operation  by pulling RW LOW
	control_bus |=1<<en;	  // Send a High-to-Low Pusle at Enable Pin
	_delay_us(1);
	control_bus &=~(1<<en);
	_delay_us(10);
	
	databus=((dat <<4) & 0xf0); // Send the Lower Nibble of the Data to LCD
	control_bus |=1<<rs;	   // Select the Data Register by pulling RS HIGH
	control_bus &=~(1<<rw);	   // Select the Write Operation  by pulling RW LOW
	control_bus |=1<<en;	   // Send a High-to-Low Pusle at Enable Pin
	_delay_us(1);
	control_bus &=~(1<<en);
	_delay_ms(1);
	databus=0;
	
}
void send_str_4bits(char *string)
{
	while(*string!='\0')
	{
		send_char_4bits(*string++);
	}
}
void goto_XY_4bits(uint8_t x,uint8_t y)
{
	if (y==1)
	{
		send_cmd_4bits(firstline+x);
	}
	else if(y==2)
	{
		send_cmd_4bits(secondline+x);
	}
}


void send_str_4bits_withXY(uint8_t x,uint8_t y,char *string)
{
	goto_XY_4bits(x,y);
	send_str_4bits(string);
}


void send_int_withXY(uint8_t x,uint8_t y,int value,uint8_t no_digits)
{
	char stringToDisplay[no_digits];
	itoa(value,stringToDisplay,10);
	send_str_4bits_withXY(x,y,stringToDisplay);
	//send_str_4bits(" ");
}

void check_busy()
{
	data_pinsmode=0;
	sbi(control_bus,rw);	//read mode
	cbi(control_bus,rs);	//command mode
	while(databus >= 0x80)			//check for busy (when it's <0x80 it's not busy
	{
		//flashing on and off
	}
	
	data_pinsmode=0xff;
}

void clear_screen_4bits()
{
	send_cmd_4bits(0x01);
	_delay_ms(2);
}
