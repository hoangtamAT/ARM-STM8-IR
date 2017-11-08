#ifndef _IR_H
#define _IR_H
#include "stm8s.h"

#define dl200us	54
#define dl500us	138
#define dl750us	209
#define dl50ms	14100

//#define IR_DATA	GPIO_ReadInputPin(GPIOD,GPIO_PIN_4)
#define IR_DATA	GPIO_ReadInputData(GPIOD)
uint8_t IR_CheckStart();
uint8_t IR_GetCode(void);
void delay_us(int n);


#endif 