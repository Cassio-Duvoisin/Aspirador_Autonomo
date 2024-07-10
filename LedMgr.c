/**
 * @file ledmgr.c
 * @brief Implementação das funções de controle de LEDs.
 */

#include "ledmgr.h"

void LED_Init(void) {
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void LED_On(uint16_t GPIO_Pin) {
    HAL_GPIO_WritePin(GPIOD, GPIO_Pin, GPIO_PIN_SET);
}

void LED_Off(uint16_t GPIO_Pin) {
    HAL_GPIO_WritePin(GPIOD, GPIO_Pin, GPIO_PIN_RESET);
}

void LED_Toggle(uint16_t GPIO_Pin) {
    HAL_GPIO_TogglePin(GPIOD, GPIO_Pin);
}
