#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

void ft_strlen_test(void) {

    const char* str = "Hello, World!";

    printf("Testing ft_strlen with string: %s\n", str);
    printf("Real strlen said : %lu\n", strlen(str));
    // printf("My assembly strlen: %lu\n", ft_strlen(str));
    printf("\n");
    if (strlen(str) == 12)
        printf(GREEN "PASSED\n" RESET);
    else
        printf(RED "FAILED\n" RESET);
    printf("\n");
}