#include "../includes/malloc.h"

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