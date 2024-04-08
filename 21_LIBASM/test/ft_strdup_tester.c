#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

void ft_strdup_test(void) {

    char *src = "Hello World!";
    char *src1 = "Hello World!";
    char *dest;
    char *dest1 = NULL;
    printf(BOLDWHITE "Testing the Original strdup with my function\n" RESET);
    
    dest = strdup(src);
    if (dest == NULL)
        printf(BOLDCYAN "NULL strdup\n");
    printf(BLUE "Original strdup = %s\n", dest);
    dest1 = ft_strdup(src1);
    if (dest1 == NULL)
        printf(BOLDCYAN "NULL ft_strdup\n" RESET);
    printf("My ft_strdup =  %s\n", dest1);

}