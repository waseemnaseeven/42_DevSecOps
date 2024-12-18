// srcs/malloc.c

/*
    - recalculer block 
    - refaire pour large addr
    - realloc test 
    - thread test
    - corrections test 
    - show_alloc_mem_ex avec free et realloc ? 
*/

#include "../includes/malloc.h"

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *g_heap = NULL;


// Aligne sur 16 octets (taille typique pour 64 bits)
static size_t align_size(size_t size) {
    size_t alignment = 16;
    return (size + alignment - 1) & ~(alignment - 1);
}

void    *malloc(size_t size)
{
    if (size <= 0)
        return (NULL);

    pthread_mutex_lock(&g_malloc_mutex);

    size_t total_block_size = 0;
    total_block_size = align_size(size);
    t_heap_group group = (total_block_size <= TINY_BLOCK_SIZE) ? TINY : (total_block_size <= SMALL_BLOCK_SIZE) ? SMALL : LARGE;

    t_heap  *my_heap = g_heap;
    t_block *block = NULL;
    
    if (group == LARGE) {
        // Pour les allocations LARGE, créer une nouvelle heap dédiée
        size_t heap_size = total_block_size + sizeof(t_heap) + sizeof(t_block);

        my_heap = create_heap(heap_size, group, NULL);
        if (!my_heap) {
            pthread_mutex_unlock(&g_malloc_mutex);
            return NULL;
        }

        block = create_block(my_heap, total_block_size);
        if (!block) {
            munmap(my_heap, heap_size);
            pthread_mutex_unlock(&g_malloc_mutex);
            return NULL;
        }


    } else {
        // Pour TINY et SMALL, chercher un bloc libre ou créer une nouvelle heap
        my_heap = g_heap;
        while (my_heap != NULL) {
            if (my_heap->group == group) {
                block = find_free_block(my_heap, total_block_size);
                if (block) {
                    block->freed = false;
                    break;
                }
            }
            my_heap = my_heap->next;
        }
    }
    // Compare_size and create_heap and create_block
    if (!block) {

        size_t heap_size = heap_size_function(group, total_block_size);

        my_heap = create_heap_from_aligned_size(heap_size, group);
        if (!my_heap) {
            pthread_mutex_unlock(&g_malloc_mutex);
            return (NULL);
        }
        block = create_block(my_heap, total_block_size);
        if (!block) {
            pthread_mutex_unlock(&g_malloc_mutex);
            return NULL;
        }
    }
    
    if (getenv("MALLOC_DEBUG")) {
        char buf[64];
        int len = sprintf(buf, "[MALLOC] Allocated %zu bytes at %p\n", size, BLOCK_SHIFT(block));
        write(1, buf, len);
    }

    pthread_mutex_unlock(&g_malloc_mutex);
    return block ? BLOCK_SHIFT(block) : NULL;
}


