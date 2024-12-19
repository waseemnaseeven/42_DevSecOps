// srcs/realloc.c

#include "../includes/malloc.h"

void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    pthread_mutex_lock(&g_malloc_mutex);

    t_block *block = (t_block *)((void *)ptr - sizeof(t_block));
    if (block->size >= size) {
        pthread_mutex_unlock(&g_malloc_mutex);
        return ptr;
    }

    pthread_mutex_unlock(&g_malloc_mutex);

    void *new_ptr = malloc(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size);
        free(ptr);
    }
    return new_ptr;
}
