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


#ifdef __cplusplus
}
#endif

#endif /* MEMORY_MAP_H */
