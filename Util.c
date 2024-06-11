#include "util.h"

void Delay_ms(uint32_t delay)
{
	for(uint32_t count=0; count<delay*4000; count++);
}
