#ifndef LEDMGR_H
#define LEDMGR_H

typedef enum
{
	LED_RED=0,
	LED_GREEN,
	LED_BLUE,
	LED_ORANGE
} LED_COLOR_TYPE;

typedef enum
{
	LED_ON=0,
	LED_OFF
} LED_STATUS_TYPE;

typedef struct
{
	LED_STATUS_TYPE Status;
	LED_COLOR_TYPE Color;
}LED_TYPE;

void LedMgr_TurnLedOn(LED_TYPE Led);
void LedMgr_TurnLEDoFF(LED_TYPE Led);
LED_TYPE LedMgr_ConfigLed(LED_COLOR_TYPE Color);
	

#endif /* LEDMGR_H */
