#include "../includes/malloc.h"

void show_alloc_mem_ex(void) {
    pthread_mutex_lock(&g_malloc_mutex);

    t_heap *current_heap = g_heap;
    char buf[256];

    while (current_heap) {
        const char *group = (current_heap->group == TINY) ? "TINY" :
                            (current_heap->group == SMALL) ? "SMALL" : "LARGE";
        int len = sprintf(buf, "%s : %p\n", group, current_heap);
        write(1, buf, len);

        len = sprintf(buf, "  Total size: %zu, Free size: %zu, Block count: %zu\n",
                      current_heap->total_size,
                      current_heap->unused_space_size,
                      current_heap->block_count);
        write(1, buf, len);

        t_block *current_block = current_heap->blocks;
        while (current_block) {
            len = sprintf(buf, "  Block at %p - Size: %zu, Freed: %s\n",
                          BLOCK_SHIFT(current_block),
                          current_block->size,
                          current_block->freed ? "Yes" : "No");
            write(1, buf, len);

            current_block = current_block->next;
        }
        break;
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}

