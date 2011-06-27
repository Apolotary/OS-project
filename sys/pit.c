#include "pit.h"

int counter = 0; 

static void test_pit(isr_param_t params)
{
	k_printf("Tick #%d\r", counter++);
}

void init_pit(uint32_t frequency)
{
	uint32_t divisor;
	register_interrupt_handler(32, &test_pit);
	
	divisor = 1193182 / frequency;
	
	outb(0x43, 0x36);
	outb(0x40, ((uint8_t) divisor & 0xFF));
	outb(0x40, ((uint8_t) (divisor >> 8)& 0xFF));
	
}