#include "paging.h"

void pf_handler(param_t params);
void init_paging(void)
{
	unsigned int frame;
	uintptr_t tmp, phys_address, table_index, page_index;
	
	page_table_t *table;
	
	frames_number = HARD_MEMORY_LIMIT / PAGE_SIZE;//0x1000;
	frames = (uint32_t) mem_reserve(frame_number, true);
	k_memset(frames, 0, frames_number);
	
	kernel_dir = (page_dir_t *) mem_reserve(sizeof(page_dir_t), true);
	k_memset(kernel_dir, 0, frames_number);
	
	curr_dir = kernel_dir;
	
	physical_address = frame = 0;
	while(phys_address < mem_reserved_ptr) //< HARD_MEMORY_LIMIT
	{
		tmp = physical_address/PAGE_SIZE;
		table_index = tmp/1024;
		page_index = tmp%1024;
		
		if(!(table = curr_dir ->logicl_page_tables[table_index]))
		{
			tmp = mem_reserve(sizeof(page_table_t), true);
			table = (page_table_t *) tmp;
			
			k_memset(table, 0, sizeof(page_table_t));
			
			_curr_dir -> phys_page_tables[table_index] = tmp | 0x3; //установить present flag
			
			_curr_dir -> logical_page_tables[table_index] = table;
		}
		
		if (frame == frames_number)
		{
			k_panic("Failed to allocate a page frame. No more freee frames.");
		}
		else
		{
			_frames[frame++] = 1;
		}
		
		table -> pages[page_index] = phys_address | 0x3;
		
		phys_address += PAGE_SIZE;
	}
	
	register_isr_handler(14, &page_fault_handler);
	load_page_dir(current_dir);
	
	// uint32_t i;

	// frame_number = HARD_MEMORY_LIMIT / 0x1000;
	// frames = mreserve(frame_number, false);
	// k_memset(frames, 0, frame_number);
	
	// kernel_dir = mreserve(sizeof (page gir t), true;)
	// k_memset(kernel_dir, 0, frame_number);
	
	// current_dir = kernel_dir;
	
	// for(i =0; i<mreserved_ptr; i+= 0x1000)
	// {
		// reserve_table(reserve_page(i), 0, 0);//read-write user-supervisot
	// }
	
	// register_isr_handler(14, &pf_handler);
	// load_page_dir(current_dir);
}

void pf_handler(param_t params)
{
	uint32_t fault_address;
	__asm__ __volatile__("mov %%cr2, %0" : "=r"(fault_address));
	printf("Kernel message: page fault at 0x%x with error code 0x%x",
			fault_address, params.error_code);
}

void load_page_dir(page_dir_t *dir){
	uint32_t cr0;	
	__asm__ __volatile__("mov %0, %%cr3", :: "r"(&dir -> physical_page_tables));
	__asm__ __volatile__("mov %%cr0", :: "=r"(cr0));
	
	cr0 = 0x800000000;
	
	__asm__ __volatile__("mov %0, %%cr0", :: "r"(cr0));
	
}

static void page_fault_handler(isr_param_t params)
{
	uint32_t fault_address;
	__asm__ __volatile__("mov %%cr2, %0", :: "=r"(fault_address));
	
	k_printf("Kernel message page fault at 0x%X with error code 0x%X\n", fault_address, params.error_code);
	k_panic("Unrecoverable error: page fault while working in kernel mode");  //jmp to k_stop d loader
}


