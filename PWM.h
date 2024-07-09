#ifndef PWM_H
#define PWM_H

#include "stm32f407xx.h"

// Estrutura para encapsular o PWM
typedef struct {
    TIM_HandleTypeDef htim;  // Estrutura do timer para o PWM
    uint32_t channel;  // Canal do PWM (1 a 4)
} PWM_TypeDef;

// Funções públicas

/**
 * @brief Inicializa o PWM com a frequência especificada.
 * 
 * @param pwm Ponteiro para a estrutura PWM_TypeDef que representa o PWM.
 * @param frequency Frequência desejada para o PWM em Hz.
 */
void PWM_Init(PWM_TypeDef *pwm, uint32_t frequency);

/**
 * @brief Ajusta o ciclo de trabalho do PWM.
 * 
 * @param pwm Ponteiro para a estrutura PWM_TypeDef que representa o PWM.
 * @param duty_cycle Ciclo de trabalho desejado (entre 0.0 e 1.0).
 */
void PWM_SetDutyCycle(PWM_TypeDef *pwm, float duty_cycle);

/**
 * @brief Inicia a geração do sinal PWM.
 * 
 * @param pwm Ponteiro para a estrutura PWM_TypeDef que representa o PWM.
 */
void PWM_Start(PWM_TypeDef *pwm);

/**
 * @brief Para a geração do sinal PWM.
 * 
 * @param pwm Ponteiro para a estrutura PWM_TypeDef que representa o PWM.
 */
void PWM_Stop(PWM_TypeDef *pwm);

#endif /* PWM_H */
