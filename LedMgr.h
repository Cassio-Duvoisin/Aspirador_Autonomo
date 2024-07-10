#ifndef LEDMGR_H
#define LEDMGR_H

#include "stm32f4xx_hal.h"

// Definições para LEDs
#define LED_RED_PIN     GPIO_PIN_14
#define LED_RED_PORT    GPIOD
#define LED_ORANGE_PIN  GPIO_PIN_13
#define LED_ORANGE_PORT GPIOD
#define LED_BLUE_PIN    GPIO_PIN_15
#define LED_BLUE_PORT   GPIOD
#define LED_GREEN_PIN   GPIO_PIN_12
#define LED_GREEN_PORT  GPIOD

// Funções públicas

/**
 * @brief Inicializa os LEDs.
 */
void LED_Init(void);

void LED_On(GPIO_PinState state, GPIO_PinState state1, GPIO_PinState state2, GPIO_PinState state3);

#endif /* LEDMGR_H */
