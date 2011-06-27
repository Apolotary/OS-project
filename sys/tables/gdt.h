#ifndef _GDT_H_
#define _GDT_H_

#include "lib/kint.h"

struct gdt_descriptor
{
	uint16_t limit_low;           // 0 - 16
	uint16_t base_low;            // 0 - 16
	uint8_t base_mid;             // 16 - 23
	uint8_t access;
	uint8_t flags_and_limit_high; // 16 - 20 + 3 on flags
	uint8_t base_high;	          // 23 - 32
} __attribute__((packed));

struct gdt_ptr   // pointer
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

typedef struct gdt_descriptor gdt_descriptor_t;
typedef struct gdt_ptr gdt_ptr_t;

gdt_descriptor_t gdt_descriptors[5];
gdt_ptr_t gdt_address;

void init_gdt(void);

#endif