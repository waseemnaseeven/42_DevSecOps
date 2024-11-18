// srcs/free.c

#include "../includes/malloc.h"

void coalesce_free_blocks(t_heap *my_heap) {
    t_block *current = my_heap->blocks;
    while (current && current->next) {
        if (current->freed && current->next->freed) {
            current->size += sizeof(t_block) + current->next->size;
            current->next = current->next->next;
            if (current->next)
                current->next->prev = current;
        } else {
            current = current->next;
        }
    }
}

void free(void *ptr) {
    if (!ptr)
        return;

    pthread_mutex_lock(&g_malloc_mutex);

    t_block *block = (t_block *)((void *)ptr - sizeof(t_block));
    block->freed = true;
    block->unused_space = 0;

    t_heap *my_heap = g_heap;
    while (my_heap) {
        if (my_heap->blocks == block) {
            coalesce_free_blocks(my_heap);
            break;
        }
        my_heap = my_heap->next;
    }

    if (getenv("MALLOC_DEBUG")) {
        char buf[64];
        int len = sprintf(buf, "[FREE] Freed memory at %p\n", ptr);
        write(1, buf, len);
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}
