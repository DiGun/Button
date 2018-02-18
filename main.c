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
    while(1)
    {
		BTN_Check();
		switch (BTN_Read(0))
		{
		case BTN_ST_PRES_EV:
			LED_OUT^=LED1;
			break;
		}
        _delay_ms(5);
		
    }
}