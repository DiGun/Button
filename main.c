/*
* Button.c
*
* Created: 14.02.2018 13:14:32
*  Author: DiGun
*/


#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "button.h"

#define LED_DDR         DDRC
#define LED_OUT			PORTC
#define LED1			(1<<PORTC0)
#define LED2			(1<<PORTC1)
#define LED3			(1<<PORTC2)
#define LED4			(1<<PORTC3)


uint8_t zone[2];
uint8_t chk_zone1_off(uint8_t zn)
{
	if (zone[zn])
	{
		if (zn==0)
		{
			LED_OUT|=LED1|LED2;
			zone[0]=0;
			return 0;
		}
		if (zn==1)
		{
			LED_OUT|=LED3|LED4;
			zone[1]=0;
			return 0;
		}
	}
	return 1;
}

int main(void)
{
	uint8_t f;
	LED_DDR|= (LED1|LED2|LED3|LED4);
	LED_OUT|= (LED1|LED2|LED3|LED4);
	BTN_Init();
	DDRB=0x0F;
	PORTB=0x0F;
	zone[0]=0;
	zone[1]=0;
	_delay_ms(11);
	BTN_Check();
	for (f=0;f<4;f++)
	{
		BTN_Read(f);
	}
	wdt_enable(WDTO_1S);
	while(1)
	{
		BTN_Check();
		switch (BTN_Read(0))
		{
			case 1:
			if(chk_zone1_off(0))
			{
				LED_OUT&=~LED1;
				zone[0]=1;
			}
			break;
			case 2:
			if(chk_zone1_off(0))
			{
				LED_OUT&=~(LED1|LED2);
				zone[0]=2;
			}
			break;
			case 3:
			if(chk_zone1_off(0))
			{
				LED_OUT&=~LED2;
				zone[0]=3;
			}
			break;
			case BTN_ST_PRES_LN_EV:
			LED_OUT^=LED1|LED2;
			break;
		}

		switch (BTN_Read(1))
		{
			case 1:
			if(chk_zone1_off(1))
			{
				LED_OUT&=~LED3;
				zone[1]=1;
			}
			break;
			case 2:
			if(chk_zone1_off(1))
			{
				LED_OUT&=~(LED3|LED4);
				zone[1]=2;
			}
			break;
			case 3:
			if(chk_zone1_off(1))
			{
				LED_OUT&=~LED4;
				zone[1]=3;
			}
			break;
			case BTN_ST_PRES_LN_EV:
			LED_OUT^=LED3|LED4;
			break;
		}
		wdt_reset();
		_delay_ms(5);
	}
}