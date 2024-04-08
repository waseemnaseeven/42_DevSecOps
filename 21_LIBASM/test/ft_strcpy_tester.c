#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

char    *my_strcpy(char *dest, const char *src)
{
    if (!src || !dest)
        return NULL; 
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

void    ft_strcpy_test(void) {
    
        char    src1[100] = "Hello, World!";
        char    dst1[100] = "Hello Tschou";
        char    dst[100] = "Hello Tschou";

        printf(BOLDWHITE "Testing ft_strcpy with the original one\n\n" RESET);
    
        printf("src1: %s\n", src1);
        printf("dst1: %s\n", dst1);
        printf("dst: %s\n\n", dst);
        strcpy(dst1, src1);
        ft_strcpy(dst, src1);
        printf(BLUE "After strcpy dst1: %s\n", dst1);
        printf("After ft_strcpy dst: %s\n", dst);
        printf("\n" RESET);
        size_t len1 = strlen(dst1);
        size_t len = strlen(dst);
        printf("%lu == %lu\n", len1, len);
        printf("\n");
        if (strcmp(dst, dst1) == 0)
            printf(GREEN "PASSED\n" RESET);
        else
            printf(RED "FAILED\n" RESET);
}