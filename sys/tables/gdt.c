#include "gdt.h"
#include "lib/kint.h"
// gdt_descriptor_t gdt_descriptors[5];
// gdt_ptr_t gdt_address;

extern void load_gdt(uint32_t); // that asm file

void gdt_set_descriptor(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	gdt_descriptors[index].base_low = base & 0xFFFF;     // (uint16_t) base and max limit
	gdt_descriptors[index].base_mid = (base>>16) & 0xFF; // (uint8_t) base shift right and max limit
	gdt_descriptors[index].base_high = (base>>24) & 0xFF;
	gdt_descriptors[index].limit_low = limit & 0xFFFF;
	gdt_descriptors[index].flags_and_limit_high = (limit >> 16) & 0x0F;
	gdt_descriptors[index].access = access;
	gdt_descriptors[index].flags_and_limit_high |= flags & 0xF0;
}

void init_gdt(void)
{
	gdt_address.base = (uint32_t) &gdt_descriptors;
	gdt_address.limit = sizeof (gdt_descriptor_t) * 5 - 1;
    // 0xFFFFFFFF ~4GB
	gdt_set_descriptor(0, 0, 0, 0, 0);                  // null descriptor
	gdt_set_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	// kernel code segment descriptor
	gdt_set_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	// kernel data segment descriptor
	gdt_set_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);	// user code
	gdt_set_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);	// user data
	load_gdt((uint32_t) &gdt_address);
}
