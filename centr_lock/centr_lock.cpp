/*
 * centr_lock.cpp
 *
 * Created: 25.03.2014 1:15:27
 *  Author: Vyacheslav
 */ 
#define F_CPU 1600000
#define LED_PIN PB4

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ISR(PCINT0_vect)
{
	PORTB |= (1<<4);
}

int main(void)
{
	DDRB = 0x00;
	DDRB |= (1<<LED_PIN);	
	SREG |= (1<<7); // √лобальное разрешение прерываний.
	GIMSK |= (1<<PCIE); //–азрешаем прерывани€ по изменению пинов
	PCMSK |= (1<<PCINT0)|(1<<PCINT1)|(1<<PCINT2);
    while(1)
    {
        //TODO:: Please write your application code 
		_delay_ms(300);
		PORTB &= ~(1<<4);
//		_delay_ms(300);
//		PORTB |= (1<<4);
    }
}