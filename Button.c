#include "button.h"

/**
 * @brief Initializes the button GPIO pin.
 * 
 * This function initializes the GPIO pin connected to the onboard button.
 * It configures the pin as input with pull-up resistor enabled.
 */
void Button_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    // Enable the GPIO port clock
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Configure button GPIO pin
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;  // Button is normally pull-up
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * @brief Reads the current state of the button.
 * 
 * @return uint8_t The current state of the button (0 = not pressed, 1 = pressed).
 * 
 * This function reads the GPIO pin state to determine if the button is pressed or not.
 */
uint8_t Button_ReadState(void) {
    // Read the button GPIO pin state
    return HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN);
}
