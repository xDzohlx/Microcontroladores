/*
 * onoffatsamd10.c
 *
 * Created: 09/10/2020 11:58:34 a. m.
 * Author : xDzohlx
 */ 


#include "sam.h"


int main(void)
{
//Inicialización del sistema
    SystemInit();
	PORT ->Group[0].DIRSET.reg = PORT_PA14;//configuración de pines de salida

    while (1){
		if (PORT ->Group[0].IN.reg & PORT_PA15){
			PORT ->Group[0].OUTSET.reg = PORT_PA14;//encedido
	}else{
		PORT ->Group[0].OUTCLR.reg = PORT_PA14;//apagado
	}
    }
}
