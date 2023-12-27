#include "malloc.h"

void show_alloc_mem()
{
    t_heap *current_heap = g_heap;
    size_t total_allocated = 0;

    while (current_heap)
    {
        printf("ZONE: %p\n", (void *)current_heap);
        t_block *block = current_heap->blocks;
        while (block)
        {
            printf("%p - %p : %zu bytes\n", (void *)(block + 1), (void *)((char *)(block + 1) + block->size), block->size);
            total_allocated += block->size;
            block = block->next;
        }
        current_heap = current_heap->next;
    }
    printf("Total : %zu bytes\n", total_allocated);
}