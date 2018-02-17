/*
 * Button.c
 *
 * Created: 14.02.2018 13:14:32
 *  Author: DiGun
 */ 


#include <avr/io.h>
#include "button.h"

int main(void)
{
	BTN_Init();
    while(1)
    {
		BTN_Check();
        //TODO:: Please write your application code 
    }
}