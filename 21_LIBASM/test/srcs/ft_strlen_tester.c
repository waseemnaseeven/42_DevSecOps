# include "includes/libasm_tester.h"

void ft_strlen_test() {
    char *str = "Hello, World!";

    printf("FT_STRLEN TEST\n", BOLDMAGENTA);
    int len = strlen(str);
    printf("Original: %d\n", RESET, len, GREEN);
}

