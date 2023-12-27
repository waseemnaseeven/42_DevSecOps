#include "malloc.h"

void    free(void *ptr)
{
    if (ptr == NULL)
        return ;
    pthread_mutex_lock(&g_malloc_mutex);
    t_heap *heap = g_heap;
    t_block *block = (t_block *)ptr - 1;
    while (heap)
    {
        t_block *block = heap->block;
        while (block)
        {
            if (block->ptr == ptr)
            {
                block->free = 1;
                pthread_mutex_unlock(&g_malloc_mutex);
                return ;
            }
            block = block->next;
        }
        heap = heap->next;
    }
    pthread_mutex_unlock(&g_malloc_mutex);
}