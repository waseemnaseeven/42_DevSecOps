#include "../includes/malloc.h"


__attribute__((constructor)) void run_tests() {
    void    *ptr1 = malloc(100);
    void    *ptr2 = malloc(200);
    free(ptr1);
    free(ptr2);
    // Test with string
    char *str = malloc(14);
    strcpy(str, "Hello, World!");
    printf("Allocated string: %s\n", str);

    // Test with a range of digit
    int *range = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; ++i) {
        range[i] = i + 1;
        printf("Range is : %d", range[i]);
    }

    show_alloc_mem();
}