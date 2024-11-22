// log/show_alloc_mem.c

#include "../includes/malloc.h"

void show_alloc_mem(void) {
    pthread_mutex_lock(&g_malloc_mutex);

    t_heap *current_heap = g_heap;
    size_t total = 0;
    char buf[256];
    int len;

    while (current_heap) {
        const char *group = (current_heap->group == TINY) ? "TINY" :
                            (current_heap->group == SMALL) ? "SMALL" : "LARGE";
        len = snprintf(buf, sizeof(buf), "%s : %p\n", group, (void *)current_heap);
        write(1, buf, len);

        t_block *current_block = current_heap->blocks;
        while (current_block) {
            if (!current_block->freed) {
                void *start_address = BLOCK_SHIFT(current_block);
                void *end_address = (void *)((char *)start_address + current_block->size);
                len = snprintf(buf, sizeof(buf), "%p - %p : %zu bytes\n",
                               start_address, end_address, current_block->size);
                write(1, buf, len);
                total += current_block->size;
            }
            current_block = current_block->next;
        }
        current_heap = current_heap->next;
    }

    // Print total allocated memory
    len = snprintf(buf, sizeof(buf), "Total : %zu bytes\n", total);
    write(1, buf, len);

    pthread_mutex_unlock(&g_malloc_mutex);
}


// static size_t print_block_list(t_block *block) {
//     size_t total = 0;
//     char buf[256];
//     int len = 0;

//     while (block) {
//         if (!block->freed) {
//             void *start_add = BLOCK_SHIFT(block);
//             void *end_add = (void *)((char *)start_add + block->size);

//             len = snprintf(buf, sizeof(buf), "%p - %p : %zu bytes\n", start_add, end_add, block->size);
//             write(1, buf, len);

//             total += block->size;
//         }
//         block = block->next;
//     }
//     return (total);
// }

// static void print_heap_header(const char* name, t_heap *heap) {
//     char buf[128];
//     int len;

//     // print heap type and address in hexa
//     len = snprintf(buf, sizeof(buf), "%s : %p\n", name, heap);
//     write(1, buf, len);
// }

// void show_alloc_mem(void) {
//     pthread_mutex_lock(&g_malloc_mutex);

//     t_heap *current_heap = g_heap;
//     size_t total = 0;

//     while (current_heap) {
//         const char *group = (current_heap->group == TINY) ? "TINY" :
//                             (current_heap->group == SMALL) ? "SMALL" : "LARGE";

//         print_heap_header(group, current_heap);
//         if (current_heap->block_count > 0) {
//             size_t heap_total = print_block_list(current_heap->blocks);
//             total += heap_total;
//         }
//         current_heap = current_heap->next;
//     }

//     char total_buf[64];
//     int total_len = snprintf(total_buf, sizeof(total_buf), "Total : %zu bytes\n", total);
//     write(1, total_buf, total_len);

//     pthread_mutex_unlock(&g_malloc_mutex);
// }
