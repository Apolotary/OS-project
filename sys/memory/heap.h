#ifndef _HEAP_H
#define _HEAP_H
#include "../tables/lib/kint.h"
#include "../tables/lib/kstd.h"

uint32_t reserved_ptr; // before vacant block

uint32_t mreserve(uint32_t size, bool align); //uintkptr_t - output

uintptr_t mem_reserved_ptr;

void* heap_start;
void* heap_end;

typedef struct heap_header 
{
    bool is_free;
    size_t size;
} heap_header_t;

typedef struct heap_footer 
{ 
    heap_header_t *header; // <- beginning
} heap_header_t;

typedef struct heap
{
    heap_header_t heap_header;
    heap_header_t heap_footer;
} heap_t;

void heap_init();

void* k_malloc (heap_t *heap, size_t size, bool aligned );

void* k_free (heap_t *heap, void* block );

#endif