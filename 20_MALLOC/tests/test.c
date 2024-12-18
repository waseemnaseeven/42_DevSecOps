#include "../includes/malloc.h"
#include <unistd.h>

void	ft_putchar_fd(char c, int fd) {
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd) {
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(2, fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

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

    free(ptr);
    show_alloc_mem_ex();
}

void test_realloc_decrease() {
    write(1, "\nRunning: test_realloc_decrease\n", 33);
    char *ptr = malloc(50);
    strcpy(ptr, "Hello, this is a long string");
    show_alloc_mem_ex();

    // Réduire à 20 octets
    ptr = realloc(ptr, 20);
    assert(ptr != NULL);
    // Les 20 premiers octets doivent toujours contenir le début de la chaîne
    assert(strncmp(ptr, "Hello, this is a l", 19) == 0); 
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

void run_realloc_tests() {
    test_realloc_increase();
    test_realloc_decrease();
    test_realloc_null();
}

void run_tests() {
    // test_random_size(512, "TINY");
    // test_zero_allocation();
    test_string();
    // test_large_alloc();
    // test_fragmentation();
}

int main(void) {

    write(1, "\nPage size: ", 12);
    ft_putnbr_fd(sysconf(_SC_PAGESIZE), 1);
    write(1, "\n", 1);

    run_tests();
    run_realloc_tests();
    return 0;
}
