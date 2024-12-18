// srcs/malloc.c

#include "../includes/malloc.h"

/*

    - Revoir norme fonctions 
    - Tester avec d'autres Treshold
    - Ecrire commandes utiles dans info.sh
    - Makefile propre pour les tests 
    - Refaire une correction propre
    - Ecrire cours et explications de malloc, free, realloc
    
*/

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *g_heap = NULL;

static size_t align_size(size_t size) { // en faire un define 
    size_t alignment = 16; // Aligne sur 16 octets (taille typique pour 64 bits)
    return (size + alignment - 1) & ~(alignment - 1);
}

void    *malloc(size_t size)
{
    if (size == 0)
        return (NULL);

    pthread_mutex_lock(&g_malloc_mutex);

    size_t total_block_size = 0;
    total_block_size = align_size(size);
    t_heap_group group = (total_block_size <= TINY_BLOCK_SIZE) ? TINY : (total_block_size <= SMALL_BLOCK_SIZE) ? SMALL : LARGE;


    t_heap  *my_heap = g_heap;
    t_block *block = NULL;

    if (group == LARGE) {
        // For LARGE allocation, create a new heap
        size_t heap_size = total_block_size + sizeof(t_heap) + sizeof(t_block);

        my_heap = create_heap(heap_size, group, NULL);
        if (!my_heap) {
            pthread_mutex_unlock(&g_malloc_mutex);
            return NULL;
        }

        block = create_block(my_heap, total_block_size);
        block->requested_size = size;
        if (!block) {
            munmap(my_heap, heap_size);
            pthread_mutex_unlock(&g_malloc_mutex);
            return NULL;
        }


    } else {
        // For TINY and SMALL, find a free_block or go to another heap (create one if so)
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
        size_t heap_size = (group == TINY) ? TINY_HEAP_ALLOCATION_SIZE : (group == SMALL) ? SMALL_HEAP_ALLOCATION_SIZE : (total_block_size + sizeof(t_heap) + sizeof(t_block));

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
    return block ? BLOCK_SHIFT(block) : NULL; // return pointer after metadata
}


