#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#define RCC_AHB1ENR		(*((volatile uint32_t *) 0x40023830)) // RCC_AHB1ENR register memory address
#define GPIOD_MODER		(*((volatile uint32_t *) 0x40020C00)) // RCC_MODER register memory address
#define GPIOD_BSRR    (*((volatile uint32_t *) 0x40020C18)) // RCC_BSRR  register memory address
#define GPIOA_MODER 	(*((volatile uint32_t *) 0x40020000))
#define GPIOA_IDR   	(*((volatile uint32_t *) 0x40020010))

#define RCC_AHB1ENR_GPIOD_ENABLE		(1<<3)
#define RCC_AHB1ENR_GPIOD_DISABLED 	(0<<3)

#define RCC_AHB1ENR_GPIOA_ENABLE 		(1<<0)
#define RCC_AHB1ENR_GPIOA_DISABLED  (0<<0)

#define GPIOD_MODER_PIN12_OUTPUT 	  (1<<24)
#define GPIOD_MODER_PIN13_OUTPUT 	  (1<<26)
#define GPIOD_MODER_PIN14_OUTPUT 	  (1<<28)
#define GPIOD_MODER_PIN15_OUTPUT 	  (1<<30)

#define GPIOA_MODER_PIN0_INPUT 		  (0<<0)

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_MAP_H */
