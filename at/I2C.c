/*
 * I2C.c
 *
 * Created: 01/11/2020 19:14:03
 * Author : xDzohlx
 */ 

#define F_CPU 20000000 //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#include <util/delay.h>
#define TWI0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU  / (2 * (float)BAUD_RATE)) + 10 )
#define scl PIN3_bm//PA3 ES SCL
#define sda PIN2_bm//PA2 ES SDA
#define device_addr 0x27

void enviar(uint8_t dato){
			// clear Read and Write interrupt flags
			//if (TWI0.MSTATUS & TWI_BUSERR_bm);						// Bus Error, abort
			TWI0.MADDR = 0x4E;//dirección con bit de escritura
			//timeout_cnt = 0;												// reset timeout counter, will be incremented by ms tick interrupt
			while (!(TWI0.MSTATUS & TWI_RIF_bm) && !(TWI0.MSTATUS & TWI_WIF_bm)){	// wait for RIF or WIF set
			}
			TWI0.MSTATUS |= (TWI_RIF_bm | TWI_WIF_bm);						// clear Read and Write interrupt flags
			TWI0.MDATA = dato;//0b11110101
			while (!(TWI0.MSTATUS & TWI_WIF_bm))					// wait until WIF set, status register contains ACK/NACK bit
			{
			}
			TWI0.MCTRLB |= TWI_MCMD_STOP_gc;												// no error
}

void setup(void){
	PORTA.DIRCLR = scl;//dcl input
	PORTA.DIRSET = sda;//sda ouput
	//TWI0.MBAUD = (uint16_t)TWI0_BAUD_RATE(10000000);//Generacion de baud para TWI el valor debe ser de como 100
	TWI0.MBAUD = 0x0A;
	TWI0.MCTRLB |=  TWI_FLUSH_bm;
	TWI0.MCTRLA |= TWI_ENABLE_bm;
	PORTA.DIRSET  = scl;
	TWI0.MSTATUS |=TWI_BUSSTATE_IDLE_gc;
	TWI0.MSTATUS |= (TWI_RIF_bm | TWI_WIF_bm | TWI_BUSERR_bm);
}
int main(void){
	setup();
    while (1){
	_delay_ms(1);
	enviar(0b01100101);
	_delay_ms(1);
	enviar(0b01010101);
	}
}
