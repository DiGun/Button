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


#define BTN_PRS			20
//Время после которого возможно следующее нажатие
#define BTN_LONG_PRS		150
//Время после которого кнопка считается нажатой длинным нажатием
#define BTN_AFT_RELIASE		150
//Время после которого регистрируется двойное нажатие
#define BTN_TIMEOUT		152
//Время после которого счётчик останавливается

#define BTN_ST_WAIT		0
#define BTN_ST_PRES_EV	2
#define BTN_ST_PRES		1
#define BTN_ST_PRES_LN	3
#define BTN_ST_PRES_LN_EV	4
#define BTN_ST_NEXT_CLR		5
#define BTN_ST_DOUBLE_EV	6



//for test
#define LED_DDR         DDRC
#define LED_OUT			PORTC
#define LED1			(1<<PORTC0)
#define LED2			(1<<PORTC1)
#define LED3			(1<<PORTC2)
#define LED4			(1<<PORTC3)

struct BTN_Data 
{
	uint8_t press;
	uint8_t count;
	uint8_t state;
	/*
BTN_ST_WAIT		Ожидание
BTN_ST_PRES_EV	Нажатие зарегистрированно
BTN_ST_PRES		Нажатие не регистрируем (антидребезг)
BTN_ST_PRES_LN	Долгое нажатие до регистрации
BTN_ST_PRES_LN_EV	Долгое нажатие зарегистрированно
BTN_ST_NEXT_CLR		Регистрация следующего нажатия возможна
BTN_ST_DOUBLE_EV	Очередного нажатия зарегистрированно
	*/	
};

struct BTN_Data btn[4];

void BTN_port_setup(void);
void BTN_Timer_Init(void);
void BTN_Init(void);
void BTN_Check(void);
void BTN_Event(struct BTN_Data b,uint8_t st);
uint8_t BTN_Read(struct BTN_Data b);


#endif /* BUTTON_H_ */