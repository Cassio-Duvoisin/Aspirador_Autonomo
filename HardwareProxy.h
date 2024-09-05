/**
 * @file HardwareProxy.h
 * @brief Funções para abstração de hardware (Hardware Proxy Pattern).
 */

#ifndef HARDWAREPROXY_H
#define HARDWAREPROXY_H

#include "Analog.h"
#include "Digital.h"
#include "LedMgr.h"
#include "PWM.h"
#include "Button.h"

// Estruturas de Abstração de Periféricos
typedef struct Pin{

}Pin_Type;
typedef struct Blackboard{
    ADC_HandleTypeDef battery_pin;
    ADC_HandleTypeDef distance_pin;

    uint32_t adc_value;
    uint32_t adc_value_2;
    uint32_t adc_value_3;           // Usando para verificar a porcentagem da bateria
    uint32_t pwmValue;
    GPIO_PinState button_state;
    GPIO_PinState digital_state_1;
    GPIO_PinState digital_state_2;  //

}Blackboard_Type;

#define MAX_PROXIMITY_SENSOR_DISTANCE   2

#define MOTOR_TURNING_DISTACE           2

/**
 * @brief Inicializa todos os componentes de hardware.
 */
void HardwareProxy_Init(Blackboard_Type* board);

/**
 * @brief Lê o valor analógico.
 * @return O valor lido.
 */
uint32_t HardwareProxy_ReadAnalog(void);

/**
 * @brief Lê o estado de um pino digital.
 * @param GPIOx Ponteiro para a porta GPIO.
 * @param GPIO_Pin Pino GPIO.
 * @return O estado do pino digital.
 */
GPIO_PinState HardwareProxy_ReadDigital(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
 * @brief Escreve um estado em um pino digital.
 * @param GPIOx Ponteiro para a porta GPIO.
 * @param GPIO_Pin Pino GPIO.
 * @param PinState Estado a ser escrito no pino.
 */
void HardwareProxy_WriteDigital(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

/**
 * @brief Define o ciclo de trabalho do PWM.
 * @param dutyCycle Ciclo de trabalho do PWM (0-100%).
 */
void HardwareProxy_SetPWM(uint32_t dutyCycle,TIM_HandleTypeDef* tim, uint32_t Timer);

/**
 * @brief Lê o estado do botão.
 * @return O estado do botão (GPIO_PIN_SET ou GPIO_PIN_RESET).
 */
GPIO_PinState HardwareProxy_ReadButton(void);

/**
 * @brief Alterna o estado de um LED.
 * @param GPIO_Pin Pino do LED a ser alternado.
 */
void HardwareProxy_ToggleLED(uint16_t GPIO_Pin);

/**
 * @brief Define o estado de um LED.
 * @param GPIO_Pin Pino do LED a ser definido.
 * @param state Estado a ser definido (GPIO_PIN_SET ou GPIO_PIN_RESET).
 */
void HardwareProxy_SetLED(uint16_t GPIO_Pin, GPIO_PinState state);

#endif
