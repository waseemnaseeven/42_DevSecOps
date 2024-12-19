#include "../../includes/malloc.h"

// Retourne le nom du groupe en fonction de t_heap_group
const char *get_group_name(t_heap_group group) {
    if (group == TINY)
        return "TINY";
    else if (group == SMALL)
        return "SMALL";
    else
        return "LARGE";
}

size_t heap_size_function(t_heap_group group, size_t total_block_size) {
    return (group == TINY) ? TINY_HEAP_ALLOCATION_SIZE : (group == SMALL) ? SMALL_HEAP_ALLOCATION_SIZE : (total_block_size + sizeof(t_heap) + sizeof(t_block));
}

