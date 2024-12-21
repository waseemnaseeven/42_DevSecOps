// srcs/realloc.c

#include "../includes/malloc.h"

// Fonction pour scinder un bloc en deux si possible
char malloc_shrink_block(t_block *block, size_t size) {
    // Vérifier s'il y a assez d'espace pour scinder le bloc
    if (block->size <= size + sizeof(t_block)) {
        // Pas assez d'espace pour créer un nouveau bloc
        return 0;
    }

    // Calculer l'adresse du nouveau bloc
    t_block *new_block = (t_block *)((char *)(block + 1) + size);
    new_block->size = block->size - size - sizeof(t_block);
    new_block->freed = true;
    new_block->prev = block;
    new_block->next = block->next;

    // Mettre à jour le bloc suivant si il existe
    if (new_block->next) {
        new_block->next->prev = new_block;
    }

    // Mettre à jour le bloc original
    block->size = size;
    block->freed = false;
    block->next = new_block;

    return 1;
}


// Vérifie si le pointeur appartient à une zone et retourne le bloc
static t_block* find_block(void *ptr) {
    if (!ptr)
        return NULL;

    // Parcourir toutes les zones
    t_heap *zones[] = {g_heap.TINY_HEAP, g_heap.SMALL_HEAP, g_heap.LARGE_HEAP};
    for (int i = 0; i < 3; i++) {
        t_heap *current_heap = zones[i];
        while (current_heap) {
            t_block *current_block = current_heap->blocks;
            while (current_block) {
                void *block_ptr = BLOCK_SHIFT(current_block);
                if (ptr == block_ptr) {
                    return current_block;
                }
                current_block = current_block->next;
            }
            current_heap = current_heap->next;
        }
    }
    return NULL;
}

size_t aligned(size_t size) {
    size_t alignment = 16;
    return (size + alignment - 1) & ~(alignment - 1);
}


void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    pthread_mutex_lock(&g_malloc_mutex);

    // Trouver le bloc correspondant
    t_block *block = find_block(ptr);
    if (!block) {
        // Le pointeur ne fait pas partie de notre allocation
        pthread_mutex_unlock(&g_malloc_mutex);
        return NULL;
    }

    size_t aligned_size = aligned(size);

    if (block->size >= aligned_size) {
        // Si la taille actuelle est suffisante, éventuellement splitter le bloc
        if (block->size > aligned_size + sizeof(t_block)) {
            malloc_shrink_block(block, aligned_size);
        }
        pthread_mutex_unlock(&g_malloc_mutex);
        return ptr;
    }

    // Tenter de fusionner avec le bloc suivant si possible
    if (block->next && block->next->freed && 
        (block->size + sizeof(t_block) + block->next->size) >= aligned_size) {
        
        // Fusionner avec le bloc suivant
        block->size += sizeof(t_block) + block->next->size;
        block->next = block->next->next;
        if (block->next) {
            block->next->prev = block;
        }

        // Split si nécessaire
        if (block->size > aligned_size + sizeof(t_block)) {
            malloc_shrink_block(block, aligned_size);
        }

        pthread_mutex_unlock(&g_malloc_mutex);
        return ptr;
    }

    // Allocation d'un nouveau bloc
    pthread_mutex_unlock(&g_malloc_mutex);
    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;

    // Copier les données
    ft_memcpy(new_ptr, ptr, block->size);

    // Libérer l'ancien bloc
    free(ptr);

    return new_ptr;
}