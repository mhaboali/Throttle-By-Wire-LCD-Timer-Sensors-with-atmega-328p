/*
 * Buttons.c
 *
 * Created: 09/09/2017 04:31:10 م
 *  Author: user
 */ 

#include "Buttons.h"

void init_ext_interrupts()
{
	EICRA|=(1<<ISC01);	//set triger INT0 for falling edge mode
	EICRA|=(1<<ISC11);	//set triger INT1 for falling edge mode
	EIMSK|=(1<<INT0);	//turn on INT0
	EIMSK|=(1<<INT1);	//turn on INT1
	sei(); 		//turn on global interrupts
}

void init_buttons()
{
	cbi(DDRD,PD2);			//60 degree button
	sbi(PORTD,PD2);			//enable pull up resistor
	cbi(DDRD,PD3);			//90 degree button
	sbi(PORTD,PD3);			//enable pull up resistor
	
}