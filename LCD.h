/*
 * LCD.h
 *
 * Created: 09/09/2017 04:13:32 م
 *  Author: user
 */ 
#include "config.h"

#ifndef LCD_H_
#define LCD_H_


void lcd_init_4bits();
void send_cmd_4bits( char cmd);
void send_char_4bits( char dat);

void send_str_4bits(char *string);
void goto_XY_4bits(uint8_t x,uint8_t y);
void send_str_4bits_withXY(uint8_t x,uint8_t y,char *string);
void send_int_withXY(uint8_t x,uint8_t y,int value,uint8_t no_digits);

void clear_screen_4bits();
void check_busy();




#endif /* LCD_H_ */