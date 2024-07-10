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

//---------------------------Funções públicas---------------------------//

/**
 * @brief Inicializa os LEDs.
 */
void LED_Init(void);

/**
 * @brief Seta o estado para os LEDs
 * 
 * @param GPIO_PinState estado desejado do LED
 */
void LED_On(GPIO_PinState led_red, GPIO_PinState led_orange, GPIO_PinState led_blue, GPIO_PinState led_green);

#endif /* LEDMGR_H */
