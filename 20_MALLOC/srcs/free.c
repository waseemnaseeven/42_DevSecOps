#include "malloc.h"

void    free(void *ptr) {
    
    if (!ptr)
        return;
    
    pthread_mutex_lock(&g_malloc_mutex);

    //use of mmunmap ? 
    t_block *block = NULL;
    block->freed = true;
    
    pthread_mutex_unlock(&g_malloc_mutex);
}