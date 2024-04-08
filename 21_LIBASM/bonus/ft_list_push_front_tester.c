#include "../functions/includes/libasm_bonus.h"
#include "libasm_tester_bonus.h"
#include "../colors.h"
#include <stdlib.h>

void list_push_front(t_list **begin_list, void *data)
{
    t_list *new = malloc(sizeof(t_list));
    if (new == NULL)
        return;
    while (*begin_list != NULL) 
    {
        new->data = data;
        new->next = *begin_list;
        *begin_list = new;
    }
}

void ft_list_push_front_test(void) {

    printf(BOLDWHITE "Testing chain list function\n" RESET);

    t_list *lst = NULL;

    int array[] = {6, 9, 8, 10, 7};
    int size = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < size; i++){
        list_push_front(&lst, &array[i]);
    }

    printf(BOLDMAGENTA "Here is my list: {");
    t_list *tmp = lst;
    while (tmp != NULL)
    {
        printf("%d, ", *(int *)(tmp->data));
        tmp = tmp->next;

    }
    printf("}" RESET);
    int arr[] = {5, 3, 1, 4, 2};
    size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++){
        ft_list_push_front(&lst, &arr[i]);
    }
}