#include "../functions/includes/libasm_bonus.h"
#include "libasm_tester_bonus.h"
#include "../colors.h"

int main() {

    printf(BOLDYELLOW "LETS TEST LIBASM BONUS\n");
    printf("_________________\n\n" RESET);

    ft_list_push_front_test();
    printf(BOLDYELLOW "_________________\n\n" RESET);
    ft_list_size_test();
    
    return (0);
}