#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
	
#define SET_BIT(REG, BIT) 	((REG) |= (BIT))
#define RESET_BIT(REG, BIT) ((REG) &= ~(BIT))


void Delay_ms(uint32_t delay);


#ifdef __cplusplus
}
#endif

#endif /* UTIL_H */
