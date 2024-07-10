#include "Observer.h"
#include "ButtonDriver.h"

Observer_Watcher_Type Observer_Reached_Target(Analog_TypeDef* analogPin, Digital_TypeDef* digitalPin) {
    
    Observer_Watcher_Type TARGET = IDLE;

    // verifica se o valor chegou no esperado
    if (analogPin != NULL) {
        if (Analog_Read(&analogPin, ADC_CHANNEL_0) >= 32768) { // uint16_t half value
            return REACH_TARGET;
        }
    } 
    else if (digitalPin != NULL) {
        if (Digital_Read(&digitalPin) == 1) { // HIGH value
            return REACH_TARGET;
        }
    } 
    else {
        printf("ERROR NO PIN CONFIGURED");
    }

    return TARGET;    
}
