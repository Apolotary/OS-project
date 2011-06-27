#include "sys/display/kdisplay.h"
#include "sys/display/80x25.h"
#include "sys/kio.h"
#include "sys/ftools.h"
#include "sys/isr.h"
#include "sys/tables/gdt.h"
#include "sys/tables/idt.h"
#include "sys/tables/lib/kint.h"

//kernel code here 
void kmain(unsigned int magic, void *multiboot_data)
{
	kcls();
	init_gdt();
    init_idt();
	__asm__ __volatile__ ("int $0x02");
}
