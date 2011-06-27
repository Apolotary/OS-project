#ifndef _PAGING_H_
#define _PAGING_H_

#include "../tables/lib/kint.h"
#include "../kio.h"
#include "../isr.h"
#include "heap.h"

#define PAGE_SIZE 0x1000;

struct pde	// p129
{
	uint32_t present: 		1; 		//cropping into chunks
	uint32_t rw: 			1;
	uint32_t us: 			1;		//user_supervisor
	uint32_t pwt: 			1;
	uint32_t pcd: 			1;
	uint32_t a: 			1; 		// access
	uint32_t ignor: 		6; 		// 0 as a result
	uint32_t table_address: 20; 	
} __attribute__((packed));
typedef struct pde pde_t;

struct pte	// p129 page table entry
{
	uint32_t present: 		1; 		
	uint32_t rw: 			1;
	uint32_t us: 			1;		
	uint32_t pwt: 			1;
	uint32_t pcd: 			1;
	uint32_t a: 			1; 		
	uint32_t dirty: 		1;
	uint32_t pat: 			1;
	uint32_t global: 		1;
	uint32_t ignor: 		3; 		
	uint32_t table_address: 20; 	
} __attribute__((packed));
typedef struct pte pte_t;

typedef struct page_table
{
	uint32_t pages[1024]			//pte_t pages[1024];
}  __attribute__((packed));
typedef struct page_table page_table_t;

typedef struct page_dir
{
	page_table_t *logical_page_tables[1024]; //for us	
	uint32_t physical_page_tables[1024]	     //pde_t physical_page_tables[1024]; //for processor
} page_dir_t;

//page_dir_t *kernel_dir; 
//page_dir_t *current_dir;

#define HARD_MEMORY_Limit 0x1000000;

uint8_t *frames;

size_t frames_number; // size_t = uint32_t 

void init_paging(void);

extern void load_page_dir(page_dir_t *dir);

#endif