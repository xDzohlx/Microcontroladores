/*
 * atmega4808simular.cpp
 *
 * Created: 25/08/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 20000000UL //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#include <util/delay.h>//para hacer un delay, para su fucnionamiento requiere definir F_CPU

int main(void)
{
	//inicialización
	PORTA.DIRSET = PINA2_bm;//dirección de entrada en este caso es de salida
    while (1){
		PORTA.OUTSET = PINA2_bm;//enciende el led pone en alto el pin PA2 del puerto PORTA
		_delay_ms(100);//espera
		PORTA.OUTCLR = PINA2_bm;//Apaga
		_delay_ms(100);//Espera
    }
}

