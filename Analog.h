/**
 * @file Analog.h
 * @brief Funções para leitura de sinal analógico.
 */

#ifndef ANALOG_H
#define ANALOG_H

#include "stm32f4xx_hal.h"

/**
 * @brief Inicializa o ADC para leitura analógica.
 */
void Analog_Init(ADC_HandleTypeDef* hadc, uint32_t channel);

/**
 * @brief Lê o valor analógico do ADC.
 * @return O valor lido do ADC.
 */
uint32_t Analog_Read(ADC_HandleTypeDef* hadc);

#endif
