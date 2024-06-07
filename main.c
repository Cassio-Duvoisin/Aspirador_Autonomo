#include <stdint.h>

// Definições de registradores e bits
#define RCC_AHB1ENR (*((volatile uint32_t *)0x40023830)) // Endereço do registrador RCC_AHB1ENR
#define GPIOD_MODER (*((volatile uint32_t *)0x40020C00)) // Endereço do registrador MODER do porto D
#define GPIOD_BSRR (*((volatile uint32_t *)0x40020C18)) // Endereço do registrador BSRR do porto D
#define GPIOA_MODER (*((volatile uint32_t *)0x40020000)) // Endereço do registrador MODER do porto A
#define GPIOA_IDR   (*((volatile uint32_t *)0x40020010)) // Endereço do registrador IDR do porto A

#define RCC_AHB1ENR_GPIODEN (1<<3) // Bit de habilitação do GPIO Port D
#define RCC_AHB1ENR_GPIOAEN (1<<0) // Bit de habilitação do GPIO Port A

#define GPIO_MODER_MODER12_0 (1<<24) // Configura o pino 12 do porto D como saída
#define GPIO_MODER_MODER13_0 (1<<26) // Configura o pino 13 do porto D como saída
#define GPIO_MODER_MODER14_0 (1<<28) // Configura o pino 14 do porto D como saída
#define GPIO_MODER_MODER15_0 (1<<30) // Configura o pino 15 do porto D como saída

#define GPIO_MODER_MODER0_INPUT (0<<0) // Configura o pino 0 do porto A como entrada

void delay(uint32_t time) {
    for(uint32_t i=0; i<time; i++);
}

int main(void) {
    // Habilita o clock para o GPIO Port D e Port A
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN;

    // Configura os pinos 12, 13, 14 e 15 do porto D como saída
    GPIOD_MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;

    // Configura o pino 0 do porto A como entrada
    GPIOA_MODER &= ~GPIO_MODER_MODER0_INPUT;

    // Pequeno delay para garantir a configuração dos pinos
    delay(100000);

    // Variável para controlar o estado dos LEDs (ligado/desligado)
    uint8_t leds_ligados = 0;

    // Variável para armazenar o estado anterior do botão
    uint8_t botao_pressionado_anterior = 0;

    /* Loop infinito */
    while(1) {
        // Leitura do estado do botão (pino 0 do porto A)
        uint8_t botao_pressionado = (GPIOA_IDR & 0x01);

        // Verifica se o botão foi pressionado (bordo de subida)
        if (botao_pressionado && !botao_pressionado_anterior) {
            leds_ligados = !leds_ligados; // Alterna o estado dos LEDs
            delay(100000); // Debounce delay para evitar múltiplas leituras rápidas
        }

        // Atualiza o estado anterior do botão
        botao_pressionado_anterior = botao_pressionado;

        if (leds_ligados) {
            // Liga todos os LEDs
            GPIOD_BSRR = (1 << 12) | (1 << 13) | (1 << 14) | (1 << 15);
            delay(1000000); // Espera

            // Desliga todos os LEDs
            GPIOD_BSRR = ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15)) << 16;
            delay(1000000); // Espera
        } else {
            // Desliga todos os LEDs (garantia de que estão desligados)
            GPIOD_BSRR = ((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15)) << 16;
        }
    }
}
