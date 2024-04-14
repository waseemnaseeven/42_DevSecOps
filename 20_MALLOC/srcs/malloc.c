#include "malloc.h"

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *g_heap = NULL;

static size_t align_size(size_t size)
{
    return (size + sizeof(t_block) - 1) & ~(sizeof(t_block) - 1);
}

void    *ft_malloc(size_t size)
{
    if (size < 0)
        return (NULL);

    pthread_mutex_lock(&g_malloc_mutex);

    size_t total_block_size = align_size(size);
    printf("total block size: %ld\n", total_block_size);
    // t_heap *current_heap = NULL;

    // if (total_block_size <= TINY_BLOCK_SIZE)
    // {
    //     // trouver la heap avec la taille tiny

    // }

    pthread_mutex_unlock(&g_malloc_mutex);
    return NULL;
}
