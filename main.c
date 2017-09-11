/*
 * Throttle_By_Wire_LCD_Timer_Sensors.c
 *
 * Created: 09/09/2017 04:00:35 م
 *  Author: user
 */ 


#include "config.h"

int main()
{
   lcd_init_4bits();		//initialize LCD with 4 bit-mode
   init_servo();			//initialize servo with fast PWM
   init_POT();				//initialize Throttle Potentionmeter
   init_LM35();				//initialize temperature sensor
   init_buttons();			//initialize buttons
 //values handlers:
   volatile uint16_t digital_LM35_read=0;    //volatile to prevent compiler to remove this variable in optmization stage
   volatile float lcd_LM35_value=0;
   volatile float digital_POT_read=0;    //volatile to prevent compiler to remove this variable in optmization stage
   volatile float lcd_POT_value=0;
  //putting min and maximum degrees for mapping servo:
	float min_deg=800.0;	//at zero digital_POT_readue from ADC
	float max_deg=4000.0;	//at 1023 digital_POT_readue from ADC
	float duty_cycle=(max_deg-min_deg)/1024.0;	//by cross multiplying  
  clear_screen_4bits();			//for clear LCD screen @ start moment
  init_ext_interrupts();		//initialize external interrupts for buttons
  
  while (1)
  {
     digital_LM35_read=adc_read(4);
     lcd_LM35_value=digital_LM35_read/4;		//because of 2.56v is referance so senstivity is 2.5/1023=2.5mv----and knowing that every degree equal 10mv---so for reading temp dividing by 4 
     digital_POT_read=adc_read(5);
     if((((PIND&_BV(PD2))!=0)&&(PIND&_BV(PD3))!=0)) //idle state
	 OCR1A=(ICR1-1900);
     /*
      else if((((PIND&_BV(PD2))==0)&&(PIND&_BV(PD3))!=0)) //60 degree state
	 OCR1A=(ICR1-1900)-1800;
      else if((((PIND&_BV(PD2))!=0)&&(PIND&_BV(PD3))==0)) //90 degree state
	 OCR1A=(ICR1-1900)-2800;
     */
     else
	OCR1A=(ICR1-1900)-(duty_cycle*digital_POT_read);  //1760 for 60 degree------2800 for 90 degree

     send_str_4bits_withXY(0,1,"Throt:");
     lcd_POT_value=floorf((digital_POT_read/1023)*99);
     send_int_withXY(6,1,lcd_POT_value,2);
     send_str_4bits_withXY(8,1,"%");
     send_str_4bits_withXY(9,1," ");
     send_str_4bits_withXY(10,1,"SEM18");
     //send_str_4bits_withXY(0,2,"Speed:");
     //send_str_4bits_withXY(6,2,"28");
     send_str_4bits_withXY(0,2,"A7la Dr Wala eh!");
     // send_str_4bits_withXY(0,2,"Temp(C):");
     //send_int_withXY(8,2,digital_LM35_read,4);
   }
   
   return 0;
}