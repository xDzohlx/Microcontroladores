/*
 * PWM.c
 *
 * Created: 22/10/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 20000000UL //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#include <util/delay.h>//para hacer un delay, para su fucnionamiento requiere definir F_CPU

void setup(void){
	PORTA.DIRSET = PIN0_bm;//dirección de entrada en este caso es de salida
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV16_gc;
	TCA0.SINGLE.PER = 0x09C4;//0x5DC
	TCA0.SINGLE.CTRLA |= 1;
	TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP0EN_bm|TCA_SINGLE_WGMODE_SINGLESLOPE_gc; 
	TCA0.SINGLE.CMP0 = 0x05DC;
}
int main(void){
	setup();
    while (1){
	
    }
}
