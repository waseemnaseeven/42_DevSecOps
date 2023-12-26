#include "malloc.h"

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *g_heap = NULL;

void    *malloc(size_t size)
{
    if (size == 0)
        return (NULL);

    void    *ret = NULL;
    pthread_mutex_lock(&g_malloc_mutex);
    

    pthread_mutex_unlock(&g_malloc_mutex);
    return NULL;
}
