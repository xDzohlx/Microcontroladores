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
//Interrupcion por cambio de estado para lectura
ISR(PCINT0_vect){
	if (!(PINA & 0x01)){//checa el cambio en el pin si es bajo
		if (cont > 0){// lectura del canal no es necesario para decodificador
		canal[cont -1]=TCNT1;//lectura del canal no necesario para salida decodificada
		}
		if (cont == 1){//flanco de subida canal 1
			PORTA |= (1<PORTA1);
		}
		if (cont == 2){//flanco de bajada canal 1 y subida canal 2
			PORTA &= ~(1<PORTA1);
			PORTA |= (1<PORTA2);
		}
		if (cont == 3){//flanco de bajada canal 2
			PORTA &= ~(1<PORTA2);
		}
		TCNT1 = 0x00;//reinicio del timer del canal
		cont++;//siguiente canal
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
