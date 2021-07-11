/*
 * ppm.c
 *
 * Created: 06/07/2021 19:38:21
 * Author : xDzohlx
 */ 

#define F_CPU 20000000UL //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
int cont = 0;//Contador de canal
volatile uint16_t VALORADC = 0x0000;
volatile uint16_t canal[6];

void setup(void){
	//Configuración de reloj
	ccp_write_io((void *) & (CLKCTRL.MCLKCTRLB), (CLKCTRL_PDIV_16X_gc|CLKCTRL_PEN_bm));	
	PORTA.DIRSET = PIN0_bm;//|PIN1_bm|PIN2_bm|PIN3_bm|PIN4_bm|PIN5_bm|PIN6_bm|PIN7_bm;//dirección de entrada en este caso es de salida

	TCB0.CTRLA |= TCB_ENABLE_bm|TCB_CLKSEL_CLKDIV1_gc;//ACTIVACION DE EVENTOS RELOJ PROVIENE DE TCA A 1MHZ //clkper 
	TCB0.CTRLB |= TCB_CNTMODE_FRQ_gc;//modo de lectura de frecuencia
	TCB0.EVCTRL |= TCB_CAPTEI_bm|TCB_EDGE_bm;//ACTIVA CAPTURA DE EVENTOS, EDGE es el sentido del pulso en este caso esta inverso
	TCB0.INTCTRL |= TCB_CAPT_bm;
	//CONFIGURACION DE RED DE EVENTOS
	EVSYS.CHANNEL2 |= EVSYS_GENERATOR_PORT0_PIN0_gc;//PORTC3 CONECTADO A CANAL 2 para lectura de ppm
	EVSYS.USERTCB0 |= EVSYS_CHANNEL_CHANNEL2_gc;//usuario TCB0 conectado al canal 2

	sei();
}
ISR(TCB0_INT_vect){
if (cont > 0)// lectura del canal no es necesario para decodificador
	canal[cont -1]=TCB0.CCMP;//lectura del canal no necesario para salida decodificada

cont++;//siguiente canal
if (canal[cont-2]>0xFA0)
	cont = 0;
}

int main(void){
	setup();
	while (1){
		if(canal[2]>1500){
			PORTA.OUTSET = PIN0_bm;
			}else{
			PORTA.OUTCLR = PIN0_bm;
		}
	}
}
