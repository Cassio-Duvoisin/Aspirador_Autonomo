/**
 * @file HardwareProxy.c
 * @brief Implementação das funções de abstração de hardware.
 */

#include "HardwareProxy.h"

void HardwareProxy_Init(Blackboard_Type* board) {
    
    board.battery_pin->Instance = ADC1;
    board.distance_pin->Instance = ADC2;
    
    Analog_Init(&board.battery_pin);
    Analog_Init(&board.distance_pin);
    
    Digital_Init();
    LED_Init();
    Button_Init();
}

uint32_t HardwareProxy_ReadAnalog(ADC_HandleTypeDef* hadc) {
    return Analog_Read(&hadc);
}

GPIO_PinState HardwareProxy_ReadDigital(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    return Digital_Read(GPIOx, GPIO_Pin);
}

void HardwareProxy_WriteDigital(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
    Digital_Write(GPIOx, GPIO_Pin, PinState);
}

void HardwareProxy_SetPWM(uint32_t dutyCycle,TIM_HandleTypeDef* tim, uint32_t Timer) {
    PWM_SetDutyCycle(dutyCycle, tim, Timer);
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
