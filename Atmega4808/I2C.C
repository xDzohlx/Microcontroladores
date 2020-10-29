/*
 * I2C.c
 *
 * Created: 26/10/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 20000000UL //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#include <util/delay.h>
#define TWI0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU  / (2 * (float)BAUD_RATE)) + 10 )

void send(void);

void send(void){
	TWI0.MADDR = 0x27;
	while(!(TWI0.MSTATUS & TWI_RXACK_bm))
	TWI0.MDATA = 0b10101010;
}


void setup(void){
	PORTA.DIRSET = PIN3_bm|PIN2_bm;
	TWI0.MBAUD = (uint16_t)TWI0_BAUD_RATE(100000);//Generacion de baud para TWI el valor debe ser de como 100
	//TWI0.MBAUD = 0x64;
	
	TWI0.CTRLA |= TWI_SMEN_bm|TWI_ENABLE_bm;
	TWI0.MSTATUS |= TWI_BUSSTATE0_bp;//buss idle
	//TWI0.SADDRMASK = (0x27<<TWI_ADDRMASK0_bp);
	TWI0.MCTRLB |= TWI_FLUSH_bm;
	//TWI0.MADDR = 0x27;
	//TWI0.MDATA = 0b10101010;
}
int main(void){
	setup();
    while (1){
		send();
		_delay_ms(10);
    }
}
