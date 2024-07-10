/**
 * @file pwm.h
 * @brief Funções para controle de PWM.
 */

#ifndef PWM_H
#define PWM_H

#include "stm32f4xx_hal.h"

/**
 * @brief Inicializa o PWM.
 */
void PWM_Init(void);

/**
 * @brief Define o ciclo de trabalho do PWM.
 * @param dutyCycle Ciclo de trabalho do PWM (0-100%).
 */
void PWM_SetDutyCycle(uint32_t dutyCycle);

#endif
