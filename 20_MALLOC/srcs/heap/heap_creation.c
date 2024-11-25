#include "../../includes/malloc.h"

t_heap *available_heap(t_heap *heap_start, t_heap_group group, size_t required_size) {
    t_heap *free_heap;

    free_heap = (t_heap*)heap_start;
    while (free_heap) {
        if ((free_heap->group == group) && (free_heap->unused_space_size >= required_size))
            return (free_heap);
        free_heap = free_heap->next;
    }
    return (NULL);
}

static rlim_t get_system_limit(void) {
    struct rlimit heap_limit;

    if (getrlimit(RLIMIT_DATA, &heap_limit) == -1) {
        perror("Limit of the heap");
        return (-1);
    }

    if (heap_limit.rlim_max == RLIM_INFINITY) {
        return (RLIM_INFINITY);
    }

    return heap_limit.rlim_max;
}

t_heap *create_heap(size_t heap_size, t_heap_group group, t_heap *gl_heap) {
    if (heap_size > get_system_limit())
        return (NULL);

    t_heap  *my_heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (my_heap == MAP_FAILED)
        return (NULL);

    ft_bzero(my_heap, heap_size);

    my_heap->total_size = heap_size;
    my_heap->unused_space_size = heap_size - sizeof(t_heap);
    my_heap->block_count = 0;
    my_heap->group = group;
    my_heap->blocks = NULL;
    my_heap->current_offset = sizeof(t_heap);

    my_heap->prev = NULL;
    my_heap->next = gl_heap;
    // if (my_heap->next)
    //     my_heap->next->prev = my_heap;
    if (g_heap)
        g_heap->prev = my_heap;
    g_heap = my_heap;

    return (my_heap);
}

t_heap *create_heap_from_aligned_size(size_t heap_size, t_heap_group group) {
    
    t_heap  *gl_heap = g_heap;
    t_heap* new_heap = available_heap(gl_heap, group, heap_size);

    if (new_heap == NULL) {
        if (!(new_heap = create_heap(heap_size, group, gl_heap)))
            return (NULL);
    }
    return (new_heap);
}