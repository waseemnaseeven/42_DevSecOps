#include "malloc.h"

int main(void)
{
    printf("yo\n");
    u_int8_t* first = mmap((void *) 0xFEEDBEF, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    u_int8_t* second = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

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
}