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
 * @brief Seta o estado para os LEDs.
 * 
 * @param led_red Estado do LED vermelho (GPIO_PIN_RESET ou GPIO_PIN_SET).
 * @param led_orange Estado do LED laranja (GPIO_PIN_RESET ou GPIO_PIN_SET).
 * @param led_blue Estado do LED azul (GPIO_PIN_RESET ou GPIO_PIN_SET).
 * @param led_green Estado do LED verde (GPIO_PIN_RESET ou GPIO_PIN_SET).
 */
void LED_On(GPIO_PinState led_red, GPIO_PinState led_orange, GPIO_PinState led_blue, GPIO_PinState led_green);

/**
 * @brief Alterna o estado dos LEDs (liga se estiver desligado, desliga se estiver ligado).
 * 
 * @param led_pin Pino do LED a ser alternado.
 */
void LED_Toggle(uint16_t led_pin);

#endif /* LEDMGR_H */
