/*
 * USART.c
 *
 * Created: 25/08/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 20000000UL //Frecuencia del cpu 20 MHz
#include <avr/io.h>
void enviar(int x){
	return 0;
}
void setup(void){
	//USART EN ONE WIRE PARA i2C
	USART0.CTRLA |= USART_LBME_bm;//Conectar internamente TX a RX 
	PORTA.PIN0CTRL |=PORT_PULLUPEN_bm;//activar resistencia de pullup en puerto PA0
	USART0.CTRLB |= USART_ODME_bm;//modo de drenador abierto
	USART0.BAUD = 0x00;//Definir a 100 Kbaud
	USART0.CTRLC |= USART_CMODE1_bm;//Modo sincrono, para sbus es invertido, paridad y 2 bits de parada
	//para lcd 
}
int main(void){
	setup();
    while (1){
		int dato;
	enviar(dato);
    }
}
