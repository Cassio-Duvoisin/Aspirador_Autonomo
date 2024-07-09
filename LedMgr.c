#include "LedMgr.h"

// Função para inicializar os LEDs
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Inicialização do Clock do Port D
    __HAL_RCC_GPIOD_CLK_ENABLE();

    // Configuração dos pinos dos LEDs como saída
    GPIO_InitStruct.Pin = LED_RED_PIN | LED_ORANGE_PIN | LED_BLUE_PIN | LED_GREEN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

// Função para controlar os LEDs
void LED_On(GPIO_PinState state, GPIO_PinState state1, GPIO_PinState state2, GPIO_PinState state3)
{
    HAL_GPIO_WritePin(GPIOD, LED_RED_PIN, state);
    HAL_GPIO_WritePin(GPIOD, LED_ORANGE_PIN, state1);
    HAL_GPIO_WritePin(GPIOD, LED_BLUE_PIN, state2);
    HAL_GPIO_WritePin(GPIOD, LED_GREEN_PIN, state3);
}
