#include "../../includes/malloc.h"


void run_tests() {
    
    // Alignment test
    // write(1, "\nRunning: Alignment test\n", 26);
    // void *ptr = malloc(16);
    // assert(((size_t)ptr % 16) == 0); // Using size_t instead of uintptr_t
    // free(ptr);

    // Zero allocation
    // write(1, "\nRunning: Zero allocation test\n", 31);
    // void *ptr0 = malloc(0);
    // assert(ptr0 == NULL);
    // free(ptr0);

    // Simple allocation
    // write(1, "\nRunning: Simple allocation test\n", 34);
    // void *ptr1 = malloc(100);
    // assert(ptr1 != NULL);
    // free(ptr1);

    
    // Allocation and Access
    // write(1, "\nRunning: Allocation and Access test\n", 38);
    // char *ptr2 = malloc(10);
    // for (int i = 0; i < 10; i++) ptr2[i] = 'A';
    // assert(ptr2[0] == 'A' && ptr2[9] == 'A');
    // free(ptr2);

    // Test with string
    write(1, "\nRunning: String test\n", 23);
    char *str = malloc(16);
    strcpy(str, "Hello, World!\n");
    write(1, str, strlen(str));
    free(str);

    // Large Allocation
    write(1, "\nRunning: Large allocation test\n", 33);
    size_t large_size = 1024 * 1024 * 1024; // 1GB
    void *large = malloc(large_size);
    assert(large != NULL);
    free(large);

    // // Test with a range of digits
    write(1, "\nRunning: Range of digits test\n", 31);
    int *range = malloc(5 * sizeof(int));
    char buf[64];
    for (int i = 0; i < 5; ++i) {
        range[i] = i + 1;
        int len = sprintf(buf, "Range is: %d\n", range[i]);
        write(1, buf, len);
    }
    free(range);


    // Fragmentation test
    write(1, "\nRunning: Fragmentation test\n", 30);
    void *frag1 = malloc(100);
    void *frag2 = malloc(200);
    void *frag3 = malloc(300);
    free(frag2);
    void *frag4 = malloc(150);
    assert(frag4 != NULL);
    free(frag1);
    free(frag3);
    free(frag4);

    // // Double free test
    // write(1, "\nRunning: Double free test\n", 28);
    // void *double_free = malloc(50);
    // free(double_free);
    // free(double_free); // Should not crash, but may produce a warning in debug mode.

    // // Freeing NULL pointer
    // write(1, "\nRunning: Freeing NULL pointer test\n", 36);
    // free(NULL); // Should do nothing and not crash.

    // // Freeing invalid pointer
    // write(1, "\nRunning: Freeing invalid pointer test\n", 40);
    // int *invalid_pointer = (int *)12345; // Invalid pointer.
    // free(invalid_pointer); // Should not crash, but behavior is undefined.
}

int main(void) {
    run_tests();
    return 0;
}
