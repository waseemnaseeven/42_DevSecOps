// srcs/heap_creation.c

#include "../includes/malloc.h"

// Recherche une heap disponible dans une liste spécifique
t_heap *available_heap(t_heap *heap_start, t_heap_group group, size_t required_size) {
    t_heap *free_heap = heap_start;
    while (free_heap) {
        if (free_heap->group == group && free_heap->unused_space_size >= required_size) {
            return free_heap;
        }
        free_heap = free_heap->next;
    }
    return NULL;
}

// Récupère la limite système pour les allocations mémoire
static rlim_t get_system_limit(void) {
    struct rlimit heap_limit;

    if (getrlimit(RLIMIT_AS, &heap_limit) == -1) { // Utiliser RLIMIT_AS pour l'espace d'adresse
        perror("Error getting system limit");
        return (rlim_t)(-1);
    }

    if (heap_limit.rlim_max == RLIM_INFINITY) {
        return (RLIM_INFINITY);
    }

    return heap_limit.rlim_max;
}

// Crée une nouvelle heap et l'ajoute à la liste correspondante dans heap_group
t_heap *create_heap(size_t heap_size, t_heap_group group, t_heap *existing_heap) {
    if (heap_size > get_system_limit()) {
        return NULL;
    }

    t_heap *new_heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (new_heap == MAP_FAILED) {
        return NULL;
    }

    ft_bzero(new_heap, heap_size);

    new_heap->total_size = heap_size;
    new_heap->unused_space_size = heap_size - sizeof(t_heap);
    new_heap->block_count = 0;
    new_heap->group = group;
    new_heap->blocks = NULL;
    new_heap->current_offset = sizeof(t_heap);

    new_heap->prev = NULL;
    new_heap->next = existing_heap;

    // Ajouter la nouvelle heap à la liste appropriée dans heap_group
    if (existing_heap) {
        existing_heap->prev = new_heap;
    }

    // Mettre à jour le pointeur dans heap_group
    if (group == TINY) {
        g_heap.TINY_HEAP = new_heap;
    } else if (group == SMALL) {
        g_heap.SMALL_HEAP = new_heap;
    } else if (group == LARGE) {
        g_heap.LARGE_HEAP = new_heap;
    }

    return new_heap;
}

// Crée une heap alignée et l'ajoute à la liste appropriée dans heap_group
t_heap *create_heap_from_aligned_size(size_t heap_size, t_heap_group group) {
    t_heap *existing_heap = NULL;

    // Sélectionner la liste de heaps à rechercher basée sur le groupe
    if (group == TINY) {
        existing_heap = g_heap.TINY_HEAP;
    } else if (group == SMALL) {
        existing_heap = g_heap.SMALL_HEAP;
    } else if (group == LARGE) {
        existing_heap = g_heap.LARGE_HEAP;
    }

    // Rechercher une heap disponible dans la liste correspondante
    t_heap *new_heap = available_heap(existing_heap, group, heap_size);
    if (new_heap == NULL) {
        // Si aucune heap disponible, créer une nouvelle heap
        new_heap = create_heap(heap_size, group, existing_heap);
        if (!new_heap) {
            return NULL;
        }
    }

    return new_heap;
}
