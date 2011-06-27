#ifndef _IDT_H_
#define _IDT_H_

#include "lib/kint.h"

struct idt_descriptor
{
	uint16_t offset_low;       // 0 - 15
	uint16_t segment_selector; // 16 - 31
    uint8_t ist;               // 0 - 8
	uint8_t access;            // 8 - 16
    uint16_t offset_high;      // 16 - 31
} __attribute__((packed));

struct idt_ptr   // pointer
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

typedef struct idt_descriptor idt_descriptor_t;
typedef struct idt_ptr idt_ptr_t;

idt_descriptor_t idt_descriptors[256];
idt_ptr_t idt_address;

void init_idt(void);

#endif