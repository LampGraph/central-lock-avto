/*
 * centr_lock.cpp
 *
 * Created: 25.03.2014 1:15:27
 *  Author: Vyacheslav
 */ 
#define F_CPU 9600000
#define LED_PIN PB4
#define LOCK_DELAY 250
#define OPEN_BUTTON_PIN PB1
#define CLOSE_BUTTON_PIN PB2


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void blink (uint8_t count, uint8_t port);

volatile bool openclose = 0, flag=1;


ISR(PCINT0_vect)
{		
	if ((!(PINB & (1<<0)))&(!openclose)) //If openbutton & close
	{
		openclose = 1; //to open
		flag=0;
	} else if ((!(PINB & (1<<1)))&(openclose)) //If closebutton & open
	{
		openclose = 0; //to close
		flag=0;
	}
}


int main(void)
{
	DDRB = 0x00;
	DDRB |= (1<<PB4); //����������� ��� �� �����	
	DDRB |= (1<<PB3); //����������� ��� �� �����
	SREG |= (1<<7); // Global Interrupt Enable
	GIMSK |= (1<<PCIE); //External Interrupt Request 0 Enable
	PCMSK |= (1<<PCINT0)|(1<<PCINT1);
    while(1)
    {
		if (!flag)
		{	
			flag=1;
			if (openclose)
			{
				blink(1,4);
			} else
			{
//				PORTB |= (1<<3);
				blink(1,3);
			}
		}
    }
}

void blink (uint8_t count, uint8_t port)
{
	for (int i = 0; i < count; i++)
	{
		PORTB |= (1<<port);
		_delay_ms(LOCK_DELAY);
		PORTB &= ~(1<<port);
		_delay_ms(LOCK_DELAY);
	}	
}