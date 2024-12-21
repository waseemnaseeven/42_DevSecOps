#include "../includes/malloc.h"


// Vérifie si un pointeur appartient à un heap donné
static int is_pointer_in_heap(t_heap *heap, void *ptr) {
    t_block *current = heap->blocks;

    while (current) {
        void *block_start = BLOCK_SHIFT(current);
        if (ptr == block_start) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Vérifie si tous les blocs d'un heap sont libres
static char is_all_blocks_free(t_heap *heap) {
    t_block *current = heap->blocks;

    while (current) {
        if (!current->freed) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

// Supprime un heap de la liste
static void remove_heap(t_heap **heap_head, t_heap *heap) {
    if (!heap_head || !*heap_head || !heap) {
        return;
    }

    if (heap->prev) {
        heap->prev->next = heap->next;
    } else {
        *heap_head = heap->next;
    }

    if (heap->next) {
        heap->next->prev = heap->prev;
    }
}

// Libérer un heap s'il est entièrement libre ou des pages inutilisées
static void free_heap_if_possible(t_heap **heap_head, t_heap *heap) {
    if (is_all_blocks_free(heap)) {
        remove_heap(heap_head, heap);
        munmap(heap, heap->total_size);
    } 
}

// Libère un bloc dans un heap spécifique
static void free_block_in_heap(t_heap **heap_head, t_heap *heap, void *ptr) {
    if (!heap || !ptr) {
        return;
    }

    // Correction du calcul de l'adresse du bloc
    t_block *block = (t_block *)((char *)ptr - sizeof(t_block));

    // Vérifiez que le pointeur calculé appartient bien au heap
    if (!is_pointer_in_heap(heap, ptr)) {
        ft_putstr_fd("Erreur : Pointeur non valide pour le heap.\n", 1);
        pthread_mutex_unlock(&g_malloc_mutex);
        return;
    }

    block->freed = true;
    block->unused_space = 0;

    ft_putstr_fd("\033[0;32mFREE : ", 1);
    print_address_hex((size_t)ptr);
    ft_putstr_fd("\033[0m\n\n", 1);

    // Fusionner les blocs libres adjacents
    coalesce_free_blocks(heap);

    // Vérifier si le heap peut être libéré ou des pages inutilisées
    free_heap_if_possible(heap_head, heap);
}

// Trouve le heap contenant un pointeur dans une liste de heaps
static t_heap *find_heap_containing_ptr(t_heap *heap_list, void *ptr) {
    t_heap *current_heap = heap_list;

    while (current_heap) {
        if (is_pointer_in_heap(current_heap, ptr)) {
            return current_heap;
        }
        current_heap = current_heap->next;
    }
    return NULL;
}

void free(void *ptr) {
    if (!ptr) {
        return;
    }

    pthread_mutex_lock(&g_malloc_mutex);

    t_heap *heap = NULL;

    // Recherche dans TINY_HEAP
    heap = find_heap_containing_ptr(g_heap.TINY_HEAP, ptr);
    if (heap) {
        free_block_in_heap(&g_heap.TINY_HEAP, heap, ptr);
        pthread_mutex_unlock(&g_malloc_mutex);
        return;
    }

    // Recherche dans SMALL_HEAP
    heap = find_heap_containing_ptr(g_heap.SMALL_HEAP, ptr);
    if (heap) {
        free_block_in_heap(&g_heap.SMALL_HEAP, heap, ptr);
        pthread_mutex_unlock(&g_malloc_mutex);
        return;
    }

    // Recherche dans LARGE_HEAP
    heap = find_heap_containing_ptr(g_heap.LARGE_HEAP, ptr);
    if (heap) {
        free_block_in_heap(&g_heap.LARGE_HEAP, heap, ptr);
        pthread_mutex_unlock(&g_malloc_mutex);
        return;
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}
