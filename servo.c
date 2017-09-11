/*
 * servo.c
 *
 * Created: 09/09/2017 04:25:53 م
 *  Author: user
 */ 
#include "servo.h"

void init_servo()
{
	//set OC1A FOR generating PWM
	sbi(DDRB,PB1);		//set PB1 output
	cbi(PORTB,PB1);		//clear PB1

	//SELECT MODE:
	//fast PWM: (with top = ICR1 & update its value @ BOTTOM , TOV flag set on TOP)
	sbi(TCCR1A,WGM11);
	cbi(TCCR1A,WGM10);
	sbi(TCCR1B,WGM13);
	sbi(TCCR1B,WGM12);
	// non inverting mode : to control on servo motion @ last 2ms in period 20 ms (50 Hz)
	sbi(TCCR1A,COM1A0);
	sbi(TCCR1A,COM1A1);

	//PRESCALING (8):(to have 40000 cycles per second which means that every ms has 2000 cycles)
	sbi(TCCR1B,CS11);
	//setting top value equal 39999 @which starting a new clock
	ICR1=39999;
}
	