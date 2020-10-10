/*
 * atmega4808simular.cpp
 *
 * Created: 25/08/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 20000000UL //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#include <util/delay.h>//para hacer un delay, para su fucnionamiento requiere definir F_CPU

#define PA2 2//pin que vamos a utilizar


int main(void)
{
	//inicialización
	PORTA_DIRSET |= (1<<PA2);//dirección de entrada en este caso es de salida
    while (1){
		PORTA_OUTSET |= (1<<PA2);//enciende el led pone en alto el pin PA2 del puerto PORTA
		_delay_ms(100);//espera
		PORTA_OUTCLR |= (1<<PA2);//Apaga
		_delay_ms(100);//Espera
    }
}

