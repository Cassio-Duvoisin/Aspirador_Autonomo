/**
 * @file BMS.c
 * @brief Implementação das funções de Monitoramento da bateria.
 */

#include "BMS.h"
#include "HardwareProxy.h"

void BMS_BatteryCheck(Blackboard_Type* board) {

    if (board.adc_value3 <= BATTERY_THERSHOLD_LOW && board.adc_value3 > BATTERY_THERSHOLD_CRITICAL)
    {
        HardwareProxy_SetLED(GPIO_PIN_13, GPIO_PIN_SET);
    }
    else if (board.adc_value3 <= BATTERY_THERSHOLD_CRITICAL && board.adc_value3 > BATTERY_THERSHOLD_CHARGE)
    {
        HardwareProxy_SetLED(GPIO_PIN_12, GPIO_PIN_SET);
        HardwareProxy_SetLED(GPIO_PIN_13, GPIO_PIN_RESET);
    }
    else if (board.adc_value3 <=BATTERY_THERSHOLD_CHARGE)
    {
        HardwareProxy_SetLED(GPIO_PIN_12, GPIO_PIN_SET);
        HardwareProxy_SetLED(GPIO_PIN_13, GPIO_PIN_RESET);
        BatteryCharge(&board);
    }
    
}

void BatteryCharge(Blackboard_Type* board){


    while (board.adc_value3 < 50)
    {
        board.adc_value3 = HardwareProxy_ReadAnalog(board.analog_pin);
    }
}
