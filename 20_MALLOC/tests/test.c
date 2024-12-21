#include "../includes/malloc.h"

void show_alloc_mem_ex(void);


void test_realloc_increase() {
    write(1, "\nRunning: test_realloc_increase\n", 33);
    char *ptr = malloc(10);
    strcpy(ptr, "12345"); // 5 chars + '\0'
    show_alloc_mem_ex();

    // Augmenter à 20 octets
    ptr = realloc(ptr, 20);
    assert(ptr != NULL);
    // Vérifier que les données sont toujours là
    assert(strcmp(ptr, "12345") == 0);
    show_alloc_mem_ex();
    ptr = realloc(ptr, 1024);
    assert(ptr != NULL);
    assert(strcmp(ptr, "12345") == 0);
    show_alloc_mem_ex();

    free(ptr);
    show_alloc_mem_ex();
}

void test_realloc_null() {
    write(1, "\nRunning: test_realloc_null\n", 29);

    // realloc(NULL, size) doit se comporter comme malloc
    char *ptr = realloc(NULL, 10);
    assert(ptr != NULL);
    strcpy(ptr, "Test");
    show_alloc_mem_ex();

    // realloc(ptr, 0) doit se comporter comme free(ptr)
    ptr = realloc(ptr, 0);
    assert(ptr == NULL);
    show_alloc_mem_ex();
}


void test_random_size(size_t alloc_size, char *group_size) {

    write(1, "Group size is : ", 15);
    write(1, group_size, strlen(group_size));
    write(1, "\n", 1);

    const size_t size = 10;
    void *array[size];
    size_t i = -1;

    while (++i < size) {
        array[i] = malloc(alloc_size);
        show_alloc_mem_ex();
    }
    i = -1;

    while (++i < size) {
        free(array[i]);
        show_alloc_mem_ex();
    }

}

void test_zero_allocation() {
    write(1, "\nRunning: Zero allocation test\n", 31);
    void *ptr0 = malloc(0);
    show_alloc_mem_ex();
    assert(ptr0 == NULL);
    free(ptr0);
    show_alloc_mem_ex();
}

// Test with string
void test_string() {
    write(1, "\nRunning: String test\n", 23);
    char *str = malloc(15);
    strcpy(str, "Hello, World!\n");
    show_alloc_mem_ex();
    write(1, str, strlen(str));
    free(str);
    show_alloc_mem_ex();
}

// Large Allocation
void test_large_alloc() {
    write(1, "\nRunning: Large allocation test\n", 33);
    size_t large_size = 1024 * 1024 * 1024; // 1GB
    void *large = malloc(large_size);
    assert(large != NULL);
    show_alloc_mem_ex();
    free(large);
    show_alloc_mem_ex();
}

// Fragmentation test
void test_fragmentation() {

    write(1, "\nRunning: Fragmentation test\n", 30);
    void *frag1 = malloc(100);
    show_alloc_mem_ex();
    void *frag2 = malloc(200);
    show_alloc_mem_ex();
    void *frag3 = malloc(300);
    show_alloc_mem_ex();
    void *frag4 = malloc(150);
    show_alloc_mem_ex();
    free(frag2);
    show_alloc_mem_ex();
    free(frag3);
    show_alloc_mem_ex();
    void *take_again_frag2 = malloc(200);
    show_alloc_mem_ex();
    void *take_again_frag3 = malloc(350);
    show_alloc_mem_ex();
    free(frag1);
    show_alloc_mem_ex();
    free(frag4);
    show_alloc_mem_ex();
    free(take_again_frag2);
    show_alloc_mem_ex();
    free(take_again_frag3);
    show_alloc_mem_ex();
}

void test_range_digits() {
    write(1, "\nRunning: Range of digits test\n", 31);
    int *range = malloc(5 * sizeof(int));
    char buf[64];
    for (int i = 0; i < 5; ++i) {
        range[i] = i + 1;
        int len = sprintf(buf, "Range is: %d\n", range[i]);
        write(1, buf, len);
    }
    show_alloc_mem_ex();
    free(range);
    show_alloc_mem_ex();
}

void *test_thread() {
    pthread_t *thread = malloc(sizeof(pthread_t) * 100);
    void *ret = malloc(80);
    pthread_exit(NULL);
    return ret;
}

void run_realloc_tests() {
    // test_realloc_increase();
    // test_realloc_null();
}

void run_tests() {
    // test_random_size(512, "TINY");
    // test_random_size(2048, "SMALL");
    // test_random_size(1024)
    // test_zero_allocation();
    test_string();
    // test_large_alloc();
    test_fragmentation();
    test_thread();
}

int main(void) {

    write(1, "\nPage size: ", 12);
    ft_putnbr_fd(sysconf(_SC_PAGESIZE), 1);
    write(1, "\n", 1);

    run_tests();
    run_realloc_tests();
    return 0;
}
