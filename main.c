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

#define LED_DDR_ADD1        DDRD
#define LED_OUT_ADD1		PORTD
#define LED5			(1<<PORTD6)
#define LED6			(1<<PORTD7)

#define LED_DDR_ADD2        DDRB
#define LED_OUT_ADD2		PORTB
#define LED7			(1<<PORTB0)
#define LED8			(1<<PORTB1)

uint8_t zone[4];
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
		if (zn==2)
		{
			LED_OUT_ADD1|=LED5|LED6;
			zone[2]=0;
			return 0;
		}
		if (zn==3)
		{
			LED_OUT_ADD2|=LED7|LED8;
			zone[3]=0;
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
	LED_DDR_ADD1|= (LED5|LED6);
	LED_OUT_ADD1|= (LED5|LED6);
	LED_DDR_ADD2|= (LED7|LED8);
	LED_OUT_ADD2|= (LED7|LED8);
	BTN_Init();
//	DDRB=0x0F;
//	PORTB=0x0F;
	zone[0]=0;
	zone[1]=0;
	zone[2]=0;
	zone[3]=0;
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
		
		switch (BTN_Read(2))
		{
			case 1:
			if(chk_zone1_off(2))
			{
				LED_OUT_ADD1&=~LED5;
				zone[2]=1;
			}
			break;
			case 2:
			if(chk_zone1_off(2))
			{
				LED_OUT_ADD1&=~(LED5|LED6);
				zone[2]=2;
			}
			break;
			case 3:
			if(chk_zone1_off(2))
			{
				LED_OUT_ADD1&=~LED6;
				zone[2]=3;
			}
			break;
			case BTN_ST_PRES_LN_EV:
			LED_OUT_ADD1^=LED5|LED6;
			break;
		}

		switch (BTN_Read(3))
		{
			case 1:
			if(chk_zone1_off(3))
			{
				LED_OUT_ADD2&=~LED7;
				zone[3]=1;
			}
			break;
			case 2:
			if(chk_zone1_off(3))
			{
				LED_OUT_ADD2&=~(LED7|LED8);
				zone[3]=2;
			}
			break;
			case 3:
			if(chk_zone1_off(3))
			{
				LED_OUT_ADD2&=~LED8;
				zone[2]=3;
			}
			break;
			case BTN_ST_PRES_LN_EV:
			LED_OUT_ADD2^=LED7|LED8;
			break;
		}

		wdt_reset();
		_delay_ms(1);
	}
}