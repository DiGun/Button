/*
 * button.h
 *
 * Created: 10.02.2018 19:58:53
 *  Author: DiGun
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include <avr/io.h>


#define BTN_DDR         DDRD
#define BTN_OUT			PORTD
#define BTN_IN			PIND


#define BTN_GET(bit)	(BTN_IN & bit)

#define BTN1			(1<<PORTD2)
#define BTN2			(1<<PORTD3)
#define BTN3			(1<<PORTD4)
#define BTN4			(1<<PORTD5)

#define BTN_MASK		(BTN1|BTN2|BTN3|BTN4)


#define BTN_IN1			BTN_GET(BTN1)
#define BTN_IN2			BTN_GET(BTN2)
#define BTN_IN3			BTN_GET(BTN3)
#define BTN_IN4			BTN_GET(BTN4)


#define BTN_PRS			8
//����� ����� �������� �������� ��������� �������
#define BTN_LONG_PRS		200
//����� ����� �������� ������ ��������� ������� ������� ��������
#define BTN_AFT_TIMEOUT		60
//����� ����� �������� �������������� ������� �������
//#define BTN_TIMEOUT		152
//����� ����� �������� ������� ���������������

#define BTN_ST_WAIT		0
#define BTN_ST_PRES_EV	2
#define BTN_ST_PRES		1
#define BTN_ST_PRES_LN	3
#define BTN_ST_NEXT_CLR		5
#define BTN_ST_PRES_LN_EV	255

struct BTN_Data 
{
	volatile	uint8_t press;
		uint8_t count;
	volatile	uint8_t state;
	/*
BTN_ST_WAIT		��������
BTN_ST_PRES_EV	������� �����������������
BTN_ST_PRES		������� �� ������������ (�����������)
BTN_ST_PRES_LN	������ ������� �� �����������
BTN_ST_PRES_LN_EV	������ �������
BTN_ST_NEXT_CLR		����������� ���������� ������� ��������
	*/	
};

struct BTN_Data btn[4];

void BTN_port_setup(void);
void BTN_Timer_Init(void);
void BTN_Init(void);
void BTN_Check(void);
void BTN_Event(uint8_t n,uint8_t st);
uint8_t BTN_Read(uint8_t n);
void BTN_Calc(uint8_t n);


#endif /* BUTTON_H_ */