// log/show_alloc_mem.c

#include "../includes/malloc.h"

void show_alloc_mem(void) {
    pthread_mutex_lock(&g_malloc_mutex);

    t_heap *current_heap = g_heap;
    char buf[128];

    while (current_heap) {
        const char *group = (current_heap->group == TINY) ? "TINY" :
                            (current_heap->group == SMALL) ? "SMALL" : "LARGE";
        int len = sprintf(buf, "%s : %p\n", group, current_heap);
        write(1, buf, len);

        t_block *current_block = current_heap->blocks;
        while (current_block) {
            if (!current_block->freed) {
                len = sprintf(buf, "%p - %p : %zu bytes\n",
                              BLOCK_SHIFT(current_block),
                              (void *)BLOCK_SHIFT(current_block) + current_block->size,
                              current_block->size);
                write(1, buf, len);
            }
            current_block = current_block->next;
        }
        current_heap = current_heap->next;
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}
