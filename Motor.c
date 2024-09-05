/**
 * @file Motor.c
 * @brief Implementação das funções de controle do Motor do AMR.
 */

#include "Motor.h"

Motor_Type Motor;

void Motor_Init(TIM_HandleTypeDef* tim, uint32_t Timer1, uint32_t Timer2){
    Motor.Last_Rotation = NONE;
    Motor.Left_Wheel = PWM_Init(tim, Timer1);
    Motor.Right_Wheel = PWM_Init(tim, Timer2);
    Motor.Left_Wheel_Timer = Timer1;
    Motor.Right_Wheel_Timer = Timer2;
}

void Motor_Run(Blackboard_Type* board) {
    
    if (board.adc_value <= MAX_PROXIMITY_SENSOR_DISTANCE)
    {
        board.pwmValue = PWM_MAX/4;
        Motor_Turn(&board);
        board.pwmValue = Distance_ToPWM(MOTOR_TURNING_DISTACE);
        Motor_Run(&board);
        board.pwmValue = PWM_MAX/4;
        Motor_Turn(&board);
    }
    
    blackboard.pwmValue = PWM_MAX/2;
    HardwareProxy_SetPWM(board.pwmValue,&Motor.Left_Wheel,&Motor.Left_Wheel_Timer);
    HardwareProxy_SetPWM(-(board.pwmValue),&Motor.Right_Wheel,&Motor.Right_Wheel_Timer);
}

void Motor_Turn(Blackboard_Type* board) {

    if (Motor.Last_Rotation = LEFT ||Motor.Last_Rotation = NONE ){
        HardwareProxy_SetPWM(board.pwmValue,&Motor.Left_Wheel,&Motor.Left_Wheel_Timer);
        HardwareProxy_SetPWM((board.pwmValue),&Motor.Right_Wheel,&Motor.Right_Wheel_Timer);
        Motor.Last_Rotation = RIGHT;
        HAL_Delay(1000);
    }
    else if (Motor.Last_Rotation = RIGHT ){
        HardwareProxy_SetPWM(-(board.pwmValue),&Motor.Left_Wheel,&Motor.Left_Wheel_Timer);
        HardwareProxy_SetPWM(-(board.pwmValue),&Motor.Right_Wheel,&Motor.Right_Wheel_Timer);
        Motor.Rotation = LEFT;
        HAL_Delay(1000);
    }
}
