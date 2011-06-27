#include "idt.h"
#include "../isr.h"
extern void load_idt(uint32_t);

void idt_set_descriptor(uint32_t index, uint32_t offset, uint16_t segment_selector, uint8_t flags_access);

void k_memset(void *base, char value, unsigned int length)
{
	unsigned int i; char* begin = (char *)base;
	for(i = 0;  i<length; ++i )
	{
		*begin = value;
		begin++;
	}
}

void init_idt(void)
{
	idt_address.base = (uint32_t) &idt_descriptors;
	idt_address.limit = sizeof (idt_descriptor_t) * 255 - 1;
	
	k_memset(&idt_descriptors, 0, idt_address.limit);
	
	idt_set_descriptor(0, (uint32_t) &isr0, 0x08, 0x08E);  
	idt_set_descriptor(1, (uint32_t) &isr1, 0x08, 0x08E);  
	idt_set_descriptor(2, (uint32_t) &isr2, 0x08, 0x08E);  
	idt_set_descriptor(3, (uint32_t) &isr3, 0x08, 0x08E);  
	idt_set_descriptor(4, (uint32_t) &isr4, 0x08, 0x08E);  
	idt_set_descriptor(5, (uint32_t) &isr5, 0x08, 0x08E);  
	idt_set_descriptor(6, (uint32_t) &isr6, 0x08, 0x08E);  
	idt_set_descriptor(7, (uint32_t) &isr7, 0x08, 0x08E);  
	idt_set_descriptor(8, (uint32_t) &isr8, 0x08, 0x08E);  
	idt_set_descriptor(9, (uint32_t) &isr9, 0x08, 0x08E);  
	idt_set_descriptor(10, (uint32_t) &isr10, 0x08, 0x08E);  
	idt_set_descriptor(11, (uint32_t) &isr11, 0x08, 0x08E);  
	idt_set_descriptor(12, (uint32_t) &isr12, 0x08, 0x08E);  
	idt_set_descriptor(13, (uint32_t) &isr13, 0x08, 0x08E);  
	idt_set_descriptor(14, (uint32_t) &isr14, 0x08, 0x08E);  
	idt_set_descriptor(15, (uint32_t) &isr15, 0x08, 0x08E);  
	idt_set_descriptor(16, (uint32_t) &isr16, 0x08, 0x08E);  
	idt_set_descriptor(17, (uint32_t) &isr17, 0x08, 0x08E);  
	idt_set_descriptor(18, (uint32_t) &isr18, 0x08, 0x08E);  
	idt_set_descriptor(19, (uint32_t) &isr19, 0x08, 0x08E);  
	idt_set_descriptor(20, (uint32_t) &isr20, 0x08, 0x08E);  
	idt_set_descriptor(21, (uint32_t) &isr21, 0x08, 0x08E);  
	idt_set_descriptor(22, (uint32_t) &isr22, 0x08, 0x08E);  
	idt_set_descriptor(23, (uint32_t) &isr23, 0x08, 0x08E);  
	idt_set_descriptor(24, (uint32_t) &isr24, 0x08, 0x08E);  
	idt_set_descriptor(25, (uint32_t) &isr25, 0x08, 0x08E);  
	idt_set_descriptor(26, (uint32_t) &isr26, 0x08, 0x08E);  
	idt_set_descriptor(27, (uint32_t) &isr27, 0x08, 0x08E);  
	idt_set_descriptor(28, (uint32_t) &isr28, 0x08, 0x08E);  
	idt_set_descriptor(29, (uint32_t) &isr29, 0x08, 0x08E);  
	idt_set_descriptor(30, (uint32_t) &isr30, 0x08, 0x08E);  
	idt_set_descriptor(31, (uint32_t) &isr31, 0x08, 0x08E);  
	
	load_idt((uint32_t) &idt_address);	
}

void idt_set_descriptor(uint32_t index, uint32_t offset, uint16_t segment_selector, uint8_t flags_access)
{
	idt_descriptors[index].offset_low= offset & 0xFFFF;
	idt_descriptors[index].offset_high= (offset>>16) & 0xFFFF ;
	idt_descriptors[index].segment_selector= segment_selector;
	idt_descriptors[index].access= flags_access;
}