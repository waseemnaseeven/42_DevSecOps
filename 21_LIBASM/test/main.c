#include "../functions/includes/libasm.h"
#include "libasm_tester.h"
#include "../colors.h"

int main() {

    printf(BOLDYELLOW "LETS TEST LIBASM\n");
    printf("_________________\n\n" RESET);

    ft_strlen_test();
    printf(BOLDYELLOW "_________________\n\n" RESET);
    ft_strcpy_test();
    printf(BOLDYELLOW "_________________\n\n" RESET);
    ft_strcmp_test();
    printf(BOLDYELLOW "_________________\n\n" RESET);
    ft_strdup_test();
    printf(BOLDYELLOW "_________________\n\n" RESET);
    ft_write_test();
    printf(BOLDYELLOW "_________________\n\n" RESET);
    ft_read_test();



    return (0);
}