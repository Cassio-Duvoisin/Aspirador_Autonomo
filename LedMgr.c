#include "LedMgr.h"
#include "util.h"
#include "Memory_Map.h"

void LedMgr_TurnLedOn(LED_TYPE Led)
{
	switch(Led.Color)
	{
		case LED_RED:
			SET_BIT(GPIOD_BSRR, 1<<14);
			Led.Status = LED_ON;
			break;
		
		case LED_GREEN:
			SET_BIT(GPIOD_BSRR, 1<<12);
			Led.Status = LED_ON;
			break;
		
		case LED_ORANGE:
			SET_BIT(GPIOD_BSRR, 1<<13);
			Led.Status = LED_ON;
			break;
		
		case LED_BLUE:
			SET_BIT(GPIOD_BSRR, 1<<15);
			Led.Status = LED_ON;
			break;
		
		default:
			// do nothing
			break;
	}
};
	
void LedMgr_TurnLEDoFF(LED_TYPE Led){
	switch(Led.Color)
	{
		case LED_RED:
			SET_BIT(GPIOD_BSRR,(1<<14)<<16);
			Led.Status = LED_OFF;
			break;
		
		case LED_GREEN:
			SET_BIT(GPIOD_BSRR,(1<<12)<<16);
			Led.Status = LED_OFF;
			break;
		
		case LED_ORANGE:
			SET_BIT(GPIOD_BSRR,(1<<13)<<16);
			Led.Status = LED_OFF;
			break;
		
		case LED_BLUE:
			SET_BIT(GPIOD_BSRR,(1<<15)<<16);
			Led.Status = LED_OFF;
			break;
		
		default:
			// do nothing
			break;
	}
};


LED_TYPE LedMgr_ConfigLed(LED_COLOR_TYPE Color)
{
	LED_TYPE Led;
	Led.Color = Color;
	Led.Status = LED_OFF;
	
	return Led;
};
