#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

#include "stm32f4xx_hal.h"
#include "Hardware_Proxy.h"

/**
 * @brief Manipulador de interrupção para o botão de emergência.
 * 
 * Esta função é chamada quando uma interrupção é gerada pelo botão de emergência.
 * Ela verifica se a interrupção pertence ao botão de emergência e, em caso afirmativo,
 * limpa a interrupção e desativa todos os periféricos do sistema para garantir um estado seguro.
 * O sistema permanece em um loop infinito, mantendo tudo desativado enquanto o botão
 * continua pressionado, garantindo que não haja reativação inadvertida do sistema.
 */
void EmergencyButton_IRQHandler(void);

#endif // INTERRUPT_HANDLERS_H
