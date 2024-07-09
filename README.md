# Projeto STM32F407 Hardware Proxy

Este projeto é um exemplo de utilização de um padrão de Proxy de Hardware para o microcontrolador STM32F407, utilizando a HAL (Hardware Abstraction Layer) do STM32CubeMX para abstrair o acesso aos periféricos.

Organização dos Arquivos: Cada tipo de periférico (ADC, GPIO, PWM, LEDs) possui seu próprio par de arquivos .h e .c, facilitando a modularidade e a manutenção do código.
Integração na main.c: A main.c inclui apenas o arquivo hardware_proxy.h, que por sua vez inclui todos os headers necessários para os periféricos específicos.
Inicialização dos Periféricos: Cada periférico é inicializado usando suas respectivas funções de inicialização (Analog_Init, Digital_InitOutput, LED_Init, PWM_Init).

## Descrição

O objetivo deste projeto é fornecer uma estrutura modularizada e organizada para controlar periféricos como ADC, GPIO (pino digital), PWM e LEDs no STM32F407. Cada periférico tem suas funções encapsuladas em arquivos separados (`analog.c`, `digital.c`, `pwm.c`, `ledmgr.c`), facilitando a manutenção e a reutilização de código.

## Estrutura do Projeto

- `analog.c` e `analog.h`: Funções para inicialização e leitura do ADC.
- `digital.c` e `digital.h`: Funções para controle de pinos digitais (GPIO).
- `pwm.c` e `pwm.h`: Funções para configuração e controle de PWM.
- `ledmgr.c` e `ledmgr.h`: Funções para controle dos LEDs.
- `hardware_proxy.h`: Arquivo header principal que inclui todos os headers dos periféricos.

## Pré-requisitos

- STM32CubeMX configurado com o HAL para o STM32F407.
- Compilador e ambiente de desenvolvimento para STM32.

## Configuração

1. Clone o repositório para sua máquina local:

    ```
    git clone https://github.com/seu-usuario/projeto-stm32f407-hardware-proxy.git
    ```

2. Abra o projeto em seu ambiente de desenvolvimento.

3. Configure o projeto STM32F407 no STM32CubeMX conforme necessário para seu hardware específico.

4. Compile o projeto e carregue-o no microcontrolador STM32F407.

## Uso

Exemplos de Utilização: Dentro do loop principal, são fornecidos exemplos de como ler do ADC, escrever em pinos digitais, controlar LEDs e configurar e usar o PWM.
Este exemplo demonstra como organizar e utilizar os arquivos hardware_proxy.h, analog.c, digital.c, pwm.c e ledmgr.c em uma aplicação STM32F407, promovendo modularidade e reutilização de código através do padrão de projeto Proxy de Hardware.

- Inclua o arquivo `hardware_proxy.h` em sua `main.c` para acessar as funções encapsuladas de cada periférico.
- Use as funções `Analog_Init`, `Digital_InitOutput`, `LED_Init`, `PWM_Init` para inicializar os periféricos desejados.
- Utilize as funções correspondentes (como `Analog_Read`, `Digital_Write`, `LED_On`, `PWM_SetDutyCycle`, etc.) para controlar e interagir com os periféricos.

Exemplo básico de uso na `main.c`:

```c
#include "hardware_proxy.h"

int main(void)
{
    // Inicialização dos periféricos...

    while (1)
    {
        // Exemplos de utilização dos periféricos...

        HAL_Delay(1000);
    }
}
