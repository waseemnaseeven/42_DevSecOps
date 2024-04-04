#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

void ft_strlen_test(void) {

    const char* str = "Hello, World!";

    printf("Testing ft_strlen with string: %s\n", str);
    size_t len = strlen(str);
    size_t myLen = ft_strlen(str);
    printf("Real strlen said : %lu\n", len);
    printf("My assembly strlen: %lu\n", myLen);
    printf("\n");
    if (len == myLen)
        printf(GREEN "PASSED\n" RESET);
    else
        printf(RED "FAILED\n" RESET);
}