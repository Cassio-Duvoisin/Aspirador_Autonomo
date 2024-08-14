/**
 * @file main.c
 * @brief Função principal do programa.
 */

#include "SystemConfig.h"
#include "HardwareProxy.h"
#include "Observer.h"

/**
 * @brief Callback para notificação de 50% do PWM.
 */
void PWM_50PercentCallback(void);

int main(void) {
    HAL_Init();  // Inicializa o HAL
    SystemClock_Config();  // Configura o clock do sistema
    HardwareProxy_Init();  // Inicializa todos os componentes de hardware

    RegisterObserver(PWM_50PercentCallback);  // Registra o callback para PWM

    uint32_t analogValue = 0;
    GPIO_PinState digitalState;
    uint32_t pwmValue = 0;  // Valor inicial do PWM

    while (1) {
        // Incrementa o valor do PWM a cada 1%
        pwmValue = (pwmValue + 100) % 10000;  // Incrementa 1% e reinicia após 100%
        HardwareProxy_SetPWM(pwmValue);  // Define o PWM

        // Adiciona um pequeno delay
        HAL_Delay(10);  // Delay de 10 ms

        // Leitura do valor analógico
        analogValue = HardwareProxy_ReadAnalog();
        // Leitura do estado do pino digital
        digitalState = HardwareProxy_ReadDigital(GPIOD, GPIO_PIN_0);

        // Verifica se o botão foi pressionado para alternar o LED
        if (HardwareProxy_ReadButton() == GPIO_PIN_SET) {
            HardwareProxy_ToggleLED(GPIO_PIN_12);  // Alterna o estado do LED verde
        }

        // Controla o estado dos LEDs azul e verde com base no estado do pino digital
        if (digitalState == GPIO_PIN_SET) {
            HardwareProxy_SetLED(GPIO_PIN_13, GPIO_PIN_SET);  // Liga o LED azul
        } else {
            HardwareProxy_SetLED(GPIO_PIN_13, GPIO_PIN_RESET);  // Desliga o LED azul
        }

        // Notifica observadores se o PWM estiver em 50%
        if (pwmValue >= 5000 && pwmValue < 5100) {
            NotifyObservers();  // Notifica todos os observadores registrados
        }
    }
}

/**
 * @brief Callback para quando o PWM atinge 50%.
 *
 * Alterna o estado do LED vermelho.
 */
void PWM_50PercentCallback(void) {
    HardwareProxy_ToggleLED(GPIO_PIN_14);  // Alterna o estado do LED vermelho
}
