/**
 * @file Motor.h
 * @brief Funções para gerenciamento de observadores (Observer Pattern).
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include "HardwareProxy.h"

typedef enum{
    LEFT,
    RIGHT,
    NONE
}Turning_Type;

typedef struct Motor{
    TIM_HandleTypeDef Left_Wheel;
    TIM_HandleTypeDef Right_Wheel;
    Turning_Type      Last_Rotation;
    uint32_t          Left_Wheel_Timer;
    uint32_t          Right_Wheel_Timer;
}Motor_Type;

/**
 * @brief Tipo de callback para observadores.
 */
void Motor_Init(TIM_HandleTypeDef* tim, uint32_t Timer1,uint32_t Timer2);

/**
 * @brief Registra um observador.
 * @param callback Função de callback do observador.
 */
void Motor_Run(Blackboard_Type* board);

/**
 * @brief Notifica todos os observadores registrados.
 */
void Motor_Turn(Blackboard_Type* board);

#endif
