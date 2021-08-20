/*
 * RTC.c
 *
 * Created: 06/07/2021 19:38:21
 * Author : xDzohlx
 * Prueba RTC
 *
 * 
 */ 

#define F_CPU 16000000UL //Frecuencia del cpu 16 MHz


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <stdbool.h>
#include <util/delay.h>

void setup(void){
	
	//Configuracion de CLKPER para fuente de reloj de varios perifericos
	ccp_write_io((void *) & (CLKCTRL.MCLKCTRLB), (CLKCTRL_PDIV_2X_gc|CLKCTRL_PEN_bm));//Maxima frecuencia de lectura de pwm en señal de reloj per, 8 MHZ
	
	//configuracion de puertos
	PORTA.DIRSET = PIN3_bm;//|PIN4_bm|PIN5_bm|PIN6_bm|PIN7_bm;//dirección de entrada en este caso es de salida

	while((RTC.STATUS > 0x00 )){}//se checa que no se este uitilizando	el RTC
		RTC.PER = 511;
		//RTC.CMP = 5;
		RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;
		RTC.DBGCTRL |= RTC_DBGRUN_bm;
		RTC.CTRLA = RTC_PRESCALER_DIV32_gc| RTC_RTCEN_bm| RTC_RUNSTDBY_bm;
		RTC.INTCTRL |= RTC_OVF_bm|;//RTC_CMP_bm;
	//COnfiguracion de prioridad de interrupciones
	CPUINT.LVL0PRI = ADC0_RESRDY_vect_num;
	CPUINT.LVL1VEC = TCB0_INT_vect_num;
	//Habilitar interrupciones generales
	sei();

	}

	ISR(RTC_CNT_vect){
		RTC.INTFLAGS = RTC_OVF_bm|RTC_CMP_bm;
	PORTA.OUTTGL = PIN3_bm;
}
	


int main(void){
	setup();
	while (1){

}//while(1)
}//main
