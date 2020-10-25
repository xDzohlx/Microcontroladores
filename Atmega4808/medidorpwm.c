/*
 * medidorpwm
 *
 * Created: 22/10/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 16000000UL //Frecuencia del cpu 16 MHz
#include <avr/io.h>
#include <util/delay.h>//para hacer un delay, para su fucnionamiento requiere definir F_CPU

volatile uint16_t CANALPWM;
void setup(void){
	//timer TCA
	PORTA.DIRSET = PIN0_bm;//PORTA0 como salida
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV16_gc;//fuente de reloj, 
	TCA0.SINGLE.PER = 0x0400;//Selección de resolucion de pwm y periodo total de pwm
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;//Habilitar pwm
	TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP0EN_bm|TCA_SINGLE_WGMODE_SINGLESLOPE_gc;//Habilitar comparador y seleccion de modo de de generacion de onda con modo de rampa sensilla
	TCA0.SINGLE.CMP0 = 0x0004;//registro de 16 bits para comparacion y pediodo de pwm
	//TCB PARA CONTADOR DE ANCHO DE PULSO
	TCB0.CTRLA |= TCB_ENABLE_bm|TCB_CLKSEL_CLKTCA_gc;//ACTIVACION DE EVENTOS RELOJ PROVIENE DE TCA A 1MHZ 
	TCB0.CTRLB |= TCB_CNTMODE_PW_gc;//modo de lectura de ancho de pulso
	TCB0.EVCTRL |= TCB_CAPT_bm;//TCB_EDGE_bm|ACTIVA CAPTURA DE EVENTOS
	//CONFIGURACION DE RED DE EVENTOS
	EVSYS.CHANNEL2 |= EVSYS_GENERATOR_PORT1_PIN0_gc;//PORTD0 CONECTADO A CANAL 2
	EVSYS.USERTCB0 |= EVSYS_CHANNEL_CHANNEL2_gc;//usuario TCB0 conectado al canal 2
}
int main(void){
	setup();//funcion de configuración
    while (1){
		CANALPWM = TCB0.CCMP-150;//mueve lectura de pwm a canalpwm
		TCA0.SINGLE.CMP0 = CANALPWM;//El valor del canalpwm controla el periodo del TCA0
    }
}
