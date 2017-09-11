/*
 * config.h
 *
 * Created: 09/09/2017 04:03:17 م
 *  Author: user
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#define sbi(reg,pin) reg|=_BV(pin)
#define cbi(reg,pin) reg&=~_BV(pin)
#define tbi(reg,pin) reg^=_BV(pin)
#define is_high(reg,pin) (((reg)&_BV(pin))==1)

#define data_pinsmode		DDRD
#define databus			PORTD
#define control_pinsmode	DDRC
#define control_bus		PORTC

#define rs PC0
#define rw PC1
#define en PC2
#define maxlines	2
#define maxchars	16
#define firstline	0x80
#define secondline 0xc0
#define blankspace ' '



#endif /* CONFIG_H_ */