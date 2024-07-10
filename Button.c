/**
 * @file Button.c
 * @brief Implementação das funções de leitura do botão.
 */

#include "Button.h"

void Button_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

GPIO_PinState Button_Read(void) {
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
}
