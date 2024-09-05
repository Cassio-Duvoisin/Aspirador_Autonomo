/**
 * @file PWM.h
 * @brief Funções para controle de PWM.
 */

#ifndef PWM_H
#define PWM_H

#include "stm32f4xx_hal.h"

#define PWM_MIN 0
#define PWM_MAX 10000
#define DIST_MIN 0
#define DIST_MAX 100 // Máxima distância em cm


/**
 * @brief Inicializa o PWM.
 */
void PWM_Init(TIM_HandleTypeDef* tim, uint32_t Timer);

/**
 * @brief Define o ciclo de trabalho do PWM.
 * @param dutyCycle Ciclo de trabalho do PWM (0-100%).
 */
void PWM_SetDutyCycle(uint32_t dutyCycle,TIM_HandleTypeDef* tim, uint32_t Timer);


uint32_t Distance_ToPWM(float distance);
#endif
