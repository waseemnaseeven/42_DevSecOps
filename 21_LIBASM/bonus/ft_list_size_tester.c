#include "../functions/includes/libasm_bonus.h"
#include "libasm_tester_bonus.h"
#include "../colors.h"
#include <stdlib.h>

void list_push_front(t_list **begin_list, void *data) {
    
    t_list *new_node = malloc(sizeof(t_list));
    if (new_node == NULL)
        return;

    while (*begin_list != NULL) {
        new_node->data = data;
        new_node->next = *begin_list;
        *begin_list = new_node;
    }

}

int list_size(t_list *begin_list) {
    
    int size = 0;
    
    while (begin_list != NULL)
    {
        size++;
        begin_list = begin_list->next;
    }
    return size;
}

void ft_list_size_test(void) {

    printf(BOLDWHITE "Testing chain list function\n" RESET);

    t_list *lst1 = NULL;

    int array[] = {6, 9, 8, 10, 7};
    int size = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < size; i++){
        list_push_front(&lst1, &array[i]);
    }

    printf(BOLDMAGENTA "Here is my list from the original function: {");
    t_list *tmp = lst1;
    while (tmp != NULL)
    {
        printf("%d, ", (*(int *)(tmp->data)));
        tmp = tmp->next;

    }
    printf("}\n" RESET);

    t_list *lst2 = NULL;

    int arr[] = {5, 3, 1, 4, 2};
    size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++) {
        ft_list_push_front(&lst2, &arr[i]);
    }
    printf(BOLDMAGENTA "Here is my list from the my assembly function: {");
    while (tmp != NULL) {
        printf("%d, ", (*(int *)(tmp->data)));
        tmp = tmp->next;
    }
    printf("}\n" RESET);

    int len1 = list_size(lst1);
    int len2 = ft_list_size(lst1);

    if (len1 == len2)
        printf(GREEN "\nPASSED\n" RESET);
    else
        printf(RED "FAILED\n" RESET);

}