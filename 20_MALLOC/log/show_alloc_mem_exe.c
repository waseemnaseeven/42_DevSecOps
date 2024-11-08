void show_alloc_mem_ex(void)
{
    pthread_mutex_lock(&g_malloc_mutex);

    t_heap *current_heap = g_heap;
    while (current_heap)
    {
        printf("%s : %p\n", (current_heap->group == TINY) ? "TINY" :
                               (current_heap->group == SMALL) ? "SMALL" : "LARGE", current_heap);
        printf("  Total size: %zu, Free size: %zu, Block count: %zu\n",
               current_heap->total_size, current_heap->free_size, current_heap->block_count);
        t_block *current_block = current_heap->blocks;
        while (current_block)
        {
            printf("  Block at %p - Size: %zu, Freed: %s\n", BLOCK_SHIFT(current_block),
                   current_block->size, current_block->freed ? "Yes" : "No");
            current_block = current_block->next;
        }
        current_heap = current_heap->next;
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}
