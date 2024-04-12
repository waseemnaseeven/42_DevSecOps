#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

void ft_strlen_test(void) {

    const char* str = "Hello, World!";

    printf( BOLDWHITE "Testing ft_strlen with string: %s\n", str );
    printf("\n" RESET);
    size_t len = strlen(str);
    size_t myLen = ft_strlen(str);
    printf("Real strlen said : %lu\n", len);
    printf("My assembly strlen: %lu\n", myLen);
    printf("\n");
    if (len == myLen)
        printf(GREEN "PASSED\n" RESET);
    else
        printf(RED "FAILED\n" RESET);

    printf("Test with 0 \n");

    size_t zero = strlen(0);
    size_t myZero = ft_strlen(0);
    
    printf("Real strlen said : %lu\n", zero);
    printf("My assembly strlen: %lu\n", myZero);
    if (zero == myZero)
        printf(GREEN "PASSED\n" RESET);
    else
        printf(RED "FAILED\n" RESET);

    len = strlen(-1);
    myLen = ft_strlen(-1);
    
}