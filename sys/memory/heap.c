#include "heap.h"

void init_mm(void){
	mem_reserved_ptr = (uintptr_t) &k_phys_mem_end;
}

uint32_t mreserve(uint32_t size, bool align)
{
	uint32_t result;
	
	if(align && (mem_reserved_ptr & 0xFFF)
	{
		mem_reserved_ptr &= 0xFFFFF000;
		mem_reserved_ptr += 0x1000;
	}
	result = mem_reserved_ptr;
	mem_reserved_ptr += size;
	
	return result;
}

void heap_init(heap_t *heap)
{
    heap_start = NULL; // ??
    heap_end = NULL; // ??
    heap.heap_footer.header = heap_start;
}

void* k_malloc (heap_t *heap, size_t size, bool aligned )
{
    heap_init(*heap);
    while ()
    {
        if (*heap.heap_header.size >= size && *heap.heap_header.is_free)
        {
            *heap.heap_header.is_free = false;
            if (*heap.heap_header.size == size)
            {
                *heap.heap_header.size = size;
            }
            else
            {
                size_t vacant = *heap.heap_header.size - size;
                *heap.heap_header.size = size;
                void* next = heap.heap_footer.header + heap.heap_header.size;
                next->heap.heap_header.is_free = true;
                next->heap.heap_header.size = vacant;
                next->heap.heap_footer.header = next;
            }
            return heap.heap_footer.header; // 
        }
        else if (heap.heap_footer.header == heap_end) // memory ends here
        {
            heap.heap_footer.header = 0;
            return heap.heap_footer.header; // null pointer?
        }
        heap.heap_footer.header += heap.heap_footer.header + heap.heap_header.size; // next block
    }
    
}

void* k_free (heap_t *heap, void* block )
{
    // in heap where the block points, 
    // there is a field is_free that 
    // we should set to true
    block->heap.heap_header.is_free = true;
}