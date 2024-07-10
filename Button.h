/**
 * @file button.h
 * @brief Funções para leitura do botão.
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "stm32f4xx_hal.h"

/**
 * @brief Inicializa o botão.
 */
void Button_Init(void);

/**
 * @brief Lê o estado do botão.
 * @return O estado do botão (GPIO_PIN_SET ou GPIO_PIN_RESET).
 */
GPIO_PinState Button_Read(void);

#endif
