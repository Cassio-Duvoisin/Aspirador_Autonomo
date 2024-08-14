#include "Interrupt_Handlers.h"


// Definição do pino de emergência
#define EMERGENCY_BUTTON_PORT GPIOC
#define EMERGENCY_BUTTON_PIN GPIO_PIN_13
#define EMERGENCY_BUTTON_IRQn EXTI15_10_IRQn

void EmergencyButton_IRQHandler(Blackboard* board) {
    // Verifica se a interrupção é do botão de emergência
    if (__HAL_GPIO_EXTI_GET_IT(EMERGENCY_BUTTON_PIN) != RESET) {
        // Limpa a interrupção
        __HAL_GPIO_EXTI_CLEAR_IT(EMERGENCY_BUTTON_PIN);

        // Desativa todos os periféricos
        Analog_DeInit(&board.Parameters.analog);
        Digital_DeInit(&board.Parameters.digital_in);
        Digital_DeInit(&board.Parameters.digital_out);
        PWM_Stop(&board.Parameters.pwm);
        LED_Off();

        // Loop infinito para manter o sistema desativado
        while(__HAL_GPIO_EXTI_GET_IT(EMERGENCY_BUTTON_PIN) != RESET) {
            // Mantém o sistema em estado seguro até que o botão seja liberado
            HAL_Delay(1000);  // Atraso para evitar sobrecarga do CPU
        }
    }
}
