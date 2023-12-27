#include "malloc.h"

int main(void)
{
    int* first = mmap((void *) 0xFEEDBEF, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    int* second = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    printf("First: %p\n", first);
    printf("Second: %p\n", second);


    int page_size = getpagesize();

    printf("Page size: %d bytes\n", page_size);

    long spage_size = sysconf(_SC_PAGESIZE);

    if (spage_size == -1) {
        perror("sysconf");
        return 1;
    }

    printf("Page size: %ld bytes\n", spage_size);

    struct rlimit stack_limit;

    if (getrlimit(RLIMIT_STACK, &stack_limit) == -1) {
        perror("getrlimit");
        return 1;
    }

    if (stack_limit.rlim_cur == RLIM_INFINITY)
        printf("Soft stack limit: Unlimited\n");
    else
        printf("Soft stack limit: %ld\n", (long) stack_limit.rlim_cur);
    if (stack_limit.rlim_max == RLIM_INFINITY)
        printf("Hard stack limit: Unlimited\n");
    else
        printf("Hard stack limit: %ld\n", (long) stack_limit.rlim_max);

    int *tab = ft_malloc(100000);
    printf("tab: %p\n", tab);
    free(tab);
    // char *ptr = malloc(1024);
    // ptr = "Hello world\n";
    // printf("ptr: %p\n", ptr);
    // printf("%s\n", ptr);
}