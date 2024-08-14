/**
 * @file PWM.c
 * @brief Implementação das funções de controle de PWM.
 */

#include "PWM.h"

TIM_HandleTypeDef htim4;

void PWM_Init(void) {
    __HAL_RCC_TIM4_CLK_ENABLE();

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 8399;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 9999;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim4);

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 5000;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

void PWM_SetDutyCycle(uint32_t dutyCycle) {
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, dutyCycle);
}
