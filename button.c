/*
* button.c
*
* Created: 10.02.2018 19:59:14
*  Author: DiGun
*/
#include <avr/interrupt.h>
#include "button.h"

ISR(TIMER2_OVF_vect)
{
	
	BTN_Calc(0);
	/*
	unsigned char f;
	for (f=0;f<BTN_CNT;f++)
	{
		if(btn_press[f]==0&&btn_set[f]==0)
		{
			switch (btn_count[f])
			{
				case 2:
				btn_set[f]=1;
				break;
				case BTN_WAIT:
				btn_set[f]=1;
				break;
				case BTN_WAIT+1:
				btn_count[f]=BTN_REPEAT;
				break;
			}
			btn_count[f]++;
		}
	}
	*/
}

inline void BTN_Timer_Init(void)
{
	// Timer/Counter 2 initialization
	ASSR=0<<AS2;
	//	TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (1<<CS22) | (1<<CS21) | (1<<CS20);
	TCCR2=(0<<COM21) | (0<<COM20) | (1<<CS22) | (1<<CS21) | (1<<CS20);
	TCNT2=0x00;
	OCR2=0x00;

	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=(0<<OCIE2) | (1<<TOIE2);
}

inline void BTN_port_setup(void)
{
	BTN_DDR&= ~(BTN1|BTN2|BTN3|BTN4);
	BTN_OUT|= (BTN1|BTN2|BTN3|BTN4);
	
	// for test
	LED_DDR|= (LED1|LED2|LED3|LED4);
	LED_OUT|= (LED1|LED2|LED3|LED4);
	
	
}

void BTN_Init(void)
{
	BTN_port_setup();
	BTN_Timer_Init();
}

void BTN_Check(void)
{
	static uint8_t prev_state=BTN_MASK;
	uint8_t last_state=BTN_IN&(BTN_MASK);
	uint8_t chng_state=prev_state^last_state;
	if(chng_state)
	{
		if ((chng_state)&BTN1)
		{
			BTN_Event(0,last_state&BTN1);
		}
		if ((chng_state)&BTN2)
		{
			BTN_Event(1,last_state&BTN2);
		}
		if ((chng_state)&BTN3)
		{
			BTN_Event(2,last_state&BTN3);
		}
		if ((chng_state)&BTN4)
		{
			BTN_Event(3,last_state&BTN4);
		}
	}
	prev_state=last_state;
}

void BTN_Event(uint8_t n,uint8_t st)
{
	struct BTN_Data *b=&btn[n];
	uint8_t prs=(!st?1:0);
	cli();
	b->press&=~1;
	b->press|=prs;
	sei();
	switch (b->state)
	{
		case BTN_ST_WAIT:
		if(prs)
		{
			b->state=BTN_ST_PRES_EV;
		}
		return;

		case BTN_ST_PRES_LN:
		if(!prs)
		{
			b->state=BTN_ST_PRES;
			b->count=BTN_PRS;
		}
		return;
	}
}

void BTN_Calc(uint8_t n)
{
	struct BTN_Data *b=&btn[n];
	if (b->count!=0)
	{
		b->count--;
		switch (b->state)
		{
			case BTN_ST_PRES:
			if (b->count==0)
			{
				LED_OUT^=LED3;
				b->state=BTN_ST_WAIT;
			}
			break;
		}
	}
}

uint8_t BTN_Read(uint8_t n)
{
	struct BTN_Data *b=&btn[n];
	switch (b->state)
	{
		case BTN_ST_PRES_EV:
			LED_OUT^=LED4;
			b->state=BTN_ST_PRES;
			b->count=BTN_PRS;
		return BTN_ST_PRES_EV;
	}		
		
	return BTN_ST_WAIT;	
}
