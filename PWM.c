#include "PWM.h"

// Função para inicializar o PWM
void PWM_Init(PWM_TypeDef *pwm, uint32_t frequency)
{
    // Configuração do timer para o PWM
    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    pwm->htim.Instance = TIM2;  // Exemplo: TIM2
    pwm->htim.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() / 1000000) - 1;  // Prescaler para microsegundos
    pwm->htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    pwm->htim.Init.Period = 1000000 / frequency - 1;  // Frequência desejada em Hz
    pwm->htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&(pwm->htim));

    // Configuração do canal PWM
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&(pwm->htim), &sConfigOC, pwm->channel);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&(pwm->htim), &sMasterConfig);
}

// Função para ajustar o ciclo de trabalho do PWM (0.0 - 1.0)
void PWM_SetDutyCycle(PWM_TypeDef *pwm, float duty_cycle)
{
    uint32_t pulse = (pwm->htim.Init.Period + 1) * duty_cycle;
    HAL_TIM_PWM_Stop(&(pwm->htim), pwm->channel);
    __HAL_TIM_SET_COMPARE(&(pwm->htim), pwm->channel, pulse);
    HAL_TIM_PWM_Start(&(pwm->htim), pwm->channel);
}

// Função para iniciar o PWM
void PWM_Start(PWM_TypeDef *pwm)
{
    HAL_TIM_PWM_Start(&(pwm->htim), pwm->channel);
}

// Função para parar o PWM
void PWM_Stop(PWM_TypeDef *pwm)
{
    HAL_TIM_PWM_Stop(&(pwm->htim), pwm->channel);
}
