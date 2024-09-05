/**
 * @file PWM.c
 * @brief Implementação das funções de controle de PWM para duas saídas.
 */

#include "PWM.h"

void PWM_Init(TIM_HandleTypeDef* tim, uint32_t Timer) {
    
    // Esse é o único timer usado no projeto
    if (tim.Instance != TIM4){
        __HAL_RCC_TIM4_CLK_ENABLE();

        tim.Instance = TIM4;
        tim.Init.Prescaler = 8399;
        tim.Init.CounterMode = TIM_COUNTERMODE_UP;
        tim.Init.Period = 9999;
        tim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        HAL_TIM_PWM_Init(&tim);

    }
    
    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 5000;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // Configurar o Canal 1
    HAL_TIM_PWM_ConfigChannel(&tim, &sConfigOC, Timer);
    HAL_TIM_PWM_Start(&tim, Timer);
}

void PWM_SetDutyCycle(uint32_t dutyCycle,TIM_HandleTypeDef* tim, uint32_t Timer) {
    __HAL_TIM_SET_COMPARE(tim, Timer, dutyCycle);
}

float PWM_ToDistance(uint32_t pwmValue) {
    if (pwmValue < PWM_MIN) pwmValue = PWM_MIN;
    if (pwmValue > PWM_MAX) pwmValue = PWM_MAX;
    
    // Conversão linear de PWM para distância
    float distance = (float)(pwmValue - PWM_MIN) * (DIST_MAX - DIST_MIN) / (PWM_MAX - PWM_MIN) + DIST_MIN;
    return distance;
}

uint32_t Distance_ToPWM(float distance) {
    if (distance < DIST_MIN) distance = DIST_MIN;
    if (distance > DIST_MAX) distance = DIST_MAX;
    
    // Conversão linear de distância para PWM
    uint32_t pwmValue = (uint32_t)((distance - DIST_MIN) * (PWM_MAX - PWM_MIN) / (DIST_MAX - DIST_MIN) + PWM_MIN);
    return pwmValue;
}
