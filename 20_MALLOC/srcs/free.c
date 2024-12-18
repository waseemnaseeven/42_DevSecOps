// srcs/free.c

#include "../includes/malloc.h"

static bool is_heap_all_free(t_heap *my_heap) {
    t_block *block = my_heap->blocks;
    while (block) {
        if (!block->freed) {
            return false;
        }
        block = block->next;
    }
    return true;
}

static void remove_heap_from_list(t_heap *my_heap) {
    if (my_heap->prev)
        my_heap->prev->next = my_heap->next;
    else
        g_heap = my_heap->next;

    if (my_heap->next)
        my_heap->next->prev = my_heap->prev;
}

static void coalesce_free_blocks(t_heap *my_heap) {
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
        t_block *b = my_heap->blocks;
        bool found = false;
        while (b) {
            if (b == block) {
                found = true;
                break;
            }
            b = b->next;
        }

        if (found) {
            coalesce_free_blocks(my_heap);

            // Si la heap est entièrement libre, on rend la mémoire au système
            if (is_heap_all_free(my_heap)) {
                remove_heap_from_list(my_heap);
                munmap(my_heap, my_heap->total_size);
            }

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
