/*
 * sensor_potenciometro.cpp
 *nueve leds de PA1 A PA7 Y PB0 Y PB1
* ADC input en PA0 (ADC0)
 * Created: 01/10/2014 12:32:31 p.m.
 *  Author: Dzohl
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

volatile static uint8_t valor_adc = 0x00;

ISR(ADC_vect)
{
	valor_adc = ADCH;
}


int main(void)
{
	
			//ADC ATTINY24
			ADMUX &= ~(1<<REFS1);//...
			ADMUX &= ~(1<<REFS0);//(esta placa a vcc)
			ADCSRB |= (1<<ADLAR);//left adjust
			//ADMUX |= (1<<MUX2)|(1<<MUX1)|(1<<MUX0);// adc canal 7
			ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADATE);//Frecuencia de muestreo 125kH:autotriger (1<<ADIE)|
			//ADCSRB = 0x00;
			ADCSRA |= (1<<ADSC);//comienza el muestreo
			DDRA |= (1<<PA1)|(1<<PA2)|(1<<PA3)|(1<<PA4)|(1<<PA5)|(1<<PA6)|(1<<PA7);//SALIDAS LEDS
			DDRB |= (1<<PB0)|(1<<PB1);//SALIDAS LEDS
			


sei();			
    while(1)
    {
	if ((valor_adc >= 0) && (valor_adc < 0x1C))//LED1
	{
		PORTA |= (1<<PA1);
		PORTA &= ~(1<<PA2);
		PORTA &= ~(1<<PA3);
		PORTA &= ~(1<<PA4);
		PORTA &= ~(1<<PA5);
		PORTA &= ~(1<<PA6);
		PORTA &= ~(1<<PA7);
		PORTB &= ~(1<<PB0);
		PORTB &= ~(1<<PB1);
	}
	
	if ((valor_adc >= 0x1C) && (valor_adc < 0x39))//LED2
	{
		PORTA &= ~(1<<PA1);
		PORTA |= (1<<PA2);
		PORTA &= ~(1<<PA3);
		PORTA &= ~(1<<PA4);
		PORTA &= ~(1<<PA5);
		PORTA &= ~(1<<PA6);
		PORTA &= ~(1<<PA7);
		PORTB &= ~(1<<PB0);
		PORTB &= ~(1<<PB1);
	}
	if ((valor_adc >= 0x39) && (valor_adc < 0x56))//LED3
	{
		PORTA &= ~(1<<PA1);
		PORTA &= ~(1<<PA2);
		PORTA |= (1<<PA3);
		PORTA &= ~(1<<PA4);
		PORTA &= ~(1<<PA5);
		PORTA &= ~(1<<PA6);
		PORTA &= ~(1<<PA7);
		PORTB &= ~(1<<PB0);
		PORTB &= ~(1<<PB1);
	}
	if ((valor_adc >= 0x56) && (valor_adc < 0x72))//LED4
	{
		PORTA &= ~(1<<PA1);
		PORTA &= ~(1<<PA2);
		PORTA &= ~(1<<PA3);
		PORTA |= (1<<PA4);
		PORTA &= ~(1<<PA5);
		PORTA &= ~(1<<PA6);
		PORTA &= ~(1<<PA7);
		PORTB &= ~(1<<PB0);
		PORTB &= ~(1<<PB1);
	}
	if ((valor_adc >= 0x72) && (valor_adc < 0x8E))//LED5
	{
		PORTA &= ~(1<<PA1);
		PORTA &= ~(1<<PA2);
		PORTA &= ~(1<<PA3);
		PORTA &= ~(1<<PA4);
		PORTA |= (1<<PA5);
		PORTA &= ~(1<<PA6);
		PORTA &= ~(1<<PA7);
		PORTB &= ~(1<<PB0);
		PORTB &= ~(1<<PB1);
	}
	if ((valor_adc >= 0x8E) && (valor_adc < 0xAB))//LED6
	{
		PORTA &= ~(1<<PA1);
		PORTA &= ~(1<<PA2);
		PORTA &= ~(1<<PA3);
		PORTA &= ~(1<<PA4);
		PORTA &= ~(1<<PA5);
		PORTA |= (1<<PA6);
		PORTA &= ~(1<<PA7);
		PORTB &= ~(1<<PB0);
		PORTB &= ~(1<<PB1);
	}
	if ((valor_adc >= 0xAB) && (valor_adc < 0xC7))//LED7
	{
		PORTA &= ~(1<<PA1);
		PORTA &= ~(1<<PA2);
		PORTA &= ~(1<<PA3);
		PORTA &= ~(1<<PA4);
		PORTA &= ~(1<<PA5);
		PORTA &= ~(1<<PA6);
		PORTA |= (1<<PA7);
		PORTB &= ~(1<<PB0);
		PORTB &= ~(1<<PB1);
	}
	if ((valor_adc >= 0xC7) && (valor_adc < 0xE4))//LED8
	{
		PORTA &= ~(1<<PA1);
		PORTA &= ~(1<<PA2);
		PORTA &= ~(1<<PA3);
		PORTA &= ~(1<<PA4);
		PORTA &= ~(1<<PA5);
		PORTA &= ~(1<<PA6);
		PORTA &= ~(1<<PA7);
		PORTB |= (1<<PB0);
		PORTB &= ~(1<<PB1);
	}
	if (valor_adc >= 0xE4)//LED9
	{
		PORTA &= ~(1<<PA1);
		PORTA &= ~(1<<PA2);
		PORTA &= ~(1<<PA3);
		PORTA &= ~(1<<PA4);
		PORTA &= ~(1<<PA5);
		PORTA &= ~(1<<PA6);
		PORTA &= ~(1<<PA7);
		PORTB &= ~(1<<PB0);
		PORTB |= (1<<PB1);
	}
		
	}//while
}//maim
