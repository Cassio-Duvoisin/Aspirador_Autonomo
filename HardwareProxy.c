/**
 * @file hardwareproxy.c
 * @brief Implementação das funções de abstração de hardware.
 */

#include "hardwareproxy.h"

void HardwareProxy_Init(void) {
    Analog_Init();
    Digital_Init();
    LED_Init();
    PWM_Init();
    Button_Init();
}

uint32_t HardwareProxy_ReadAnalog(void) {
    return Analog_Read();
}

GPIO_PinState HardwareProxy_ReadDigital(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    return Digital_Read(GPIOx, GPIO_Pin);
}

void HardwareProxy_WriteDigital(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
    Digital_Write(GPIOx, GPIO_Pin, PinState);
}

void HardwareProxy_SetPWM(uint32_t dutyCycle) {
    PWM_SetDutyCycle(dutyCycle);
}

GPIO_PinState HardwareProxy_ReadButton(void) {
    return Button_Read();
}

void HardwareProxy_ToggleLED(uint16_t GPIO_Pin) {
    LED_Toggle(GPIO_Pin);
}

void HardwareProxy_SetLED(uint16_t GPIO_Pin, GPIO_PinState state) {
    if (state == GPIO_PIN_SET) {
        LED_On(GPIO_Pin);
    } else {
        LED_Off(GPIO_Pin);
    }
}
