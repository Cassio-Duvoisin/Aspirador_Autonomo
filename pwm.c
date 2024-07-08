#include <stdint.h>

// Definições de registradores e bits
#define RCC_AHB1ENR (*((volatile uint32_t *)0x40023830)) // Endereço do registrador RCC_AHB1ENR
#define RCC_APB2ENR (*((volatile uint32_t *)0x40023844)) // Endereço do registrador RCC_APB2ENR
#define RCC_APB1ENR (*((volatile uint32_t *)0x40023840)) // Endereço do registrador RCC_APB1ENR

#define GPIOD_MODER (*((volatile uint32_t *)0x40020C00)) // Endereço do registrador MODER do porto D
#define GPIOD_AFRH  (*((volatile uint32_t *)0x40020C24)) // Endereço do registrador AFRH do porto D

#define GPIOA_MODER (*((volatile uint32_t *)0x40020000)) // Endereço do registrador MODER do porto A
#define GPIOA_PUPDR (*((volatile uint32_t *)0x4002000C)) // Endereço do registrador PUPDR do porto A

#define ADC1_SR     (*((volatile uint32_t *)0x40012000)) // Endereço do registrador SR do ADC1
#define ADC1_CR1    (*((volatile uint32_t *)0x40012004)) // Endereço do registrador CR1 do ADC1
#define ADC1_CR2    (*((volatile uint32_t *)0x40012008)) // Endereço do registrador CR2 do ADC1
#define ADC1_SMPR2  (*((volatile uint32_t *)0x40012010)) // Endereço do registrador SMPR2 do ADC1
#define ADC1_SQR3   (*((volatile uint32_t *)0x40012034)) // Endereço do registrador SQR3 do ADC1
#define ADC1_DR     (*((volatile uint32_t *)0x4001204C)) // Endereço do registrador DR do ADC1

#define TIM4_CR1    (*((volatile uint32_t *)0x40000800)) // Endereço do registrador CR1 do TIM4
#define TIM4_CCMR1  (*((volatile uint32_t *)0x40000818)) // Endereço do registrador CCMR1 do TIM4
#define TIM4_CCMR2  (*((volatile uint32_t *)0x4000081C)) // Endereço do registrador CCMR2 do TIM4
#define TIM4_CCER   (*((volatile uint32_t *)0x40000820)) // Endereço do registrador CCER do TIM4
#define TIM4_PSC    (*((volatile uint32_t *)0x40000828)) // Endereço do registrador PSC do TIM4
#define TIM4_ARR    (*((volatile uint32_t *)0x4000082C)) // Endereço do registrador ARR do TIM4
#define TIM4_CCR1   (*((volatile uint32_t *)0x40000834)) // Endereço do registrador CCR1 do TIM4
#define TIM4_CCR2   (*((volatile uint32_t *)0x40000838)) // Endereço do registrador CCR2 do TIM4
#define TIM4_CCR3   (*((volatile uint32_t *)0x4000083C)) // Endereço do registrador CCR3 do TIM4
#define TIM4_CCR4   (*((volatile uint32_t *)0x40000840)) // Endereço do registrador CCR4 do TIM4

#define RCC_AHB1ENR_GPIODEN (1<<3) // Bit de habilitação do GPIO Port D
#define RCC_AHB1ENR_GPIOAEN (1<<0) // Bit de habilitação do GPIO Port A
#define RCC_APB2ENR_ADC1EN  (1<<8) // Bit de habilitação do ADC1
#define RCC_APB1ENR_TIM4EN  (1<<2) // Bit de habilitação do TIM4

#define GPIO_MODER_MODER12_0 (1<<24) // Configura o pino 12 do porto D como saída
#define GPIO_MODER_MODER13_1 (1<<27) // Configura o pino 13 do porto D como função alternativa
#define GPIO_MODER_MODER15_1 (1<<31) // Configura o pino 15 do porto D como função alternativa

#define GPIO_AFRH_AFRH13_AF2 (2<<20) // Configura o pino 13 do porto D como TIM4_CH2
#define GPIO_AFRH_AFRH15_AF2 (2<<28) // Configura o pino 15 do porto D como TIM4_CH4

void delay(uint32_t time) {
    for(uint32_t i=0; i<time; i++);
}

void adc_init(void) {
    // Habilita o clock para o ADC1
    RCC_APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Configura o pino PA0 como entrada analógica
    GPIOA_MODER |= (3<<0); // PA0 em modo analógico

    // Configura o ADC
    ADC1_CR1 = 0x00;        // Reset CR1
    ADC1_CR2 = 0x00;        // Reset CR2
    ADC1_SMPR2 |= (7<<0);   // Tempo de amostragem para canal 0
    ADC1_SQR3 |= (0<<0);    // Canal 0 é o primeiro na sequência regular
    ADC1_CR2 |= (1<<10);    // Habilita EOCS (fim de conversão)
    ADC1_CR2 |= (1<<0);     // Habilita o ADC
}

uint16_t adc_read(void) {
    ADC1_CR2 |= (1<<30);    // Inicia a conversão
    while (!(ADC1_SR & (1<<1))); // Espera a conversão terminar
    return ADC1_DR;         // Retorna o valor convertido
}

void tim4_pwm_init(void) {
    // Habilita o clock para o TIM4
    RCC_APB1ENR |= RCC_APB1ENR_TIM4EN;

    // Configura os pinos PD13 e PD15 como função alternativa
    GPIOD_MODER |= GPIO_MODER_MODER13_1 | GPIO_MODER_MODER15_1;
    GPIOD_AFRH |= GPIO_AFRH_AFRH13_AF2 | GPIO_AFRH_AFRH15_AF2;

    // Configura o TIM4 para PWM
    TIM4_PSC = 1600 - 1;    // Prescaler
    TIM4_ARR = 1000 - 1;    // Auto-reload register

    // Configura os canais 2 e 4 para PWM modo 1
    TIM4_CCMR1 |= (6<<12);  // PWM mode 1 no canal 2 (PD13)
    TIM4_CCMR2 |= (6<<12);  // PWM mode 1 no canal 4 (PD15)

    // Habilita os canais 2 e 4
    TIM4_CCER |= (1<<4) | (1<<12);

    // Habilita o TIM4
    TIM4_CR1 |= (1<<0);
}

int main(void) {
    // Habilita o clock para o GPIO Port D e Port A
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN;

    // Inicializa o ADC
    adc_init();

    // Inicializa o PWM
    tim4_pwm_init();

    // Variável para armazenar o valor do ADC
    uint16_t adc_value;

    /* Loop infinito */
    while(1) {
        // Lê o valor do ADC
        adc_value = adc_read();

        // Ajusta o duty cycle do PWM com base no valor do ADC
        TIM4_CCR2 = adc_value; // Ajusta o PWM no canal 2 (PD13 - LED laranja)
        TIM4_CCR4 = adc_value; // Ajusta o PWM no canal 4 (PD15 - LED azul)

        delay(10000); // Pequeno delay para estabilizar a leitura
    }
}


