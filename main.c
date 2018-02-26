/*
 * Button.c
 *
 * Created: 14.02.2018 13:14:32
 *  Author: DiGun
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "button.h"

int main(void)
{
	BTN_Init();
	DDRB=0x0F;
	PORTB=0x0F;
    while(1)
    {
		BTN_Check();
		switch (BTN_Read(0))
		{
		case 1:
		LED_OUT^=LED1;
		break;
		case 2:
		LED_OUT^=LED2;
		break;
		case BTN_ST_PRES_LN_EV:
		LED_OUT^=LED3;
		break;

		}
        _delay_ms(5);
		
    }
}