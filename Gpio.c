#include "Gpio.h"
#include "Memory_Map.h"
#include "util.h"

void Gpio_ClkEnable(GPIO_PORT Port)
{
	switch(Port)
	{
		case PORTA:
			SET_BIT(RCC_AHB1ENR, RCC_AHB1ENR_GPIOA_ENABLE);
			break;
				
		case PORTD:
			SET_BIT(RCC_AHB1ENR, RCC_AHB1ENR_GPIOD_ENABLE);
			break;
		
		default:
			// do nothing
			break;
	}
};

void Gpio_ClkDisable(GPIO_PORT Port)
{
	switch(Port)
	{
		case PORTA:
			SET_BIT(RCC_AHB1ENR, RCC_AHB1ENR_GPIOA_DISABLED);
			break;
				
		case PORTD:
			SET_BIT(RCC_AHB1ENR, RCC_AHB1ENR_GPIOD_DISABLED);
			break;
		
		default:
			// do nothing
			break;
	}
};

void Gpio_SetMode(GPIO_PORT Port, GPIO_PIN Pin, GPIO_MODE Mode)
{
	switch(Pin)
	{
		case 0:
			if(Port == PORTA)
			{
				SET_BIT(GPIOA_MODER, GPIOA_MODER_PIN0_INPUT);
			}
			break;
			
		case 12:
			if(Port == PORTD)
			{
				if(Mode == OUTPUT)
				{
					SET_BIT(GPIOD_MODER, GPIOD_MODER_PIN12_OUTPUT);
				}
			}
			break;
			
			case 13:
			if(Port == PORTD)
			{
				if(Mode == OUTPUT)
				{
					SET_BIT(GPIOD_MODER, GPIOD_MODER_PIN13_OUTPUT);
				}
			}
			break;
			
			case 14:
			if(Port == PORTD)
			{
				if(Mode == OUTPUT)
				{
					SET_BIT(GPIOD_MODER, GPIOD_MODER_PIN14_OUTPUT);
				}
			}
			break;
			
			case 15:
			if(Port == PORTD)
			{
				if(Mode == OUTPUT)
				{
					SET_BIT(GPIOD_MODER, GPIOD_MODER_PIN15_OUTPUT);
				}
			}
			break;
		
		default:
			// do nothing
			break;
	}
};
