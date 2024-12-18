// srcs/realloc.c

#include "../includes/malloc.h"
#include <string.h>
#include <pthread.h>

// Vérifie si un pointeur pointe sur un bloc alloué connu.
// Retourne true s'il est valide, false sinon.
static bool is_valid_ptr(void *ptr) {
    if (!ptr)
        return false;

    t_heap *heap = g_heap;
    while (heap) {
        t_block *block = heap->blocks;
        while (block) {
            if (!block->freed && BLOCK_SHIFT(block) == ptr)
                return true;
            block = block->next;
        }
        heap = heap->next;
    }
    return false;
}

void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    pthread_mutex_lock(&g_malloc_mutex);

    // Vérification de la validité du pointeur
    if (!is_valid_ptr(ptr)) {
        pthread_mutex_unlock(&g_malloc_mutex);
        return NULL; // Le pointeur ne correspond pas à un bloc alloué par notre malloc
    }

    t_block *block = (t_block *)((char *)ptr - sizeof(t_block));

    size_t current_size = block->size;
    if (size == current_size) {
        // Même taille, on retourne juste ptr
        pthread_mutex_unlock(&g_malloc_mutex);
        return ptr;
    }

    if (size < current_size) {
        // Dans l'exemple fourni, il y a une fonction malloc_shrink_block(block, size);
        // Ici, on pourrait juste retourner ptr, ou implémenter une telle fonction.
        // Pour simplifier, on retourne ptr sans réellement "shrink" le bloc.
        pthread_mutex_unlock(&g_malloc_mutex);
        return ptr;
    }

    // size > current_size
    pthread_mutex_unlock(&g_malloc_mutex);

    // On alloue un nouveau bloc, on copie et on free l'ancien
    void *new_ptr = malloc(size);
    if (!new_ptr) {
        // Si on ne peut pas allouer, on ne touche pas à l'ancien bloc
        return NULL;
    }

    memcpy(new_ptr, ptr, current_size);
    free(ptr);
    return new_ptr;
}
