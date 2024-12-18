// log/show_alloc_mem.c

#include "../includes/malloc.h"

void show_alloc_mem_basic(void) {
    pthread_mutex_lock(&g_malloc_mutex);

    t_heap *current_heap = g_heap;
    size_t total = 0;
    char buf[256];
    int len;

    while (current_heap) {
        const char *group = (current_heap->group == TINY) ? "TINY" :
                            (current_heap->group == SMALL) ? "SMALL" : "LARGE";
        len = snprintf(buf, sizeof(buf), "heap %s : %p\n", group, (void *)current_heap);
        write(1, buf, len);

        t_block *current_block = current_heap->blocks;
        while (current_block) {
            if (!current_block->freed) {
                void *start_address = BLOCK_SHIFT(current_block);
                void *end_address = (void *)((char *)start_address + current_block->size);
                len = snprintf(buf, sizeof(buf), "%p - %p : %zu bytes\n",
                               start_address, end_address, current_block->size);
                write(1, buf, len);
                total += current_block->size;
            }
            current_block = current_block->next;
        }
        current_heap = current_heap->next;
    }


    len = snprintf(buf, sizeof(buf), "Total : %zu bytes\n\n", total);
    write(1, buf, len);

    pthread_mutex_unlock(&g_malloc_mutex);
}

