/*
 * sbus.c
 *
 * Created: 17/10/2020 12:35:05
 * Author : Usuario
 */ 
#define F_CPU 20000000
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
//#include <avr/sleep.h>
#include <string.h>

char USART0_readChar(void)
{
    while (!(USART0.STATUS & USART_RXCIF_bm))
    {
        ;
    }
    return USART0.RXDATAL;
}

void setup(void){
    PORTA.DIRCLR = PIN3_bm;
    PORTA.DIRSET = PIN2_bm;
	PORTA.PIN3CTRL = PORT_INVEN_bm;
    //cofiguracion para lecutra de sbus se tiene que negar
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(100000);

    USART0.CTRLB |= USART_RXEN_bm;
	USART0.CTRLC |= USART_PMODE0_bm|USART_SBMODE_bm;
}

int main(void)
{
setup();

    while (1){
		 USART0_readChar();
		 //if(c != '\n' && c != '\r')
        //{
            //command[index++] = c;
            //if(index > MAX_COMMAND_LEN)
            //{
                //index = 0;
            //}
        //}
        //
        //if(c == '\n')
        //{
            //command[index] = '\0';
            //index = 0;
            //executeCommand(command);
        //}
    }
}

