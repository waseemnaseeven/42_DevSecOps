#include "malloc.h"

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *g_heap = NULL;

// La fonction align_size ajuste la taille de la mémoire demandée pour la rendre alignée avec la taille de la structure t_block.
static  size_t align_size(size_t size) {
    return (size + sizeof(t_block) - 1) & ~(sizeof(t_block) - 1);
}

t_heap *create_heap(size_t heap_size, t_heap_group group) {
    // TODO
    // use of mmap
}

t_block *find_free_block(t_heap *heap, size_t size) {
    // TODO

}

t_block *create_block(t_heap *heap, size_t size) {
    // TODO
}

void    *malloc(size_t size)
{
    if (size < 0)
        return (NULL);

    pthread_mutex_lock(&g_malloc_mutex);

    size_t total_block_size = align_size(size);
    printf("total block size: %ld\n", total_block_size);
    t_heap  *my_heap = g_heap;
    t_block *block = NULL;

    while (my_heap) {
        // Compare size and find free_block
    }

    if (!block) {
        
        // Compare_size and create_heap and create_block

    }

    if (block)
        block->freed = false;


    pthread_mutex_unlock(&g_malloc_mutex);
    return NULL;
}

