#include "main.h"

int main(void)
{
	Gpio_ClkEnable(PORTD);
	Gpio_SetMode(PORTD, PIN12, OUTPUT);
	Gpio_SetMode(PORTD, PIN13, OUTPUT);
	Gpio_SetMode(PORTD, PIN14, OUTPUT);
	Gpio_SetMode(PORTD, PIN15, OUTPUT);
	
	Gpio_ClkEnable(PORTA);
	Gpio_SetMode(PORTA, PIN0, INPUT);
	
	Delay_ms(500);

	LED_TYPE Led_Green = LedMgr_ConfigLed(LED_GREEN);
	LED_TYPE Led_Orange = LedMgr_ConfigLed(LED_ORANGE);
	LED_TYPE Led_Blue = LedMgr_ConfigLed(LED_BLUE);
	LED_TYPE Led_Red = LedMgr_ConfigLed(LED_RED);
	
	uint8_t button;
	
	while(1)
	{		
		button = (GPIOA_IDR & 0x01);
		if (button != 0)
		{
			LedMgr_TurnLedOn(Led_Green);
			LedMgr_TurnLedOn(Led_Orange);
			LedMgr_TurnLedOn(Led_Blue);
			LedMgr_TurnLedOn(Led_Red);
		}
		else
		{
			LedMgr_TurnLEDoFF(Led_Red);
			LedMgr_TurnLEDoFF(Led_Blue);
			LedMgr_TurnLEDoFF(Led_Green);
			LedMgr_TurnLEDoFF(Led_Orange);
		}
		
	};
}
