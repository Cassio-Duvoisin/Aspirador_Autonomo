/**
 * @file LedMgr.h
 * @brief Funções para controle de LEDs.
 */

#ifndef LEDMGR_H
#define LEDMGR_H

#include "stm32f4xx_hal.h"

/**
 * @brief Inicializa os LEDs.
 */
void LED_Init(void);

/**
 * @brief Liga um LED.
 * @param GPIO_Pin Pino do LED a ser ligado.
 */
void LED_On(uint16_t GPIO_Pin);

/**
 * @brief Desliga um LED.
 * @param GPIO_Pin Pino do LED a ser desligado.
 */
void LED_Off(uint16_t GPIO_Pin);

/**
 * @brief Alterna o estado de um LED.
 * @param GPIO_Pin Pino do LED a ser alternado.
 */
void LED_Toggle(uint16_t GPIO_Pin);

#endif
