#include "../includes/malloc.h"

void hex_dump(void *addr, size_t size) {
    unsigned char *ptr = (unsigned char *)addr;
    char buf[128];
    int len = 0;
    for (size_t i = 0; i < size; i += 16) {
        len = snprintf(buf, sizeof(buf), "%08lx  ", (intptr_t) (ptr + i));
        if (len > 0 && len < (int)sizeof(buf))
            write(1, buf, len);

        for (size_t j = 0; j < 16 && i + j < size; ++j) {
            len = snprintf(buf, sizeof(buf), "%02x ", ptr[i + j]);
            if (len > 0 && len < (int)sizeof(buf))
                write(1, buf, len);
        }
        write(1, "\n", 1);
    }
}

void show_alloc_mem_ex(void) {
    pthread_mutex_lock(&g_malloc_mutex);

    char buf[256];
    int len;

    len = snprintf(buf, sizeof(buf), "Allocation History:\n");
    if (len > 0 && len < (int)sizeof(buf))
        write(1, buf, len);

    t_heap *current_heap = g_heap;
    t_block *current_block = NULL;

    // Trouver le premier bloc alloué
    while (current_heap) {
        if (current_heap->blocks) {
            // Trouver le premier bloc alloué dans cette heap
            t_block *first_allocated_block = current_heap->blocks;
            while (first_allocated_block->next) {
                first_allocated_block = first_allocated_block->next;
            }
            current_block = first_allocated_block;
            break;
        }
        current_heap = current_heap->next;
    }

    // Parcourir les blocs alloués dans l'ordre
    while (current_block) {
        const char *group = (current_block->size <= TINY_BLOCK_SIZE) ? "TINY" :
                            (current_block->size <= SMALL_BLOCK_SIZE) ? "SMALL" : "LARGE";

        void *start_address = BLOCK_SHIFT(current_block);
        len = snprintf(buf, sizeof(buf), "Address: %p - Size: %zu bytes - Group: %s %s\n",
                       start_address, current_block->size, group,
                       current_block->freed ? "[FREED]" : "");
        if (len > 0 && len < (int)sizeof(buf))
            write(1, buf, len);

        // Dump hexadécimal du bloc
        if (!current_block->freed) {
            hex_dump(start_address, current_block->size);
        }

        // Passer au bloc alloué suivant
        current_block = current_block->next_alloc;
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}


// void show_alloc_mem_ex(void) {
//     pthread_mutex_lock(&g_malloc_mutex);

//     t_heap *current_heap = g_heap;
//     char buf[256];

//     while (current_heap) {
//         const char *group = (current_heap->group == TINY) ? "TINY" :
//                             (current_heap->group == SMALL) ? "SMALL" : "LARGE";
//         int len = sprintf(buf, "My group is %s : %p\n", group, current_heap);
//         write(1, buf, len);

//         len = sprintf(buf, "  Total size: %zu, Free size: %zu, Block count: %zu\n",
//                       current_heap->total_size,
//                       current_heap->unused_space_size,
//                       current_heap->block_count);
//         write(1, buf, len);

//         t_block *current_block = current_heap->blocks;
//         while (current_block) {
//             len = sprintf(buf, "  Block at %p - Size: %zu, Freed: %s\n",
//                           BLOCK_SHIFT(current_block),
//                           current_block->size,
//                           current_block->freed ? "Yes" : "No");
//             write(1, buf, len);

//             current_block = current_block->next;
//         }
//         break;
//     }

//     pthread_mutex_unlock(&g_malloc_mutex);
// }

