/*
 * ADC828.c
 *
 * Created: 25/01/2021 20:57:45
 * Author : Usuario
 */ 

#include <avr/io.h>


int main(void)
{
		DDRC |= (1<<PORTC6);
		ADCSRB |= (1<<ADLAR);//left adjust
		ADMUXA |= (1<<MUX0);// adc canal 7
		ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADATE);//Frecuencia de muestreo 125kH:autotriger (1<<ADIE)|
		ADCSRA |= (1<<ADSC);//comienza el muestreo
		
    while (1) {
    if(ADCH>189){
			PORTC &= ~(1<<PORTC6);
	}else{
		PORTC |= (1<<PORTC6);
	}
    }
}

