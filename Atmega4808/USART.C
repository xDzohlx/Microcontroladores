/*
 * USART.c
 *
 * Created: 26/10/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 20000000UL //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#include <string.h>
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#include <util/delay.h>

void send(uint8_t dato){
	    while (!(USART0.STATUS & USART_DREIF_bm))
	    {
		    ;
	    }
	    USART0.TXDATAL = dato;
}
int enviar(uint8_t x){
	return 0;
}
void setup(void){
	//USART EN ONE WIRE PARA i2C
	PORTA.DIRSET = PIN2_bm;//Reloj sincrono
	PORTA.DIRSET = PIN0_bm;
	//USART0.CTRLA |= USART_LBME_bm;//Conectar internamente TX a RX 
	PORTA.PIN0CTRL |=PORT_PULLUPEN_bm;//activar resistencia de pullup en puerto PA0
	PORTA.PIN2CTRL |=PORT_PULLUPEN_bm;//activar resistencia de pullup en puerto PA0
	USART0.CTRLB |= USART_ODME_bm;//modo de drenador abierto
	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(100000);
	USART0.CTRLC = USART_CHSIZE_8BIT_gc|USART_CMODE0_bm;//Modo sincrono,7 bits para direccion en 12c XCLK en pin PA2
	USART0.CTRLB |= USART_TXEN_bm;//|USART_RXEN_bm;habilita transmision
	//para lcd 
}
int main(void){
	setup();
    while (1){
		uint8_t x = 0x27;
		//PORTA.DIRSET = PIN0_bm;
		send(x);
		_delay_ms(10);	
    }
}
