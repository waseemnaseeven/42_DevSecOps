#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

void ft_strdup_test(void) {

    char *src = "Hello World!";
    char *dest;
    char *dest1;
    printf("Testing the Original strdup with my function\n");
    
    dest = strdup(src);
    printf(BLUE "original strdup = %s\n", dest);
    dest1 = ft_strdup(src);
    printf("my ft_strdup =  %s\n", dest1);

    if (dest == dest1)
        printf(GREEN "\nPASSED\n" RESET);
    else
        printf(RED "\nFAILED\n" RESET);

}