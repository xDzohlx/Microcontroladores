/*
 * Bateria.c
 *
 * Created: 25/01/2021 20:57:45
 * Author : Usuario
 */ 

#include <avr/io.h>


int main(void)
{
		DDRA |= (1<<PORTA0);
		ADCSRB |= (1<<ADLAR);//left adjust
		ADMUXA |= (1<<MUX1)|(1<<MUX4);// adc canal 7
		ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADATE);//Frecuencia de muestreo 125kH:autotriger (1<<ADIE)|
		ADCSRA |= (1<<ADSC);//comienza el muestreo
		
    while (1) {
    if(ADCH>230){
		PORTA &= ~(1<<PORTA0);
	}else{
		PORTA |= (1<<PORTA0);
	}
    }
}

