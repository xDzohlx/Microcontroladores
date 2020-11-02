/*
 * I2C.c
 *
 * Created: 26/10/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 20000000 //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#include <util/delay.h>
#define TWI0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU  / (2 * (float)BAUD_RATE)) + 10 )
#define scl PIN3_bm//PA3 ES SCL
#define sda PIN2_bm//PA2 ES SDA
#define device_addr 0x27
void send(void);

void send(void){
	TWI0.MADDR = 0x27;
	while(!(TWI0.MSTATUS & TWI_RXACK_bm))
	TWI0.MDATA = 0b10101010;
}

uint8_t I2C_write(uint8_t data)									// write data, return status
{
	//timeout_cnt = 0;												// reset timeout counter, will be incremented by ms tick interrupt
	if ((TWI0.MSTATUS & TWI_BUSSTATE_gm) == TWI_BUSSTATE_OWNER_gc)	// if master controls bus
	{
		TWI0.MDATA = data;
		while (!(TWI0.MSTATUS & TWI_WIF_bm))						// wait until WIF set, status register contains ACK/NACK bit
		{
		//	if (timeout_cnt > WRITE_TIMEOUT) return 0xff;			// return timeout error
		}
		if (TWI0.MSTATUS & TWI_BUSERR_bm) return 4;					// Bus Error, abort
		if (TWI0.MSTATUS & TWI_RXACK_bm) return 1;					// Slave replied with NACK, abort
		return 0;													// no error
	}
	else return 8;													// master does not control bus
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
		// clear Read and Write interrupt flags
		//if (TWI0.MSTATUS & TWI_BUSERR_bm);						// Bus Error, abort
		TWI0.MADDR = device_addr & 0xFE;
			//timeout_cnt = 0;												// reset timeout counter, will be incremented by ms tick interrupt
	while (!(TWI0.MSTATUS & TWI_RIF_bm) && !(TWI0.MSTATUS & TWI_WIF_bm))	// wait for RIF or WIF set
	{
		//if (timeout_cnt > ADDR_TIMEOUT) return 0xff;				// return timeout error
	}
	TWI0.MSTATUS |= (TWI_RIF_bm | TWI_WIF_bm);						// clear Read and Write interrupt flags	
    }

		TWI0.MDATA = 0xFF;		
		while (!(TWI0.MSTATUS & TWI_WIF_bm))					// wait until WIF set, status register contains ACK/NACK bit
		{
		}
			TWI0.MCTRLB |= TWI_MCMD_STOP_gc;												// no error	
	
}
