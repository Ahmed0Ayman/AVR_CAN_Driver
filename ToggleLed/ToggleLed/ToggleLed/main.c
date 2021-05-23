/*
 * ToggleLed.c
 *
 * Created: 5/18/2021 9:00:06 PM
 * Author : Ahmed_Ayman
 */ 
#define F_CPU  16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0x80;
    /* Replace with your application code */
    while (1) 
    {


					PORTD |= 0x80 ;
					_delay_ms(200);
					PORTD &= ~(0x80);
					_delay_ms(200);
			if((PIND & 0x01)==1) /* request jump to bootloader mode from app */
			{
				asm("jmp 0x3800");
			}
    }
}

