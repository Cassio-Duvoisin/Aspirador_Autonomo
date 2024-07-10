#include "Digital.h"

// Função para inicializar um pino como entrada
void Digital_InitInput(Digital_TypeDef *digital)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Configuração do pino como entrada
    GPIO_InitStruct.Pin = digital->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(digital->port, &GPIO_InitStruct);
}

// Função para inicializar um pino como saída
void Digital_InitOutput(Digital_TypeDef *digital, GPIO_PinState initial_state)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Configuração do pino como saída
    GPIO_InitStruct.Pin = digital->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(digital->port, &GPIO_InitStruct);

    // Define o estado inicial do pino
    HAL_GPIO_WritePin(digital->port, digital->pin, initial_state);
}

// Função para ler o estado de um pino digital
GPIO_PinState Digital_Read(Digital_TypeDef *digital)
{
    return HAL_GPIO_ReadPin(digital->port, digital->pin);
}

// Função para escrever um estado em um pino digital
void Digital_Write(Digital_TypeDef *digital, GPIO_PinState state)
{
    HAL_GPIO_WritePin(digital->port, digital->pin, state);
}

// Função para habilitar interrupção em um pino digital
void Digital_EnableInterrupt(Digital_TypeDef *digital, void (*callback)(void))
{
    // Configuração da interrupção
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);  // Prioridade da interrupção (ajuste conforme necessário)
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);  // Habilita a interrupção EXTI0

    // Configuração do pino para interrupção externa
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = digital->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;  // Exemplo: Interrupção em borda de subida e descida
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(digital->port, &GPIO_InitStruct);

    // Associação da função de callback à interrupção
    //HAL_GPIO_RegisterCallback(&digital->port, HAL_GPIO_EXTI_Callback_IT, callback);
}
