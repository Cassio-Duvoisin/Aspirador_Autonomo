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
void LED_On(GPIO_PinState led_red, GPIO_PinState led_orange, GPIO_PinState led_blue, GPIO_PinState led_green)
{
    HAL_GPIO_WritePin(GPIOD, LED_RED_PIN, led_red);
    HAL_GPIO_WritePin(GPIOD, LED_ORANGE_PIN, led_orange);
    HAL_GPIO_WritePin(GPIOD, LED_BLUE_PIN, led_blue);
    HAL_GPIO_WritePin(GPIOD, LED_GREEN_PIN, led_green);
}

// Função para alternar o estado de um LED
void LED_Toggle(uint16_t led_pin)
{
    HAL_GPIO_TogglePin(GPIOD, led_pin);
}
