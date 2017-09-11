/*
 * sensors.c
 *
 * Created: 09/09/2017 04:12:06 م
 *  Author: user
 */ 

#include "sensors.h"

void init_POT()
{  
   //voltage referance:(with AVCC reference):
    sbi(ADMUX,REFS0);   
    //cbi(ADMUX,REFS1);

    //select ADC5 Channel:
    sbi(ADMUX,MUX0);
    cbi(ADMUX,MUX1);
    sbi(ADMUX,MUX2);
    cbi(ADMUX,MUX3);

    cbi(ADMUX,ADLAR);    //right adjustment

    //prescaler selector: (128 division factor):
    sbi(ADCSRA,ADPS0);
    sbi(ADCSRA,ADPS1);
    sbi(ADCSRA,ADPS2);
    sbi(ADCSRA,ADEN);	   //enable ADC

    //consumption reduction:
        //disable digital inputs:
        DIDR0=0xff;
        //POWER reduction:
        sbi(SMCR,SE);   //ENABLE SLEEP MODE
        sbi(SMCR,SM0);  //ADC noise cancellation
	
}

void init_LM35()
{  
   //voltage referance:(with 2.56v reference):
    sbi(ADMUX,REFS0);   
    sbi(ADMUX,REFS1);

    //select ADC5 Channel:
    cbi(ADMUX,MUX0);
    cbi(ADMUX,MUX1);
    sbi(ADMUX,MUX2);
    cbi(ADMUX,MUX3);

    cbi(ADMUX,ADLAR);    //right adjustment

    //prescaler selector: (128 division factor):
    sbi(ADCSRA,ADPS0);
    sbi(ADCSRA,ADPS1);
    sbi(ADCSRA,ADPS2);
    sbi(ADCSRA,ADEN);	   //enable ADC

    //consumption reduction:
        //disable digital inputs:
        DIDR0=0xff;
        //POWER reduction:
        sbi(SMCR,SE);   //ENABLE SLEEP MODE
        sbi(SMCR,SM0);  //ADC noise cancellation
	
}

uint16_t adc_read(uint8_t adcx) 
{
	/* adcx is the analog pin we want to use.  ADMUX's first few bits are
	 * the binary representations of the numbers of the pins so we can
	 * just 'OR' the pin's number with ADMUX to select that pin.
	 * We first zero the four bits by setting ADMUX equal to its higher
	 * four bits. */
	ADMUX	&=	0xf0;
	ADMUX	|=	adcx;

	/* This starts the conversion. */
	ADCSRA |= _BV(ADSC);

	/* This is an idle loop that just wait around until the conversion
	 * is finished.  It constantly checks ADCSRA's ADSC bit, which we just
	 * set above, to see if it is still set.  This bit is automatically
	 * reset (zeroed) when the conversion is ready so if we do this in
	 * a loop the loop will just go until the conversion is ready. */
	while ( (ADCSRA & _BV(ADSC)) );

	/* Finally, we return the converted value to the calling function. */
	return ADC;
}


