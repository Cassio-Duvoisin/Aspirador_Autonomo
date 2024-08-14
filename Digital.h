/**
 * @file Digital.h
 * @brief Funções para leitura e escrita de sinais digitais.
 */

#ifndef DIGITAL_H
#define DIGITAL_H

#include "stm32f4xx_hal.h"

/**
 * @brief Inicializa os pinos digitais.
 */
void Digital_Init(void);

/**
 * @brief Lê o estado de um pino digital.
 * @param GPIOx Ponteiro para a porta GPIO.
 * @param GPIO_Pin Pino GPIO.
 * @return O estado do pino digital.
 */
GPIO_PinState Digital_Read(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
 * @brief Escreve um estado em um pino digital.
 * @param GPIOx Ponteiro para a porta GPIO.
 * @param GPIO_Pin Pino GPIO.
 * @param PinState Estado a ser escrito no pino.
 */
void Digital_Write(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

#endif
