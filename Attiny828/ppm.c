/*
 * Controladora con ppm.c
 *
 * Created: 28/07/2020 19:50:39
 * Author : xDzohlx
 */ 


#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>

void setup(void){
	//Configuracion de timer de 16 bits para lectura de ppm con microsegundos
	TCCR1B = (1<<WGM12)|(1<<CS11);//Seleccion de reloj y forma de donda en este caso sirve para captura
	
	OCR1A = 0xFA0;//valor de sincronizacion
  //Interrupciones	
	TIMSK1 = (1<<OCIE1A);//Habilita interrupciones del timer
	
	TCNT1 = 0x0000;//Reinicia el contador
	sei();//Activa interrupciones globales
}
ISR(PCINT0_vect){//Primer vector de interrupcion, reinicio del timer y captura
if (!(PINA & 0x01)){//checa flancos ¿
	if (cont > 0){//Verifica inicio de la captura
		canal[cont -1]=TCNT1;//toma captura de datos
		//asigna datos a los canales, se pueden agregar mas canales
    giro = canal[0];
		accel = canal[1];
	}
	TCNT1 = 0x00;//se reinicia el contador
	cont++;//Asigna al siguiente canal
}
}
ISR(TIMER1_COMPA_vect){//Segundo vector de interrupcion, sincronizacion
	cont = 0;//reinicia la posicion de los canales
}
int main(void){
	setup();//inizializacion
	while(1){
  }
  }
