#include "isr.h"

void isr_handler(isr_param_t params)
{
	printf("Ex %d : ", params.vector_num);
	switch(params.vector_num)
	{
		case 0:  printf("=0");    break; // Dividing by zero
		case 2:  printf(":3");    break; // NMI Interrupt
		case 3:  printf("^^");    break; // Breakpoint
		case 4:  printf(".__.");  break; // Overflow
		case 5:  printf("-__-");  break; // Bound Range Exceeded
		case 6:  printf("= 3 ="); break; // Invalid Opcode
		case 7:  printf("O__O");  break; // Device not avaliable
		case 8:  printf("o__O");  break; // Double fault
		case 9:  printf("O___o"); break; // Coprocessor segment overrun(reserved)
		case 10: printf(":I");    break; // Invalid TSS
		case 11: printf(":S");    break; // Segment not present
		case 12: printf(":S :S"); break; // Stack-segment fault
		case 13: printf(":G");    break; // General Protection
		case 14: printf(":P"); 	  break; // Page fault
		case 16: printf(":M");	  break; // Math Fault
		case 17: printf(":C");	  break; // Aligment check
		case 18: printf(":C :M"); break; // Machine Check
		case 19: printf(":F");    break; // SIMD Floating Point Exception
	}
	printf("\n");
}