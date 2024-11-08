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

void show_alloc_mem(void)
{
    pthread_mutex_lock(&g_malloc_mutex);

    t_heap *current_heap = g_heap;
    while (current_heap)
    {
        printf("%s : %p\n", (current_heap->group == TINY) ? "TINY" :
                               (current_heap->group == SMALL) ? "SMALL" : "LARGE", current_heap);
        t_block *current_block = current_heap->blocks;
        while (current_block)
        {
            if (!current_block->freed)
            {
                printf("%p - %p : %zu bytes\n", BLOCK_SHIFT(current_block),
                       (void *)BLOCK_SHIFT(current_block) + current_block->size, current_block->size);
            }
            current_block = current_block->next;
        }
        current_heap = current_heap->next;
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}