# Aspirador_Autonomo
Repositório para Trabalho da Disciplina de Arquitetura de Software

Organização dos Arquivos: Cada tipo de periférico (ADC, GPIO, PWM, LEDs) possui seu próprio par de arquivos .h e .c, facilitando a modularidade e a manutenção do código.

Integração na main.c: A main.c inclui apenas o arquivo hardware_proxy.h, que por sua vez inclui todos os headers necessários para os periféricos específicos.

Inicialização dos Periféricos: Cada periférico é inicializado usando suas respectivas funções de inicialização (Analog_Init, Digital_InitOutput, LED_Init, PWM_Init).

Exemplos de Utilização: Dentro do loop principal, são fornecidos exemplos de como ler do ADC, escrever em pinos digitais, controlar LEDs e configurar e usar o PWM.

Este exemplo demonstra como organizar e utilizar os arquivos hardware_proxy.h, analog.c, digital.c, pwm.c e ledmgr.c em uma aplicação STM32F407, promovendo modularidade e reutilização de código através do padrão de projeto Proxy de Hardware.
