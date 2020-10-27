#include <avr/io.h>
// #include <avr/delay.h>
#include <avr/interrupt.h>


volatile static uint8_t count  = 0;
volatile static uint8_t out_time = 0;


// read ADC channel
// http://www.rn-wissen.de/index.php/ADC_(Avr)
uint16_t adc(void)
{ 
 ADCSRA |= (1<<ADSC); // start conversion
 while (ADCSRA & (1<<ADSC)); // wait to finish conversion
 uint16_t val = ADCW; 
 return val;
}

volatile static uint8_t in_start = 0;
volatile static uint8_t timer = 0;

/*// input ppm pin signal change interrupt
ISR(PCINT0_vect)
{
  timer = TCNT0; 
  if (PINB & (1<<PB0)) {
   // low->high   
    in_start = timer;    
  } else {
    // high->low   
    in_time = timer - in_start;   
  }      
}
*/
/*
// timer overflow ISR
ISR(TIMER0_OVF_vect)       
{
} */

volatile static uint8_t sethigh = 1;
volatile static uint8_t pwm = 0;

 // timer comparator interrupt
ISR(TIM1_COMPA_vect)
{ 
  if (sethigh == 1){    
    PORTB |= (1<<PB0); // set output port high
    OCR1A = pwm;   
  } else {
    PORTB &= ~(1<<PB0); // set output port low
    OCR1A=157;  // wait max. possible time for next pulse
 
  }
 
  sethigh = !sethigh;
}  



int main (void)
{
 /*// configure ADC
 ADMUX &= ~(1<<REFS0); // voltage reference (VCC) 
 ADMUX |= (1<<MUX1);// | (1<<MUX0); // choose ADC3 mux
 ADCSRA = ( 1 << ADPS2 );  // ADC speed (clk/16)
 ADCSRA |= (1<<ADEN);  // enable ADC
  */
 // configure timer0 (8bit)
 // used to control servo pulse length
 //TCCR0A = 0;      // normal operation
 //TCCR0B = (1 << CS01) |  (1 << CS00);  // timer speed clk/64  (75 kHz)  
 TCCR1 |= (1<<CTC1)|(1<<CS13)|(1<<CS11)|(1<<CS10);
 TIMSK |= (1 << OCIE1A);  // enable timer comparator interrupt  
 //TIMSK0 |= (1 << TOIE0);   // enable timer overflow interrupt
 
 TCNT1 = 0;
 OCR1A = 157;
 OCR1C = 157;
 
 // configure I/O pins
 //DDRB &= ~(1<<PB4);  // PB4 as output
 DDRB |= (1<<PB0);  // PB0 as input
 
 // configure PCINT0 change interrupt
 //PCMSK |= (1 << PCINT0);
 //GIMSK |= (1 << PCIE);
 
     
 sei();   // enable interrupts*/

 // no-reverse ppm test
 /*while (1){   
    PORTB = (PORTB & (~(1<<PB4))) | ((PINB & (1<<PB0)) << PB4);
 } */
 
 // idea used: http://homepages.which.net/~paul.hills/Circuits/ServoReverser/ServoReverser.html
 
   
      
 while (1){   
for (pwm = 0;pwm<=20;pwm++)
{
 //pwm = pwm +1;
 delay_ms(200);
}
for (pwm ;pwm>=3;pwm--)
{
  //pwm = pwm -1;
  delay_ms(200);
 
}
            
  } 
}

void delay_us(uint8_t time)            //time delay for us
{
 while(time--)
 {
  asm volatile ("NOP");
 }
}


void delay_ms(uint16_t time)
{
 uint8_t i;
 while(time--)
 {
  for(i=0;i<10;i++) delay_us(100);
 }
}
