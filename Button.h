#ifndef BUTTON_H
#define BUTTON_H

#include "stm32f4xx_hal.h"

/**
 * @brief GPIO port and pin configuration for the onboard button.
 * 
 * Define the GPIO port and pin number where the onboard button is connected.
 */
#define BUTTON_GPIO_PORT    GPIOC
#define BUTTON_PIN          GPIO_PIN_13

/**
 * @brief Initializes the button GPIO pin.
 * 
 * This function initializes the GPIO pin connected to the onboard button.
 * It configures the pin as input with pull-up resistor enabled.
 */
void Button_Init(void);

/**
 * @brief Reads the current state of the button.
 * 
 * @return uint8_t The current state of the button (0 = not pressed, 1 = pressed).
 * 
 * This function reads the GPIO pin state to determine if the button is pressed or not.
 */
uint8_t Button_ReadState(void);

#endif /* BUTTON_H */
