/*
 * ADC828.c
 *
 * Created: 25/01/2021 20:57:45
 * Author : Usuario
 */ 

#include <avr/io.h>


int main(void)
{
		DDRC |= (1<<PORTC6);//Pin de salida para un led
		ADCSRB |= (1<<ADLAR);//Ajustado a la izquierda para una resolución de 8 bits
		ADMUXA |= (1<<MUX0);// adc canal 1
		ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADATE);//Frecuencia de muestreo 125kH y lectura automatica
		ADCSRA |= (1<<ADSC);//comienza el muestreo
		
    while (1) {
    if(ADCH>189){//valor de 3.7 volts
			PORTC &= ~(1<<PORTC6); //prende el led con un valor bajo
	}else{
		PORTC |= (1<<PORTC6);	//prende el led con un valor alto
	}
    }
}

