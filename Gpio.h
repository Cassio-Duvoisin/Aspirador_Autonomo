#ifndef GPIO_H
#define GPIO_H

#include "Memory_Map.h"

typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH,
	PORTI,
	PORTJ,
	PORTK
} GPIO_PORT;

typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
} GPIO_PIN;

typedef enum
{
	INPUT=0,
	OUTPUT,
	ALT,
	ANALOG
} GPIO_MODE;

void Gpio_ClkEnable(GPIO_PORT Port);
void Gpio_ClkDisable(GPIO_PORT Port);
void Gpio_SetMode(GPIO_PORT Port, GPIO_PIN Pin, GPIO_MODE Mode);


#endif /* GPIO_H */
