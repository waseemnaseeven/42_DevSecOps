#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

void    ft_strcmp_test(void) {

    char *s1 = "Hello World!";
    char *s2 = "Hello MyWorld!";

    printf("Testing my ft_strcmp with the original strcmp\n");
    printf("I'll compare if the result of my strcmp and the original are the same\n");
    if (strcmp(s1, s2) == ft_strcmp(s1, s2))
        printf(GREEN "\nPASSED\n" RESET);
    else
        printf(RED "\nFAILED\n" RESET);

}